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

namespace Karo.Gui
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class KaroGui : Microsoft.Xna.Framework.Game
    {
        //default members
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        FramerateComponent fc;
        TextPrinterComponent tpc;

        //background
        SpriteBatch backgroundBatch;
        Texture2D background;

        // game models
        Model tile, piece;
        Matrix view, cameraView, topView, projection, world;

        // zoom members
        float zoom = 1f;
        float zoomFactor = 0.02f;

        //rotation members
        bool rotateUp = true;

        float _angle, _angleBefore;
        float _xAngle = 45f;

        /// <summary>
        /// Get's and sets the rotation angle
        /// </summary>
        public float RotationAngleZ
        {
            get { return _angle; }
            set
            {
                if (value < 0)
                    value = 360 + value;
                value = value % 360;
                _angle = value;
            }
        }

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
        bool tPressed, rPressed, rotate, middleMousePressed, f1Pressed;

        // Maybe other location for this?
        public UIConnector UIConnector
        {
            get { return UIConnector.Instance; }
        }

        public KaroGui()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
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
            tpc = new TextPrinterComponent(this, Color.White);
            this.Components.Add(fc);
            this.Components.Add(tpc);

            IsMouseVisible = true;
            tPressed = false;
            rotate = false;
            middleMousePressed = false;

            // init views
            view = Matrix.CreateLookAt(new Vector3(0, -10, 10), new Vector3(0, 0, 0), Vector3.Up);
            topView = Matrix.CreateLookAt(new Vector3(0, 0, 10), new Vector3(0, 0, 0), Vector3.Up);
            cameraView = Matrix.CreateLookAt(new Vector3(0, -10, 10), new Vector3(0, 0, 0), Vector3.Up);

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

            if (Keyboard.GetState().IsKeyDown(Keys.T))
                tPressed = true;

            if (Keyboard.GetState().IsKeyUp(Keys.T))
            {
                if (tPressed)
                {
                    if (view == topView)
                        view = cameraView;
                    else
                        view = topView;
                }
                tPressed = false;
            }

            if (Keyboard.GetState().IsKeyDown(Keys.R))
                rPressed = true;

            if (Keyboard.GetState().IsKeyUp(Keys.R))
            {
                if (rPressed)
                {
                    rotate = true;
                    _angleBefore = RotationAngleZ;
                }
                rPressed = false;
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
            #endregion

            #region rotate
            float percentage = ((float)gameTime.ElapsedGameTime.Milliseconds / 1000f);
            float rotateAngle = 60f * percentage;
            float rotateAngleX = rotateAngle;

            if (!rotateUp)
                rotateAngle *= -1;

            // rotate with 'r'
            if (rotate)
            {
                RotationAngleZ += rotateAngle;

                if (RotationAngleZ > 180 || RotationAngleZ < 0)
                {
                    if (rotateUp)
                        rotateAngle = RotationAngleZ - 180;
                    else
                        rotateAngle = 360 - RotationAngleZ;

                    if (!rotateUp)
                        RotationAngleZ = 0;
                    else
                        RotationAngleZ = 180;

                    // switch
                    rotate = false;

                    if (rotateUp)
                        rotateUp = false;
                    else
                        rotateUp = true;
                }

                world *= Matrix.CreateRotationZ(MathHelper.ToRadians(rotateAngle));
            }

            // rotate with keys
            if (Keyboard.GetState().IsKeyDown(Keys.Left))
            {
                rotate = false;
                RotationAngleZ += rotateAngle;

                world *= Matrix.CreateRotationZ(MathHelper.ToRadians(rotateAngle));
            }

            // rotate with keys
            if (Keyboard.GetState().IsKeyDown(Keys.Right))
            {
                rotate = false;
                rotateAngle *= -1;
                RotationAngleZ += rotateAngle;

                world *= Matrix.CreateRotationZ(MathHelper.ToRadians(rotateAngle));
            }

            // rotate with keys
            if (Keyboard.GetState().IsKeyDown(Keys.Up))
            {
                RotationAngleX += rotateAngle;

                world *= Matrix.CreateRotationX(MathHelper.ToRadians(rotateAngleX));

            }

            // rotate with keys
            if (Keyboard.GetState().IsKeyDown(Keys.Down))
            {

                rotateAngleX *= -1;
                RotationAngleX += rotateAngle;

                world *= Matrix.CreateRotationX(MathHelper.ToRadians(rotateAngleX));

            }

            if (Keyboard.GetState().IsKeyDown(Keys.PageUp))
            {
                if (zoom > 0.05f)
                {
                    zoom -= zoomFactor;
                    world *= Matrix.CreateScale(1f - zoomFactor);
                }
            }

            if (Keyboard.GetState().IsKeyDown(Keys.PageDown))
            {
                if (zoom < 2.5f)
                {
                    zoom += zoomFactor;
                    world *= Matrix.CreateScale(1f + zoomFactor);
                }
            }
            #endregion

            // TODO: Add your update logic here

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);
            backgroundBatch.Begin(SpriteBlendMode.None);
            DrawBackground(backgroundBatch);
            backgroundBatch.End();

            tpc.Print("FPS:" + fc.Framerate.ToString(), new Vector2(5, 5));

            foreach (ModelMesh m in tile.Meshes)
            {
                for (int x = -2; x <= 2; x++)
                {
                    for (int y = -2; y < 2; y++)
                    {
                        foreach (BasicEffect e in m.Effects)
                        {
                            e.EnableDefaultLighting();
                            e.PreferPerPixelLighting = true;

                            e.View = view;
                            e.Projection = projection;
                            e.World = Matrix.CreateTranslation(x, y, 0) * world;
                        }
                        m.Draw();
                    }
                }
            }

            // TODO: Add your drawing code here

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
