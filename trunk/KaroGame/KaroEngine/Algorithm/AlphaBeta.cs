using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    class AlphaBeta : IAlgorithm
    {
        private int plieDepth;
        private bool moveOrdering;
        private bool transtable;

        public AlphaBeta(int plieDepth, bool doMoveOrdering, bool doTranstable)
        {
            this.plieDepth = plieDepth;
            this.moveOrdering = doMoveOrdering;
            this.transtable = doTranstable;
        }

        public Board NextMove(Board currentBoard)
        {
            Board next = DoAlphaBeta(currentBoard, plieDepth, Game.Instance.GetTurn(), Int32.MinValue, Int32.MaxValue);

            return next;
        }

        private Board DoAlphaBeta(Board node, int depth, bool turnA, int alphaEval, int betaEval)
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
                if (turnA)
                    nextTurn = false;

                Board beta = DoAlphaBeta(b, depth-1, nextTurn, -1 * alphaEval, -1 * b.Evaluation(nextTurn));
                int betaEvaluation = beta.Evaluation(nextTurn);
                
                if (alphaEvalution < (-1 * betaEvaluation))
                {
                    alphaEvalution = betaEvaluation;
                    alpha = b;
                }

                if (betaEval <= alphaEval)
                    break;
            }

            return alpha;
        }
    }
}
