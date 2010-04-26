using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    class MiniMax : IAlgorithm
    {
        private int plieDepth;

        public MiniMax(int plieDepth)
        {
            this.plieDepth = plieDepth;
        }

        public Board NextMove(Board currentBoard)
        {

            Board next = Minimax(currentBoard, plieDepth, Game.Instance.GetTurn());

            return null;
        }

        private Board Minimax(Board node, int depth, bool turnA)
        {
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
                if(turnA)
                    nextTurn = false;

                Board beta = Minimax(b, depth--, nextTurn);
                if (alphaEvalution < (-1 * beta.Evaluation(nextTurn)))
                    alpha = beta;
            }

            return alpha;
        }
    }
}
