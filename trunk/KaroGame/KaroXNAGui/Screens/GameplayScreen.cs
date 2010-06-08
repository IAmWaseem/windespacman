#region File Description
//-----------------------------------------------------------------------------
// GameplayScreen.cs
//
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#endregion

#region Using Statements
using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;
using Karo;
using GameStateManagement;
using System.Threading;
using Karo.Gui;
#endregion

namespace GameStateManagement
{
    /// <summary>
    /// This screen implements the actual game logic. It is just a
    /// placeholder to get the idea across: you'll probably want to
    /// put some more interesting gameplay in here!
    /// </summary>
    class GameplayScreen : GameScreen
    {
        #region Fields

        ContentManager content;
        SpriteFont gameFont;

        // non-default
        Vector3 cameraLocation;
        FramerateComponent fc;
        LoggerComponent lc;
        //GraphicsDeviceManager graphics;

        //background
        SpriteBatch backgroundBatch, spriteBatch;
        Texture2D background;

        // game models
        Model tile, pieceRed, pieceWhite;
        Matrix cameraView, topView, projection;
        private Matrix world, newworld;
        private float moveTime;
        private const float animationTime = 3.0f;
        public bool ShowTargetPlaces { get; set; }



        public Matrix World
        {
            get
            {
                return world;
            }
        }

        public Matrix Projection
        {
            get { return projection; }
        }

        public Matrix View
        {
            get
            {
                if (lookAtTop)
                    return topView;
                else
                    return cameraView;
            }
        }

        // zoom members
        float zoom = 1f;
        float zoomFactor = 0.02f;

        //rotation members
        bool rotateUp = false;
        public bool EnableDebug { get; set; }

        float angle, totalAngle;

        float _xAngle = 45f;
        /// <summary>
        /// Get's and sets the rotation angle
        /// </summary>
        public float RotationAngleX
        {
            get { return _xAngle; }
            set
            {
                if (value < 0)
                    value = 360 + value;
                value = value % 360;

                if (value >= 315)
                {
                    // ok
                }
                else if (value <= 44.9f)
                {
                    // ok
                }
                else if( value < 315f && value > 60f)
                {
                    value = 315f;
                }
                else if (value > 44.9f)
                {
                    value = 44.9f;
                }


                _xAngle = value;
            }
        }

        // key pressed
        bool tPressed, rPressed, rotate, middleMousePressed, f1Pressed, f12Pressed;

        private static bool boardAnimating = false;
        private static bool pieceAnimating = false;
        private static bool tileAnimating = false;

        bool uPressed = false;
        bool lookAtTop = false;

        public static Board current { get; set; }
        private List<BoundingBox> BoundingBoxes = new List<BoundingBox>();

        // Maybe other location for this?
        public UIConnector UIConnector
        {
            get { return UIConnector.Instance; }
        }
        private static BoardManager manager;
        #endregion

        #region Initialization

