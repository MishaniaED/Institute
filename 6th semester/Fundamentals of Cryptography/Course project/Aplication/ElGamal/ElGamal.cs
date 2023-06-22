using System.Linq;
using System.Numerics;
using System.Security.Cryptography;
using System.Text;

namespace elGamal
{
    public class ElGamal
    {
        public RandomNumberGenerator randomNumberGenerator = RandomNumberGenerator.Create(); 
        public BigInteger p = new BigInteger(), g = new BigInteger(), y = new BigInteger();
        private BigInteger x = new BigInteger();
        private const int keyLenghtInByte = 8;

        public ElGamal()
        {
            GenerateKey(keyLenghtInByte);
        }

        async public Task<byte[]> EncryptAsync(byte[] text)
        {
            byte[] new_text;
            return await Task.Run(() => new_text = Encrypt(text));
        }

        async public Task<byte[]> DecryptAsync(byte[] text)
        {
            byte[] new_text;
            return await Task.Run(() => new_text = Decrypt(text));
        }

        public byte[] Encrypt(byte[] text) 
        {
            int size = p.ToByteArray().Length - 1;
            List<byte[]> new_text = new List<byte[]>();
            byte[] block = new byte[size];

            CheckLengt(ref text, size);

            BigInteger b = new BigInteger(), a = new BigInteger() , k = new BigInteger();
            for (int i = 0; i < text.LongLength; i+=size)
            {
                do k = (1 + Rand(p.ToByteArray().Length)) % p; // взаимно простое с p-1
                while (BigInteger.GreatestCommonDivisor(k, p - 1) != 1);

                a = BigInteger.ModPow(g, k, p);
                for(int j = 0; j < size; j++)
                {
                    block[j] = text[i+j];
                }
                b = MultMOD(BigInteger.ModPow(y, k, p), new BigInteger(block), p);
                new_text.Add(Merge(a,b, size));
            }
            return new_text.SelectMany(s => s).ToArray();
        }        

        public byte[] Decrypt(byte[] text) 
        {
            // M = b*a^(p-1-x) mod p
            List<byte[]> new_text = new List<byte[]>();
            int size = p.ToByteArray().Length - 1;

            CheckLengt(ref text, size);

            BigInteger b, a, M = new BigInteger();
            for(int i = 0; i < text.LongLength - 4 * size + 1; i += 4*size) 
            { 
                a = new BigInteger((text[i..(i+2*size)]));
                b = new BigInteger((text[(i + 2*size)..(i + 4*size)]));
                M = MultMOD(b, BigInteger.ModPow(a, p - 1 - x, p), p);
                new_text.Add(M.ToByteArray());
            }

            return CutTail(new_text.SelectMany(s => s).ToArray());
        }
        
        private void GenerateKey(int len)
        {            
            do p = Rand(len);  // генерировать случайное простое число от размера len
            while (!MillerRabinTest(p, 1000));

            g = (1 + Rand(len)) % p; //  генерировать случайное число размера 1<g<p

            x = (1 + Rand(len)) % (p-1); //  генерировать случайное число размера 1<x<p-1

            y = BigInteger.ModPow(g, x, p); // Открытым ключом является (y,g,p), закрытым ключом — число x.
        }

        private bool MillerRabinTest(BigInteger number, int k)
        {
            if (number == 2 || number == 3)
                return true;
            if (number < 2 || number % 2 == 0)
                return false;

            // представим n − 1 в виде (2^s)·t, где t нечётно, это можно сделать последовательным делением n - 1 на 2
            BigInteger t = number - 1;
            int s = 0;
            while (t % 2 == 0)
            {
                t /= 2;
                s += 1;
            }

            byte[] _a = new byte[number.ToByteArray().LongLength];/*GetByteCount()*/

            for (int i = 0; i < k; i++)
            {
                // выберем случайное целое число a в отрезке [2, n − 2]
                BigInteger a = new BigInteger();
                do
                {
                    randomNumberGenerator.GetBytes(_a);
                    a = new BigInteger(_a);
                }
                while (a < 2 || a >= number - 2);

                BigInteger x = BigInteger.ModPow(a, t, number);

                // если x == 1 или x == n − 1, то перейти на следующую итерацию цикла
                if (x == 1 || x == number - 1)
                    continue;

                // повторить s − 1 раз
                for (int r = 1; r < s; r++)
                {
                    // x ← x^2 mod n
                    x = BigInteger.ModPow(x, 2, number);

                    // если x == 1, то вернуть "составное"
                    if (x == 1)
                        return false;

                    // если x == n − 1, то перейти на следующую итерацию внешнего цикла
                    if (x == number - 1)
                        break;
                }
                if (x != number - 1)
                    return false;
            }
            return true;
        }

