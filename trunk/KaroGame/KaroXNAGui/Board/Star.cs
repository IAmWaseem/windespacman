using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using GameStateManagement;

namespace Karo.Gui
{
    class Star : DrawableGameComponent
    {
        private Matrix world, view, projection;
        private Model model;
        private Matrix[] transforms;
        private GameplayScreen game;
        private float y;
        private float x;
        private Random random;
        private float speed;
        private float xRotation;
        private float yRotation;
        private float zRotation;
        private float xRotation2 = 0.0f;
        private float yRotation2 = 0.0f;
        private float zRotation2 = 0.0f;
        private Vector3 color;
        private float timeToDisplay = 10000f;

        public Star(GameplayScreen game, Model model, Matrix view, Matrix projection, Random random) : base(game.ScreenManager.Game)
        {
            this.random = random;
            this.x = random.Next(-340, 200) / 100f;
            this.speed = random.Next(2, 8) / 1000f;

            float scale = random.Next(100, 1000)/100000f;

            if(speed > 0.0004)
                this.y = random.Next(5, 10);
            else
                this.y = random.Next(2, 5);

            xRotation = (float) random.Next(-360, 360);
            yRotation = (float)random.Next(-360, 360);
            zRotation = (float)random.Next(-360, 360);

            color = new Vector3((float)random.NextDouble(), (float)random.NextDouble(), (float)random.NextDouble());

            this.DrawOrder = 900;
            this.view = view;
            this.projection = projection;
            this.model = model;
            this.game = game;
            this.world = Matrix.Identity * Matrix.CreateScale(scale) * Matrix.CreateTranslation(x, y, 13f);
            transforms = new Matrix[model.Bones.Count];
            model.CopyAbsoluteBoneTransformsTo(transforms);

        }

        public override void Draw(GameTime gameTime)
        {
            foreach (ModelMesh mesh in model.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    effect.World = world * Matrix.CreateRotationY(yRotation2) * Matrix.CreateRotationX(xRotation2) * Matrix.CreateRotationZ(zRotation2) * Matrix.CreateTranslation(0f, y, 0f) * Matrix.CreateRotationX(MathHelper.ToRadians(xRotation)) * Matrix.CreateRotationZ(MathHelper.ToRadians(zRotation)) * Matrix.CreateRotationY(MathHelper.ToRadians(yRotation));
                    
                    effect.View = view;
                    effect.Projection = projection;
                    effect.DiffuseColor = color;
                    effect.EnableDefaultLighting();
                }
                mesh.Draw();
            }
            base.Draw(gameTime);
        }

        public override void Update(GameTime gameTime)
        {
            y -= gameTime.ElapsedGameTime.Milliseconds * speed;
            xRotation2 -= 0.005f;
            yRotation2 -= 0.005f;
            zRotation2 -= 0.005f;
            base.Update(gameTime);
            timeToDisplay -= gameTime.ElapsedGameTime.Milliseconds;
            if(timeToDisplay<=0)
                game.ScreenManager.Game.Components.Remove(this);
        }
    }
}
