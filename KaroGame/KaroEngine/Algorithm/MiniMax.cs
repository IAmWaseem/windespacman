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
            int valuelast = Int32.MinValue;
            List<Board> sameHighest = new List<Board>();
            List<Board> moves = currentBoard.GenerateMoves(Game.Instance.GetTurn());
            foreach (Board board in moves)
            {
                int value = 0;

                if(board.IsTileMoved)
                    value = MiniMaxFunction(board, plieDepth, Game.Instance.GetTurn(), Game.Instance.GetTurn());
                else
                    value = MiniMaxFunction(board, plieDepth, Game.Instance.GetTurn(), !Game.Instance.GetTurn()); 

                if (value > valuelast || !evaluationBoardSet)
                {
                    sameHighest = new List<Board>();
                    sameHighest.Add(board);
                    evaluationBoard = board;
                    valuelast = value;
                    evaluationBoardSet = true;
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
            if (IsEqual(evaluationBoard, currentBoard))
                throw new Exception();
            //Logger.AddLine("MiniMax: boards with same value: " + sameHighest.Count + " of " + moves.Count + " moves");
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

        private int MiniMaxFunction(Board node, int depth, bool isPlayerAMax, bool turnPlayerA)
        {
            if (depth <= 0 || node.IsWon())
            {
                return node.Evaluation(isPlayerAMax, turnPlayerA);
            }
            if (this.transtable)
            {
                if(table.IsCalculatedBefore(node, depth, isPlayerAMax, turnPlayerA))
                    return table.GetCalculatedValue(node, depth, isPlayerAMax, turnPlayerA);
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
                    if(board.IsTileMoved)
                        alpha = Math.Max(alpha, MiniMaxFunction(board, depth - 1, isPlayerAMax, !turnPlayerA));
                    else
                        alpha = Math.Max(alpha, MiniMaxFunction(board, depth - 1, isPlayerAMax, turnPlayerA));
                }
                else
                {
                    if(board.IsTileMoved)
                        alpha = Math.Max(alpha, -MiniMaxFunction(board, depth - 1, isPlayerAMax, !turnPlayerA));
                    else
                        alpha = Math.Max(alpha, -MiniMaxFunction(board, depth - 1, isPlayerAMax, turnPlayerA));
                }
            }
            if(this.transtable)
            {
                table.InsertCalculatedValue(node, depth, isPlayerAMax, !turnPlayerA, alpha);
            }

            return alpha;
        }
    }
}
