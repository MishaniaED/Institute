using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    internal class F_function : IF_function
    {
        public UInt32 Transform(UInt32 block, byte[] roundKey)
        {
            var permutedBlock = Utilities.expansion_permutation(block); // Расширение

            permutedBlock ^= BitConverter.ToUInt64(roundKey); // XOR

            block = Utilities.Substitutions(permutedBlock); // S

            return Utilities.Permutation(block); // P
        }
    }
}
