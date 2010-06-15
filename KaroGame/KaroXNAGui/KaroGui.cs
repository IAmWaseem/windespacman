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

namespace Karo.Gui
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class KaroGui : Microsoft.Xna.Framework.Game
    {
        // default members
        public GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        ScreenManager screenManager;
        SoundPlayerLoop loopSound;
        //background
        SpriteBatch backgroundBatch;
        Texture2D background;
        bool f10Pressed = false;

        public KaroGui()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
        }

        private Properties.Settings DefaultSettings
        {
            get { return Properties.Settings.Default; }
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            if (DefaultSettings.FirstRun)
            {
                DefaultSettings.FirstRun = false;

                List<DisplayMode> dispList = GraphicsAdapter.DefaultAdapter.SupportedDisplayModes.ToList();
                List<DisplayMode> tempList = GraphicsAdapter.DefaultAdapter.SupportedDisplayModes.ToList();

                foreach (DisplayMode dm in tempList)
                {
                    if (dm.Format != SurfaceFormat.Bgr32)
                        dispList.Remove(dm);
                }

                if (dispList.Count > 2)
                {
                    DefaultSettings.ScreenWidth = dispList[dispList.Count - 2].Width;
                    DefaultSettings.ScreenHeight = dispList[dispList.Count - 2].Height;
                }

                SurfaceFormat format = GraphicsAdapter.DefaultAdapter.CurrentDisplayMode.Format;
                // Check for 4xAA
                if (GraphicsAdapter.DefaultAdapter.CheckDeviceMultiSampleType(DeviceType.Hardware, format,
                    false, MultiSampleType.FourSamples))
                {
                    DefaultSettings.MultiSamplingLevel = MultiSampleType.FourSamples;
                }
                // Check for 2xAA
                else if (GraphicsAdapter.DefaultAdapter.CheckDeviceMultiSampleType(DeviceType.Hardware, format,
                    false, MultiSampleType.TwoSamples))
                {
                    DefaultSettings.MultiSamplingLevel = MultiSampleType.TwoSamples;
                }
                // Check for 1xAA
                else if (GraphicsAdapter.DefaultAdapter.CheckDeviceMultiSampleType(DeviceType.Hardware, format,
                    false, MultiSampleType.NonMaskable))
                {
                    DefaultSettings.MultiSamplingLevel = MultiSampleType.NonMaskable;
                }
                else
                {
                    DefaultSettings.MultiSamplingLevel = MultiSampleType.None;
                }


                DefaultSettings.Save();
            }

            InitGraphics();

            // screenmanager
            screenManager = new ScreenManager(this);
            Components.Add(screenManager);

            // Activate the first screens.
            screenManager.AddScreen(new BackgroundScreen(), null);
            screenManager.AddScreen(new MainMenuScreen(), null);

            base.Initialize();
        }

        public void InitGraphics()
        {
            // TODO: Add your initialization logic here
            graphics.GraphicsDevice.RenderState.MultiSampleAntiAlias = DefaultSettings.MultiSampleAntiAlias;
            graphics.GraphicsDevice.PresentationParameters.MultiSampleType = DefaultSettings.MultiSamplingLevel;

            graphics.PreferredBackBufferWidth = DefaultSettings.ScreenWidth;
            graphics.PreferredBackBufferHeight = DefaultSettings.ScreenHeight;
            graphics.PreferMultiSampling = DefaultSettings.MultiSampleAntiAlias;
            graphics.IsFullScreen = DefaultSettings.FullScreen;

            graphics.ApplyChanges();
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
            background = Content.Load<Texture2D>("GameMenuBackground");
            loopSound = new SoundPlayerLoop(this, "guitar");

            // check to enable or disable music
            if (Karo.Gui.Properties.Settings.Default.EnableSound)
                loopSound.PlayLoop();
            else
                loopSound.StopLoop();
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
            if (Keyboard.GetState().IsKeyDown(Keys.F10))
                f10Pressed = true;

            if(Keyboard.GetState().IsKeyUp(Keys.F10) && f10Pressed)
            {
                // switch setting

                if (Karo.Gui.Properties.Settings.Default.EnableSound)
                    Karo.Gui.Properties.Settings.Default.EnableSound = false;
                else
                    Karo.Gui.Properties.Settings.Default.EnableSound = true;

                // save settings
                Karo.Gui.Properties.Settings.Default.Save();

                // check to enable or disable music
                if (Karo.Gui.Properties.Settings.Default.EnableSound)
                    loopSound.PlayLoop();
                else
                    loopSound.StopLoop();


                f10Pressed = false;
            }

            


            base.Update(gameTime);
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
