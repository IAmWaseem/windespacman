using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    /// <summary>
    /// class responsible for creation of transposition table and hashtable
    /// </summary>
    class TranspositionTable
    {
        private int tableSize;
        private Int32[,,] hashtable;
        private int[] transpostionTable;
        private System.Random random = new System.Random();
        private Int32 currentState;

        /// <summary>
        /// constructor of TranspositionTable class
        /// </summary>
        /// <param name="tableSize"> desired size of the table </param>
        public TranspositionTable( int tableSize )
        {
            this.tableSize = tableSize;
            currentState = 0;
            transpostionTable = new int[tableSize];
            creatingHashtable();
        }

        /// <summary>
        /// function creating the hashtable
        /// </summary>
        private void creatingHashtable()
        {
            hashtable = new int[21, 20, 6];
            for (int i = 0; i < 21; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    for (int k = 0; k < 6; k++)
                    {
                        hashtable[i, j, k] = random.Next();
                    }
                }
            }
        }

        /// <summary>
        /// getter of transposition table
        /// </summary>
        /// <returns></returns>
        public int[] GetTranspositionTable()
        {
            return transpostionTable;
        }

        /// <summary>
        /// function calculating hashvalue of given board situation
        /// </summary>
        /// <param name="boardPositions"> board situation for calculations </param>
        /// <returns> hashvalue of input board </returns>
        public Int32 HashValueOfBoardState(BoardPosition[,] boardPositions)
        {
            Int32 hashBoardState = 0;
            for (int i = 0; i < 21; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    hashBoardState = hashBoardState ^ hashtable[i, j, (int)boardPositions[i,j]];
                }
            }
            return hashBoardState;
        }

        /// <summary>
        /// function putting a hashvalue to transposition table after adding a piece
        /// </summary>
        /// <param name="position_x"> x coordinate were to place piece</param>
        /// <param name="position_y"> y coordinate were to place piece </param>
        /// <param name="piece_type"> type of the piece </param>
        public void Adding_a_piece(int position_x, int position_y, BoardPosition piece_type)
        {
            int positionInTranspositionTable;
            currentState = currentState ^ hashtable[position_x, position_y, (int)piece_type];
            positionInTranspositionTable = currentState % this.tableSize;
            transpostionTable[positionInTranspositionTable] = currentState;
        }

        /// <summary>
        /// function putting a hashvalue to transposition table after moving a piece
        /// </summary>
        /// <param name="position_start_x"> x coordinate where from to take piece </param>
        /// <param name="position_start_y"> y coordinate where from to take piece </param>
        /// <param name="position_end_x"> x coordinate were to place piece </param>
        /// <param name="position_end_y"> y coordinate were to place piece </param>
        /// <param name="piece_type"> type of the piece </param>
        public void Moving_one_piece(int position_start_x, int position_start_y, int position_end_x, int position_end_y, BoardPosition piece_type)
        {
            int positionInTranspositionTable;
            currentState = currentState ^ hashtable[position_start_x, position_start_y, (int)piece_type];
            currentState = currentState ^ hashtable[position_end_x, position_end_y, (int)piece_type];
            positionInTranspositionTable = currentState % this.tableSize;
            transpostionTable[positionInTranspositionTable] = currentState;
        }

        /// <summary>
        /// function putting a hashvalue to transposition table after jumping with a piece
        /// </summary>
        /// <param name="position_start_x"> x coordinate where from to take piece </param>
        /// <param name="position_start_y"> y coordinate where from to take piece </param>
        /// <param name="position_end_x"> x coordinate were to place piece </param>
        /// <param name="position_end_y"> y coordinate were to place piece </param>
        /// <param name="piece_type"> type of the piece </param>
        public void Jumping_with_a_piece(int position_start_x, int position_start_y, int position_end_x, int position_end_y, BoardPosition piece_type)
        {
            int positionInTranspositionTable = 0;
            currentState = currentState ^ hashtable[position_start_x, position_start_y, (int)piece_type];
            currentState = currentState ^ hashtable[position_end_x, position_end_y, (int)piece_type + 1];
            positionInTranspositionTable = currentState % this.tableSize;
            transpostionTable[positionInTranspositionTable] = currentState;
        }
    }
}
