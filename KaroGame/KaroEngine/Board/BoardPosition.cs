using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    /// <summary>
    /// State of position
    /// </summary>
    public enum BoardPosition
    {
        /// <summary>
        /// Nothing here
        /// </summary>
        Empty = 0,

        /// <summary>
        /// Black tile here
        /// </summary>
        Tile = 1,

        /// <summary>
        /// Black tile with red piece, tail up
        /// </summary>
        RedTail = 2,

        /// <summary>
        /// Black tile with red piece, head up
        /// </summary>
        RedHead = 3,

        /// <summary>
        /// Black tile with white piece, tail up
        /// </summary>
        WhiteTail = 4,

        /// <summary>
        /// Black tile with white piece, head up
        /// </summary>
        WhiteHead = 5
    }
}
