using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Karo.Gui
{
    /// <summary>
    /// Form for creating player settings
    /// </summary>
    public partial class PlayerSetup : Form
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public PlayerSetup()
        {
            InitializeComponent();

            mPlayerAAlgoComboBox.SelectedIndex = 0;
            mPlayerBAlgoComboBox.SelectedIndex = 2;

            PlayerA = new PlayerSettings();
            PlayerB = new PlayerSettings();
        }

        /// <summary>
        /// Playersettings for A
        /// </summary>
        public PlayerSettings PlayerA { get; private set; }

        /// <summary>
        /// Playersettings for B
        /// </summary>
        public PlayerSettings PlayerB { get; private set; }

        /// <summary>
        /// Max ai moves
        /// </summary>
        public int MaxAIMoves { get; private set; }

        /// <summary>
        /// Refreshrate
        /// </summary>
        public int RefreshRate { get; private set; }

        /// <summary>
        /// Accept button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Accept(object sender, EventArgs e)
        {
            AlgorithmType algoA = AlgorithmType.Random;
            if (mPlayerAAlgoComboBox.SelectedIndex == 1)
                algoA = AlgorithmType.MiniMax;
            else if (mPlayerAAlgoComboBox.SelectedIndex == 2)
                algoA = AlgorithmType.AlphaBeta;
            else
                algoA = AlgorithmType.Random;

            EvaluationType etA = EvaluationType.FreeSpace;
            if (mAbetterone.Checked)
                etA = EvaluationType.BetterOne;

            EvaluationType etB = EvaluationType.FreeSpace;
            if (mBbetterone.Checked)
                etB = EvaluationType.BetterOne;

            PlayerA = new PlayerSettings(
                mPlayerAAIYes.Checked, algoA, (int)mPlayerAPlieDepth.Value, 
                mPlayerATransYes.Checked, mPlayerAMoveYes.Checked, etA);

            AlgorithmType algoB = AlgorithmType.Random;
            if (mPlayerBAlgoComboBox.SelectedIndex == 1)
                algoB = AlgorithmType.MiniMax;
            else if (mPlayerBAlgoComboBox.SelectedIndex == 2)
                algoB = AlgorithmType.AlphaBeta;
            else
                algoB = AlgorithmType.Random;

            PlayerB = new PlayerSettings(
                mPlayerBAIYes.Checked, algoB, (int)mPlayerBPlieDepth.Value,
                mPlayerBTransYes.Checked, mPlayerBMoveYes.Checked, etB);

            MaxAIMoves = (int)mAIMoves.Value;
            RefreshRate = (int)numericUpDown1.Value;

            this.Visible = false;
        }

        /// <summary>
        /// Reset all fields
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ResetFields(object sender, EventArgs e)
        {
            mPlayerAAINo.Checked = true;
            mPlayerAAlgoComboBox.SelectedIndex = 0;
            mPlayerAPlieDepth.Value = 1;
            mPlayerATransNo.Checked = true;
            mPlayerAMoveNo.Checked = true;

            mPlayerBAINo.Checked = true;
            mPlayerBAlgoComboBox.SelectedIndex = 0;
            mPlayerBPlieDepth.Value = 1;
            mPlayerBTransNo.Checked = true;
            mPlayerBMoveNo.Checked = true;

            mAIMoves.Value = 1;
        }

        /// <summary>
        /// Close form
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Close(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
