﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using GameStateManagement;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System.Drawing;
using Point = Microsoft.Xna.Framework.Point;
using FormPoint = System.Drawing.Point;

namespace Karo.Gui
{
    class BoardManager : DrawableGameComponent
    {
        public List<BoardElement> BoardElements { get; set; }
        public List<Tile> PossiblePlaces { get; set; }
        public readonly Microsoft.Xna.Framework.Graphics.Color PossibleColor = Microsoft.Xna.Framework.Graphics.Color.Green;
        public Karo.BoardPosition[,] currentBoard { get; set; }
        public int redItems { get; set; }
        public int whiteItems { get; set; }
        private BoardElement selectedElementFrom;
        private BoardElement selectedElementTo;
        private GameplayScreen game;
        private UIConnector uiConnector;

        public int MaxX { get; set; }
        public int MaxY { get; set; }
        public int MinX { get; set; }
        public int MinY { get; set; }        
        public int BoardWidth { get; private set; }
        public int BoardHeight { get; private set; }

        private bool leftMouseButtonPressed;
        private bool isSelected;
        private TimeSpan timeSpan;
        private bool isGameEnded = false;

        public bool FromTileSelected
        {
            get
            {
                if (selectedElementFrom != null)
                {
                    if (selectedElementFrom.IsPossiblePlace == false)
                    {
                        if (selectedElementFrom.GetType() == typeof(Tile))
                        {
                            return true;
                        }
                    }
                }
                GenerateTargetTiles(false);
                return false;
            }
        }

        public void StartGame(Difficulty difficulty)
        {
            PlayerSettings playerA = new PlayerSettings(false, AlgorithmType.AlphaBeta, 2, true, true, EvaluationType.BetterOne);
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
            uiConnector.StartGame(playerB, playerA);
            leftMouseButtonPressed = false;
            selectedElementFrom = null;
            selectedElementTo = null;
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

            BoardWidth = MaxX - MinX + 1;
            BoardHeight = MaxY - MinY + 1;
        }

        public BoardElement Get(float x, float y)
        {
            foreach (BoardElement b in BoardElements)
            {
                if (b.BoardX == x && b.BoardY == y && b.IsPossiblePlace == false)
                    return b;
            }

            return null;
        }

        public void GenerateTargetTiles()
        {
            GenerateTargetTiles(true);
        }

        public void GenerateTargetTiles(bool generate)
        {
            // new list of possible pos
            List<PointF> possiblePositions = new List<PointF>();

            if (!uiConnector.IsTwoAI())
            {
                if (generate)
                {
                    // get all tiles (also real tiles
                    List<Tile> allTiles = BoardElements.OfType<Tile>().ToList();

                    foreach (Tile t in allTiles)
                    {
                        if (t.IsPossiblePlace == false && !t.IsSelected)
                        {

                            if (Get(t.BoardX - 1, t.BoardY) == null)
                            {
                                PointF left = new PointF(t.BoardX - 1, t.BoardY);
                                if (!possiblePositions.Contains(left))
                                    possiblePositions.Add(left);
                            }

                            if (Get(t.BoardX + 1, t.BoardY) == null)
                            {
                                PointF right = new PointF(t.BoardX + 1, t.BoardY);
                                if (!possiblePositions.Contains(right))
                                    possiblePositions.Add(right);
                            }

                            if (Get(t.BoardX, t.BoardY + 1) == null)
                            {
                                PointF up = new PointF(t.BoardX, t.BoardY + 1);
                                if (!possiblePositions.Contains(up))
                                    possiblePositions.Add(up);
                            }

                            if (Get(t.BoardX, t.BoardY - 1) == null)
                            {
                                PointF down = new PointF(t.BoardX, t.BoardY - 1);
                                if (!possiblePositions.Contains(down))
                                    possiblePositions.Add(down);
                            }
                        }
                    }
                }

                // clear all components
                List<Tile> oldTiles = game.ScreenManager.Game.Components.OfType<Tile>().ToList();

                foreach (Tile t in oldTiles)
                {
                    if (t.IsPossiblePlace)
                    {
                        game.ScreenManager.Game.Components.Remove(t);
                    }
                }
            }

            // only add
            if (generate)
            {
                List<Tile> targetList = new List<Tile>();
                foreach (PointF target in possiblePositions)
                {
                    Tile t = new Tile(game, game.Tile, (int)target.Y, (int)target.X);
                    t.DefaultColor = PossibleColor.ToVector3();
                    t.IsPossiblePlace = true;
                    game.ScreenManager.Game.Components.Add(t);

                    targetList.Add(t);
                }
                PossiblePlaces = targetList;
            }

        }

