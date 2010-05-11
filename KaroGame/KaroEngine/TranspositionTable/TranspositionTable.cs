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
        private int[,,] hashtable;
        private int[] transpostionTable;
        private System.Random random = new System.Random();
        private int playerA, playerB;

        /// <summary>
        /// constructor of TranspositionTable class
        /// </summary>
        /// <param name="tableSize"> desired size of the table </param>
        public TranspositionTable(int tableSize)
        {
            this.tableSize = tableSize;
            transpostionTable = new int[tableSize];
            playerA = random.Next();
            while ((playerB = random.Next()) == playerA) { }
            hashtable = new int[21, 20, 5];
            for (int i = 0; i < 21; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    for (int k = 0; k < 5; k++)
                    {
                    NotUniq:
                        hashtable[i, j, k] = random.Next();
                        for (int m = 0; m <= i; m++)
                        {
                            for (int n = 0; n <= j; n++)
                            {
                                for (int p = 0; p < k; p++)
                                {
                                    if (hashtable[m, n, p] == hashtable[i, j, k] ||
                                        playerA == hashtable[m, n, p] || playerB == hashtable[m, n, p])
                                    {
                                        goto NotUniq;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        /// <summary>
        /// getter of transposition table
        /// </summary>
        /// <returns> transpositon table </returns>
        public int[] GetTranspositionTable()
        {
            return transpostionTable;
        }

        /// <summary>
        /// function calculating hashvalue of given board situation
        /// </summary>
        /// <param name="boardPositions"> board situation for calculations </param>
        /// <param name="turnPlayerA"> bool - which player has it's turn </param>
        /// <returns> hashvalue of input board </returns>
        public int HashValueOfBoardState(BoardPosition[,] boardPositions, bool turnPlayerA)
        {
            int hashBoardState = 0;
            for (int i = 0; i < 21; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    if ((int)boardPositions[i, j] != 0)
                        hashBoardState = hashBoardState ^ hashtable[i, j, (int)boardPositions[i, j] - 1];
                }
            }
            if (turnPlayerA)
                hashBoardState = hashBoardState ^ playerA;
            else
                hashBoardState = hashBoardState ^ playerB;

            transpostionTable[hashBoardState % transpostionTable.Length] = hashBoardState;

            return hashBoardState;
        }
    }
}