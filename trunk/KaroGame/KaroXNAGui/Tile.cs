using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;

namespace Karo.Gui
{
    class Tile : BoardElement
    {
        public Tile(KaroGui game, Model model, int boardY, int boardX)
            : base(game, model, boardY, boardX)
        {
        }

        public override void Update(Microsoft.Xna.Framework.GameTime gameTime)
        {
            base.Update(gameTime);
        }

        protected override void CreateBoundingBox()
        {
            throw new NotImplementedException();
        }

        public override void Move(int i, int y)
        {
            throw new NotImplementedException();
        }
    }
}
