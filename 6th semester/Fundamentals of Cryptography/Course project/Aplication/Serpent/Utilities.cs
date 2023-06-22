using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Serpent
{
    internal class Utilities
    {
        // данные для начальной перестановки    
        private static readonly byte[] IP = {
    0, 32, 64, 96, 1, 33, 65, 97, 2, 34, 66, 98, 3, 35, 67, 99,
    4, 36, 68, 100, 5, 37, 69, 101, 6, 38, 70, 102, 7, 39, 71, 103,
    8, 40, 72, 104, 9, 41, 73, 105, 10, 42, 74, 106, 11, 43, 75, 107,
    12, 44, 76, 108, 13, 45, 77, 109, 14, 46, 78, 110, 15, 47, 79, 111,
    16, 48, 80, 112, 17, 49, 81, 113, 18, 50, 82, 114, 19, 51, 83, 115,
    20, 52, 84, 116, 21, 53, 85, 117, 22, 54, 86, 118, 23, 55, 87, 119,
    24, 56, 88, 120, 25, 57, 89, 121, 26, 58, 90, 122, 27, 59, 91, 123,
    28, 60, 92, 124, 29, 61, 93, 125, 30, 62, 94, 126, 31, 63, 95, 127
};
        // данные для конечной перестановки    
        private static readonly byte[] FP = {
    0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60,
    64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124,
    1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61,
    65, 69, 73, 77, 81, 85, 89, 93, 97, 101, 105, 109, 113, 117, 121, 125,
    2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62,
    66, 70, 74, 78, 82, 86, 90, 94, 98, 102, 106, 110, 114, 118, 122, 126,
    3, 7, 11, 15, 19, 23, 27, 31, 35, 39, 43, 47, 51, 55, 59, 63,
    67, 71, 75, 79, 83, 87, 91, 95, 99, 103, 107, 111, 115, 119, 123, 127
};
        // данные для работы s-box  
        private static readonly byte[,] sboxLogic =
{
    { 3, 8, 15, 1, 10, 6, 5, 11, 14, 13, 4, 2, 7, 0, 9, 12 },
    { 15, 12, 2, 7, 9, 0, 5, 10, 1, 11, 14, 8, 6, 13, 3, 4 },
    { 8, 6, 7, 9, 3, 12, 10, 15, 13, 1, 14, 4, 0, 11, 5, 2 },
    { 0, 15, 11, 8, 12, 9, 6, 3, 13, 1, 2, 4, 10, 7, 5, 14 },
    { 1, 15, 8, 3, 12, 0, 11, 6, 2, 5, 4, 10, 9, 14, 7, 13 },
    { 15, 5, 2, 11, 4, 10, 9, 12, 0, 3, 14, 8, 13, 6, 7, 1 },
    { 7, 2, 12, 5, 8, 4, 6, 11, 14, 9, 1, 15, 13, 3, 10, 0 },
    { 1, 13, 15, 0, 14, 8, 2, 11, 7, 4, 12, 10, 9, 3, 5, 6 }
};
        // данные для работы инвертированных s-box  
        private static readonly byte[,] sboxLogicInverse =
{
    { 13, 3, 11, 0, 10, 6, 5, 12, 1, 14, 4, 7, 15, 9, 8, 2 },
    { 5, 8, 2, 14, 15, 6, 12, 3, 11, 4, 7, 9, 1, 13, 10, 0 },
    {  12, 9, 15, 4, 11, 14, 1, 2, 0, 3, 6, 13, 5, 8, 10, 7 },
    {  0, 9, 10, 7, 11, 14, 6, 13, 3, 5, 12, 2, 4, 8, 15, 1 },
    {  5, 0, 8, 3, 10, 9, 7, 14, 2, 12, 11, 6, 4, 15, 13, 1 },
    {  8, 15, 2, 9, 4, 1, 13, 14, 11, 6, 5, 3, 7, 12, 10, 0 },
    {  15, 10, 1, 13, 5, 3, 6, 0, 4, 9, 14, 7, 2, 12, 8, 11 },
    {  3, 0, 6, 13, 9, 14, 15, 8, 5, 12, 11, 7, 10, 1, 4, 2 }
};

       /* public static byte[] Transform(byte[] block, byte[][] keys)
        {
            InitialPermutation(block);
            for (int i = 0; i < 31; i++)
                Round(i % 8, block, keys[i]);
            LastRound(block, keys);
            FinalPermutation(block);
            return block;
        }

        public static byte[] InverseTransform(byte[] block, byte[][] keys)
        {
            Utilities.InitialPermutation(block);
            Utilities.InverseLastRound(block, keys);
            for (int i = 30; i >= 0; i--)
                Utilities.InverseRound(i % 8, block, keys[i]);
            Utilities.FinalPermutation(block);
            return block;
        }*/

        public static byte[][] GetByts(ref byte[] text)
        {
            CheckLenght(ref text);
            byte[][] blocks = new byte[text.Length / 16][];
            for (int i = 0; i < text.Length / 16; ++i)
            {
                blocks[i] = new byte[16];
                for (byte j = 0; j < 16; ++j)
                {
                    blocks[i][j] = text[i * 16 + j];
                }
            }
            return blocks;
        }

        public static void CheckLenght(ref byte[] bytes)
        {
            int padding = bytes.Length % 16;
            if (padding > 0)
            {
                padding = 16 - padding;
                Array.Resize(ref bytes, bytes.Length + padding);
                for (int i = bytes.Length - 1; i >= bytes.Length - padding; --i)
                {
                    bytes[i] = (byte)padding;
                }
            }
        }

        public static uint ROTL(uint tmp, int n)
        {
            return (tmp << n) | (tmp >> (sizeof(uint) * 8 - n));
        }
        public static uint ROTR(uint tmp, int n)
        {
            return (tmp >> n) | (tmp << (sizeof(uint) * 8 - n)); ;
        }

        public static void KeyExpansion(ref byte[] key)
        {
            int padding = 32 - key.Length % 32;
            if (padding != 0)
            {
                // прибавляется единичный бит справа, за ним следуют нулевые биты.
                Array.Resize(ref key, 32);
                BitArray new_key = new BitArray(key); // 256
                new_key.Set((32 - padding) * 8 + 1, true); // скорее всего неправильно устанавливается правый бит
                new_key.CopyTo(key, 0);
            }
        }

        public static void XOR(byte[] buffer1, byte[] buffer2)
        {
            for(int i=0;i<buffer1.Length;++i)
            {
                buffer1[i] ^= buffer2[i];
            }
        }

        public static void InverseRound(int j, byte[] block, byte[] currentKey)
        {
            InverseLineralTransformation(block);
            InverseSubstitution(j, block);
            XOR(block, currentKey);
        }
        public static void Round(int j, byte[] block, byte[] currentKey)
        {
            XOR(block, currentKey);
            Substitution(j, block);
            LineralTransformation(block);
        }

        public static void LastRound(byte[] block, byte[][] keys)
        {
            XOR(block, keys[31]);
            Substitution(7, block);
            XOR(block, keys[32]);
        }
        public static void InverseLastRound(byte[] block, byte[][] keys)
        {
            XOR(block, keys[32]);
            InverseSubstitution(7, block);
            XOR(block, keys[31]);
        }

        private static void InverseLineralTransformation(byte[] block)
        {
            UInt32 X0 = (uint)(block[3] | (block[2] << 8) | (block[1] << 16) | (block[0] << 24));
            UInt32 X1 = (uint)(block[7] | (block[6] << 8) | (block[5] << 16) | (block[4] << 24));
            UInt32 X2 = (uint)(block[11] | (block[10] << 8) | (block[9] << 16) | (block[8] << 24));
            UInt32 X3 = (uint)(block[15] | (block[14] << 8) | (block[13] << 16) | (block[12] << 24));

            X2 = ROTR(X2, 22); 
            X0 = ROTR(X0, 5);
            X2 ^= X3 ^ (X1 << 7);
            X0 ^= X1 ^ X3;
            X3 = ROTR(X3, 7);
            X1 = ROTR(X1, 1);
            X3 ^= X2 ^ (X0 << 3);
            X1 ^= X0 ^ X2;
            X2 = ROTR(X2, 3);
            X0 = ROTR(X0, 13);

            block[0] = (byte)(X0 >> 24 & 0xFF);
            block[1] = (byte)(X0 >> 16 & 0xFF);
            block[2] = (byte)(X0 >> 8 & 0xFF);
            block[3] = (byte)(X0 & 0xFF);

            block[4] = (byte)(X1 >> 24 & 0xFF);
            block[5] = (byte)(X1 >> 16 & 0xFF);
            block[6] = (byte)(X1 >> 8 & 0xFF);
            block[7] = (byte)(X1 & 0xFF);

            block[8] = (byte)(X2 >> 24 & 0xFF);
            block[9] = (byte)(X2 >> 16 & 0xFF);
            block[10] = (byte)(X2 >> 8 & 0xFF);
            block[11] = (byte)(X2 & 0xFF);

            block[12] = (byte)(X3 >> 24 & 0xFF);
            block[13] = (byte)(X3 >> 16 & 0xFF);
            block[14] = (byte)(X3 >> 8 & 0xFF);
            block[15] = (byte)(X3 & 0xFF);
        }
        private static void LineralTransformation(byte[] block)
        {
            UInt32 X0 = (uint)(block[3] | (block[2] << 8) | (block[1] << 16) | (block[0] << 24));
            UInt32 X1 = (uint)(block[7] | (block[6] << 8) | (block[5] << 16) | (block[4] << 24));
            UInt32 X2 = (uint)(block[11] | (block[10] << 8) | (block[9] << 16) | (block[8] << 24));
            UInt32 X3 = (uint)(block[15] | (block[14] << 8) | (block[13] << 16) | (block[12] << 24));

            X0 = ROTL(X0, 13);
            X2 = ROTL(X2, 3);
            X1 ^= X0 ^ X2; 
            X3 ^= X2 ^ (X0 << 3);
            X1 = ROTL(X1, 1);
            X3 = ROTL(X3, 7);
            X0 ^= X1 ^ X3;
            X2 ^= X3 ^ (X1 << 7);
            X0 = ROTL(X0, 5);
            X2 = ROTL(X2, 22);

            block[0] = (byte)(X0 >> 24 & 0xFF);
            block[1] = (byte)(X0 >> 16 & 0xFF);
            block[2] = (byte)(X0 >> 8 & 0xFF);
            block[3] = (byte)(X0 & 0xFF);

            block[4] = (byte)(X1 >> 24 & 0xFF);
            block[5] = (byte)(X1 >> 16 & 0xFF);
            block[6] = (byte)(X1 >> 8 & 0xFF);
            block[7] = (byte)(X1 & 0xFF);

            block[8] = (byte)(X2 >> 24 & 0xFF);
            block[9] = (byte)(X2 >> 16 & 0xFF);
            block[10] = (byte)(X2 >> 8 & 0xFF);
            block[11] = (byte)(X2 & 0xFF);

            block[12] = (byte)(X3 >> 24 & 0xFF);
            block[13] = (byte)(X3 >> 16 & 0xFF);
            block[14] = (byte)(X3 >> 8 & 0xFF);
            block[15] = (byte)(X3 & 0xFF);
        }

        public static byte[] CutTail(byte[] data)
        {
            int i;
            for (i = data.Length - 1; i >= 0; i--)
            {
                if (data.Length - i == (byte)data[i])
                {
                    bool is_padding = true;
                    for (int j = i; j < data.Length - 1; j++)
                    {
                        if (data[j] != data[i])
                            is_padding = false;
                    }
                    if (!is_padding) i = data.Length;
                    break;
                }
            }
            if (i > 0)
            {
                byte[] outdata = new byte[i];
                for (int j = 0; j < i; j++)
                    outdata[j] = data[j];
                return outdata;
            }
            else return data;
            
        }

        public static void Substitution(int SboxType, byte[] block) // возможно это сделано неверно
        {
            for (int i = 0; i < 16; i++)
            {
                // разделить байт на 2 части  по 4 бита
                byte a = (byte)(block[i] >> 4);             // левая
                byte b = (byte)(block[i] & 0x0F);         // правая

                // применить s-box к каждой части  
                byte anew = sboxLogic[SboxType, a];
                byte bnew = sboxLogic[SboxType, b];

                // соединить две части вместе и сохранить их   
                block[i] = (byte)((anew << 4) | bnew);
            }
        }
        private static void InverseSubstitution(int SboxType, byte[] block)
        {
            for (int i = 0; i < 16; i++)
            {
                // разделить байт на 2 части  по 4 бита
                byte a = (byte)(block[i] >> 4);             // левая
                byte b = (byte)(block[i] & 0x0F);         // правая

                // применить s-box к каждой части  
                byte anew = sboxLogicInverse[SboxType, a];
                byte bnew = sboxLogicInverse[SboxType, b];

                // соединить две части вместе и сохранить их   
                block[i] = (byte)((anew << 4) | bnew);
            }
        }

        public static void InitialPermutation(byte[] block)
        {
            BitArray bits = new BitArray(block);
            BitArray outBits = new BitArray(128);
            for (int i = 0; i < 128; i++)
            {
                outBits[i] = bits[IP[i]];
            }
            outBits.CopyTo(block, 0);
        }
        public static void FinalPermutation(byte[] block)
        {
            BitArray bits = new BitArray(block);
            BitArray outBits = new BitArray(128);
            for (int i = 0; i < 128; i++)
            {
                outBits[i] = bits[FP[i]];
            }
            outBits.CopyTo(block, 0);
        }
    }
}