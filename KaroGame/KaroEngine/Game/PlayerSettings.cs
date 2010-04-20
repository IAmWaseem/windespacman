using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    class PlayerSettings
    {
        #region "Properties"

        /// <summary>
        /// Is the player driven by AI
        /// </summary>
        public bool IsAI { get; set; }

        /// <summary>
        /// Algorithm type of AI player if AI
        /// </summary>
        public AlgorithmType AlgorithmType { get; set; }

        // Depth of plie for the algorithm (if random, not used)
        public int PlieDepth { get; set; }

        /// <summary>
        /// Algorithm uses transposition table (if random, not used)
        /// </summary>
        public bool DoTransTable { get; set; }

        /// <summary>
        /// Algorithm uses move ordering (only if AlphaBeta algorithm)
        /// </summary>
        public bool DoMoveOrdering { get; set; }

        #endregion

        #region "Constructors"

        /// <summary>
        /// Creates a human player
        /// </summary>
        public PlayerSettings()
        {
            IsAI = false;
            AlgorithmType = AlgorithmType.Random;
            PlieDepth = 0;
            DoTransTable = false;
            DoMoveOrdering = false;
        }

        /// <summary>
        /// Creates a human or ai player type with the provided attributes
        /// </summary>
        /// <param name="pIsAI">True if player will be handles by AI</param>
        /// <param name="pAlgorithmType">Type of algorithm used by the AI (if AI)</param>
        /// <param name="pPlieDepth">Plie depth used by the algorithm (if MiniMax or AlphaBeta)</param>
        /// <param name="pTransTable">Algorithm uses transposition table (if MiniMax or AlphaBeta)</param>
        /// <param name="pMoveOrdering">Algorithm sorts the moves (if AlphaBeta)</param>
        public PlayerSettings(bool pIsAI, AlgorithmType pAlgorithmType, int pPlieDepth, bool pTransTable, bool pMoveOrdering)
        {
            IsAI = pIsAI;
            AlgorithmType = pAlgorithmType;
            PlieDepth = pPlieDepth;
            DoTransTable = pTransTable;
            DoMoveOrdering = pMoveOrdering;
        }

        #endregion
    }
}
