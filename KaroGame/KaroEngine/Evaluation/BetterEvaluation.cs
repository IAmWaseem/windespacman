using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;

namespace Karo
{
    class BetterEvaluation
    {
        /// <summary>
        /// Evaluates the board
        /// </summary>
        /// <param name="board">Provided board</param>
        /// <param name="isRed">Is player red's turn</param>
        /// <returns></returns>
        public static int Evaluate(Board board, bool isPlayerAMax, bool turnPlayerA )
        {
            // evaluation value
            int lEvaluationValue = 0;

            // starttime
            DateTime lStartTime = DateTime.Now;

            // if won, we don't have to do things
            if (board.IsWon())
                if (isPlayerAMax == turnPlayerA)
                    lEvaluationValue = -140;
                else
                    lEvaluationValue = 140;
            else
            {
                // check if tile moved, if so, return evaluation value of next board of tile moved
                if (board.IsTileMoved)
                {
                    List<Board> nextMoves = board.GenerateMoves(turnPlayerA);
                    if (nextMoves.Count == 1)
                    {
                        return nextMoves[0].Evaluation(isPlayerAMax, !turnPlayerA);
                    }
                }
                else
                {
                    // tiles not moves, so we can continue here
                    List<PieceSituation> goodSituations = FindSituations(board.BoardSituation, turnPlayerA);
                    List<PieceSituation> badSituations = FindSituations(board.BoardSituation, !turnPlayerA);
                    
                    if (goodSituations.Count > 0)
                    {
                        IOrderedEnumerable<PieceSituation> orderedGood = from e in goodSituations orderby e select e;
                        if (orderedGood.First() == PieceSituation.ThreeHeads)
                            lEvaluationValue = 100;
                        else if (orderedGood.First() == PieceSituation.ThreeHeadsWithSpace)
                            lEvaluationValue = 60;
                        else if (orderedGood.First() == PieceSituation.ThreeHeadsBlocked)
                            lEvaluationValue = 20;
                    }
                    else if (badSituations.Count > 0)
                    {
                        IOrderedEnumerable<PieceSituation> orderedBad = from e in badSituations orderby e select e;
                        if (orderedBad.First() == PieceSituation.ThreeHeads)
                            lEvaluationValue = -100;
                        else if (orderedBad.First() == PieceSituation.ThreeHeadsWithSpace)
                            lEvaluationValue = -60;
                        else if (orderedBad.First() == PieceSituation.ThreeHeadsBlocked)
                            lEvaluationValue = -20;
                    }
                }
            }

            // add amount of head times 5 to eval value
            int addToEval = 0;

            if (turnPlayerA)
                addToEval += 5 * board.RedHeads;
            else
                addToEval += 5 * board.WhiteHeads;

            return (lEvaluationValue + addToEval);
        }

