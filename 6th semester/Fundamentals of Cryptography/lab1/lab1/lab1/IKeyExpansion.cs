using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    internal interface IRound_generation // 1
    {
        byte[][] GenerateKeys(byte[] key64b);
    }
}
