/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmSymbolBoxesPwdSettings.cs
///   Description :  Symbol boxes password settings window module
/// </summary>

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using DataModule;
using Encryption;
using ServerConnector;

namespace ManagementTool
{

    /// <summary>
    /// Symbol boxes password settings window class
    /// </summary>
    public partial class fmSymbolBoxesPwdSettings : Form
    {
        #region DB manager

        // Database manager instance
        private DataBaseManager _dbManager;

        // Database manager property
        public DataBaseManager dbManager
        {
            get
            {
                return _dbManager;
            }

            set
            {
                _dbManager = value;
            }
        }

        #endregion

        #region Encryption

        // Encryptor instance
        private Encryptor _encryptor;

        // Encryptor property
        public Encryptor encryptor
        {
            get
            {
                return _encryptor;
            }

            set
            {
                _encryptor = value;
            }
        }
                
        #endregion

        #region Constants

        // Symbol box rules range

        // Joker 1
        public const int TWO_SYM_PWD_JOKER_1_MIN = 101;
        public const int TWO_SYM_PWD_JOKER_1_MAX = 106;

        // Joker 2
        public const int TWO_SYM_PWD_JOKER_2_MIN = 107;
        public const int TWO_SYM_PWD_JOKER_2_MAX = 112;

        // Formula
        public const int TWO_SYM_PWD_FORMULA_MIN = 113;
        public const int TWO_SYM_PWD_FORMULA_MAX = 116;

        //Pair location
        public const int TWO_SYM_PWD_PAIR_LOCATION_MIN = 117;
        public const int TWO_SYM_PWD_PAIR_LOCATION_MAX = 124;

        //Symbol location
        public const int TWO_SYM_PWD_SYMBOL_LOCATION_MIN = 125;
        public const int TWO_SYM_PWD_SYMBOL_LOCATION_MAX = 126;



        // Joker 1
        public const int ONE_SYM_PWD_JOKER_1_MIN = 127;
        public const int ONE_SYM_PWD_JOKER_1_MAX = 132;

        // Joker 2
        public const int ONE_SYM_PWD_JOKER_2_MIN = 133;
        public const int ONE_SYM_PWD_JOKER_2_MAX = 138;

        // Formula
        public const int ONE_SYM_PWD_FORMULA_MIN = 139;
        public const int ONE_SYM_PWD_FORMULA_MAX = 142;

        //Symbol location
        public const int ONE_SYM_PWD_SYMBOL_LOCATION_MIN = 143;
        public const int ONE_SYM_PWD_SYMBOL_LOCATION_MAX = 150;
        
        

        // Pair location values
        public const int PAIR_LOCATION_UPPER_LEFT = 0;
        public const int PAIR_LOCATION_UPPER = 1;
        public const int PAIR_LOCATION_UPPER_RIGHT = 2;
        public const int PAIR_LOCATION_RIGHT = 3;
        public const int PAIR_LOCATION_LOWER_RIGHT = 4;
        public const int PAIR_LOCATION_LOWER = 5;
        public const int PAIR_LOCATION_LOWER_LEFT = 6;
        public const int PAIR_LOCATION_LEFT = 7;

        //Symbol location values
        public const int SYMBOL_LOCATION_LEFT = 0;
        public const int SYMBOL_LOCATION_RIGHT = 1;
        public const int SYMBOL_LOCATION_UPPER_LEFT = 2;
        public const int SYMBOL_LOCATION_UPPER = 3;
        public const int SYMBOL_LOCATION_UPPER_RIGHT = 4;
        public const int SYMBOL_LOCATION_LOWER_LEFT = 5;
        public const int SYMBOL_LOCATION_LOWER = 6;
        public const int SYMBOL_LOCATION_LOWER_RIGHT = 7;

        #endregion

        #region Constructing

        /// <summary>
        /// Constructor
        /// </summary>
        public fmSymbolBoxesPwdSettings(DataBaseManager dbManager, Encryptor encryptor, bool personalPage)
        {
            this.dbManager = dbManager;
            this.encryptor = encryptor;

            _personalPage = personalPage;
            _commited = false;

            currentTmpJoker1RuleID = -1;
            currentTmpJoker2RuleID = -1;
            currentTmpFormulaRuleID = -1;
            currentTmpPairLocationRuleID = -1;
            currentTmpSymbolLocationRuleID = -1;

            currentJoker1RuleID = -1;
            currentJoker2RuleID = -1;
            currentFormulaRuleID = -1;
            currentPairLocationRuleID = -1;
            currentSymbolLocationRuleID = -1;

            _pwdReseted = 0;

            InitializeComponent();
            
        }

        /// <summary>
        /// Form load
        /// </summary>
        private void fmSymbolBoxesPwdSettings_Load(object sender, EventArgs e)
        {
            switch (GetPasswordType())
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        joker1RulesNames = GetRuleNames(ONE_SYM_PWD_JOKER_1_MIN, ONE_SYM_PWD_JOKER_1_MAX);
                        joker2RulesNames = GetRuleNames(ONE_SYM_PWD_JOKER_2_MIN, ONE_SYM_PWD_JOKER_2_MAX);
                        formulaRulesNames = GetRuleNames(ONE_SYM_PWD_FORMULA_MIN, ONE_SYM_PWD_FORMULA_MAX);
                        symbolLocationRulesNames = GetRuleNames(ONE_SYM_PWD_SYMBOL_LOCATION_MIN, ONE_SYM_PWD_SYMBOL_LOCATION_MAX);
                        symbolBoxCentralLabel.Text = "5";
                        break;

                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        joker1RulesNames = GetRuleNames(TWO_SYM_PWD_JOKER_1_MIN, TWO_SYM_PWD_JOKER_1_MAX);
                        joker2RulesNames = GetRuleNames(TWO_SYM_PWD_JOKER_2_MIN, TWO_SYM_PWD_JOKER_2_MAX);
                        formulaRulesNames = GetRuleNames(TWO_SYM_PWD_FORMULA_MIN, TWO_SYM_PWD_FORMULA_MAX);
                        pairLocationRulesNames = GetRuleNames(TWO_SYM_PWD_PAIR_LOCATION_MIN, TWO_SYM_PWD_PAIR_LOCATION_MAX);
                        symbolLocationRulesNames = GetRuleNames(TWO_SYM_PWD_SYMBOL_LOCATION_MIN, TWO_SYM_PWD_SYMBOL_LOCATION_MAX);
                        symbolBoxCentralLabel.Text = "18";
                        break;

                    }
            }

