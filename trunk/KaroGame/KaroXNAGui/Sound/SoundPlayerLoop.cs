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
    public class SoundPlayerLoop : Microsoft.Xna.Framework.GameComponent
    {
        SoundEffect sound;
        SoundEffectInstance soundInstance;

        /// <summary>
        /// Constructor of looped sound player
        /// </summary>
        /// <param name="game"> instance of game to be used for content load </param>
        /// <param name="name"> path to the wav file to be played </param>
        public SoundPlayerLoop(Microsoft.Xna.Framework.Game game, string name)
            : base(game)
        {
            sound = game.Content.Load<SoundEffect>(name);
            soundInstance = sound.CreateInstance();
            soundInstance.IsLooped = true;
        }

        /// <summary>
        /// Starts to play a looped sound
        /// </summary>
        public void PlayLoop()
        {
            soundInstance.Play();
        }

        /// <summary>
        /// Stops to play the looped sound
        /// </summary>
        public void StopLoop()
        {
            soundInstance.Stop();
        }
    }
}