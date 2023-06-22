using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Threading.Tasks;

namespace Validator.ValidServer
{
    public class CheckerService
    {
        private static CheckerService service = null;
        private CheckerService() { }

        public static CheckerService GetCheckerService()
        {
            if (service == null)
            {
                service = new CheckerService();
            }
            return service;
        }
        public bool CheckFIO(List<string> fioData)
        {
            if (fioData.Count != 3) return false;
            if (!Char.IsUpper(fioData[1][0]) || !Char.IsUpper(fioData[0][0]) || !Char.IsUpper(fioData[2][0]) || !Char.IsLetter(fioData[1][0]) ||
                !Char.IsLetter(fioData[0][0]) || !Char.IsLetter(fioData[2][0]) || fioData[0].Length == 0 || fioData[1].Length == 0 || fioData[2].Length == 0)
                return false;

            for (int i = 1; i < fioData[1].Length; i++)
            {
                if (Char.IsUpper(fioData[1][i]) || !Char.IsLetter(fioData[1][i])) return false;
            }
            for (int i = 1; i < fioData[0].Length; i++)
            {
                if (Char.IsUpper(fioData[0][i]) || !Char.IsLetter(fioData[0][i])) return false;
            }
            for (int i = 1; i < fioData[2].Length; i++)
            {
                if (Char.IsUpper(fioData[2][i]) || !Char.IsLetter(fioData[2][i])) return false;
            }

            return true;
        }
        public bool CheckTelephoneNum(List<string> phoneData)
        {
            if (phoneData.Count == 0) return false;
            foreach (var list in phoneData)
            {
                if (list.Length != 11 || list[0] == '0' || list.Contains(' ')) return false;
                for (int i = 0; i < list.Length; i++)
                    if (!Char.IsDigit(list[i])) return false;
            }
            return true;
        }

        public bool CheckEmail(List<string> emailData)
        {
            if (emailData.Count == 0) return false;
            foreach (var email in emailData)
            {
                if (string.IsNullOrWhiteSpace(email)) return false;
                if (email[0] == '.' || email[email.Length - 1] == '.' || email.Contains(' ')) return false;
                string[] str = email.Split('@');
                if (str.Count() != 2) return false;
                if (str[0].Length < 1 || str[0].Length > 64 || str[1].Split('.').Count() < 1 || str[1].Length > 253 || email.Length > 256) return false;
            }
            return true;
        }


        public bool CheckAdress(List<string> adressData)
        {
            if (adressData.Count == 0) return false;
            foreach (var address in adressData)
            {
                if (string.IsNullOrWhiteSpace(address)) return false;
            }
            return true;
        }

        public bool CheckPassportNum(string pasportData)
        {
            // проверить что в нем только числа и их определенное кол-во
            if (string.IsNullOrWhiteSpace(pasportData)) return false;
            var str = pasportData.Split(' ');
            if (str.Count() < 2 || str.Count() > 4) return false;
            if (str.LastOrDefault().Length != 6) return false;
            foreach (var tmp in pasportData)
            {
                if (!Char.IsDigit(tmp) && tmp != ' ') return false;
            }
            return true;
        }

        public bool CheckDateOfBirth(string data)
        {
            DateTime dt;
            if (!DateTime.TryParse(data, CultureInfo.CurrentCulture, DateTimeStyles.None, out dt))
            {
                return false;
            }
            if (dt > DateTime.Today) return false;
            return true;
        }
    }
}
