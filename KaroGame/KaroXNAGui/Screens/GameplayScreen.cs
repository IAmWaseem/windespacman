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
        Matrix cameraView, topView, projection, world;

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
        bool enableDebug = true;

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
                _xAngle = value;
            }
        }

        // key pressed
        bool tPressed, rPressed, rotate, middleMousePressed, f1Pressed, f12Pressed;

        bool uPressed = false;
        bool lookAtTop = false;

        public static Board current { get; set; }
        private List<BoundingBox> BoundingBoxes = new List<BoundingBox>();

        // Maybe other location for this?
        public UIConnector UIConnector
        {
            get { return UIConnector.Instance; }
        }

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
            

            newBoard = UIConnector.Instance.GetBoard();
            UIConnector.Instance.MaxAIMoves(aiMoves);
            aiMoves++;
            current = newBoard;

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
            TransitionOnTime = TimeSpan.FromSeconds(1.5);
            TransitionOffTime = TimeSpan.FromSeconds(0.5);


            UIConnector.StartGame(
                new PlayerSettings()
                {
                    IsAI = true,
                    AlgorithmType = AlgorithmType.Random,
                    PlieDepth = 1,
                    DoTransTable = false,
                    DoMoveOrdering = false,
                    EvaluationFunction = EvaluationType.BetterOne
                },
                new PlayerSettings()
                {
                    IsAI = true,
                    AlgorithmType = AlgorithmType.AlphaBeta,
                    PlieDepth = 2,
                    DoTransTable = true,
                    DoMoveOrdering = true,
                    EvaluationFunction = EvaluationType.BetterOne
                });

            current = UIConnector.GetBoard();
            if (UIConnector.IsTwoAI())
                thread.Start();
        }

        public void Initialize()
        {
            cameraLocation = new Vector3(0, -10, 10);

            // framerate
            fc = new FramerateComponent(ScreenManager.Game);
            lc = new LoggerComponent(ScreenManager.Game);

            ScreenManager.Game.Components.Add(fc);
            ScreenManager.Game.Components.Add(lc);

            ScreenManager.Game.IsMouseVisible = true;
            tPressed = false;
            rotate = false;
            middleMousePressed = false;

            // init views
            topView = Matrix.CreateLookAt(new Vector3(0, 0, 10), new Vector3(0, 0, 0), Vector3.Up);

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

            world = Matrix.Identity;
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

            // once the load has finished, we use ResetElapsedTime to tell the game's
            // timing mechanism that we have just finished a very long frame, and that
            // it should not try to catch up.
            ScreenManager.Game.ResetElapsedTime();
        }


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

            lc.ClearLog();
            if (IsActive)
            {
                if (UIConnector.IsWon())
                {
                    thread.Abort();
                    current = UIConnector.GetBoard();
                }

                #region keypresses
                // Allows the game to exit
                if (Keyboard.GetState().IsKeyDown(Keys.Escape))
                {
                    if (thread.IsAlive)
                        thread.Abort();

                    // return to main menu
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
                    if (enableDebug)
                        enableDebug = false;
                    else
                        enableDebug = true;

                    f12Pressed = false;
                }

                // logger
                if (enableDebug)
                {
                    lc.Line("Debug information");
                    lc.Line();

                    lc.Line("FPS", fc.Framerate.ToString());
                    lc.Line("AI Calculates", calculating.ToString());
                    lc.Line();

                    lc.Line("X Rotation", RotationAngleX.ToString());
                    lc.Line("Z Rotation", angle.ToString());
                    lc.Line();
                    lc.Line("Zoom factor", zoom.ToString());
                    lc.Line();

                    lc.Line("Rotate", rotate.ToString());
                    lc.Line("Rotate up", rotateUp.ToString());
                    lc.Line("Remaining", totalAngle.ToString());
                    lc.Line();

                    lc.Line("Camera location");
                    lc.Line("X", cameraLocation.X.ToString());
                    lc.Line("Y", cameraLocation.Y.ToString());
                    lc.Line("Z", cameraLocation.Z.ToString());
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

        private void ResetGraphicsDeviceSettings()
        {
            ScreenManager.Game.GraphicsDevice.RenderState.DepthBufferEnable = true;
            ScreenManager.Game.GraphicsDevice.RenderState.AlphaBlendEnable = false;
            ScreenManager.Game.GraphicsDevice.RenderState.AlphaTestEnable = false;

            ScreenManager.Game.GraphicsDevice.SamplerStates[0].AddressU = TextureAddressMode.Wrap;
            ScreenManager.Game.GraphicsDevice.SamplerStates[0].AddressV = TextureAddressMode.Wrap;
            
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

            ResetGraphicsDeviceSettings();

            // tiles
            if (current != null)
            {
                foreach (ModelMesh m in tile.Meshes)
                {
                    for (int x = 0; x <= 20; x++)
                    {
                        for (int y = 0; y < 19; y++)
                        {
                            if (current.BoardSituation[x, y] != BoardPosition.Empty)
                            {
                                foreach (BasicEffect e in m.Effects)
                                {
                                    e.EnableDefaultLighting();
                                    e.PreferPerPixelLighting = true;

                                    e.View = View;
                                    e.Projection = projection;
                                    e.World = Matrix.CreateTranslation(x - 10, y - 9, 0) * world;

                                    //make boundingboxes
                                    BoundingBox meshBox = BoundingBox.CreateFromSphere(m.BoundingSphere);
                                    meshBox.Max = Vector3.Transform(meshBox.Max, Matrix.CreateScale(0.5f) * e.World);
                                    meshBox.Min = Vector3.Transform(meshBox.Min, Matrix.CreateScale(0.5f) * e.World);
                                    meshBox.Max.Z /= 2;
                                    meshBox.Min.Z /= 4;

                                    BoundingBoxes.Add(meshBox);

                                    Vector3 near = new Vector3(Mouse.GetState().X, Mouse.GetState().Y, 0);
                                    Vector3 far = new Vector3(Mouse.GetState().X, Mouse.GetState().Y, 1);

                                    near = ScreenManager.Game.GraphicsDevice.Viewport.Unproject(near, projection, View, Matrix.Identity);
                                    far = ScreenManager.Game.GraphicsDevice.Viewport.Unproject(far, projection, View, Matrix.Identity);

                                    Vector3 direction = Vector3.Subtract(far, near);
                                    direction.Normalize();

                                    Ray ray = new Ray(near, direction);
                                    float? intersect = ray.Intersects(meshBox);
                                    if (intersect != null)
                                    {
                                        e.DiffuseColor = Color.Red.ToVector3();
                                    }
                                    else
                                        e.DiffuseColor = Color.White.ToVector3();
                                }
                                m.Draw();

                                if (current.BoardSituation[x, y] == BoardPosition.RedHead || current.BoardSituation[x, y] == BoardPosition.RedTail)
                                {
                                    foreach (ModelMesh mesh in pieceRed.Meshes)
                                    {
                                        foreach (BasicEffect effect in mesh.Effects)
                                        {
                                            effect.EnableDefaultLighting();
                                            effect.PreferPerPixelLighting = true;
                                            effect.View = View;
                                            effect.Projection = projection;
                                            if (current.BoardSituation[x, y] == BoardPosition.RedTail)
                                            {
                                                effect.World = Matrix.CreateTranslation(x - 10, y - 9, 0) * world;
                                                effect.World = Matrix.CreateRotationX(MathHelper.ToRadians(180)) * effect.World;
                                                effect.World = Matrix.CreateTranslation(0, 0, -0.65f) * effect.World;
                                            }
                                            else
                                            {
                                                effect.World = Matrix.CreateTranslation(x - 10, y - 9, 0.15f) * world;
                                            }
                                            BoundingBox meshBox = BoundingBox.CreateFromSphere(mesh.BoundingSphere);
                                            meshBox.Max = Vector3.Transform(meshBox.Max, Matrix.CreateScale(0.7f) * effect.World);
                                            meshBox.Min = Vector3.Transform(meshBox.Min, Matrix.CreateScale(0.7f) * effect.World);

                                            BoundingBoxes.Add(meshBox);

                                            Vector3 near = new Vector3(Mouse.GetState().X, Mouse.GetState().Y, 0);
                                            Vector3 far = new Vector3(Mouse.GetState().X, Mouse.GetState().Y, 1);

                                            near = ScreenManager.Game.GraphicsDevice.Viewport.Unproject(near, projection, View, Matrix.Identity);
                                            far = ScreenManager.Game.GraphicsDevice.Viewport.Unproject(far, projection, View, Matrix.Identity);

                                            Vector3 direction = Vector3.Subtract(far, near);
                                            direction.Normalize();

                                            Ray ray = new Ray(near, direction);
                                            float? intersect = ray.Intersects(meshBox);
                                            if (intersect != null)
                                            {
                                                effect.DiffuseColor = Color.Orange.ToVector3();
                                            }
                                            else
                                                effect.DiffuseColor = Color.Red.ToVector3();
                                        }
                                        mesh.Draw();
                                    }
                                }

                                if (current.BoardSituation[x, y] == BoardPosition.WhiteHead || current.BoardSituation[x, y] == BoardPosition.WhiteTail)
                                {
                                    foreach (ModelMesh mesh in pieceWhite.Meshes)
                                    {
                                        foreach (BasicEffect effect in mesh.Effects)
                                        {
                                            effect.EnableDefaultLighting();
                                            effect.PreferPerPixelLighting = true;
                                            effect.View = View;
                                            effect.Projection = projection;
                                            if (current.BoardSituation[x, y] == BoardPosition.WhiteTail)
                                            {
                                                effect.World = Matrix.CreateTranslation(x - 10, y - 9, 0) * world;
                                                effect.World = Matrix.CreateRotationX(MathHelper.ToRadians(180)) * effect.World;
                                                effect.World = Matrix.CreateTranslation(0, 0, -0.65f) * effect.World;
                                            }
                                            else
                                            {
                                                effect.World = Matrix.CreateTranslation(x - 10, y - 9, 0.15f) * world;
                                            }
                                            BoundingBox meshBox = BoundingBox.CreateFromSphere(mesh.BoundingSphere);
                                            meshBox.Max = Vector3.Transform(meshBox.Max, Matrix.CreateScale(0.7f) * effect.World);
                                            meshBox.Min = Vector3.Transform(meshBox.Min, Matrix.CreateScale(0.7f) * effect.World);

                                            BoundingBoxes.Add(meshBox);

                                            Vector3 near = new Vector3(Mouse.GetState().X, Mouse.GetState().Y, 0);
                                            Vector3 far = new Vector3(Mouse.GetState().X, Mouse.GetState().Y, 1);

                                            near = ScreenManager.Game.GraphicsDevice.Viewport.Unproject(near, projection, View, Matrix.Identity);
                                            far = ScreenManager.Game.GraphicsDevice.Viewport.Unproject(far, projection, View, Matrix.Identity);

                                            Vector3 direction = Vector3.Subtract(far, near);
                                            direction.Normalize();

                                            Ray ray = new Ray(near, direction);
                                            float? intersect = ray.Intersects(meshBox);
                                            if (intersect != null)
                                            {
                                                effect.DiffuseColor = Color.Orange.ToVector3();
                                            }
                                            else
                                                effect.DiffuseColor = Color.White.ToVector3();
                                        }
                                        mesh.Draw();
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //draw start red pieces
            if (current.RedItems < 6)
            {
                foreach (ModelMesh mesh in pieceRed.Meshes)
                {
                    for (int i = 0; i < 6 - current.RedItems; i++)
                    {
                        foreach (BasicEffect effect in mesh.Effects)
                        {
                            effect.EnableDefaultLighting();
                            effect.PreferPerPixelLighting = true;
                            effect.View = View;
                            effect.Projection = projection;

                            effect.World = Matrix.CreateTranslation(-2.5f + i, -2, 0) * world;
                            effect.World = Matrix.CreateRotationX(MathHelper.ToRadians(180)) * effect.World;
                            effect.World = Matrix.CreateTranslation(0, 0, -0.65f) * effect.World;

                            BoundingBox meshBox = BoundingBox.CreateFromSphere(mesh.BoundingSphere);
                            meshBox.Max = Vector3.Transform(meshBox.Max, Matrix.CreateScale(0.7f) * effect.World);
                            meshBox.Min = Vector3.Transform(meshBox.Min, Matrix.CreateScale(0.7f) * effect.World);

                            BoundingBoxes.Add(meshBox);

                            Vector3 near = new Vector3(Mouse.GetState().X, Mouse.GetState().Y, 0);
                            Vector3 far = new Vector3(Mouse.GetState().X, Mouse.GetState().Y, 1);

                            near = ScreenManager.Game.GraphicsDevice.Viewport.Unproject(near, projection, View, Matrix.Identity);
                            far = ScreenManager.Game.GraphicsDevice.Viewport.Unproject(far, projection, View, Matrix.Identity);

                            Vector3 direction = Vector3.Subtract(far, near);
                            direction.Normalize();

                            Ray ray = new Ray(near, direction);
                            float? intersect = ray.Intersects(meshBox);
                            if (intersect != null)
                            {
                                effect.DiffuseColor = Color.Orange.ToVector3();
                            }
                            else
                                effect.DiffuseColor = Color.Red.ToVector3();
                        }
                        mesh.Draw();
                    }
                }

            }

            //draw start white pieces
            if (current.WhiteItems < 6)
            {
                foreach (ModelMesh mesh in pieceWhite.Meshes)
                {
                    for (int i = 0; i < 6 - current.WhiteItems; i++)
                    {
                        foreach (BasicEffect effect in mesh.Effects)
                        {
                            effect.EnableDefaultLighting();
                            effect.PreferPerPixelLighting = true;
                            effect.View = View;
                            effect.Projection = projection;

                            effect.World = Matrix.CreateTranslation(-2.5f + i, 3, 0) * world;
                            effect.World = Matrix.CreateRotationX(MathHelper.ToRadians(180)) * effect.World;
                            effect.World = Matrix.CreateTranslation(0, 0, -0.65f) * effect.World;

                            BoundingBox meshBox = BoundingBox.CreateFromSphere(mesh.BoundingSphere);
                            meshBox.Max = Vector3.Transform(meshBox.Max, Matrix.CreateScale(0.7f) * effect.World);
                            meshBox.Min = Vector3.Transform(meshBox.Min, Matrix.CreateScale(0.7f) * effect.World);

                            BoundingBoxes.Add(meshBox);

                            Vector3 near = new Vector3(Mouse.GetState().X, Mouse.GetState().Y, 0);
                            Vector3 far = new Vector3(Mouse.GetState().X, Mouse.GetState().Y, 1);

                            near = ScreenManager.Game.GraphicsDevice.Viewport.Unproject(near, projection, View, Matrix.Identity);
                            far = ScreenManager.Game.GraphicsDevice.Viewport.Unproject(far, projection, View, Matrix.Identity);

                            Vector3 direction = Vector3.Subtract(far, near);
                            direction.Normalize();

                            Ray ray = new Ray(near, direction);
                            float? intersect = ray.Intersects(meshBox);
                            if (intersect != null)
                            {
                                effect.DiffuseColor = Color.Orange.ToVector3();
                            }
                            else
                                effect.DiffuseColor = Color.White.ToVector3();
                        }
                        mesh.Draw();
                    }
                }
            }

            if (enableDebug)
            {
                foreach (BoundingBox boundingBox in BoundingBoxes)
                {
                    DrawBoundingBox.Draw(ScreenManager.Game.GraphicsDevice, boundingBox, View, projection);
                }
            }

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
