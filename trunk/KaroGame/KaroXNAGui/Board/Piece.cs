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
            world = Matrix.CreateTranslation(-10 + BoardX, -9.5f + BoardY, 0.15f);
            CreateBoundingBox();
        }

        public override void Update(Microsoft.Xna.Framework.GameTime gameTime)
        {
 	         base.Update(gameTime);
        }

        protected override void CreateBoundingBox()
        {
            boundingBox = BoundingBox.CreateFromSphere(model.Meshes[0].BoundingSphere);
            boundingBox.Max = Vector3.Transform(boundingBox.Max, Matrix.CreateScale(0.6f, 0.6f, 0.7f) * Matrix.CreateTranslation(-0.02f, -0.04f, 0.1f) * world);
            boundingBox.Min = Vector3.Transform(boundingBox.Min, Matrix.CreateScale(0.6f, 0.6f, 0.7f) * Matrix.CreateTranslation(-0.02f, -0.04f, 0.1f) * world);
        
        }

        public override void Move(int i, int y)
        {
            throw new NotImplementedException();
        }
    }
}
