﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Karo.Gui
{
    abstract class BoardElement : DrawableGameComponent 
    {
        protected KaroGui game;
        protected Model model;
        protected BoundingBox boundingBox;
        protected int boardX;
        protected int boardY;
        protected Matrix world;
        protected bool isSelected;
        protected bool isMouseOver;
        protected Color color;
        protected Color mouseOverColor;
        protected bool animatedStarted;
        protected bool animatedEnded;

        protected BoardElement(KaroGui game, Model model, int boardY, int boardX) : base(game)
        {
            this.model = model;
            this.boardX = boardX;
            this.boardY = boardY;
            this.game = game;
            CreateBoundingBox();
        }

        protected abstract void CreateBoundingBox();

        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);
        }

        public override void Draw(GameTime gameTime)
        {
            base.Draw(gameTime);
        }

        public abstract void Move(int i, int y);

        public float Intersect(Ray ray)
        {
            return 0.0f;
        }

        public int BoardX
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

        public Color Color
        {
            get { return color; }
            set { color = value; }
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

        public int BoardY
        {
            get { return boardY; }
            set { boardY = value; }
        }

        public KaroGui Game
        {
            get { return game; }
            set { game = value; }
        }

        public Model Model
        {
            get { return model; }
            set { model = value; }
        }

    }
}