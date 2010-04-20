using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Karo
{
    public class UIConnector
    {
        private static UIConnector instance;

        public UIConnector()
        {
        }

        public static UIConnector Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new UIConnector();
                }
                return instance;
            }
        }

        public void StartGame(PlayerSettings playerA, PlayerSettings playerB)
        {
            // IMPLEMENTATION NEEDED
        }

        public void StartGame(PlayerSettings playerA, PlayerSettings playerB, Board startBoard)
        {
            // IMPLEMENTATION NEEDED
        }

        public void StartGame(PlayerSettings playerA, PlayerSettings playerB, Board startBoard, int startingPlayer)
        {
            // IMPLEMENTATION NEEDED
        }

        public void MoveTile(Point a, Point b)
        {
            // IMPLEMENTATION NEEDED
        }

        public void MovePiece(Point a, Point b)
        {
            // IMPLEMENTATION NEEDED
        }

        /// <summary>
        /// Get the boardstate
        /// </summary>
        /// <returns>The current board</returns>
        public Board GetBoard()
        {
            // IMPLEMENTATION NEEDED
            return null;
        }

        public string GetCurrentPlayer()
        {
            // IMPLEMENTATION NEEDED
            return null;
        }

        public bool IsWon()
        {
            // IMPLEMENTATION NEEDED
            return false;
        }
    }
}
