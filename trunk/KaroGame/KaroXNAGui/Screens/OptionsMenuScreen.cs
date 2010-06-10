#region File Description
//-----------------------------------------------------------------------------
// OptionsMenuScreen.cs
//
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#endregion

#region Using Statements
using Microsoft.Xna.Framework;
using Karo.Gui;
#endregion

namespace GameStateManagement
{
    /// <summary>
    /// The options screen is brought up over the top of the main menu
    /// screen, and gives the user a chance to configure the game
    /// in various hopefully useful ways.
    /// </summary>
    class OptionsMenuScreen : MenuScreen
    {
        #region Fields

        MenuEntry computerLevelMenuEntry;
        MenuEntry algorithmMenuEntry;
        MenuEntry transtableMenuEntry;
        MenuEntry plyDepthMenuEntry;

        static Difficulty currentLevel = Difficulty.Medium;

        static string[] computerAI = { "Random", "Mini Max", "Alpha Beta" };
        static int currentAI = 0;
        static bool useTransTable = true;
        static int plyDepth = 2;

        #endregion

        #region Initialization


        /// <summary>
        /// Constructor.
        /// </summary>
        public OptionsMenuScreen()
            : base("Options")
        {
            // Create our menu entries.
            computerLevelMenuEntry = new MenuEntry(string.Empty);
            algorithmMenuEntry = new MenuEntry(string.Empty);
            transtableMenuEntry = new MenuEntry(string.Empty);
            plyDepthMenuEntry = new MenuEntry(string.Empty);

            SetMenuEntryText();

            MenuEntry backMenuEntry = new MenuEntry("Back");

            // Hook up menu event handlers.
            computerLevelMenuEntry.Selected += computerlevelMenuEntrySelected;
            algorithmMenuEntry.Selected += algorithmMenuEntrySelected;
            transtableMenuEntry.Selected += transtableMenuEntrySelected;
            plyDepthMenuEntry.Selected += plydepthMenuEntrySelected;
            backMenuEntry.Selected += OnCancel;

            // Add entries to the menu.
            MenuEntries.Add(computerLevelMenuEntry);
            MenuEntries.Add(algorithmMenuEntry);
            MenuEntries.Add(transtableMenuEntry);
            MenuEntries.Add(plyDepthMenuEntry);
            MenuEntries.Add(backMenuEntry);
        }


        /// <summary>
        /// Fills in the latest values for the options screen menu text.
        /// </summary>
        void SetMenuEntryText()
        {
            computerLevelMenuEntry.Text = "Difficulty: " + currentLevel;
            algorithmMenuEntry.Text = "Custom algorithm: " + computerAI[currentAI];
            transtableMenuEntry.Text = "Use transposition table: " + (useTransTable ? "on" : "off");
            plyDepthMenuEntry.Text = "Ply depth: " + plyDepth;
        }


        #endregion

        #region Handle Input


        /// <summary>
        /// Event handler for when the Ungulate menu entry is selected.
        /// </summary>
        void computerlevelMenuEntrySelected(object sender, PlayerIndexEventArgs e)
        {
            currentLevel++;

            if (currentLevel > Difficulty.Hard)
                currentLevel = 0;

            SetMenuEntryText();
        }


        /// <summary>
        /// Event handler for when the Language menu entry is selected.
        /// </summary>
        void algorithmMenuEntrySelected(object sender, PlayerIndexEventArgs e)
        {
            currentAI = (currentAI + 1) % computerAI.Length;

            SetMenuEntryText();
        }


        /// <summary>
        /// Event handler for when the Frobnicate menu entry is selected.
        /// </summary>
        void transtableMenuEntrySelected(object sender, PlayerIndexEventArgs e)
        {
            useTransTable = !useTransTable;

            SetMenuEntryText();
        }


        /// <summary>
        /// Event handler for when the Elf menu entry is selected.
        /// </summary>
        void plydepthMenuEntrySelected(object sender, PlayerIndexEventArgs e)
        {
            plyDepth++;
            if (plyDepth > 6)
                plyDepth = 1;

            SetMenuEntryText();
        }


        #endregion
    }
}
