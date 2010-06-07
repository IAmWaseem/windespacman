using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using GameStateManagement;

namespace Karo.Gui
{
    abstract class BoardElement : DrawableGameComponent
    {
        protected GameplayScreen game;
        protected Model model;
        protected BoundingBox boundingBox;
        protected float boardX;
        protected float boardY;
        protected Matrix world;
        protected bool isSelected;
        protected bool isMouseOver;
        protected Color selectedColor;
        protected Color mouseOverColor;
        protected bool animatedStarted;
        protected bool animatedEnded;
        protected Vector3 defaultColor;
        protected bool isPossiblePlace;

        protected BoardElement(GameplayScreen game, Model model, float boardY, float boardX)
            : base(game.ScreenManager.Game)
        {
            this.IsPossiblePlace = false;
            this.model = model;
            this.boardX = boardX;
            this.boardY = boardY;
            this.game = game;
            this.world = Matrix.Identity;
            this.selectedColor = Color.Yellow;
            this.mouseOverColor = Color.Magenta;

            BasicEffect basicEffect = (BasicEffect)model.Meshes[0].Effects[0];

            defaultColor = Color.White.ToVector3();

            if (basicEffect != null)
                if (basicEffect.DiffuseColor != null)
                    defaultColor = basicEffect.DiffuseColor;

            CreateBoundingBox();
        }

        protected abstract void CreateBoundingBox();

        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);
        }

        public override void Draw(GameTime gameTime)
        {
            game.ScreenManager.ResetGraphicsDeviceSettings();
            if (game.IsActive)
            {
                if (IsPossiblePlace && !this.IsMouseOver)
                    game.ScreenManager.GraphicsDevice.RenderState.FillMode = FillMode.WireFrame;

                if (!isPossiblePlace || isPossiblePlace && game.ShowTargetPlaces)
                {
                    foreach (ModelMesh mesh in model.Meshes)
                    {
                        foreach (BasicEffect effect in mesh.Effects)
                        {
                            effect.World = World;
                            effect.World *= game.World;
                            effect.View = game.View;
                            effect.Projection = game.Projection;

                            if (this.IsSelected)
                                effect.DiffuseColor = selectedColor.ToVector3();
                            else if (this.IsMouseOver)
                                effect.DiffuseColor = mouseOverColor.ToVector3();
                            else
                                effect.DiffuseColor = defaultColor;

                            effect.EnableDefaultLighting();

                        }
                        mesh.Draw();
                    }
                }

                // reset to solid, only if drawn as wire
                if(IsPossiblePlace)
                    game.ScreenManager.GraphicsDevice.RenderState.FillMode = FillMode.Solid;

                if (game.EnableDebug)
                    DrawBoundingBox.Draw(game.ScreenManager.GraphicsDevice, this.boundingBox, game.View, game.Projection);
            }

            base.Draw(gameTime);
        }

        public abstract void Move(int i, int y);

        public float? Intersect(Ray ray)
        {
            return ray.Intersects(boundingBox);
        }

        public float BoardX
        {
            get { return boardX; }
            set { boardX = value; }
        }

        public bool AnimatedEnded
        {
            get { return animatedEnded; }
            set { animatedEnded = value; }
        }

        public bool AnimatedStarted
        {
            get { return animatedStarted; }
            set { animatedStarted = value; }
        }

        public Color MouseOverColor
        {
            get { return mouseOverColor; }
            set { mouseOverColor = value; }
        }

        public Color SelectedColor
        {
            get { return selectedColor; }
            set { selectedColor = value; }
        }

        public Vector3 DefaultColor
        {
            get { return defaultColor; }
            set { defaultColor = value; }
        }

        public bool IsMouseOver
        {
            get { return isMouseOver; }
            set { isMouseOver = value; }
        }

        public bool IsSelected
        {
            get { return isSelected; }
            set { isSelected = value; }
        }

        public Matrix World
        {
            get { return world; }
            set { world = value; }
        }

        public float BoardY
        {
            get { return boardY; }
            set { boardY = value; }
        }

        public GameplayScreen Game
        {
            get { return game; }
            set { game = value; }
        }

        public Model Model
        {
            get { return model; }
            set { model = value; }
        }

        public bool IsPossiblePlace
        {
            get { return isPossiblePlace; }
            set { isPossiblePlace = value; }
        }

    }
}
