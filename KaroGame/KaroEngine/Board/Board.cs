using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;

namespace Karo
{
    /// <summary>
    /// 
    /// </summary>
    public class Board : IComparable, ICloneable
    {
        private BoardPosition[,] boardPositions;
        private int amountOfRedItems;
        private int amountOfWhiteItems;
        private List<Point> movablePoints;
        private bool isTileMoved = false;

        /// <summary>
        /// 
        /// </summary>
        public Board()
        {
            boardPositions = new BoardPosition[21, 20];
            boardPositions[8, 8] = BoardPosition.Tile;
            boardPositions[8, 9] = BoardPosition.Tile;
            boardPositions[8, 10] = BoardPosition.Tile;
            boardPositions[8, 11] = BoardPosition.Tile;

            boardPositions[9, 8] = BoardPosition.Tile;
            boardPositions[9, 9] = BoardPosition.Tile;
            boardPositions[9, 10] = BoardPosition.Tile;
            boardPositions[9, 11] = BoardPosition.Tile;

            boardPositions[10, 8] = BoardPosition.Tile;
            boardPositions[10, 9] = BoardPosition.Tile;
            boardPositions[10, 10] = BoardPosition.Tile;
            boardPositions[10, 11] = BoardPosition.Tile;

            boardPositions[11, 8] = BoardPosition.Tile;
            boardPositions[11, 9] = BoardPosition.Tile;
            boardPositions[11, 10] = BoardPosition.Tile;
            boardPositions[11, 11] = BoardPosition.Tile;

            boardPositions[12, 8] = BoardPosition.Tile;
            boardPositions[12, 9] = BoardPosition.Tile;
            boardPositions[12, 10] = BoardPosition.Tile;
            boardPositions[12, 11] = BoardPosition.Tile;
            Logger.AddLine("Board created!");

            amountOfRedItems = 6;
            amountOfWhiteItems = 6;
            CalculateMovableTiles();
        }
        public Board(BoardPosition[,] boardPositions)
        {
            this.boardPositions = boardPositions;
            CalculateMovableTiles();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="toChange"></param>
        /// <returns></returns>
        private List<Board> NewBoardPosition(BoardPosition toChange)
        {
            List<Board> boards = new List<Board>();

            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    if (boardPositions[x, y] == BoardPosition.Tile)
                    {
                        BoardPosition[,] newBoardPosition = (BoardPosition[,]) boardPositions.Clone();
                        newBoardPosition[x, y] = toChange;

                        Board newBoard = new Board(newBoardPosition);

                        if (toChange == BoardPosition.RedTail)
                        {
                            newBoard.amountOfRedItems = amountOfRedItems + 1;
                            newBoard.amountOfWhiteItems = amountOfWhiteItems;
                        }
                        else
                        {
                            newBoard.amountOfRedItems = amountOfRedItems;
                            newBoard.amountOfWhiteItems = amountOfWhiteItems + 1;
                        }
                        newBoard.IsTileMoved = false;
                        boards.Add(newBoard);
                    }
                }
            }

