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
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        Model tile, piece;
        Matrix view, cameraView, topView, projection, world;
        bool rotateUp = true;

        float _angle, _angleBefore;
        public float RotationAngle 
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

        bool tPressed, rPressed, rotate, middleMousePressed;

        // Maybe other location for this?
        public UIConnector KaroEngine { get; set; }

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

            IsMouseVisible = true;
            tPressed = false;
            rotate = false;
            middleMousePressed = false;

            // init views
            view = Matrix.CreateLookAt(new Vector3(0, -10, 10), new Vector3(0, 0, 0), Vector3.Up);
            topView = Matrix.CreateLookAt(new Vector3(0, 0, 10), new Vector3(0, 0, 0), Vector3.Up);
            cameraView = Matrix.CreateLookAt(new Vector3(0, -10, 10), new Vector3(0, 0, 0), Vector3.Up);

            projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45f), (4f / 3f), 0.1f, 100.0f);
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
                    if(view == topView)
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
                    _angleBefore = RotationAngle;
                }
                rPressed = false;
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

            if (!rotateUp)
                rotateAngle *= -1;

            // rotate with 'r'
            if (rotate)
            {
                    RotationAngle += rotateAngle;

                if (RotationAngle  > 180 || RotationAngle < 0)
                {
                    if(rotateUp)
                        rotateAngle = RotationAngle - 180;
                    else
                        rotateAngle = 360 - RotationAngle;

                    if (!rotateUp)
                        RotationAngle = 0;
                    else
                        RotationAngle = 180;
                    
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
                RotationAngle += rotateAngle;

                world *= Matrix.CreateRotationZ(MathHelper.ToRadians(rotateAngle));
            }

            // rotate with keys
            if (Keyboard.GetState().IsKeyDown(Keys.Right))
            {
                rotate = false;
                rotateAngle *= -1;
                RotationAngle += rotateAngle;

                world *= Matrix.CreateRotationZ(MathHelper.ToRadians(rotateAngle));
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
    }
}
