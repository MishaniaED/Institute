using Serpent;
using System.Collections;
using System.Numerics;

namespace Serpent
{
    public enum EncryptionMode
    {
        ECB,
        CBC,
        CFB,
        OFB,
        CTR,
        RD,
        RDH
    };

    public class SErpent
    {
        private static byte[][] _keys = new byte[33][];
        private byte[] _key = new byte[16];
        private readonly EncryptionMode _mode;
        private readonly byte[]? _initializationVector;
        private readonly int _blockSize = 16;

        public delegate void PrograssInBarCBW(long i, int len, int step);
        public static event PrograssInBarCBW onCount;

        public SErpent(byte[] key, EncryptionMode mode, byte[]? initializationVector = null)
        {
            _key = key;
            for (int i = 0; i < 33; i++)
                _keys[i] = new byte[16];
            GenerateKeys(key);
            _mode = mode;
            _initializationVector = initializationVector;
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
            List<byte[]> new_text = new List<byte[]>();
            byte[][] blocks = Utilities.GetByts(ref text);

            switch (_mode)
            {
                case EncryptionMode.ECB:
                    {
                        /*for (int i = 0; i < blocks.Length / 16; i++)
                        {
                            new_text.Add(new byte[(_blockSize)]);
                        }
                        Parallel.For(0, blocks.Count, i => new_text[i] = Utilities.Transform();*/
                        int counter = 0;
                        foreach (byte[] block in blocks)
                        {
                            
                            Utilities.InitialPermutation(block);

                            for (int i = 0; i < 31; i++)
                            {
                                Utilities.Round(i % 8, block, _keys[i]);
                            }
                            Utilities.LastRound(block, _keys);
                            Utilities.FinalPermutation(block);
                            new_text.Add(block);
                            onCount(counter += 1, blocks.Count(), 1);
                        }
                        onCount(blocks.Count(), blocks.Count(), 1);
                        break;
                    }
                case EncryptionMode.CBC:
                    {
                        int counter = 0;
                        var prevBlock = _initializationVector;
                        foreach (byte[] block in blocks)
                        {
                            var currBlock = block;

                            Utilities.XOR(currBlock, prevBlock);
                            Utilities.InitialPermutation(currBlock);
                            for (int i = 0; i < 31; i++)
                            {
                                Utilities.Round(i % 8, currBlock, _keys[i]);
                            }
                            Utilities.LastRound(currBlock, _keys);
                            Utilities.FinalPermutation(currBlock);

                            new_text.Add(currBlock);
                            Array.Copy(currBlock, prevBlock, _blockSize);
                            onCount(counter+=1, blocks.Count(), 1);
                        }
                        onCount(blocks.Count(), blocks.Count(), 1);
                        break;
                    }
                case EncryptionMode.CFB:
                    {
                        int counter = 0;
                        var prevBlock = new byte[_blockSize];
                        var nextBlock = new byte[_blockSize];
                        Array.Copy(_initializationVector, prevBlock, prevBlock.Length);
                        foreach (byte[] block in blocks)
                        {
                            Array.Copy(block, nextBlock, _blockSize);

                            Utilities.InitialPermutation(prevBlock);
                            for (int i = 0; i < 31; i++)
                            {
                                Utilities.Round(i % 8, prevBlock, _keys[i]);
                            }
                            Utilities.LastRound(prevBlock, _keys);
                            Utilities.FinalPermutation(prevBlock);

                            Utilities.XOR(prevBlock, nextBlock);
                            new_text.Add(prevBlock);
                            Array.Copy(nextBlock, prevBlock, _blockSize);
                            onCount(++counter, blocks.Count(), 1);
                        }
                        onCount(blocks.Count(), blocks.Count(), 1);
                        break;
                    } 
                case EncryptionMode.OFB:
                    {
                        int counter = 0;
                        var prevBlock = new byte[_blockSize];
                        var nextBlock = new byte[_blockSize];
                        Array.Copy(_initializationVector, prevBlock, prevBlock.Length);
                        foreach (byte[] block in blocks)
                        {
                            Array.Copy(block, nextBlock, _blockSize);

                            Utilities.InitialPermutation(prevBlock);
                            for (int i = 0; i < 31; i++)
                            {
                                Utilities.Round(i % 8, prevBlock, _keys[i]);
                                onCount(i, 31, 1);
                            }
                            Utilities.LastRound(prevBlock, _keys);
                            Utilities.FinalPermutation(prevBlock);

                            var encryptedBlock = prevBlock;

                            Utilities.XOR(prevBlock, nextBlock);

                            new_text.Add(prevBlock);
                            Array.Copy(encryptedBlock, prevBlock, _blockSize);
                            onCount(++counter, blocks.Count(), 1);
                        }
                        onCount(blocks.Count(), blocks.Count(), 1);
                        break;
                    }
                case EncryptionMode.CTR:
                    {
                        int opcounter = 0;
                        var IV = new byte[_blockSize];
                        _initializationVector.CopyTo(IV, 0);
                        var counter = new BigInteger(IV);
                        var currBlock = new byte[_blockSize];
                        foreach (byte[] block in blocks)
                        {
                            Array.Copy(block, currBlock, _blockSize);

                            Utilities.InitialPermutation(IV);
                            for (int i = 0; i < 31; i++)
                            {
                                Utilities.Round(i % 8, IV, _keys[i]);
                            }
                            Utilities.LastRound(IV, _keys);
                            Utilities.FinalPermutation(IV);

                            Utilities.XOR(IV, currBlock);
                            new_text.Add(IV);
                            IV = (counter += 1).ToByteArray();
                            onCount(++opcounter, blocks.Count(), 1);
                        }
                        onCount(blocks.Count(), blocks.Count(), 1);
                        break;
                    }
                case EncryptionMode.RD:
                    {
                        int counter = 0;
                        byte[] curBlock = new byte[_blockSize];
                        byte[] copyIV = _initializationVector;                        
                        var delta = new BigInteger(_initializationVector);
                        var IV = new BigInteger(copyIV);

                        Utilities.InitialPermutation(copyIV);
                        for (int i = 0; i < 31; i++)
                            Utilities.Round(i % 8, copyIV, _keys[i]);
                        Utilities.LastRound(copyIV, _keys);
                        Utilities.FinalPermutation(copyIV);
                        new_text.Add(copyIV);

                        foreach (var block in blocks)
                        {
                            Array.Copy(block, curBlock, _blockSize);
                            Utilities.XOR(copyIV, curBlock);

                            Utilities.InitialPermutation(copyIV);
                            for (int i = 0; i < 31; i++)
                                Utilities.Round(i % 8, copyIV, _keys[i]);   
                            Utilities.LastRound(copyIV, _keys);
                            Utilities.FinalPermutation(copyIV);

                            new_text.Add(copyIV);
                            IV += delta;
                            copyIV = IV.ToByteArray();
                            onCount(++counter, blocks.Count(), 1);
                        }
                        onCount(blocks.Count(), blocks.Count(), 1);
                        break;
                    }
                case EncryptionMode.RDH:
                    {
                        int counter = 0;
                        var curBlock = new byte[_blockSize];
                        var copyIV = _initializationVector; 
                        var IV = new BigInteger(copyIV);
                        var delta = new BigInteger(_initializationVector);


                        Utilities.InitialPermutation(copyIV);
                        for (int i = 0; i < 31; i++)
                            Utilities.Round(i % 8, copyIV, _keys[i]);
                        Utilities.LastRound(copyIV, _keys);
                        Utilities.FinalPermutation(copyIV);
                        new_text.Add(copyIV);

                        var hash = BitConverter.GetBytes(blocks.GetHashCode());
                        Utilities.CheckLenght(ref hash);
                        var tmp = copyIV;
                        Utilities.XOR(tmp, hash);
                        new_text.Add(tmp);

                        foreach (var block in blocks)
                        {
                            IV += delta;
                            copyIV = IV.ToByteArray();

                            Array.Copy(block, curBlock, _blockSize);
                            Utilities.XOR(curBlock, copyIV);

                            Utilities.InitialPermutation(curBlock);
                            for (int i = 0; i < 31; i++)
                                Utilities.Round(i % 8, curBlock, _keys[i]);
                            Utilities.LastRound(curBlock, _keys);
                            Utilities.FinalPermutation(curBlock);

                            new_text.Add(tmp);
                            onCount(++counter, blocks.Count(), 1);
                        }
                        onCount(blocks.Count(), blocks.Count(), 1);
                        break;
                    }
                default:
                    throw new ArgumentOutOfRangeException(nameof(_mode), "Incorrect mode");
            }
            return new_text.SelectMany(s => s).ToArray();
        }

