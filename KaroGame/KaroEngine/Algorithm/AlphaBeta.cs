using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    /// <summary>
    /// AlphaBeta algorithm
    /// </summary>
    class AlphaBeta : IAlgorithm
    {
        private int plieDepth;
        private bool moveOrdering;
        private bool transtable;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="plieDepth">Depth to plie</param>
        /// <param name="doMoveOrdering">Use move ordering</param>
        /// <param name="doTranstable">Use transposition table</param>
        public AlphaBeta(int plieDepth, bool doMoveOrdering, bool doTranstable)
        {
            this.plieDepth = plieDepth;
            this.moveOrdering = doMoveOrdering;
            this.transtable = doTranstable;
        }

        /// <summary>
        /// Does the next move
        /// </summary>
        /// <param name="currentBoard">Board to calculate best move</param>
        /// <returns>Best boardsituation</returns>
        public Board NextMove(Board currentBoard)
        {
            Board next = DoAlphaBeta(currentBoard, plieDepth, Game.Instance.GetTurn(), Int32.MinValue, Int32.MaxValue);
            Logger.AddLine("Board -> Evaluation value: " + next.Evaluation(Game.Instance.GetTurn()));
            return next;
        }

        /// <summary>
        /// Alpha Beta function
        /// </summary>
        /// <param name="node">'Current' board</param>
        /// <param name="depth">Plie depth</param>
        /// <param name="turnA">Which turn</param>
        /// <param name="alphaEval">Alpha evalution value</param>
        /// <param name="betaEval">Beta evalution value</param>
        /// <returns>Best boardsituation</returns>
        private Board DoAlphaBeta(Board node, int depth, bool turnA, int alphaEval, int betaEval)
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
                if (turnA)
                    nextTurn = false;

                // calculate beta & evalution
                Board beta = DoAlphaBeta(b, depth-1, nextTurn, -1 * alphaEval, -1 * b.Evaluation(nextTurn));
                int betaEvaluation = -1 * beta.Evaluation(nextTurn);

                // check if alpha is smaller then beta
                if (alphaEvalution < betaEvaluation)
                {
                    // alpha = beta
                    alphaEvalution = betaEvaluation;
                    alpha = b;

                    // show debug information
                    if(Game.Instance.ShowDebug)
                        Logger.AddLine(depth + " Beta: " + betaEvaluation);
                }

                // check if we can break
                if (betaEval <= alphaEval)
                    break;
            }

            // return best situation
            return alpha;
        }
    }
}
