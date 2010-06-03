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
        public List<BoardElement> BoardElements { get; set; }
        public Karo.BoardPosition[,] currentBoard { get; set; }
        public int redItems { get; set; }
        public int whiteItems { get; set; }
        private BoardElement selectedElement;
        private GameplayScreen game;
        private UIConnector uiConnector;
        public int MaxX { get; set; }
        public int MaxY { get; set; }
        public int MinX { get; set; }
        public int MinY { get; set; }

        public void StartGame(Difficulty difficulty)
        {
            PlayerSettings playerA = new PlayerSettings(true, AlgorithmType.AlphaBeta, 0, false, false, EvaluationType.BetterOne);
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
            this.BoardElements = new List<BoardElement>();
            uiConnector.StartGame(playerA, playerB);
            SetupBoard();
        }

        public BoardManager(GameplayScreen game)
            : base(game.ScreenManager.Game)
        {
            this.uiConnector = UIConnector.Instance;
            this.game = game;
        }

        public void UpdateMinMax()
        {
            MinX = Int32.MaxValue;
            MinY = Int32.MaxValue;
            MaxX = Int32.MinValue;
            MaxY = Int32.MinValue;

            foreach (BoardElement be in BoardElements)
            {
                if (redItems == 6 && whiteItems == 6)
                {
                    MinX = Math.Min((int)be.BoardX, MinX);
                    MinY = Math.Min((int)be.BoardY, MinY);
                    MaxX = Math.Max((int)be.BoardX, MaxX);
                    MaxY = Math.Max((int)be.BoardY, MaxY);
                }
                else
                {
                    MinX = 8;
                    MinY = 8;
                    MaxX = 12;
                    MaxY = 11;
                }
            }
        }

        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);
        }

        public void DoMove()
        {
        }

        public void SetupBoard()
        {
            if (!uiConnector.IsTwoAI() || currentBoard == null)
            {
                Board tempBoard = uiConnector.GetBoard();
                currentBoard = tempBoard.BoardSituation;
                whiteItems = tempBoard.WhiteItems;
                redItems = tempBoard.RedItems;
            }

            foreach (BoardElement boardElement in BoardElements)
            {
                boardElement.Dispose();
            }

            BoardElements.Clear();
            
            if (redItems<6)
            {
                float y = 6.5f;
                float x = 7.5f;
                for (int i = redItems; i < 6; i++)
                {
                    Piece boardElement = new Piece(game, game.PieceRed, y, x);
                    BoardElements.Add(boardElement);
                    game.ScreenManager.Game.Components.Add(boardElement);
                    x += 1;
                }
            }
            if (whiteItems < 6)
            {
                float y = 12.5f;
                float x = 7.5f;
                for (int i = whiteItems; i < 6; i++)
                {
                    Piece boardElement = new Piece(game, game.PieceWhite, y, x);
                    BoardElements.Add(boardElement);
                    game.ScreenManager.Game.Components.Add(boardElement);
                    x += 1;
                }
            }
            

            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    BoardPosition boardPosition = currentBoard[x, y];
                    if (boardPosition == BoardPosition.Tile)
                    {
                        Tile boardElement = new Tile(game, game.Tile, y, x);
                        BoardElements.Add(boardElement);
                        game.ScreenManager.Game.Components.Add(boardElement);
                    }
                    if (boardPosition == BoardPosition.WhiteHead || boardPosition == BoardPosition.WhiteTail)
                    {
                        Piece boardElement = new Piece(game, game.PieceWhite, y, x);
                        if (boardPosition == BoardPosition.WhiteHead)
                            boardElement.HeadUp = true;
                        Tile boardElementTile = new Tile(game, game.Tile, y, x);
                        BoardElements.Add(boardElement);
                        BoardElements.Add(boardElementTile);
                        game.ScreenManager.Game.Components.Add(boardElement);
                        game.ScreenManager.Game.Components.Add(boardElementTile);
                    }
                    if (boardPosition == BoardPosition.RedHead || boardPosition == BoardPosition.RedTail)
                    {
                        Piece boardElement = new Piece(game, game.PieceRed, y, x);
                        if (boardPosition == BoardPosition.RedHead)
                            boardElement.HeadUp = true;
                        Tile boardElementTile = new Tile(game, game.Tile, y, x);
                        BoardElements.Add(boardElement);
                        BoardElements.Add(boardElementTile);
                        game.ScreenManager.Game.Components.Add(boardElement);
                        game.ScreenManager.Game.Components.Add(boardElementTile);
                    }
                }
            }
        }
    }
}