        public byte[] Decrypt(byte[] text)
        {
            List<byte[]> new_text = new List<byte[]>();
            byte[][] blocks = Utilities.GetByts(ref text);

            switch (_mode)
            {
                case EncryptionMode.ECB:
                    {
                        foreach (byte[] block in blocks)
                        {
                            Utilities.InitialPermutation(block);
                            Utilities.InverseLastRound(block, _keys);
                            for (int i = 30; i >= 0; i--)
                                Utilities.InverseRound(i % 8, block, _keys[i]);
                            Utilities.FinalPermutation(block);
                            new_text.Add(block);
                        }
                        break;
                    }
                case EncryptionMode.CBC:
                    {
                        var prevBlock = _initializationVector;
                        foreach (byte[] block in blocks)
                        {
                            var currBlock = block;
                            
                            Utilities.InitialPermutation(currBlock);
                            Utilities.InverseLastRound(currBlock, _keys);
                            for (int i = 30; i >= 0; i--)
                            {
                                Utilities.InverseRound(i % 8, currBlock, _keys[i]);
                            }
                            Utilities.FinalPermutation(currBlock);

                            Utilities.XOR(prevBlock, currBlock);
                            byte[] tmp = new byte[prevBlock.Length];
                            Array.Copy(prevBlock, 0, tmp, 0, prevBlock.Length);
                            new_text.Add(tmp);
                            Array.Copy(currBlock, prevBlock, _blockSize);
                        }
                        break;
                    }
                case EncryptionMode.CFB:
                    {
                        var prevBlock = new byte[_blockSize];
                        var nextBlock = new byte[_blockSize];
                        Array.Copy(_initializationVector, prevBlock, prevBlock.Length);
                        foreach (byte[] block in blocks)
                        {
                            Array.Copy(block, nextBlock, _blockSize);

                            Utilities.InitialPermutation(prevBlock);
                            Utilities.InverseLastRound(prevBlock, _keys);
                            for (int i = 30; i >= 0; i--)
                                Utilities.InverseRound(i % 8, prevBlock, _keys[i]);
                            Utilities.FinalPermutation(prevBlock);

                            Utilities.XOR(prevBlock, nextBlock);
                            new_text.Add(prevBlock);
                            Array.Copy(nextBlock, prevBlock, _blockSize);
                        }
                        break;
                    }
                case EncryptionMode.OFB:
                    {
                        var prevBlock = new byte[_blockSize];
                        var currBlock = new byte[_blockSize];
                        Array.Copy(_initializationVector, prevBlock, prevBlock.Length);
                        foreach (byte[] block in blocks)
                        {
                            Array.Copy(block, currBlock, _blockSize);

                            Utilities.InitialPermutation(prevBlock);
                            Utilities.InverseLastRound(prevBlock, _keys);
                            for (int i = 30; i >= 0; i--)
                                Utilities.InverseRound(i % 8, prevBlock, _keys[i]);
                            Utilities.FinalPermutation(prevBlock);

                            var encryptedBlock = prevBlock;
                            Utilities.XOR(prevBlock, currBlock);

                            new_text.Add(prevBlock);
                            Array.Copy(encryptedBlock, prevBlock, _blockSize);
                        }
                        break;
                    }
                case EncryptionMode.CTR:
                    {
                        var IV = new byte[_blockSize];
                        _initializationVector.CopyTo(IV, 0);
                        var counter = new BigInteger(IV);
                        var currBlock = new byte[_blockSize];
                        foreach (byte[] block in blocks)
                        {
                            Array.Copy(block, currBlock, _blockSize);

                            Utilities.InitialPermutation(IV);
                            Utilities.InverseLastRound(IV, _keys);
                            for (int i = 30; i >= 0; i--)
                                Utilities.InverseRound(i % 8, IV, _keys[i]);
                            Utilities.FinalPermutation(IV);

                            Utilities.XOR(IV, currBlock);
                            new_text.Add(IV);
                            IV = (counter += 1).ToByteArray();
                        }
                        break;
                    }
                case EncryptionMode.RD:
                    {
                        byte[] curBlock = blocks[0];
                        byte[] copyIV = new byte[16];
                        _initializationVector.CopyTo(copyIV, 0);
                        var delta = new BigInteger(_initializationVector);
                        var IV = new BigInteger(copyIV);

                        Utilities.InitialPermutation(curBlock);
                        Utilities.InverseLastRound(curBlock, _keys);
                        for (int i = 30; i >= 0; i--)
                            Utilities.InverseRound(i % 8, curBlock, _keys[i]);
                        Utilities.FinalPermutation(curBlock);
                        new_text.Add(curBlock);

                        for (var i = 1; i < blocks.Length / _blockSize; ++i)
                        {
                            Array.Copy(blocks[i], curBlock, _blockSize);

                            Utilities.InitialPermutation(curBlock);
                            Utilities.InverseLastRound(curBlock, _keys);
                            for (int j = 30; j >= 0; j--)
                                Utilities.InverseRound(j % 8, curBlock, _keys[j]);
                            Utilities.FinalPermutation(curBlock); 

                            Utilities.XOR(curBlock, curBlock);
                            new_text.Add(curBlock);
                            IV += delta;
                            copyIV = IV.ToByteArray();
                        }
                        break;
                    }
                case EncryptionMode.RDH:
                    {
                        var curBlock = blocks[0];
                        var copyIV = new byte[16];
                        var delta = new BigInteger(_initializationVector);

                        Utilities.InitialPermutation(curBlock);
                        Utilities.InverseLastRound(curBlock, _keys);
                        for (int i = 30; i >= 0; i--)
                            Utilities.InverseRound(i % 8, curBlock, _keys[i]);
                        Utilities.FinalPermutation(curBlock);

                        copyIV = curBlock;
                        var IV = new BigInteger(copyIV);

                        Array.Copy(blocks[1], curBlock, 0);

                        var hash = BitConverter.GetBytes(blocks.GetHashCode());
                        Utilities.CheckLenght(ref hash);
                        var tmp = copyIV;
                        Utilities.XOR(tmp, hash);
                        new_text.Add(tmp);

                        foreach (var block in blocks)
                        {
                            IV += delta;
                            copyIV = IV.ToByteArray();

                            Array.Copy(block, curBlock, _blockSize);
                            
                            Utilities.InitialPermutation(curBlock);
                            Utilities.InverseLastRound(curBlock, _keys);
                            for (int i = 30; i >= 0; i--)
                                Utilities.InverseRound(i % 8, curBlock, _keys[i]);
                            Utilities.FinalPermutation(curBlock);

                            Utilities.XOR(curBlock, copyIV);
                            new_text.Add(curBlock);
                        }
                        break;
                    } 
            }
            return Utilities.CutTail(new_text.SelectMany(s => s).ToArray());
        }

