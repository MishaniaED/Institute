using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace lab1
{
    internal class DES
    {
        public enum Mode {ECB} ;

        private byte[] key;
        private Mode mode;
        //private byte[] InVector;
        private ISym_Encrypt algorytm;

        public DES(Mode mode, byte[] key, params object[] other)
        {
            this.key = key;
            this.mode = mode;
            algorytm = new FeistelCipher(new RoundGeneration(), new F_function(), this.key);
        }

        public byte[] Decrypt(byte[] text)
        {
            List<byte[]> new_text = new List<byte[]>();
            byte[][] blocks = GetByts(ref text);
            foreach (byte[] block in blocks)
            {
                new_text.Add(algorytm.Decrypt(block));
            }
            return new_text.SelectMany(s=>s).ToArray(); // склеивает массиывы в один большой и возвращает его
        }

        public byte[] Encrypt(byte[] text)
        {
            List<byte[]> new_text = new List<byte[]>();
            byte[][] blocks = GetByts(ref text);
            foreach (byte[] block in blocks)
            {
                new_text.Add(algorytm.Encrypt(block));
            }
            return new_text.SelectMany(s => s).ToArray();
        }

        private byte[][] GetByts(ref byte[] text)
        {
            CheckLengt(ref text);
            byte[][] blocks = new byte[text.Length / 8][]; // размер блока
            for(int i=0;i < text.Length / 8; ++i)
            {
                blocks[i] = new byte[8];
                for(byte j=0;j< 8; ++j)
                {
                    blocks[i][j] = text[i*8 + j];
                }
            }
            return blocks;
        }

        public void CheckLengt(ref byte[] bytes)
        {
            int padding = bytes.Length % 8;
            if (padding > 0)
            {
                padding = 8 - padding;
                Array.Resize(ref bytes, bytes.Length + padding);
                for (int i = bytes.Length - 1; i >= bytes.Length - padding; --i)
                {
                    bytes[i] = (byte)padding;
                }
            }
        }

    }
}