        private bool FermaTest(BigInteger number, int k)
        {
            if (number == 2 || number == 3)
                return true;
            if (number < 2 || number % 2 == 0)
                return false;

            byte[] _a = new byte[number.ToByteArray().LongLength];

            for (int i = 0; i < k; i++)
            {
                BigInteger a = new BigInteger();
                do
                {
                    randomNumberGenerator.GetBytes(_a);
                    a = new BigInteger(_a);
                }
                while (a < 2 || a >= number - 2);

                if(BigInteger.GreatestCommonDivisor(a, p - 1) != 1)
                    return false;

                if (BigInteger.ModPow(a, p - 1, p) != 1)
                    return false;
            }
            return true;
        }

        private bool SoloveyShtrassenTest(BigInteger number, int k)
        {
            if (number == 2 || number == 3)
                return true;
            if (number < 2 || number % 2 == 0)
                return false;

            byte[] _a = new byte[number.ToByteArray().LongLength];

            for (int i = 0; i < k; i++)
            {
                BigInteger a = new BigInteger();
                do
                {
                    randomNumberGenerator.GetBytes(_a);
                    a = new BigInteger(_a);
                }
                while (a < 2 || a >= number - 2);

                if (BigInteger.GreatestCommonDivisor(a, p - 1) != 1)
                    return false;

                BigInteger jacobian = BigInteger.ModPow(a, -p, p);
                if (jacobian == 0 || BigInteger.ModPow(a, (p-1)/2, p) != jacobian)
                    return false;
            }
            return true;
        }

        private BigInteger Rand(int len)
        {
            byte[] count = new byte[len];
            randomNumberGenerator.GetBytes(count);
            BigInteger result = new BigInteger(count);
            return result > 0 ? result : -result;
        }

        private BigInteger MultMOD(BigInteger a, BigInteger b, BigInteger mod)
        {
            BigInteger res = 0; 
            a %= mod;
            while (b > 0)
            {
                if ((b & 1) > 0)
                    res = (res + a) % mod;

                a = (2 * a) % mod;
                b >>= 1;
            }
            return res;
        }

        private byte[] Merge(BigInteger a, BigInteger b, int size)
        {
            List<byte> list1 = a.ToByteArray().ToList(), list2 = b.ToByteArray().ToList();
            int padding = size - list1.Count % size;
            if(padding > 0)
            {
                while(padding > 0)
                {
                    list1.Add((byte)0);
                    padding -= 1;
                }
            }
            padding = size - list2.Count % size;
            if(padding > 0)
            {
                while (padding > 0)
                {
                    list2.Add((byte)0);
                    padding -= 1;
                }
            }
            var tmp = list1.Concat(list2).ToArray();
            return tmp;
        }

        private void CheckLengt(ref byte[] bytes, int size)
        {
            int padding = bytes.Length % size;
            if (padding > 0)
            {
                padding = size - padding;
                Array.Resize(ref bytes, bytes.Length + padding);
                for (int i = bytes.Length - 1; i >= bytes.Length - padding; --i)
                {
                    bytes[i] = (byte)padding;
                }
            }
        }

        public byte[] CutTail(byte[] data)
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
            if (i > 0) // вылетала ошибка
            {
                byte[] outdata = new byte[i];
                for (int j = 0; j < i; j++)
                    outdata[j] = data[j];
                return outdata;
            }
            else return data;

        }
    }
}