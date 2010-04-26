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

            return null;
        }

        private Board DoAlphaBeta(Board node, int depth, bool turnA, int alphaEval, int betaEval)
        {
            //            function alphabeta(node, depth, α, β)         
            //    (* β represents previous player best choice - doesn't want it if α would worsen it *)
            //    if  depth = 0 or node is a terminal node
            //        return the heuristic value of node
            //    foreach child of node
            //        α := max(α, -alphabeta(child, depth-1, -β, -α))     
            //        (* use symmetry, -β becomes subsequently pruned α *)
            //        if β≤α
            //            break                             (* Beta cut-off *)
            //    return α

            //(* Initial call *)
            //alphabeta(origin, depth, -infinity, +infinity)


            if (depth <= 0)
                return node;
            if (node.IsWon())
                return node;

            int alphaEvalution = Int32.MinValue;
            Board alpha = null;

            List<Board> possibleMoves = node.GenerateMoves(turnA);

            foreach (Board b in possibleMoves)
            {
                bool nextTurn = true;
                if (turnA)
                    nextTurn = false;

                Board beta = DoAlphaBeta(b, depth--, nextTurn, -1 * alphaEval, -1 * b.Evaluation(nextTurn));
                if (alphaEvalution < (-1 * beta.Evaluation(nextTurn)))
                    alpha = beta;
            }

            return alpha;
        }
    }
}
