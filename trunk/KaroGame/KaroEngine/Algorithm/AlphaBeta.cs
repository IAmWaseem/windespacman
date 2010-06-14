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
                table = new TranspositionTable();
        }

        /// <summary>
        /// Does the next move
        /// </summary>
        /// <param name="currentBoard">Board to calculate best move</param>
        /// <returns>Best boardsituation</returns>
        public Board NextMove(Board currentBoard)
        {
            Board evaluationBoard = new Board();
            bool evaluationBoardSet = false;
            evaluationBoard.BoardSituation[0, 0] = BoardPosition.RedTail;
            int valuelast = Int32.MinValue;
            List<Board> sameHighest = new List<Board>();
            int alpha = Int32.MinValue + 10;
            int beta = Int32.MaxValue;
            List<Board> moves = currentBoard.GenerateMoves(Game.Instance.GetTurn());
            foreach (Board board in moves)
            {
                if (board.IsTileMoved)
                    alpha = AlphaBetaFunction(board, plieDepth, Game.Instance.GetTurn(), Game.Instance.GetTurn(), alpha, beta);
                else
                    alpha = AlphaBetaFunction(board, plieDepth, Game.Instance.GetTurn(), !Game.Instance.GetTurn(), alpha, beta);

                if (alpha > valuelast || !evaluationBoardSet)
                {
                    sameHighest = new List<Board>();
                    sameHighest.Add(board);
                    evaluationBoard = board;
                    valuelast = alpha;
                    evaluationBoardSet = true;
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
            if (IsEqual(evaluationBoard, currentBoard))
                throw new Exception();

            Logger.AddLine("AB: boards with same value: " + sameHighest.Count + " of " + moves.Count + " moves");
            Logger.AddLine("Board -> Evaluation value: " + evaluationBoard.Evaluation(Game.Instance.GetTurn(), Game.Instance.GetTurn()));
            return evaluationBoard;
        }

        private bool IsEqual(Board boardA, Board boardB)
        {
            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    if (boardA.BoardSituation[x, y] != boardB.BoardSituation[x, y])
                        return false;
                }
            }

            return true;
        }


        private int AlphaBetaFunction(Board node, int depth, bool isPlayerAMax, bool turnPlayerA, int alphaEval, int betaEval)
        {
            if (node.IsWon() || depth <= 0)
            {
                return node.Evaluation(isPlayerAMax, turnPlayerA);
            }
            if (this.transtable)
            {
                if (table.IsCalculatedBefore(node, depth, isPlayerAMax, turnPlayerA))
                    return table.GetCalculatedValue(node, depth, isPlayerAMax, turnPlayerA);
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

                    if(board.IsTileMoved)
                        value = Math.Max(value, AlphaBetaFunction(board, depth - 1, isPlayerAMax, !turnPlayerA, alphaEval, betaEval));
                    else
                        value = Math.Max(value, AlphaBetaFunction(board, depth - 1, isPlayerAMax, turnPlayerA, alphaEval, betaEval));

                    alphaEval = Math.Max(value, alphaEval);
                    if (betaEval <= alphaEval)
                    {
                        if (this.transtable)
                            table.InsertCalculatedValue(node, depth, isPlayerAMax, !turnPlayerA, alphaEval);
                        return alphaEval;
                    }
                }
                else
                {

                    if(board.IsTileMoved)
                        value = Math.Max(value, -AlphaBetaFunction(board, depth - 1, isPlayerAMax, !turnPlayerA, alphaEval, betaEval));
                    else
                        value = Math.Max(value, -AlphaBetaFunction(board, depth - 1, isPlayerAMax, turnPlayerA, alphaEval, betaEval));

                    betaEval = Math.Min(value, betaEval);
                    if (betaEval <= alphaEval)
                    {
                        if (this.transtable)
                            table.InsertCalculatedValue(node, depth, isPlayerAMax, !turnPlayerA, betaEval);
                        return betaEval;
                    }
                }
            }

            if (this.transtable)
                table.InsertCalculatedValue(node, depth, isPlayerAMax, !turnPlayerA, value);

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
