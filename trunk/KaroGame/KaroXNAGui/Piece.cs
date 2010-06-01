using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo.Gui
{
    class Piece : BoardElement
    {
        public Piece(Microsoft.Xna.Framework.Game game) : base(game)
        {
        }

        public override void Update(Microsoft.Xna.Framework.GameTime gameTime)
        {
 	         base.Update(gameTime);
        }

        public override void Move(int i, int y)
        {
            throw new NotImplementedException();
        }
    }
}
