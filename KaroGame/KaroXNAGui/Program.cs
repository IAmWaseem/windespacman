using System;

namespace Karo.Gui
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main(string[] args)
        {
            using (KaroGui game = new KaroGui())
            {
                game.Run();
            }
        }
    }
}

