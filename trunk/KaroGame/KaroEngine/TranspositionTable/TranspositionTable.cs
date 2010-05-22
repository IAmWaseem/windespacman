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
        private int tableSize, maxTableSize;
        private int[, ,] hashtable;
        private HashObject[] transpostionTable;
        private System.Random random = new System.Random();
        private int playerA, playerB;

        /// <summary>
        /// getter of size of transposition table
        /// </summary>
        public int GetTableSize()
        {
            return tableSize;
        }

        /// <summary>
        /// constructor of TranspositionTable class
        /// </summary>
        /// <param name="tableSize"> desired size of the table </param>
        /// <param name="maxTableSize"> maximal size to which the table may be extended </param>
        public TranspositionTable(int tableSize, int maxTableSize)
        {
            this.tableSize = tableSize;
            this.maxTableSize = maxTableSize;
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
        /// <param name="index"> index of the HashObject to be returned </param>
        /// <returns> transpositon table </returns>
        public HashObject GetHashObject(int index)
        {
            return transpostionTable[index];
        }

        /// <summary>
        /// function calculating hashvalue of given board and putting it to transpostion table
        /// providing most accurate information about evaluation value
        /// </summary>
        /// <param name="board"> board for calculations </param>
        /// <param name="turnPlayerA"> bool - which player has it's turn </param>
        /// <param name="depth"> depth of search in algorithm </param>
        /// <returns> evaluation of given board </returns>
        public int EvaluationByHashing(Board board, bool isPlayerAMAX, bool turnPlayerA, int depth)
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
                transpostionTable[position] = new HashObject(depth, hashKey, board.Evaluation(isPlayerAMAX, turnPlayerA));
            }
            else if (transpostionTable[position].hashKey == hashKey)
            {
                if (transpostionTable[position].depth < depth)
                {
                    transpostionTable[position] = new HashObject(depth, hashKey, board.Evaluation(isPlayerAMAX, turnPlayerA));
                }
            }
            else if (tableSize < maxTableSize)
            {
                tableResize();
                goto TableTooSmall;
            }
            else
            {
                transpostionTable[position] = new HashObject(depth, hashKey, board.Evaluation(isPlayerAMAX, turnPlayerA));
            }

            return transpostionTable[position].value;
        }

        /// <summary>
        /// function calculating hashvalue of given board situation and putting it to transposition table
        /// providing information about depth of evaluation value that is available in transposition table
        /// </summary>
        /// <param name="board"> board for calculations </param>
        /// <param name="turnPlayerA"> bool - which player has it's turn </param>
        /// <param name="depth"> depth of search in algorithm </param>
        /// <returns> depth of evaluation value stored in transposition table </returns>
        public int DepthByHashing(Board board, bool isPlayerAMAX, bool turnPlayerA, int depth)
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

            board.BoardHashvalue = hashKey;

        TableTooSmall:
            position = hashKey % tableSize;
            if (transpostionTable[position] == null)
            {
                transpostionTable[position] = new HashObject(depth, hashKey, board.Evaluation(isPlayerAMAX, turnPlayerA));
            }
            else if (transpostionTable[position].hashKey == hashKey)
            {
                if (transpostionTable[position].depth < depth)
                {
                    transpostionTable[position] = new HashObject(depth, hashKey, board.Evaluation(isPlayerAMAX, turnPlayerA));
                }
            }
            else if (tableSize < maxTableSize)
            {
                tableResize();
                goto TableTooSmall;
            }
            else
            {
                transpostionTable[position] = new HashObject(depth, hashKey, board.Evaluation(isPlayerAMAX, turnPlayerA));
            }

            return transpostionTable[position].depth;
        }

        private void tableResize()
        {
            tableSize = NextPrime(tableSize) ;
            HashObject[] transTable = new HashObject[tableSize];
            foreach (HashObject obj in transpostionTable)
            {
                if (obj != null)
                    transTable[obj.hashKey % tableSize] = obj;
            }
            transpostionTable = transTable;
        }

        private int NextPrime(int previousPrime)
        {
            while (!IsPrime(++previousPrime)) ;
            return previousPrime;
        }

        private bool IsPrime(int possiblePrime)
        {
            int a = 1;
            for (int m = 2; m <= Math.Sqrt(possiblePrime); m += a)
            {
                if (m == 3)
                    a = 2;
                if (possiblePrime % m == 0)
                    return false;
            }
            return true;
        }

        public bool IsCalculatedBefore(Board board, int depth, bool turnPlayerA)
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

            int positionInArray = hashKey % tableSize;

            HashObject boardInArray = transpostionTable[positionInArray];
            if (boardInArray == null)
                return false;
            if (boardInArray.hashKey == hashKey && boardInArray.depth >= depth)
                return true;
            else
                return false;
        }

        public int GetCalculatedValue(Board board, int depth, bool turnPlayerA)
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

            int positionInArray = hashKey % tableSize;

            HashObject boardInArray = transpostionTable[positionInArray];
            if (boardInArray != null)
                return boardInArray.value;
            else
                return 0;
        }

        public void InsertCalculatedValue(Board board, int depth, bool turnPlayerA, int value)
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

            int positionInArray = hashKey % tableSize;

            bool collision = true;
            while (collision)
            {
                if (transpostionTable[positionInArray] != null)
                    if (transpostionTable[positionInArray].hashKey != hashKey)
                    {
                        tableResize();
                        positionInArray = hashKey % tableSize;
                    }
                    else
                        collision = false;
                else
                    collision = false;
            }
            transpostionTable[positionInArray] = new HashObject(depth, hashKey, value);
        }

    }
}