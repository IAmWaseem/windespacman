using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace PacManGame
{
    interface IDrawObject
    {
        void DoAnim();

        void Draw(Graphics g, Point pixelPosition, Point direction);
    }
}
