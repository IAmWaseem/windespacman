using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    /// <summary>
    /// Contains settings for player
    /// </summary>
    public class AIPlayer
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
                algorithm = new MiniMax(playerSettings.PlieDepth, playerSettings.DoTransTable);
            }
            else if (playerSettings.AlgorithmType == AlgorithmType.AlphaBeta)
            {
                algorithm = new AlphaBeta(playerSettings.PlieDepth, playerSettings.DoMoveOrdering, playerSettings.DoTransTable);
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
                if(IsEqual(currentBoard, next)
                    throw new Exception();
                Game.Instance.SetBoard(next);
            }

        }

        private bool IsEqual(Board boardA, Board boardB)
        {
            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    if (boardA.BoardSituation[x, y] != boardB.BoardSituation[x, y])
                        return false;
                }
            }

            return true;
        }
    }
}
