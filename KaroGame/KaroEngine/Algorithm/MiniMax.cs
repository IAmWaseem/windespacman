﻿using System;
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="plieDepth">Depth to plie</param>
        /// <param name="doTranstable">Use transposition table</param>
        public MiniMax(int plieDepth, bool doTranstable)
        {
            this.plieDepth = plieDepth;
            this.transtable = doTranstable;
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

            foreach (Board board in currentBoard.GenerateMoves(Game.Instance.GetTurn()))
            {
                int value = MiniMaxFunction(board, plieDepth, Game.Instance.GetTurn());
                if(value>valuelast)
                {
                    evaluationBoard = board;
                    valuelast = value;
                }
            }
            Logger.AddLine("Board -> Evaluation value: " + evaluationBoard.Evaluation(Game.Instance.GetTurn()));
            return evaluationBoard;
        }

        private int MiniMaxFunction(Board node, int depth, bool turnA)
        {
            if (depth <= 0 || node.IsWon())
            {
                return node.Evaluation(turnA);
            }
            
            int alpha = Int32.MinValue;
            List<Board> possibleMoves = node.GenerateMoves(turnA);

            foreach (Board board in possibleMoves)
            {
                alpha = Math.Max(alpha, MiniMaxFunction(board, depth-1, turnA));
            }

            return alpha;
        }


        /// <summary>
        /// MiniMax function
        /// </summary>
        /// <param name="node">'Current' board</param>
        /// <param name="depth">Plie depth</param>
        /// <param name="turnA">Which turn</param>
        /// <returns>Best board situation</returns>
        private Board DoMiniMax(Board node, int depth, bool turnA)
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
            alpha.EvaluationValue = Int32.MinValue;

            // generate moves
            List<Board> possibleMoves = node.GenerateMoves(turnA);

            // iterate trough moves
            foreach (Board b in possibleMoves)
            {
                // switch turn if needed
                bool nextTurn = true;
                if(turnA)
                    nextTurn = false;

                // calculate beta & evalution
                Board beta = DoMiniMax(b, depth - 1, nextTurn);
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
            }

            // return best board situation
            return alpha;
        }
    }
}
