using System;
using System.Collections.Generic;
using System.Linq;

namespace Models
{
    public class Card
    {
        private string fio;
        private string phones;
        private string emails;
        private string address;
        private string pasport;
        private DateTime birthDay;

        public Card()
        {
/*            Phones = new List<string>();
            Emails = new List<string>();
            Address = new List<string>();*/
        }

        public string Fio
        {
            get => fio;
            set => fio = value;
        }

        public string Phones
        {
            get => phones;
            set => phones = value;
        }

        public string Emails
        {
            get => emails;
            set => emails = value;
        }
        public string Address
        {
            get => address;
            set => address = value;
        }
        public string Pasport
        {
            get => pasport;
            set => pasport = value;
        }
        public DateTime BirthDay
        {
            get => birthDay;
            set => birthDay = value;
        }
    }
}