            CustomizeControls();
        }

        #endregion

        #region Customize

        // Personal page flag
        private bool _personalPage;

        // Password reseted flag
        private short _pwdReseted;

        // User token buffers
        private int _begUserToken, _begUserTmpToken;

        // Password type (One or two symbols)
        private int _passwordType;

        // Commit flag
        private bool _commited;

        public bool Commited
        {
            get
            {
                return _commited;
            }
        }

        // Buffer for current rules
        private int currentTmpJoker1RuleID;
        private int currentTmpJoker2RuleID;
        private int currentTmpFormulaRuleID;
        private int currentTmpPairLocationRuleID;
        private int currentTmpSymbolLocationRuleID;

        private int currentJoker1RuleID;
        private int currentJoker2RuleID;
        private int currentFormulaRuleID;
        private int currentPairLocationRuleID;
        private int currentSymbolLocationRuleID;


        // Joker 1 rules names
        Dictionary<int, string> joker1RulesNames;

        // Joker 2 rules names
        Dictionary<int, string> joker2RulesNames;

        // Formula rules names
        Dictionary<int, string> formulaRulesNames;

        // Pair location rules names
        Dictionary<int, string> pairLocationRulesNames;

        // Symbol location rules names
        Dictionary<int, string> symbolLocationRulesNames;


        /// <summary>
        /// Find rule name by ID
        /// </summary>
        /// <param name="ID">rule ID</param>
        /// <param name="rulesList">rules list</param>
        /// <returns>rule name</returns>
        private string GetRuleNameByID(int ID, Dictionary<int, string> rulesList)
        {
            return rulesList.ContainsKey(ID) ? rulesList[ID] : String.Empty;
        }


        /// <summary>
        /// Get rule ID by name
        /// </summary>
        /// <param name="ruleName">rule name</param>
        /// <param name="rulesList">rules list</param>
        /// <returns>rule ID</returns>
        private int GetRuleIDByName(string ruleName, Dictionary<int, string> rulesList)
        {
            return rulesList.FirstOrDefault(x => x.Value.Equals(ruleName)).Key;
        }

        /// <summary>
        /// Get list of rules names
        /// </summary>
        private Dictionary<int, string> GetRuleNames(int minID, int maxID)
        {
            // Decrypt password construction rules names
            if (dbManager.passwordConstructionRulesBindingSource.Count > 0)
            {
                Dictionary<int, string> ruleNames = new Dictionary<int, string>();

                for (int i = minID; i <= maxID; i++)
                {
                    string filterExpr = "ID = " + i.ToString();
                    DataRow[] selRows = dbManager.dataSet.PasswordConstructionRules.Select(filterExpr);
                    if ((selRows != null) && (selRows.Length > 0))
                    {
                        byte[] encName = selRows[0]["Name", DataRowVersion.Original] as byte[];
                        string decName = encryptor.DecryptString(encName);

                        ruleNames.Add(i, decName);
                    }
                }

                return ruleNames;
            }
            else
                return null;
        }

        /// <summary>
        /// Get password type
        /// </summary>
        int GetPasswordType()
        {
            if (_personalPage)
            {
                _passwordType = (int)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["PwdTypeID"];
            }
            else
            {
                _passwordType = (int)(dbManager.usersBindingSource.Current as DataRowView).Row["PwdTypeID"];
            }

            return _passwordType;
        }

        /// <summary>
        /// Customize temp password controls
        /// </summary>
        private void CustomizeTempPassword()
        {
            // Make changes to UI
            if (_passwordType == fmConnect.ONE_SYMBOL_BOX_PWD)
            {
                tmpPairLocationLabel.Visible = false;
                tmpPairLocationComboBox.Visible = false;
                tmpSymbolLocationLabel.Location = tmpPairLocationLabel.Location;
                tmpSymbolLocationComboBox.Location = tmpPairLocationComboBox.Location;

                tmpLabelULR.Visible = false;
                tmpLabelUR.Visible = false;
                tmpLabelURL.Visible = false;

                tmpLabelLR.Visible = false;
                tmpLabelRL.Visible = false;

                tmpLabelBLR.Visible = false;
                tmpLabelBR.Visible = false;
                tmpLabelBRL.Visible = false;

                tmpLabelUL.Left += tmpLabelUL.Width / 2;
                tmpLabelBL.Left += tmpLabelBL.Width / 2;
            }


            // Fill joker 1 combobox
            foreach (KeyValuePair<int, string> pair in joker1RulesNames)
               tmpJoker1ComboBox.Items.Add(pair.Value);
            
            // Fill joker 2 combobox
            foreach (KeyValuePair<int, string> pair in joker2RulesNames)
                tmpJoker2ComboBox.Items.Add(pair.Value);

            // Fill formula combobox
            foreach (KeyValuePair<int, string> pair in formulaRulesNames)
                tmpFormulaComboBox.Items.Add(pair.Value);

            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
            {
                // Fill pair location combobox
                foreach (KeyValuePair<int, string> pair in pairLocationRulesNames)
                    tmpPairLocationComboBox.Items.Add(pair.Value);
            }

            // Fill symbol location combobox
            foreach (KeyValuePair<int, string> pair in symbolLocationRulesNames)
                tmpSymbolLocationComboBox.Items.Add(pair.Value);

            int JOKER_1_MIN = -1, JOKER_1_MAX = -1;
            int JOKER_2_MIN = -1, JOKER_2_MAX = -1;
            int FORMULA_MIN = -1, FORMULA_MAX = -1;
            int PAIR_LOCATION_MIN = -1, PAIR_LOCATION_MAX = -1;
            int SYMBOL_LOCATION_MIN = -1, SYMBOL_LOCATION_MAX = -1;

            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        JOKER_1_MIN = ONE_SYM_PWD_JOKER_1_MIN;
                        JOKER_1_MAX = ONE_SYM_PWD_JOKER_1_MAX;
                        JOKER_2_MIN = ONE_SYM_PWD_JOKER_2_MIN;
                        JOKER_2_MAX = ONE_SYM_PWD_JOKER_2_MAX;
                        FORMULA_MIN = ONE_SYM_PWD_FORMULA_MIN;
                        FORMULA_MAX = ONE_SYM_PWD_FORMULA_MAX;
                        SYMBOL_LOCATION_MIN = ONE_SYM_PWD_SYMBOL_LOCATION_MIN;
                        SYMBOL_LOCATION_MAX = ONE_SYM_PWD_SYMBOL_LOCATION_MAX;
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        JOKER_1_MIN = TWO_SYM_PWD_JOKER_1_MIN;
                        JOKER_1_MAX = TWO_SYM_PWD_JOKER_1_MAX;
                        JOKER_2_MIN = TWO_SYM_PWD_JOKER_2_MIN;
                        JOKER_2_MAX = TWO_SYM_PWD_JOKER_2_MAX;
                        FORMULA_MIN = TWO_SYM_PWD_FORMULA_MIN;
                        FORMULA_MAX = TWO_SYM_PWD_FORMULA_MAX;
                        PAIR_LOCATION_MIN = TWO_SYM_PWD_PAIR_LOCATION_MIN;
                        PAIR_LOCATION_MAX = TWO_SYM_PWD_PAIR_LOCATION_MAX;
                        SYMBOL_LOCATION_MIN = TWO_SYM_PWD_SYMBOL_LOCATION_MIN;
                        SYMBOL_LOCATION_MAX = TWO_SYM_PWD_SYMBOL_LOCATION_MAX;
                        break;
                    }
            }

            if (_personalPage)
            {
                // User token
                tmpUserTokenTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.personalUsersBindingSource, "TmpUserToken", true));
                _begUserTmpToken = (int)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["TmpUserToken"];

                // Get current temp joker1 value
                dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + JOKER_1_MIN.ToString() + ") AND (RuleID <= " + JOKER_1_MAX.ToString() + ")";
                if (dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentTmpJoker1RuleID = (int)(dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    tmpJoker1ComboBox.Text = GetRuleNameByID(currentTmpJoker1RuleID, joker1RulesNames);
                }

                // Get current temp joker2 value
                dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + JOKER_2_MIN.ToString() + ") AND (RuleID <= " + JOKER_2_MAX.ToString() + ")";
                if (dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentTmpJoker2RuleID = (int)(dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    tmpJoker2ComboBox.Text = GetRuleNameByID(currentTmpJoker2RuleID, joker2RulesNames);
                }

                // Get current temp formula value
                dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + FORMULA_MIN.ToString() + ") AND (RuleID <= " + FORMULA_MAX.ToString() + ")";
                if (dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentTmpFormulaRuleID = (int)(dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    tmpFormulaComboBox.Text = GetRuleNameByID(currentTmpFormulaRuleID, formulaRulesNames);
                }

                if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                {
                    // Get current temp pair location value
                    dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + PAIR_LOCATION_MIN.ToString() + ") AND (RuleID <= " + PAIR_LOCATION_MAX.ToString() + ")";
                    if (dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                    {
                        dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                        currentTmpPairLocationRuleID = (int)(dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                        tmpPairLocationComboBox.Text = GetRuleNameByID(currentTmpPairLocationRuleID, pairLocationRulesNames);
                    }
                }

                // Get current temp symbol location value
                dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + SYMBOL_LOCATION_MIN.ToString() + ") AND (RuleID <= " + SYMBOL_LOCATION_MAX.ToString() + ")";
                if (dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentTmpSymbolLocationRuleID = (int)(dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    tmpSymbolLocationComboBox.Text = GetRuleNameByID(currentTmpSymbolLocationRuleID, symbolLocationRulesNames);
                }
            }
            else
            {
                // User token
                tmpUserTokenTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.usersBindingSource, "TmpUserToken", true));
                _begUserTmpToken = (int)(dbManager.usersBindingSource.Current as DataRowView).Row["TmpUserToken"];

                // Get current temp joker1 value
                dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + JOKER_1_MIN.ToString() + ") AND (RuleID <= " + JOKER_1_MAX.ToString() + ")";
                if (dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentTmpJoker1RuleID = (int)(dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    tmpJoker1ComboBox.Text = GetRuleNameByID(currentTmpJoker1RuleID, joker1RulesNames);
                }

                // Get current temp joker2 value
                dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + JOKER_2_MIN.ToString() + ") AND (RuleID <= " + JOKER_2_MAX.ToString() + ")";
                if (dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentTmpJoker2RuleID = (int)(dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    tmpJoker2ComboBox.Text = GetRuleNameByID(currentTmpJoker2RuleID, joker2RulesNames);
                }

                // Get current temp formula value
                dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + FORMULA_MIN.ToString() + ") AND (RuleID <= " + FORMULA_MAX.ToString() + ")";
                if (dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentTmpFormulaRuleID = (int)(dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    tmpFormulaComboBox.Text = GetRuleNameByID(currentTmpFormulaRuleID, formulaRulesNames);
                }

                if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                {
                    // Get current temp pair location value
                    dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + PAIR_LOCATION_MIN.ToString() + ") AND (RuleID <= " + PAIR_LOCATION_MAX.ToString() + ")";
                    if (dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                    {
                        dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                        currentTmpPairLocationRuleID = (int)(dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                        tmpPairLocationComboBox.Text = GetRuleNameByID(currentTmpPairLocationRuleID, pairLocationRulesNames);
                    }
                }
   
                // Get current temp symbol location value
                dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + SYMBOL_LOCATION_MIN.ToString() + ") AND (RuleID <= " + SYMBOL_LOCATION_MAX.ToString() + ")";
                if (dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentTmpSymbolLocationRuleID = (int)(dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    tmpSymbolLocationComboBox.Text = GetRuleNameByID(currentTmpSymbolLocationRuleID, symbolLocationRulesNames);
                }
            }
        }


        /// <summary>
        /// Customize main password controls
        /// </summary>
        private void CustomizeMainPassword()
        {
            // Make changes to UI
            if (_passwordType == fmConnect.ONE_SYMBOL_BOX_PWD)
            {
                pairLocationLabel.Visible = false;
                pairLocationComboBox.Visible = false;
                symbolLocationLabel.Location = pairLocationLabel.Location;
                symbolLocationComboBox.Location = pairLocationComboBox.Location;

                labelULR.Visible = false;
                labelUR.Visible = false;
                labelURL.Visible = false;

                labelLR.Visible = false;
                labelRL.Visible = false;

                labelBLR.Visible = false;
                labelBR.Visible = false;
                labelBRL.Visible = false;

                labelUL.Left += labelUL.Width / 2;
                labelBL.Left += labelBL.Width / 2;
            }

            // Fill joker 1 combo box
            foreach (KeyValuePair<int, string> pair in joker1RulesNames)
                joker1ComboBox.Items.Add(pair.Value);

            // Fill joker 2 combo box
            foreach (KeyValuePair<int, string> pair in joker2RulesNames)
                joker2ComboBox.Items.Add(pair.Value);

            // Fill formula combo box
            foreach (KeyValuePair<int, string> pair in formulaRulesNames)
                formulaComboBox.Items.Add(pair.Value);

            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
            {
                // Fill pair location combo box
                foreach (KeyValuePair<int, string> pair in pairLocationRulesNames)
                    pairLocationComboBox.Items.Add(pair.Value);
            }

            // Fill symbol location combo box
            foreach (KeyValuePair<int, string> pair in symbolLocationRulesNames)
                symbolLocationComboBox.Items.Add(pair.Value);

            int JOKER_1_MIN = -1, JOKER_1_MAX = -1;
            int JOKER_2_MIN = -1, JOKER_2_MAX = -1;
            int FORMULA_MIN = -1, FORMULA_MAX = -1;
            int PAIR_LOCATION_MIN = -1, PAIR_LOCATION_MAX = -1;
            int SYMBOL_LOCATION_MIN = -1, SYMBOL_LOCATION_MAX = -1;

            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        JOKER_1_MIN = ONE_SYM_PWD_JOKER_1_MIN;
                        JOKER_1_MAX = ONE_SYM_PWD_JOKER_1_MAX;
                        JOKER_2_MIN = ONE_SYM_PWD_JOKER_2_MIN;
                        JOKER_2_MAX = ONE_SYM_PWD_JOKER_2_MAX;
                        FORMULA_MIN = ONE_SYM_PWD_FORMULA_MIN;
                        FORMULA_MAX = ONE_SYM_PWD_FORMULA_MAX;
                        SYMBOL_LOCATION_MIN = ONE_SYM_PWD_SYMBOL_LOCATION_MIN;
                        SYMBOL_LOCATION_MAX = ONE_SYM_PWD_SYMBOL_LOCATION_MAX;
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        JOKER_1_MIN = TWO_SYM_PWD_JOKER_1_MIN;
                        JOKER_1_MAX = TWO_SYM_PWD_JOKER_1_MAX;
                        JOKER_2_MIN = TWO_SYM_PWD_JOKER_2_MIN;
                        JOKER_2_MAX = TWO_SYM_PWD_JOKER_2_MAX;
                        FORMULA_MIN = TWO_SYM_PWD_FORMULA_MIN;
                        FORMULA_MAX = TWO_SYM_PWD_FORMULA_MAX;
                        PAIR_LOCATION_MIN = TWO_SYM_PWD_PAIR_LOCATION_MIN;
                        PAIR_LOCATION_MAX = TWO_SYM_PWD_PAIR_LOCATION_MAX;
                        SYMBOL_LOCATION_MIN = TWO_SYM_PWD_SYMBOL_LOCATION_MIN;
                        SYMBOL_LOCATION_MAX = TWO_SYM_PWD_SYMBOL_LOCATION_MAX;
                        break;
                    }
            }

            if (_personalPage)
            {
                // User token
                userTokenTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.personalUsersBindingSource, "UserToken", true));
                _begUserToken = (int)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["UserToken"];

                // Get current temp joker1 value
                dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + JOKER_1_MIN.ToString() + ") AND (RuleID <= " + JOKER_1_MAX.ToString() + ")";
                if (dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentJoker1RuleID = (int)(dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    joker1ComboBox.Text = GetRuleNameByID(currentJoker1RuleID, joker1RulesNames);
                }

                // Get current temp joker2 value
                dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + JOKER_2_MIN.ToString() + ") AND (RuleID <= " + JOKER_2_MAX.ToString() + ")";
                if (dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentJoker2RuleID = (int)(dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    joker2ComboBox.Text = GetRuleNameByID(currentJoker2RuleID, joker2RulesNames);
                }

                // Get current temp formula value
                dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + FORMULA_MIN.ToString() + ") AND (RuleID <= " + FORMULA_MAX.ToString() + ")";
                if (dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentFormulaRuleID = (int)(dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    formulaComboBox.Text = GetRuleNameByID(currentFormulaRuleID, formulaRulesNames);
                }

                if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                {
                    // Get current temp pair location value
                    dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + PAIR_LOCATION_MIN.ToString() + ") AND (RuleID <= " + PAIR_LOCATION_MAX.ToString() + ")";
                    if (dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                    {
                        dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                        currentPairLocationRuleID = (int)(dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                        pairLocationComboBox.Text = GetRuleNameByID(currentPairLocationRuleID, pairLocationRulesNames);
                    }
                }

                // Get current temp symbol location value
                dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + SYMBOL_LOCATION_MIN.ToString() + ") AND (RuleID <= " + SYMBOL_LOCATION_MAX.ToString() + ")";
                if (dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentSymbolLocationRuleID = (int)(dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    symbolLocationComboBox.Text = GetRuleNameByID(currentSymbolLocationRuleID, symbolLocationRulesNames);
                }
            }
            else
            {
                // User token
                userTokenTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.usersBindingSource, "UserToken", true));
                _begUserToken = (int)(dbManager.usersBindingSource.Current as DataRowView).Row["UserToken"];


                // Get current temp joker1 value
                dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + JOKER_1_MIN.ToString() + ") AND (RuleID <= " + JOKER_1_MAX.ToString() + ")";
                if (dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentJoker1RuleID = (int)(dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    joker1ComboBox.Text = GetRuleNameByID(currentJoker1RuleID, joker1RulesNames);
                }

                // Get current temp joker2 value
                dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + JOKER_2_MIN.ToString() + ") AND (RuleID <= " + JOKER_2_MAX.ToString() + ")";
                if (dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentJoker2RuleID = (int)(dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    joker2ComboBox.Text = GetRuleNameByID(currentJoker2RuleID, joker2RulesNames);
                }

                // Get current temp formula value
                dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + FORMULA_MIN.ToString() + ") AND (RuleID <= " + FORMULA_MAX.ToString() + ")";
                if (dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentFormulaRuleID = (int)(dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    formulaComboBox.Text = GetRuleNameByID(currentFormulaRuleID, formulaRulesNames);
                }

                if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                {
                    // Get current temp pair location value
                    dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + PAIR_LOCATION_MIN.ToString() + ") AND (RuleID <= " + PAIR_LOCATION_MAX.ToString() + ")";
                    if (dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                    {
                        dbManager.fkUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                        currentPairLocationRuleID = (int)(dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                        pairLocationComboBox.Text = GetRuleNameByID(currentPairLocationRuleID, pairLocationRulesNames);
                    }
                }

                // Get current temp symbol location value
                dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + SYMBOL_LOCATION_MIN.ToString() + ") AND (RuleID <= " + SYMBOL_LOCATION_MAX.ToString() + ")";

                if (dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Count > 0)
                {
                    dbManager.fkUserPasswordConstructionRulesUsersBindingSource.MoveFirst();
                    currentSymbolLocationRuleID = (int)(dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Current as DataRowView).Row["RuleID"];
                    symbolLocationComboBox.Text = GetRuleNameByID(currentSymbolLocationRuleID, symbolLocationRulesNames);
                }
            }
        }

        /// <summary>
        /// Customize controls
        /// </summary>
        private void CustomizeControls()
        {
            // Check password reseted flag
            if (_personalPage)
            {
                _pwdReseted = (short)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["PwdResetted"];
                if (_pwdReseted != 0)
                {
                    tmpJoker1ComboBox.Enabled = false;
                    tmpJoker2ComboBox.Enabled = false;
                    tmpFormulaComboBox.Enabled = false;
                    tmpPairLocationComboBox.Enabled = false;
                    tmpSymbolLocationComboBox.Enabled = false;
                    tmpUserTokenTextBox.ReadOnly = true;
                }
            }
            else
            {
                _pwdReseted = (short)(dbManager.usersBindingSource.Current as DataRowView).Row["PwdResetted"];
            }

            // Clear tab pages
            passwordSettingsTabControl.TabPages.Clear();

            // Customize main password
            passwordSettingsTabControl.TabPages.Add(mainPasswordTabPage);
            dbManager.userPasswordConstructionRulesTableAdapter.Fill(dbManager.dataSet.UserPasswordConstructionRules);
            CustomizeMainPassword();

            // Customize temp password if needed
            if (_pwdReseted != 0)
            {
                passwordSettingsTabControl.TabPages.Add(tmpPasswordTabPage);
                dbManager.tmpUserPasswordConstructionRulesTableAdapter.Fill(dbManager.dataSet.TmpUserPasswordConstructionRules);
                CustomizeTempPassword();
            }
        }

        /// <summary>
        /// Delete temp password
        /// </summary>
        private void DeletePreviousTempPassword()
        {
            int userID = -1;

            if (_personalPage)
                userID = (int)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["ID"];
            else
                userID = (int)(dbManager.usersBindingSource.Current as DataRowView).Row["ID"];

            // Delete previous temp password 
            string filterExpr = "";

            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD : 
                    {
                        filterExpr = "((UserID = " + userID.ToString() + ") AND (RuleID >= " + ONE_SYM_PWD_JOKER_1_MIN.ToString() + ") AND (RuleID <= " + ONE_SYM_PWD_SYMBOL_LOCATION_MAX.ToString() + "))";
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        filterExpr = "((UserID = " + userID.ToString() + ") AND (RuleID >= " + TWO_SYM_PWD_JOKER_1_MIN.ToString() + ") AND (RuleID <= " + TWO_SYM_PWD_SYMBOL_LOCATION_MAX.ToString() + "))";
                        break;
                    }
            }

            DataRow [] selRows = dbManager.dataSet.TmpUserPasswordConstructionRules.Select(filterExpr);
            if ((selRows != null) && (selRows.Length > 0))
            {
                foreach (DataRow row in selRows)
                {
                    int ruleID = (int)row["RuleID"];
                    int? ruleOrder = (int?)row["RulesOrder"];
                    dbManager.tmpUserPasswordConstructionRulesTableAdapter.Delete(userID, ruleID, ruleOrder);
                }
            }
        }
        
        /// <summary>
        /// Delete main password
        /// </summary>
        private void DeletePreviousMainPassword()
        {
            int userID = -1;

            if (_personalPage)
                userID = (int)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["ID"];
            else
                userID = (int)(dbManager.usersBindingSource.Current as DataRowView).Row["ID"];

            string filterExpr = "";

            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        filterExpr = "((UserID = " + userID.ToString() + ") AND (RuleID >= " + ONE_SYM_PWD_JOKER_1_MIN.ToString() + ") AND (RuleID <= " + ONE_SYM_PWD_SYMBOL_LOCATION_MAX.ToString() + "))";
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        filterExpr = "((UserID = " + userID.ToString() + ") AND (RuleID >= " + TWO_SYM_PWD_JOKER_1_MIN.ToString() + ") AND (RuleID <= " + TWO_SYM_PWD_SYMBOL_LOCATION_MAX.ToString() + "))";
                        break;
                    }
            }

            DataRow [] selRows = dbManager.dataSet.UserPasswordConstructionRules.Select(filterExpr);
            if ((selRows != null) && (selRows.Length > 0))
            {
                foreach (DataRow row in selRows)
                {
                    int ruleID = (int)row["RuleID"];
                    int? ruleOrder = (int?)row["RulesOrder"];
                    dbManager.userPasswordConstructionRulesTableAdapter.Delete(userID, ruleID, ruleOrder);
                }
            }
        }

        /// <summary>
        /// Save current temp password
        /// </summary>
        private void SaveCurrentTempPassword()
        {
            int userID = -1;

            if (_personalPage)
                userID = (int)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["ID"];
            else
                userID = (int)(dbManager.usersBindingSource.Current as DataRowView).Row["ID"];

            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        if (currentTmpJoker1RuleID != -1)
                            dbManager.tmpUserPasswordConstructionRulesTableAdapter.Insert(userID, currentTmpJoker1RuleID, 1);

                        if (currentTmpJoker2RuleID != -1)
                            dbManager.tmpUserPasswordConstructionRulesTableAdapter.Insert(userID, currentTmpJoker2RuleID, 2);

                        if (currentTmpFormulaRuleID != -1)
                            dbManager.tmpUserPasswordConstructionRulesTableAdapter.Insert(userID, currentTmpFormulaRuleID, 3);

                        if (currentTmpSymbolLocationRuleID != -1)
                            dbManager.tmpUserPasswordConstructionRulesTableAdapter.Insert(userID, currentTmpSymbolLocationRuleID, 4);

                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        if (currentTmpJoker1RuleID != -1)
                            dbManager.tmpUserPasswordConstructionRulesTableAdapter.Insert(userID, currentTmpJoker1RuleID, 1);

                        if (currentTmpJoker2RuleID != -1)
                            dbManager.tmpUserPasswordConstructionRulesTableAdapter.Insert(userID, currentTmpJoker2RuleID, 2);

                        if (currentTmpFormulaRuleID != -1)
                            dbManager.tmpUserPasswordConstructionRulesTableAdapter.Insert(userID, currentTmpFormulaRuleID, 3);

                        if (currentTmpPairLocationRuleID != -1)
                            dbManager.tmpUserPasswordConstructionRulesTableAdapter.Insert(userID, currentTmpPairLocationRuleID, 4);

                        if (currentTmpSymbolLocationRuleID != -1)
                            dbManager.tmpUserPasswordConstructionRulesTableAdapter.Insert(userID, currentTmpSymbolLocationRuleID, 5);

                        break;
                    }
            }
        }

        /// <summary>
        /// Save current main password
        /// </summary>
        private void SaveCurrentMainPassword()
        {
            int userID = -1;

            if (_personalPage)
                userID = (int)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["ID"];
            else
                userID = (int)(dbManager.usersBindingSource.Current as DataRowView).Row["ID"];

            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        if (currentJoker1RuleID != -1)
                            dbManager.userPasswordConstructionRulesTableAdapter.Insert(userID, currentJoker1RuleID, 1);

                        if (currentJoker2RuleID != -1)
                            dbManager.userPasswordConstructionRulesTableAdapter.Insert(userID, currentJoker2RuleID, 2);

                        if (currentFormulaRuleID != -1)
                            dbManager.userPasswordConstructionRulesTableAdapter.Insert(userID, currentFormulaRuleID, 3);

                        if (currentSymbolLocationRuleID != -1)
                            dbManager.userPasswordConstructionRulesTableAdapter.Insert(userID, currentSymbolLocationRuleID, 4);

                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        if (currentJoker1RuleID != -1)
                            dbManager.userPasswordConstructionRulesTableAdapter.Insert(userID, currentJoker1RuleID, 1);

                        if (currentJoker2RuleID != -1)
                            dbManager.userPasswordConstructionRulesTableAdapter.Insert(userID, currentJoker2RuleID, 2);

                        if (currentFormulaRuleID != -1)
                            dbManager.userPasswordConstructionRulesTableAdapter.Insert(userID, currentFormulaRuleID, 3);

                        if (currentPairLocationRuleID != -1)
                            dbManager.userPasswordConstructionRulesTableAdapter.Insert(userID, currentPairLocationRuleID, 4);

                        if (currentSymbolLocationRuleID != -1)
                            dbManager.userPasswordConstructionRulesTableAdapter.Insert(userID, currentSymbolLocationRuleID, 5);

                        break;
                    }
            }
        }


        #endregion

        #region Buttons

        /// <summary>
        /// Button OK click
        /// </summary>
        private void btnOK_Click(object sender, EventArgs e)
        {
            
            if (_pwdReseted != 0)
            {
                DeletePreviousTempPassword();
                SaveCurrentTempPassword();
            }

            DeletePreviousMainPassword();
            SaveCurrentMainPassword();

            if (_personalPage)
            {
                dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.EndEdit();
                dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.EndEdit();
                dbManager.personalUsersBindingSource.EndEdit();
            }
            else
            {
                dbManager.fkUserPasswordConstructionRulesUsersBindingSource.EndEdit();
                dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.EndEdit();
                dbManager.usersBindingSource.EndEdit();
            }

            dbManager.UpdateAll();

            _commited = true;

            Close();
        }

        /// <summary>
        /// Button Cancel click
        /// </summary>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            if (_personalPage)
            {
                dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.CancelEdit();
                dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.CancelEdit();
                (dbManager.personalUsersBindingSource.Current as DataRowView).Row["UserToken"] = _begUserToken;
                if (_pwdReseted != 0) (dbManager.personalUsersBindingSource.Current as DataRowView).Row["TmpUserToken"] = _begUserTmpToken;
            }
            else
            {
                dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.CancelEdit();
                dbManager.fkUserPasswordConstructionRulesUsersBindingSource.CancelEdit();
                (dbManager.usersBindingSource.Current as DataRowView).Row["UserToken"] = _begUserToken;
                if (_pwdReseted != 0) (dbManager.usersBindingSource.Current as DataRowView).Row["TmpUserToken"] = _begUserTmpToken;
            }

            _commited = false;

            Close();
        }

        #endregion

        #region Symbol labels

        /// <summary>
        /// Temp password. Upper left click
        /// </summary>
        private void tmpLabelULL_Click(object sender, EventArgs e)
        {            
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_UPPER_LEFT, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_UPPER_LEFT, pairLocationRulesNames);
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Temp password. Upper left click
        /// </summary>
        private void tmpLabelULR_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_UPPER_LEFT, pairLocationRulesNames);

            tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Temp password. Upper click
        /// </summary>
        private void tmpLabelUL_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_UPPER, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_UPPER, pairLocationRulesNames);
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Temp password. Upper click
        /// </summary>
        private void tmpLabelUR_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_UPPER, pairLocationRulesNames);

            tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Temp password. Upper right click
        /// </summary>
        private void tmpLabelURL_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_UPPER_RIGHT, pairLocationRulesNames);

            tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Temp password. Upper right click
        /// </summary>
        private void tmpLabelURR_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_UPPER_RIGHT, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_UPPER_RIGHT, pairLocationRulesNames);
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Temp password. Left click
        /// </summary>
        private void tmpLabelLL_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LEFT, pairLocationRulesNames);
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
                        break;
                    }
            }
                        
        }

        /// <summary>
        /// Temp password. Left click
        /// </summary>
        private void tmpLabelLR_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LEFT, pairLocationRulesNames);

            tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Temp password. Right click
        /// </summary>
        private void tmpLabelRL_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_RIGHT, pairLocationRulesNames);

            tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Temp password. Right click
        /// </summary>
        private void tmpLabelRR_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_RIGHT, pairLocationRulesNames);
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Temp password. Bottom left click
        /// </summary>
        private void tmpLabelBLL_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LOWER_LEFT, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LOWER_LEFT, pairLocationRulesNames);
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Temp password. Bottom left click
        /// </summary>
        private void tmpLabelBLR_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LOWER_LEFT, pairLocationRulesNames);

            tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Temp password. Bottom click
        /// </summary>
        private void tmpLabelBL_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LOWER, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LOWER, pairLocationRulesNames);
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Temp password. Bottom click
        /// </summary>
        private void tmpLabelBR_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LOWER, pairLocationRulesNames);

            tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Temp password. Bottom right click
        /// </summary>
        private void tmpLabelBRL_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LOWER_RIGHT, pairLocationRulesNames);

            tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Temp password. Bottom right click
        /// </summary>
        private void tmpLabelBRR_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LOWER_RIGHT, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        tmpPairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LOWER_RIGHT, pairLocationRulesNames);
                        tmpSymbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Main password. Upper left click
        /// </summary>
        private void labelULL_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        symbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_UPPER_LEFT, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_UPPER_LEFT, pairLocationRulesNames);
                        symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Main password. Upper left click
        /// </summary>
        private void labelULR_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_UPPER_LEFT, pairLocationRulesNames);

            symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Main password. Upper click
        /// </summary>
        private void labelUL_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        symbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_UPPER, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_UPPER, pairLocationRulesNames);
                        symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Main password. Upper click
        /// </summary>
        private void labelUR_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_UPPER, pairLocationRulesNames);

            symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Main password. Upper right click
        /// </summary>
        private void labelURL_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_UPPER_RIGHT, pairLocationRulesNames);

            symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Main password. Upper right click
        /// </summary>
        private void labelURR_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        symbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_UPPER_RIGHT, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_UPPER_RIGHT, pairLocationRulesNames);
                        symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Main password. Left click
        /// </summary>
        private void labelLL_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        symbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LEFT, pairLocationRulesNames);
                        symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Main password. Left click
        /// </summary>
        private void labelLR_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LEFT, pairLocationRulesNames);

            symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Main password. Right click
        /// </summary>
        private void labelRL_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_RIGHT, pairLocationRulesNames);

            symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Main password. Right click
        /// </summary>
        private void labelRR_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        symbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_RIGHT, pairLocationRulesNames);
                        symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Main password. Bottom left click
        /// </summary>
        private void labelBLL_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        symbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LOWER_LEFT, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LOWER_LEFT, pairLocationRulesNames);
                        symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Main password. Bottom left click
        /// </summary>
        private void labelBLR_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LOWER_LEFT, pairLocationRulesNames);

            symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Main password. Bottom click
        /// </summary>
        private void labelBL_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        symbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LOWER, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LOWER, pairLocationRulesNames);
                        symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
                        break;
                    }
            }
        }

        /// <summary>
        /// Main password. Bottom click
        /// </summary>
        private void labelBR_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LOWER, pairLocationRulesNames);

            symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Main password. Bottom right click
        /// </summary>
        private void labelBRL_Click(object sender, EventArgs e)
        {
            if (_passwordType == fmConnect.TWO_SYMBOL_BOX_PWD)
                pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LOWER_RIGHT, pairLocationRulesNames);

            symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LEFT, symbolLocationRulesNames);
        }

        /// <summary>
        /// Main password. Bottom right click
        /// </summary>
        private void labelBRR_Click(object sender, EventArgs e)
        {
            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        symbolLocationComboBox.Text = GetRuleNameByID(ONE_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_LOWER_RIGHT, symbolLocationRulesNames);
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        pairLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_PAIR_LOCATION_MIN + PAIR_LOCATION_LOWER_RIGHT, pairLocationRulesNames);
                        symbolLocationComboBox.Text = GetRuleNameByID(TWO_SYM_PWD_SYMBOL_LOCATION_MIN + SYMBOL_LOCATION_RIGHT, symbolLocationRulesNames);
                        break;
                    }
            }
        }


        /// <summary>
        /// Set default colors to symbols on tmp field
        /// </summary>
        private void ClearTmpSymbolLabelBackColors()
        {
            tmpLabelULL.BackColor = Color.White;
            tmpLabelULR.BackColor = Color.White;
            tmpLabelUL.BackColor = Color.White;
            tmpLabelUR.BackColor = Color.White;
            tmpLabelURL.BackColor = Color.White;
            tmpLabelURR.BackColor = Color.White;
            tmpLabelLL.BackColor = Color.White;
            tmpLabelLR.BackColor = Color.White;
            tmpLabelRL.BackColor = Color.White;
            tmpLabelRR.BackColor = Color.White;
            tmpLabelBLL.BackColor = Color.White;
            tmpLabelBLR.BackColor = Color.White;
            tmpLabelBL.BackColor = Color.White;
            tmpLabelBR.BackColor = Color.White;
            tmpLabelBRL.BackColor = Color.White;
            tmpLabelBRR.BackColor = Color.White;
        }


        /// <summary>
        /// Set default colors to symbols on tmp field
        /// </summary>
        private void ClearTmpSymbolLabelForeColors()
        {
            tmpLabelULL.ForeColor = SystemColors.ControlText;
            tmpLabelULR.ForeColor = SystemColors.ControlText;
            tmpLabelUL.ForeColor = SystemColors.ControlText;
            tmpLabelUR.ForeColor = SystemColors.ControlText;
            tmpLabelURL.ForeColor = SystemColors.ControlText;
            tmpLabelURR.ForeColor = SystemColors.ControlText;
            tmpLabelLL.ForeColor = SystemColors.ControlText;
            tmpLabelLR.ForeColor = SystemColors.ControlText;
            tmpLabelRL.ForeColor = SystemColors.ControlText;
            tmpLabelRR.ForeColor = SystemColors.ControlText;
            tmpLabelBLL.ForeColor = SystemColors.ControlText;
            tmpLabelBLR.ForeColor = SystemColors.ControlText;
            tmpLabelBL.ForeColor = SystemColors.ControlText;
            tmpLabelBR.ForeColor = SystemColors.ControlText;
            tmpLabelBRL.ForeColor = SystemColors.ControlText;
            tmpLabelBRR.ForeColor = SystemColors.ControlText;
        }

        /// <summary>
        /// Set default colors to symbols
        /// </summary>
        private void ClearSymbolLabelBackColors()
        {
            labelULL.BackColor = Color.White;
            labelULR.BackColor = Color.White;
            labelUL.BackColor = Color.White;
            labelUR.BackColor = Color.White;
            labelURL.BackColor = Color.White;
            labelURR.BackColor = Color.White;
            labelLL.BackColor = Color.White;
            labelLR.BackColor = Color.White;
            labelRL.BackColor = Color.White;
            labelRR.BackColor = Color.White;
            labelBLL.BackColor = Color.White;
            labelBLR.BackColor = Color.White;
            labelBL.BackColor = Color.White;
            labelBR.BackColor = Color.White;
            labelBRL.BackColor = Color.White;
            labelBRR.BackColor = Color.White;
        }


        /// <summary>
        /// Set default colors to symbols
        /// </summary>
        private void ClearSymbolLabelForeColors()
        {
            labelULL.ForeColor = SystemColors.ControlText;
            labelULR.ForeColor = SystemColors.ControlText;
            labelUL.ForeColor = SystemColors.ControlText;
            labelUR.ForeColor = SystemColors.ControlText;
            labelURL.ForeColor = SystemColors.ControlText;
            labelURR.ForeColor = SystemColors.ControlText;
            labelLL.ForeColor = SystemColors.ControlText;
            labelLR.ForeColor = SystemColors.ControlText;
            labelRL.ForeColor = SystemColors.ControlText;
            labelRR.ForeColor = SystemColors.ControlText;
            labelBLL.ForeColor = SystemColors.ControlText;
            labelBLR.ForeColor = SystemColors.ControlText;
            labelBL.ForeColor = SystemColors.ControlText;
            labelBR.ForeColor = SystemColors.ControlText;
            labelBRL.ForeColor = SystemColors.ControlText;
            labelBRR.ForeColor = SystemColors.ControlText;
        }


        #endregion

        #region Combo boxes

        /// <summary>
        /// Tmp pair location combobox selected item changed
        /// </summary>
        private void tmpPairLocationComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ClearTmpSymbolLabelBackColors();

            currentTmpPairLocationRuleID = GetRuleIDByName(tmpPairLocationComboBox.Text, pairLocationRulesNames);

            switch (currentTmpPairLocationRuleID - TWO_SYM_PWD_PAIR_LOCATION_MIN)
            {
                case PAIR_LOCATION_UPPER_LEFT:
                    {
                        tmpLabelULL.BackColor = Color.Yellow;
                        tmpLabelULR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_UPPER:
                    {
                        tmpLabelUL.BackColor = Color.Yellow;
                        tmpLabelUR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_UPPER_RIGHT:
                    {
                        tmpLabelURL.BackColor = Color.Yellow;
                        tmpLabelURR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_LEFT:
                    {
                        tmpLabelLL.BackColor = Color.Yellow;
                        tmpLabelLR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_RIGHT:
                    {
                        tmpLabelRL.BackColor = Color.Yellow;
                        tmpLabelRR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_LOWER_LEFT:
                    {
                        tmpLabelBLL.BackColor = Color.Yellow;
                        tmpLabelBLR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_LOWER:
                    {
                        tmpLabelBL.BackColor = Color.Yellow;
                        tmpLabelBR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_LOWER_RIGHT:
                    {
                        tmpLabelBRL.BackColor = Color.Yellow;
                        tmpLabelBRR.BackColor = Color.Yellow;
                        break;
                    }

            }

            tmpSymbolLocationComboBox_SelectedIndexChanged(null, null);
        }

        /// <summary>
        /// Tmp symbol location combobox selected item changed
        /// </summary>
        private void tmpSymbolLocationComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ClearTmpSymbolLabelForeColors();

            currentTmpSymbolLocationRuleID = GetRuleIDByName(tmpSymbolLocationComboBox.Text, symbolLocationRulesNames);

            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        switch (currentTmpSymbolLocationRuleID - ONE_SYM_PWD_SYMBOL_LOCATION_MIN)
                        {
                            case SYMBOL_LOCATION_UPPER_LEFT:
                                {
                                    tmpLabelULL.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_UPPER:
                                {
                                    tmpLabelUL.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_UPPER_RIGHT:
                                {
                                    tmpLabelURR.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_LOWER_LEFT:
                                {
                                    tmpLabelBLL.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_LOWER:
                                {
                                    tmpLabelBL.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_LOWER_RIGHT:
                                {
                                    tmpLabelBRR.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_LEFT:
                                {
                                    tmpLabelLL.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_RIGHT:
                                {
                                    tmpLabelRR.ForeColor = Color.Red;
                                    break;
                                }
                        }
            
                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        switch (currentTmpSymbolLocationRuleID - TWO_SYM_PWD_SYMBOL_LOCATION_MIN)
                        {
                            case SYMBOL_LOCATION_LEFT:
                                {
                                    switch (currentTmpPairLocationRuleID - TWO_SYM_PWD_PAIR_LOCATION_MIN)
                                    {
                                        case PAIR_LOCATION_UPPER_LEFT:
                                            {
                                                tmpLabelULL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_UPPER:
                                            {
                                                tmpLabelUL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_UPPER_RIGHT:
                                            {
                                                tmpLabelURL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LEFT:
                                            {
                                                tmpLabelLL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_RIGHT:
                                            {
                                                tmpLabelRL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LOWER_LEFT:
                                            {
                                                tmpLabelBLL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LOWER:
                                            {
                                                tmpLabelBL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LOWER_RIGHT:
                                            {
                                                tmpLabelBRL.ForeColor = Color.Red;
                                                break;
                                            }
                                    }

                                    break;
                                }

                            case SYMBOL_LOCATION_RIGHT:
                                {
                                    switch (currentTmpPairLocationRuleID - TWO_SYM_PWD_PAIR_LOCATION_MIN)
                                    {
                                        case PAIR_LOCATION_UPPER_LEFT:
                                            {
                                                tmpLabelULR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_UPPER:
                                            {
                                                tmpLabelUR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_UPPER_RIGHT:
                                            {
                                                tmpLabelURR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LEFT:
                                            {
                                                tmpLabelLR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_RIGHT:
                                            {
                                                tmpLabelRR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LOWER_LEFT:
                                            {
                                                tmpLabelBLR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LOWER:
                                            {
                                                tmpLabelBR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LOWER_RIGHT:
                                            {
                                                tmpLabelBRR.ForeColor = Color.Red;
                                                break;
                                            }
                                    }

                                    break;
                                }
                        }

                        break;
                    }
            }
        }


        /// <summary>
        /// Pair location combobox selected item changed
        /// </summary>
        private void pairLocationComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ClearSymbolLabelBackColors();

            currentPairLocationRuleID = GetRuleIDByName(pairLocationComboBox.Text, pairLocationRulesNames);

            switch (currentPairLocationRuleID - TWO_SYM_PWD_PAIR_LOCATION_MIN)
            {
                case PAIR_LOCATION_UPPER_LEFT:
                    {
                        labelULL.BackColor = Color.Yellow;
                        labelULR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_UPPER:
                    {
                        labelUL.BackColor = Color.Yellow;
                        labelUR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_UPPER_RIGHT:
                    {
                        labelURL.BackColor = Color.Yellow;
                        labelURR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_LEFT:
                    {
                        labelLL.BackColor = Color.Yellow;
                        labelLR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_RIGHT:
                    {
                        labelRL.BackColor = Color.Yellow;
                        labelRR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_LOWER_LEFT:
                    {
                        labelBLL.BackColor = Color.Yellow;
                        labelBLR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_LOWER:
                    {
                        labelBL.BackColor = Color.Yellow;
                        labelBR.BackColor = Color.Yellow;
                        break;
                    }
                case PAIR_LOCATION_LOWER_RIGHT:
                    {
                        labelBRL.BackColor = Color.Yellow;
                        labelBRR.BackColor = Color.Yellow;
                        break;
                    }

            }

            symbolLocationComboBox_SelectedIndexChanged(null, null);
        }


        /// <summary>
        /// Symbol location combobox selected item changed
        /// </summary>
        private void symbolLocationComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ClearSymbolLabelForeColors();

            currentSymbolLocationRuleID = GetRuleIDByName(symbolLocationComboBox.Text, symbolLocationRulesNames);

            switch (_passwordType)
            {
                case fmConnect.ONE_SYMBOL_BOX_PWD:
                    {
                        switch (currentSymbolLocationRuleID - ONE_SYM_PWD_SYMBOL_LOCATION_MIN)
                        {
                            case SYMBOL_LOCATION_UPPER_LEFT:
                                {
                                    labelULL.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_UPPER:
                                {
                                    labelUL.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_UPPER_RIGHT:
                                {
                                    labelURR.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_LOWER_LEFT:
                                {
                                    labelBLL.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_LOWER:
                                {
                                    labelBL.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_LOWER_RIGHT:
                                {
                                    labelBRR.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_LEFT:
                                {
                                    labelLL.ForeColor = Color.Red;
                                    break;
                                }

                            case SYMBOL_LOCATION_RIGHT:
                                {
                                    labelRR.ForeColor = Color.Red;
                                    break;
                                }
                        }

                        break;
                    }

                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        switch (currentSymbolLocationRuleID - TWO_SYM_PWD_SYMBOL_LOCATION_MIN)
                        {
                            case SYMBOL_LOCATION_LEFT:
                                {
                                    switch (currentPairLocationRuleID - TWO_SYM_PWD_PAIR_LOCATION_MIN)
                                    {
                                        case PAIR_LOCATION_UPPER_LEFT:
                                            {
                                                labelULL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_UPPER:
                                            {
                                                labelUL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_UPPER_RIGHT:
                                            {
                                                labelURL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LEFT:
                                            {
                                                labelLL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_RIGHT:
                                            {
                                                labelRL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LOWER_LEFT:
                                            {
                                                labelBLL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LOWER:
                                            {
                                                labelBL.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LOWER_RIGHT:
                                            {
                                                labelBRL.ForeColor = Color.Red;
                                                break;
                                            }
                                    }

                                    break;
                                }

                            case SYMBOL_LOCATION_RIGHT:
                                {
                                    switch (currentPairLocationRuleID - TWO_SYM_PWD_PAIR_LOCATION_MIN)
                                    {
                                        case PAIR_LOCATION_UPPER_LEFT:
                                            {
                                                labelULR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_UPPER:
                                            {
                                                labelUR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_UPPER_RIGHT:
                                            {
                                                labelURR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LEFT:
                                            {
                                                labelLR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_RIGHT:
                                            {
                                                labelRR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LOWER_LEFT:
                                            {
                                                labelBLR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LOWER:
                                            {
                                                labelBR.ForeColor = Color.Red;
                                                break;
                                            }
                                        case PAIR_LOCATION_LOWER_RIGHT:
                                            {
                                                labelBRR.ForeColor = Color.Red;
                                                break;
                                            }
                                    }

                                    break;
                                }
                        }

                        break;
                    }
            }
        }

        /// <summary>
        /// Tmp joker 1 combo selected item changed
        /// </summary>
        private void tmpJoker1ComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            currentTmpJoker1RuleID = GetRuleIDByName(tmpJoker1ComboBox.Text, joker1RulesNames);
        }

        /// <summary>
        /// Tmp joker 2 combo selected item changed
        /// </summary>
        private void tmpJoker2ComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            currentTmpJoker2RuleID = GetRuleIDByName(tmpJoker2ComboBox.Text, joker2RulesNames);
        }

        /// <summary>
        /// Tmp formula combo selected item changed
        /// </summary>
        private void tmpFormulaComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            currentTmpFormulaRuleID = GetRuleIDByName(tmpFormulaComboBox.Text, formulaRulesNames);
        }

        /// <summary>
        /// Joker 1 combo selected item changed
        /// </summary>
        private void joker1ComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            currentJoker1RuleID = GetRuleIDByName(joker1ComboBox.Text, joker1RulesNames);
        }

        /// <summary>
        /// Joker 2 combo selected item changed
        /// </summary>
        private void joker2ComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            currentJoker2RuleID = GetRuleIDByName(joker2ComboBox.Text, joker2RulesNames);
        }

        /// <summary>
        /// Formula combo selected item changed
        /// </summary>
        private void formulaComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            currentFormulaRuleID = GetRuleIDByName(formulaComboBox.Text, formulaRulesNames);
        }

        #endregion

    }
}
