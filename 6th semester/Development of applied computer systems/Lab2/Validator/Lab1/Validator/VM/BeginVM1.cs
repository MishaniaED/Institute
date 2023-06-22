using System.Collections.Generic;
using System.Windows;
using System.Windows.Input;
using System.Linq;
using Base;
using System;
using Models;
using Validator;
using System.Text;

namespace Validator.VM
{
    internal sealed class BeginVM1 : VMBase
    {

        #region IComands

        private ICommand _curCommand;

        #endregion

        private ClientToServer client = new ClientToServer();
        private bool _canExecute = true;
        public bool _fSBool = false;
        private List<string> nameParsed = new List<string>();
        private string name = "Введите имя фамилию отчество";
        private char[] delimiterChars = { ' ', ',' };

        private string phones = "";
        private List<string> phonesParsed = new List<string>();

        private string emails = "";
        private List<string> emailsParsed = new List<string>();

        private string adress = "";
        private List<string> adressParsed = new List<string>();

        private string pasport = "";
        private string validationResult = "";
        private readonly string[] fields = new string[]{ "ФИО", "Телефонах", "Адресах почтовых ящиков", "Адресах проживания", "Номере паспорта", "Дате рождения" };
        private string guid = "";
        private DateTime birthDateD;

        #region Fields

        public string Guid
        {
            get
            {
                return guid;
            }
            set
            {
                guid = value;
                OnPropertiesChanged(nameof(guid));
            }
        }
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                nameParsed = value.Split(" ").ToList();
                name = value;
                OnPropertiesChanged(nameof(name));
            }
        }

        public string Phones
        {
            get
            {
                return phones;
            }
            set
            {
                phonesParsed = value.Split(delimiterChars).ToList();
                phones = value;
                OnPropertiesChanged(nameof(phones));
            }
        }

        public string Emails
        {
            get
            {
                return emails;
            }
            set
            {
                emailsParsed = value.Split(delimiterChars).ToList();
                emails = value;
                OnPropertiesChanged(nameof(emails));
            }
        }

        public string Adress
        {
            get
            {
                return adress;
            }
            set
            {
                emailsParsed = value.Split(";").ToList();
                adress = value;
                OnPropertiesChanged(nameof(adress));
            }
        }

        public string Pasport
        {
            get
            {
                return pasport;
            }
            set
            {
                pasport = value;
                OnPropertiesChanged(nameof(pasport));
            }
        }

        public DateTime BirthDateD
        {
            get
            {
                return birthDateD;
            }
            set
            {
                birthDateD = value;
                OnPropertiesChanged(nameof(birthDateD));
            }
        }

        public string ValidationResult
        {
            get =>
                validationResult;
            private set
            {
                validationResult = value;
                OnPropertiesChanged(nameof(validationResult));
            }
        }
        public bool CanExecute
        {
            get =>
                _canExecute;

            private set
            {
                _canExecute = value;
                OnPropertyChanged(nameof(CanExecute));
            }
        }

        #endregion

        public BeginVM1()
        {
            ClientToServer.guidEvent += GuidToVM;
        }

        #region ICommand Functions

        public ICommand SendInfoCommand =>
            _curCommand ??= new Relay(_ => SendInfo(), _ => CanExecute);

        private async void SendInfo()
        {
            Card curinfo = new Card();
            curinfo.Fio = name;
            curinfo.Phones = phones;
            curinfo.Emails = emails;
            curinfo.Address = adress;
            curinfo.Pasport = pasport;
            curinfo.BirthDay = birthDateD;

            List<bool> result = await client.SendToServer(curinfo);
            ResultChange(result);
        }

        public void GuidToVM(string curGuid)
        {
            Guid = curGuid;
        }

        private void ResultChange(List<bool> res)
        {
            StringBuilder tmp = new StringBuilder();

            if (!res.Contains(false))
                tmp.Append("Данные корректны!");
            else
            {
                tmp.Append("Данные не корректны!" + Environment.NewLine);
                tmp.Append("Ошибки в: " + Environment.NewLine);

                for (int i = 0; i < res.Count; i++)
                {
                    if (!res[i])
                        tmp.Append(fields[i] + Environment.NewLine);

                }
            }
            ValidationResult = tmp.ToString();
        }
        #endregion

    }
}
