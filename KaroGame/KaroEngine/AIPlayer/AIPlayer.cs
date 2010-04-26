using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    class AIPlayer
    {
        private IAlgorithm algorithm = null;

        /// <summary>
        /// PlayerSettings of player
        /// </summary>
        public PlayerSettings PlayerSettings { get; private set; }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="playerSettings">Playersettings</param>
        public AIPlayer(PlayerSettings playerSettings)
        {
            PlayerSettings = playerSettings;
            if (playerSettings.AlgorithmType == AlgorithmType.Random)
            {
                algorithm = new Random();
            }
            else if (playerSettings.AlgorithmType == AlgorithmType.MiniMax)
            {
                algorithm = new MiniMax(playerSettings.PlieDepth);
            }
        }

        /// <summary>
        /// Executes AI move
        /// </summary>
        /// <param name="currentBoard">The current board</param>
        public void Execute(Board currentBoard)
        {
            DateTime beforeFunction = DateTime.Now;

            if (algorithm != null)
            {
                Board next = algorithm.NextMove(currentBoard);
                Game.Instance.SetBoard(next);
            }

            // Elapsed time
            DateTime afterFunction = DateTime.Now;
            TimeSpan elapsedTime = afterFunction - beforeFunction;
            Logger.AddLine(Game.Instance.GetCurrentPlayerNumber() + "-> AI calculated in: " + elapsedTime.TotalMilliseconds.ToString() + " ms");
        }
    }
}
