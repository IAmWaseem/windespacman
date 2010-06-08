using System;
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
        private bool isVisible;
        private float moveToY;
        private float moveToX;
        private float toMoveY;
        private float toMoveX;
        private float speed = 0.001f;
        private float height = 0f;
        private float arcSpeed = 0.005f;
        private bool goingUp = false;
        private float halfwayX;
        private float halfwayY;

        public Tile(GameplayScreen game, Model model, int boardY, int boardX)
            : base(game, model, boardY, boardX)
        {
            world = Matrix.CreateTranslation(BoardX, BoardY, 0);
            CreateBoundingBox();
        }

        public override void Update(Microsoft.Xna.Framework.GameTime gameTime)
        {
            if (animatedStarted)
            {
                float distanceTraveledX = Math.Abs(gameTime.ElapsedGameTime.Milliseconds * speed * toMoveX);
                float distanceTraveledY = Math.Abs(gameTime.ElapsedGameTime.Milliseconds * speed * toMoveY);
                float distanceTraveledHeight = arcSpeed * gameTime.ElapsedGameTime.Milliseconds;

                if (Math.Abs(boardX - halfwayX) < 0.1f && Math.Abs(boardY - halfwayY) < 0.1f)
                    goingUp = false;

                if (goingUp)
                    height += distanceTraveledHeight;
                else
                    height -= distanceTraveledHeight;

                if (boardX > moveToX)
                    boardX -= distanceTraveledX;
                else
                    boardX += distanceTraveledX;
                if (boardY > moveToY)
                    boardY -= distanceTraveledY;
                else
                    boardY += distanceTraveledY;
                if (Math.Abs(boardX - moveToX) < 0.1f && Math.Abs(boardY - moveToY) < 0.1f)
                {
                    animatedStarted = false;
                    animatedEnded = true;
                    boardX = moveToX;
                    boardY = moveToY;
                    height = 0;
                }
            }
            world = Matrix.CreateTranslation(BoardX, BoardY, height);
            CreateBoundingBox();
            base.Update(gameTime);
        }

        protected override void CreateBoundingBox()
        {
            boundingBox = BoundingBox.CreateFromSphere(model.Meshes[0].BoundingSphere);
            boundingBox.Max = Vector3.Transform(boundingBox.Max, Matrix.CreateScale(0.55f, 0.10f, 0.55f) * Matrix.CreateRotationX(MathHelper.ToRadians(90)) * Matrix.CreateTranslation(0.095f, 0.0f, 0.1f) * world * game.World);
            boundingBox.Min = Vector3.Transform(boundingBox.Min, Matrix.CreateScale(0.55f, 0.10f, 0.55f) * Matrix.CreateRotationX(MathHelper.ToRadians(90)) * Matrix.CreateTranslation(0.095f, 0.0f, 0.1f) * world * game.World);
        }

        public override void Move(int x, int y)
        {
            moveToX = x;
            moveToY = y;
            halfwayX = (boardX + (float)x) / 2f;
            halfwayY = (boardY + (float)y) / 2f;
            toMoveX = boardX - x;
            toMoveY = boardY - y;
            AnimatedStarted = true;
            animatedEnded = false;
            goingUp = true;
        }
    }
}
