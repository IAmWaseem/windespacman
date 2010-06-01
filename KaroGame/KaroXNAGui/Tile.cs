﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using GameStateManagement;

namespace Karo.Gui
{
    class Tile : BoardElement
    {
        public Tile(GameplayScreen game, Model model, int boardY, int boardX)
            : base(game, model, boardY, boardX)
        {
            world = Matrix.CreateRotationX(MathHelper.ToRadians(-90)) * Matrix.CreateTranslation(boardX, 0, boardY);
            
        }

        public override void Update(Microsoft.Xna.Framework.GameTime gameTime)
        {
            base.Update(gameTime);
        }

        protected override void CreateBoundingBox()
        {
            boundingBox = BoundingBox.CreateFromSphere(model.Meshes[0].BoundingSphere);
            boundingBox.Max = Vector3.Transform(boundingBox.Max, Matrix.CreateScale(0.55f, 0.10f, 0.55f) * Matrix.CreateTranslation(boardX + 0.095f, 0.05f, boardY + 0.005f));
            boundingBox.Min = Vector3.Transform(boundingBox.Min, Matrix.CreateScale(0.55f, 0.10f, 0.55f) * Matrix.CreateTranslation(boardX + 0.095f, 0.05f, boardY + 0.005f));
        }

        public override void Move(int i, int y)
        {
            throw new NotImplementedException();
        }
    }
}