        private static void GenerateKeys(byte[] keyf)
        {
            Utilities.KeyExpansion(ref keyf); // дополняем ключ до 256 бит

            uint[] words = new uint[140];
            uint fi = 0x9e3779b9;
            for (int i = 0; i < 8; i++)
            {
                words[i] = 0;
                words[i] |= (uint)(keyf[4 * i] << (8 * 3));
                words[i] |= (uint)(keyf[4 * i] << (8 * 2));
                words[i] |= (uint)(keyf[4 * i] << (8));
                words[i] |= keyf[4 * i];
            }
            for (int i = 8; i < 140; i++) // расчитываем промежуточные ключи
                words[i] = Utilities.ROTL((uint)(words[i - 8] ^ words[i - 5] ^ words[i - 3] ^ words[i - 1] ^ fi ^ i), 11);

            int iwords = 0;
            /*byte[][] keys = new byte[33][];*/
            for (int i = 0; i < 33; i++)
            {
                // разделить слова на байты и сохранить их в подключ  
                for (int j = 0; j < 4; j++)
                {
                    _keys[i][4 * j] = (byte)((words[iwords] & 0xFF000000) >> 8 * 3);
                    _keys[i][4 * j + 1] = (byte)((words[iwords] & 0x00FF0000) >> 8 * 2);
                    _keys[i][4 * j + 2] = (byte)((words[iwords] & 0x0000FF00) >> 8 * 1);
                    _keys[i][4 * j + 3] = (byte)(words[iwords] & 0x000000FF);
                    iwords += 1;
                }
            }

            int s_counter = 3;
            for (int i = 0; i < 33; i++)
            {
                if (s_counter < 0)
                    s_counter = 7;

                Utilities.Substitution(s_counter, _keys[i]);
                Utilities.InitialPermutation(_keys[i]);
                s_counter -= 1;
            }
        }
    }
}