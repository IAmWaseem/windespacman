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
        }

        /// <summary>
        /// Executes AI move
        /// </summary>
        /// <param name="currentBoard">The current board</param>
        public void Execute(Board currentBoard)
        {
            if (algorithm != null)
            {
                Board next = algorithm.NextMove(currentBoard);
                Game.Instance.SetBoard(next);
            }
        }
    }
}
