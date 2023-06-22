using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    internal class FeistelCipher : ISym_Encrypt
    {
        private IRound_generation roundKeysGen;
        private IF_function Feistel_f;
        private byte[][] roundKeys;

        public FeistelCipher(IRound_generation key, IF_function feistel_f, byte[] origkeys)
        {
            this.roundKeysGen = key;
            Feistel_f = feistel_f;
            this.roundKeys = key.GenerateKeys(origkeys);
        }

        public byte[] Decrypt(byte[] block)
        {
            UInt64 tmp = Utilities.InitialPermutation(BitConverter.ToUInt64(block));
            UInt32 L = ((uint)(tmp >> 32)), R = (uint)(tmp);
            for (int round = 15; round >= 0; --round)
            {
                (R, L) = (L, Feistel_f.Transform(L, roundKeys[round]) ^ R);
            }
            (R, L) = (L, R);
            tmp = L;
            tmp = (tmp << 32) | R;
            return BitConverter.GetBytes(Utilities.FinalPermutation(tmp));
        }

        public byte[] Encrypt(byte[] block)
        {
            UInt64 tmp = Utilities.InitialPermutation(BitConverter.ToUInt64(block));
            UInt32 L = ((uint)(tmp >> 32)), R = (uint)(tmp);
            for (int round = 0; round < 16; ++round)
            {
                (R, L) = (Feistel_f.Transform(R, roundKeys[round]) ^ L, R);
            }
            (R, L) = (L, R);
            tmp = L;
            tmp = (tmp << 32) | R;
            return BitConverter.GetBytes(Utilities.FinalPermutation(tmp));
        }
    }
}
