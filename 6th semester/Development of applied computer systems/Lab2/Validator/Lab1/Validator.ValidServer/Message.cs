using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Threading.Tasks;

namespace Validator.ValidServer
{
    public class Message : ICloneable
    {
        private List<string> fio;
        private List<string> emails;
        private List<string> phoneNumber;
        private List<string> address;
        private string passportNumber;
        private string birthDay;

        public Message()
        {
            Emails = new List<string>();
            PhoneNumber = new List<string>();
            Address = new List<string>();
        }

        public Message(string fio, string phone, string email, string adress, string pasport, string birthday)
        {
            Fio = ParseFio(fio);
            PhoneNumber = ParsePhoneNumbers(phone);
            Emails = ParseEmails(email);
            Address = ParseAdresses(adress);
            PassportNumber = pasport;
            BirthDay = birthday;
        }

        public List<string> Fio { get; set; }

        public string PassportNumber { get; set; }

        public List<string> PhoneNumber { get; set; }

        public List<string> Emails { get; set; }

        public List<string> Address { get; set; }

        public string BirthDay { get; set; }

        public object Clone()
            => new Message()
            {
                Fio = Fio.ToList(),
                PassportNumber = PassportNumber,
                PhoneNumber = PhoneNumber.ToList(),
                Emails = Emails.ToList(),
                Address = Address.ToList(),
                BirthDay = BirthDay
            };

        public List<string> ParseFio(string str)
        {
            var tmp = str.Split(" ");
            List<string> list = tmp.ToList();
            return list;
        }
        public List<string> ParseEmails(string str)
        {
            var tmp = str.Split(", ");
            List<string> list = tmp.ToList();
            return list;
        }

        public List<string> ParsePhoneNumbers(string str)
        {
            var tmp = str.Split(", ");
            List<string> list = tmp.ToList();
            return list;
        }

        public List<string> ParseAdresses(string str)
        {
            var tmp = str.Split(";");
            List<string> list = tmp.ToList();
            return list;
        }
    }
}
