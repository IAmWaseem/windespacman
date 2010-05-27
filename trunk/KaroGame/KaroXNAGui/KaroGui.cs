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
using System.Threading;

namespace Karo.Gui
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class KaroGui : Microsoft.Xna.Framework.Game
    {
        Vector3 cameraLocation;
        //default members
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;

        FramerateComponent fc;
        LoggerComponent lc;

        //background
        SpriteBatch backgroundBatch;
        Texture2D background;

        // game models
        Model tile, pieceRed, pieceWhite;
        Matrix cameraView, topView, projection, world;

        Matrix view
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

        private Board current;
        private List<BoundingBox> BoundingBoxes = new List<BoundingBox>();

        // Maybe other location for this?
        public UIConnector UIConnector
        {
            get { return UIConnector.Instance; }
        }

        public KaroGui()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";

            UIConnector.StartGame(new PlayerSettings() { IsAI = false, AlgorithmType = AlgorithmType.Random, DoMoveOrdering = false, DoTransTable = false, EvaluationFunction = EvaluationType.BetterOne, PlieDepth = 2 }, new PlayerSettings() { IsAI = true, AlgorithmType = AlgorithmType.AlphaBeta, PlieDepth = 2, EvaluationFunction = EvaluationType.BetterOne, DoTransTable = true, DoMoveOrdering = true });
            UIConnector.MaxAIMoves(100);
            current = UIConnector.GetBoard();
            current.BoardSituation[11, 10] = BoardPosition.Empty;
            cameraLocation = new Vector3(0, -10, 10);
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            // TODO: Add your initialization logic here
            graphics.PreferredBackBufferWidth = 800;
            graphics.PreferredBackBufferHeight = 600;
            graphics.ApplyChanges();

            // framerate
            fc = new FramerateComponent(this);
            lc = new LoggerComponent(this);

            this.Components.Add(fc);
            this.Components.Add(lc);

            IsMouseVisible = true;
            tPressed = false;
            rotate = false;
            middleMousePressed = false;

            // init views
            topView = Matrix.CreateLookAt(new Vector3(0, 0, 10), new Vector3(0, 0, 0), Vector3.Up);

            Vector3 loc = new Vector3(0, -10, 10);
            Matrix trans = Matrix.Identity;
            //trans *= Matrix.CreateRotationX(MathHelper.ToRadians(RotationAngleX));
            //trans *= Matrix.CreateRotationZ(MathHelper.ToRadians(angle));
            //trans *= Matrix.CreateScale(zoom);
            cameraLocation = Vector3.Transform(loc, trans);
            cameraView = Matrix.CreateLookAt(cameraLocation, new Vector3(0, 0, 0), Vector3.UnitZ);

            projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45f),
                ((float)GraphicsDevice.Viewport.Width / (float)GraphicsDevice.Viewport.Height), 0.1f, 100.0f);

            world = Matrix.Identity;

            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);
            backgroundBatch = new SpriteBatch(GraphicsDevice);
            background = Content.Load<Texture2D>("pdc08-1600x1200");
            tile = Content.Load<Model>("tile");
            pieceRed = Content.Load<Model>("pawnred");
            pieceWhite = Content.Load<Model>("pawnwhite");

            // TODO: use this.Content to load your game content here
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }


        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            #region keypresses
            // Allows the game to exit
            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
                this.Exit();

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
                    if (graphics.IsFullScreen)
                    {
                        graphics.IsFullScreen = false;
                        graphics.PreferredBackBufferWidth = 800;
                        graphics.PreferredBackBufferHeight = 600;
                    }
                    else
                    {
                        graphics.IsFullScreen = true;
                        graphics.PreferredBackBufferWidth = 1280;
                        graphics.PreferredBackBufferHeight = 800;
                    }

                    // apply changes
                    graphics.ApplyChanges();

                    // reset projection
                    projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45f),
                        ((float)GraphicsDevice.Viewport.Width / (float)GraphicsDevice.Viewport.Height), 0.1f, 100.0f);
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

                if (angle >= 180)
                {
                    rotateUp = true;
                    totalAngle = 180;
                }
                else
                {
                    rotateUp = true;
                    totalAngle = 180;
                }

                rPressed = false;
            }

            // rotate with 'r'
            if (rotate)
            {
                if (rotateUp)
                {
                    rotate = false;
                }
                else
                {
                    rotateAngle *= -1;
                    totalAngle += rotateAngle;
                    angle += rotateAngle;

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

            if (Keyboard.GetState().IsKeyDown(Keys.U))
                uPressed = true;

            if (Keyboard.GetState().IsKeyUp(Keys.U) && uPressed)
            {
                current = UIConnector.GetBoard();
                uPressed = false;
            }

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
            lc.ClearLog();

            if (enableDebug)
            {
                lc.Line("Debug information");
                lc.Line();

                lc.Line("FPS", fc.Framerate.ToString());
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

            base.Update(gameTime);
        }

        private void ResetGraphicsDeviceSettings()
        {
            GraphicsDevice.RenderState.DepthBufferEnable = true;
            GraphicsDevice.RenderState.AlphaBlendEnable = false;
            GraphicsDevice.RenderState.AlphaTestEnable = false;

            GraphicsDevice.SamplerStates[0].AddressU = TextureAddressMode.Wrap;
            GraphicsDevice.SamplerStates[0].AddressV = TextureAddressMode.Wrap;
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            // clear screen
            GraphicsDevice.Clear(Color.CornflowerBlue);

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

                                    e.View = view;
                                    e.Projection = projection;
                                    e.World = Matrix.CreateTranslation(x - 10, y - 9, 0) * world;

                                    //make boundingboxes
                                    BoundingBox meshBox = BoundingBox.CreateFromSphere(m.BoundingSphere);
                                    meshBox.Max = Vector3.Transform(meshBox.Max, Matrix.CreateScale(0.5f) * e.World);
                                    meshBox.Min = Vector3.Transform(meshBox.Min, Matrix.CreateScale(0.5f) * e.World);
                                    meshBox.Max.Z /= 2;
                                    meshBox.Min.Z /= 4;
                                    if (BoundingBoxes.Count < 20)
                                    {
                                        BoundingBoxes.Add(meshBox);
                                    }

                                    Vector3 near = new Vector3(Mouse.GetState().X, Mouse.GetState().Y, 0);
                                    Vector3 far = new Vector3(Mouse.GetState().X, Mouse.GetState().Y, 1);

                                    near = GraphicsDevice.Viewport.Unproject(near, projection, view, Matrix.Identity);
                                    far = GraphicsDevice.Viewport.Unproject(far, projection, view, Matrix.Identity);

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

                                if (current.BoardSituation[x, y] == BoardPosition.RedHead || UIConnector.GetBoard().BoardSituation[x, y] == BoardPosition.RedTail)
                                {
                                    foreach (ModelMesh mesh in pieceRed.Meshes)
                                    {
                                        foreach (BasicEffect effect in mesh.Effects)
                                        {
                                            effect.EnableDefaultLighting();
                                            effect.PreferPerPixelLighting = true;
                                            effect.View = view;
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
                                        }
                                        mesh.Draw();
                                    }
                                }

                                if (current.BoardSituation[x, y] == BoardPosition.WhiteHead || UIConnector.GetBoard().BoardSituation[x, y] == BoardPosition.WhiteTail)
                                {
                                    foreach (ModelMesh mesh in pieceWhite.Meshes)
                                    {
                                        foreach (BasicEffect effect in mesh.Effects)
                                        {
                                            effect.EnableDefaultLighting();
                                            effect.PreferPerPixelLighting = true;
                                            effect.View = view;
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
                                        }
                                        mesh.Draw();
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (enableDebug)
            {
                foreach (BoundingBox boundingBox in BoundingBoxes)
                {
                    DrawBoundingBox.Draw(GraphicsDevice, boundingBox, view, projection);
                }
            }

            base.Draw(gameTime);
        }

        private void DrawBackground(SpriteBatch Batch)
        {
            // Center the sprite on the center of the screen.
            Vector2 origin = new Vector2(GraphicsDevice.Viewport.Width / 2 - (GraphicsDevice.Viewport.Height / 2), 0);
            Batch.Draw(background, Vector2.Zero, null,
                Color.White, 0, origin, 1, SpriteEffects.None, 0.99999f);
        }

    }
}
