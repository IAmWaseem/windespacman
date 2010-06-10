using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;


namespace Karo.Gui
{
    /// <summary>
    /// 
    /// </summary>
    public class SoundPlayer : Microsoft.Xna.Framework.GameComponent
    {
        SoundEffect sound;

        /// <summary>
        /// Constructor of sound player
        /// </summary>
        /// <param name="game"> instance of game to be used for content load </param>
        /// <param name="name"> path to the wav file to be played </param>
        public SoundPlayer(Microsoft.Xna.Framework.Game game, string name)
            : base(game)
        {
            sound = game.Content.Load<SoundEffect>(name);
        }

        /// <summary>
        /// Plays sound once
        /// </summary>
        public void PlaySound()
        {
            sound.Play();
        }
    }
}