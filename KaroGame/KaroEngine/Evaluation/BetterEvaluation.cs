using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{


    class BetterEvaluation : IEvaluation
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
                lEvaluationValue = 140;
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
            }

            return lEvaluationValue;
        }

        private List<PieceSituation> FindSituations(BoardPosition[,] boardSituation)
        {
            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    BoardPosition current = boardSituation[x, y];
                }
            }


            return new List<PieceSituation>();
        }
    }

    enum PieceSituation
    {
        MaxFourHeads = 0,
        MaxThreeHeads = 1,
        MaxThreeHeadsWithSpace = 2,
        MaxThreeHeadsBlocked = 3,
        MinThreeHeadsBlocked = 4,
        MinThreeHeadsWithSpace = 5,
        MinThreeHeads = 6,
        MinFourHeads = 7
    }
}
