using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Karo
{
    public class UIConnector
    {
        public static UIConnector instance;

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

        void StartGame(PlayerSettings playerA, PlayerSettings playerB)
        {
            // IMPLEMENTATION NEEDED
        }

        void StartGame(PlayerSettings playerA, PlayerSettings playerB, Board startBoard)
        {
            // IMPLEMENTATION NEEDED
        }

        void StartGame(PlayerSettings playerA, PlayerSettings playerB, Board startBoard, int startingPlayer)
        {
            // IMPLEMENTATION NEEDED
        }

        void MoveTile(Point a, Point b)
        {
            // IMPLEMENTATION NEEDED
        }

        void MovePiece(Point a, Point b)
        {
            // IMPLEMENTATION NEEDED
        }

        Board GetBoard()
        {
            // IMPLEMENTATION NEEDED
            return null;
        }

        string GetCurrentPlayer()
        {
            // IMPLEMENTATION NEEDED
            return null;
        }

        bool IsWon()
        {
            // IMPLEMENTATION NEEDED
            return false;
        }

        void Showlog()
        {
            // IMPLEMENTATION NEEDED
        }
    }
}
