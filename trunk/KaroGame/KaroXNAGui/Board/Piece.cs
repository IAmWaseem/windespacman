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
        public bool PreviousHead { get; set; }
        private float moveToY;
        private float moveToX;
        private float toMoveY;
        private float toMoveX;
        private float speed = 0.001f;
        private float height = 0f;
        private float arcSpeed = 0.003f;
        private bool goingUp = false;
        private float halfwayX;
        private float halfwayY;
        private float rotationValue = 180f;
        private float distanceToMoveX;
        private float distanceMovedX;
        private float directionDegrees;
        
        public Piece(GameplayScreen game, Model model, float boardY, float boardX)
            : base(game, model, boardY, boardX)
        {
            HeadUp = false;
            PreviousHead = false;
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
                distanceMovedX += distanceTraveledX;
                if (HeadUp)
                {
                    float percentageMoved = (distanceToMoveX / distanceMovedX) / 100f;
                    percentageMoved = 1f;
                    rotationValue = percentageMoved * 180f;
                }
                if (Math.Abs(boardX - halfwayX) < 0.1f && Math.Abs(boardY - halfwayY) < 0.1f)
                    goingUp = false;

                if (goingUp)
                    height += distanceTraveledHeight;
                else
                    height -= distanceTraveledHeight;

                if(boardX > moveToX)
                    boardX -= distanceTraveledX;
                else
                    boardX += distanceTraveledX;
                if (boardY > moveToY)
                    boardY -= distanceTraveledY;
                else
                    boardY += distanceTraveledY;
                if (Math.Abs(boardX - moveToX) < 0.1f && Math.Abs(boardY - moveToY) < 0.1f || game.EnableAnimation == false)
                {
                    animatedStarted = false;
                    animatedEnded = true;
                    boardX = moveToX;
                    boardY = moveToY;
                    height = 0;
                }
            }
            if (animatedStarted)
            {
                if (HeadUp && !PreviousHead)
                {
                    //rotate
                    rotationValue = Math.Abs(gameTime.ElapsedGameTime.Milliseconds * speed * 180);
                    PreviousHead = true;
                }
                else if (HeadUp && rotationValue == 180.0f)
                {
                    rotationValue = 0.0f;
                }
                world = Matrix.CreateRotationZ(MathHelper.ToRadians(this.directionDegrees));
                world *= Matrix.CreateRotationX(MathHelper.ToRadians(rotationValue));
                world *= Matrix.CreateTranslation(BoardX, BoardY, height);
                world *= Matrix.CreateTranslation(0, 0, 0.05f + (0.0027f * Math.Abs(rotationValue)));
                world *= Matrix.CreateTranslation(0, 0, 0.55f);
            }
            else if (!HeadUp)
            {
                world = Matrix.CreateRotationX(MathHelper.ToRadians(180f));
                world *= Matrix.CreateTranslation(BoardX, BoardY, height);
                world *= Matrix.CreateTranslation(0, 0, 0.55f);
            }
            else
            {
                world = Matrix.CreateTranslation(BoardX, BoardY, height);
                world *= Matrix.CreateTranslation(0, 0, 0.05f);
            }
            if(animatedEnded)
                CreateBoundingBox();
            base.Update(gameTime);
        }

        protected override void CreateBoundingBox()
        {
            boundingBox = BoundingBox.CreateFromSphere(model.Meshes[0].BoundingSphere);
            boundingBox.Max = Vector3.Transform(boundingBox.Max, Matrix.CreateScale(0.6f, 0.6f, 0.7f) * Matrix.CreateTranslation(-0.02f, -0.04f, 0.1f) * world * game.World);
            boundingBox.Min = Vector3.Transform(boundingBox.Min, Matrix.CreateScale(0.6f, 0.6f, 0.7f) * Matrix.CreateTranslation(-0.02f, -0.04f, 0.1f) * world * game.World);
        }

        public override void Move(float x, float y)
        {

            directionDegrees = MathHelper.ToDegrees((float)Math.Atan2(boardX - x, boardY - y));
            moveToX = x;
            moveToY = y;
            halfwayX = (boardX + (float)x) / 2f;
            halfwayY = (boardY + (float)y) / 2f;
            distanceToMoveX = Math.Abs(boardX - x);
            distanceMovedX = 0;
            toMoveX = boardX - x;
            toMoveY = boardY - y;
            AnimatedStarted = true;
            AnimatedEnded = false;
            goingUp = true;
        }
    }
}
