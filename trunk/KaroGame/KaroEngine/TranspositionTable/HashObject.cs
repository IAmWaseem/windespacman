using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    class HashObject
    {
        public int depth;
        public Int64 hashKey;
        public int value;
        public bool isPlayerAMax;
        public bool turnPlayerA;

        public HashObject(int depth, Int64 hashKey, int value, bool isPlayerAMax, bool turnPlayerA)
        {
            this.depth = depth;
            this.hashKey = hashKey;
            this.value = value;
            this.isPlayerAMax = isPlayerAMax;
            this.turnPlayerA = turnPlayerA;
        }
    }
}
