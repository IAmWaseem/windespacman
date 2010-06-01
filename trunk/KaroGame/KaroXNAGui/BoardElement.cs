using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Karo.Gui
{
    abstract class BoardElement : DrawableGameComponent 
    {
        protected Model model;
        protected BoundingBox boundingBox;
        protected int boardX;
        protected int boardY;
        protected Matrix world;
        protected bool isSelected;
        protected bool isMouseOver;
        protected Color color;
        protected Color mouseOverColor;
        protected bool animatedStarted;
        protected bool animatedEnded;

        protected BoardElement(Microsoft.Xna.Framework.Game game) : base(game)
        {
        }

        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);
        }

        public override void Draw(GameTime gameTime)
        {
            base.Draw(gameTime);
        }

        public abstract void Move(int i, int y);

        public float Intersect(Ray ray)
        {
            return 0.0f;
        }
    }
}
