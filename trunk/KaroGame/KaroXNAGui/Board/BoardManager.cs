using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using GameStateManagement;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System.Drawing;
using Color = Microsoft.Xna.Framework.Graphics.Color;
using Point = Microsoft.Xna.Framework.Point;
using FormPoint = System.Drawing.Point;
using System.Threading;

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

        public bool AICalculates { get; private set; }
        public bool HumanCalculates { get; private set; }
        private BoardElement selectedElementFrom;
        private BoardElement selectedElementTo;
        private GameplayScreen game;
        private UIConnector uiConnector;
        private Difficulty difficulty;
        private Matrix world, worldWhite, worldRed, worldBlue, view, projection;
        private Model cogwheel, cogwheelRed, cogwheelBlue, cogwheelWhite;
        private Matrix[] transforms, transformsRed, transformsBlue, transformsWhite;
        private SoundPlayer wrongMoveSound;

        public int MaxX { get; set; }
        public int MaxY { get; set; }
        public int MinX { get; set; }
        public int MinY { get; set; }
        public int BoardWidth { get; private set; }
        public int BoardHeight { get; private set; }

        private bool leftMouseButtonPressed;
        private bool isSelected;
        private TimeSpan timeSpan;
        private SpriteBatch spriteBatch;
        private bool isGameEnded = false;
        private bool isBusy = false;
        private bool threadWaiting = false;
        private bool undoMove = false;
        private bool rightMouseButtonPressed = false;

        public float XRotation { get; set; }
        public float ZRotation { get; set; }

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
            PlayerSettings playerA = new PlayerSettings(false, AlgorithmType.AlphaBeta, 2, false, false, EvaluationType.BetterOne);
            PlayerSettings playerB = null;
            this.difficulty = difficulty;
            switch (difficulty)
            {
                case Difficulty.Easy:
                    playerB = new PlayerSettings(true, AlgorithmType.AlphaBeta, 2, false, false, EvaluationType.BetterOne);
                    break;

                case Difficulty.Medium:
                    playerB = new PlayerSettings(true, AlgorithmType.AlphaBeta, 3, false, false, EvaluationType.BetterOne);
                    break;

                case Difficulty.Hard:
                    playerB = new PlayerSettings(true, AlgorithmType.AlphaBeta, 4, false, false, EvaluationType.BetterOne);
                    break;
            }

            this.BoardElements = new List<BoardElement>();
            uiConnector.StartGame(playerB, playerA);
            leftMouseButtonPressed = false;
            selectedElementFrom = null;
            selectedElementTo = null;
            SetupBoard();
        }

        private void ClearScreen()
        {
            List<GameComponent> clearList = new List<GameComponent>();

            foreach (GameComponent gameComponent in game.ScreenManager.Game.Components)
            {
                if (!(gameComponent is BoardElement))
                {
                    clearList.Add(gameComponent);
                }
            }

            game.ScreenManager.Game.Components.Clear();

            foreach (GameComponent gameComponent in clearList)
            {
                game.ScreenManager.Game.Components.Add(gameComponent);
            }
        }

        protected override void LoadContent()
        {
            cogwheel = game.ScreenManager.Game.Content.Load<Model>("Cogwheel"); ;
            cogwheelRed = game.ScreenManager.Game.Content.Load<Model>("CogwheelRed");
            cogwheelWhite = game.ScreenManager.Game.Content.Load<Model>("CogwheelWhite");
            cogwheelBlue = game.ScreenManager.Game.Content.Load<Model>("CogwheelBlue");

            wrongMoveSound = new SoundPlayer(game.ScreenManager.Game, "error");
            transforms = new Matrix[cogwheel.Bones.Count];
            transformsRed = new Matrix[cogwheelRed.Bones.Count];
            transformsWhite = new Matrix[cogwheelWhite.Bones.Count];
            transformsBlue = new Matrix[cogwheelBlue.Bones.Count];
            cogwheel.CopyAbsoluteBoneTransformsTo(transforms);
            cogwheelRed.CopyAbsoluteBoneTransformsTo(transformsRed);
            cogwheelWhite.CopyAbsoluteBoneTransformsTo(transformsWhite);
            cogwheelBlue.CopyAbsoluteBoneTransformsTo(transformsBlue);
            base.LoadContent();
        }

        public BoardManager(GameplayScreen game)
            : base(game.ScreenManager.Game)
        {
            this.uiConnector = UIConnector.Instance;
            this.game = game;
            this.DrawOrder = 1000000;
            game.ScreenManager.Game.Components.Add(new Letters(game, this));

            world = Matrix.CreateScale(0.4f) * Matrix.Identity * Matrix.CreateTranslation(0f, 1.5f, 11f);
            worldRed = Matrix.CreateScale(0.3f) * Matrix.Identity * Matrix.CreateTranslation(0f, 2.5f, 13f);
            worldBlue = Matrix.CreateScale(0.5f) * Matrix.Identity * Matrix.CreateTranslation(1f, 2.5f, 9f);
            worldWhite = Matrix.CreateScale(0.2f) * Matrix.Identity * Matrix.CreateTranslation(1f, 1.7f, 13f);
            view = Matrix.CreateLookAt(new Vector3(1, 3, 17), new Vector3(0, 0, 0), Vector3.Up);
            projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45), 1.3f, 0.1f, 10000.0f);
        }

        public void UpdateMinMax()
        {
            MinX = Int32.MaxValue;
            MinY = Int32.MaxValue;
            MaxX = Int32.MinValue;
            MaxY = Int32.MinValue;

            List<Tile> tiles = BoardElements.OfType<Tile>().ToList();

            foreach (Tile be in tiles)
            {
                MinX = Math.Min((int)be.BoardX, MinX);
                MinY = Math.Min((int)be.BoardY, MinY);
                MaxX = Math.Max((int)be.BoardX, MaxX);
                MaxY = Math.Max((int)be.BoardY, MaxY);
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
            if (Mouse.GetState().RightButton == ButtonState.Pressed)
                rightMouseButtonPressed = true;
            if (Mouse.GetState().RightButton == ButtonState.Released && rightMouseButtonPressed)
            {
                rightMouseButtonPressed = false;
                //if from and to selected, then do undoMove, else do undo select
                if (selectedElementFrom != null && selectedElementTo != null)
                {
                    undoMove = true;
                }
                else
                {
                    selectedElementFrom = null;
                }
            }
            if (isBusy)
                return;
            uiConnector.GetBoard().CalculateMovableTiles();
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
            if (PossiblePlaces != null)
                foreach (BoardElement b in PossiblePlaces)
                    intersectList.Add(b);

            foreach (BoardElement boardElement in intersectList)
            {
                float? intersect = boardElement.Intersect(ray);
                if (intersect != null)
                {
                    if (smallestIntersect > intersect)
                    {
                        if (uiConnector.CurrentPlayerNumPieces() < 6 && boardElement is Tile && selectedElementFrom == null)
                        {
                        }
                        else if (boardElement.DefaultColor != Color.Red.ToVector3())
                        {
                            selected = boardElement;
                            smallestIntersect = intersect;
                        }
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
                        else
                            wrongMoveSound.PlaySound();
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
            {
                Thread thread = new Thread(new ThreadStart(this.DoMove));
                thread.Start();
            }

            UpdateMinMax();

            base.Update(gameTime);
        }

        public override void Draw(GameTime gameTime)
        {
            if (isGameEnded)
            {
                timeSpan = timeSpan.Subtract(new TimeSpan(0, 0, 0, 0, gameTime.ElapsedGameTime.Milliseconds));
                if (timeSpan.TotalMilliseconds > 0)
                {
                    spriteBatch.Begin();
                    SpriteFont sf = game.ScreenManager.Game.Content.Load<SpriteFont>("GameEndFont");

                    string winning = "";

                    if (uiConnector.GetCurrentPlayer().Equals("Player A (red)"))
                        winning = "You've won the game! :-)";
                    else
                        winning = "You've lost the game! :-(";

                    Vector2 sizeText = sf.MeasureString(winning);

                    int widthScreen = game.ScreenManager.Game.Window.ClientBounds.Width;
                    int heightScreen = game.ScreenManager.Game.Window.ClientBounds.Height;

                    float positionCenterX = (widthScreen / 2) - (sizeText.X / 2);
                    float positionCenterY = (heightScreen / 2) - (sizeText.Y / 2);

                    spriteBatch.DrawString(sf, winning, new Vector2(positionCenterX, positionCenterY), Color.White);
                    spriteBatch.End();
                }
                else
                {
                    isGameEnded = false;
                    timeSpan = new TimeSpan(0, 0, 0, 0);
                    ClearScreen();
                    this.StartGame(difficulty);
                }

                game.ScreenManager.ResetGraphicsDeviceSettings();
            }


            if (AICalculates)
            {
                foreach (ModelMesh mesh in cogwheel.Meshes)
                {
                    world = Matrix.CreateRotationZ(0.001f) * world;
                    foreach (BasicEffect effect in mesh.Effects)
                    {
                        effect.EnableDefaultLighting();
                        effect.Projection = projection;
                        effect.World = transforms[mesh.ParentBone.Index] * world;
                        effect.View = view;
                    }
                    mesh.Draw();
                }
                foreach (ModelMesh mesh in cogwheelRed.Meshes)
                {
                    worldRed = Matrix.CreateRotationZ(0.003f) * worldRed;
                    foreach (BasicEffect effect in mesh.Effects)
                    {
                        effect.EnableDefaultLighting();
                        effect.Projection = projection;
                        effect.World = transformsRed[mesh.ParentBone.Index] * worldRed;
                        effect.View = view;
                    }
                    mesh.Draw();
                }
                foreach (ModelMesh mesh in cogwheelBlue.Meshes)
                {
                    worldBlue = Matrix.CreateRotationZ(0.0016f) * worldBlue;
                    foreach (BasicEffect effect in mesh.Effects)
                    {
                        effect.EnableDefaultLighting();
                        effect.Projection = projection;
                        effect.World = transformsBlue[mesh.ParentBone.Index] * worldBlue;
                        effect.View = view;
                    }
                    mesh.Draw();
                }
                foreach (ModelMesh mesh in cogwheelWhite.Meshes)
                {
                    worldWhite = Matrix.CreateRotationZ(0.0016f) * worldWhite;
                    foreach (BasicEffect effect in mesh.Effects)
                    {
                        effect.EnableDefaultLighting();
                        effect.Projection = projection;
                        effect.World = transformsWhite[mesh.ParentBone.Index] * worldWhite;
                        effect.View = view;
                    }
                    mesh.Draw();
                }

                spriteBatch.Begin();
                SpriteFont sf = game.ScreenManager.Game.Content.Load<SpriteFont>("GameEndFont");

                string text = "The AI is thinking...";

                Vector2 sizeText = sf.MeasureString(text);

                int widthScreen = game.ScreenManager.Game.Window.ClientBounds.Width;
                int heightScreen = game.ScreenManager.Game.Window.ClientBounds.Height;

                float positionCenterX = (widthScreen / 2) - (sizeText.X / 2);
                float positionCenterY = (heightScreen / 2) - (sizeText.Y / 2);

                spriteBatch.DrawString(sf, text, new Vector2(positionCenterX, positionCenterY), Color.White);
                spriteBatch.End();
            }
            game.ScreenManager.ResetGraphicsDeviceSettings();

            base.Draw(gameTime);
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
                    movedPiece.Move((float)toXPiece, (float)toYPiece);
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
                    movedTile.Move((float)toXTile, (float)toYTile);
                    while (movedTile.AnimatedStarted) ;
                }
                if (movedPiece != null)
                {
                    if (newBoardSituation[(int)toXTile, (int)toYTile] == BoardPosition.RedTail)
                        movedPiece.HeadUp = false;
                    else
                        movedPiece.HeadUp = true;
                    movedPiece.Move((float)toXTile, (float)toYTile);
                    while (movedPiece.AnimatedStarted) ;
                }
            }
            else if (fromXPiece != null && fromYPiece != null && toXPiece != null && toYPiece != null)
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
                    movedPiece.Move((float)toXPiece, (float)toYPiece);
                    while (movedPiece.AnimatedStarted) ;
                }
            }
            else
            {
                if (!isGameEnded)
                    throw new Exception("This should not happen if the game is not ended!");
            }
        }

        public void DoMove()
        {
            isBusy = true;
            if (selectedElementFrom != null)
            {
                if (selectedElementFrom is Tile)
                {
                    foreach (BoardElement element in BoardElements)
                    {
                        if (element is Piece && element.BoardX == selectedElementFrom.BoardX && element.BoardY == selectedElementFrom.BoardY)
                            selectedElementFrom = element;
                    }
                }

                int numItems = uiConnector.CurrentPlayerNumPieces();
                if (numItems < 6 && selectedElementFrom.BoardY == 12.5f)
                {
                    FormPoint placePoint = new FormPoint((int)selectedElementTo.BoardX,
                                                                               (int)selectedElementTo.BoardY);
                    if (uiConnector.ValidatePlacePiece(placePoint))
                    {
                        Piece piece = (Piece)selectedElementFrom;
                        float oldBoardX = piece.BoardX;
                        float oldBoardY = piece.BoardY;

                        piece.Move(selectedElementTo.BoardX, selectedElementTo.BoardY);
                        while (piece.AnimatedStarted) ;

                        threadWaiting = true;
                        Thread.Sleep(1000);
                        if (undoMove)
                        {
                            piece.Move(oldBoardX, oldBoardY);
                            while (piece.AnimatedStarted) ;
                            selectedElementFrom = null;
                            selectedElementTo = null;
                            isBusy = false;
                            undoMove = false;
                            return;
                        }
                        //set to false, so no yellow will apear after 1 sec.
                        selectedElementFrom.IsSelected = false;
                        selectedElementFrom.IsMouseOver = false;
                        selectedElementTo.IsSelected = false;
                        selectedElementTo.IsMouseOver = false;
                        
                        AICalculates = true;
                        threadWaiting = false;
                        currentBoard = (BoardPosition[,])uiConnector.GetBoard().BoardSituation.Clone();
                        currentBoard[(int)selectedElementTo.BoardX, (int)selectedElementTo.BoardY] = BoardPosition.WhiteTail;
                        uiConnector.PlacePiece(placePoint);
                        BoardPosition[,] newBoardSituation = (BoardPosition[,])uiConnector.GetBoard().BoardSituation.Clone();

                        AICalculates = false;
                        DoAIMove(currentBoard, newBoardSituation);
                    }
                    else
                        wrongMoveSound.PlaySound();
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

                        float oldBoardX = selectedElementFrom.BoardX;
                        float oldBoardY = selectedElementFrom.BoardY;

                        selectedElementFrom.Move(selectedElementTo.BoardX, selectedElementTo.BoardY);
                        while (selectedElementFrom.AnimatedStarted) ;

                        threadWaiting = true;
                        Thread.Sleep(1000);
                        if (undoMove)
                        {
                            if (moveDistance == 2)
                                piece.HeadUp = !piece.HeadUp;
                            selectedElementFrom.Move(oldBoardX, oldBoardY);
                            while (selectedElementFrom.AnimatedStarted) ;
                            selectedElementFrom = null;
                            selectedElementTo = null;
                            isBusy = false;
                            undoMove = false;
                            return;
                        }

                        threadWaiting = false;
                        AICalculates = true;
                        uiConnector.MovePiece(fromPoint, toPoint);

                        BoardPosition[,] newBoardSituation = (BoardPosition[,])uiConnector.GetBoard().BoardSituation.Clone();
                        if (uiConnector.IsWon())
                        {
                            isGameEnded = true;
                            DoAIMove(currentBoard, newBoardSituation);
                            selectedElementFrom = null;
                            selectedElementTo = null;
                            AICalculates = false;
                            isBusy = false;
                            PlayWinningAnimation(uiConnector.GetCurrentPlayer());
                            return;
                        }

                        AICalculates = false;
                        DoAIMove(currentBoard, newBoardSituation);

                    }
                    else if (uiConnector.ValidateMoveTile(fromPoint, toPoint))
                    {
                        currentBoard = (BoardPosition[,])uiConnector.GetBoard().BoardSituation.Clone();
                        currentBoard[fromPoint.X, fromPoint.Y] = BoardPosition.Empty;
                        currentBoard[toPoint.X, toPoint.Y] = BoardPosition.Tile;

                        Tile tile = (Tile)selectedElementFrom;
                        float oldBoardX = tile.BoardX;
                        float oldBoardY = tile.BoardY;

                        tile.Move(toPoint.X, toPoint.Y);
                        while (tile.AnimatedStarted) ;
                        threadWaiting = true;
                        Thread.Sleep(1000);
                        if (undoMove)
                        {
                            tile.Move(oldBoardX, oldBoardY);
                            while (tile.AnimatedStarted) ;
                            selectedElementFrom = null;
                            selectedElementTo = null;
                            isBusy = false;
                            undoMove = false;
                            return;
                        }
                        threadWaiting = false;

                        uiConnector.MoveTile(fromPoint, toPoint);
                        BoardPosition[,] newBoardSituation = (BoardPosition[,])uiConnector.GetBoard().BoardSituation.Clone();
                    }
                    else
                        wrongMoveSound.PlaySound();
                }
            }
            selectedElementFrom = null;
            selectedElementTo = null;
            this.UpdateMinMax();
            isBusy = false;
        }


        private void PlayWinningAnimation(string currentPlayer)
        {
            timeSpan = new TimeSpan(0, 0, 0, 0, 10000);
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

            spriteBatch = new SpriteBatch(game.ScreenManager.Game.GraphicsDevice);
        }
    }
}
