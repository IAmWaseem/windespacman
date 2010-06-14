using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    /// <summary>
    /// Minimax algorithm
    /// </summary>
    class MiniMax : IAlgorithm
    {
        private int plieDepth;
        private bool transtable;
        private TranspositionTable table;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="plieDepth">Depth to plie</param>
        /// <param name="doTranstable">Use transposition table</param>
        public MiniMax(int plieDepth, bool doTranstable)
        {
            this.plieDepth = plieDepth;
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
            List<Board> moves = currentBoard.GenerateMoves(Game.Instance.GetTurn());
            foreach (Board board in moves)
            {
                int value = 0;
                if (this.transtable)
                {
                    /**TODO**/
                }
                else
                {
                    if(board.IsTileMoved)
                        value = MiniMaxFunction(board, plieDepth, Game.Instance.GetTurn(), Game.Instance.GetTurn());
                    else
                        value = MiniMaxFunction(board, plieDepth, Game.Instance.GetTurn(), !Game.Instance.GetTurn()); 
                }

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
            //Logger.AddLine("MiniMax: boards with same value: " + sameHighest.Count + " of " + moves.Count + " moves");
            Logger.AddLine("Board -> Evaluation value: " + evaluationBoard.Evaluation(Game.Instance.GetTurn(), Game.Instance.GetTurn()));
            return evaluationBoard;
        }

        private int MiniMaxFunction(Board node, int depth, bool isPlayerAMax, bool turnPlayerA)
        {
            if (depth <= 0 || node.IsWon())
            {
                return node.Evaluation(isPlayerAMax, turnPlayerA);
            }

            int alpha = Int32.MinValue;

            List<Board> possibleMoves = node.GenerateMoves(turnPlayerA);

            turnPlayerA = !turnPlayerA;
            
            if (possibleMoves.Count == 0)
                throw new Exception();

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
                            alpha = Math.Max(alpha, MiniMaxFunction(board, depth - 1, isPlayerAMax, !turnPlayerA));
                        else
                            alpha = Math.Max(alpha, MiniMaxFunction(board, depth - 1, isPlayerAMax, turnPlayerA));
                    }
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
                            alpha = Math.Max(alpha, -MiniMaxFunction(board, depth - 1, isPlayerAMax, !turnPlayerA));
                        else
                            alpha = Math.Max(alpha, -MiniMaxFunction(board, depth - 1, isPlayerAMax, turnPlayerA));
                    }
                }
            }

            return alpha;
        }
    }
}
