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
        private int[, ,] hashtable;
        private HashObject[] transpostionTable;
        private System.Random random = new System.Random();
        private int playerA, playerB;

        /// <summary>
        /// constructor of TranspositionTable class
        /// </summary>
        /// <param name="tableSize"> desired size of the table </param>
        public TranspositionTable(int tableSize)
        {
            this.tableSize = tableSize;
            transpostionTable = new HashObject[tableSize];
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
                        if (playerA == hashtable[i, j, k] || playerB == hashtable[i, j, k])
                        {
                            goto NotUniq;
                        }
                        for (int m = 0; m <= i; m++)
                        {
                            for (int n = 0; n <= j; n++)
                            {
                                for (int p = 0; p < k; p++)
                                {
                                    if (hashtable[m, n, p] == hashtable[i, j, k])
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
        public HashObject[] GetTranspositionTable()
        {
            return transpostionTable;
        }

        /// <summary>
        /// function calculating hashvalue of given board situation
        /// </summary>
        /// <param name="board"> board for calculations </param>
        /// <param name="turnPlayerA"> bool - which player has it's turn </param>
        /// <param name="depth"> depth of search in algorithm </param>
        /// <returns> hashvalue of input board </returns>
        public int EvaluationByHashing(Board board, bool turnPlayerA, int depth)
        {
            int hashKey = 0, position = 0;

            for (int i = 0; i < 21; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    if ((int)board.BoardSituation[i, j] != 0)
                        hashKey = hashKey ^ hashtable[i, j, (int)board.BoardSituation[i, j] - 1];
                }
            }

            if (turnPlayerA)
                hashKey = hashKey ^ playerA;
            else
                hashKey = hashKey ^ playerB;

            TableTooSmall:
            position = hashKey % tableSize;
            if (transpostionTable[position] == null) 
            {
                transpostionTable[position] = new HashObject(depth, hashKey, board.Evaluation(turnPlayerA));
            } 
            else if (transpostionTable[position].hashKey == hashKey)
            {
                if (transpostionTable[position].depth < depth)
                {
                    transpostionTable[position] = new HashObject(depth, hashKey, board.Evaluation(turnPlayerA));
                }
            }
            else 
            {
                tableResize();
                goto TableTooSmall;
            }

            return transpostionTable[position].value;
        }

        private void tableResize()
        {
            tableSize *= 2;
            HashObject[] transTable = new HashObject[tableSize];
            foreach (HashObject obj in transpostionTable)
            {
                if(obj!=null)
                    transTable[obj.hashKey % tableSize] = obj;
            }
            transpostionTable = transTable;
        }
    }
}