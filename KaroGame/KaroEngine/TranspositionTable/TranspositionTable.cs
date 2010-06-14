using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    /// <summary>
    /// class responsible for creation of transposition table and hashtable
    /// </summary>
    /// 
    static class RandomExtension
    {
        public static Int64 NextInt64(this System.Random rnd)
        {
            var buffer = new byte[sizeof(Int64)];
            rnd.NextBytes(buffer);
            return BitConverter.ToInt64(buffer, 0);
        }
    }

    class TranspositionTable
    {


        private Int64[,] emptySpacesKeys = new Int64[21, 20];
        private Int64[,] tilesKeys = new Int64[21, 20];
        private Int64[,] redTailKeys = new Int64[21, 20];
        private Int64[,] redheadKeys = new Int64[21, 20];
        private Int64[,] whiteTailKeys = new Int64[21, 20];
        private Int64[,] whiteHeadKeys = new Int64[21, 20];
        private Int64 turnPlayerA;
        private Int64 turnPlayerB;
        private Int64 playerAMax;
        private Int64 playerBMax;
        private HashObject[] tableContent;
        private int tableSize = 100;

        public TranspositionTable()
        {
            tableContent = new HashObject[tableSize];
            System.Random random = new System.Random(DateTime.Now.Millisecond);
            List<Int64> generatedBefore = new List<Int64>();
            turnPlayerA = random.NextInt64();
            turnPlayerB = random.NextInt64();
            playerAMax = random.NextInt64();
            playerBMax = random.NextInt64();
            generatedBefore.Add(turnPlayerA);

            while (generatedBefore.Contains(turnPlayerB)) turnPlayerB = random.NextInt64();
            generatedBefore.Add(turnPlayerB);

            while (generatedBefore.Contains(playerAMax)) playerAMax = random.NextInt64();
            generatedBefore.Add(playerAMax);

            while (generatedBefore.Contains(playerBMax)) playerBMax = random.NextInt64();
            generatedBefore.Add(playerBMax);

            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    for (int n = 0; n < 6; n++)
                    {
                        Int64 randomValue = random.NextInt64();
                        while (generatedBefore.Contains(randomValue)) randomValue = random.NextInt64();
                        generatedBefore.Add(randomValue);

                        switch (n)
                        {
                            case 0:
                                emptySpacesKeys[x,y] = randomValue;
                                break;
                            case 1:
                                tilesKeys[x,y] = randomValue;
                                break;
                            case 2:
                                redTailKeys[x,y] = randomValue;
                                break;
                            case 3:
                                redheadKeys[x,y] = randomValue;
                                break;
                            case 4:
                                whiteTailKeys[x,y] = randomValue;
                                break;
                            case 5:
                                whiteHeadKeys[x, y] = randomValue;
                                break;
                        }
                    }
                }
            }
        }

        public bool IsCalculatedBefore(Board board, int depth, bool isPlayerAMax, bool turnPlayerA)
        {
            Int64 hashKey = CreateHashKey(board, depth, isPlayerAMax, turnPlayerA);
            int position = (int)Math.Abs((hashKey % tableSize));
            HashObject hashObject = tableContent[position];
            if (hashObject == null)
                return false;
            if (hashObject.depth >= depth && hashObject.hashKey == hashKey && hashObject.isPlayerAMax == isPlayerAMax && hashObject.turnPlayerA == turnPlayerA)
                return true;
            return false;
        }

        public int GetCalculatedValue(Board board, int depth, bool isPlayerAMax, bool turnPlayerA)
        {
            Int64 hashKey = CreateHashKey(board, depth, isPlayerAMax, turnPlayerA);
            int position = (int)Math.Abs((hashKey % tableSize));
            HashObject hashObject = tableContent[position];
            if (hashObject == null)
                throw new Exception("Board has not been calculated before and inserted into the transposition table");
            if (hashObject.depth >= depth && hashObject.hashKey == hashKey && hashObject.isPlayerAMax == isPlayerAMax && hashObject.turnPlayerA == turnPlayerA)
                return hashObject.value;
            else
                throw new Exception("Board has not been calculated before and inserted into the transposition table");
        }

        public void InsertCalculatedValue(Board board, int depth, bool isPlayerAMax, bool turnPlayerA, int value)
        {
            Int64 hashKey = CreateHashKey(board, depth, isPlayerAMax, turnPlayerA);
            int position = (int)Math.Abs((hashKey % tableSize));
            HashObject hashObject = tableContent[position];
            if (hashObject == null)
                tableContent[position] = new HashObject(depth, hashKey, value, isPlayerAMax, turnPlayerA);
            else
            {
                bool collision = true;
                while (collision)
                {
                    position = (int)Math.Abs((hashKey % tableSize));
                    hashObject = tableContent[position];
                    if (hashObject == null)
                        collision = false;
                    else if (hashObject.hashKey != hashKey || hashObject.isPlayerAMax != isPlayerAMax || hashObject.turnPlayerA != turnPlayerA)
                        TableResize();
                    else
                        collision = false;
                }
                tableContent[position] = new HashObject(depth, hashKey, value, isPlayerAMax, turnPlayerA);
            }

        }

        private Int64 CreateHashKey(Board board, int depth, bool isPlayerAMax, bool turnPlayerA)
        {
            Int64 result = 0;

            if (isPlayerAMax)
                result = result ^ playerAMax;
            else
                result = result ^ playerBMax;

            if (turnPlayerA)
                result = result ^ this.turnPlayerA;
            else
                result = result ^ turnPlayerB;


            for (int x = 0; x < 21; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    switch (board.BoardSituation[x, y])
                    {
                        case BoardPosition.Empty:
                            result = result ^ emptySpacesKeys[x, y];
                            break;
                        case BoardPosition.Tile:
                            result = result ^ tilesKeys[x, y];
                            break;
                        case BoardPosition.RedTail:
                            result = result ^ redTailKeys[x, y];
                            break;
                        case BoardPosition.RedHead:
                            result = result ^ redheadKeys[x, y];
                            break;
                        case BoardPosition.WhiteTail:
                            result = result ^ whiteTailKeys[x, y];
                            break;
                        case BoardPosition.WhiteHead:
                            result = result ^ whiteHeadKeys[x, y];
                            break;
                    }
                }
            }

            return result;

        }

        private void TableResize()
        {
            tableSize = NextPrime(this.tableSize);
            HashObject[] transTable = new HashObject[tableSize];
            foreach (HashObject obj in this.tableContent)
            {
                if (obj != null)
                    transTable[(int)Math.Abs((obj.hashKey % tableSize))] = obj;
            }
            tableContent = transTable;
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


        //private int tableSize, maxTableSize;
        //private int[, ,] hashtable;
        //private HashObject[] transpostionTable;
        //private System.Random random = new System.Random();
        //private int playerA, playerB;

        ///// <summary>
        ///// constructor of TranspositionTable class
        ///// </summary>
        ///// <param name="tableSize"> desired size of the table </param>
        ///// <param name="maxTableSize"> maximal size to which the table may be extended </param>
        //public TranspositionTable(int tableSize, int maxTableSize)
        //{
        //    this.tableSize = tableSize;
        //    this.maxTableSize = maxTableSize;
        //    transpostionTable = new HashObject[tableSize];
        //    playerA = random.Next();
        //    while ((playerB = random.Next()) == playerA) { }
        //    hashtable = new int[21, 20, 5];
        //    for (int i = 0; i < 21; i++)
        //    {
        //        for (int j = 0; j < 20; j++)
        //        {
        //            for (int k = 0; k < 5; k++)
        //            {
        //            NotUniq:
        //                hashtable[i, j, k] = random.Next();
        //                if (playerA == hashtable[i, j, k] || playerB == hashtable[i, j, k])
        //                {
        //                    goto NotUniq;
        //                }
        //                for (int m = 0; m <= i; m++)
        //                {
        //                    for (int n = 0; n <= j; n++)
        //                    {
        //                        for (int p = 0; p < k; p++)
        //                        {
        //                            if (hashtable[m, n, p] == hashtable[i, j, k])
        //                            {
        //                                goto NotUniq;
        //                            }
        //                        }
        //                    }
        //                }
        //            }
        //        }
        //    }
        //}

        //private void tableResize()
        //{
        //    tableSize = NextPrime(tableSize) ;
        //    HashObject[] transTable = new HashObject[tableSize];
        //    foreach (HashObject obj in transpostionTable)
        //    {
        //        if (obj != null)
        //            transTable[obj.hashKey % tableSize] = obj;
        //    }
        //    transpostionTable = transTable;
        //}

        //private int NextPrime(int previousPrime)
        //{
        //    while (!IsPrime(++previousPrime)) ;
        //    return previousPrime;
        //}

        //private bool IsPrime(int possiblePrime)
        //{
        //    int a = 1;
        //    for (int m = 2; m <= Math.Sqrt(possiblePrime); m += a)
        //    {
        //        if (m == 3)
        //            a = 2;
        //        if (possiblePrime % m == 0)
        //            return false;
        //    }
        //    return true;
        //}

        //public bool IsCalculatedBefore(Board board, int depth, bool turnPlayerA)
        //{
        //    int hashKey = 0;

        //    for (int i = 0; i < 21; i++)
        //    {
        //        for (int j = 0; j < 20; j++)
        //        {
        //            if ((int)board.BoardSituation[i, j] != 0)
        //                hashKey = hashKey ^ hashtable[i, j, (int)board.BoardSituation[i, j] - 1];
        //        }
        //    }

        //    if (turnPlayerA)
        //        hashKey = hashKey ^ playerA;
        //    else
        //        hashKey = hashKey ^ playerB;

        //    HashObject boardInArray = transpostionTable[hashKey % tableSize];
        //    if (boardInArray == null)
        //        return false;
        //    if (boardInArray.hashKey == hashKey && boardInArray.depth >= depth)
        //        return true;
        //    else
        //        return false;
        //}

        //public int GetCalculatedValue(Board board, int depth, bool turnPlayerA)
        //{
        //    int hashKey = 0;

        //    for (int i = 0; i < 21; i++)
        //    {
        //        for (int j = 0; j < 20; j++)
        //        {
        //            if ((int)board.BoardSituation[i, j] != 0)
        //                hashKey = hashKey ^ hashtable[i, j, (int)board.BoardSituation[i, j] - 1];
        //        }
        //    }

        //    if (turnPlayerA)
        //        hashKey = hashKey ^ playerA;
        //    else
        //        hashKey = hashKey ^ playerB;

        //    HashObject boardInArray = transpostionTable[hashKey % tableSize];
        //    if (boardInArray != null)
        //        return boardInArray.value;
        //    else
        //        return 0;
        //}

        //public void InsertCalculatedValue(Board board, int depth, bool turnPlayerA, int value)
        //{
        //    int hashKey = 0;

        //    for (int i = 0; i < 21; i++)
        //    {
        //        for (int j = 0; j < 20; j++)
        //        {
        //            if ((int)board.BoardSituation[i, j] != 0)
        //                hashKey = hashKey ^ hashtable[i, j, (int)board.BoardSituation[i, j] - 1];
        //        }
        //    }

        //    if (turnPlayerA)
        //        hashKey = hashKey ^ playerA;
        //    else
        //        hashKey = hashKey ^ playerB;

        //    int positionInArray = hashKey % tableSize;

        //    bool collision = true;
        //    while (collision)
        //    {
        //        if (transpostionTable[positionInArray] != null)
        //            if (transpostionTable[positionInArray].hashKey != hashKey)
        //            {
        //                tableResize();
        //                positionInArray = hashKey % tableSize;
        //            }
        //            else
        //                collision = false;
        //        else
        //            collision = false;
        //    }
        //    transpostionTable[positionInArray] = new HashObject(depth, hashKey, value);
        //}

    }
}