        public override void Update(GameTime gameTime)
        {
            isSelected = false;
            if (isGameEnded)
            {
                TimeSpan timeSpanCurrent = new TimeSpan(0, 0, 0, gameTime.ElapsedGameTime.Seconds);
                timeSpan.Subtract(timeSpanCurrent);
            }

            if (Mouse.GetState().LeftButton == ButtonState.Pressed)
                leftMouseButtonPressed = true;

            if (leftMouseButtonPressed && Mouse.GetState().LeftButton == ButtonState.Released)
            {
                isSelected = true;
                leftMouseButtonPressed = false;
            }

            Microsoft.Xna.Framework.Point pMouse = new Microsoft.Xna.Framework.Point(Mouse.GetState().X, Mouse.GetState().Y);

            Vector3 nearUnproject = game.ScreenManager.GraphicsDevice.Viewport.Unproject(new Vector3(pMouse.X, pMouse.Y, 0), game.Projection, game.View, Matrix.Identity);
            Vector3 farUnproject = game.ScreenManager.GraphicsDevice.Viewport.Unproject(new Vector3(pMouse.X, pMouse.Y, 1), game.Projection, game.View, Matrix.Identity);

            Vector3 direction = Vector3.Subtract(farUnproject, nearUnproject);

            direction.Normalize();

            Ray ray = new Ray(nearUnproject, direction);

            BoardElement selected = null;
            float? smallestIntersect = float.MaxValue;

            List<BoardElement> intersectList = BoardElements.ToList();
            if(PossiblePlaces != null)
                foreach (BoardElement b in PossiblePlaces)
                    intersectList.Add(b);

            foreach (BoardElement boardElement in intersectList)
            {
                float? intersect = boardElement.Intersect(ray);
                if (intersect != null)
                {
                    if (smallestIntersect > intersect)
                    {
                        selected = boardElement;
                        smallestIntersect = intersect;
                    }
                }

                if (selectedElementFrom != boardElement && boardElement != selectedElementTo)
                {
                    boardElement.IsSelected = false;
                    boardElement.IsMouseOver = false;
                }
            }

            if (selected != null)
            {
                if (isSelected)
                {
                    selected.IsSelected = true;
                    if (selectedElementFrom == null)
                        selectedElementFrom = selected;
                    else if (selectedElementFrom == selected)
                        selectedElementFrom = null;
                    else
                        selectedElementTo = selected;

                    if (FromTileSelected)
                    {
                        if (uiConnector.IsMovable((int)selectedElementFrom.BoardX, (int)selectedElementFrom.BoardY))
                            GenerateTargetTiles();
                    }
                    else
                    {
                        GenerateTargetTiles(false);
                    }
                }
                else
                {
                    selected.IsMouseOver = true;
                }
            }

            if (selectedElementFrom != null && selectedElementTo != null)
                DoMove();

            if (isGameEnded)
            {
                TimeSpan s = (TimeSpan)timeSpan;
                if (s.Seconds < 0)
                {

                }
            }

            UpdateMinMax();

            base.Update(gameTime);
        }

