using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    internal interface ISym_Encrypt // 3
    {
        byte[] Encrypt(byte[] text);

        byte[] Decrypt(byte[] text);
    }
}
