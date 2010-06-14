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
            evaluationBoard.BoardSituation[0, 0] = BoardPosition.RedTail;
            int valuelast = Int32.MinValue;
            List<Board> sameHighest = new List<Board>();
            int alpha = Int32.MinValue + 10;
            int beta = Int32.MaxValue;
            List<Board> moves = currentBoard.GenerateMoves(Game.Instance.GetTurn());
            foreach (Board board in moves)
            {
                if (this.transtable)
                {
                    /** TODO**/
                }
                else
                {
                    if (board.IsTileMoved)
                        alpha = AlphaBetaFunction(board, plieDepth, Game.Instance.GetTurn(), Game.Instance.GetTurn(), alpha, beta);
                    else
                        alpha = AlphaBetaFunction(board, plieDepth, Game.Instance.GetTurn(), !Game.Instance.GetTurn(), alpha, beta);
                }
                if (alpha > valuelast)
                {
                    sameHighest = new List<Board>();
                    sameHighest.Add(board);
                    evaluationBoard = board;
                    valuelast = alpha;
                }
                else if (alpha == valuelast)
                {
                    sameHighest.Add(board);
                }
            }

            if (sameHighest.Count > 1 && sameHighest.Contains(evaluationBoard))
            {
                int highest = Int32.MinValue;
                List<Board> highestOfTheHighest = new List<Board>();
                foreach (Board board in sameHighest)
                {
                    int eval = Int32.MinValue;
                    if(board.IsTileMoved)
                        eval = board.Evaluation(Game.Instance.GetTurn(), Game.Instance.GetTurn());
                    else
                        eval = board.Evaluation(Game.Instance.GetTurn(), !Game.Instance.GetTurn());
                    if (eval > highest)
                    {
                        highest = eval;
                        highestOfTheHighest = new List<Board>();
                        highestOfTheHighest.Add(board);
                    }
                    else if (eval == highest)
                        highestOfTheHighest.Add(board);
                }
                System.Random random = new System.Random();
                evaluationBoard = highestOfTheHighest[random.Next(0, highestOfTheHighest.Count - 1)];
            }
            Logger.AddLine("AB: boards with same value: " + sameHighest.Count + " of " + moves.Count + " moves");
            Logger.AddLine("Board -> Evaluation value: " + evaluationBoard.Evaluation(Game.Instance.GetTurn(), Game.Instance.GetTurn()));
            return evaluationBoard;
        }


        private int AlphaBetaFunction(Board node, int depth, bool isPlayerAMax, bool turnPlayerA, int alphaEval, int betaEval)
        {
            if (node.IsWon() || depth <= 0)
            {
                return node.Evaluation(isPlayerAMax, turnPlayerA);
            }

            int value = Int32.MinValue;

            List<Board> possibleMoves = node.GenerateMoves(turnPlayerA);

            turnPlayerA = !turnPlayerA;

            if (isPlayerAMax == turnPlayerA)
                possibleMoves = Order(possibleMoves, true, true);
            else
                possibleMoves = Order(possibleMoves, false, false);

            foreach (Board board in possibleMoves)
            {
                if (turnPlayerA == isPlayerAMax)
                {
                    if (this.transtable)
                    {
                        /**TODO**/
                    }
                    else
                    {
                        if(board.IsTileMoved)
                            value = Math.Max(value, AlphaBetaFunction(board, depth - 1, isPlayerAMax, !turnPlayerA, alphaEval, betaEval));
                        else
                            value = Math.Max(value, AlphaBetaFunction(board, depth - 1, isPlayerAMax, turnPlayerA, alphaEval, betaEval));
                    }
                    alphaEval = Math.Max(value, alphaEval);
                    if (betaEval <= alphaEval)
                        return alphaEval;
                }
                else
                {
                    if (this.transtable)
                    {
                        /**TODO**/
                    }
                    else
                    {
                        if(board.IsTileMoved)
                            value = Math.Max(value, -AlphaBetaFunction(board, depth - 1, isPlayerAMax, !turnPlayerA, alphaEval, betaEval));
                        else
                            value = Math.Max(value, -AlphaBetaFunction(board, depth - 1, isPlayerAMax, turnPlayerA, alphaEval, betaEval));
                    }
                    betaEval = Math.Min(value, betaEval);
                    if (betaEval <= alphaEval)
                        return betaEval;
                }
            }

            return value;

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
