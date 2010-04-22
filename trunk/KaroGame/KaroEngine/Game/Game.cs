using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Timers;

namespace Karo
{
    /// <summary>
    /// Kind of world to contain much
    /// </summary>
    public class Game
    {
        private AIPlayer playerA;
        private AIPlayer playerB;
        private Boolean turnPlayerA;
        private Board board;
        private static Game instance;

        private Game() { }

        /// <summary>
        /// returns an instance of game
        /// </summary>
        /// <returns>game</returns>
        public static Game Instance
        {
            get
            {
                if (instance == null)
                    instance = new Game();
                return instance;
            }
        }

        /// <summary>
        /// gets the current board
        /// </summary>
        /// <returns>current board</returns>
        public Board GetBoard()
        {
            List<Board> moves = board.GenerateMoves(turnPlayerA);
            return board;
        }

        /// <summary>
        /// gets the current player
        /// </summary>
        /// <returns>bool turn of PlayerA</returns>
        public Boolean GetTurn()
        {
            return turnPlayerA;
        }

        /// <summary>
        /// sets the board
        /// </summary>
        /// <param name="board">the new board</param>
        public void SetBoard(Board board)
        {
            this.board = board;
        }

        /// <summary>
        /// Will return what is at position
        /// </summary>
        /// <param name="column">X value of tile</param>
        /// <param name="row">Y value of tile</param>
        /// <returns>BoardPosition</returns>
        public BoardPosition AtPosition(int column, int row)
        {
            return board.BoardSituation[column, row];
        }

        /// <summary>
        /// Will return what is at position
        /// </summary>
        /// <param name="point">Point of tile</param>
        /// <returns></returns>
        public BoardPosition AtPosition(Point point)
        {
            return AtPosition(point.X, point.Y);
        }

        /// <summary>
        /// move tile to a new point
        /// </summary>
        /// <param name="a">from point</param>
        /// <param name="b">to point</param>
        public void MoveTile(Point a, Point b)
        {
            board.BoardSituation[b.X, b.Y] = BoardPosition.Tile;
            board.BoardSituation[a.X, a.Y] = BoardPosition.Empty;

            Logger.AddLine(GetCurrentPlayerNumber() + "-> Moved tile from: " + a.X + ", " + a.Y + " to " + b.X + ", " + b.Y);
        }

        /// <summary>
        /// move piece to a new point and switches the turn
        /// </summary>
        /// <param name="a">from point</param>
        /// <param name="b">to point</param>
        public void MovePiece(Point a, Point b)
        {
            BoardPosition old = board.BoardSituation[a.X, a.Y];
            board.BoardSituation[b.X, b.Y] = old;
            board.BoardSituation[a.X, a.Y] = BoardPosition.Tile;

            Logger.AddLine(GetCurrentPlayerNumber() + "-> Moved piece from: " + a.X + ", " + a.Y + " to " + b.X + ", " + b.Y);
            ChangePlayer();
        }

        /// <summary>
        /// place pace to a point and switches the turn
        /// </summary>
        /// <param name="point">point for piece</param>
        public void PlacePiece(Point point)
        {
            board.BoardSituation[point.X, point.Y] = (turnPlayerA ? BoardPosition.RedTail : BoardPosition.WhiteTail);
            
            if (turnPlayerA)
                board.RedItems++;
            else
                board.WhiteItems++;

            Logger.AddLine(GetCurrentPlayerNumber() + "-> Placed piece on: " + point.X + ", " + point.Y);
            ChangePlayer();
        }

        /// <summary>
        /// starts a new game with a startboard and a turningplayer
        /// </summary>
        /// <param name="playerA">playersettings of player A</param>
        /// <param name="playerB">playersettings of player B</param>
        /// <param name="startBoard">a board to start with</param>
        /// <param name="startPlayer">player that turns first</param>
        public void StartGame(PlayerSettings playerA, PlayerSettings playerB, Board startBoard, int startPlayer)
        {
            this.playerA = new AIPlayer(playerA);
            this.playerB = new AIPlayer(playerB);
            this.board = startBoard;
            this.turnPlayerA = (startPlayer == 0 ? true : false);

            Logger.AddLine("Start new game, with startboard and turningPlayer");
        }

        /// <summary>
        /// starts a new game with a starboard
        /// </summary>
        /// <param name="playerA">playersettings of player A</param>
        /// <param name="playerB">playersettings of player B</param>
        /// <param name="startBoard">a board to start with</param>
        public void StartGame(PlayerSettings playerA, PlayerSettings playerB, Board startBoard)
        {
            this.playerA = new AIPlayer(playerA);
            this.playerB = new AIPlayer(playerB);
            this.board = startBoard;
            
            // random first player
            System.Random r = new System.Random();
            int player = r.Next(1, 3);
            
            turnPlayerA = true;
            if(player == 2)
                turnPlayerA = false;

            Logger.AddLine("Start new game, with startboard");
        }

        /// <summary>
        /// starts a new game
        /// </summary>
        /// <param name="playerA">playersettings of player A</param>
        /// <param name="playerB">playersettings of player B</param>
        public void StartGame(PlayerSettings playerA, PlayerSettings playerB)
        {
            this.playerA = new AIPlayer(playerA);
            this.playerB = new AIPlayer(playerB);

            // random first player
            System.Random r = new System.Random();
            int player = r.Next(1, 3);

            turnPlayerA = true;
            if (player == 2)
                turnPlayerA = false;

            board = new Board();

            Logger.AddLine("Start new game");
        }

        /// <summary>
        /// Returns the amount of pieces of the current player
        /// </summary>
        /// <returns>Min 0, max 6</returns>
        public int CurrentPlayerNumPieces()
        {
            if (turnPlayerA)
                return board.RedItems;
            else
                return board.WhiteItems;
        }

        /// <summary>
        /// Changes the current player and checks if he want to do something
        /// </summary>
        public void ChangePlayer()
        {
            turnPlayerA = (turnPlayerA ? false : true);
            DateTime beforeFunction = DateTime.Now;            

            if (turnPlayerA && playerA.PlayerSettings.IsAI)
            {
                playerA.Execute(board);

                // Elapsed time
                DateTime afterFunction = DateTime.Now;
                TimeSpan elapsedTime = afterFunction - beforeFunction;
                Logger.AddLine(GetCurrentPlayerNumber() + "-> AI calculated in: " + elapsedTime.TotalMilliseconds.ToString() + " ms");

                ChangePlayer();
            }
            else if (!turnPlayerA && playerB.PlayerSettings.IsAI)
            {
                playerB.Execute(board);

                // Elapsed time
                DateTime afterFunction = DateTime.Now;
                TimeSpan elapsedTime = afterFunction - beforeFunction;
                Logger.AddLine(GetCurrentPlayerNumber() + "-> AI calculated in: " + elapsedTime.TotalMilliseconds.ToString() + " ms");

                ChangePlayer();
            }
        }

        /// <summary>
        /// Returns current player number
        /// </summary>
        /// <returns>1 or 2</returns>
        public int GetCurrentPlayerNumber()
        {
            if (GetTurn())
                return 1;
            else
                return 2;
        }
    }
}
