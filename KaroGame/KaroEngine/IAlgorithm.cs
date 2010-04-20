using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    interface IAlgorithm
    {
        public Board NextMove(Board currentBoard);
    }
}
