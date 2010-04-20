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
            Game.Instance.StartGame(playerA, playerB);
        }

        public void StartGame(PlayerSettings playerA, PlayerSettings playerB, Board startBoard)
        {
            Game.Instance.StartGame(playerA, playerB, startBoard);
        }

        public void StartGame(PlayerSettings playerA, PlayerSettings playerB, Board startBoard, int startPlayer)
        {
            Game.Instance.StartGame(playerA, playerB, startBoard, startPlayer);
        }

        public void MoveTile(Point a, Point b)
        {
            Game.Instance.MoveTile(a, b);
        }

        public void MovePiece(Point a, Point b)
        {
            Game.Instance.MovePiece(a, b);
        }

        public void PlacePiece(Point a)
        {
            Game.Instance.PlacePiece(a);
        }

        public Board GetBoard()
        {
            return Game.Instance.GetBoard();
        }

        public string GetCurrentPlayer()
        {
            if (Game.Instance.GetTurn())
                return "Player A";
            else
                return "Player B";
        }

        public bool IsWon()
        {
            if (Game.Instance.GetBoard().IsWon())
                return true;
            else
                return false;
        }

        //void Showlog()
        //{
        //    Logger.ShowLog();
        //}
    }
}
