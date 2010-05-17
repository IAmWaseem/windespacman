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

        private List<PieceSituation> FindSituations(BoardPosition[,] boardSituation, bool isRed)
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
                                        situations.Add(PieceSituation.MaxThreeHeads);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
                                            }
                                        }
                                        else
                                        {
                                            if (x > 2)
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x - 3, y] == lookFor)
                                                    situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                        situations.Add(PieceSituation.MaxThreeHeads);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
                                            }
                                        }
                                        else
                                        {
                                            if (x < 19)
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x + 3, y] == lookFor)
                                                    situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                        situations.Add(PieceSituation.MaxThreeHeads);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
                                            }
                                            else
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                                situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
                                        }
                                    }
                                    else
                                    {
                                        // space was blocked
                                        if (boardSituation[x, y - 2] == lookFor)
                                        {
                                            // if next two spaces are head of himself then max tree with blocked point
                                            if (boardSituation[x, y - 3] == lookFor)
                                                situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                        situations.Add(PieceSituation.MaxThreeHeads);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
                                            }
                                            else
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x, y + 3] == lookFor)
                                                    situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                                situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
                                        }
                                    }
                                    else
                                    {
                                        // space was blocked
                                        if (boardSituation[x, y + 2] == lookFor)
                                        {
                                            // if next two spaces are head of himself then max tree with blocked point
                                            if (boardSituation[x, y + 3] == lookFor)
                                                situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                        situations.Add(PieceSituation.MaxThreeHeads);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
                                            }
                                        }
                                        else
                                        {
                                            if (x >2 && y > 2)
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x - 3, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                        situations.Add(PieceSituation.MaxThreeHeads);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
                                            }
                                        }
                                        else
                                        {
                                            if (x < 19 && y > 2)
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x + 3, y - 3] == lookFor)
                                                    situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                        situations.Add(PieceSituation.MaxThreeHeads);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
                                            }
                                            else
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x - 3, y + 3] == lookFor)
                                                    situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                                situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
                                        }
                                    }
                                    else
                                    {
                                        // space was blocked
                                        if (boardSituation[x - 2, y + 2] == lookFor)
                                        {
                                            // if next two spaces are head of himself then max tree with blocked point
                                            if (boardSituation[x - 3, y + 3] == lookFor)
                                                situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                        situations.Add(PieceSituation.MaxThreeHeads);
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
                                                    situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
                                            }
                                            else
                                            {
                                                // three with space and blocked
                                                if (boardSituation[x + 3, y + 3] == lookFor)
                                                    situations.Add(PieceSituation.MaxThreeHeadsBlocked);
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
                                                situations.Add(PieceSituation.MaxThreeHeadsWithSpace);
                                        }
                                    }
                                    else
                                    {
                                        // space was blocked
                                        if (boardSituation[x + 2, y + 2] == lookFor)
                                        {
                                            // if next two spaces are head of himself then max tree with blocked point
                                            if (boardSituation[x + 3, y + 3] == lookFor)
                                                situations.Add(PieceSituation.MaxThreeHeadsBlocked);
                                        }
                                    }
                                }
                            }
                        }

                        #endregion
                    }
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
