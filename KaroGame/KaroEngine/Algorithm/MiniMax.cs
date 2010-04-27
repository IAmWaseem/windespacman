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
            Logger.AddLine("Board -> Evaluation value: " + next.Evaluation(Game.Instance.GetTurn()));
            return next;
        }

        private Board DoMiniMax(Board node, int depth, bool turnA)
        {
            if (depth <= 0)
                return node;
            if (node.IsWon())
                return node;

            Board alpha = node;
            int alphaEvalution = Int32.MinValue;

            List<Board> possibleMoves = node.GenerateMoves(turnA);

            foreach (Board b in possibleMoves)
            {
                bool nextTurn = true;

                if(turnA)
                    nextTurn = false;

                Board beta = DoMiniMax(b, depth - 1, nextTurn);
                int betaEvaluation = -1 * beta.Evaluation(nextTurn);

                if (alphaEvalution < betaEvaluation)
                {
                    alphaEvalution = betaEvaluation;
                    alpha = b;

                    if (Game.Instance.ShowDebug)
                        Logger.AddLine(depth + " Beta: " + betaEvaluation);
                }
            }

            return alpha;
        }
    }
}
