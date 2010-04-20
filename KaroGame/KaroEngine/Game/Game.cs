using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Karo
{
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
        /// move tile to a new point
        /// </summary>
        /// <param name="a">from point</param>
        /// <param name="b">to point</param>
        public void MoveTile(Point a, Point b)
        {
            turnPlayerA = (turnPlayerA ? false : true);
        }

        /// <summary>
        /// move piece to a new point
        /// </summary>
        /// <param name="a">from point</param>
        /// <param name="b">to point</param>
        public void MovePiece(Point a, Point b)
        {
            turnPlayerA = (turnPlayerA ? false : true);
        }

        /// <summary>
        /// place pace to a point
        /// </summary>
        /// <param name="point">point for piece</param>
        public void PlacePiece(Point point)
        {
            turnPlayerA = (turnPlayerA ? false : true);
        }

        /// <summary>
        /// starts a new game
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
        }

        /// <summary>
        /// starts a new game
        /// </summary>
        /// <param name="playerA">playersettings of player A</param>
        /// <param name="playerB">playersettings of player B</param>
        /// <param name="startBoard">a board to start with</param>
        public void StartGame(PlayerSettings playerA, PlayerSettings playerB, Board startBoard)
        {
            this.playerA = new AIPlayer(playerA);
            this.playerB = new AIPlayer(playerB);
            this.board = startBoard;
            turnPlayerA = true;
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
            turnPlayerA = true;
            board = new Board();
        }
    }
}
