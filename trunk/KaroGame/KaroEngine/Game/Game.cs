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

        public static Game Instance
        {
            get
            {
                if (instance == null)
                    instance = new Game();
                return instance;
            }
        }

        public Board GetBoard()
        {
            return board;
        }

        public void SetBoard(Board board)
        {
            this.board = board;
        }

        public void MoveTile(Point a, Point b)
        {
            turnPlayerA = (turnPlayerA ? false : true);
        }

        public void MovePiece(Point a, Point b)
        {
            turnPlayerA = (turnPlayerA ? false : true);
        }

        public void PlacePiece(Point point)
        {
            turnPlayerA = (turnPlayerA ? false : true);
        }

        public void StartGame(PlayerSettings playerA, PlayerSettings playerB, Board startBoard, int startPlayer)
        {
            this.playerA = new AIPlayer(playerA);
            this.playerB = new AIPlayer(playerB);
            this.board = startBoard;
            this.turnPlayerA = (startPlayer == 0 ? true : false);
        }

        public void StartGame(PlayerSettings playerA, PlayerSettings playerB, Board startBoard)
        {
            this.playerA = new AIPlayer(playerA);
            this.playerB = new AIPlayer(playerB);
            this.board = startBoard;
            turnPlayerA = true;
        }

        public void StartGame(PlayerSettings playerA, PlayerSettings playerB)
        {
            this.playerA = new AIPlayer(playerA);
            this.playerB = new AIPlayer(playerB);
            turnPlayerA = true;
            board = new Board();
        }
    }
}
