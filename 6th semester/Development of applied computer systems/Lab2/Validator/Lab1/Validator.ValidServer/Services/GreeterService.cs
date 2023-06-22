using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using Validator.ValidServer;

namespace Validator.ValidServerNamespace
{
    public class ValidServerService : ValidServer.ValidServerBase
    {
        private readonly ILogger<ValidServerService> _logger;
        private Dictionary <string, Message> _requests = new Dictionary<string, Message>();
        private CheckerService service;
        public ValidServerService(ILogger<ValidServerService> logger)
        {
            service = CheckerService.GetCheckerService();
            _logger = logger;
        }

        public override Task<HelloReply> SayHello(HelloRequest request, ServerCallContext context)
        {
            return Task.FromResult(new HelloReply
            {
                Message = "Hello " + request.Name
            });
        }

        public override Task<ValidationInfo> SendInfoForValidation(InfoStructure request, ServerCallContext context)
        {
            List<bool> result = new List<bool>(6);
            Message currentMess = new Message(request.Fio, request.Phones, request.Emails, request.Adresses, request.Pasport, request.Birthday);

            result.Add(service.CheckFIO(currentMess.Fio));
            result.Add(service.CheckTelephoneNum(currentMess.PhoneNumber));
            result.Add(service.CheckEmail(currentMess.Emails));
            result.Add(service.CheckAdress(currentMess.Address));
            result.Add(service.CheckPassportNum(currentMess.PassportNumber));
            result.Add(service.CheckDateOfBirth(currentMess.BirthDay));
            var guid = Guid.NewGuid().ToString("N");
            _requests[guid] = currentMess;

            return Task.FromResult(new ValidationInfo
            {
                Fio = result[0],
                Phones = result[1],
                Emails = result[2],
                Adresses = result[3],
                Pasport = result[4],
                Birthday = result[5],
                CurGuid = guid
            });
        }
    }
}
