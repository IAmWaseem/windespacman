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
    public struct TextObject
    {
        public string text;
        public object obj;
    }

    /// <summary>
    /// This is a game component that implements IUpdateable.
    /// </summary>
    public class LoggerComponent : Microsoft.Xna.Framework.DrawableGameComponent
    {
        List<TextObject> textList;
        private SpriteBatch spriteBatch;
        protected SpriteFont spriteFont;

        public LoggerComponent(Microsoft.Xna.Framework.Game game)
            : base(game)
        {
            // TODO: Construct any child components here
            textList = new List<TextObject>();
            spriteBatch = new SpriteBatch(Game.GraphicsDevice);
            spriteFont = Game.Content.Load<SpriteFont>(@"FPSfont");
            
        }

        /// <summary>
        /// Allows the game component to perform any initialization it needs to before starting
        /// to run.  This is where it can query for any required services and load content.
        /// </summary>
        public override void Initialize()
        {
            // TODO: Add your initialization code here

            base.Initialize();
        }

        /// <summary>
        /// Clear lines
        /// </summary>
        public void ClearLog()
        {
            textList.Clear();
        }

        /// <summary>
        /// Add empty line
        /// </summary>
        public void Line()
        {
            TextObject t = new TextObject();
            t.text = "";
            t.obj = "";

            textList.Add(t);
        }

        // Add line with text
        public void Line(string text)
        {
            TextObject t = new TextObject();
            t.text = text;
            t.obj = "";

            textList.Add(t);
        }

        // Add line with value
        public void Line(string text, string show)
        {
            TextObject t = new TextObject();
            t.text = text + ":";
            t.obj = show;

            textList.Add(t);
        }      

        /// <summary>
        /// Allows the game component to update itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        public override void Update(GameTime gameTime)
        {
            // TODO: Add your update code here

            base.Update(gameTime);
        }

        /// <summary>
        /// Allows the game component to draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        public override void Draw(GameTime gameTime)
        {
            int loc = 5;
            foreach (TextObject t in textList)
            {
                if (t.text.Length > 0)
                {
                    spriteBatch.Begin();
                    spriteBatch.DrawString(spriteFont, t.text + " " + t.obj, new Vector2(5, loc), Color.White);
                    spriteBatch.End();
                }
                int height = (int)spriteFont.MeasureString("TEST").Y;
                loc += height;
            }

            base.Draw(gameTime);
        }
    }
}