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
        public bool HeadUp { get; set; }
        private float moveToY;
        private float moveToX;
        private float toMoveY;
        private float toMoveX;
        private float speed = 0.001f;
        
        public Piece(GameplayScreen game, Model model, float boardY, float boardX)
            : base(game, model, boardY, boardX)
        {
            HeadUp = false;
            world = Matrix.CreateTranslation(BoardX, BoardY, 0);
            CreateBoundingBox();
        }

        public override void Update(Microsoft.Xna.Framework.GameTime gameTime)
        {
            if (animatedStarted)
            {
                float distanceTraveledX = Math.Abs(gameTime.ElapsedGameTime.Milliseconds * speed * toMoveX);
                float distanceTraveledY = Math.Abs(gameTime.ElapsedGameTime.Milliseconds * speed * toMoveY);
                if(boardX > moveToX)
                    boardX -= distanceTraveledX;
                else
                    boardX += distanceTraveledX;
                if (boardY > moveToY)
                    boardY -= distanceTraveledY;
                else
                    boardY += distanceTraveledY;
                if (Math.Abs(boardX - moveToX) < 0.2f && Math.Abs(boardY - moveToY) < 0.2f)
                {
                    animatedStarted = false;
                    animatedEnded = true;
                    boardX = moveToX;
                    boardY = moveToY;
                }
            }
            if (!HeadUp)
            {
                world = Matrix.CreateRotationX(MathHelper.ToRadians(180f));
                world *= Matrix.CreateTranslation(BoardX, BoardY, 0);
                world *= Matrix.CreateTranslation(0, 0, 0.55f);
            }
            else
            {
                world = Matrix.CreateTranslation(BoardX, BoardY, 0) ;
                world *= Matrix.CreateTranslation(0, 0, 0.05f);
            }
            CreateBoundingBox();
            base.Update(gameTime);
        }

        protected override void CreateBoundingBox()
        {
            boundingBox = BoundingBox.CreateFromSphere(model.Meshes[0].BoundingSphere);
            boundingBox.Max = Vector3.Transform(boundingBox.Max, Matrix.CreateScale(0.6f, 0.6f, 0.7f) * Matrix.CreateTranslation(-0.02f, -0.04f, 0.1f) * world * game.World);
            boundingBox.Min = Vector3.Transform(boundingBox.Min, Matrix.CreateScale(0.6f, 0.6f, 0.7f) * Matrix.CreateTranslation(-0.02f, -0.04f, 0.1f) * world * game.World);
        }

        public override void Move(int x, int y)
        {
            moveToX = x;
            moveToY = y;
            toMoveX = boardX - x;
            toMoveY = boardY - y;
            AnimatedStarted = true;
        }
    }
}
