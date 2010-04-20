using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    class AIPlayer
    {
        private IAlgorithm algorithm;

        public AIPlayer(PlayerSettings playerSettings)
        {

        }

        public void Execute(Board currentBoard)
        {
            algorithm.NextMove(currentBoard);

        }
    }
}
