using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    class Board : IComparable, ICloneable
    {
        private BoardPosition[,] boardPositions;

        public Board()
        {
            boardPositions = new BoardPosition[21,20];
        }

        public List<Board> GenerateMoves()
        {
            // IMPLEMENTATION NEEDED
            return null;
        }

        public void IsMoveValid(Board board)
        {
            // IMPLEMENTATION NEEDED
        }

        public int Evaluation()
        {
            // IMPLEMENTATION NEEDED
            return 0;
        }

        public bool IsWon()
        {
            // IMPLEMENTATION NEEDED
            return true;
        }

        public int CompareTo(object obj)
        {
            // IMPLEMENTATION NEEDED
            throw new NotImplementedException();
        }

        public object Clone()
        {
            // IMPLEMENTATION NEEDED
            throw new NotImplementedException();
        }
    }
}