        Thread thread = new Thread(new ThreadStart(updateBoard));
        static int aiMoves = 1;
        static bool calculating = false;
        static Board newBoard;
        public static void updateBoard()
        {
            // set calculation to true
            calculating = true;
            Thread.Sleep(50);
            while (boardAnimating || tileAnimating || pieceAnimating)
            {
                Thread.Sleep(50);
            }

            newBoard = UIConnector.Instance.GetBoard();
            UIConnector.Instance.MaxAIMoves(aiMoves);
            aiMoves++;
            manager.currentBoard = newBoard.BoardSituation;
            manager.redItems = newBoard.RedItems;
            manager.whiteItems = newBoard.WhiteItems;
            manager.SetupBoard();

            // set calculation to false;
            calculating = false;

            Thread.Sleep(1450);
            updateBoard();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        public GameplayScreen()
        {
            EnableDebug = true;
            TransitionOnTime = TimeSpan.FromSeconds(1.5);
            TransitionOffTime = TimeSpan.FromSeconds(0.5);
        }

        public void Initialize()
        {
            cameraLocation = new Vector3(0, -10, 10);

            // framerate
            fc = new FramerateComponent(ScreenManager.Game);
            lc = new LoggerComponent(ScreenManager.Game);

            ScreenManager.Game.Components.Add(fc);
            ScreenManager.Game.Components.Add(lc);

            tPressed = false;
            rotate = false;
            middleMousePressed = false;

            // init views
            topView = Matrix.CreateLookAt(new Vector3(0, 0, 10), new Vector3(0, 0, 0), Vector3.Down);

            Vector3 loc = new Vector3(0, -10, 10);
            Matrix trans = Matrix.Identity;
            RotationAngleX = 0;
            trans *= Matrix.CreateRotationX(MathHelper.ToRadians(RotationAngleX));
            trans *= Matrix.CreateRotationZ(MathHelper.ToRadians(angle));
            trans *= Matrix.CreateScale(zoom);
            cameraLocation = Vector3.Transform(loc, trans);
            cameraView = Matrix.CreateLookAt(cameraLocation, new Vector3(0, 0, 0), Vector3.UnitZ);

            projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45f),
                ((float)ScreenManager.Game.GraphicsDevice.Viewport.Width / (float)ScreenManager.Game.GraphicsDevice.Viewport.Height), 0.1f, 100.0f);

            world = Matrix.CreateTranslation(-10, -9.5f, 0f);
        }


        /// <summary>
        /// Load graphics content for the game.
        /// </summary>
        public override void LoadContent()
        {
            Initialize();

            if (content == null)
                content = new ContentManager(ScreenManager.Game.Services, "Content");

            gameFont = content.Load<SpriteFont>("FPSFont");
            spriteBatch = new SpriteBatch(ScreenManager.Game.GraphicsDevice);
            backgroundBatch = new SpriteBatch(ScreenManager.Game.GraphicsDevice);
            background = ScreenManager.Game.Content.Load<Texture2D>("GameBackground");
            tile = ScreenManager.Game.Content.Load<Model>("tile");
            pieceRed = ScreenManager.Game.Content.Load<Model>("pawnred");
            pieceWhite = ScreenManager.Game.Content.Load<Model>("pawnwhite");


            manager = new BoardManager(this);
            manager.StartGame(Difficulty.Easy);
            ScreenManager.Game.Components.Add(manager);
            if (UIConnector.IsTwoAI())
                thread.Start();

            // once the load has finished, we use ResetElapsedTime to tell the game's
            // timing mechanism that we have just finished a very long frame, and that
            // it should not try to catch up.
            ScreenManager.Game.ResetElapsedTime();
        }

        public Model Tile { get { return tile; } }
        public Model PieceRed { get { return pieceRed; } }
        public Model PieceWhite { get { return pieceWhite; } }

        /// <summary>
        /// Unload graphics content used by the game.
        /// </summary>
        public override void UnloadContent()
        {
            content.Unload();
        }


        #endregion

        #region Update and Draw


