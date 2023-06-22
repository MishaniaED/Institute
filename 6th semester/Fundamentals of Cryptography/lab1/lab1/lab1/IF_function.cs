using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    internal interface IF_function // 2
    {
        UInt32 Transform(UInt32 block, byte[] roundKey);
    }
}
