using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Karo.Gui
{
    class BoardManager : GameComponent
    {
        private List<BoardElement> boardElements;
        private Karo.BoardPosition[,] currentBoard;
        private BoardElement selectedElement;
        private KaroGui game;
        private UIConnector uiConnector;

        public void StartGame(Difficulty difficulty)
        {
        }

        public BoardManager(KaroGui game) : base(game)
        {
            this.uiConnector = UIConnector.Instance;
            this.game = game;
        }

        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);
        }

        public void DoMove()
        {
        }
    }
}
