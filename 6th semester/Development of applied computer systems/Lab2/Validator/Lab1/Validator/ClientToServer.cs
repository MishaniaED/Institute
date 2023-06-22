using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Grpc.Net.Client;
using Validator.ValidServerNamespace;
using Models;

namespace Validator
{
    public class ClientToServer
    {
        private static readonly HttpClientHandler unsafeHandler = new HttpClientHandler();
        private GrpcChannel channel = GrpcChannel.ForAddress("https://localhost:5001", new GrpcChannelOptions
        {
            HttpHandler = unsafeHandler
        });
        private ValidServer.ValidServerClient client;

        public delegate void GuidToVM(string curguid);

        public static event GuidToVM guidEvent;

        public ClientToServer()
        {
            unsafeHandler.ServerCertificateCustomValidationCallback = HttpClientHandler.DangerousAcceptAnyServerCertificateValidator;
            client = new ValidServer.ValidServerClient(channel);
        }

        public async Task<List<bool>> SendToServer(Card curinfo)
        {
            var reply = await client.SendInfoForValidationAsync(new InfoStructure
            {
                Fio = curinfo.Fio,
                Phones = curinfo.Phones,
                Emails = curinfo.Emails,
                Adresses = curinfo.Address,
                Pasport = curinfo.Pasport,
                Birthday = curinfo.BirthDay.ToString()
            });
            List<bool> result = new List<bool>();
            result.Add(reply.Fio);
            result.Add(reply.Phones);
            result.Add(reply.Emails);
            result.Add(reply.Adresses);
            result.Add(reply.Pasport);
            result.Add(reply.Birthday);
            guidEvent(reply.CurGuid);

            return result;
        }
    }
}
