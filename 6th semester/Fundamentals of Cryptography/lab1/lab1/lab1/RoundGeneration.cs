using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    public class RoundGeneration : IRound_generation
    {
        byte[][] IRound_generation.GenerateKeys(byte[] key64b)
        {
            byte[][] keys48b = new byte[16][];
            for(int i = 0; i < 16; i++)
            {
                keys48b[i] = new byte[8];
            }
            UInt64 tmp = BitConverter.ToUInt64(key64b);
            UInt32 L = ((uint)(tmp >> 32)), R = (uint)(tmp);
            Utilities.key_permutation_56bits_to_28bits(BitConverter.ToUInt64(key64b), ref L, ref R);
            Utilities.key_expansion_to_48bits(L,R,keys48b);
            return keys48b;
        }
    }
}
