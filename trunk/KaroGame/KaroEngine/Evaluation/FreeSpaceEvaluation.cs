using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    class FreeSpaceEvaluation : IEvaluation
    {
        /// <summary>
        /// Evaluates the board
        /// </summary>
        /// <param name="board">Provided board</param>
        /// <param name="isRed">Is player red's turn</param>
        /// <returns></returns>
        public int Evaluate(Board board, bool isRed)
        {
            // evaluation value
            int lEvaluationValue = 0;

            // starttime
            DateTime lStartTime = DateTime.Now;

            // if won, we don't have to do things
            if (board.IsWon())
                lEvaluationValue = 1000000;
            else
            {
                if (board.IsTileMoved)
                {
                    List<Board> nextMoves = board.GenerateMoves(isRed);
                    if (nextMoves.Count == 1)
                    {
                        return nextMoves[0].Evaluation(isRed);
                    }
                }

                // temp values
                int lEmptySpots = 0;
                int lOwnHead = 0;

                // temp value for storing the to be checked head position
                BoardPosition lHead = BoardPosition.RedHead;
                if (!isRed)
                    lHead = BoardPosition.WhiteHead;

                // loop trough board
                for (int x = 0; x < 21; x++)
                {
                    for (int y = 0; y < 20; y++)
                    {
                        //if (boardPositions[x, y] == lHead)
                        //    lOwnHead++;

                        #region "Check if piece belongs to current player"

                        bool lCheck = false;

                        if (board.BoardSituation[x, y] != BoardPosition.Empty && board.BoardSituation[x, y] != BoardPosition.Tile)
                        {
                            if (isRed)
                            {
                                if (board.BoardSituation[x, y] == BoardPosition.RedHead || board.BoardSituation[x, y] == BoardPosition.RedTail)
                                    lCheck = true;
                            }
                            else if (!isRed)
                            {
                                if (board.BoardSituation[x, y] == BoardPosition.WhiteHead || board.BoardSituation[x, y] == BoardPosition.WhiteTail)
                                    lCheck = true;
                            }
                        }

                        #endregion

                        if (lCheck)
                        {
                            #region "Left Column"

                            // x - -
                            // x - -
                            // x - -
                            if (x > 0)
                            {
                                // x - -
                                // - - -
                                // - - -
                                if (y > 0)
                                {
                                    if (board.BoardSituation[x - 1, y - 1] == BoardPosition.Tile)
                                        lEmptySpots++;
                                    else if (board.BoardSituation[x - 1, y - 1] == lHead)
                                        lOwnHead++;
                                }

                                // - - -
                                // x - -
                                // - - -
                                if (board.BoardSituation[x - 1, y] == BoardPosition.Tile)
                                    lEmptySpots++;
                                else if (board.BoardSituation[x - 1, y] == lHead)
                                    lOwnHead++;

                                // - - -
                                // - - -
                                // x - -
                                if (y < (20 - 1))
                                {
                                    if (board.BoardSituation[x - 1, y + 1] == BoardPosition.Tile)
                                        lEmptySpots++;
                                    else if (board.BoardSituation[x - 1, y + 1] == lHead)
                                        lOwnHead++;
                                }
                            }

                            #endregion

                            #region "Middle column"

                            // - x -
                            // - x -
                            // - x -

                            // - x -
                            // - - -
                            // - - -
                            if (y > 0)
                            {
                                if (board.BoardSituation[x, y - 1] == BoardPosition.Tile)
                                    lEmptySpots++;
                                else if (board.BoardSituation[x, y - 1] == lHead)
                                    lOwnHead++;
                            }

                            // - - -
                            // - x -
                            // - - -
                            // needs no check, is this position

                            // - - -
                            // - - -
                            // - x -
                            if (y < (20 - 1))
                            {
                                if (board.BoardSituation[x, y + 1] == BoardPosition.Tile)
                                    lEmptySpots++;
                                else if (board.BoardSituation[x, y + 1] == lHead)
                                    lOwnHead++;
                            }

                            #endregion

                            #region "Right column"

                            // - - x
                            // - - x
                            // - - x
                            if (x < (21 - 1))
                            {
                                // - - x
                                // - - -
                                // - - -
                                if (y > 0)
                                {
                                    if (board.BoardSituation[x + 1, y - 1] == BoardPosition.Tile)
                                        lEmptySpots++;
                                    else if (board.BoardSituation[x + 1, y - 1] == lHead)
                                        lOwnHead++;
                                }

                                // - - -
                                // - - x
                                // - - -
                                if (board.BoardSituation[x + 1, y] == BoardPosition.Tile)
                                    lEmptySpots++;
                                else if (board.BoardSituation[x + 1, y] == lHead)
                                    lOwnHead++;

                                // - - -
                                // - - -
                                // - - x
                                if (y < (20 - 1))
                                {
                                    if (board.BoardSituation[x + 1, y + 1] == BoardPosition.Tile)
                                        lEmptySpots++;
                                    else if (board.BoardSituation[x + 1, y + 1] == lHead)
                                        lOwnHead++;
                                }
                            }

                            #endregion
                        }
                    }
                }

                // calculate evalution value
                int evalAdd = 0;
                if (Game.Instance.CurrentPlayerNumPieces() > 0)
                {
                    //evalAdd = (lEmptySpots * (lOwnHead / Game.Instance.CurrentPlayerNumPieces()));
                    evalAdd = lEmptySpots * (lOwnHead ^ 2);
                }

                lEvaluationValue = lEmptySpots + evalAdd;
            }

            #region "debug"
            //DateTime lStopTime = DateTime.Now;
            //TimeSpan lDiff = lStopTime - lStartTime;

            //Logger.AddLine("Board -> Evaluation value: " + lEvaluationValue + " (calculated in: " + lDiff.TotalMilliseconds + " ms)");
            #endregion

            return lEvaluationValue;
        }
    }
}
