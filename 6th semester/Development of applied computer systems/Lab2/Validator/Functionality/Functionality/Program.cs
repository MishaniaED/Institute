using System.Globalization;
using System.Text.RegularExpressions;

public class Message : ICloneable
{
    private string name, surname, middleName, passportNumber;
    private List<string> emails;
    private List<string> phoneNumber;
    private List<string> address;
    private string birthDay;

    public Message()
    {
        Emails = new List<string>();
        PhoneNumber = new List<string>();
        Address = new List<string>();
    }

    public string Name { get; set; }

    public string Surname { get; set; }

    public string MiddleName { get; set; }

    public string PassportNumber { get; set; }

    public List<string> PhoneNumber { get; set; }

    public List<string> Emails { get; set; }

    public List<string> Address { get; set; }

    public string BirthDay { get; set; }

    public object Clone()
        => new Message()
        {
            Name = Name,
            Surname = Surname,
            MiddleName = MiddleName,
            PassportNumber = PassportNumber,
            PhoneNumber = PhoneNumber.ToList(),
            Emails = Emails.ToList(),
            Address = Address.ToList(),
            BirthDay = BirthDay
        };

    public bool CheckFIO()
    {
        if (!Char.IsUpper(Name[0]) || !Char.IsUpper(Surname[0]) || !Char.IsUpper(MiddleName[0]) || !Char.IsLetter(Name[0]) ||
            !Char.IsLetter(Surname[0]) || !Char.IsLetter(MiddleName[0]) || Name.Length == 0 || Surname.Length == 0 || MiddleName.Length == 0)
            return false;

        for (int i = 1; i < Name.Length; i++)
        {
            if (Char.IsUpper(Name[i]) || !Char.IsLetter(Name[i])) return false;
        }
        for (int i = 1; i < Surname.Length; i++)
        {
            if (Char.IsUpper(Surname[i]) || !Char.IsLetter(Surname[i])) return false;
        }
        for (int i = 1; i < MiddleName.Length; i++)
        {
            if (Char.IsUpper(MiddleName[i]) || !Char.IsLetter(MiddleName[i])) return false;
        }

        return true;
    }
    public bool CheckTelephoneNum()
    {
        if (PhoneNumber.Count == 0) return false;
        foreach (var list in PhoneNumber)
        {
            if (list.Length != 10 || list[0] == '0') return false;
            for (int i = 0; i < list.Length; i++)
                if (!Char.IsDigit(list[i])) return false;
        }
        return true;
    }

    public bool CheckEmail()
    {
        if (Emails.Count == 0) return false;
        foreach (var email in Emails)
        {
            if (string.IsNullOrWhiteSpace(email)) return false;
            if (email[0] == '.' || email[email.Length - 1] == '.') return false;
            string[] str = email.Split('@');
            if (str.Count() != 2) return false;
            if (str[0].Length < 1 || str[0].Length > 64 || str[1].Split('.').Count() < 1 || str[1].Length > 253 || email.Length > 256) return false;
        }
        return true;
    }


    public bool CheckAdress()
    {
        if (Address.Count == 0) return false;
        foreach (var address in Address)
        {
            if (string.IsNullOrWhiteSpace(address)) return false;
        }
        return true;
    }

    public bool CheckPassportNum()
    {
        // проверить что в нем только числа и их определенное кол-во
        if (string.IsNullOrWhiteSpace(PassportNumber)) return false;
        var str = PassportNumber.Split(' ');
        if (str.Count() < 2) return false;
        if (str.LastOrDefault().Length != 6) return false;
        foreach (var tmp in PassportNumber)
        {
            if (!Char.IsDigit(tmp) && tmp != ' ') return false;
        }
        return true;
    }

    public bool CheckDateOfBirth()
    {
        DateTime dt;
        if (!DateTime.TryParse(BirthDay, CultureInfo.CurrentCulture, DateTimeStyles.None, out dt))
        {
            return false;
        }
        if (dt > DateTime.Today) return false;
        return true;
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
        var tmp = str.Split(", ");
        List<string> list = tmp.ToList();
        return list;
    }
}