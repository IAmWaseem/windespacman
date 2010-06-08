using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;
using GameStateManagement;


namespace Karo.Gui
{
    enum RomanNumbers
    {
        I = 1,
        II = 2,
        III = 3,
        IV = 4,
        V = 5,
        VI = 6,
        VII = 7,
        VIII = 8,
        IX = 9,
        X = 10,
        XI = 11,
        XII = 12,
        XIII = 13,
        XIV = 14,
        XV = 15,
        XVI = 16,
        XVII = 17,
        XVIII = 18,
        XIX = 19,
        XX = 20
    }

    class Letters : DrawableGameComponent
    {
        List<Model> letters;
        GameplayScreen game;
        BoardManager manager;

        public Letters(GameplayScreen game, BoardManager manager)
            : base(game.ScreenManager.Game)
        {
            this.game = game;
            this.manager = manager;
        }

        public override void Initialize()
        {
            letters = new List<Model>();
            base.Initialize();
        }

        protected override void LoadContent()
        {
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/A"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/B"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/C"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/D"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/E"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/F"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/G"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/H"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/I"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/J"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/K"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/L"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/M"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/N"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/O"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/P"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/Q"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/R"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/S"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/T"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/U"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/V"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/W"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/X"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/Y"));
            letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/Z"));
        }

        public override void Update(GameTime gameTime)
        {
            if (letters.Count == 0)
            {
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/A"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/B"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/C"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/D"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/E"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/F"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/G"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/H"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/I"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/J"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/K"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/L"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/M"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/N"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/O"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/P"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/Q"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/R"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/S"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/T"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/U"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/V"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/W"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/X"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/Y"));
                letters.Add(game.ScreenManager.Game.Content.Load<Model>("letters/Z"));
            }
            base.Update(gameTime);
        }

        public override void Draw(GameTime gameTime)
        {
            game.ScreenManager.ResetGraphicsDeviceSettings();

            //letters
            for (int i = manager.MinX; i <= manager.MaxX; i++)
            {
                foreach (ModelMesh mesh in letters[i].Meshes)
                {
                    foreach (BasicEffect effect in mesh.Effects)
                    {
                        Matrix trans = Matrix.Identity;
                        trans *= Matrix.CreateScale(0.03f);
                        trans *= Matrix.CreateRotationX(MathHelper.ToRadians(180));
                        trans *= Matrix.CreateRotationZ(MathHelper.ToRadians(180));
                        trans *= Matrix.CreateTranslation(i, manager.MinY - 3, 0);
                        trans *= game.World;

                        effect.World = trans;
                        effect.View = game.View;
                        effect.Projection = game.Projection;
                        effect.EnableDefaultLighting();
                    }
                    mesh.Draw();
                }
            }
            //numbers
            for (int i = 0; i < manager.BoardHeight; i++)
            {
                RomanNumbers current = (RomanNumbers)manager.MinY + i;
                int j = 1;
                foreach (char c in current.ToString())
                {
                    int number = 0;
                    if (c == 'I')
                    {
                        number = 8;
                    }
                    else if (c == 'V')
                    {
                        number = 21;
                    }
                    else if (c == 'X')
                    {
                        number = 23;
                    }
                    foreach (ModelMesh mesh in letters[number].Meshes)
                    {
                        foreach (BasicEffect effect in mesh.Effects)
                        {
                            Matrix trans = Matrix.Identity;
                            trans *= Matrix.CreateScale(0.03f);
                            trans *= Matrix.CreateRotationX(MathHelper.ToRadians(180));
                            trans *= Matrix.CreateRotationZ(MathHelper.ToRadians(180));
                            trans *= Matrix.CreateTranslation(12 - manager.BoardWidth + (j * -0.3f), 8f + ((i - 1) * 1), 0);
                            trans *= game.World;

                            effect.World = trans;
                            effect.View = game.View;
                            effect.Projection = game.Projection;
                            effect.EnableDefaultLighting();
                        }
                        mesh.Draw();
                    }
                    j++;
                }
            }
            base.Draw(gameTime);
        }
    }
}