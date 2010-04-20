using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    interface IAlgorithm
    {
        Board NextMove(Board currentBoard);
    }
}