        /// <summary>
        /// Updates the state of the game. This method checks the GameScreen.IsActive
        /// property, so the game will stop updating when the pause menu is active,
        /// or if you tab away to a different application.
        /// </summary>
        public override void Update(GameTime gameTime, bool otherScreenHasFocus,
                                                       bool coveredByOtherScreen)
        {
            base.Update(gameTime, otherScreenHasFocus, coveredByOtherScreen);
            ScreenManager.Game.IsMouseVisible = false;
            if (manager.FromTileSelected)
                ShowTargetPlaces = true;
            else
                ShowTargetPlaces = false;

            lc.ClearLog();
            if (!IsActive)
            {
                if (thread.IsAlive)
                {
                    thread.Suspend();
                }
            }
            if (IsActive)
            {
                ScreenManager.Game.IsMouseVisible = true;
                if (UIConnector.IsWon())
                {
                    if (thread.ThreadState == ThreadState.Running)
                    {
                        thread.Abort();
                        manager.currentBoard = UIConnector.GetBoard().BoardSituation;
                        manager.SetupBoard();
                    }
                }

                #region keypresses
                // Allows the game to exit
                if (thread.ThreadState == ThreadState.Suspended)
                {
                    thread.Resume();
                }
                // top view
                if (Keyboard.GetState().IsKeyDown(Keys.T))
                    tPressed = true;

                if (Keyboard.GetState().IsKeyUp(Keys.T))
                {
                    if (tPressed)
                    {
                        if (lookAtTop)
                            lookAtTop = false;
                        else
                            lookAtTop = true;
                    }
                    tPressed = false;
                }

                if (Mouse.GetState().MiddleButton == ButtonState.Pressed)
                    middleMousePressed = true;

                if (Mouse.GetState().MiddleButton == ButtonState.Released)
                {
                    if (middleMousePressed)
                    {
                        rotate = true;
                    }
                    middleMousePressed = false;
                }

                // enter or leave fullscreen
                if (Keyboard.GetState().IsKeyDown(Keys.F1))
                    f1Pressed = true;

                if (Keyboard.GetState().IsKeyUp(Keys.F1))
                {
                    if (f1Pressed)
                    {
                        if (ScreenManager.Graphics.IsFullScreen)
                        {
                            ScreenManager.Graphics.IsFullScreen = false;
                            ScreenManager.Graphics.PreferredBackBufferWidth = 800;
                            ScreenManager.Graphics.PreferredBackBufferHeight = 600;
                        }
                        else
                        {
                            ScreenManager.Graphics.IsFullScreen = true;
                            ScreenManager.Graphics.PreferredBackBufferWidth = 1280;
                            ScreenManager.Graphics.PreferredBackBufferHeight = 800;
                        }

                        // apply changes
                        ScreenManager.Graphics.ApplyChanges();

                        // reset projection
                        projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45f),
                            ((float)ScreenManager.Game.GraphicsDevice.Viewport.Width / (float)ScreenManager.Game.GraphicsDevice.Viewport.Height), 0.1f, 100.0f);
                    }
                    f1Pressed = false;
                }

                #endregion

                #region rotate
                float percentage = ((float)gameTime.ElapsedGameTime.Milliseconds / 1000f);
                float rotateAngle = 60f * percentage;
                float rotateAngleX = rotateAngle;

                // rotate
                if (Mouse.GetState().MiddleButton == ButtonState.Pressed)
                {
                    middleMousePressed = true;
                }
                if (Mouse.GetState().MiddleButton == ButtonState.Released && middleMousePressed)
                {
                    rotate = true;
                    if (angle == 0.0f)
                    {
                        rotateUp = true;
                        totalAngle = 180;
                    }
                    else if (angle == 180.0f)
                    {
                        rotateUp = false;
                        totalAngle = 180;
                    }
                    else if (angle < 180)
                    {
                        rotateUp = false;
                        totalAngle = angle;
                        if (totalAngle < 0.0f)
                            totalAngle = 360 + angle;
                    }
                    else if (angle > 180)
                    {
                        rotateUp = true;
                        totalAngle = angle - 180;
                    }
                    middleMousePressed = false;
                }
                if (Keyboard.GetState().IsKeyDown(Keys.R))
                    rPressed = true;

                if (Keyboard.GetState().IsKeyUp(Keys.R) && rPressed)
                {
                    rotate = true;
                    if (angle == 0.0f)
                    {
                        rotateUp = true;
                        totalAngle = 180;
                    }
                    else if (angle == 180.0f)
                    {
                        rotateUp = false;
                        totalAngle = 180;
                    }
                    else if (angle < 180)
                    {
                        rotateUp = false;
                        totalAngle = angle;
                        if (totalAngle < 0.0f)
                            totalAngle = 360 + angle;
                    }
                    else if (angle > 180)
                    {
                        rotateUp = true;
                        totalAngle = angle - 180;
                    }

                    rPressed = false;
                }

