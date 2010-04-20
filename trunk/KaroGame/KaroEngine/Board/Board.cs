using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    public class Board : IComparable, ICloneable
    {
        private BoardPosition[,] boardPositions;

        /// <summary>
        /// create a new empty board, with in the middle the empty tiles
        /// </summary>
        public Board()
        {
            boardPositions = new BoardPosition[21,20];
            boardPositions[8,8] = BoardPosition.Tile;
            boardPositions[8,9] = BoardPosition.Tile;
            boardPositions[8,10] = BoardPosition.Tile;
            boardPositions[8,11] = BoardPosition.Tile;

            boardPositions[9,8] = BoardPosition.Tile;
            boardPositions[9,9] = BoardPosition.Tile;
            boardPositions[9,10] = BoardPosition.Tile;
            boardPositions[9,11] = BoardPosition.Tile;

            boardPositions[10,8] = BoardPosition.Tile;
            boardPositions[10,9] = BoardPosition.Tile;
            boardPositions[10,10] = BoardPosition.Tile;
            boardPositions[10,11] = BoardPosition.Tile;

            boardPositions[11,8] = BoardPosition.Tile;
            boardPositions[11,9] = BoardPosition.Tile;
            boardPositions[11,10] = BoardPosition.Tile;
            boardPositions[11,11] = BoardPosition.Tile;

            boardPositions[12,8] = BoardPosition.Tile;
            boardPositions[12,9] = BoardPosition.Tile;
            boardPositions[12,10] = BoardPosition.Tile;
            boardPositions[12,11] = BoardPosition.Tile;
            Logger.AddLine("Board created!");
        }

        public BoardPosition[,] GetBoardState()
        {
            return boardPositions;
        }

        public List<Board> GenerateMoves()
        {
            // IMPLEMENTATION NEEDED
            Logger.AddLine("Generated moves");
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
