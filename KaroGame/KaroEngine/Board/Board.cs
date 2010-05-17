using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml;
using System.Xml.Serialization;

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
        private List<Point> piecesList;
        private bool isTileMoved = false;
        private Point movedTilePosition;
        private IEvaluation evaluationFunction;

        /// <summary>
        /// Property for setting evaluation value of the board, used by algorthims.
        /// </summary>
        public int EvaluationValue { get; set; }

        /// <summary>
        /// Property for the movable points
        /// </summary>
        public List<Point> MovablePoints
        {
            get { return movablePoints; }
            private set { movablePoints = value; }
        }

        /// <summary>
        /// Amount of red heads
        /// </summary>
        public int RedHeads
        {
            get
            {
                int count = 0;
                foreach (BoardPosition b in boardPositions)
                {
                    if (b == BoardPosition.RedHead)
                        count++;
                }
                return count;
            }
        }

        /// <summary>
        /// Amount of white heads
        /// </summary>
        public int WhiteHeads
        {
            get
            {
                int count = 0;
                foreach (BoardPosition b in boardPositions)
                {
                    if (b == BoardPosition.WhiteHead)
                        count++;
                }
                return count;
            }
        }


        /// <summary>
        /// 
        /// </summary>
        public Board()
        {
            this.EvaluationValue = 0;

            // what evaluation function to use
            if (Game.Instance.GetCurrentPlayer().PlayerSettings.EvaluationFunction == EvaluationType.FreeSpace)
                evaluationFunction = new FreeSpaceEvaluation();
            else
                evaluationFunction = new BetterEvaluation();

            piecesList = new List<Point>();
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

            amountOfRedItems = 0;
            amountOfWhiteItems = 0;
            CalculateMovableTiles();

            Logger.AddLine("Board created!");
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="boardPositions"></param>
        public Board(BoardPosition[,] boardPositions)
        {
            // what evaluation function to use
            if (Game.Instance.GetCurrentPlayer().PlayerSettings.EvaluationFunction == EvaluationType.FreeSpace)
                evaluationFunction = new FreeSpaceEvaluation();
            else
                evaluationFunction = new BetterEvaluation();

            this.EvaluationValue = 0;
            amountOfRedItems = 0;
            amountOfWhiteItems = 0;
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
                        BoardPosition[,] newBoardPosition = (BoardPosition[,])boardPositions.Clone();
                        newBoardPosition[x, y] = toChange;

                        Board newBoard = new Board(newBoardPosition);

                        if (toChange == BoardPosition.RedTail)
                        {
                            newBoard.RedItems = this.RedItems + 1;
                            newBoard.WhiteItems = this.WhiteItems;
                        }
                        else
                        {
                            newBoard.RedItems = this.RedItems;
                            newBoard.WhiteItems = this.WhiteItems + 1;
                        }
                        newBoard.IsTileMoved = false;
                        boards.Add(newBoard);
                    }
                }
            }

            return boards;
        }

        public void Print()
        {
            if (Game.Instance.ShowDebug)
            {
                for (int y = 0; y < 20; y++)
                {
                    for (int x = 0; x < 21; x++)
                    {
                        System.Console.Out.Write((int)boardPositions[x, y] + " ");
                    }
                    System.Console.Out.Write("\r\n");
                }
                System.Console.Out.Write("\r\n");
            }
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

            if (turnPlayerA)
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
                                if (!(i == 0 && j == 0) && (x + i >= 0 && x + i < 21) && (y + j >= 0 && y + j < 20))
                                {
                                    // Moving a piece to a empty tile next to him
                                    if (boardPositions[x + i, y + j] == BoardPosition.Tile)
                                    {
                                        if ((this.isTileMoved && (this.movedTilePosition.X == x + i && this.movedTilePosition.Y == y + j)) || !this.isTileMoved)
                                        {
                                            BoardPosition[,] newBoardPosition = (BoardPosition[,])boardPositions.Clone();

                                            newBoardPosition[x, y] = BoardPosition.Tile;
                                            newBoardPosition[x + i, y + j] = boardPositions[x, y];

                                            Board newBoard = new Board(newBoardPosition);
                                            newBoard.RedItems = this.RedItems;
                                            newBoard.WhiteItems = this.WhiteItems;
                                            newBoard.IsTileMoved = false;
                                            boards.Add(newBoard);
                                        }
                                    }
                                    // Moving a piece by jumping over a other piece next to him
                                    else if (boardPositions[x + i, y + j] != BoardPosition.Empty)
                                    {
                                        if (x + i + i >= 0 && x + i + i < 21 && y + j + j >= 0 && y + j + j < 20)
                                        {
                                            if (boardPositions[x + i + i, y + j + j] == BoardPosition.Tile || (this.isTileMoved && boardPositions[x + i + i, y + j + j] == BoardPosition.Empty))
                                            {
                                                if ((this.isTileMoved && (this.movedTilePosition.X == x + i + i && this.movedTilePosition.Y == y + j + j)) || !this.isTileMoved)
                                                {
                                                    BoardPosition[,] newBoardPosition =
                                                        (BoardPosition[,])boardPositions.Clone();
                                                    newBoardPosition[x, y] = BoardPosition.Tile;

                                                    if (boardPositions[x, y] == colorTail)
                                                        newBoardPosition[x + i + i, y + j + j] = colorHead;
                                                    else
                                                        newBoardPosition[x + i + i, y + j + j] = colorTail;

                                                    Board newBoard = new Board(newBoardPosition);
                                                    newBoard.RedItems = this.RedItems;
                                                    newBoard.WhiteItems = this.WhiteItems;
                                                    newBoard.IsTileMoved = false;
                                                    boards.Add(newBoard);
                                                }
                                            }
                                            else if (boardPositions[x + i + i, y + j + j] == BoardPosition.Empty && !isTileMoved)
                                            {
                                                Point moveTileTo = new Point(x + i + i, y + j + j);

                                                foreach (Point movablePoint in movablePoints)
                                                {
                                                     if(boardPositions[movablePoint.X, movablePoint.Y] == BoardPosition.Tile)
                                                     {
                                                        BoardPosition[,] newBoardPosition = (BoardPosition[,])boardPositions.Clone();
                                                        newBoardPosition[movablePoint.X, movablePoint.Y] = BoardPosition.Empty;
                                                        newBoardPosition[moveTileTo.X, moveTileTo.Y] = BoardPosition.Tile;
                                                        bool canBeMovedThere = false;

                                                        if (newBoardPosition[moveTileTo.X + 1, moveTileTo.Y] != BoardPosition.Empty)
                                                            canBeMovedThere = true;
                                                        if (newBoardPosition[moveTileTo.X - 1, moveTileTo.Y] != BoardPosition.Empty)
                                                            canBeMovedThere = true;
                                                        if (newBoardPosition[moveTileTo.X, moveTileTo.Y + 1] != BoardPosition.Empty)
                                                            canBeMovedThere = true;
                                                        if (newBoardPosition[moveTileTo.X, moveTileTo.Y - 1] != BoardPosition.Empty)
                                                            canBeMovedThere = true;

                                                        if (canBeMovedThere)
                                                        {
                                                            Board newBoard = new Board(newBoardPosition);
                                                            newBoard.RedItems = this.RedItems;
                                                            newBoard.WhiteItems = this.WhiteItems;
                                                            newBoard.IsTileMoved = true;
                                                            newBoard.MovedTilePosition = moveTileTo;
                                                            boards.Add(newBoard);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else if (!isTileMoved && (boardPositions[x + i, y + j] == BoardPosition.Empty || boardPositions[x + i + i, y + j + j] == BoardPosition.Empty))
                                    {
                                        bool isMovableTile = false;

                                        if ((i == -1 && j == -1) ||
                                            (i == 1 && j == 1) ||
                                            (i == -1 && j == 1) ||
                                            (i == 1 && j == -1))
                                        {
                                            int currentI = x + i;
                                            int currentJ = y + j;

                                            if (currentJ - 1 >= 0)
                                                if (boardPositions[currentI, currentJ - 1] != BoardPosition.Empty) isMovableTile = true;
                                            if (currentJ + 1 < 20)
                                                if (boardPositions[currentI, currentJ + 1] != BoardPosition.Empty) isMovableTile = true;
                                            if (currentI + 1 < 21)
                                                if (boardPositions[currentI + 1, currentJ] != BoardPosition.Empty) isMovableTile = true;
                                            if (currentI - 1 >= 0)
                                                if (boardPositions[currentI - 1, currentJ] != BoardPosition.Empty) isMovableTile = true;
                                        }
                                        else
                                            isMovableTile = true;

                                        if (isMovableTile)
                                        {
                                            Point moveTileTo = new Point(x + i, y + j);
                                            if (boardPositions[x + i, y + j] != BoardPosition.Empty)
                                            {
                                                moveTileTo.X += i;
                                                moveTileTo.Y += j;
                                            }
                                            foreach (Point movablePoint in movablePoints)
                                            {
                                                if(boardPositions[movablePoint.X, movablePoint.Y] == BoardPosition.Tile)
                                                {
                                                    BoardPosition[,] newBoardPosition = (BoardPosition[,])boardPositions.Clone();
                                                    newBoardPosition[movablePoint.X, movablePoint.Y] = BoardPosition.Empty;
                                                    newBoardPosition[moveTileTo.X, moveTileTo.Y] = BoardPosition.Tile;
                                                    bool canBeMovedThere = false;

                                                    if (newBoardPosition[moveTileTo.X + 1, moveTileTo.Y] != BoardPosition.Empty)
                                                        canBeMovedThere = true;
                                                    if (newBoardPosition[moveTileTo.X - 1, moveTileTo.Y] != BoardPosition.Empty)
                                                        canBeMovedThere = true;
                                                    if (newBoardPosition[moveTileTo.X, moveTileTo.Y + 1] != BoardPosition.Empty)
                                                        canBeMovedThere = true;
                                                    if (newBoardPosition[moveTileTo.X, moveTileTo.Y - 1] != BoardPosition.Empty)
                                                        canBeMovedThere = true;

                                                    if (canBeMovedThere)
                                                    {
                                                        Board newBoard = new Board(newBoardPosition);
                                                        newBoard.RedItems = this.RedItems;
                                                        newBoard.WhiteItems = this.WhiteItems;
                                                        newBoard.IsTileMoved = true;
                                                        newBoard.MovedTilePosition = moveTileTo;
                                                        boards.Add(newBoard);
                                                    }
                                                }
                                            }
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

            if (turnPlayerA && RedItems < 6)
                generatedMoves.AddRange(NewBoardPosition(BoardPosition.RedTail));

            else if (!turnPlayerA && WhiteItems < 6)
                generatedMoves.AddRange(NewBoardPosition(BoardPosition.WhiteTail));

            else
                generatedMoves.AddRange(ChangeBoardPosition(turnPlayerA));

            foreach( Board b in generatedMoves)
                b.EvaluationValue = b.Evaluation(turnPlayerA);

            //Logger.AddLine("Generated moves: " + generatedMoves.Count);
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
        public int Evaluation(bool isRed)
        {
            return evaluationFunction.Evaluate(this, isRed);
        }

        /// <summary>
        /// checking if the current board state is winning for any player
        /// </summary>
        /// <returns> true for winning state </returns>
        public bool IsWon()
        {
            int x = 0, y = 0, FourInARow = 0, count = this.amountOfRedItems + this.amountOfWhiteItems;
            BoardPosition checking = BoardPosition.Empty;

            for (; x < 21 && count != 0; x++)
            {
                FourInARow = 0;

                for (y = 0; y < 20 && count != 0; y++)
                {
                    if (boardPositions[x, y] != BoardPosition.Empty && boardPositions[x, y] != BoardPosition.Tile)
                    {
                        count--;
                        if (boardPositions[x, y] == BoardPosition.RedHead || boardPositions[x, y] == BoardPosition.WhiteHead)
                        {
                            if (IsRowWinning(x, y))
                                return true;
                            if (IsDiagWinning(x, y))
                                return true;
                            if (boardPositions[x, y] != checking)
                            {
                                checking = boardPositions[x, y];
                                FourInARow = 1;
                            }
                            else if (++FourInARow == 4)
                                return true;
                        }
                        else
                        {
                            checking = BoardPosition.Empty;
                            FourInARow = 0;
                        }
                    }
                }
            }

            return false;
        }

        /// <summary>
        /// checking for winning state in row around given piece
        /// </summary>
        /// <param name="x"> x positon of piece from which to check </param>
        /// <param name="y"> y positon of piece from which to check </param>
        /// <returns>true for winning in a row</returns>
        private bool IsRowWinning(int x, int y)
        {
            int FourInARowRight = 1, FourInARowLeft = 1;
            bool find = false;
            BoardPosition checking = boardPositions[x, y];

            for (int i = 1; i < 4; i++)
            {
                if (x + i < 21)
                    if (boardPositions[x + i, y] == checking)
                        if (++FourInARowRight == 4)
                        {
                            find = true;
                            break;
                        }

                if (x - i > -1)
                    if (boardPositions[x - i, y] == checking)
                        if (++FourInARowLeft == 4)
                        {
                            find = true;
                            break;
                        }
            }

            return find;
        }

        /// <summary>
        /// checking for winning state in diagonal around given piece
        /// </summary>
        /// <param name="x"> x positon of piece from which to check </param>
        /// <param name="y"> y positon of piece from which to check </param>
        /// <returns>true for winning in a diagonal</returns>
        private bool IsDiagWinning(int x, int y)
        {
            int FourInARowUpperRight = 1, FourInARowUpperLeft = 1, FourInARowLowerRight = 1, FourInARowLowerLeft = 1;
            bool find = false;
            BoardPosition checking = boardPositions[x, y];

            for (int i = 1; i < 4; i++)
            {
                if (x + i < 21 && y - i > -1)
                    if (boardPositions[x + i, y - i] == checking)
                        if (++FourInARowUpperRight == 4)
                        {
                            find = true;
                            break;
                        }

                if (x - i > -1 && y - i > -1)
                    if (boardPositions[x - i, y - i] == checking)
                        if (++FourInARowUpperLeft == 4)
                        {
                            find = true;
                            break;
                        }

                if (x + i < 21 && y + i < 20)
                    if (boardPositions[x + i, y + i] == checking)
                        if (++FourInARowLowerRight == 4)
                        {
                            find = true;
                            break;
                        }

                if (x - i > -1 && y + i < 20)
                    if (boardPositions[x - i, y + i] == checking)
                        if (++FourInARowLowerLeft == 4)
                        {
                            find = true;
                            break;
                        }
            }

            return find;
        }


        /// <summary>
        /// 
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        public int CompareTo(object obj)
        {
            Board b = (Board)obj;

            if (b.WhiteItems == this.WhiteItems &&
                b.IsTileMoved == this.IsTileMoved &&
                b.RedItems == this.RedItems)
            {

                for (int x = 0; x < 21; x++)
                {
                    for (int y = 0; y < 20; y++)
                    {
                        if (b.BoardSituation[x, y] != this.boardPositions[x, y])
                        {
                            BoardPosition b1 = b.BoardSituation[x, y];
                            BoardPosition b2 = this.BoardSituation[x, y];
                            return 1;
                        }
                    }
                }
                return 0;
            }
            return 1;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public object Clone()
        {
            Board b = new Board((BoardPosition[,])this.BoardSituation.Clone());
            b.WhiteItems = this.WhiteItems;
            b.IsTileMoved = this.IsTileMoved;
            b.RedItems = this.RedItems;
            b.MovedTilePosition = this.movedTilePosition;
            return b;
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

        public Point MovedTilePosition
        {
            get { return this.movedTilePosition; }
            set { this.movedTilePosition = value; }
        }

        public bool IsTileMoved
        {
            get { return isTileMoved; }
            set { isTileMoved = value; }
        }

        public void CalculateMovableTiles()
        {
            this.movablePoints = new List<Point>();

            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    if (boardPositions[x, y] == BoardPosition.Tile)
                    {
                        int emptySpots = 0;

                        if (y - 1 >= 0)
                            if (boardPositions[x, y - 1] == BoardPosition.Empty) emptySpots++;
                        if (y + 1 < 20)
                            if (boardPositions[x, y + 1] == BoardPosition.Empty) emptySpots++;
                        if (x + 1 < 21)
                            if (boardPositions[x + 1, y] == BoardPosition.Empty) emptySpots++;
                        if (x - 1 >= 0)
                            if (boardPositions[x - 1, y] == BoardPosition.Empty) emptySpots++;

                        if (emptySpots >= 2)
                        {
                            Point point = new Point(x, y);
                            movablePoints.Add(point);
                        }
                    }
                }
            }

            ValidateMovableTiles();
        }

        private void ValidateMovableTiles()
        {
            List<Point> movablePointsValidated = new List<Point>();

            foreach (Point point in movablePoints)
            {
                List<Point> visitedPoints = new List<Point>();

                BoardPosition[,] b = (BoardPosition[,])this.boardPositions.Clone();

                b[point.X, point.Y] = BoardPosition.Empty;

                Point pointToCheck = new Point();


                if (point.X + 1 < 21)
                {
                    if (b[point.X + 1, point.Y] != BoardPosition.Empty)
                        pointToCheck = new Point(point.X + 1, point.Y);
                }

                if (point.X - 1 > 0)
                {
                    if (b[point.X - 1, point.Y] != BoardPosition.Empty)
                        pointToCheck = new Point(point.X - 1, point.Y);
                }

                if (point.Y - 1 > 0)
                {
                    if (b[point.X, point.Y - 1] != BoardPosition.Empty)
                        pointToCheck = new Point(point.X, point.Y - 1);
                }

                if (point.Y + 1 < 20)
                {
                    if (b[point.X, point.Y + 1] != BoardPosition.Empty)
                        pointToCheck = new Point(point.X, point.Y + 1);
                }

                if (pointToCheck.X != 0 && pointToCheck.Y != 0)
                    VisitedPoints(visitedPoints, pointToCheck, b);

                if (visitedPoints.Count >= 19)
                    movablePointsValidated.Add(point);
            }

            this.movablePoints = movablePointsValidated;
        }

        private void VisitedPoints(List<Point> visitedPoints, Point point, BoardPosition[,] b)
        {
            if (b[point.X + 1, point.Y] != BoardPosition.Empty)
            {
                Point p = new Point(point.X + 1, point.Y);
                if (!visitedPoints.Contains(p))
                {
                    visitedPoints.Add(p);
                    VisitedPoints(visitedPoints, p, b);
                }
            }
            if (b[point.X - 1, point.Y] != BoardPosition.Empty)
            {
                Point p = new Point(point.X - 1, point.Y);
                if (!visitedPoints.Contains(p))
                {
                    visitedPoints.Add(p);
                    VisitedPoints(visitedPoints, p, b);
                }
            }
            if (b[point.X, point.Y - 1] != BoardPosition.Empty)
            {
                Point p = new Point(point.X, point.Y - 1);
                if (!visitedPoints.Contains(p))
                {
                    visitedPoints.Add(p);
                    VisitedPoints(visitedPoints, p, b);
                }
            }
            if (b[point.X, point.Y + 1] != BoardPosition.Empty)
            {
                Point p = new Point(point.X, point.Y + 1);
                if (!visitedPoints.Contains(p))
                {
                    visitedPoints.Add(p);
                    VisitedPoints(visitedPoints, p, b);
                }
            }
        }
    }
}
