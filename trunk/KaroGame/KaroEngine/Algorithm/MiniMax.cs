using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    class MiniMax : IAlgorithm
    {
        private int plieDepth;
        private bool transtable;

        public MiniMax(int plieDepth, bool doTranstable)
        {
            this.plieDepth = plieDepth;
            this.transtable = doTranstable;
        }

        public Board NextMove(Board currentBoard)
        {
            Board next = DoMiniMax(currentBoard, plieDepth, Game.Instance.GetTurn());

            return next;
        }

        private Board DoMiniMax(Board node, int depth, bool turnA)
        {
            if (depth <= 0)
                return node;
            if (node.IsWon())
                return node;

            int alphaEvalution = Int32.MinValue;
            Board alpha = node;

            List<Board> possibleMoves = node.GenerateMoves(turnA);

            foreach (Board b in possibleMoves)
            {
                bool nextTurn = true;
                if(turnA)
                    nextTurn = false;

                Board beta = DoMiniMax(b, depth-1, nextTurn);
                int betaEvaluation = beta.Evaluation(nextTurn);

                if (alphaEvalution < (-1 * betaEvaluation))
                {
                    alphaEvalution = betaEvaluation;
                    alpha = b;
                }
            }

            return alpha;
        }
    }
}
