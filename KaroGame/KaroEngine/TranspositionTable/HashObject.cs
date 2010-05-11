using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    class HashObject
    {
        public int depth, hashKey, value;

        public HashObject(int depth, int hashKey, int value)
        {
            this.depth = depth;
            this.hashKey = hashKey;
            this.value = value;
        }
    }
}
