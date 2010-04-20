using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Karo
{
    class Game
    {
        private AIPlayer playerA;
        private AIPlayer playerB;
        private Boolean turnPlayerA;
        private Board board;

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
        }

        public void MovePiece(Point a, Point b)
        {
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
        }

        public void StartGame(PlayerSettings playerA, PlayerSettings playerB)
        {
            this.playerA = new AIPlayer(playerA);
            this.playerB = new AIPlayer(playerB);
        }
    }
}
