using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    internal class Utilities 
    {
        private static readonly int[,,] Sbox = // таблица преобразований
     {
             { // 0
        {14, 4 , 13, 1 , 2 , 15, 11, 8 , 3 , 10, 6 , 12, 5 , 9 , 0 , 7 },
        {0 , 15, 7 , 4 , 14, 2 , 13, 1 , 10, 6 , 12, 11, 9 , 5 , 3 , 8 },
        {4 , 1 , 14, 8 , 13, 6 , 2 , 11, 15, 12, 9 , 7 , 3 , 10, 5 , 0 },
        {15, 12, 8 , 2 , 4 , 9 , 1 , 7 , 5 , 11, 3 , 14, 10, 0 , 6 , 13},
    },
    { // 1
        {15, 1 , 8 , 14, 6 , 11, 3 , 4 , 9 , 7 , 2 , 13, 12, 0 , 5 , 10},
        {3 , 13, 4 , 7 , 15, 2 , 8 , 14, 12, 0 , 1 , 10, 6 , 9 , 11, 5 },
        {0 , 14, 7 , 11, 10, 4 , 13, 1 , 5 , 8 , 12, 6 , 9 , 3 , 2 , 15},
        {13, 8 , 10, 1 , 3 , 15, 4 , 2 , 11, 6 , 7 , 12, 0 , 5 , 14, 9 },
    },
    { // 2
        {10, 0 , 9 , 14, 6 , 3 , 15, 5 , 1 , 13, 12, 7 , 11, 4 , 2 , 8 },
        {13, 7 , 0 , 9 , 3 , 4 , 6 , 10, 2 , 8 , 5 , 14, 12, 11, 15, 1 },
        {13, 6 , 4 , 9 , 8 , 15, 3 , 0 , 11, 1 , 2 , 12, 5 , 10, 14, 7 },
        {1 , 10, 13, 0 , 6 , 9 , 8 , 7 , 4 , 15, 14, 3 , 11, 5 , 2 , 12},
    },
    { // 3
        {7 , 13, 14, 3 , 0 , 6 , 9 , 10, 1 , 2 , 8 , 5 , 11, 12, 4 , 15},
        {13, 8 , 11, 5 , 6 , 15, 0 , 3 , 4 , 7 , 2 , 12, 1 , 10, 14, 9 },
        {10, 6 , 9 , 0 , 12, 11, 7 , 13, 15, 1 , 3 , 14, 5 , 2 , 8 , 4 },
        {3 , 15, 0 , 6 , 10, 1 , 13, 8 , 9 , 4 , 5 , 11, 12, 7 , 2 , 14},
    },
    { // 4
        {2 , 12, 4 , 1 , 7 , 10, 11, 6 , 8 , 5 , 3 , 15, 13, 0 , 14, 9 },
        {14, 11, 2 , 12, 4 , 7 , 13, 1 , 5 , 0 , 15, 10, 3 , 9 , 8 , 6 },
        {4 , 2 , 1 , 11, 10, 13, 7 , 8 , 15, 9 , 12, 5 , 6 , 3 , 0 , 14},
        {11, 8 , 12, 7 , 1 , 14, 2 , 13, 6 , 15, 0 , 9 , 10, 4 , 5 , 3 },
    },
    { // 5
        {12, 1 , 10, 15, 9 , 2 , 6 , 8 , 0 , 13, 3 , 4 , 14, 7 , 5 , 11},
        {10, 15, 4 , 2 , 7 , 12, 9 , 5 , 6 , 1 , 13, 14, 0 , 11, 3 , 8 },
        {9 , 14, 15, 5 , 2 , 8 , 12, 3 , 7 , 0 , 4 , 10, 1 , 13, 11, 6 },
        {4 , 3 , 2 , 12, 9 , 5 , 15, 10, 11, 14, 1 , 7 , 6 , 0 , 8 , 13},
    },
    { // 6
        {4 , 11, 2 , 14, 15, 0 , 8 , 13, 3 , 12, 9 , 7 , 5 , 10, 6 , 1 },
        {13, 0 , 11, 7 , 4 , 9 , 1 , 10, 14, 3 , 5 , 12, 2 , 15, 8 , 6 },
        {1 , 4 , 11, 13, 12, 3 , 7 , 14, 10, 15, 6 , 8 , 0 , 5 , 9 , 2 },
        {6 , 11, 13, 8 , 1 , 4 , 10, 7 , 9 , 5 , 0 , 15, 14, 2 , 3 , 12},
    },
    { // 7
        {13, 2 , 8 , 4 , 6 , 15, 11, 1 , 10, 9 , 3 , 14, 5 , 0 , 12, 7 },
        {1 , 15, 13, 8 , 10, 3 , 7 , 4 , 12, 5 , 6 , 11, 0 , 14, 9 , 2 },
        {7 , 11, 4 , 1 , 9 , 12, 14, 2 , 0 , 6 , 10, 13, 15, 3 , 5 , 8 },
        {2 , 1 , 14, 7 , 4 , 10, 8 , 13, 15, 12, 9 , 0 , 3 , 5 , 6 , 11},
    },
    };

        private static readonly int[] IP = // таблица для начальной перестановки
   {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17,  9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    };

        private static readonly int[] FP = { // таблица для конечной перестановки
        40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9 , 49, 17, 57, 25,
    };

        private static readonly int[] K1P =
        {
        57, 49, 41, 33, 25, 17, 9 , 1 , 58, 50, 42, 34, 26, 18,
        10, 2 , 59, 51, 43, 35, 27, 19, 11, 3 , 60, 52, 44, 36
        };

        private static readonly int[] K2P =
       {
        63, 55, 47, 39, 31, 23, 15, 7 , 62, 54, 46, 38, 30, 22,
        14, 6 , 61, 53, 45, 37, 29, 21, 13, 5 , 28, 20, 12, 4
        };

        private static readonly int[] CP =
        {
        14, 17, 11, 24, 1 , 5 , 3 , 28, 15, 6 , 21, 10,
        23, 19, 12, 4 , 26, 8 , 16, 7 , 27, 20, 13, 2 ,
        41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
        };

        private static readonly int[] EP = { // Функция расширения E
        32, 1 , 2 , 3 , 4 , 5 , 4 , 5 , 6 , 7 , 8 , 9 ,
        8 , 9 , 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 ,
    };

        private static readonly int[] P ={ // Перестановка P
        16, 7 , 20, 21, 29, 12, 28, 17, 1 , 15, 23, 26, 5 , 18, 31, 10,
        2 , 8 , 24, 14, 32, 27, 3 , 9 , 19, 13, 30, 6 , 22, 11, 4 , 25,
    };

        private enum Mode
        {
            ECB, CBC, CFB, OFB, CTR, RD, RDH
        }

        public static UInt64 expansion_permutation(UInt32 block32b)
        {
            UInt64 block48b = 0;
            for (int i = 0; i < 48; ++i)
            {
                block48b |= (UInt64)((block32b >> (32 - EP[i])) & 0x01) << (63 - i);
            }
            return block48b;
        }

        public static UInt32 Substitutions(UInt64 block48b)
        {
            byte[] blocks4b = new byte[4], blocks6b = new byte[8];
            split_48bits_to_6bits(block48b, blocks6b);
            substitution_6bits_to_4bits(blocks6b, blocks4b);
            return join_4bits_to_32bits(blocks4b);
        }

        public static void substitution_6bits_to_4bits(byte[] blocks6b, byte[] blocks4b)
        {
            byte block2b, block4b;

            for (int i = 0, j = 0; i < 8; i += 2, ++j)
            {
                block2b = extreme_bits(blocks6b[i]);
                block4b = middle_bits(blocks6b[i]);
                blocks4b[j] = (byte)Sbox[i,block2b,block4b];

                block2b = extreme_bits(blocks6b[i + 1]);
                block4b = middle_bits(blocks6b[i + 1]);
                blocks4b[j] = (byte)((blocks4b[j] << 4) | Sbox[i + 1, block2b, block4b]);
            }
        }

        public static byte extreme_bits(byte block6b)
        {
            return (byte)(((block6b >> 6) & 0x2) | ((block6b >> 2) & 0x1));
        }

        public static byte middle_bits(byte block6b)
        {
            return (byte)((block6b >> 3) & 0xF);
        }

        public static UInt32 Permutation(UInt32 block32b)
        {
            UInt32 new_block32b = 0;
            for (byte i = 0; i < 32; ++i)
            {
                new_block32b |= ((block32b >> (32 - P[i])) & 0x01) << (31 - i);
            }
            return new_block32b;
        }

        public static UInt64 InitialPermutation(UInt64 block64b)
        {
            UInt64 new_block64b = 0;
            for (int i = 0; i < 64; ++i)
            {
                new_block64b |= ((block64b >> (64 - IP[i])) & 0x01) << (63 - i);
            }
            return new_block64b;
        }

        public static UInt64 FinalPermutation(UInt64 block64b)
        {
            UInt64 new_block64b = 0;
            for (byte i = 0; i < 64; ++i)
            {
                new_block64b |= ((block64b >> (64 - FP[i])) & 0x01) << (63 - i);
            }
            return new_block64b;
        }

        public static void key_permutation_56bits_to_28bits(UInt64 block56b, ref UInt32 block28b_1, ref UInt32 block28b_2)
        {
            for (byte i = 0; i < 28; ++i)
            {
                block28b_1 |= (UInt32)((block56b >> (64 - K1P[i])) & 0x01) << (31 - i);
                block28b_2 |= (UInt32)((block56b >> (64 - K2P[i])) & 0x01) << (31 - i);
            }
        }

        public static void key_expansion_to_48bits(UInt32 block28b_1, UInt32 block28b_2, byte[][] keys48b)
        {
            UInt64 block56b;
            byte n;

            for (byte i = 0; i < 16; ++i)
            {
                switch (i)
                {
                    case 0: case 1: case 8: case 15: n = 1; break;
                    default: n = 2; break;
                }

                block28b_1 = LSHIFT_28BIT(block28b_1, n);
                block28b_2 = LSHIFT_28BIT(block28b_2, n);
                block56b = join_28bits_to_56bits(block28b_1, block28b_2);
                key_contraction_permutation(block56b).CopyTo(keys48b[i], 0);
            }
        }

        public static byte[] key_contraction_permutation(UInt64 block56b)
        {
            UInt64 block48b = 0;
            for (byte i = 0; i < 48; ++i)
            {
                block48b |= ((block56b >> (64 - CP[i])) & 0x01) << (63 - i);
            }
            return BitConverter.GetBytes(block48b);
        }

        public static void split_48bits_to_6bits(UInt64 block48b, byte[] blocks6b)
        {
            for (byte i = 0; i < 8; ++i)
            {
                blocks6b[i] = (byte)((block48b >> (58 - (i * 6))) << 2);
            }
        }

        public static UInt64 join_28bits_to_56bits(UInt32 block28b_1, UInt32 block28b_2)
        {
            UInt64 block56b;
            block56b = (block28b_1 >> 4);
            block56b = ((block56b << 32) | block28b_2) << 4;
            return block56b;
        }

        public static UInt32 join_4bits_to_32bits(byte[] blocks4b)
        {
            UInt32 block32b = 0;
            for (byte p = 0; p < blocks4b.Length; p+=8)
            {
                block32b = (block32b << 8) | blocks4b[p];
            }
            return block32b;
        }
        public static UInt32 LSHIFT_28BIT(UInt32 x, byte L) { 
            return (UInt32)((((x) << (L)) | ((x) >> (-(L) & 27))) & (((UInt64)1 << 32) - 1));
        }
    }
}