                // rotate with 'r'
                if (rotate)
                {
                    if (rotateUp)
                    {
                        rotateAngle *= -1;
                        totalAngle += rotateAngle;
                        angle += rotateAngle;

                        if (angle < 0)
                            angle = 360 + angle;

                        if (totalAngle <= 0)
                        {
                            rotate = false;
                            angle = 180;
                        }
                    }
                    else
                    {
                        rotateAngle *= -1;
                        totalAngle += rotateAngle;
                        angle += rotateAngle;

                        if (angle < 0)
                            angle = 360 + angle;

                        if (totalAngle <= 0)
                        {
                            rotate = false;
                            angle = 0;
                        }
                    }
                }

                if (!lookAtTop)
                {
                    // rotate with left key
                    if (Keyboard.GetState().IsKeyDown(Keys.Left))
                    {
                        rotate = false;
                        angle += rotateAngle;
                        if (angle > 360)
                            angle = 360 - angle;
                    }

                    // rotate with right key
                    if (Keyboard.GetState().IsKeyDown(Keys.Right))
                    {
                        rotate = false;
                        angle -= rotateAngle;
                        if (angle < 0)
                            angle = 360 + angle;
                    }

                    // rotate with  up key
                    if (Keyboard.GetState().IsKeyDown(Keys.Up))
                    {
                        RotationAngleX += rotateAngle;
                    }

                    // rotate with down key
                    if (Keyboard.GetState().IsKeyDown(Keys.Down))
                    {
                        rotateAngle = rotateAngle * -1;
                        RotationAngleX += rotateAngle;
                    }

                    // zoom out
                    if (Keyboard.GetState().IsKeyDown(Keys.PageUp))
                    {
                        if (zoom > 0.05f)
                            zoom -= zoomFactor;
                    }
                    // zoom in
                    if (Keyboard.GetState().IsKeyDown(Keys.PageDown))
                    {
                        if (zoom < 2.5f)
                            zoom += zoomFactor;
                    }
                }
                #endregion

                // set camera view
                Vector3 loc = new Vector3(0, 10, 10);
                Matrix trans = Matrix.Identity;
                trans *= Matrix.CreateRotationX(MathHelper.ToRadians(RotationAngleX));
                trans *= Matrix.CreateRotationZ(MathHelper.ToRadians(angle));
                trans *= Matrix.CreateScale(zoom);
                cameraLocation = Vector3.Transform(loc, trans);
                cameraView = Matrix.CreateLookAt(cameraLocation, new Vector3(0, 0, 0), Vector3.UnitZ);

                if (Keyboard.GetState().IsKeyDown(Keys.F12))
                    f12Pressed = true;

                if (Keyboard.GetState().IsKeyUp(Keys.F12) && f12Pressed)
                {
                    if (EnableDebug)
                        EnableDebug = false;
                    else
                        EnableDebug = true;

                    f12Pressed = false;
                }

                float middleX = ((float)manager.MaxX + (float)manager.MinX) / 2f;
                float middleY = ((float)manager.MaxY + (float)manager.MinY) / 2f;
                newworld = Matrix.CreateTranslation(-1 * middleX, -1 * middleY, 0);

                if (newworld != world && boardAnimating == false)
                {
                    boardAnimating = true;
                    moveTime = animationTime;
                }

                if (boardAnimating)
                {
                    bool wanttomove = true;
                    float xMove = newworld.M41 - world.M41;
                    float yMove = newworld.M42 - world.M42;
                    float time = (float)gameTime.ElapsedGameTime.Milliseconds / 1000f;

                    moveTime -= time;
                    
                    float xMovement = (time / moveTime) * xMove * animationTime;
                    float yMovement = (time / moveTime) * yMove * animationTime;

                    world *= Matrix.CreateTranslation(xMovement, yMovement, 0);

                    if (newworld == world || moveTime <= -0.5f || !wanttomove)
                    {
                        world = newworld;
                        boardAnimating = false;
                    }
                }


                int max = Math.Max(manager.BoardWidth, manager.BoardHeight);

