﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;


namespace Karo
{
    /// <summary>
    /// Wrapper class for connecting to the game
    /// </summary>
    public class UIConnector
    {
        private static UIConnector instance;

        /// <summary>
        /// Constructor
        /// </summary>
        public UIConnector()
        {

        }

        /// <summary>
        /// returns an instance of UIConnector
        /// </summary>
        /// <returns>UIConnector</returns>
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

        /// <summary>
        /// starts a new game
        /// </summary>
        /// <param name="playerA">playersettings of player A</param>
        /// <param name="playerB">playersettings of player B</param>
        public void StartGame(PlayerSettings playerA, PlayerSettings playerB)
        {
            Game.Instance.StartGame(playerA, playerB);
        }
        
        /// <summary>
        /// starts a new game
        /// </summary>
        /// <param name="playerA">playersettings of player A</param>
        /// <param name="playerB">playersettings of player B</param>
        /// <param name="startBoard">a board to start with</param>
        public void StartGame(PlayerSettings playerA, PlayerSettings playerB, Board startBoard)
        {
            Game.Instance.StartGame(playerA, playerB, startBoard);
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
            Game.Instance.StartGame(playerA, playerB, startBoard, startPlayer);
        }

        /// <summary>
        /// Will return what is at position
        /// </summary>
        /// <param name="column">X value of tile</param>
        /// <param name="row">Y value of tile</param>
        /// <returns>BoardPosition</returns>
        public BoardPosition AtPosition(int column, int row)
        {
            return Game.Instance.AtPosition(column, row);
        }

        /// <summary>
        /// Will return what is at position
        /// </summary>
        /// <param name="point">Point of tile</param>
        /// <returns></returns>
        public BoardPosition AtPosition(Point point)
        {
            return Game.Instance.AtPosition(point);
        }

        /// <summary>
        /// moves the tile
        /// </summary>
        /// <param name="a"> position from which to take the tile </param>
        /// <param name="b"> position to place the tile </param>
        public void MoveTile(Point a, Point b)
        {
            Game.Instance.MoveTile(a, b);
        }

        /// <summary>
        /// moves the piece
        /// </summary>
        /// <param name="a"> position from which to take the piece </param>
        /// <param name="b"> position to place the piece </param>
        public void MovePiece(Point a, Point b)
        {
            Game.Instance.MovePiece(a, b);
        }

        /// <summary>
        /// places a piece on board
        /// </summary>
        /// <param name="a"> position to place the piece </param>
        public void PlacePiece(Point a)
        {
            Game.Instance.PlacePiece(a);
        }

        /// <summary>
        /// gets the current board
        /// </summary>
        /// <returns> current board </returns>
        public Board GetBoard()
        {
            return Game.Instance.GetBoard();
        }

        /// <summary>
        /// returns current player
        /// </summary>
        /// <returns> player name : A or B </returns>
        public string GetCurrentPlayer()
        {
            if (Game.Instance.GetTurn())
                return "Player A";
            else
                return "Player B";
        }

        /// <summary>
        /// returns if the game has ended
        /// </summary>
        /// <returns> bool true for winning state </returns>
        public bool IsWon()
        {
            if (Game.Instance.GetBoard().IsWon())
                return true;
            else
                return false;
        }
    }
}