            return boards;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="turnPlayerA"></param>
        /// <returns></returns>
        public List<Board> ChangeBoardPosition(bool turnPlayerA)
        {
            List<Board> boards = new List<Board>();

            BoardPosition colorHead = BoardPosition.WhiteHead;
            BoardPosition colorTail = BoardPosition.WhiteTail;

            if(turnPlayerA)
            {
                colorHead = BoardPosition.RedHead;
                colorTail = BoardPosition.RedTail;
            }



            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    if (boardPositions[x, y] == colorHead || boardPositions[x, y] == colorTail)
                    {
                        for (int j = -1; j < 2; j++)
                        {
                            for (int i = -1; i < 2; i++)
                            {
                                if(!(i==0 && j==0))
                                {
                                    // Moving a piece to a empty tile next to him
                                    if (boardPositions[x + i, y + j] == BoardPosition.Tile)
                                    {
                                        BoardPosition[,] newBoardPosition = (BoardPosition[,])boardPositions.Clone();

                                        newBoardPosition[x, y] = BoardPosition.Tile;
                                        newBoardPosition[x + i, y + j] = boardPositions[x, y];

                                        Board newBoard = new Board(newBoardPosition);
                                        newBoard.IsTileMoved = false;
                                        boards.Add(newBoard);
                                    }
                                    // Moving a piece by jumping over a other piece next to him
                                    else if (boardPositions[x + i, y + j] != BoardPosition.Empty)
                                    {
                                        if (boardPositions[x + i + i, y + j + j] == BoardPosition.Tile)
                                        {
                                            BoardPosition[,] newBoardPosition = (BoardPosition[,])boardPositions.Clone();
                                            newBoardPosition[x, y] = BoardPosition.Tile;

                                            if (boardPositions[x, y] == colorTail)
                                                newBoardPosition[x + i + i, y + j + j] = colorHead;
                                            else
                                                newBoardPosition[x + i + i, y + j + j] = colorTail;

                                            Board newBoard = new Board(newBoardPosition);
                                            newBoard.IsTileMoved = false;
                                            boards.Add(newBoard);
                                        }
                                    }
                                    else if (!isTileMoved && (boardPositions[x + i, y + j] == BoardPosition.Empty || boardPositions[x + i + i, y + j + j] == BoardPosition.Empty))
                                    {
                                        Point moveTileTo = new Point(x + i, y + i);
                                        if(boardPositions[x + i, y + j] != BoardPosition.Empty)
                                        {
                                            moveTileTo.X += i;
                                            moveTileTo.Y += j;
                                        }
                                        foreach(Point movablePoint in movablePoints)
                                        {
                                            BoardPosition[,] newBoardPosition = (BoardPosition[,])boardPositions.Clone();
                                            newBoardPosition[movablePoint.X, movablePoint.Y] = BoardPosition.Empty;
                                            newBoardPosition[moveTileTo.X, moveTileTo.Y] = BoardPosition.Tile;
                                            Board newBoard = new Board(newBoardPosition);
                                            newBoard.IsTileMoved = true;
                                            boards.Add(newBoard);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            return boards;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="turnPlayerA"></param>
        /// <returns></returns>
        public List<Board> GenerateMoves(bool turnPlayerA)
        {
            List<Board> generatedMoves = new List<Board>();

            if (turnPlayerA && amountOfRedItems < 6)
                generatedMoves.AddRange(NewBoardPosition(BoardPosition.RedTail));

            else if (!turnPlayerA && amountOfWhiteItems < 6)
                generatedMoves.AddRange(NewBoardPosition(BoardPosition.WhiteTail));

            else
                generatedMoves.AddRange(ChangeBoardPosition(turnPlayerA));

            return generatedMoves;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="board"></param>
        public void IsMoveValid(Board board)
        {
            // IMPLEMENTATION NEEDED
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public int Evaluation()
        {
            // IMPLEMENTATION NEEDED
            return 0;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public bool IsWon()
        {
            // IMPLEMENTATION NEEDED
            return true;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        public int CompareTo(object obj)
        {
            // IMPLEMENTATION NEEDED
            throw new NotImplementedException();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public object Clone()
        {
            // IMPLEMENTATION NEEDED
            throw new NotImplementedException();
        }

        /// <summary>
        /// 
        /// </summary>
        public int RedItems
        {
            get { return amountOfRedItems; }
            set { amountOfRedItems = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public int WhiteItems
        {
            get { return amountOfWhiteItems; }
            set { amountOfWhiteItems = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public BoardPosition[,] BoardSituation
        {
            get { return boardPositions; }
            set { boardPositions = value; }
        }

        public bool IsTileMoved
        {
            get { return isTileMoved; }
            set { isTileMoved = value;}
        }

        private void CalculateMovableTiles()
        {
            this.movablePoints = new List<Point>();

            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    if (boardPositions[x, y] == BoardPosition.Tile)
                    {
                        int emptySpots = 0;

                        if (boardPositions[x, y - 1] == BoardPosition.Empty) emptySpots++;
                        if (boardPositions[x, y + 1] == BoardPosition.Empty) emptySpots++;
                        if (boardPositions[x + 1, y] == BoardPosition.Empty) emptySpots++;
                        if (boardPositions[x - 1, y] == BoardPosition.Empty) emptySpots++;

                        if(emptySpots>=2)
                        {
                            Point point = new Point(x,y);
                            movablePoints.Add(point);
                        }
                    }
                }
            }
        }
    }
}