                float autozoom =(float)max / 6f;
                Vector3 loca = new Vector3(0, 0, 10);
                loca = Vector3.Transform(loca, Matrix.CreateScale(autozoom));
                topView = Matrix.CreateLookAt(loca, new Vector3(0, 0, 0), Vector3.Down);
                manager.ZRotation = angle;
                manager.XRotation = RotationAngleX;
                
                // logger
                if (EnableDebug)
                {
                    lc.Line("Debug information");
                    lc.Line();

                    lc.Line("FPS", fc.Framerate.ToString());
                    lc.Line("AI Calculates", calculating.ToString());
                    lc.Line("Multisample type", ScreenManager.GraphicsDevice.PresentationParameters.MultiSampleType.ToString());
                    lc.Line();

                    lc.Line("Animating");
                    lc.Line("Board", boardAnimating.ToString());
                    lc.Line("Piece", pieceAnimating.ToString());
                    lc.Line("Tile", tileAnimating.ToString());
                    lc.Line();

                    lc.Line("Rotation and zoom");
                    lc.Line("X Rotation", RotationAngleX.ToString());
                    lc.Line("Z Rotation", angle.ToString());
                    lc.Line("Zoom factor", zoom.ToString());
                    lc.Line();

                    lc.Line("Auto rotate", rotate.ToString());
                    lc.Line("Remaining", totalAngle.ToString());
                    lc.Line();

                    lc.Line("Camera location");
                    lc.Line("X", cameraLocation.X.ToString());
                    lc.Line("Y", cameraLocation.Y.ToString());
                    lc.Line("Z", cameraLocation.Z.ToString());
                    lc.Line();

                    lc.Line("Tile");
                    lc.Line("Min X", manager.MinX.ToString("0"));
                    lc.Line("Max X", manager.MaxX.ToString("0"));
                    lc.Line("Min Y", manager.MinY.ToString("0"));
                    lc.Line("Max Y", manager.MaxY.ToString("0"));
                    lc.Line("Width", manager.BoardWidth.ToString());
                    lc.Line("Height", manager.BoardHeight.ToString());
                    lc.Line("Autozoom factor", autozoom.ToString("0.00"));
                    lc.Line("BoardElements count", manager.BoardElements.Count.ToString("0.00"));
                }
            }
        }


        /// <summary>
        /// Lets the game respond to player input. Unlike the Update method,
        /// this will only be called when the gameplay screen is active.
        /// </summary>
        public override void HandleInput(InputState input)
        {
            if (input == null)
                throw new ArgumentNullException("input");

            if (input.IsPauseGame(ControllingPlayer))
            {
                ScreenManager.AddScreen(new PauseMenuScreen(), ControllingPlayer);
            }
            else
            {
                                
            }
        }

        /// <summary>
        /// Draws the gameplay screen.
        /// </summary>
        public override void Draw(GameTime gameTime)
        {
            // This game has a blue background. Why? Because!
            ScreenManager.GraphicsDevice.Clear(ClearOptions.Target,
                                               Color.CornflowerBlue, 0, 0);

            // Our player and enemy are both actually just text strings.
            BoundingBoxes = new List<BoundingBox>();

            // background
            backgroundBatch.Begin(SpriteBlendMode.None);
            DrawBackground(backgroundBatch);
            backgroundBatch.End();

            ScreenManager.ResetGraphicsDeviceSettings();

            // If the game is transitioning on or off, fade it out to black.
            if (TransitionPosition > 0)
                ScreenManager.FadeBackBufferToBlack(255 - TransitionAlpha);
        }

        private void DrawBackground(SpriteBatch Batch)
        {
            // Center the sprite on the center of the screen.
            Vector2 origin = new Vector2(ScreenManager.Game.GraphicsDevice.Viewport.Width / 2 - (ScreenManager.Game.GraphicsDevice.Viewport.Height / 2), 0);
            Batch.Draw(background, Vector2.Zero, null,
                Color.White, 0, origin, 1, SpriteEffects.None, 0.99999f);
        }


        #endregion
    }
}
