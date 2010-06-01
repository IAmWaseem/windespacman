using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using GameStateManagement;

namespace Karo.Gui
{
    class Piece : BoardElement
    {
        public Piece(GameplayScreen game, Model model, int boardY, int boardX)
            : base(game, model, boardY, boardX)
        {
        }

        public override void Update(Microsoft.Xna.Framework.GameTime gameTime)
        {
 	         base.Update(gameTime);
        }

        protected override void CreateBoundingBox()
        {
            boundingBox = BoundingBox.CreateFromSphere(model.Meshes[0].BoundingSphere);
            boundingBox.Max = Vector3.Transform(boundingBox.Max, Matrix.CreateScale(0.7f));
            boundingBox.Min = Vector3.Transform(boundingBox.Min, Matrix.CreateScale(0.7f));
        }

        public override void Move(int i, int y)
        {
            throw new NotImplementedException();
        }
    }
}
