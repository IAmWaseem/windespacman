using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    /// <summary>
    /// Random algorithm
    /// </summary>
    class Random : IAlgorithm
    {
        /// <summary>
        /// Does a random move
        /// </summary>
        /// <param name="currentBoard">Board to calculate random move</param>
        /// <returns>Random move</returns>
        public Board NextMove(Board currentBoard)
        {
            // Generate moves
            List<Board> nextMoves = currentBoard.GenerateMoves(Game.Instance.GetTurn());

            // create random and get random number
            System.Random random = new System.Random();
            int move = random.Next(0, nextMoves.Count);

            // return move
            return nextMoves[move];
        }
    }
}