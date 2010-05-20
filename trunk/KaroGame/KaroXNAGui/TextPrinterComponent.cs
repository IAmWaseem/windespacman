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
    public class TextPrinterComponent : DrawableGameComponent
    {
        private SpriteBatch spriteBatch;
        protected SpriteFont spriteFont;
        protected string text;
        protected Vector2 location;

        private Color color;

        public TextPrinterComponent(Microsoft.Xna.Framework.Game game, Color color)
            : base(game)
        {
            this.color = color;

            text = "";
            location = new Vector2();

            spriteBatch = new SpriteBatch(Game.GraphicsDevice);
            spriteFont = Game.Content.Load<SpriteFont>(@"FPSfont");
        }

        public void Print(string text, Vector2 location)
        {
            this.text = text;
            this.location = location;
        }

        public override void Draw(GameTime gameTime)
        {
            if (text.Length > 0)
            {
                spriteBatch.Begin();
                spriteBatch.DrawString(spriteFont, text, location, color);
                spriteBatch.End();
            }
            base.Draw(gameTime);
        }
    }
}
