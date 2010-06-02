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
            PlayerSettings playerA = new PlayerSettings(false, AlgorithmType.AlphaBeta, 0, false, false, EvaluationType.BetterOne);
            PlayerSettings playerB = null;
            switch (difficulty)
            {
                case Difficulty.Easy:
                    playerB = new PlayerSettings(true, AlgorithmType.Random, 0, false, false, EvaluationType.BetterOne);
                    break;

                case Difficulty.Medium:
                    playerB = new PlayerSettings(true, AlgorithmType.MiniMax, 1, false, false, EvaluationType.BetterOne);
                    break;

                case Difficulty.Hard:
                    playerB = new PlayerSettings(true, AlgorithmType.AlphaBeta, 4, true, true, EvaluationType.BetterOne);
                    break;
            }
            uiConnector.StartGame(playerA, playerB);
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

        private void SetupBoard()
        {
            currentBoard = uiConnector.GetBoard();
            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {

                }
            }
        }
    }
}
