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
using Microsoft.Xna.Framework.Graphics;
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
        MenuEntry multisamplingtypeMenuEntry;
        MenuEntry transtableMenuEntry;
        MenuEntry plyDepthMenuEntry;

        private static Karo.Gui.Properties.Settings DefaultSettings { get { return Karo.Gui.Properties.Settings.Default; } }
        static Difficulty currentLevel = (Difficulty)DefaultSettings.Difficulty;

        static bool enableMultiSampling = DefaultSettings.MultiSampleAntiAlias;
        static MultiSampleType multisamplingType = DefaultSettings.MultiSamplingLevel;

        static int currentSampling = 0;
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
            multisamplingtypeMenuEntry = new MenuEntry(string.Empty);
            transtableMenuEntry = new MenuEntry(string.Empty);
            plyDepthMenuEntry = new MenuEntry(string.Empty);

            SetMenuEntryText();

            MenuEntry backMenuEntry = new MenuEntry("Back");

            // Hook up menu event handlers.
            computerLevelMenuEntry.Selected += computerlevelMenuEntrySelected;
            multisamplingtypeMenuEntry.Selected += multisamplingtypeMenuEntrySelected;
            transtableMenuEntry.Selected += transtableMenuEntrySelected;
            plyDepthMenuEntry.Selected += plydepthMenuEntrySelected;
            backMenuEntry.Selected += OnCancel;

            // Add entries to the menu.
            MenuEntries.Add(computerLevelMenuEntry);
            MenuEntries.Add(multisamplingtypeMenuEntry);
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
            multisamplingtypeMenuEntry.Text = "Anti alias level: " + (int)multisamplingType;
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

            DefaultSettings.Difficulty = (int)currentLevel;
            DefaultSettings.Save();

            SetMenuEntryText();
        }


        /// <summary>
        /// Event handler for when the Language menu entry is selected.
        /// </summary>
        void multisamplingtypeMenuEntrySelected(object sender, PlayerIndexEventArgs e)
        {
            int level = (int)multisamplingType;
            if (level == 0 || level == 1 || level == 2 || level == 4 || level == 8 || level == 16)
            {
                // ok multisample
            }
            else
            {
                multisamplingType = 0;
            }

            if (multisamplingType == 0)
                multisamplingType++;
            else
                multisamplingType = (MultiSampleType)((int)multisamplingType * 2);

            if (multisamplingType > MultiSampleType.SixteenSamples)
                multisamplingType = 0;

            if (multisamplingType == 0)
                DefaultSettings.MultiSampleAntiAlias = false;
            else
                DefaultSettings.MultiSampleAntiAlias = true;

            DefaultSettings.MultiSamplingLevel = multisamplingType;
            DefaultSettings.Save();

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
