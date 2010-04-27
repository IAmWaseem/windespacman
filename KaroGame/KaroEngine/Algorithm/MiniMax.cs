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
            // if depth has reached zero, quit
            if (depth <= 0)
                return node;

            // if won, we also can quit
            if (node.IsWon())
                return node;

            // set alpha
            Board alpha = node;
            int alphaEvalution = Int32.MinValue;

            // generate moves
            List<Board> possibleMoves = node.GenerateMoves(turnA);

            // iterate trough moves
            foreach (Board b in possibleMoves)
            {
                // switch turn if needed
                bool nextTurn = true;
                if(turnA)
                    nextTurn = false;

                // calculate beta & evalution
                Board beta = DoMiniMax(b, depth - 1, nextTurn);
                int betaEvaluation = -1 * beta.Evaluation(nextTurn);

                // check if alpha is smaller then beta
                if (alphaEvalution < betaEvaluation)
                {
                    // alpha = beta
                    alphaEvalution = betaEvaluation;
                    alpha = b;

                    // show debug information
                    if (Game.Instance.ShowDebug)
                        Logger.AddLine(depth + " Beta: " + betaEvaluation);
                }
            }

            return alpha;
        }
    }
}
