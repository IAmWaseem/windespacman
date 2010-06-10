#region File Description
//-----------------------------------------------------------------------------
// OptionsMenuScreen.cs
//
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#endregion

#region Using Statements
using Karo.Gui;
using System;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System.Collections.Generic;
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
        MenuEntry fullScreenMenuEntry;
        MenuEntry resolutionMenuEntry;

        private static Karo.Gui.Properties.Settings DefaultSettings { get { return Karo.Gui.Properties.Settings.Default; } }
        static Difficulty currentLevel = (Difficulty)DefaultSettings.Difficulty;

        static bool enableMultiSampling = DefaultSettings.MultiSampleAntiAlias;
        static MultiSampleType multisamplingType = DefaultSettings.MultiSamplingLevel;
        static List<DisplayMode> supportedModes;
        static int currentSampling = 0;
        static bool fullScreen = DefaultSettings.FullScreen;
        static int SelectedMode = 2;

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
            fullScreenMenuEntry = new MenuEntry(string.Empty);
            resolutionMenuEntry = new MenuEntry(string.Empty);

            MenuEntry backMenuEntry = new MenuEntry("Back");

            supportedModes = GraphicsAdapter.DefaultAdapter.SupportedDisplayModes.ToList();
            List<DisplayMode> temp = supportedModes.ToList();
            foreach (DisplayMode dm in temp)
            {
                if (dm.Format != SurfaceFormat.Bgr32 || dm.Width < 800)
                    supportedModes.Remove(dm);
            }

            SelectCurrentDisplay();
            SetMenuEntryText();

            // Hook up menu event handlers.
            computerLevelMenuEntry.Selected += computerlevelMenuEntrySelected;
            multisamplingtypeMenuEntry.Selected += multisamplingtypeMenuEntrySelected;
            fullScreenMenuEntry.Selected += fullScreenMenuEntrySelected;
            resolutionMenuEntry.Selected += resolutionMenuEntrySelected;
            backMenuEntry.Selected += OnCancel;

            // Add entries to the menu.
            MenuEntries.Add(computerLevelMenuEntry);
            MenuEntries.Add(multisamplingtypeMenuEntry);
            MenuEntries.Add(fullScreenMenuEntry);
            MenuEntries.Add(resolutionMenuEntry);
            MenuEntries.Add(backMenuEntry);
        }

        private void SelectCurrentDisplay()
        {
            for(int i = 0; i < supportedModes.Count; i++)
            {
                DisplayMode dm = supportedModes[i];
                if (dm.Width == DefaultSettings.ScreenWidth && dm.Height == DefaultSettings.ScreenHeight)
                {
                    SelectedMode = i;
                }
            }
        }

        /// <summary>
        /// Fills in the latest values for the options screen menu text.
        /// </summary>
        void SetMenuEntryText()
        {
            computerLevelMenuEntry.Text = "Difficulty: " + currentLevel;
            if((int)multisamplingType > 0)
                multisamplingtypeMenuEntry.Text = "Anti alias: " + (int)multisamplingType + "x";
            else
                multisamplingtypeMenuEntry.Text = "Anti alias: off";

            
            fullScreenMenuEntry.Text = "Full screen: " + (fullScreen ? "on" : "off");
            resolutionMenuEntry.Text = "Resolution: " + supportedModes[SelectedMode].Width.ToString("0") +"x" +supportedModes[SelectedMode].Height.ToString("0");
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

            SurfaceFormat format = GraphicsAdapter.DefaultAdapter.CurrentDisplayMode.Format;
            // Check for 4xAA
            if (GraphicsAdapter.DefaultAdapter.CheckDeviceMultiSampleType(DeviceType.Hardware, format,
                false, multisamplingType))
            {
                // it supports!!!!
            }
            else
            {
                multisamplingType = 0;
            }


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
        void fullScreenMenuEntrySelected(object sender, PlayerIndexEventArgs e)
        {
            fullScreen = !fullScreen;
            ScreenManager.Graphics.IsFullScreen = fullScreen;
            ScreenManager.Graphics.ApplyChanges();
            DefaultSettings.FullScreen = fullScreen;
            DefaultSettings.Save();
            SetMenuEntryText();
        }

        /// <summary>
        /// Event handler for when the Elf menu entry is selected.
        /// </summary>
        void resolutionMenuEntrySelected(object sender, PlayerIndexEventArgs e)
        {
            SelectedMode++;
            if (SelectedMode > supportedModes.Count - 1)
                SelectedMode = 0;

            DefaultSettings.ScreenWidth = supportedModes[SelectedMode].Width;
            DefaultSettings.ScreenHeight = supportedModes[SelectedMode].Height;
            DefaultSettings.Save();

            ScreenManager.Graphics.PreferredBackBufferWidth = DefaultSettings.ScreenWidth;
            ScreenManager.Graphics.PreferredBackBufferHeight = DefaultSettings.ScreenHeight;
            ScreenManager.Graphics.ApplyChanges();

            SetMenuEntryText();
        }


        #endregion
    }
}
