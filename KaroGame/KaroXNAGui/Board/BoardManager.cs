using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using GameStateManagement;
using Microsoft.Xna.Framework.Graphics;

namespace Karo.Gui
{
    class BoardManager : GameComponent
    {
        private List<BoardElement> boardElements;
        private Karo.BoardPosition[,] currentBoard;
        private BoardElement selectedElement;
        private GameplayScreen game;
        private UIConnector uiConnector;

        public void StartGame(Difficulty difficulty)
        {
            PlayerSettings playerA = new PlayerSettings(false, AlgorithmType.AlphaBeta, 0, false, false, EvaluationType.BetterOne);
            PlayerSettings playerB = null;
            switch (difficulty)
            {
                case Difficulty.Easy:
                    playerB = new PlayerSettings(true, AlgorithmType.Random, 0, false, false, EvaluationType.BetterOne);
                    break;

                case Difficulty.Medium:
                    playerB = new PlayerSettings(true, AlgorithmType.MiniMax, 1, false, false, EvaluationType.BetterOne);
                    break;

                case Difficulty.Hard:
                    playerB = new PlayerSettings(true, AlgorithmType.AlphaBeta, 4, true, true, EvaluationType.BetterOne);
                    break;
            }
            this.boardElements = new List<BoardElement>();
            uiConnector.StartGame(playerA, playerB);
            SetupBoard();
        }

        public BoardManager(GameplayScreen game)
            : base(game.ScreenManager.Game)
        {
            this.uiConnector = UIConnector.Instance;
            this.game = game;
        }

        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);
        }

        public void DoMove()
        {
        }

        private void SetupBoard()
        {
            currentBoard = uiConnector.GetBoard().BoardSituation;

            foreach (BoardElement boardElement in boardElements)
            {
                boardElement.Dispose();
            }
            
            boardElements.Clear();

            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    BoardPosition boardPosition = currentBoard[x, y];
                    if(boardPosition==BoardPosition.Tile)
                    {
                        Tile boardElement = new Tile(game, game.Tile, y, x);
                        Piece boardElementTile = new Piece(game, game.PieceWhite, y, x);
                        boardElements.Add(boardElement);
                        game.ScreenManager.Game.Components.Add(boardElement);
                        boardElements.Add(boardElementTile);
                        game.ScreenManager.Game.Components.Add(boardElementTile);
                    }
                    if(boardPosition==BoardPosition.WhiteHead || boardPosition==BoardPosition.WhiteTail)
                    {
                        Piece boardElement = new Piece(game, game.PieceWhite, y, x);
                        Tile boardElementTile = new Tile(game, game.Tile, y, x);
                        boardElements.Add(boardElement);
                        boardElements.Add(boardElementTile);
                        game.ScreenManager.Game.Components.Add(boardElement);
                        game.ScreenManager.Game.Components.Add(boardElementTile);
                    }
                    if (boardPosition == BoardPosition.RedHead || boardPosition == BoardPosition.RedTail)
                    {
                        Piece boardElement = new Piece(game, game.PieceRed, y, x);
                        Tile boardElementTile = new Tile(game, game.Tile, y, x);
                        boardElements.Add(boardElement);
                        boardElements.Add(boardElementTile);
                        game.ScreenManager.Game.Components.Add(boardElement);
                        game.ScreenManager.Game.Components.Add(boardElementTile);
                    }
                }
            }
        }
    }
}