        private static List<PieceSituation> FindSituations(BoardPosition[,] boardSituation, bool isRed)
        {
            BoardPosition lookFor = BoardPosition.RedHead;
            if (!isRed)
                lookFor = BoardPosition.WhiteHead;

            List<PieceSituation> situations = new List<PieceSituation>();

            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    BoardPosition current = boardSituation[x, y];

                    if (current == lookFor)
                    {
                        #region LeftLeft

                        // left left
                        if (x > 0)
                        {
                            // check if neighbour is also head
                            if (boardSituation[x - 1, y] == lookFor)
                            {
                                // check if we can move left
                                if (x > 1)
                                {
                                    if (boardSituation[x - 2, y] == lookFor)
                                    {
                                        // if neighbour is also head
                                        // three heads on a row
                                        situations.Add(PieceSituation.ThreeHeads);
                                    }
                                    else if (boardSituation[x - 2, y] != BoardPosition.Empty)
                                    {
                                        // space is not nothing, but also not a head of yourself

                                        if (boardSituation[x - 2, y] == BoardPosition.Tile)
                                        {
                                            if (x > 2)
                                            {
                                                // if next is tile, then we can have tree with space
                                                if (boardSituation[x - 3, y] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                            }
                                        }
                                        else
                                        {
                                            if (x > 2)
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x - 3, y] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsBlocked);
                                            }
                                        }
                                    }
                                }
                            }
                            else if (boardSituation[x - 1, y] != BoardPosition.Empty)
                            {
                                // space next to piece is not nothing or not a head of himself
                                if (x > 2)
                                {
                                    if (boardSituation[x - 1, y] == BoardPosition.Tile)
                                    {
                                        // space is tile
                                        if (boardSituation[x - 2, y] == lookFor)
                                        {

                                            if (x > 2)
                                            {
                                                // if next two spaces are head of himself then max tree with space
                                                if (boardSituation[x - 3, y] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        // space was blocked
                                        if (boardSituation[x - 2, y] == lookFor)
                                        {
                                            if (x > 2)
                                            {
                                                // if next two spaces are head of himself then max tree with blocked point
                                                if (boardSituation[x - 3, y] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsBlocked);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        #endregion

                        #region RightRight

                        // right right
                        if (x < 21)
                        {
                            // check if neighbour is also head
                            if (boardSituation[x + 1, y] == lookFor)
                            {
                                // check if we can move left
                                if (x < 20)
                                {
                                    if (boardSituation[x + 2, y] == lookFor)
                                    {
                                        // if neighbour is also head
                                        // three heads on a row
                                        situations.Add(PieceSituation.ThreeHeads);
                                    }
                                    else if (boardSituation[x + 2, y] != BoardPosition.Empty)
                                    {
                                        // space is not nothing, but also not a head of yourself

                                        if (boardSituation[x + 2, y] == BoardPosition.Tile)
                                        {
                                            if (x < 19)
                                            {
                                                // if next is tile, then we can have tree with space
                                                if (boardSituation[x + 3, y] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                            }
                                        }
                                        else
                                        {
                                            if (x < 19)
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x + 3, y] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsBlocked);
                                            }
                                        }
                                    }
                                }
                            }
                            else if (boardSituation[x + 1, y] != BoardPosition.Empty)
                            {
                                // space next to piece is not nothing or not a head of himself
                                if (x < 20)
                                {
                                    if (boardSituation[x + 1, y] == BoardPosition.Tile)
                                    {
                                        // space is tile
                                        if (boardSituation[x + 2, y] == lookFor)
                                        {
                                            if (x < 19)
                                            {
                                                // if next two spaces are head of himself then max tree with space
                                                if (boardSituation[x + 3, y] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        // space was blocked
                                        if (boardSituation[x + 2, y] == lookFor)
                                        {
                                            if (x < 19)
                                            {
                                                // if next two spaces are head of himself then max tree with blocked point
                                                if (boardSituation[x + 3, y] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsBlocked);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        #endregion

                        #region UpUp

                        // up up
                        if (y > 0)
                        {
                            // check if neighbour is also head
                            if (boardSituation[x, y - 1] == lookFor)
                            {
                                // check if we can move left
                                if (y > 1)
                                {
                                    if (boardSituation[x, y - 2] == lookFor)
                                    {
                                        // if neighbour is also head
                                        // three heads on a row
                                        situations.Add(PieceSituation.ThreeHeads);
                                    }
                                    else if (boardSituation[x, y - 2] != BoardPosition.Empty)
                                    {
                                        // space is not nothing, but also not a head of yourself
                                        if (y > 2)
                                        {
                                            if (boardSituation[x, y - 2] == BoardPosition.Tile)
                                            {
                                                // if next is tile, then we can have tree with space
                                                if (boardSituation[x, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                            }
                                            else
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsBlocked);
                                            }
                                        }
                                    }
                                }
                            }
                            else if (boardSituation[x, y - 2] != BoardPosition.Empty)
                            {
                                // space next to piece is not nothing or not a head of himself
                                if (y > 2)
                                {
                                    if (boardSituation[x, y - 1] == BoardPosition.Tile)
                                    {
                                        // space is tile
                                        if (boardSituation[x, y - 2] == lookFor)
                                        {
                                            // if next two spaces are head of himself then max tree with space
                                            if (boardSituation[x, y - 3] == lookFor)
                                                situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                        }
                                    }
                                    else
                                    {
                                        // space was blocked
                                        if (boardSituation[x, y - 2] == lookFor)
                                        {
                                            // if next two spaces are head of himself then max tree with blocked point
                                            if (boardSituation[x, y - 3] == lookFor)
                                                situations.Add(PieceSituation.ThreeHeadsBlocked);
                                        }
                                    }
                                }
                            }
                        }

                        #endregion

                        #region DownDown

                        // down down
                        if (y < 19)
                        {
                            // check if neighbour is also head
                            if (boardSituation[x, y + 1] == lookFor)
                            {
                                // check if we can move left
                                if (y < 18)
                                {
                                    if (boardSituation[x, y + 2] == lookFor)
                                    {
                                        // if neighbour is also head
                                        // three heads on a row
                                        situations.Add(PieceSituation.ThreeHeads);
                                    }
                                    else if (boardSituation[x, y + 2] != BoardPosition.Empty)
                                    {
                                        // space is not nothing, but also not a head of yourself
                                        if (y < 17)
                                        {
                                            if (boardSituation[x, y + 2] == BoardPosition.Tile)
                                            {
                                                // if next is tile, then we can have tree with space
                                                if (boardSituation[x, y + 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                            }
                                            else
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x, y + 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsBlocked);
                                            }
                                        }
                                    }
                                }
                            }
                            else if (boardSituation[x, y + 2] != BoardPosition.Empty)
                            {
                                // space next to piece is not nothing or not a head of himself
                                if (y < 17)
                                {
                                    if (boardSituation[x, y + 1] == BoardPosition.Tile)
                                    {
                                        // space is tile
                                        if (boardSituation[x, y + 2] == lookFor)
                                        {
                                            // if next two spaces are head of himself then max tree with space
                                            if (boardSituation[x, y + 3] == lookFor)
                                                situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                        }
                                    }
                                    else
                                    {
                                        // space was blocked
                                        if (boardSituation[x, y + 2] == lookFor)
                                        {
                                            // if next two spaces are head of himself then max tree with blocked point
                                            if (boardSituation[x, y + 3] == lookFor)
                                                situations.Add(PieceSituation.ThreeHeadsBlocked);
                                        }
                                    }
                                }
                            }
                        }

                        #endregion

                        #region UpLeft

                        // up right
                        if (x > 0 && y > 0)
                        {
                            // check if neighbour is also head
                            if (boardSituation[x - 1, y - 1] == lookFor)
                            {
                                // check if we can move left
                                if (x >1 && y > 1)
                                {
                                    if (boardSituation[x - 2, y - 2] == lookFor)
                                    {
                                        // if neighbour is also head
                                        // three heads on a row
                                        situations.Add(PieceSituation.ThreeHeads);
                                    }
                                    else if (boardSituation[x - 2, y - 2] != BoardPosition.Empty)
                                    {
                                        // space is not nothing, but also not a head of yourself

                                        if (boardSituation[x - 2, y - 2] == BoardPosition.Tile)
                                        {
                                            if (x >2 && y > 2)
                                            {
                                                // if next is tile, then we can have tree with space
                                                if (boardSituation[x - 3, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                            }
                                        }
                                        else
                                        {
                                            if (x >2 && y > 2)
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x - 3, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsBlocked);
                                            }
                                        }
                                    }
                                }
                            }
                            else if (boardSituation[x - 1, y - 1] != BoardPosition.Empty)
                            {
                                // space next to piece is not nothing or not a head of himself
                                if (x > 1 && y > 1)
                                {
                                    if (boardSituation[x - 1, y - 1] == BoardPosition.Tile)
                                    {
                                        // space is tile
                                        if (boardSituation[x - 2, y - 2] == lookFor)
                                        {
                                            if (x > 2 && y > 2)
                                            {
                                                // if next two spaces are head of himself then max tree with space
                                                if (boardSituation[x -3, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        // space was blocked
                                        if (boardSituation[x - 2, y - 2] == lookFor)
                                        {
                                            if (x > 2 && y > 2)
                                            {
                                                // if next two spaces are head of himself then max tree with blocked point
                                                if (boardSituation[x - 3, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsBlocked);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        #endregion

                        #region UpRight

                        // up right
                        if (x < 21 && y > 0)
                        {
                            // check if neighbour is also head
                            if (boardSituation[x + 1, y - 1] == lookFor)
                            {
                                // check if we can move left
                                if (x < 20 && y > 1)
                                {
                                    if (boardSituation[x + 2, y - 2] == lookFor)
                                    {
                                        // if neighbour is also head
                                        // three heads on a row
                                        situations.Add(PieceSituation.ThreeHeads);
                                    }
                                    else if (boardSituation[x + 2, y - 2] != BoardPosition.Empty)
                                    {
                                        // space is not nothing, but also not a head of yourself

                                        if (boardSituation[x + 2, y - 2] == BoardPosition.Tile)
                                        {
                                            if (x < 19 && y > 2)
                                            {
                                                // if next is tile, then we can have tree with space
                                                if (boardSituation[x + 3, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                            }
                                        }
                                        else
                                        {
                                            if (x < 19 && y > 2)
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x + 3, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsBlocked);
                                            }
                                        }
                                    }
                                }
                            }
                            else if (boardSituation[x + 1, y - 1] != BoardPosition.Empty)
                            {
                                // space next to piece is not nothing or not a head of himself
                                if (x < 20 && y > 1)
                                {
                                    if (boardSituation[x + 1, y - 1] == BoardPosition.Tile)
                                    {
                                        // space is tile
                                        if (boardSituation[x + 2, y - 2] == lookFor)
                                        {
                                            if (x < 19 && y > 2)
                                            {
                                                // if next two spaces are head of himself then max tree with space
                                                if (boardSituation[x + 3, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        // space was blocked
                                        if (boardSituation[x + 2, y - 2] == lookFor)
                                        {
                                            if (x < 19 && y > 2)
                                            {
                                                // if next two spaces are head of himself then max tree with blocked point
                                                if (boardSituation[x + 3, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsBlocked);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        #endregion

                        #region DownLeft

                        // down left
                        if (y < 19 && x > 0)
                        {
                            // check if neighbour is also head
                            if (boardSituation[x - 1, y + 1] == lookFor)
                            {
                                // check if we can move left
                                if (y < 18 && x > 1)
                                {
                                    if (boardSituation[x - 2, y + 2] == lookFor)
                                    {
                                        // if neighbour is also head
                                        // three heads on a row
                                        situations.Add(PieceSituation.ThreeHeads);
                                    }
                                    else if (boardSituation[x - 2, y + 2] != BoardPosition.Empty)
                                    {
                                        // space is not nothing, but also not a head of yourself
                                        if (y < 17 && x > 2)
                                        {
                                            if (boardSituation[x - 2, y + 2] == BoardPosition.Tile)
                                            {
                                                // if next is tile, then we can have tree with space
                                                if (boardSituation[x - 3, y + 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                            }
                                            else
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x - 3, y + 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsBlocked);
                                            }
                                        }
                                    }
                                }
                            }
                            else if (boardSituation[x - 2, y + 2] != BoardPosition.Empty)
                            {
                                // space next to piece is not nothing or not a head of himself
                                if (y < 17 && x > 2)
                                {
                                    if (boardSituation[x - 1, y + 1] == BoardPosition.Tile)
                                    {
                                        // space is tile
                                        if (boardSituation[x - 2, y + 2] == lookFor)
                                        {
                                            // if next two spaces are head of himself then max tree with space
                                            if (boardSituation[x - 3, y + 3] == lookFor)
                                                situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                        }
                                    }
                                    else
                                    {
                                        // space was blocked
                                        if (boardSituation[x - 2, y + 2] == lookFor)
                                        {
                                            // if next two spaces are head of himself then max tree with blocked point
                                            if (boardSituation[x - 3, y + 3] == lookFor)
                                                situations.Add(PieceSituation.ThreeHeadsBlocked);
                                        }
                                    }
                                }
                            }
                        }

                        #endregion

                        #region DownRight

                        // down right
                        if (y < 19 && x < 20)
                        {
                            // check if neighbour is also head
                            if (boardSituation[x + 1, y + 1] == lookFor)
                            {
                                // check if we can move left
                                if (y < 18 && x <19)
                                {
                                    if (boardSituation[x + 2, y + 2] == lookFor)
                                    {
                                        // if neighbour is also head
                                        // three heads on a row
                                        situations.Add(PieceSituation.ThreeHeads);
                                    }
                                    else if (boardSituation[x + 2, y + 2] != BoardPosition.Empty)
                                    {
                                        // space is not nothing, but also not a head of yourself
                                        if (y < 17 && x <18)
                                        {
                                            if (boardSituation[x + 2, y + 2] == BoardPosition.Tile)
                                            {
                                                // if next is tile, then we can have tree with space
                                                if (boardSituation[x + 3, y + 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                            }
                                            else
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x + 3, y + 3] == lookFor)
                                                    situations.Add(PieceSituation.ThreeHeadsBlocked);
                                            }
                                        }
                                    }
                                }
                            }
                            else if (boardSituation[x + 2, y + 2] != BoardPosition.Empty)
                            {
                                // space next to piece is not nothing or not a head of himself
                                if (y < 17 && x <18)
                                {
                                    if (boardSituation[x + 1, y + 1] == BoardPosition.Tile)
                                    {
                                        // space is tile
                                        if (boardSituation[x + 2, y + 2] == lookFor)
                                        {
                                            // if next two spaces are head of himself then max tree with space
                                            if (boardSituation[x + 3, y + 3] == lookFor)
                                                situations.Add(PieceSituation.ThreeHeadsWithSpace);
                                        }
                                    }
                                    else
                                    {
                                        // space was blocked
                                        if (boardSituation[x + 2, y + 2] == lookFor)
                                        {
                                            // if next two spaces are head of himself then max tree with blocked point
                                            if (boardSituation[x + 3, y + 3] == lookFor)
                                                situations.Add(PieceSituation.ThreeHeadsBlocked);
                                        }
                                    }
                                }
                            }
                        }

                        #endregion
                    }
                }
            }

            return situations;
        }
    }

    enum PieceSituation
    {
        FourHeads = 0,
        ThreeHeads = 1,
        ThreeHeadsWithSpace = 2,
        ThreeHeadsBlocked = 3
    }
}
