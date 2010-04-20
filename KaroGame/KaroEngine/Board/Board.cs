using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    public class Board : IComparable, ICloneable
    {
        private BoardPosition[,] boardPositions;
        private int amountOfRedItems;
        private int amountOfWhiteItems;

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

            amountOfRedItems = 0;
            amountOfWhiteItems = 0;
        }

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

                        Board newBoard = new Board();
                        newBoard.BoardSituation = newBoardPosition;

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

                        boards.Add(newBoard);
                    }
                }
            }

            return boards;
        }

        public List<Board> ChangeBoardPosition(bool turnPlayerA)
        {
            List<Board> boards = new List<Board>();

            if (turnPlayerA)
            {
                for (int x = 0; x < 20; x++)
                {
                    for (int y = 0; y < 21; y++)
                    {
                        if(boardPositions[x, y] == BoardPosition.RedHead || boardPositions[x, y] == BoardPosition.RedTail)
                        {
                            for(int i=-1; x < 2; i++)
                            {
                                

                            }

                            //FirstLeft   
                            //boardPositions[x - 1, y - 1];
                            //FirstMiddle 
                            //    boardPositions[x, y-1]
                            //FirstRight  
                            //    boardPositions[x+1, y-1]
                            //SecondLeft  
                            //    boardPositions[x-1, y]
                            //SecondRight 
                             //   boardPositions[x+1, y]
                            //ThirdLeft   
                            //    boardPositions[x-1, y+1]
                            //ThirdMiddle 
                            //    boardPositions[x, y+1]
                            //ThirdRight  
                            //    boardPositions[x+1, y+1]
                        }
                    }
                }
            }
            else
            {
                
            }

            return boards;
        }

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

        public int RedItems
        {
            get { return amountOfRedItems; }
            set { amountOfRedItems = value; }
        }

        public int WhiteItems
        {
            get { return amountOfWhiteItems; }
            set { amountOfWhiteItems = value; }
        }

        public BoardPosition[,] BoardSituation
        {
            get { return boardPositions; }
            set { boardPositions = value; }
        }
    }
}
