using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    class Random : IAlgorithm
    {
        public Board NextMove(Board currentBoard)
        {
            List<Board> nextMoves = currentBoard.GenerateMoves(Game.Instance.GetTurn());
            System.Random random = new System.Random();
            int move = random.Next(0, nextMoves.Count);
            return nextMoves[move];
        }
    }
}