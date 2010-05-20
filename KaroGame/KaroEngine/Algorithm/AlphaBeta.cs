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
            Console.Out.WriteLine("Num moves: " + moves.Count);
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
                int highest = Int32.MinValue;
                List<Board> highestOfTheHighest = new List<Board>();
                foreach (Board board in sameHighest)
                {
                    int eval = board.Evaluation(Game.Instance.GetTurn(), !Game.Instance.GetTurn());
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
            if (depth <= 0 || node.IsWon())
            {
                if (this.transtable)
                    return table.EvaluationByHashing(node, isPlayerAMax, turnPlayerA, depth);
                else
                    return node.Evaluation(isPlayerAMax, turnPlayerA);
            }

            List<Board> possibleMoves = node.GenerateMoves(turnPlayerA);


            if (moveOrdering)
                possibleMoves = Order(possibleMoves, (turnPlayerA == isPlayerAMax ? true : false), turnPlayerA);

            if (this.transtable)
                if (depth < table.DepthByHashing(node, isPlayerAMax, turnPlayerA, depth))
                    return table.GetHashObject(node.BoardHashvalue % table.GetTableSize()).value;

            turnPlayerA = !turnPlayerA;

            if (turnPlayerA != isPlayerAMax)
            {
                foreach (Board board in possibleMoves)
                {
                    bool turnPlayerB = turnPlayerA;
                    if (!board.IsTileMoved)
                        turnPlayerB = !turnPlayerB;

                    if (this.transtable)
                        table.DepthByHashing(node, isPlayerAMax, turnPlayerA, depth - 1);

                    alphaEval = Math.Max(alphaEval, AlphaBetaFunction(board, depth - 1, isPlayerAMax, turnPlayerB, alphaEval, betaEval));

                    if (betaEval <= alphaEval)
                        return alphaEval;
                }

                return alphaEval;
            }
            else
            {
                foreach (Board board in possibleMoves)
                {
                    bool turnPlayerB = turnPlayerA;
                    if (!board.IsTileMoved)
                        turnPlayerB = !turnPlayerB;

                    if (this.transtable)
                        table.DepthByHashing(node, isPlayerAMax, turnPlayerA, depth - 1);

                    betaEval = Math.Min(betaEval, AlphaBetaFunction(board, depth - 1, isPlayerAMax, turnPlayerB, alphaEval, betaEval));

                    if (betaEval <= alphaEval)
                        return betaEval;
                }

                return betaEval;
            }
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