        private void DoAIMove(BoardPosition[,] currentBoard, BoardPosition[,] newBoardSituation)
        {
            int? fromXPiece = null;
            int? fromYPiece = null;
            int? toXPiece = null;
            int? toYPiece = null;

            int? fromXTile = null;
            int? fromYTile = null;
            int? toXTile = null;
            int? toYTile = null;

            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    if (currentBoard[x, y] != newBoardSituation[x, y])
                    {
                        // If on the current board there is a tile and on the new board there is none,/
                        // this is the position where a tile is moved from
                        if (currentBoard[x, y] == BoardPosition.Tile && newBoardSituation[x, y] == BoardPosition.Empty)
                        {
                            fromXTile = x;
                            fromYTile = y;
                        }
                        // If on the current board there isn't a empty spot or a tile, then a piece
                        // was on this spot
                        if (currentBoard[x, y] != BoardPosition.Empty && currentBoard[x, y] != BoardPosition.Tile)
                        {
                            fromXPiece = x;
                            fromYPiece = y;
                        }
                        // If the currentboard position is a tile then a piece was moved to it.
                        if (currentBoard[x, y] == BoardPosition.Tile)
                        {
                            toXPiece = x;
                            toYPiece = y;
                        }
                        // If the current board position is empty then there was a piece and tile move.
                        if (currentBoard[x, y] == BoardPosition.Empty)
                        {
                            toXPiece = x;
                            toYPiece = y;
                            toXTile = x;
                            toYTile = y;
                        }
                    }
                }
            }
            bool found = false;
            // Check if there have been placed new pieces on the board in the starting situation.
            if (fromXPiece == null && fromYPiece == null && toXPiece != null && toYPiece != null)
            {
                Piece movedPiece = null;
                foreach (BoardElement boardElement in BoardElements)
                {
                    if (boardElement is Piece && boardElement.BoardY == 6.5f && !found)
                    {
                        movedPiece = (Piece)boardElement;
                        found = true;
                    }
                }
                if (movedPiece != null)
                {
                    movedPiece.Move((int)toXPiece, (int)toYPiece);
                    while (movedPiece.AnimatedStarted) ;
                }
            }
            else if (fromXTile != null && fromYTile != null && toXTile != null &&
                toYTile != null && fromXPiece != null && fromYPiece != null)
            {
                Tile movedTile = null;
                Piece movedPiece = null;
                foreach (BoardElement tempBoardElement in BoardElements)
                {
                    if (tempBoardElement is Tile)
                    {
                        Tile tempTile = (Tile)tempBoardElement;
                        if (tempTile.BoardX == fromXTile && tempTile.BoardY == fromYTile)
                            movedTile = tempTile;
                    }
                    if (tempBoardElement is Piece)
                    {
                        Piece tempPiece = (Piece)tempBoardElement;
                        if (tempPiece.BoardX == (float)fromXPiece && tempPiece.BoardY == (float)fromYPiece)
                            movedPiece = tempPiece;
                    }
                }
                if (movedTile != null)
                {
                    movedTile.Move((int)toXTile, (int)toYTile);
                    while (movedTile.AnimatedStarted) ;
                }
                if (movedPiece != null)
                {
                    if (newBoardSituation[(int)toXPiece, (int)toYPiece] == BoardPosition.RedTail)
                        movedPiece.HeadUp = false;
                    else
                        movedPiece.HeadUp = true;
                    movedPiece.Move((int)toXTile, (int)toYTile);
                    while (movedPiece.AnimatedStarted) ;
                }
            }
            else
            {
                Piece movedPiece = null;
                foreach (BoardElement tempBoardElement in BoardElements)
                {
                    if (tempBoardElement is Piece)
                    {
                        Piece tempPiece = (Piece)tempBoardElement;
                        if (tempPiece.BoardX == (float)fromXPiece && tempPiece.BoardY == (float)fromYPiece)
                            movedPiece = tempPiece;
                    }
                }
                if (movedPiece != null)
                {
                    if (newBoardSituation[(int)toXPiece, (int)toYPiece] == BoardPosition.RedTail)
                        movedPiece.HeadUp = false;
                    else
                        movedPiece.HeadUp = true;
                    movedPiece.Move((int)toXPiece, (int)toYPiece);
                    while (movedPiece.AnimatedStarted) ;
                }
            }
        }

        public void DoMove()
        {
            int numItems = uiConnector.CurrentPlayerNumPieces();
            if (numItems < 6)
            {
                FormPoint placePoint = new FormPoint((int)selectedElementTo.BoardX,
                                                                           (int)selectedElementTo.BoardY);
                if (uiConnector.ValidatePlacePiece(placePoint))
                {
                    selectedElementFrom.Move((int)selectedElementTo.BoardX, (int)selectedElementTo.BoardY);
                    while (selectedElementFrom.AnimatedStarted) ;

                    currentBoard = (BoardPosition[,])uiConnector.GetBoard().BoardSituation.Clone();
                    currentBoard[(int)selectedElementTo.BoardX, (int)selectedElementTo.BoardY] = BoardPosition.WhiteTail;
                    uiConnector.PlacePiece(placePoint);
                    BoardPosition[,] newBoardSituation = (BoardPosition[,])uiConnector.GetBoard().BoardSituation.Clone();

                    DoAIMove(currentBoard, newBoardSituation);
                }
            }
            else
            {
                FormPoint fromPoint = new FormPoint((int)selectedElementFrom.BoardX,
                                                                           (int)selectedElementFrom.BoardY);
                FormPoint toPoint = new FormPoint((int)selectedElementTo.BoardX,
                                                                           (int)selectedElementTo.BoardY);

                if (uiConnector.ValidateMovePiece(fromPoint, toPoint) && selectedElementFrom is Piece)
                {
                    Piece piece = (Piece)selectedElementFrom;
                    int moveDistance = 0;
                    currentBoard = (BoardPosition[,])uiConnector.GetBoard().BoardSituation.Clone();
                    BoardPosition changeTo = BoardPosition.Empty;
                    if (Math.Abs(fromPoint.X - toPoint.X) == 1 || Math.Abs(fromPoint.Y - toPoint.Y) == 1)
                        moveDistance = 1;
                    if (Math.Abs(fromPoint.X - toPoint.X) == 2 || Math.Abs(fromPoint.Y - toPoint.Y) == 2)
                        moveDistance = 2;

                    if (moveDistance == 1)
                        changeTo = currentBoard[fromPoint.X, fromPoint.Y];
                    else
                    {
                        piece.HeadUp = false;
                        changeTo = BoardPosition.WhiteTail;
                        if (currentBoard[fromPoint.X, fromPoint.Y] == BoardPosition.WhiteTail)
                        {
                            changeTo = BoardPosition.WhiteHead;
                            piece.HeadUp = true;
                        }
                    }
                    currentBoard[fromPoint.X, fromPoint.Y] = BoardPosition.Tile;
                    currentBoard[toPoint.X, toPoint.Y] = changeTo;

                    selectedElementFrom.Move((int)selectedElementTo.BoardX, (int)selectedElementTo.BoardY);
                    while (selectedElementFrom.AnimatedStarted) ;

                    uiConnector.MovePiece(fromPoint, toPoint);
                    BoardPosition[,] newBoardSituation = (BoardPosition[,])uiConnector.GetBoard().BoardSituation.Clone();
                    if (uiConnector.IsWon())
                    {
                        PlayWinningAnimation(uiConnector.GetCurrentPlayer());
                        return;
                    }

                    DoAIMove(currentBoard, newBoardSituation);

                }
                else if (uiConnector.ValidateMoveTile(fromPoint, toPoint))
                {
                    currentBoard = (BoardPosition[,])uiConnector.GetBoard().BoardSituation.Clone();
                    currentBoard[fromPoint.X, fromPoint.Y] = BoardPosition.Empty;
                    currentBoard[toPoint.X, toPoint.Y] = BoardPosition.Tile;
                    Tile tile = (Tile)selectedElementFrom;
                    tile.Move(toPoint.X, toPoint.Y);
                    while (tile.AnimatedStarted) ;
                    uiConnector.MoveTile(fromPoint, toPoint);
                    BoardPosition[,] newBoardSituation = (BoardPosition[,])uiConnector.GetBoard().BoardSituation.Clone();
                }
            }
            selectedElementFrom = null;
            selectedElementTo = null;
            this.UpdateMinMax();
        }


        private void PlayWinningAnimation(string currentPlayer)
        {
            timeSpan = new TimeSpan(0, 0, 0, 30);
            isGameEnded = true;
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

            if (redItems < 6)
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