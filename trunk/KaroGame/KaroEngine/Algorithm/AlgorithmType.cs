using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    /// <summary>
    /// Type of algorithm used
    /// </summary>
    public enum AlgorithmType
    {
        /// <summary>
        /// Algorithm chooses random move from the avalible moves.
        /// </summary>
        Random = 0,
        /// <summary>
        /// Calculate best move with minimax
        /// </summary>
        MiniMax = 1,
        /// <summary>
        /// Calculate best move with minimax with alpha beta pruning, better result
        /// </summary>
        AlphaBeta = 2
    }
}
