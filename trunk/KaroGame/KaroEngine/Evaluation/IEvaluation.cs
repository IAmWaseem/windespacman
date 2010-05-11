using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    /// <summary>
    /// Evaluation interface
    /// </summary>
    public interface IEvaluation
    {
        /// <summary>
        /// Evaluates the board
        /// </summary>
        /// <param name="board">Provided board</param>
        /// <param name="isRed">Is player red's turn</param>
        /// <returns></returns>
        int Evaluate(Board board, bool isRed);
    }

    public enum EvaluationType
    {
        FreeSpace = 0,
        BetterOne = 1
    }
}
