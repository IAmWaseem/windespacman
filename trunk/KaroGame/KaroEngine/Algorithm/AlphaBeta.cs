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
        private TranspositionTable table;

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
            if (this.transtable)
                table = new TranspositionTable(50000, 1600000);
        }

        /// <summary>
        /// Does the next move
        /// </summary>
        /// <param name="currentBoard">Board to calculate best move</param>
        /// <returns>Best boardsituation</returns>
        public Board NextMove(Board currentBoard)
        {
            Board evaluationBoard = new Board();
            int valuelast = Int32.MinValue;
            List<Board> sameHighest = new List<Board>();
            int alpha = Int32.MinValue;
            int beta = Int32.MaxValue;
            List<Board> moves = currentBoard.GenerateMoves(Game.Instance.GetTurn());
            foreach (Board board in moves)
            {
                int value = AlphaBetaFunction(board, plieDepth, Game.Instance.GetTurn(), !Game.Instance.GetTurn(), alpha, beta);
                if (value > valuelast)
                {
                    sameHighest = new List<Board>();
                    sameHighest.Add(board);
                    evaluationBoard = board;
                    valuelast = value;
                }
                else if (value == valuelast)
                {
                    sameHighest.Add(board);
                }
            }

            if (sameHighest.Count > 1 && sameHighest.Contains(evaluationBoard))
            {
                System.Random random = new System.Random();
                evaluationBoard = sameHighest[random.Next(0, sameHighest.Count - 1)];
                while (evaluationBoard.IsTileMoved)
                    evaluationBoard = sameHighest[random.Next(0, sameHighest.Count - 1)];
            }
            Logger.AddLine("AB: boards with same value: " + sameHighest.Count + " of " + moves.Count + " moves");
            Logger.AddLine("Board -> Evaluation value: " + evaluationBoard.Evaluation(Game.Instance.GetTurn()));
            return evaluationBoard;
        }


        private int AlphaBetaFunction(Board node, int depth, bool isPlayerAMax, bool turnPlayerA, int alphaEval, int betaEval)
        {
            if (depth <= 0 || node.IsWon())
            {
                if (this.transtable)
                    if (turnPlayerA == isPlayerAMax)
                        return table.EvaluationByHashing(node, turnPlayerA, depth);
                    else
                        return -1 * table.EvaluationByHashing(node, turnPlayerA, depth);
                else if (turnPlayerA == isPlayerAMax)
                    return node.Evaluation(turnPlayerA);
                else
                    return -1 * node.Evaluation(turnPlayerA);
            }

            List<Board> possibleMoves = node.GenerateMoves(turnPlayerA);


            if (moveOrdering)
                possibleMoves = Order(possibleMoves, (turnPlayerA == isPlayerAMax ? true : false), turnPlayerA);

            if (this.transtable)
                if (depth < table.DepthByHashing(node, turnPlayerA, depth))
                    return table.GetHashObject(node.BoardHashvalue % table.GetTableSize()).value;

            turnPlayerA = !turnPlayerA;
            foreach (Board board in possibleMoves)
            {
                bool turnPlayerB = turnPlayerA;
                if (!board.IsTileMoved)
                    turnPlayerB = !turnPlayerB;

                if (this.transtable)
                    table.DepthByHashing(node, turnPlayerA, depth - 1);

                alphaEval = Math.Max(alphaEval, -AlphaBetaFunction(board, depth - 1, isPlayerAMax, turnPlayerB, -betaEval, -alphaEval));

                if (betaEval <= alphaEval)
                    return alphaEval;
            }


            return alphaEval;
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
            {
                node.EvaluationValue = node.Evaluation(turnA);
                return node;
            }

            // if won, we also can quit
            if (node.IsWon())
            {
                node.EvaluationValue = node.Evaluation(turnA);
                return node;
            }

            // set alpha
            Board alpha = node;
            alpha.EvaluationValue = alphaEval;

            // generate moves
            List<Board> possibleMoves = node.GenerateMoves(turnA);

            if (moveOrdering)
                possibleMoves = Order(possibleMoves, (Game.Instance.GetTurn() == turnA ? true : false), turnA);

            // iterate trough moves
            foreach (Board b in possibleMoves)
            {
                // switch turn if needed
                bool nextTurn = true;
                if (turnA)
                    nextTurn = false;

                // calculate beta & evalution
                Board beta = DoAlphaBeta(b, depth - 1, nextTurn, -1 * alphaEval, -1 * b.Evaluation(nextTurn));
                int betaEvaluation = -1 * beta.EvaluationValue;

                // check if alpha is smaller then beta
                if (alpha.EvaluationValue < betaEvaluation)
                {
                    // alpha = beta
                    alpha.EvaluationValue = betaEvaluation;
                    alpha = b;

                    // show debug information
                    if (Game.Instance.ShowDebug)
                        Logger.AddLine(depth + " Alpha set: " + alpha.EvaluationValue);
                }

                // check if we can break
                if (betaEval <= alpha.EvaluationValue)
                    break;
            }

            // return best situation
            return alpha;
        }

        /// <summary>
        /// Order the moves, descending for max player,
        /// ascending for min player
        /// </summary>
        /// <param name="moves">unordered moves</param>
        /// <param name="descending">true->hoog naar laag</param>
        /// <param name="isRed">necessary for evaluation function</param>
        /// <returns></returns>
        private List<Board> Order(List<Board> moves, Boolean descending, Boolean isRed)
        {
            if (descending)
                return moves.OrderByDescending(t => t.EvaluationValue).ToList();

            return moves.OrderBy(t => t.EvaluationValue).ToList();
        }
    }
}
