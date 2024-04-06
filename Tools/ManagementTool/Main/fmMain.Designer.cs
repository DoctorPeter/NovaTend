namespace ManagementTool
{
    partial class fmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.Label userPwdAttemptsCountLabel;
            System.Windows.Forms.Label userMaxPwdAttemptsCountLabel;
            System.Windows.Forms.Label usrEducationLabel;
            System.Windows.Forms.Label lessonOrderLabel;
            System.Windows.Forms.Label userNameLabel;
            System.Windows.Forms.Label personalFullNameLabel;
            System.Windows.Forms.Label personalUserNameLabel;
            System.Windows.Forms.Label personalUserEmailLabel;
            System.Windows.Forms.Label personalUserPhoneLabel;
            System.Windows.Forms.Label userPhoneLabel;
            System.Windows.Forms.Label userEmailLabel;
            System.Windows.Forms.Label userPwdResetPeriodLabel;
            System.Windows.Forms.Label checkParamTitleLabel;
            System.Windows.Forms.Label usrAccListTitleLabel;
            System.Windows.Forms.Label userGroupsTitleLabel;
            System.Windows.Forms.Label rightAnswerIDLabel;
            System.Windows.Forms.Label questionOrderLabel;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fmMain));
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("Services management");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("IPC settings");
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("Database settings");
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("Messaging settings");
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("LOG-files settings");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("Post Login process settings");
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("Programs control");
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("Commands history");
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("File transfer settings");
            System.Windows.Forms.TreeNode treeNode10 = new System.Windows.Forms.TreeNode("Update settings");
            System.Windows.Forms.TreeNode treeNode11 = new System.Windows.Forms.TreeNode("Services configuration", new System.Windows.Forms.TreeNode[] {
            treeNode2,
            treeNode3,
            treeNode4,
            treeNode5,
            treeNode6,
            treeNode7,
            treeNode8,
            treeNode9,
            treeNode10});
            System.Windows.Forms.TreeNode treeNode12 = new System.Windows.Forms.TreeNode("User accounts synchronization");
            this.mainMenu = new System.Windows.Forms.MenuStrip();
            this.connectionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.connectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.disconnectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.mainPanel = new System.Windows.Forms.Panel();
            this.mainTabControl = new System.Windows.Forms.TabControl();
            this.usersTabPage = new System.Windows.Forms.TabPage();
            this.userManagementTabControl = new System.Windows.Forms.TabControl();
            this.userPage = new System.Windows.Forms.TabPage();
            this.userDetailsTabControl = new System.Windows.Forms.TabControl();
            this.mainUsrInfoPage = new System.Windows.Forms.TabPage();
            this.novaUserAccessLabel = new System.Windows.Forms.Label();
            this.generalUserTitleLabel = new System.Windows.Forms.Label();
            this.userLockedCheckBox = new System.Windows.Forms.CheckBox();
            this.userPhoneTextBox = new System.Windows.Forms.TextBox();
            this.userEmailTextBox = new System.Windows.Forms.TextBox();
            this.lastLogOnDateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.dateOfLastLogOnLabel = new System.Windows.Forms.Label();
            this.userNameTextBox = new System.Windows.Forms.TextBox();
            this.usrGroupsInfoPage = new System.Windows.Forms.TabPage();
            this.userGroupsDataGridView = new System.Windows.Forms.DataGridView();
            this.userGroupNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.userGroupIDColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.usrPermissionsPage = new System.Windows.Forms.TabPage();
            this.permissionTitleLabel = new System.Windows.Forms.Label();
            this.userPermissionsDataGridView = new System.Windows.Forms.DataGridView();
            this.userPermissionNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.userPermissionIDColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.userPwdPage = new System.Windows.Forms.TabPage();
            this.resetPwdButton = new System.Windows.Forms.Button();
            this.hoursLabel = new System.Windows.Forms.Label();
            this.pwdResetTitleLabel = new System.Windows.Forms.Label();
            this.userPwdResetPeriodTextBox = new System.Windows.Forms.TextBox();
            this.changePwdSettingsButton = new System.Windows.Forms.Button();
            this.userPwdResetDateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.pwdUserSettingsTitleLabel = new System.Windows.Forms.Label();
            this.userPwdResetDateLabel = new System.Windows.Forms.Label();
            this.userPwdResetedCheckBox = new System.Windows.Forms.CheckBox();
            this.userPwdAttemptsCountTextBox = new System.Windows.Forms.TextBox();
            this.userSMSPwdResetCheckBox = new System.Windows.Forms.CheckBox();
            this.userEmailPwdResetCheckBox = new System.Windows.Forms.CheckBox();
            this.userPwdTypeLabel = new System.Windows.Forms.Label();
            this.userMaxPwdAttemptsCountTextBox = new System.Windows.Forms.TextBox();
            this.userPwdTypeComboBox = new System.Windows.Forms.ComboBox();
            this.usrEduPage = new System.Windows.Forms.TabPage();
            this.userNeedStudyCheckBox = new System.Windows.Forms.CheckBox();
            this.userRandomEduCategCheckBox = new System.Windows.Forms.CheckBox();
            this.usrAccountsPage = new System.Windows.Forms.TabPage();
            this.userAccountsDataGridView = new System.Windows.Forms.DataGridView();
            this.authSystemTypeNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.accountUserNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.accountPasswordColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.passThruColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.lastSignInDateColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.usrAccListTitlePanel = new System.Windows.Forms.Panel();
            this.userAccountGroupsButton = new System.Windows.Forms.Button();
            this.userAccountsArchiveButton = new System.Windows.Forms.Button();
            this.changeUserAccountButton = new System.Windows.Forms.Button();
            this.usrCheckParamsPage = new System.Windows.Forms.TabPage();
            this.userCheckValuesDataGridView = new System.Windows.Forms.DataGridView();
            this.userCheckValueObjectIDColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.userCheckValueColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.checkParamTitlePanel = new System.Windows.Forms.Panel();
            this.usersInfoImageList = new System.Windows.Forms.ImageList(this.components);
            this.userNamesDataGridView = new System.Windows.Forms.DataGridView();
            this.userNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.usersBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.bindingNavigatorAddNewItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorCountItem = new System.Windows.Forms.ToolStripLabel();
            this.bindingNavigatorDeleteItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorMoveFirstItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorMovePreviousItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.bindingNavigatorPositionItem = new System.Windows.Forms.ToolStripTextBox();
            this.bindingNavigatorSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.bindingNavigatorMoveNextItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorMoveLastItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.usersBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.usersBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.userGroupsPage = new System.Windows.Forms.TabPage();
            this.groupDetailsPanel = new System.Windows.Forms.Panel();
            this.groupUsersGroupBox = new System.Windows.Forms.GroupBox();
            this.usersGroupDataGridView = new System.Windows.Forms.DataGridView();
            this.groupUserNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.groupUserIDColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.splitter30 = new System.Windows.Forms.Splitter();
            this.groupAuthSystemsGroupBox = new System.Windows.Forms.GroupBox();
            this.groupGroupAuthSystemsDataGridView = new System.Windows.Forms.DataGridView();
            this.groupAuthSystemColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.authGroupNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupReferencesPanel = new System.Windows.Forms.Panel();
            this.groupUsersButton = new System.Windows.Forms.Button();
            this.userGroupSettingsButton = new System.Windows.Forms.Button();
            this.splitter27 = new System.Windows.Forms.Splitter();
            this.groupPermissionsGroupBox = new System.Windows.Forms.GroupBox();
            this.groupPermissionsDataGridView = new System.Windows.Forms.DataGridView();
            this.groupPermissionsColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.groupPermissionIDColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.splitter26 = new System.Windows.Forms.Splitter();
            this.groupListGroupBox = new System.Windows.Forms.GroupBox();
            this.groupsDataGridView = new System.Windows.Forms.DataGridView();
            this.groupNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupDescriptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupsBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton65 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel13 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton67 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton68 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton69 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator38 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox13 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator39 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton70 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton71 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator43 = new System.Windows.Forms.ToolStripSeparator();
            this.groupsBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.groupsBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.computersPage = new System.Windows.Forms.TabPage();
            this.computersDataGridView = new System.Windows.Forms.DataGridView();
            this.computerNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.computerDescriptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.computersBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.bindingNavigatorAddNewItem1 = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorCountItem1 = new System.Windows.Forms.ToolStripLabel();
            this.bindingNavigatorDeleteItem1 = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorMoveFirstItem1 = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorMovePreviousItem1 = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.bindingNavigatorPositionItem1 = new System.Windows.Forms.ToolStripTextBox();
            this.bindingNavigatorSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.bindingNavigatorMoveNextItem1 = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorMoveLastItem1 = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.computersBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.computersBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.authSystemsPage = new System.Windows.Forms.TabPage();
            this.authSystemsDataGridView = new System.Windows.Forms.DataGridView();
            this.authSystemTypeColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.authSystemNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.onDeleteActionColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.onInsertActionColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.onUpdateActionColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.moveGroupUsersColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.authSystemsBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton66 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel14 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton73 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton74 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton75 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator40 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox14 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator41 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton76 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton77 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator42 = new System.Windows.Forms.ToolStripSeparator();
            this.authSystemsBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.authSystemsBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator56 = new System.Windows.Forms.ToolStripSeparator();
            this.authSystemsBindingNavigatorConfigureItem = new System.Windows.Forms.ToolStripButton();
            this.usersTabImageList = new System.Windows.Forms.ImageList(this.components);
            this.presetTabPage = new System.Windows.Forms.TabPage();
            this.presetSplitContainer = new System.Windows.Forms.SplitContainer();
            this.presetDetailsMainPanel = new System.Windows.Forms.Panel();
            this.presetDetailsSubPanel = new System.Windows.Forms.Panel();
            this.presetScreenObjectsGroupBox = new System.Windows.Forms.GroupBox();
            this.presetScreenObjectsDataGridView = new System.Windows.Forms.DataGridView();
            this.presetScreenObjectNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.presetScreenObjectOrderColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.presetScreenObjectScopeColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.splitter3 = new System.Windows.Forms.Splitter();
            this.presetScreensGroupBox = new System.Windows.Forms.GroupBox();
            this.presetScreensDataGridView = new System.Windows.Forms.DataGridView();
            this.presetScreenNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.presetScreenScopeColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.splitter2 = new System.Windows.Forms.Splitter();
            this.presetNamesGroupBox = new System.Windows.Forms.GroupBox();
            this.presetNamesDataGridView = new System.Windows.Forms.DataGridView();
            this.presetNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.presetDateColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.presetDescriptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.presetBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton7 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel2 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton8 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton9 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton10 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox2 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton11 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton12 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.presetBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.presetBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator37 = new System.Windows.Forms.ToolStripSeparator();
            this.presetBindingNavigatorHookupIten = new System.Windows.Forms.ToolStripButton();
            this.screenObjectsPanel = new System.Windows.Forms.Panel();
            this.screenObjectsGroupBox = new System.Windows.Forms.GroupBox();
            this.screenObjectsDataGridView = new System.Windows.Forms.DataGridView();
            this.screenObjectNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectCaptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectTypeIDColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.screenObjectStrValueColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectLocationXColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectLocationYColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectLocationXPersColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectLocationYPersColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectWidthColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectHeightColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectWidthPersColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectHeightPersColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectColorColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectFontSizeColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectTextColorColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.screenObjectValuesTabControl = new System.Windows.Forms.TabControl();
            this.tabScreenObjectText = new System.Windows.Forms.TabPage();
            this.screenObjectTextPanel = new System.Windows.Forms.Panel();
            this.screenObjectTextClearButton = new System.Windows.Forms.Button();
            this.screenObjectRichTextBox = new System.Windows.Forms.RichTextBox();
            this.loadScreenObjecTextButton = new System.Windows.Forms.Button();
            this.tabScreenObjectImage = new System.Windows.Forms.TabPage();
            this.screenObjectImagePanel = new System.Windows.Forms.Panel();
            this.scrennObjectImageClearButton = new System.Windows.Forms.Button();
            this.loadScreenObjectImageButton = new System.Windows.Forms.Button();
            this.screenObjectPictureBox = new System.Windows.Forms.PictureBox();
            this.tabScreenObjectListValues = new System.Windows.Forms.TabPage();
            this.screenObjectListValuesPanel = new System.Windows.Forms.Panel();
            this.screenObjectListValuesDataGridView = new System.Windows.Forms.DataGridView();
            this.screenObjectListValuesColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjValuesImageList = new System.Windows.Forms.ImageList(this.components);
            this.splitter4 = new System.Windows.Forms.Splitter();
            this.screensGroupBox = new System.Windows.Forms.GroupBox();
            this.screensDataGridView = new System.Windows.Forms.DataGridView();
            this.screenNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenCaptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenTypeIDColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.screenLocationXColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenLocationYColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenLocationXPersColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenLocationYPersColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenWidthColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenHeightColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenWidthPersColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenHeightPersColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenColorColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenFontSizeColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenTextColorColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.screenObjectsBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton3 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton4 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox1 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton5 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton6 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.screenObjectsBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.screenObjectsBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.educationTabPage = new System.Windows.Forms.TabPage();
            this.educationMainPanel = new System.Windows.Forms.Panel();
            this.educationMainSplitContainer = new System.Windows.Forms.SplitContainer();
            this.eduEditorPanel = new System.Windows.Forms.Panel();
            this.eduLessonsTabControl = new System.Windows.Forms.TabControl();
            this.tabLessons = new System.Windows.Forms.TabPage();
            this.eduLessonSplitContainer = new System.Windows.Forms.SplitContainer();
            this.eduLessonImagePanel = new System.Windows.Forms.Panel();
            this.eduLessonImageClearButton = new System.Windows.Forms.Button();
            this.eduLessonImageOpenButton = new System.Windows.Forms.Button();
            this.eduLessonPictureBox = new System.Windows.Forms.PictureBox();
            this.eduLessonTextPanel = new System.Windows.Forms.Panel();
            this.eduLessonTextClearButton = new System.Windows.Forms.Button();
            this.eduLessonRichTextBox = new System.Windows.Forms.RichTextBox();
            this.eduLessonTextOpenButton = new System.Windows.Forms.Button();
            this.splitter9 = new System.Windows.Forms.Splitter();
            this.lessonsOrderPanel = new System.Windows.Forms.Panel();
            this.eduLessonOrderTextBox = new System.Windows.Forms.TextBox();
            this.eduLessonsBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.eduLessonsBindingNavigatorAddNewItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel4 = new System.Windows.Forms.ToolStripLabel();
            this.eduLessonsBindingNavigatorRemoveItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton21 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton22 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator10 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox4 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator11 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton23 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton24 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator12 = new System.Windows.Forms.ToolStripSeparator();
            this.eduLessonsBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.eduLessonsBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.tabQuestions = new System.Windows.Forms.TabPage();
            this.eduQuestionSplitContainer = new System.Windows.Forms.SplitContainer();
            this.eduQuestionTextPanel = new System.Windows.Forms.Panel();
            this.eduQuestionTextClearButton = new System.Windows.Forms.Button();
            this.eduQuestionRichTextBox = new System.Windows.Forms.RichTextBox();
            this.eduQuestionTextOpenButton = new System.Windows.Forms.Button();
            this.questionOrderPanel = new System.Windows.Forms.Panel();
            this.rightAnswerComboBox = new System.Windows.Forms.ComboBox();
            this.eduQuestionOrderTextBox = new System.Windows.Forms.TextBox();
            this.eduQuestionsBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.eduQuestionsBindingNavigatorAddNewItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel5 = new System.Windows.Forms.ToolStripLabel();
            this.eduQuestionsBindingNavigatorRemoveItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton27 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton28 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator13 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox5 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator14 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton29 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton30 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator15 = new System.Windows.Forms.ToolStripSeparator();
            this.eduQuestionsBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.eduQuestionsBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.eduAnswersDataGridView = new System.Windows.Forms.DataGridView();
            this.eduQuestionAnswerTextColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.eduQuestionAnswerOrderColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.eduAnswersBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.eduAnswersBindingNavigatorAddItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel23 = new System.Windows.Forms.ToolStripLabel();
            this.eduAnswersBindingNavigatorRemoveItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton123 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton124 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator71 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox23 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator72 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton125 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton126 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator73 = new System.Windows.Forms.ToolStripSeparator();
            this.eduAnswersBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.eduAnswersBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.tabAnswers = new System.Windows.Forms.TabPage();
            this.generalAnswersListDataGridView = new System.Windows.Forms.DataGridView();
            this.eduGeneralAnswerTextColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.eduAllAnswersBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.eduAllAnswersBindingNavigatorAddItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel24 = new System.Windows.Forms.ToolStripLabel();
            this.eduAllAnswersBindingNavigatorRemoveItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton131 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton132 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator74 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox24 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator75 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton133 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton134 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator76 = new System.Windows.Forms.ToolStripSeparator();
            this.eduAllAnswersBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.eduAllAnswersBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.splitter8 = new System.Windows.Forms.Splitter();
            this.eduCategoriesGroupBox = new System.Windows.Forms.GroupBox();
            this.eduCategoriesDataGridView = new System.Windows.Forms.DataGridView();
            this.eduCategoriesNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.eduCategoriesBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton13 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel3 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton14 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton15 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton16 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator7 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox3 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator8 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton17 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton18 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator9 = new System.Windows.Forms.ToolStripSeparator();
            this.eduCategoriesBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.eduCategoriesBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.eduButtonsBottomPanel = new System.Windows.Forms.Panel();
            this.eduImportFromDBButton = new System.Windows.Forms.Button();
            this.eduTabControl = new System.Windows.Forms.TabControl();
            this.usrEduTabPage = new System.Windows.Forms.TabPage();
            this.userEducationSplitContainer = new System.Windows.Forms.SplitContainer();
            this.eduUserCategoriesGroupBox = new System.Windows.Forms.GroupBox();
            this.eduUserCategoriesDataGridView = new System.Windows.Forms.DataGridView();
            this.eduUserCategoryNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.eduRandomCategoryQuestionsColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.eduUserCategOrderColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.eduUserCategoriesBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton37 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel7 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton38 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton39 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton40 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator19 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox7 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator20 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton41 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton42 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator21 = new System.Windows.Forms.ToolStripSeparator();
            this.eduUserCategoriesBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.eduUserCategoriesBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.eduUserHistoryGroupBox = new System.Windows.Forms.GroupBox();
            this.eduUserHistoryDataGridView = new System.Windows.Forms.DataGridView();
            this.eduUserQuestionTextColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.eduUserAnswerTextColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.eduUserCorrectAnswerColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.eduUserAnswerDateColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.eduUserHistoryBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton43 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel8 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton44 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton45 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton46 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator22 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox8 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator23 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton47 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton48 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator24 = new System.Windows.Forms.ToolStripSeparator();
            this.eduUserHistoryBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.eduUserHistoryBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.splitter12 = new System.Windows.Forms.Splitter();
            this.eduUsersGroupBox = new System.Windows.Forms.GroupBox();
            this.eduUsersDataGridView = new System.Windows.Forms.DataGridView();
            this.eduUserNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.eduUsersBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripLabel6 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton33 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton34 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator16 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox6 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator17 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton35 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton36 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator18 = new System.Windows.Forms.ToolStripSeparator();
            this.eduUsersBindingNavigatorRefreshIntem = new System.Windows.Forms.ToolStripButton();
            this.usrGroupEduTabPage = new System.Windows.Forms.TabPage();
            this.eduUserGroupCategoriesGroupBox = new System.Windows.Forms.GroupBox();
            this.eduUserGroupCategoriesDataGridView = new System.Windows.Forms.DataGridView();
            this.eduUserGroupCategoryNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.eduUserGroupRandomCategoryQuestionsColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.eduUserGroupCategOrderColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.eduUserGroupCategoriesBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton81 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel18 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton82 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton83 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton90 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator54 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox18 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator55 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton97 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton98 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator57 = new System.Windows.Forms.ToolStripSeparator();
            this.eduUserGroupCategoriesBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.eduUserGroupCategoriesBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.splitter31 = new System.Windows.Forms.Splitter();
            this.eduUserGroupsGroupBox = new System.Windows.Forms.GroupBox();
            this.eduUserGroupsDataGridView = new System.Windows.Forms.DataGridView();
            this.eduGroupNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.eduGroupDescriptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.eduUserGroupsBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripLabel15 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton72 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton78 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator45 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox15 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator46 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton79 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton80 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator53 = new System.Windows.Forms.ToolStripSeparator();
            this.eduUserGroupsBindingNavigatorRefreshIntem = new System.Windows.Forms.ToolStripButton();
            this.eduImageList = new System.Windows.Forms.ImageList(this.components);
            this.notificationTabPage = new System.Windows.Forms.TabPage();
            this.notificationSplitContainer = new System.Windows.Forms.SplitContainer();
            this.splitter15 = new System.Windows.Forms.Splitter();
            this.noticesImageTextPanel = new System.Windows.Forms.Panel();
            this.noticeValuesSplitContainer = new System.Windows.Forms.SplitContainer();
            this.notificationPicturePanel = new System.Windows.Forms.Panel();
            this.noticesImageClearBtn = new System.Windows.Forms.Button();
            this.noticesImageOpenBtn = new System.Windows.Forms.Button();
            this.notificationPictureBox = new System.Windows.Forms.PictureBox();
            this.notificationTextPanel = new System.Windows.Forms.Panel();
            this.noticesTextClearBtn = new System.Windows.Forms.Button();
            this.notificationRichTextBox = new System.Windows.Forms.RichTextBox();
            this.noticesTextOpenBtn = new System.Windows.Forms.Button();
            this.noticesTopPanel = new System.Windows.Forms.Panel();
            this.noticeScopeLabel = new System.Windows.Forms.Label();
            this.noticeDisplayTypeLabel = new System.Windows.Forms.Label();
            this.noticeTypeLabel = new System.Windows.Forms.Label();
            this.noticeScopesComboBox = new System.Windows.Forms.ComboBox();
            this.noticeDisplayTypeComboBox = new System.Windows.Forms.ComboBox();
            this.noticeTypeComboBox = new System.Windows.Forms.ComboBox();
            this.notificationBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton19 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel9 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton20 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton25 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton26 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator25 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox9 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator26 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton31 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton32 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator27 = new System.Windows.Forms.ToolStripSeparator();
            this.notificationBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.notificationBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.notificationsTabControl = new System.Windows.Forms.TabControl();
            this.userNotificationsTabPage = new System.Windows.Forms.TabPage();
            this.userNotificationSplitContainer = new System.Windows.Forms.SplitContainer();
            this.userNotificationGroupBox = new System.Windows.Forms.GroupBox();
            this.userNotificationDataGridView = new System.Windows.Forms.DataGridView();
            this.userNotificationNoticeTextColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.userNotificationDisplayTypeColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.userNotificationBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton54 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel11 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton55 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton56 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton57 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator31 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox11 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator32 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton58 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton59 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator33 = new System.Windows.Forms.ToolStripSeparator();
            this.userNotificationBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.userNotificationBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.userNotificationHistoryGroupBox = new System.Windows.Forms.GroupBox();
            this.userNotificationHistoryDataGridView = new System.Windows.Forms.DataGridView();
            this.userNotificationHistoryNoticeTextColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.userNotificationHistoryDateColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.userNotificationHistoryBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton49 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel12 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton60 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton61 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton62 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator34 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox12 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator35 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton63 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton64 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator36 = new System.Windows.Forms.ToolStripSeparator();
            this.userNotificationHistoryBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.userNotificationHistoryBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.splitter17 = new System.Windows.Forms.Splitter();
            this.notificationUsersGroupBox = new System.Windows.Forms.GroupBox();
            this.notificationUsersDataGridView = new System.Windows.Forms.DataGridView();
            this.notificationUsersUserNameTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.notificationUsersBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripLabel10 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton50 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton51 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator28 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox10 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator29 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton52 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton53 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator30 = new System.Windows.Forms.ToolStripSeparator();
            this.notificationUsersBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.userGroupNotificationsTabPage = new System.Windows.Forms.TabPage();
            this.userGroupNotificationGroupBox = new System.Windows.Forms.GroupBox();
            this.userGroupNotificationDataGridView = new System.Windows.Forms.DataGridView();
            this.userGroupNotificationNoticeTextColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.userGroupNotificationDisplayTypeColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.userGroupsNotificationBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton104 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel20 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton105 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton106 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton107 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator61 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox20 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator62 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton108 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton109 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator63 = new System.Windows.Forms.ToolStripSeparator();
            this.userGroupNotificationBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.userGroupNotificationBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.splitter32 = new System.Windows.Forms.Splitter();
            this.notificationUserGroupsGroupBox = new System.Windows.Forms.GroupBox();
            this.notificationUserGroupsDataGridView = new System.Windows.Forms.DataGridView();
            this.notificationGroupNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.notificationGroupDescriptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.notificationUserGroupsBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripLabel19 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton99 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton100 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator58 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox19 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator59 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton101 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton102 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator60 = new System.Windows.Forms.ToolStripSeparator();
            this.notificationUserGroupsBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.licenseTabPage = new System.Windows.Forms.TabPage();
            this.licManagmentMainPanel = new System.Windows.Forms.Panel();
            this.licensePointsPanel = new System.Windows.Forms.Panel();
            this.licenseBottomPanel = new System.Windows.Forms.Panel();
            this.btnClearLicenseInfo = new System.Windows.Forms.Button();
            this.btnAddLicInfoRecord = new System.Windows.Forms.Button();
            this.btnSaveLicenseInfo = new System.Windows.Forms.Button();
            this.btnRefreshLicenseInfo = new System.Windows.Forms.Button();
            this.logFilesTabPage = new System.Windows.Forms.TabPage();
            this.logFileMainPanel = new System.Windows.Forms.Panel();
            this.logFileRichTextBox = new System.Windows.Forms.RichTextBox();
            this.logFilesPanel = new System.Windows.Forms.Panel();
            this.logFilePathLabel = new System.Windows.Forms.Label();
            this.logFileClearButton = new System.Windows.Forms.Button();
            this.logFileOpenButton = new System.Windows.Forms.Button();
            this.confTabPage = new System.Windows.Forms.TabPage();
            this.confTabControl = new System.Windows.Forms.TabControl();
            this.tabServiceControl = new System.Windows.Forms.TabPage();
            this.splitter29 = new System.Windows.Forms.Splitter();
            this.servicesGroupBox = new System.Windows.Forms.GroupBox();
            this.servicesListView = new System.Windows.Forms.ListView();
            this.nameColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.statusColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.confImageList = new System.Windows.Forms.ImageList(this.components);
            this.servicesButtonsPanel = new System.Windows.Forms.Panel();
            this.btnRefreshServicesList = new System.Windows.Forms.Button();
            this.btnRestart = new System.Windows.Forms.Button();
            this.btnPause = new System.Windows.Forms.Button();
            this.btnStop = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.serviceDescriptionGroupBox = new System.Windows.Forms.GroupBox();
            this.serviceDescriptionTextBox = new System.Windows.Forms.TextBox();
            this.tabIPCSettings = new System.Windows.Forms.TabPage();
            this.globalServerPriorityLabel = new System.Windows.Forms.Label();
            this.globalServerPriorityNud = new System.Windows.Forms.NumericUpDown();
            this.globalServerAddressTextBox = new System.Windows.Forms.TextBox();
            this.globalServerAddressLabel = new System.Windows.Forms.Label();
            this.globalServerPortTextBox = new System.Windows.Forms.TextBox();
            this.globalServerPortLabel = new System.Windows.Forms.Label();
            this.globalServerNameTextBox = new System.Windows.Forms.TextBox();
            this.globalServerNameLabel = new System.Windows.Forms.Label();
            this.globalServerTypeComboBox = new System.Windows.Forms.ComboBox();
            this.globalServerTypeLabel = new System.Windows.Forms.Label();
            this.globalServerIDTextBox = new System.Windows.Forms.TextBox();
            this.globalServerIDLabel = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnDelServer = new System.Windows.Forms.Button();
            this.btnAddServer = new System.Windows.Forms.Button();
            this.btnLastServer = new System.Windows.Forms.Button();
            this.btnNextServer = new System.Windows.Forms.Button();
            this.btnPrevServer = new System.Windows.Forms.Button();
            this.btnFirstServer = new System.Windows.Forms.Button();
            this.serverPriorityLabel = new System.Windows.Forms.Label();
            this.serverPriorityNud = new System.Windows.Forms.NumericUpDown();
            this.serverAddressTextBox = new System.Windows.Forms.TextBox();
            this.serverAddressLabel = new System.Windows.Forms.Label();
            this.serverPortTextBox = new System.Windows.Forms.TextBox();
            this.serverPortLabel = new System.Windows.Forms.Label();
            this.serverNameTextBox = new System.Windows.Forms.TextBox();
            this.serverNameLabel = new System.Windows.Forms.Label();
            this.serverTypeComboBox = new System.Windows.Forms.ComboBox();
            this.serverTypeLabel = new System.Windows.Forms.Label();
            this.serverIDTextBox = new System.Windows.Forms.TextBox();
            this.serverIDLabel = new System.Windows.Forms.Label();
            this.alternativeServersLabel = new System.Windows.Forms.Label();
            this.desktopStartingCheckBox = new System.Windows.Forms.CheckBox();
            this.hubStartingCheckBox = new System.Windows.Forms.CheckBox();
            this.hostStartingCheckBox = new System.Windows.Forms.CheckBox();
            this.desktopServerPriorityLabel = new System.Windows.Forms.Label();
            this.desktopServerPriorityNud = new System.Windows.Forms.NumericUpDown();
            this.desktopServerAddressTextBox = new System.Windows.Forms.TextBox();
            this.desktopServerAddressLabel = new System.Windows.Forms.Label();
            this.desktopServerPortTextBox = new System.Windows.Forms.TextBox();
            this.desktopServerPortLabel = new System.Windows.Forms.Label();
            this.desktopServerNameTextBox = new System.Windows.Forms.TextBox();
            this.desktopServerNameLabel = new System.Windows.Forms.Label();
            this.desktopServerTypeComboBox = new System.Windows.Forms.ComboBox();
            this.desktopServerTypeLabel = new System.Windows.Forms.Label();
            this.desktopServerIDTextBox = new System.Windows.Forms.TextBox();
            this.desktopServerIDLabel = new System.Windows.Forms.Label();
            this.desktopServerLabel = new System.Windows.Forms.Label();
            this.hubServerPriorityLabel = new System.Windows.Forms.Label();
            this.hubServerPriorityNud = new System.Windows.Forms.NumericUpDown();
            this.hubServerAddressTextBox = new System.Windows.Forms.TextBox();
            this.hubServerAddressLabel = new System.Windows.Forms.Label();
            this.hubServerPortTextBox = new System.Windows.Forms.TextBox();
            this.hubServerPortLabel = new System.Windows.Forms.Label();
            this.hubServerNameTextBox = new System.Windows.Forms.TextBox();
            this.hubServerNameLabel = new System.Windows.Forms.Label();
            this.hubServerTypeComboBox = new System.Windows.Forms.ComboBox();
            this.hubServerTypeLabel = new System.Windows.Forms.Label();
            this.hubServerIDTextBox = new System.Windows.Forms.TextBox();
            this.hubServerIDLabel = new System.Windows.Forms.Label();
            this.hubServerLabel = new System.Windows.Forms.Label();
            this.ipcSplitPanel1 = new System.Windows.Forms.Panel();
            this.hostServerPriorityLabel = new System.Windows.Forms.Label();
            this.hostServerPriorityNud = new System.Windows.Forms.NumericUpDown();
            this.hostServerAddressTextBox = new System.Windows.Forms.TextBox();
            this.hostServerAddressLabel = new System.Windows.Forms.Label();
            this.hostServerPortTextBox = new System.Windows.Forms.TextBox();
            this.hostServerPortLabel = new System.Windows.Forms.Label();
            this.hostServerNameTextBox = new System.Windows.Forms.TextBox();
            this.hostServerNameLabel = new System.Windows.Forms.Label();
            this.hostServerTypeComboBox = new System.Windows.Forms.ComboBox();
            this.hostServerTypeLabel = new System.Windows.Forms.Label();
            this.hostServerIDTextBox = new System.Windows.Forms.TextBox();
            this.hostServerIDLabel = new System.Windows.Forms.Label();
            this.hostServerLabel = new System.Windows.Forms.Label();
            this.btnSaveIPCSettings = new System.Windows.Forms.Button();
            this.lblIPCTitle = new System.Windows.Forms.Label();
            this.tabDatabaseSettings = new System.Windows.Forms.TabPage();
            this.changeDBPwdLabel = new System.Windows.Forms.Label();
            this.onDelUserAccActionComboBox = new System.Windows.Forms.ComboBox();
            this.lblUserAccountsOnDeleteAction = new System.Windows.Forms.Label();
            this.lblUserAccountsManagement = new System.Windows.Forms.Label();
            this.dbPasswordTextBox = new System.Windows.Forms.TextBox();
            this.lblDBPassword = new System.Windows.Forms.Label();
            this.dbUserNameTextBox = new System.Windows.Forms.TextBox();
            this.lblDBUserName = new System.Windows.Forms.Label();
            this.btnDataBaseAccessSettingsSave = new System.Windows.Forms.Button();
            this.dbNameTextBox = new System.Windows.Forms.TextBox();
            this.lblDBName = new System.Windows.Forms.Label();
            this.dbServerTextBox = new System.Windows.Forms.TextBox();
            this.lblDBServer = new System.Windows.Forms.Label();
            this.lblDatabaseAccessSettings = new System.Windows.Forms.Label();
            this.tabMessagesSettings = new System.Windows.Forms.TabPage();
            this.changeGVoicePwdLabel = new System.Windows.Forms.Label();
            this.changeEmailPwdLabel = new System.Windows.Forms.Label();
            this.gvPasswordTextBox = new System.Windows.Forms.TextBox();
            this.lblGVPassword = new System.Windows.Forms.Label();
            this.gvLoginTextBox = new System.Windows.Forms.TextBox();
            this.lblGVLogin = new System.Windows.Forms.Label();
            this.lblGVSettings = new System.Windows.Forms.Label();
            this.emailRecipientTextBox = new System.Windows.Forms.TextBox();
            this.lblEmailRecipient = new System.Windows.Forms.Label();
            this.emailSenderTextBox = new System.Windows.Forms.TextBox();
            this.lblEmailSender = new System.Windows.Forms.Label();
            this.emailPasswordTextBox = new System.Windows.Forms.TextBox();
            this.lblEmailPassword = new System.Windows.Forms.Label();
            this.emailLoginTextBox = new System.Windows.Forms.TextBox();
            this.lblEmailLogin = new System.Windows.Forms.Label();
            this.emailAuthCheckBox = new System.Windows.Forms.CheckBox();
            this.emailSecTypeComboBox = new System.Windows.Forms.ComboBox();
            this.lblEmailSecType = new System.Windows.Forms.Label();
            this.btnMessagingSettingsSave = new System.Windows.Forms.Button();
            this.emailPortTextBox = new System.Windows.Forms.TextBox();
            this.lblEmailPort = new System.Windows.Forms.Label();
            this.emailHostTextBox = new System.Windows.Forms.TextBox();
            this.lblEMailHost = new System.Windows.Forms.Label();
            this.lblEMailSettings = new System.Windows.Forms.Label();
            this.tabLOGSettings = new System.Windows.Forms.TabPage();
            this.fixedSizeLabel = new System.Windows.Forms.Label();
            this.fixedSizeNumUpDown = new System.Windows.Forms.NumericUpDown();
            this.fixedSizeCheckBox = new System.Windows.Forms.CheckBox();
            this.logPathButton = new System.Windows.Forms.Button();
            this.logPathTextBox = new System.Windows.Forms.TextBox();
            this.logPathLabel = new System.Windows.Forms.Label();
            this.btnLogSettingsSave = new System.Windows.Forms.Button();
            this.logEmailCheckBox = new System.Windows.Forms.CheckBox();
            this.logEncryptionCheckBox = new System.Windows.Forms.CheckBox();
            this.lblLOGSettings = new System.Windows.Forms.Label();
            this.tabServicesConfiguration = new System.Windows.Forms.TabPage();
            this.updateSettingsLabel = new System.Windows.Forms.Label();
            this.updateSettingsPictureBox = new System.Windows.Forms.PictureBox();
            this.fileTransferLabel = new System.Windows.Forms.Label();
            this.fileTransferPictureBox = new System.Windows.Forms.PictureBox();
            this.commandsHistorySettingsLabel = new System.Windows.Forms.Label();
            this.commandsHistorySettingsPictureBox = new System.Windows.Forms.PictureBox();
            this.programsControlSettingsLabel = new System.Windows.Forms.Label();
            this.programsControlSettingsPictureBox = new System.Windows.Forms.PictureBox();
            this.postLoginSettingsLabel = new System.Windows.Forms.Label();
            this.postLoginSettingsPictureBox = new System.Windows.Forms.PictureBox();
            this.logSettingsLabel = new System.Windows.Forms.Label();
            this.logSettingsPictureBox = new System.Windows.Forms.PictureBox();
            this.msgSettingsLabel = new System.Windows.Forms.Label();
            this.msgSettingsPictureBox = new System.Windows.Forms.PictureBox();
            this.dbSettingsLabel = new System.Windows.Forms.Label();
            this.dbSettingsPictureBox = new System.Windows.Forms.PictureBox();
            this.ipcSettingsLabel = new System.Windows.Forms.Label();
            this.ipcSettingsPictureBox = new System.Windows.Forms.PictureBox();
            this.tabSynchronization = new System.Windows.Forms.TabPage();
            this.revLinkTabControl = new System.Windows.Forms.TabControl();
            this.revLinkUsersTabPage = new System.Windows.Forms.TabPage();
            this.btnRefreshRevUsersList = new System.Windows.Forms.Button();
            this.accountsListView = new System.Windows.Forms.ListView();
            this.userNameColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.usersImageList = new System.Windows.Forms.ImageList(this.components);
            this.btnReverseLink = new System.Windows.Forms.Button();
            this.revLinkGroupsTabPage = new System.Windows.Forms.TabPage();
            this.btnRefreshRevGroupsList = new System.Windows.Forms.Button();
            this.groupsListView = new System.Windows.Forms.ListView();
            this.groupNameColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.btnReverseGroupLink = new System.Windows.Forms.Button();
            this.syncLogonCheckBox = new System.Windows.Forms.CheckBox();
            this.lblLogonSyncSettings = new System.Windows.Forms.Label();
            this.revSyncAuthSystemsComboBox = new System.Windows.Forms.ComboBox();
            this.lblReverseSyncAuthSystem = new System.Windows.Forms.Label();
            this.lblReverseSyncSettings = new System.Windows.Forms.Label();
            this.btnForcedSync = new System.Windows.Forms.Button();
            this.lblSyncTime = new System.Windows.Forms.Label();
            this.btnSaveSyncSettings = new System.Windows.Forms.Button();
            this.syncPeriodComboBox = new System.Windows.Forms.ComboBox();
            this.lblSyncPeriod = new System.Windows.Forms.Label();
            this.periodicSyncOnOffCheckBox = new System.Windows.Forms.CheckBox();
            this.lblPeriodicSyncSet = new System.Windows.Forms.Label();
            this.tabPostLoginSettings = new System.Windows.Forms.TabPage();
            this.postLoginPathButton = new System.Windows.Forms.Button();
            this.postLoginTimeLabel = new System.Windows.Forms.Label();
            this.postLoginPeriodNumUpDown = new System.Windows.Forms.NumericUpDown();
            this.postLoginPeriodicCheckBox = new System.Windows.Forms.CheckBox();
            this.postLoginPathTextBox = new System.Windows.Forms.TextBox();
            this.postLoginPathLabel = new System.Windows.Forms.Label();
            this.btnPostLoginSettingsSave = new System.Windows.Forms.Button();
            this.lblPostLoginSettings = new System.Windows.Forms.Label();
            this.tabProgramsControlSettings = new System.Windows.Forms.TabPage();
            this.chbProgramsControlEnabled = new System.Windows.Forms.CheckBox();
            this.btnProgramsControlSettingsSave = new System.Windows.Forms.Button();
            this.lblProgramsControlSettings = new System.Windows.Forms.Label();
            this.tabCommandsHistory = new System.Windows.Forms.TabPage();
            this.snapshotCheckBox = new System.Windows.Forms.CheckBox();
            this.screenshotCheckBox = new System.Windows.Forms.CheckBox();
            this.currentUserNameCheckBox = new System.Windows.Forms.CheckBox();
            this.userEnviromentCheckBox = new System.Windows.Forms.CheckBox();
            this.commandsHistoryPathButton = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.commandsHistoryPeriodNumUpDown = new System.Windows.Forms.NumericUpDown();
            this.commandsHistoryPeriodCheckBox = new System.Windows.Forms.CheckBox();
            this.commandsHistoryPathTextBox = new System.Windows.Forms.TextBox();
            this.lblCommandsHistoryPath = new System.Windows.Forms.Label();
            this.btnCommandsHistorySettingsSave = new System.Windows.Forms.Button();
            this.lblCommandsHistorySettings = new System.Windows.Forms.Label();
            this.tabFileTransferSettings = new System.Windows.Forms.TabPage();
            this.tempDirectoryButton = new System.Windows.Forms.Button();
            this.tempDirectoryTextBox = new System.Windows.Forms.TextBox();
            this.lblTempDirectory = new System.Windows.Forms.Label();
            this.downloadDirectoryButton = new System.Windows.Forms.Button();
            this.downloadDirectoryTextBox = new System.Windows.Forms.TextBox();
            this.lblDownloadDirectory = new System.Windows.Forms.Label();
            this.uploadDirectoryButton = new System.Windows.Forms.Button();
            this.uploadDirectoryTextBox = new System.Windows.Forms.TextBox();
            this.lblUploadDirectory = new System.Windows.Forms.Label();
            this.btnFileTransferSettings = new System.Windows.Forms.Button();
            this.lblFileTransferSettings = new System.Windows.Forms.Label();
            this.tabUpdateSettings = new System.Windows.Forms.TabPage();
            this.updateDirPathButton = new System.Windows.Forms.Button();
            this.updateDirPathTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.updaterPathButton = new System.Windows.Forms.Button();
            this.updaterPathTextBox = new System.Windows.Forms.TextBox();
            this.lblUpdaterPath = new System.Windows.Forms.Label();
            this.lblUpdateHours = new System.Windows.Forms.Label();
            this.updatesPeriodNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.updatesEnableCheckBox = new System.Windows.Forms.CheckBox();
            this.btnUpdateSettingsSave = new System.Windows.Forms.Button();
            this.lblUpdateSettings = new System.Windows.Forms.Label();
            this.splitter28 = new System.Windows.Forms.Splitter();
            this.confTreeView = new System.Windows.Forms.TreeView();
            this.personalTabPage = new System.Windows.Forms.TabPage();
            this.personalPanel = new System.Windows.Forms.Panel();
            this.personalAccoutsParametersPanel = new System.Windows.Forms.Panel();
            this.personalAccountsParametersSplitContainer = new System.Windows.Forms.SplitContainer();
            this.personalUserAccountsGroupBox = new System.Windows.Forms.GroupBox();
            this.personalAccountsDataGridView = new System.Windows.Forms.DataGridView();
            this.personalAuthSystemNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.personalUserNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.personalUserPasswordColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.personalPassThruPwdColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.personalLastLogonDateColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.personalAccountsBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton84 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel16 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton85 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton86 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton87 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator47 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox16 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator48 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton88 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton89 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator49 = new System.Windows.Forms.ToolStripSeparator();
            this.personalAccountsBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.personalAccountsBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator44 = new System.Windows.Forms.ToolStripSeparator();
            this.personalAccountsBindingNavigatorChangePwdItem = new System.Windows.Forms.ToolStripButton();
            this.personalAccountsHeaderPanel = new System.Windows.Forms.Panel();
            this.personalAccountsLabel = new System.Windows.Forms.Label();
            this.personalParametersGroupBox = new System.Windows.Forms.GroupBox();
            this.personalParametersDataGridView = new System.Windows.Forms.DataGridView();
            this.personalParameterNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.personalParameterValueColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.personalParametersBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton91 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel17 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton92 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton93 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton94 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator50 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox17 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator51 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton95 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton96 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator52 = new System.Windows.Forms.ToolStripSeparator();
            this.personalParametersBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.personalParametersBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.personalCheckValuesHeaderPanel = new System.Windows.Forms.Panel();
            this.personalCheckValuesHeaderLabel = new System.Windows.Forms.Label();
            this.personalPwdSettingsPanel = new System.Windows.Forms.Panel();
            this.personalChangePasswordPanel = new System.Windows.Forms.Panel();
            this.changePasswordButton = new System.Windows.Forms.Button();
            this.personalPwdResetSettingsPanel = new System.Windows.Forms.Panel();
            this.personalPwdTypeLabel = new System.Windows.Forms.Label();
            this.personalPwdTypeComboBox = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.personalSMSResetCheckBox = new System.Windows.Forms.CheckBox();
            this.personalEmailResetCheckBox = new System.Windows.Forms.CheckBox();
            this.personalPwdResetPanel = new System.Windows.Forms.Panel();
            this.personalPwdResetDateLabel = new System.Windows.Forms.Label();
            this.tempInstructionLabel1 = new System.Windows.Forms.Label();
            this.personalPwdResetPeriodLabel = new System.Windows.Forms.Label();
            this.personalPasswrodSettingLabel = new System.Windows.Forms.Label();
            this.personalVerticalSplitPanel = new System.Windows.Forms.Panel();
            this.refreshUserButton = new System.Windows.Forms.Button();
            this.saveUserButton = new System.Windows.Forms.Button();
            this.personalGroupsLabel = new System.Windows.Forms.Label();
            this.personalGroupsListView = new System.Windows.Forms.ListView();
            this.label1 = new System.Windows.Forms.Label();
            this.personalUserPhoneTextBox = new System.Windows.Forms.TextBox();
            this.personalUserEmailTextBox = new System.Windows.Forms.TextBox();
            this.personalUserNameTextBox = new System.Windows.Forms.TextBox();
            this.personalPwdAttemptsLabel = new System.Windows.Forms.Label();
            this.personalFullNameTextBox = new System.Windows.Forms.TextBox();
            this.personalMaxPwdAttemptsLabel = new System.Windows.Forms.Label();
            this.personalLogonDateLabel = new System.Windows.Forms.Label();
            this.personalEducationLabel = new System.Windows.Forms.Label();
            this.scheduleTabPage = new System.Windows.Forms.TabPage();
            this.scheduleSplitContainer = new System.Windows.Forms.SplitContainer();
            this.controlledProgramsDataGridView = new System.Windows.Forms.DataGridView();
            this.controlledProgramNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.controlledProgramAllowedColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.controlledProgramsBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton103 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel21 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton110 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton111 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton112 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator64 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox21 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator65 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton113 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton114 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator66 = new System.Windows.Forms.ToolStripSeparator();
            this.controlledProgramsBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.controlledProgramsBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.scheduleDataGridView = new System.Windows.Forms.DataGridView();
            this.scheduleUserIDColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.scheduleGroupIDColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.scheduleUserNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.scheduleGroupNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.scheduleComputerNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.scheduleProgramNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.scheduleFunctionNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.scheduleActionNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.scheduleIncrementValuesColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.scheduleConditionStringColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.scheduleBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripButton115 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel22 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton116 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton117 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton118 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator67 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox22 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator68 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton119 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton120 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator69 = new System.Windows.Forms.ToolStripSeparator();
            this.scheduleBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.scheduleBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator70 = new System.Windows.Forms.ToolStripSeparator();
            this.scheduleConditionBuilderItem = new System.Windows.Forms.ToolStripButton();
            this.mainPanelImageList = new System.Windows.Forms.ImageList(this.components);
            this.openImageDialog = new System.Windows.Forms.OpenFileDialog();
            this.openTextFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.openLogFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.pwdToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.logFilesFolderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.postLoginOpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.commandHistoryOpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.directoriesBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.openUpdaterFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.updateDirBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.eduLessonsImageList = new System.Windows.Forms.ImageList(this.components);
            userPwdAttemptsCountLabel = new System.Windows.Forms.Label();
            userMaxPwdAttemptsCountLabel = new System.Windows.Forms.Label();
            usrEducationLabel = new System.Windows.Forms.Label();
            lessonOrderLabel = new System.Windows.Forms.Label();
            userNameLabel = new System.Windows.Forms.Label();
            personalFullNameLabel = new System.Windows.Forms.Label();
            personalUserNameLabel = new System.Windows.Forms.Label();
            personalUserEmailLabel = new System.Windows.Forms.Label();
            personalUserPhoneLabel = new System.Windows.Forms.Label();
            userPhoneLabel = new System.Windows.Forms.Label();
            userEmailLabel = new System.Windows.Forms.Label();
            userPwdResetPeriodLabel = new System.Windows.Forms.Label();
            checkParamTitleLabel = new System.Windows.Forms.Label();
            usrAccListTitleLabel = new System.Windows.Forms.Label();
            userGroupsTitleLabel = new System.Windows.Forms.Label();
            rightAnswerIDLabel = new System.Windows.Forms.Label();
            questionOrderLabel = new System.Windows.Forms.Label();
            this.mainMenu.SuspendLayout();
            this.mainPanel.SuspendLayout();
            this.mainTabControl.SuspendLayout();
            this.usersTabPage.SuspendLayout();
            this.userManagementTabControl.SuspendLayout();
            this.userPage.SuspendLayout();
            this.userDetailsTabControl.SuspendLayout();
            this.mainUsrInfoPage.SuspendLayout();
            this.usrGroupsInfoPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userGroupsDataGridView)).BeginInit();
            this.usrPermissionsPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userPermissionsDataGridView)).BeginInit();
            this.userPwdPage.SuspendLayout();
            this.usrEduPage.SuspendLayout();
            this.usrAccountsPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userAccountsDataGridView)).BeginInit();
            this.usrAccListTitlePanel.SuspendLayout();
            this.usrCheckParamsPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userCheckValuesDataGridView)).BeginInit();
            this.checkParamTitlePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userNamesDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.usersBindingNavigator)).BeginInit();
            this.usersBindingNavigator.SuspendLayout();
            this.userGroupsPage.SuspendLayout();
            this.groupDetailsPanel.SuspendLayout();
            this.groupUsersGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.usersGroupDataGridView)).BeginInit();
            this.groupAuthSystemsGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.groupGroupAuthSystemsDataGridView)).BeginInit();
            this.groupReferencesPanel.SuspendLayout();
            this.groupPermissionsGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.groupPermissionsDataGridView)).BeginInit();
            this.groupListGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.groupsDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.groupsBindingNavigator)).BeginInit();
            this.groupsBindingNavigator.SuspendLayout();
            this.computersPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.computersDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.computersBindingNavigator)).BeginInit();
            this.computersBindingNavigator.SuspendLayout();
            this.authSystemsPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.authSystemsDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.authSystemsBindingNavigator)).BeginInit();
            this.authSystemsBindingNavigator.SuspendLayout();
            this.presetTabPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.presetSplitContainer)).BeginInit();
            this.presetSplitContainer.Panel1.SuspendLayout();
            this.presetSplitContainer.Panel2.SuspendLayout();
            this.presetSplitContainer.SuspendLayout();
            this.presetDetailsMainPanel.SuspendLayout();
            this.presetDetailsSubPanel.SuspendLayout();
            this.presetScreenObjectsGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.presetScreenObjectsDataGridView)).BeginInit();
            this.presetScreensGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.presetScreensDataGridView)).BeginInit();
            this.presetNamesGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.presetNamesDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.presetBindingNavigator)).BeginInit();
            this.presetBindingNavigator.SuspendLayout();
            this.screenObjectsPanel.SuspendLayout();
            this.screenObjectsGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.screenObjectsDataGridView)).BeginInit();
            this.screenObjectValuesTabControl.SuspendLayout();
            this.tabScreenObjectText.SuspendLayout();
            this.screenObjectTextPanel.SuspendLayout();
            this.tabScreenObjectImage.SuspendLayout();
            this.screenObjectImagePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.screenObjectPictureBox)).BeginInit();
            this.tabScreenObjectListValues.SuspendLayout();
            this.screenObjectListValuesPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.screenObjectListValuesDataGridView)).BeginInit();
            this.screensGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.screensDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.screenObjectsBindingNavigator)).BeginInit();
            this.screenObjectsBindingNavigator.SuspendLayout();
            this.educationTabPage.SuspendLayout();
            this.educationMainPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.educationMainSplitContainer)).BeginInit();
            this.educationMainSplitContainer.Panel1.SuspendLayout();
            this.educationMainSplitContainer.Panel2.SuspendLayout();
            this.educationMainSplitContainer.SuspendLayout();
            this.eduEditorPanel.SuspendLayout();
            this.eduLessonsTabControl.SuspendLayout();
            this.tabLessons.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduLessonSplitContainer)).BeginInit();
            this.eduLessonSplitContainer.Panel1.SuspendLayout();
            this.eduLessonSplitContainer.Panel2.SuspendLayout();
            this.eduLessonSplitContainer.SuspendLayout();
            this.eduLessonImagePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduLessonPictureBox)).BeginInit();
            this.eduLessonTextPanel.SuspendLayout();
            this.lessonsOrderPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduLessonsBindingNavigator)).BeginInit();
            this.eduLessonsBindingNavigator.SuspendLayout();
            this.tabQuestions.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduQuestionSplitContainer)).BeginInit();
            this.eduQuestionSplitContainer.Panel1.SuspendLayout();
            this.eduQuestionSplitContainer.Panel2.SuspendLayout();
            this.eduQuestionSplitContainer.SuspendLayout();
            this.eduQuestionTextPanel.SuspendLayout();
            this.questionOrderPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduQuestionsBindingNavigator)).BeginInit();
            this.eduQuestionsBindingNavigator.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduAnswersDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduAnswersBindingNavigator)).BeginInit();
            this.eduAnswersBindingNavigator.SuspendLayout();
            this.tabAnswers.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.generalAnswersListDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduAllAnswersBindingNavigator)).BeginInit();
            this.eduAllAnswersBindingNavigator.SuspendLayout();
            this.eduCategoriesGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduCategoriesDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduCategoriesBindingNavigator)).BeginInit();
            this.eduCategoriesBindingNavigator.SuspendLayout();
            this.eduButtonsBottomPanel.SuspendLayout();
            this.eduTabControl.SuspendLayout();
            this.usrEduTabPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userEducationSplitContainer)).BeginInit();
            this.userEducationSplitContainer.Panel1.SuspendLayout();
            this.userEducationSplitContainer.Panel2.SuspendLayout();
            this.userEducationSplitContainer.SuspendLayout();
            this.eduUserCategoriesGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserCategoriesDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserCategoriesBindingNavigator)).BeginInit();
            this.eduUserCategoriesBindingNavigator.SuspendLayout();
            this.eduUserHistoryGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserHistoryDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserHistoryBindingNavigator)).BeginInit();
            this.eduUserHistoryBindingNavigator.SuspendLayout();
            this.eduUsersGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduUsersDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduUsersBindingNavigator)).BeginInit();
            this.eduUsersBindingNavigator.SuspendLayout();
            this.usrGroupEduTabPage.SuspendLayout();
            this.eduUserGroupCategoriesGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserGroupCategoriesDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserGroupCategoriesBindingNavigator)).BeginInit();
            this.eduUserGroupCategoriesBindingNavigator.SuspendLayout();
            this.eduUserGroupsGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserGroupsDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserGroupsBindingNavigator)).BeginInit();
            this.eduUserGroupsBindingNavigator.SuspendLayout();
            this.notificationTabPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.notificationSplitContainer)).BeginInit();
            this.notificationSplitContainer.Panel1.SuspendLayout();
            this.notificationSplitContainer.Panel2.SuspendLayout();
            this.notificationSplitContainer.SuspendLayout();
            this.noticesImageTextPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.noticeValuesSplitContainer)).BeginInit();
            this.noticeValuesSplitContainer.Panel1.SuspendLayout();
            this.noticeValuesSplitContainer.Panel2.SuspendLayout();
            this.noticeValuesSplitContainer.SuspendLayout();
            this.notificationPicturePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.notificationPictureBox)).BeginInit();
            this.notificationTextPanel.SuspendLayout();
            this.noticesTopPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.notificationBindingNavigator)).BeginInit();
            this.notificationBindingNavigator.SuspendLayout();
            this.notificationsTabControl.SuspendLayout();
            this.userNotificationsTabPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userNotificationSplitContainer)).BeginInit();
            this.userNotificationSplitContainer.Panel1.SuspendLayout();
            this.userNotificationSplitContainer.Panel2.SuspendLayout();
            this.userNotificationSplitContainer.SuspendLayout();
            this.userNotificationGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userNotificationDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.userNotificationBindingNavigator)).BeginInit();
            this.userNotificationBindingNavigator.SuspendLayout();
            this.userNotificationHistoryGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userNotificationHistoryDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.userNotificationHistoryBindingNavigator)).BeginInit();
            this.userNotificationHistoryBindingNavigator.SuspendLayout();
            this.notificationUsersGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.notificationUsersDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.notificationUsersBindingNavigator)).BeginInit();
            this.notificationUsersBindingNavigator.SuspendLayout();
            this.userGroupNotificationsTabPage.SuspendLayout();
            this.userGroupNotificationGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userGroupNotificationDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.userGroupsNotificationBindingNavigator)).BeginInit();
            this.userGroupsNotificationBindingNavigator.SuspendLayout();
            this.notificationUserGroupsGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.notificationUserGroupsDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.notificationUserGroupsBindingNavigator)).BeginInit();
            this.notificationUserGroupsBindingNavigator.SuspendLayout();
            this.licenseTabPage.SuspendLayout();
            this.licManagmentMainPanel.SuspendLayout();
            this.licenseBottomPanel.SuspendLayout();
            this.logFilesTabPage.SuspendLayout();
            this.logFileMainPanel.SuspendLayout();
            this.logFilesPanel.SuspendLayout();
            this.confTabPage.SuspendLayout();
            this.confTabControl.SuspendLayout();
            this.tabServiceControl.SuspendLayout();
            this.servicesGroupBox.SuspendLayout();
            this.servicesButtonsPanel.SuspendLayout();
            this.serviceDescriptionGroupBox.SuspendLayout();
            this.tabIPCSettings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.globalServerPriorityNud)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.serverPriorityNud)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.desktopServerPriorityNud)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.hubServerPriorityNud)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.hostServerPriorityNud)).BeginInit();
            this.tabDatabaseSettings.SuspendLayout();
            this.tabMessagesSettings.SuspendLayout();
            this.tabLOGSettings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fixedSizeNumUpDown)).BeginInit();
            this.tabServicesConfiguration.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.updateSettingsPictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fileTransferPictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.commandsHistorySettingsPictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.programsControlSettingsPictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.postLoginSettingsPictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.logSettingsPictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.msgSettingsPictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dbSettingsPictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ipcSettingsPictureBox)).BeginInit();
            this.tabSynchronization.SuspendLayout();
            this.revLinkTabControl.SuspendLayout();
            this.revLinkUsersTabPage.SuspendLayout();
            this.revLinkGroupsTabPage.SuspendLayout();
            this.tabPostLoginSettings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.postLoginPeriodNumUpDown)).BeginInit();
            this.tabProgramsControlSettings.SuspendLayout();
            this.tabCommandsHistory.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.commandsHistoryPeriodNumUpDown)).BeginInit();
            this.tabFileTransferSettings.SuspendLayout();
            this.tabUpdateSettings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.updatesPeriodNumericUpDown)).BeginInit();
            this.personalTabPage.SuspendLayout();
            this.personalPanel.SuspendLayout();
            this.personalAccoutsParametersPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.personalAccountsParametersSplitContainer)).BeginInit();
            this.personalAccountsParametersSplitContainer.Panel1.SuspendLayout();
            this.personalAccountsParametersSplitContainer.Panel2.SuspendLayout();
            this.personalAccountsParametersSplitContainer.SuspendLayout();
            this.personalUserAccountsGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.personalAccountsDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.personalAccountsBindingNavigator)).BeginInit();
            this.personalAccountsBindingNavigator.SuspendLayout();
            this.personalAccountsHeaderPanel.SuspendLayout();
            this.personalParametersGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.personalParametersDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.personalParametersBindingNavigator)).BeginInit();
            this.personalParametersBindingNavigator.SuspendLayout();
            this.personalCheckValuesHeaderPanel.SuspendLayout();
            this.personalPwdSettingsPanel.SuspendLayout();
            this.personalChangePasswordPanel.SuspendLayout();
            this.personalPwdResetSettingsPanel.SuspendLayout();
            this.personalPwdResetPanel.SuspendLayout();
            this.scheduleTabPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.scheduleSplitContainer)).BeginInit();
            this.scheduleSplitContainer.Panel1.SuspendLayout();
            this.scheduleSplitContainer.Panel2.SuspendLayout();
            this.scheduleSplitContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.controlledProgramsDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.controlledProgramsBindingNavigator)).BeginInit();
            this.controlledProgramsBindingNavigator.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.scheduleDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.scheduleBindingNavigator)).BeginInit();
            this.scheduleBindingNavigator.SuspendLayout();
            this.SuspendLayout();
            // 
            // userPwdAttemptsCountLabel
            // 
            userPwdAttemptsCountLabel.AutoSize = true;
            userPwdAttemptsCountLabel.Location = new System.Drawing.Point(17, 52);
            userPwdAttemptsCountLabel.Name = "userPwdAttemptsCountLabel";
            userPwdAttemptsCountLabel.Size = new System.Drawing.Size(243, 13);
            userPwdAttemptsCountLabel.TabIndex = 109;
            userPwdAttemptsCountLabel.Text = "Number of attempts to enter the correct password:";
            // 
            // userMaxPwdAttemptsCountLabel
            // 
            userMaxPwdAttemptsCountLabel.AutoSize = true;
            userMaxPwdAttemptsCountLabel.Location = new System.Drawing.Point(17, 82);
            userMaxPwdAttemptsCountLabel.Name = "userMaxPwdAttemptsCountLabel";
            userMaxPwdAttemptsCountLabel.Size = new System.Drawing.Size(288, 13);
            userMaxPwdAttemptsCountLabel.TabIndex = 111;
            userMaxPwdAttemptsCountLabel.Text = "Maximum number of attempts to enter the correct password:";
            // 
            // usrEducationLabel
            // 
            usrEducationLabel.AutoSize = true;
            usrEducationLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            usrEducationLabel.Location = new System.Drawing.Point(31, 33);
            usrEducationLabel.Name = "usrEducationLabel";
            usrEducationLabel.Size = new System.Drawing.Size(207, 13);
            usrEducationLabel.TabIndex = 117;
            usrEducationLabel.Text = "Education settings for current user:";
            // 
            // lessonOrderLabel
            // 
            lessonOrderLabel.AutoSize = true;
            lessonOrderLabel.Location = new System.Drawing.Point(18, 16);
            lessonOrderLabel.Name = "lessonOrderLabel";
            lessonOrderLabel.Size = new System.Drawing.Size(71, 13);
            lessonOrderLabel.TabIndex = 12;
            lessonOrderLabel.Text = "Lesson order:";
            // 
            // userNameLabel
            // 
            userNameLabel.AutoSize = true;
            userNameLabel.Location = new System.Drawing.Point(48, 70);
            userNameLabel.Name = "userNameLabel";
            userNameLabel.Size = new System.Drawing.Size(61, 13);
            userNameLabel.TabIndex = 122;
            userNameLabel.Text = "User name:";
            // 
            // personalFullNameLabel
            // 
            personalFullNameLabel.AutoSize = true;
            personalFullNameLabel.Location = new System.Drawing.Point(28, 45);
            personalFullNameLabel.Name = "personalFullNameLabel";
            personalFullNameLabel.Size = new System.Drawing.Size(55, 13);
            personalFullNameLabel.TabIndex = 128;
            personalFullNameLabel.Text = "Full name:";
            // 
            // personalUserNameLabel
            // 
            personalUserNameLabel.AutoSize = true;
            personalUserNameLabel.Location = new System.Drawing.Point(28, 75);
            personalUserNameLabel.Name = "personalUserNameLabel";
            personalUserNameLabel.Size = new System.Drawing.Size(61, 13);
            personalUserNameLabel.TabIndex = 126;
            personalUserNameLabel.Text = "User name:";
            // 
            // personalUserEmailLabel
            // 
            personalUserEmailLabel.AutoSize = true;
            personalUserEmailLabel.Location = new System.Drawing.Point(28, 105);
            personalUserEmailLabel.Name = "personalUserEmailLabel";
            personalUserEmailLabel.Size = new System.Drawing.Size(35, 13);
            personalUserEmailLabel.TabIndex = 134;
            personalUserEmailLabel.Text = "Email:";
            // 
            // personalUserPhoneLabel
            // 
            personalUserPhoneLabel.AutoSize = true;
            personalUserPhoneLabel.Location = new System.Drawing.Point(28, 135);
            personalUserPhoneLabel.Name = "personalUserPhoneLabel";
            personalUserPhoneLabel.Size = new System.Drawing.Size(79, 13);
            personalUserPhoneLabel.TabIndex = 136;
            personalUserPhoneLabel.Text = "Phone number:";
            // 
            // userPhoneLabel
            // 
            userPhoneLabel.AutoSize = true;
            userPhoneLabel.Location = new System.Drawing.Point(48, 131);
            userPhoneLabel.Name = "userPhoneLabel";
            userPhoneLabel.Size = new System.Drawing.Size(41, 13);
            userPhoneLabel.TabIndex = 140;
            userPhoneLabel.Text = "Phone:";
            // 
            // userEmailLabel
            // 
            userEmailLabel.AutoSize = true;
            userEmailLabel.Location = new System.Drawing.Point(48, 100);
            userEmailLabel.Name = "userEmailLabel";
            userEmailLabel.Size = new System.Drawing.Size(35, 13);
            userEmailLabel.TabIndex = 138;
            userEmailLabel.Text = "Email:";
            // 
            // userPwdResetPeriodLabel
            // 
            userPwdResetPeriodLabel.AutoSize = true;
            userPwdResetPeriodLabel.Location = new System.Drawing.Point(19, 389);
            userPwdResetPeriodLabel.Name = "userPwdResetPeriodLabel";
            userPwdResetPeriodLabel.Size = new System.Drawing.Size(176, 13);
            userPwdResetPeriodLabel.TabIndex = 128;
            userPwdResetPeriodLabel.Text = "Period of temporary password use is";
            // 
            // checkParamTitleLabel
            // 
            checkParamTitleLabel.AutoSize = true;
            checkParamTitleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            checkParamTitleLabel.Location = new System.Drawing.Point(43, 12);
            checkParamTitleLabel.Name = "checkParamTitleLabel";
            checkParamTitleLabel.Size = new System.Drawing.Size(240, 13);
            checkParamTitleLabel.TabIndex = 118;
            checkParamTitleLabel.Text = "Parameters for checking for current user:";
            // 
            // usrAccListTitleLabel
            // 
            usrAccListTitleLabel.AutoSize = true;
            usrAccListTitleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            usrAccListTitleLabel.Location = new System.Drawing.Point(12, 55);
            usrAccListTitleLabel.Name = "usrAccListTitleLabel";
            usrAccListTitleLabel.Size = new System.Drawing.Size(183, 13);
            usrAccListTitleLabel.TabIndex = 118;
            usrAccListTitleLabel.Text = "List of current user\'s accounts:";
            // 
            // userGroupsTitleLabel
            // 
            userGroupsTitleLabel.AutoSize = true;
            userGroupsTitleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            userGroupsTitleLabel.Location = new System.Drawing.Point(20, 30);
            userGroupsTitleLabel.Name = "userGroupsTitleLabel";
            userGroupsTitleLabel.Size = new System.Drawing.Size(138, 13);
            userGroupsTitleLabel.TabIndex = 118;
            userGroupsTitleLabel.Text = "Groups of current user:";
            // 
            // rightAnswerIDLabel
            // 
            rightAnswerIDLabel.AutoSize = true;
            rightAnswerIDLabel.Location = new System.Drawing.Point(9, 47);
            rightAnswerIDLabel.Name = "rightAnswerIDLabel";
            rightAnswerIDLabel.Size = new System.Drawing.Size(72, 13);
            rightAnswerIDLabel.TabIndex = 27;
            rightAnswerIDLabel.Text = "Right answer:";
            // 
            // questionOrderLabel
            // 
            questionOrderLabel.AutoSize = true;
            questionOrderLabel.Location = new System.Drawing.Point(9, 21);
            questionOrderLabel.Name = "questionOrderLabel";
            questionOrderLabel.Size = new System.Drawing.Size(79, 13);
            questionOrderLabel.TabIndex = 25;
            questionOrderLabel.Text = "Question order:";
            // 
            // mainMenu
            // 
            this.mainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.connectionToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.mainMenu.Location = new System.Drawing.Point(0, 0);
            this.mainMenu.Name = "mainMenu";
            this.mainMenu.Size = new System.Drawing.Size(1008, 24);
            this.mainMenu.TabIndex = 1;
            this.mainMenu.Text = "MainMenu";
            // 
            // connectionToolStripMenuItem
            // 
            this.connectionToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.connectToolStripMenuItem,
            this.disconnectToolStripMenuItem,
            this.toolStripMenuItem1,
            this.exitToolStripMenuItem});
            this.connectionToolStripMenuItem.Name = "connectionToolStripMenuItem";
            this.connectionToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.C)));
            this.connectionToolStripMenuItem.Size = new System.Drawing.Size(81, 20);
            this.connectionToolStripMenuItem.Text = "Connection";
            // 
            // connectToolStripMenuItem
            // 
            this.connectToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("connectToolStripMenuItem.Image")));
            this.connectToolStripMenuItem.Name = "connectToolStripMenuItem";
            this.connectToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.C)));
            this.connectToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.connectToolStripMenuItem.Text = "Connect";
            this.connectToolStripMenuItem.Click += new System.EventHandler(this.connectToolStripMenuItem_Click);
            // 
            // disconnectToolStripMenuItem
            // 
            this.disconnectToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("disconnectToolStripMenuItem.Image")));
            this.disconnectToolStripMenuItem.Name = "disconnectToolStripMenuItem";
            this.disconnectToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.D)));
            this.disconnectToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.disconnectToolStripMenuItem.Text = "Disconnect";
            this.disconnectToolStripMenuItem.Click += new System.EventHandler(this.disconnectToolStripMenuItem_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(168, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("exitToolStripMenuItem.Image")));
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.D)));
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("aboutToolStripMenuItem.Image")));
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // statusStrip
            // 
            this.statusStrip.Location = new System.Drawing.Point(0, 707);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(1008, 22);
            this.statusStrip.TabIndex = 3;
            this.statusStrip.Text = "statusStrip";
            // 
            // mainPanel
            // 
            this.mainPanel.Controls.Add(this.mainTabControl);
            this.mainPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainPanel.Location = new System.Drawing.Point(0, 24);
            this.mainPanel.Name = "mainPanel";
            this.mainPanel.Size = new System.Drawing.Size(1008, 683);
            this.mainPanel.TabIndex = 4;
            this.mainPanel.Visible = false;
            // 
            // mainTabControl
            // 
            this.mainTabControl.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
            this.mainTabControl.Controls.Add(this.usersTabPage);
            this.mainTabControl.Controls.Add(this.presetTabPage);
            this.mainTabControl.Controls.Add(this.educationTabPage);
            this.mainTabControl.Controls.Add(this.notificationTabPage);
            this.mainTabControl.Controls.Add(this.licenseTabPage);
            this.mainTabControl.Controls.Add(this.logFilesTabPage);
            this.mainTabControl.Controls.Add(this.confTabPage);
            this.mainTabControl.Controls.Add(this.personalTabPage);
            this.mainTabControl.Controls.Add(this.scheduleTabPage);
            this.mainTabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainTabControl.ImageList = this.mainPanelImageList;
            this.mainTabControl.Location = new System.Drawing.Point(0, 0);
            this.mainTabControl.Name = "mainTabControl";
            this.mainTabControl.SelectedIndex = 0;
            this.mainTabControl.Size = new System.Drawing.Size(1008, 683);
            this.mainTabControl.TabIndex = 1;
            this.mainTabControl.SelectedIndexChanged += new System.EventHandler(this.mainTabControl_SelectedIndexChanged);
            // 
            // usersTabPage
            // 
            this.usersTabPage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.usersTabPage.Controls.Add(this.userManagementTabControl);
            this.usersTabPage.ImageIndex = 0;
            this.usersTabPage.Location = new System.Drawing.Point(4, 42);
            this.usersTabPage.Name = "usersTabPage";
            this.usersTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.usersTabPage.Size = new System.Drawing.Size(1000, 637);
            this.usersTabPage.TabIndex = 0;
            this.usersTabPage.Text = "Users and computers";
            this.usersTabPage.UseVisualStyleBackColor = true;
            // 
            // userManagementTabControl
            // 
            this.userManagementTabControl.Controls.Add(this.userPage);
            this.userManagementTabControl.Controls.Add(this.userGroupsPage);
            this.userManagementTabControl.Controls.Add(this.computersPage);
            this.userManagementTabControl.Controls.Add(this.authSystemsPage);
            this.userManagementTabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userManagementTabControl.ImageList = this.usersTabImageList;
            this.userManagementTabControl.Location = new System.Drawing.Point(3, 3);
            this.userManagementTabControl.Name = "userManagementTabControl";
            this.userManagementTabControl.SelectedIndex = 0;
            this.userManagementTabControl.Size = new System.Drawing.Size(992, 629);
            this.userManagementTabControl.TabIndex = 4;
            // 
            // userPage
            // 
            this.userPage.BackColor = System.Drawing.SystemColors.Control;
            this.userPage.Controls.Add(this.userDetailsTabControl);
            this.userPage.Controls.Add(this.userNamesDataGridView);
            this.userPage.Controls.Add(this.usersBindingNavigator);
            this.userPage.ImageIndex = 0;
            this.userPage.Location = new System.Drawing.Point(4, 31);
            this.userPage.Name = "userPage";
            this.userPage.Padding = new System.Windows.Forms.Padding(3);
            this.userPage.Size = new System.Drawing.Size(984, 594);
            this.userPage.TabIndex = 0;
            this.userPage.Text = "Users";
            // 
            // userDetailsTabControl
            // 
            this.userDetailsTabControl.Controls.Add(this.mainUsrInfoPage);
            this.userDetailsTabControl.Controls.Add(this.usrGroupsInfoPage);
            this.userDetailsTabControl.Controls.Add(this.usrPermissionsPage);
            this.userDetailsTabControl.Controls.Add(this.userPwdPage);
            this.userDetailsTabControl.Controls.Add(this.usrEduPage);
            this.userDetailsTabControl.Controls.Add(this.usrAccountsPage);
            this.userDetailsTabControl.Controls.Add(this.usrCheckParamsPage);
            this.userDetailsTabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userDetailsTabControl.ImageList = this.usersInfoImageList;
            this.userDetailsTabControl.Location = new System.Drawing.Point(257, 28);
            this.userDetailsTabControl.Name = "userDetailsTabControl";
            this.userDetailsTabControl.SelectedIndex = 0;
            this.userDetailsTabControl.Size = new System.Drawing.Size(724, 563);
            this.userDetailsTabControl.TabIndex = 111;
            // 
            // mainUsrInfoPage
            // 
            this.mainUsrInfoPage.BackColor = System.Drawing.Color.White;
            this.mainUsrInfoPage.Controls.Add(this.novaUserAccessLabel);
            this.mainUsrInfoPage.Controls.Add(this.generalUserTitleLabel);
            this.mainUsrInfoPage.Controls.Add(this.userLockedCheckBox);
            this.mainUsrInfoPage.Controls.Add(this.userPhoneTextBox);
            this.mainUsrInfoPage.Controls.Add(userNameLabel);
            this.mainUsrInfoPage.Controls.Add(userPhoneLabel);
            this.mainUsrInfoPage.Controls.Add(this.userEmailTextBox);
            this.mainUsrInfoPage.Controls.Add(userEmailLabel);
            this.mainUsrInfoPage.Controls.Add(this.lastLogOnDateTimePicker);
            this.mainUsrInfoPage.Controls.Add(this.dateOfLastLogOnLabel);
            this.mainUsrInfoPage.Controls.Add(this.userNameTextBox);
            this.mainUsrInfoPage.ImageIndex = 1;
            this.mainUsrInfoPage.Location = new System.Drawing.Point(4, 23);
            this.mainUsrInfoPage.Name = "mainUsrInfoPage";
            this.mainUsrInfoPage.Padding = new System.Windows.Forms.Padding(3);
            this.mainUsrInfoPage.Size = new System.Drawing.Size(716, 536);
            this.mainUsrInfoPage.TabIndex = 0;
            this.mainUsrInfoPage.Text = "Main info";
            // 
            // novaUserAccessLabel
            // 
            this.novaUserAccessLabel.AutoSize = true;
            this.novaUserAccessLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.novaUserAccessLabel.Location = new System.Drawing.Point(25, 183);
            this.novaUserAccessLabel.Name = "novaUserAccessLabel";
            this.novaUserAccessLabel.Size = new System.Drawing.Size(296, 13);
            this.novaUserAccessLabel.TabIndex = 145;
            this.novaUserAccessLabel.Text = "Information about access to the NovaTend system:";
            // 
            // generalUserTitleLabel
            // 
            this.generalUserTitleLabel.AutoSize = true;
            this.generalUserTitleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.generalUserTitleLabel.Location = new System.Drawing.Point(25, 33);
            this.generalUserTitleLabel.Name = "generalUserTitleLabel";
            this.generalUserTitleLabel.Size = new System.Drawing.Size(121, 13);
            this.generalUserTitleLabel.TabIndex = 144;
            this.generalUserTitleLabel.Text = "General information:";
            // 
            // userLockedCheckBox
            // 
            this.userLockedCheckBox.AutoSize = true;
            this.userLockedCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userLockedCheckBox.Location = new System.Drawing.Point(51, 263);
            this.userLockedCheckBox.Name = "userLockedCheckBox";
            this.userLockedCheckBox.Size = new System.Drawing.Size(98, 17);
            this.userLockedCheckBox.TabIndex = 143;
            this.userLockedCheckBox.Text = "Account locked";
            this.userLockedCheckBox.UseVisualStyleBackColor = true;
            // 
            // userPhoneTextBox
            // 
            this.userPhoneTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.userPhoneTextBox.Location = new System.Drawing.Point(115, 129);
            this.userPhoneTextBox.Name = "userPhoneTextBox";
            this.userPhoneTextBox.Size = new System.Drawing.Size(289, 20);
            this.userPhoneTextBox.TabIndex = 141;
            this.userPhoneTextBox.Leave += new System.EventHandler(this.userPhoneTextBox_Leave);
            // 
            // userEmailTextBox
            // 
            this.userEmailTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.userEmailTextBox.Location = new System.Drawing.Point(115, 98);
            this.userEmailTextBox.Name = "userEmailTextBox";
            this.userEmailTextBox.Size = new System.Drawing.Size(289, 20);
            this.userEmailTextBox.TabIndex = 139;
            this.userEmailTextBox.Leave += new System.EventHandler(this.userEmailTextBox_Leave);
            // 
            // lastLogOnDateTimePicker
            // 
            this.lastLogOnDateTimePicker.Location = new System.Drawing.Point(150, 218);
            this.lastLogOnDateTimePicker.Name = "lastLogOnDateTimePicker";
            this.lastLogOnDateTimePicker.Size = new System.Drawing.Size(254, 20);
            this.lastLogOnDateTimePicker.TabIndex = 125;
            // 
            // dateOfLastLogOnLabel
            // 
            this.dateOfLastLogOnLabel.AutoSize = true;
            this.dateOfLastLogOnLabel.Location = new System.Drawing.Point(48, 222);
            this.dateOfLastLogOnLabel.Name = "dateOfLastLogOnLabel";
            this.dateOfLastLogOnLabel.Size = new System.Drawing.Size(96, 13);
            this.dateOfLastLogOnLabel.TabIndex = 124;
            this.dateOfLastLogOnLabel.Text = "Date of last log on:";
            // 
            // userNameTextBox
            // 
            this.userNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.userNameTextBox.Location = new System.Drawing.Point(115, 68);
            this.userNameTextBox.Name = "userNameTextBox";
            this.userNameTextBox.Size = new System.Drawing.Size(289, 20);
            this.userNameTextBox.TabIndex = 123;
            this.userNameTextBox.Leave += new System.EventHandler(this.userNameTextBox_Leave);
            // 
            // usrGroupsInfoPage
            // 
            this.usrGroupsInfoPage.BackColor = System.Drawing.Color.White;
            this.usrGroupsInfoPage.Controls.Add(userGroupsTitleLabel);
            this.usrGroupsInfoPage.Controls.Add(this.userGroupsDataGridView);
            this.usrGroupsInfoPage.ImageIndex = 6;
            this.usrGroupsInfoPage.Location = new System.Drawing.Point(4, 23);
            this.usrGroupsInfoPage.Name = "usrGroupsInfoPage";
            this.usrGroupsInfoPage.Padding = new System.Windows.Forms.Padding(3);
            this.usrGroupsInfoPage.Size = new System.Drawing.Size(716, 536);
            this.usrGroupsInfoPage.TabIndex = 1;
            this.usrGroupsInfoPage.Text = "Groups";
            this.usrGroupsInfoPage.Enter += new System.EventHandler(this.usrGroupsInfoPage_Enter);
            // 
            // userGroupsDataGridView
            // 
            this.userGroupsDataGridView.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.userGroupsDataGridView.BackgroundColor = System.Drawing.Color.White;
            this.userGroupsDataGridView.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.userGroupsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.userGroupsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.userGroupNameColumn,
            this.userGroupIDColumn});
            this.userGroupsDataGridView.Location = new System.Drawing.Point(20, 56);
            this.userGroupsDataGridView.Name = "userGroupsDataGridView";
            this.userGroupsDataGridView.Size = new System.Drawing.Size(306, 462);
            this.userGroupsDataGridView.TabIndex = 111;
            this.userGroupsDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.userGroupsDataGridView_CellFormatting);
            this.userGroupsDataGridView.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.userGroupsDataGridView_CellValueChanged);
            this.userGroupsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.userGroupsDataGridView.Enter += new System.EventHandler(this.userGroupsDataGridView_Enter);
            // 
            // userGroupNameColumn
            // 
            this.userGroupNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userGroupNameColumn.HeaderText = "Group name";
            this.userGroupNameColumn.Name = "userGroupNameColumn";
            this.userGroupNameColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.userGroupNameColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.userGroupNameColumn.Width = 250;
            // 
            // userGroupIDColumn
            // 
            this.userGroupIDColumn.HeaderText = "Group ID";
            this.userGroupIDColumn.Name = "userGroupIDColumn";
            this.userGroupIDColumn.Visible = false;
            // 
            // usrPermissionsPage
            // 
            this.usrPermissionsPage.BackColor = System.Drawing.Color.White;
            this.usrPermissionsPage.Controls.Add(this.permissionTitleLabel);
            this.usrPermissionsPage.Controls.Add(this.userPermissionsDataGridView);
            this.usrPermissionsPage.ImageIndex = 3;
            this.usrPermissionsPage.Location = new System.Drawing.Point(4, 23);
            this.usrPermissionsPage.Name = "usrPermissionsPage";
            this.usrPermissionsPage.Padding = new System.Windows.Forms.Padding(3);
            this.usrPermissionsPage.Size = new System.Drawing.Size(716, 536);
            this.usrPermissionsPage.TabIndex = 2;
            this.usrPermissionsPage.Text = "Permissions";
            // 
            // permissionTitleLabel
            // 
            this.permissionTitleLabel.AutoSize = true;
            this.permissionTitleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.permissionTitleLabel.Location = new System.Drawing.Point(20, 30);
            this.permissionTitleLabel.Name = "permissionTitleLabel";
            this.permissionTitleLabel.Size = new System.Drawing.Size(178, 13);
            this.permissionTitleLabel.TabIndex = 3;
            this.permissionTitleLabel.Text = "Current user\'s permissions list:";
            // 
            // userPermissionsDataGridView
            // 
            this.userPermissionsDataGridView.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.userPermissionsDataGridView.BackgroundColor = System.Drawing.Color.White;
            this.userPermissionsDataGridView.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.userPermissionsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.userPermissionsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.userPermissionNameColumn,
            this.userPermissionIDColumn});
            this.userPermissionsDataGridView.Location = new System.Drawing.Point(20, 56);
            this.userPermissionsDataGridView.Name = "userPermissionsDataGridView";
            this.userPermissionsDataGridView.Size = new System.Drawing.Size(314, 462);
            this.userPermissionsDataGridView.TabIndex = 2;
            this.userPermissionsDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.userPermissionsDataGridView_CellFormatting);
            this.userPermissionsDataGridView.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.userPermissionsDataGridView_CellValueChanged);
            this.userPermissionsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.userPermissionsDataGridView.Enter += new System.EventHandler(this.userPermissionsDataGridView_Enter);
            // 
            // userPermissionNameColumn
            // 
            this.userPermissionNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userPermissionNameColumn.HeaderText = "Permissions";
            this.userPermissionNameColumn.Name = "userPermissionNameColumn";
            this.userPermissionNameColumn.Width = 250;
            // 
            // userPermissionIDColumn
            // 
            this.userPermissionIDColumn.HeaderText = "Permission";
            this.userPermissionIDColumn.Name = "userPermissionIDColumn";
            this.userPermissionIDColumn.Visible = false;
            // 
            // userPwdPage
            // 
            this.userPwdPage.Controls.Add(this.resetPwdButton);
            this.userPwdPage.Controls.Add(this.hoursLabel);
            this.userPwdPage.Controls.Add(this.pwdResetTitleLabel);
            this.userPwdPage.Controls.Add(userPwdResetPeriodLabel);
            this.userPwdPage.Controls.Add(this.userPwdResetPeriodTextBox);
            this.userPwdPage.Controls.Add(this.changePwdSettingsButton);
            this.userPwdPage.Controls.Add(this.userPwdResetDateTimePicker);
            this.userPwdPage.Controls.Add(this.pwdUserSettingsTitleLabel);
            this.userPwdPage.Controls.Add(this.userPwdResetDateLabel);
            this.userPwdPage.Controls.Add(userPwdAttemptsCountLabel);
            this.userPwdPage.Controls.Add(this.userPwdResetedCheckBox);
            this.userPwdPage.Controls.Add(this.userPwdAttemptsCountTextBox);
            this.userPwdPage.Controls.Add(this.userSMSPwdResetCheckBox);
            this.userPwdPage.Controls.Add(userMaxPwdAttemptsCountLabel);
            this.userPwdPage.Controls.Add(this.userEmailPwdResetCheckBox);
            this.userPwdPage.Controls.Add(this.userPwdTypeLabel);
            this.userPwdPage.Controls.Add(this.userMaxPwdAttemptsCountTextBox);
            this.userPwdPage.Controls.Add(this.userPwdTypeComboBox);
            this.userPwdPage.ImageIndex = 4;
            this.userPwdPage.Location = new System.Drawing.Point(4, 23);
            this.userPwdPage.Name = "userPwdPage";
            this.userPwdPage.Padding = new System.Windows.Forms.Padding(3);
            this.userPwdPage.Size = new System.Drawing.Size(716, 536);
            this.userPwdPage.TabIndex = 3;
            this.userPwdPage.Text = "Password";
            this.userPwdPage.UseVisualStyleBackColor = true;
            // 
            // resetPwdButton
            // 
            this.resetPwdButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.resetPwdButton.Image = ((System.Drawing.Image)(resources.GetObject("resetPwdButton.Image")));
            this.resetPwdButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.resetPwdButton.Location = new System.Drawing.Point(19, 423);
            this.resetPwdButton.Name = "resetPwdButton";
            this.resetPwdButton.Size = new System.Drawing.Size(202, 37);
            this.resetPwdButton.TabIndex = 148;
            this.resetPwdButton.Text = "Reset user password";
            this.resetPwdButton.UseVisualStyleBackColor = true;
            this.resetPwdButton.Click += new System.EventHandler(this.usersBindingNavigatorPasswordResetItem_Click);
            // 
            // hoursLabel
            // 
            this.hoursLabel.AutoSize = true;
            this.hoursLabel.Location = new System.Drawing.Point(254, 389);
            this.hoursLabel.Name = "hoursLabel";
            this.hoursLabel.Size = new System.Drawing.Size(39, 13);
            this.hoursLabel.TabIndex = 130;
            this.hoursLabel.Text = "hour(s)";
            // 
            // pwdResetTitleLabel
            // 
            this.pwdResetTitleLabel.AutoSize = true;
            this.pwdResetTitleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.pwdResetTitleLabel.Location = new System.Drawing.Point(17, 233);
            this.pwdResetTitleLabel.Name = "pwdResetTitleLabel";
            this.pwdResetTitleLabel.Size = new System.Drawing.Size(165, 13);
            this.pwdResetTitleLabel.TabIndex = 147;
            this.pwdResetTitleLabel.Text = "Settings of password reset :";
            // 
            // userPwdResetPeriodTextBox
            // 
            this.userPwdResetPeriodTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.userPwdResetPeriodTextBox.Location = new System.Drawing.Point(198, 387);
            this.userPwdResetPeriodTextBox.Name = "userPwdResetPeriodTextBox";
            this.userPwdResetPeriodTextBox.Size = new System.Drawing.Size(50, 20);
            this.userPwdResetPeriodTextBox.TabIndex = 129;
            // 
            // changePwdSettingsButton
            // 
            this.changePwdSettingsButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.changePwdSettingsButton.Image = ((System.Drawing.Image)(resources.GetObject("changePwdSettingsButton.Image")));
            this.changePwdSettingsButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.changePwdSettingsButton.Location = new System.Drawing.Point(20, 159);
            this.changePwdSettingsButton.Name = "changePwdSettingsButton";
            this.changePwdSettingsButton.Size = new System.Drawing.Size(201, 37);
            this.changePwdSettingsButton.TabIndex = 146;
            this.changePwdSettingsButton.Text = "User password settings";
            this.changePwdSettingsButton.UseVisualStyleBackColor = true;
            this.changePwdSettingsButton.Click += new System.EventHandler(this.usersBindingNavigatorChangePasswordItem_Click);
            // 
            // userPwdResetDateTimePicker
            // 
            this.userPwdResetDateTimePicker.Location = new System.Drawing.Point(138, 350);
            this.userPwdResetDateTimePicker.Name = "userPwdResetDateTimePicker";
            this.userPwdResetDateTimePicker.Size = new System.Drawing.Size(158, 20);
            this.userPwdResetDateTimePicker.TabIndex = 127;
            // 
            // pwdUserSettingsTitleLabel
            // 
            this.pwdUserSettingsTitleLabel.AutoSize = true;
            this.pwdUserSettingsTitleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.pwdUserSettingsTitleLabel.Location = new System.Drawing.Point(17, 17);
            this.pwdUserSettingsTitleLabel.Name = "pwdUserSettingsTitleLabel";
            this.pwdUserSettingsTitleLabel.Size = new System.Drawing.Size(204, 13);
            this.pwdUserSettingsTitleLabel.TabIndex = 145;
            this.pwdUserSettingsTitleLabel.Text = "Password settings for current user:";
            // 
            // userPwdResetDateLabel
            // 
            this.userPwdResetDateLabel.AutoSize = true;
            this.userPwdResetDateLabel.Location = new System.Drawing.Point(19, 354);
            this.userPwdResetDateLabel.Name = "userPwdResetDateLabel";
            this.userPwdResetDateLabel.Size = new System.Drawing.Size(119, 13);
            this.userPwdResetDateLabel.TabIndex = 126;
            this.userPwdResetDateLabel.Text = "Date of password reset:";
            // 
            // userPwdResetedCheckBox
            // 
            this.userPwdResetedCheckBox.AutoSize = true;
            this.userPwdResetedCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userPwdResetedCheckBox.Location = new System.Drawing.Point(19, 267);
            this.userPwdResetedCheckBox.Name = "userPwdResetedCheckBox";
            this.userPwdResetedCheckBox.Size = new System.Drawing.Size(107, 17);
            this.userPwdResetedCheckBox.TabIndex = 2;
            this.userPwdResetedCheckBox.Text = "Password reseted";
            this.userPwdResetedCheckBox.UseVisualStyleBackColor = true;
            // 
            // userPwdAttemptsCountTextBox
            // 
            this.userPwdAttemptsCountTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.userPwdAttemptsCountTextBox.Location = new System.Drawing.Point(312, 50);
            this.userPwdAttemptsCountTextBox.Name = "userPwdAttemptsCountTextBox";
            this.userPwdAttemptsCountTextBox.Size = new System.Drawing.Size(61, 20);
            this.userPwdAttemptsCountTextBox.TabIndex = 110;
            this.userPwdAttemptsCountTextBox.Enter += new System.EventHandler(this.userNamesDataGridView_Enter);
            // 
            // userSMSPwdResetCheckBox
            // 
            this.userSMSPwdResetCheckBox.AutoSize = true;
            this.userSMSPwdResetCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userSMSPwdResetCheckBox.Location = new System.Drawing.Point(19, 314);
            this.userSMSPwdResetCheckBox.Name = "userSMSPwdResetCheckBox";
            this.userSMSPwdResetCheckBox.Size = new System.Drawing.Size(281, 17);
            this.userSMSPwdResetCheckBox.TabIndex = 1;
            this.userSMSPwdResetCheckBox.Text = "Reset password and send instructions by phone (SMS)";
            this.userSMSPwdResetCheckBox.UseVisualStyleBackColor = true;
            // 
            // userEmailPwdResetCheckBox
            // 
            this.userEmailPwdResetCheckBox.AutoSize = true;
            this.userEmailPwdResetCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userEmailPwdResetCheckBox.Location = new System.Drawing.Point(19, 294);
            this.userEmailPwdResetCheckBox.Name = "userEmailPwdResetCheckBox";
            this.userEmailPwdResetCheckBox.Size = new System.Drawing.Size(243, 17);
            this.userEmailPwdResetCheckBox.TabIndex = 0;
            this.userEmailPwdResetCheckBox.Text = "Reset password and send instructions by email";
            this.userEmailPwdResetCheckBox.UseVisualStyleBackColor = true;
            // 
            // userPwdTypeLabel
            // 
            this.userPwdTypeLabel.AutoSize = true;
            this.userPwdTypeLabel.Location = new System.Drawing.Point(19, 123);
            this.userPwdTypeLabel.Name = "userPwdTypeLabel";
            this.userPwdTypeLabel.Size = new System.Drawing.Size(79, 13);
            this.userPwdTypeLabel.TabIndex = 144;
            this.userPwdTypeLabel.Text = "Password type:";
            // 
            // userMaxPwdAttemptsCountTextBox
            // 
            this.userMaxPwdAttemptsCountTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.userMaxPwdAttemptsCountTextBox.Location = new System.Drawing.Point(312, 79);
            this.userMaxPwdAttemptsCountTextBox.Name = "userMaxPwdAttemptsCountTextBox";
            this.userMaxPwdAttemptsCountTextBox.Size = new System.Drawing.Size(61, 20);
            this.userMaxPwdAttemptsCountTextBox.TabIndex = 112;
            this.userMaxPwdAttemptsCountTextBox.Enter += new System.EventHandler(this.userNamesDataGridView_Enter);
            // 
            // userPwdTypeComboBox
            // 
            this.userPwdTypeComboBox.FormattingEnabled = true;
            this.userPwdTypeComboBox.Location = new System.Drawing.Point(99, 120);
            this.userPwdTypeComboBox.Name = "userPwdTypeComboBox";
            this.userPwdTypeComboBox.Size = new System.Drawing.Size(223, 21);
            this.userPwdTypeComboBox.TabIndex = 143;
            this.userPwdTypeComboBox.SelectedIndexChanged += new System.EventHandler(this.userPwdTypeComboBox_SelectedIndexChanged);
            // 
            // usrEduPage
            // 
            this.usrEduPage.Controls.Add(usrEducationLabel);
            this.usrEduPage.Controls.Add(this.userNeedStudyCheckBox);
            this.usrEduPage.Controls.Add(this.userRandomEduCategCheckBox);
            this.usrEduPage.ImageIndex = 5;
            this.usrEduPage.Location = new System.Drawing.Point(4, 23);
            this.usrEduPage.Name = "usrEduPage";
            this.usrEduPage.Padding = new System.Windows.Forms.Padding(3);
            this.usrEduPage.Size = new System.Drawing.Size(716, 536);
            this.usrEduPage.TabIndex = 4;
            this.usrEduPage.Text = "Education";
            this.usrEduPage.UseVisualStyleBackColor = true;
            // 
            // userNeedStudyCheckBox
            // 
            this.userNeedStudyCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userNeedStudyCheckBox.Location = new System.Drawing.Point(61, 74);
            this.userNeedStudyCheckBox.Name = "userNeedStudyCheckBox";
            this.userNeedStudyCheckBox.Size = new System.Drawing.Size(235, 24);
            this.userNeedStudyCheckBox.TabIndex = 118;
            this.userNeedStudyCheckBox.Text = "This user participates in a education program";
            this.userNeedStudyCheckBox.UseVisualStyleBackColor = true;
            this.userNeedStudyCheckBox.Enter += new System.EventHandler(this.userNamesDataGridView_Enter);
            // 
            // userRandomEduCategCheckBox
            // 
            this.userRandomEduCategCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userRandomEduCategCheckBox.Location = new System.Drawing.Point(61, 103);
            this.userRandomEduCategCheckBox.Name = "userRandomEduCategCheckBox";
            this.userRandomEduCategCheckBox.Size = new System.Drawing.Size(232, 24);
            this.userRandomEduCategCheckBox.TabIndex = 119;
            this.userRandomEduCategCheckBox.Text = "Subject lessons is chosen at random";
            this.userRandomEduCategCheckBox.UseVisualStyleBackColor = true;
            this.userRandomEduCategCheckBox.Enter += new System.EventHandler(this.userNamesDataGridView_Enter);
            // 
            // usrAccountsPage
            // 
            this.usrAccountsPage.Controls.Add(this.userAccountsDataGridView);
            this.usrAccountsPage.Controls.Add(this.usrAccListTitlePanel);
            this.usrAccountsPage.ImageIndex = 0;
            this.usrAccountsPage.Location = new System.Drawing.Point(4, 23);
            this.usrAccountsPage.Name = "usrAccountsPage";
            this.usrAccountsPage.Padding = new System.Windows.Forms.Padding(3);
            this.usrAccountsPage.Size = new System.Drawing.Size(716, 536);
            this.usrAccountsPage.TabIndex = 5;
            this.usrAccountsPage.Text = "User accounts";
            this.usrAccountsPage.UseVisualStyleBackColor = true;
            // 
            // userAccountsDataGridView
            // 
            this.userAccountsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.userAccountsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.authSystemTypeNameColumn,
            this.accountUserNameColumn,
            this.accountPasswordColumn,
            this.passThruColumn,
            this.lastSignInDateColumn});
            this.userAccountsDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userAccountsDataGridView.Location = new System.Drawing.Point(3, 79);
            this.userAccountsDataGridView.Name = "userAccountsDataGridView";
            this.userAccountsDataGridView.Size = new System.Drawing.Size(710, 454);
            this.userAccountsDataGridView.TabIndex = 5;
            this.userAccountsDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.userAccountsDataGridView_CellFormatting);
            this.userAccountsDataGridView.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.userAccountsDataGridView_CellParsing);
            this.userAccountsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.userAccountsDataGridView.Enter += new System.EventHandler(this.userAccountsDataGridView_Enter);
            // 
            // authSystemTypeNameColumn
            // 
            this.authSystemTypeNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.authSystemTypeNameColumn.HeaderText = "System";
            this.authSystemTypeNameColumn.Name = "authSystemTypeNameColumn";
            this.authSystemTypeNameColumn.Width = 200;
            // 
            // accountUserNameColumn
            // 
            this.accountUserNameColumn.HeaderText = "User name";
            this.accountUserNameColumn.Name = "accountUserNameColumn";
            this.accountUserNameColumn.Width = 200;
            // 
            // accountPasswordColumn
            // 
            this.accountPasswordColumn.HeaderText = "Password";
            this.accountPasswordColumn.Name = "accountPasswordColumn";
            this.accountPasswordColumn.ReadOnly = true;
            this.accountPasswordColumn.Width = 200;
            // 
            // passThruColumn
            // 
            this.passThruColumn.HeaderText = "Pass password through";
            this.passThruColumn.Name = "passThruColumn";
            this.passThruColumn.Width = 150;
            // 
            // lastSignInDateColumn
            // 
            this.lastSignInDateColumn.HeaderText = "Date of last logon";
            this.lastSignInDateColumn.Name = "lastSignInDateColumn";
            this.lastSignInDateColumn.Width = 200;
            // 
            // usrAccListTitlePanel
            // 
            this.usrAccListTitlePanel.Controls.Add(this.userAccountGroupsButton);
            this.usrAccListTitlePanel.Controls.Add(this.userAccountsArchiveButton);
            this.usrAccListTitlePanel.Controls.Add(this.changeUserAccountButton);
            this.usrAccListTitlePanel.Controls.Add(usrAccListTitleLabel);
            this.usrAccListTitlePanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.usrAccListTitlePanel.Location = new System.Drawing.Point(3, 3);
            this.usrAccListTitlePanel.Name = "usrAccListTitlePanel";
            this.usrAccListTitlePanel.Size = new System.Drawing.Size(710, 76);
            this.usrAccListTitlePanel.TabIndex = 6;
            // 
            // userAccountGroupsButton
            // 
            this.userAccountGroupsButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userAccountGroupsButton.Image = ((System.Drawing.Image)(resources.GetObject("userAccountGroupsButton.Image")));
            this.userAccountGroupsButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.userAccountGroupsButton.Location = new System.Drawing.Point(384, 10);
            this.userAccountGroupsButton.Name = "userAccountGroupsButton";
            this.userAccountGroupsButton.Size = new System.Drawing.Size(180, 25);
            this.userAccountGroupsButton.TabIndex = 149;
            this.userAccountGroupsButton.Text = "User account groups";
            this.userAccountGroupsButton.UseVisualStyleBackColor = true;
            this.userAccountGroupsButton.Click += new System.EventHandler(this.usersBindingNavigatorGroupsItem_Click);
            // 
            // userAccountsArchiveButton
            // 
            this.userAccountsArchiveButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userAccountsArchiveButton.Image = ((System.Drawing.Image)(resources.GetObject("userAccountsArchiveButton.Image")));
            this.userAccountsArchiveButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.userAccountsArchiveButton.Location = new System.Drawing.Point(198, 10);
            this.userAccountsArchiveButton.Name = "userAccountsArchiveButton";
            this.userAccountsArchiveButton.Size = new System.Drawing.Size(180, 25);
            this.userAccountsArchiveButton.TabIndex = 148;
            this.userAccountsArchiveButton.Text = "User accounts archive";
            this.userAccountsArchiveButton.UseVisualStyleBackColor = true;
            this.userAccountsArchiveButton.Click += new System.EventHandler(this.usersBindingNavigatorArchiveItem_Click);
            // 
            // changeUserAccountButton
            // 
            this.changeUserAccountButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.changeUserAccountButton.Image = ((System.Drawing.Image)(resources.GetObject("changeUserAccountButton.Image")));
            this.changeUserAccountButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.changeUserAccountButton.Location = new System.Drawing.Point(12, 10);
            this.changeUserAccountButton.Name = "changeUserAccountButton";
            this.changeUserAccountButton.Size = new System.Drawing.Size(180, 25);
            this.changeUserAccountButton.TabIndex = 147;
            this.changeUserAccountButton.Text = "Change password";
            this.changeUserAccountButton.UseVisualStyleBackColor = true;
            this.changeUserAccountButton.Click += new System.EventHandler(this.usersBindingNavigatorChangeUsrAccountPasswordItem_Click);
            // 
            // usrCheckParamsPage
            // 
            this.usrCheckParamsPage.Controls.Add(this.userCheckValuesDataGridView);
            this.usrCheckParamsPage.Controls.Add(this.checkParamTitlePanel);
            this.usrCheckParamsPage.ImageIndex = 2;
            this.usrCheckParamsPage.Location = new System.Drawing.Point(4, 23);
            this.usrCheckParamsPage.Name = "usrCheckParamsPage";
            this.usrCheckParamsPage.Padding = new System.Windows.Forms.Padding(3);
            this.usrCheckParamsPage.Size = new System.Drawing.Size(716, 536);
            this.usrCheckParamsPage.TabIndex = 6;
            this.usrCheckParamsPage.Text = "Parameters for checking";
            this.usrCheckParamsPage.UseVisualStyleBackColor = true;
            // 
            // userCheckValuesDataGridView
            // 
            this.userCheckValuesDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.userCheckValuesDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.userCheckValueObjectIDColumn,
            this.userCheckValueColumn});
            this.userCheckValuesDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userCheckValuesDataGridView.Location = new System.Drawing.Point(3, 42);
            this.userCheckValuesDataGridView.Name = "userCheckValuesDataGridView";
            this.userCheckValuesDataGridView.Size = new System.Drawing.Size(710, 491);
            this.userCheckValuesDataGridView.TabIndex = 1;
            this.userCheckValuesDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.userCheckValuesDataGridView_CellFormatting);
            this.userCheckValuesDataGridView.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.userCheckValuesDataGridView_CellParsing);
            this.userCheckValuesDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.userCheckValuesDataGridView.Enter += new System.EventHandler(this.userCheckValuesDataGridView_Enter);
            // 
            // userCheckValueObjectIDColumn
            // 
            this.userCheckValueObjectIDColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userCheckValueObjectIDColumn.HeaderText = "Parameter for checking";
            this.userCheckValueObjectIDColumn.Name = "userCheckValueObjectIDColumn";
            this.userCheckValueObjectIDColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.userCheckValueObjectIDColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.userCheckValueObjectIDColumn.Width = 250;
            // 
            // userCheckValueColumn
            // 
            this.userCheckValueColumn.HeaderText = "Value";
            this.userCheckValueColumn.Name = "userCheckValueColumn";
            this.userCheckValueColumn.Width = 250;
            // 
            // checkParamTitlePanel
            // 
            this.checkParamTitlePanel.Controls.Add(checkParamTitleLabel);
            this.checkParamTitlePanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.checkParamTitlePanel.Location = new System.Drawing.Point(3, 3);
            this.checkParamTitlePanel.Name = "checkParamTitlePanel";
            this.checkParamTitlePanel.Size = new System.Drawing.Size(710, 39);
            this.checkParamTitlePanel.TabIndex = 2;
            // 
            // usersInfoImageList
            // 
            this.usersInfoImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("usersInfoImageList.ImageStream")));
            this.usersInfoImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.usersInfoImageList.Images.SetKeyName(0, "id_cards.png");
            this.usersInfoImageList.Images.SetKeyName(1, "user1_information.png");
            this.usersInfoImageList.Images.SetKeyName(2, "user1_preferences.png");
            this.usersInfoImageList.Images.SetKeyName(3, "flag.png");
            this.usersInfoImageList.Images.SetKeyName(4, "key1.png");
            this.usersInfoImageList.Images.SetKeyName(5, "book_blue.png");
            this.usersInfoImageList.Images.SetKeyName(6, "users2.png");
            // 
            // userNamesDataGridView
            // 
            this.userNamesDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.userNamesDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.userNameColumn});
            this.userNamesDataGridView.Dock = System.Windows.Forms.DockStyle.Left;
            this.userNamesDataGridView.Location = new System.Drawing.Point(3, 28);
            this.userNamesDataGridView.Name = "userNamesDataGridView";
            this.userNamesDataGridView.Size = new System.Drawing.Size(254, 563);
            this.userNamesDataGridView.TabIndex = 110;
            this.userNamesDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.userNamesDataGridView_CellFormatting);
            this.userNamesDataGridView.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.userNamesDataGridView_CellParsing);
            this.userNamesDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.userNamesDataGridView.Sorted += new System.EventHandler(this.userNamesDataGridView_Sorted);
            this.userNamesDataGridView.Enter += new System.EventHandler(this.userNamesDataGridView_Enter);
            // 
            // userNameColumn
            // 
            this.userNameColumn.HeaderText = "Name";
            this.userNameColumn.Name = "userNameColumn";
            this.userNameColumn.Width = 200;
            // 
            // usersBindingNavigator
            // 
            this.usersBindingNavigator.AddNewItem = this.bindingNavigatorAddNewItem;
            this.usersBindingNavigator.BackColor = System.Drawing.SystemColors.Control;
            this.usersBindingNavigator.CountItem = this.bindingNavigatorCountItem;
            this.usersBindingNavigator.DeleteItem = this.bindingNavigatorDeleteItem;
            this.usersBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.bindingNavigatorMoveFirstItem,
            this.bindingNavigatorMovePreviousItem,
            this.bindingNavigatorSeparator,
            this.bindingNavigatorPositionItem,
            this.bindingNavigatorCountItem,
            this.bindingNavigatorSeparator1,
            this.bindingNavigatorMoveNextItem,
            this.bindingNavigatorMoveLastItem,
            this.bindingNavigatorSeparator2,
            this.bindingNavigatorAddNewItem,
            this.bindingNavigatorDeleteItem,
            this.usersBindingNavigatorSaveItem,
            this.usersBindingNavigatorRefreshItem});
            this.usersBindingNavigator.Location = new System.Drawing.Point(3, 3);
            this.usersBindingNavigator.MoveFirstItem = this.bindingNavigatorMoveFirstItem;
            this.usersBindingNavigator.MoveLastItem = this.bindingNavigatorMoveLastItem;
            this.usersBindingNavigator.MoveNextItem = this.bindingNavigatorMoveNextItem;
            this.usersBindingNavigator.MovePreviousItem = this.bindingNavigatorMovePreviousItem;
            this.usersBindingNavigator.Name = "usersBindingNavigator";
            this.usersBindingNavigator.PositionItem = this.bindingNavigatorPositionItem;
            this.usersBindingNavigator.Size = new System.Drawing.Size(978, 25);
            this.usersBindingNavigator.TabIndex = 21;
            this.usersBindingNavigator.Text = "bindingNavigator1";
            // 
            // bindingNavigatorAddNewItem
            // 
            this.bindingNavigatorAddNewItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorAddNewItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorAddNewItem.Image")));
            this.bindingNavigatorAddNewItem.Name = "bindingNavigatorAddNewItem";
            this.bindingNavigatorAddNewItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorAddNewItem.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorAddNewItem.Text = "Add new";
            // 
            // bindingNavigatorCountItem
            // 
            this.bindingNavigatorCountItem.Name = "bindingNavigatorCountItem";
            this.bindingNavigatorCountItem.Size = new System.Drawing.Size(43, 22);
            this.bindingNavigatorCountItem.Text = "для {0}";
            this.bindingNavigatorCountItem.ToolTipText = "Total number of items";
            // 
            // bindingNavigatorDeleteItem
            // 
            this.bindingNavigatorDeleteItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorDeleteItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorDeleteItem.Image")));
            this.bindingNavigatorDeleteItem.Name = "bindingNavigatorDeleteItem";
            this.bindingNavigatorDeleteItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorDeleteItem.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorDeleteItem.Text = "Delete";
            // 
            // bindingNavigatorMoveFirstItem
            // 
            this.bindingNavigatorMoveFirstItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMoveFirstItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveFirstItem.Image")));
            this.bindingNavigatorMoveFirstItem.Name = "bindingNavigatorMoveFirstItem";
            this.bindingNavigatorMoveFirstItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMoveFirstItem.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorMoveFirstItem.Text = "Move first";
            // 
            // bindingNavigatorMovePreviousItem
            // 
            this.bindingNavigatorMovePreviousItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMovePreviousItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMovePreviousItem.Image")));
            this.bindingNavigatorMovePreviousItem.Name = "bindingNavigatorMovePreviousItem";
            this.bindingNavigatorMovePreviousItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMovePreviousItem.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorMovePreviousItem.Text = "Move previous";
            // 
            // bindingNavigatorSeparator
            // 
            this.bindingNavigatorSeparator.Name = "bindingNavigatorSeparator";
            this.bindingNavigatorSeparator.Size = new System.Drawing.Size(6, 25);
            // 
            // bindingNavigatorPositionItem
            // 
            this.bindingNavigatorPositionItem.AccessibleName = "Position";
            this.bindingNavigatorPositionItem.AutoSize = false;
            this.bindingNavigatorPositionItem.Name = "bindingNavigatorPositionItem";
            this.bindingNavigatorPositionItem.Size = new System.Drawing.Size(50, 23);
            this.bindingNavigatorPositionItem.Text = "0";
            this.bindingNavigatorPositionItem.ToolTipText = "Current position";
            // 
            // bindingNavigatorSeparator1
            // 
            this.bindingNavigatorSeparator1.Name = "bindingNavigatorSeparator1";
            this.bindingNavigatorSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // bindingNavigatorMoveNextItem
            // 
            this.bindingNavigatorMoveNextItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMoveNextItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveNextItem.Image")));
            this.bindingNavigatorMoveNextItem.Name = "bindingNavigatorMoveNextItem";
            this.bindingNavigatorMoveNextItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMoveNextItem.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorMoveNextItem.Text = "Move next";
            // 
            // bindingNavigatorMoveLastItem
            // 
            this.bindingNavigatorMoveLastItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMoveLastItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveLastItem.Image")));
            this.bindingNavigatorMoveLastItem.Name = "bindingNavigatorMoveLastItem";
            this.bindingNavigatorMoveLastItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMoveLastItem.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorMoveLastItem.Text = "Move last";
            // 
            // bindingNavigatorSeparator2
            // 
            this.bindingNavigatorSeparator2.Name = "bindingNavigatorSeparator2";
            this.bindingNavigatorSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // usersBindingNavigatorSaveItem
            // 
            this.usersBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.usersBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("usersBindingNavigatorSaveItem.Image")));
            this.usersBindingNavigatorSaveItem.Name = "usersBindingNavigatorSaveItem";
            this.usersBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.usersBindingNavigatorSaveItem.Text = "Save Data";
            this.usersBindingNavigatorSaveItem.Click += new System.EventHandler(this.usersBindingNavigatorSaveItem_Click);
            // 
            // usersBindingNavigatorRefreshItem
            // 
            this.usersBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.usersBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("usersBindingNavigatorRefreshItem.Image")));
            this.usersBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.usersBindingNavigatorRefreshItem.Name = "usersBindingNavigatorRefreshItem";
            this.usersBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.usersBindingNavigatorRefreshItem.Text = "Refresh";
            this.usersBindingNavigatorRefreshItem.Click += new System.EventHandler(this.usersBindingNavigatorRefreshItem_Click);
            // 
            // userGroupsPage
            // 
            this.userGroupsPage.BackColor = System.Drawing.SystemColors.Control;
            this.userGroupsPage.Controls.Add(this.groupDetailsPanel);
            this.userGroupsPage.Controls.Add(this.splitter26);
            this.userGroupsPage.Controls.Add(this.groupListGroupBox);
            this.userGroupsPage.Controls.Add(this.groupsBindingNavigator);
            this.userGroupsPage.ImageIndex = 1;
            this.userGroupsPage.Location = new System.Drawing.Point(4, 31);
            this.userGroupsPage.Name = "userGroupsPage";
            this.userGroupsPage.Padding = new System.Windows.Forms.Padding(3);
            this.userGroupsPage.Size = new System.Drawing.Size(984, 594);
            this.userGroupsPage.TabIndex = 3;
            this.userGroupsPage.Text = "User groups";
            // 
            // groupDetailsPanel
            // 
            this.groupDetailsPanel.Controls.Add(this.groupUsersGroupBox);
            this.groupDetailsPanel.Controls.Add(this.splitter30);
            this.groupDetailsPanel.Controls.Add(this.groupAuthSystemsGroupBox);
            this.groupDetailsPanel.Controls.Add(this.splitter27);
            this.groupDetailsPanel.Controls.Add(this.groupPermissionsGroupBox);
            this.groupDetailsPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupDetailsPanel.Location = new System.Drawing.Point(521, 28);
            this.groupDetailsPanel.Name = "groupDetailsPanel";
            this.groupDetailsPanel.Size = new System.Drawing.Size(460, 563);
            this.groupDetailsPanel.TabIndex = 25;
            // 
            // groupUsersGroupBox
            // 
            this.groupUsersGroupBox.Controls.Add(this.usersGroupDataGridView);
            this.groupUsersGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupUsersGroupBox.Location = new System.Drawing.Point(0, 380);
            this.groupUsersGroupBox.Name = "groupUsersGroupBox";
            this.groupUsersGroupBox.Size = new System.Drawing.Size(460, 183);
            this.groupUsersGroupBox.TabIndex = 5;
            this.groupUsersGroupBox.TabStop = false;
            this.groupUsersGroupBox.Text = "Users of group";
            // 
            // usersGroupDataGridView
            // 
            this.usersGroupDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.usersGroupDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.groupUserNameColumn,
            this.groupUserIDColumn});
            this.usersGroupDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.usersGroupDataGridView.Location = new System.Drawing.Point(3, 16);
            this.usersGroupDataGridView.Name = "usersGroupDataGridView";
            this.usersGroupDataGridView.Size = new System.Drawing.Size(454, 164);
            this.usersGroupDataGridView.TabIndex = 0;
            this.usersGroupDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.usersGroupDataGridView_CellFormatting);
            this.usersGroupDataGridView.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.usersGroupDataGridView_CellValueChanged);
            this.usersGroupDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.usersGroupDataGridView.Enter += new System.EventHandler(this.usersGroupDataGridView_Enter);
            // 
            // groupUserNameColumn
            // 
            this.groupUserNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.groupUserNameColumn.HeaderText = "User name";
            this.groupUserNameColumn.Name = "groupUserNameColumn";
            this.groupUserNameColumn.Width = 250;
            // 
            // groupUserIDColumn
            // 
            this.groupUserIDColumn.HeaderText = "User ID";
            this.groupUserIDColumn.Name = "groupUserIDColumn";
            this.groupUserIDColumn.Visible = false;
            // 
            // splitter30
            // 
            this.splitter30.Dock = System.Windows.Forms.DockStyle.Top;
            this.splitter30.Location = new System.Drawing.Point(0, 377);
            this.splitter30.Name = "splitter30";
            this.splitter30.Size = new System.Drawing.Size(460, 3);
            this.splitter30.TabIndex = 4;
            this.splitter30.TabStop = false;
            // 
            // groupAuthSystemsGroupBox
            // 
            this.groupAuthSystemsGroupBox.Controls.Add(this.groupGroupAuthSystemsDataGridView);
            this.groupAuthSystemsGroupBox.Controls.Add(this.groupReferencesPanel);
            this.groupAuthSystemsGroupBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupAuthSystemsGroupBox.Location = new System.Drawing.Point(0, 170);
            this.groupAuthSystemsGroupBox.Name = "groupAuthSystemsGroupBox";
            this.groupAuthSystemsGroupBox.Size = new System.Drawing.Size(460, 207);
            this.groupAuthSystemsGroupBox.TabIndex = 3;
            this.groupAuthSystemsGroupBox.TabStop = false;
            this.groupAuthSystemsGroupBox.Text = "Group references";
            // 
            // groupGroupAuthSystemsDataGridView
            // 
            this.groupGroupAuthSystemsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.groupGroupAuthSystemsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.groupAuthSystemColumn,
            this.authGroupNameColumn});
            this.groupGroupAuthSystemsDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupGroupAuthSystemsDataGridView.Location = new System.Drawing.Point(3, 51);
            this.groupGroupAuthSystemsDataGridView.Name = "groupGroupAuthSystemsDataGridView";
            this.groupGroupAuthSystemsDataGridView.Size = new System.Drawing.Size(454, 153);
            this.groupGroupAuthSystemsDataGridView.TabIndex = 0;
            this.groupGroupAuthSystemsDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.groupGroupAuthSystemsDataGridView_CellFormatting);
            this.groupGroupAuthSystemsDataGridView.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.groupGroupAuthSystemsDataGridView_CellParsing);
            this.groupGroupAuthSystemsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.groupGroupAuthSystemsDataGridView.Enter += new System.EventHandler(this.groupGroupAuthSystemsDataGridView_Enter);
            // 
            // groupAuthSystemColumn
            // 
            this.groupAuthSystemColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.groupAuthSystemColumn.HeaderText = "Authentication system";
            this.groupAuthSystemColumn.Name = "groupAuthSystemColumn";
            this.groupAuthSystemColumn.Width = 200;
            // 
            // authGroupNameColumn
            // 
            this.authGroupNameColumn.HeaderText = "Group name";
            this.authGroupNameColumn.Name = "authGroupNameColumn";
            this.authGroupNameColumn.Width = 200;
            // 
            // groupReferencesPanel
            // 
            this.groupReferencesPanel.Controls.Add(this.groupUsersButton);
            this.groupReferencesPanel.Controls.Add(this.userGroupSettingsButton);
            this.groupReferencesPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupReferencesPanel.Location = new System.Drawing.Point(3, 16);
            this.groupReferencesPanel.Name = "groupReferencesPanel";
            this.groupReferencesPanel.Size = new System.Drawing.Size(454, 35);
            this.groupReferencesPanel.TabIndex = 1;
            // 
            // groupUsersButton
            // 
            this.groupUsersButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.groupUsersButton.Image = ((System.Drawing.Image)(resources.GetObject("groupUsersButton.Image")));
            this.groupUsersButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.groupUsersButton.Location = new System.Drawing.Point(197, 6);
            this.groupUsersButton.Name = "groupUsersButton";
            this.groupUsersButton.Size = new System.Drawing.Size(179, 23);
            this.groupUsersButton.TabIndex = 1;
            this.groupUsersButton.Text = "Users of the group";
            this.groupUsersButton.UseVisualStyleBackColor = true;
            this.groupUsersButton.Click += new System.EventHandler(this.groupUsersButton_Click);
            // 
            // userGroupSettingsButton
            // 
            this.userGroupSettingsButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userGroupSettingsButton.Image = ((System.Drawing.Image)(resources.GetObject("userGroupSettingsButton.Image")));
            this.userGroupSettingsButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.userGroupSettingsButton.Location = new System.Drawing.Point(12, 6);
            this.userGroupSettingsButton.Name = "userGroupSettingsButton";
            this.userGroupSettingsButton.Size = new System.Drawing.Size(179, 23);
            this.userGroupSettingsButton.TabIndex = 0;
            this.userGroupSettingsButton.Text = "Additional settings";
            this.userGroupSettingsButton.UseVisualStyleBackColor = true;
            this.userGroupSettingsButton.Click += new System.EventHandler(this.userGroupSettingsButton_Click);
            // 
            // splitter27
            // 
            this.splitter27.Dock = System.Windows.Forms.DockStyle.Top;
            this.splitter27.Location = new System.Drawing.Point(0, 167);
            this.splitter27.Name = "splitter27";
            this.splitter27.Size = new System.Drawing.Size(460, 3);
            this.splitter27.TabIndex = 2;
            this.splitter27.TabStop = false;
            // 
            // groupPermissionsGroupBox
            // 
            this.groupPermissionsGroupBox.Controls.Add(this.groupPermissionsDataGridView);
            this.groupPermissionsGroupBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupPermissionsGroupBox.Location = new System.Drawing.Point(0, 0);
            this.groupPermissionsGroupBox.Name = "groupPermissionsGroupBox";
            this.groupPermissionsGroupBox.Size = new System.Drawing.Size(460, 167);
            this.groupPermissionsGroupBox.TabIndex = 1;
            this.groupPermissionsGroupBox.TabStop = false;
            this.groupPermissionsGroupBox.Text = "Group permissions";
            // 
            // groupPermissionsDataGridView
            // 
            this.groupPermissionsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.groupPermissionsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.groupPermissionsColumn,
            this.groupPermissionIDColumn});
            this.groupPermissionsDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupPermissionsDataGridView.Location = new System.Drawing.Point(3, 16);
            this.groupPermissionsDataGridView.Name = "groupPermissionsDataGridView";
            this.groupPermissionsDataGridView.Size = new System.Drawing.Size(454, 148);
            this.groupPermissionsDataGridView.TabIndex = 0;
            this.groupPermissionsDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.groupPermissionsDataGridView_CellFormatting);
            this.groupPermissionsDataGridView.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.groupPermissionsDataGridView_CellValueChanged);
            this.groupPermissionsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.groupPermissionsDataGridView.Enter += new System.EventHandler(this.groupPermissionsDataGridView_Enter);
            // 
            // groupPermissionsColumn
            // 
            this.groupPermissionsColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.groupPermissionsColumn.HeaderText = "Permissions";
            this.groupPermissionsColumn.Name = "groupPermissionsColumn";
            this.groupPermissionsColumn.Width = 250;
            // 
            // groupPermissionIDColumn
            // 
            this.groupPermissionIDColumn.HeaderText = "Permission ID";
            this.groupPermissionIDColumn.Name = "groupPermissionIDColumn";
            this.groupPermissionIDColumn.Visible = false;
            // 
            // splitter26
            // 
            this.splitter26.Location = new System.Drawing.Point(518, 28);
            this.splitter26.Name = "splitter26";
            this.splitter26.Size = new System.Drawing.Size(3, 563);
            this.splitter26.TabIndex = 27;
            this.splitter26.TabStop = false;
            // 
            // groupListGroupBox
            // 
            this.groupListGroupBox.Controls.Add(this.groupsDataGridView);
            this.groupListGroupBox.Dock = System.Windows.Forms.DockStyle.Left;
            this.groupListGroupBox.Location = new System.Drawing.Point(3, 28);
            this.groupListGroupBox.Name = "groupListGroupBox";
            this.groupListGroupBox.Size = new System.Drawing.Size(515, 563);
            this.groupListGroupBox.TabIndex = 26;
            this.groupListGroupBox.TabStop = false;
            this.groupListGroupBox.Text = "User groups";
            // 
            // groupsDataGridView
            // 
            this.groupsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.groupsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.groupNameColumn,
            this.groupDescriptionColumn});
            this.groupsDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupsDataGridView.Location = new System.Drawing.Point(3, 16);
            this.groupsDataGridView.Name = "groupsDataGridView";
            this.groupsDataGridView.Size = new System.Drawing.Size(509, 544);
            this.groupsDataGridView.TabIndex = 23;
            this.groupsDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.groupsDataGridView_CellFormatting);
            this.groupsDataGridView.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.groupsDataGridView_CellParsing);
            this.groupsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.groupsDataGridView.Enter += new System.EventHandler(this.groupsDataGridView_Enter);
            // 
            // groupNameColumn
            // 
            this.groupNameColumn.HeaderText = "Group name";
            this.groupNameColumn.Name = "groupNameColumn";
            this.groupNameColumn.Width = 150;
            // 
            // groupDescriptionColumn
            // 
            this.groupDescriptionColumn.HeaderText = "Description";
            this.groupDescriptionColumn.Name = "groupDescriptionColumn";
            this.groupDescriptionColumn.Width = 300;
            // 
            // groupsBindingNavigator
            // 
            this.groupsBindingNavigator.AddNewItem = this.toolStripButton65;
            this.groupsBindingNavigator.BackColor = System.Drawing.SystemColors.Control;
            this.groupsBindingNavigator.CountItem = this.toolStripLabel13;
            this.groupsBindingNavigator.DeleteItem = this.toolStripButton67;
            this.groupsBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton68,
            this.toolStripButton69,
            this.toolStripSeparator38,
            this.toolStripTextBox13,
            this.toolStripLabel13,
            this.toolStripSeparator39,
            this.toolStripButton70,
            this.toolStripButton71,
            this.toolStripSeparator43,
            this.toolStripButton65,
            this.toolStripButton67,
            this.groupsBindingNavigatorSaveItem,
            this.groupsBindingNavigatorRefreshItem});
            this.groupsBindingNavigator.Location = new System.Drawing.Point(3, 3);
            this.groupsBindingNavigator.MoveFirstItem = this.toolStripButton68;
            this.groupsBindingNavigator.MoveLastItem = this.toolStripButton71;
            this.groupsBindingNavigator.MoveNextItem = this.toolStripButton70;
            this.groupsBindingNavigator.MovePreviousItem = this.toolStripButton69;
            this.groupsBindingNavigator.Name = "groupsBindingNavigator";
            this.groupsBindingNavigator.PositionItem = this.toolStripTextBox13;
            this.groupsBindingNavigator.Size = new System.Drawing.Size(978, 25);
            this.groupsBindingNavigator.TabIndex = 22;
            this.groupsBindingNavigator.Text = "bindingNavigator1";
            // 
            // toolStripButton65
            // 
            this.toolStripButton65.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton65.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton65.Image")));
            this.toolStripButton65.Name = "toolStripButton65";
            this.toolStripButton65.RightToLeftAutoMirrorImage = true;
            this.toolStripButton65.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton65.Text = "Add new";
            // 
            // toolStripLabel13
            // 
            this.toolStripLabel13.Name = "toolStripLabel13";
            this.toolStripLabel13.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel13.Text = "для {0}";
            this.toolStripLabel13.ToolTipText = "Total number of items";
            // 
            // toolStripButton67
            // 
            this.toolStripButton67.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton67.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton67.Image")));
            this.toolStripButton67.Name = "toolStripButton67";
            this.toolStripButton67.RightToLeftAutoMirrorImage = true;
            this.toolStripButton67.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton67.Text = "Delete";
            // 
            // toolStripButton68
            // 
            this.toolStripButton68.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton68.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton68.Image")));
            this.toolStripButton68.Name = "toolStripButton68";
            this.toolStripButton68.RightToLeftAutoMirrorImage = true;
            this.toolStripButton68.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton68.Text = "Move first";
            // 
            // toolStripButton69
            // 
            this.toolStripButton69.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton69.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton69.Image")));
            this.toolStripButton69.Name = "toolStripButton69";
            this.toolStripButton69.RightToLeftAutoMirrorImage = true;
            this.toolStripButton69.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton69.Text = "Move previous";
            // 
            // toolStripSeparator38
            // 
            this.toolStripSeparator38.Name = "toolStripSeparator38";
            this.toolStripSeparator38.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox13
            // 
            this.toolStripTextBox13.AccessibleName = "Position";
            this.toolStripTextBox13.AutoSize = false;
            this.toolStripTextBox13.Name = "toolStripTextBox13";
            this.toolStripTextBox13.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox13.Text = "0";
            this.toolStripTextBox13.ToolTipText = "Current position";
            // 
            // toolStripSeparator39
            // 
            this.toolStripSeparator39.Name = "toolStripSeparator39";
            this.toolStripSeparator39.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton70
            // 
            this.toolStripButton70.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton70.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton70.Image")));
            this.toolStripButton70.Name = "toolStripButton70";
            this.toolStripButton70.RightToLeftAutoMirrorImage = true;
            this.toolStripButton70.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton70.Text = "Move next";
            // 
            // toolStripButton71
            // 
            this.toolStripButton71.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton71.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton71.Image")));
            this.toolStripButton71.Name = "toolStripButton71";
            this.toolStripButton71.RightToLeftAutoMirrorImage = true;
            this.toolStripButton71.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton71.Text = "Move last";
            // 
            // toolStripSeparator43
            // 
            this.toolStripSeparator43.Name = "toolStripSeparator43";
            this.toolStripSeparator43.Size = new System.Drawing.Size(6, 25);
            // 
            // groupsBindingNavigatorSaveItem
            // 
            this.groupsBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.groupsBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("groupsBindingNavigatorSaveItem.Image")));
            this.groupsBindingNavigatorSaveItem.Name = "groupsBindingNavigatorSaveItem";
            this.groupsBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.groupsBindingNavigatorSaveItem.Text = "Save Data";
            this.groupsBindingNavigatorSaveItem.Click += new System.EventHandler(this.groupsBindingNavigatorSaveItem_Click);
            // 
            // groupsBindingNavigatorRefreshItem
            // 
            this.groupsBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.groupsBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("groupsBindingNavigatorRefreshItem.Image")));
            this.groupsBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.groupsBindingNavigatorRefreshItem.Name = "groupsBindingNavigatorRefreshItem";
            this.groupsBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.groupsBindingNavigatorRefreshItem.Text = "Refresh";
            this.groupsBindingNavigatorRefreshItem.Click += new System.EventHandler(this.groupsBindingNavigatorRefreshItem_Click);
            // 
            // computersPage
            // 
            this.computersPage.Controls.Add(this.computersDataGridView);
            this.computersPage.Controls.Add(this.computersBindingNavigator);
            this.computersPage.ImageIndex = 2;
            this.computersPage.Location = new System.Drawing.Point(4, 31);
            this.computersPage.Name = "computersPage";
            this.computersPage.Padding = new System.Windows.Forms.Padding(3);
            this.computersPage.Size = new System.Drawing.Size(984, 594);
            this.computersPage.TabIndex = 2;
            this.computersPage.Text = "Computers";
            this.computersPage.UseVisualStyleBackColor = true;
            // 
            // computersDataGridView
            // 
            this.computersDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.computersDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.computerNameColumn,
            this.computerDescriptionColumn});
            this.computersDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.computersDataGridView.Location = new System.Drawing.Point(3, 28);
            this.computersDataGridView.Name = "computersDataGridView";
            this.computersDataGridView.Size = new System.Drawing.Size(978, 563);
            this.computersDataGridView.TabIndex = 32;
            // 
            // computerNameColumn
            // 
            this.computerNameColumn.HeaderText = "Computer name";
            this.computerNameColumn.Name = "computerNameColumn";
            this.computerNameColumn.Width = 250;
            // 
            // computerDescriptionColumn
            // 
            this.computerDescriptionColumn.HeaderText = "Description";
            this.computerDescriptionColumn.Name = "computerDescriptionColumn";
            this.computerDescriptionColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.computerDescriptionColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.computerDescriptionColumn.Width = 400;
            // 
            // computersBindingNavigator
            // 
            this.computersBindingNavigator.AddNewItem = this.bindingNavigatorAddNewItem1;
            this.computersBindingNavigator.CountItem = this.bindingNavigatorCountItem1;
            this.computersBindingNavigator.DeleteItem = this.bindingNavigatorDeleteItem1;
            this.computersBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.bindingNavigatorMoveFirstItem1,
            this.bindingNavigatorMovePreviousItem1,
            this.bindingNavigatorSeparator3,
            this.bindingNavigatorPositionItem1,
            this.bindingNavigatorCountItem1,
            this.bindingNavigatorSeparator4,
            this.bindingNavigatorMoveNextItem1,
            this.bindingNavigatorMoveLastItem1,
            this.bindingNavigatorSeparator5,
            this.bindingNavigatorAddNewItem1,
            this.bindingNavigatorDeleteItem1,
            this.computersBindingNavigatorSaveItem,
            this.computersBindingNavigatorRefreshItem});
            this.computersBindingNavigator.Location = new System.Drawing.Point(3, 3);
            this.computersBindingNavigator.MoveFirstItem = this.bindingNavigatorMoveFirstItem1;
            this.computersBindingNavigator.MoveLastItem = this.bindingNavigatorMoveLastItem1;
            this.computersBindingNavigator.MoveNextItem = this.bindingNavigatorMoveNextItem1;
            this.computersBindingNavigator.MovePreviousItem = this.bindingNavigatorMovePreviousItem1;
            this.computersBindingNavigator.Name = "computersBindingNavigator";
            this.computersBindingNavigator.PositionItem = this.bindingNavigatorPositionItem1;
            this.computersBindingNavigator.Size = new System.Drawing.Size(978, 25);
            this.computersBindingNavigator.TabIndex = 31;
            // 
            // bindingNavigatorAddNewItem1
            // 
            this.bindingNavigatorAddNewItem1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorAddNewItem1.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorAddNewItem1.Image")));
            this.bindingNavigatorAddNewItem1.Name = "bindingNavigatorAddNewItem1";
            this.bindingNavigatorAddNewItem1.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorAddNewItem1.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorAddNewItem1.Text = "Add new";
            // 
            // bindingNavigatorCountItem1
            // 
            this.bindingNavigatorCountItem1.Name = "bindingNavigatorCountItem1";
            this.bindingNavigatorCountItem1.Size = new System.Drawing.Size(43, 22);
            this.bindingNavigatorCountItem1.Text = "для {0}";
            this.bindingNavigatorCountItem1.ToolTipText = "Total number of items";
            // 
            // bindingNavigatorDeleteItem1
            // 
            this.bindingNavigatorDeleteItem1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorDeleteItem1.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorDeleteItem1.Image")));
            this.bindingNavigatorDeleteItem1.Name = "bindingNavigatorDeleteItem1";
            this.bindingNavigatorDeleteItem1.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorDeleteItem1.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorDeleteItem1.Text = "Delete";
            // 
            // bindingNavigatorMoveFirstItem1
            // 
            this.bindingNavigatorMoveFirstItem1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMoveFirstItem1.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveFirstItem1.Image")));
            this.bindingNavigatorMoveFirstItem1.Name = "bindingNavigatorMoveFirstItem1";
            this.bindingNavigatorMoveFirstItem1.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMoveFirstItem1.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorMoveFirstItem1.Text = "Move first";
            // 
            // bindingNavigatorMovePreviousItem1
            // 
            this.bindingNavigatorMovePreviousItem1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMovePreviousItem1.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMovePreviousItem1.Image")));
            this.bindingNavigatorMovePreviousItem1.Name = "bindingNavigatorMovePreviousItem1";
            this.bindingNavigatorMovePreviousItem1.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMovePreviousItem1.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorMovePreviousItem1.Text = "Move previous";
            // 
            // bindingNavigatorSeparator3
            // 
            this.bindingNavigatorSeparator3.Name = "bindingNavigatorSeparator3";
            this.bindingNavigatorSeparator3.Size = new System.Drawing.Size(6, 25);
            // 
            // bindingNavigatorPositionItem1
            // 
            this.bindingNavigatorPositionItem1.AccessibleName = "Position";
            this.bindingNavigatorPositionItem1.AutoSize = false;
            this.bindingNavigatorPositionItem1.Name = "bindingNavigatorPositionItem1";
            this.bindingNavigatorPositionItem1.Size = new System.Drawing.Size(50, 23);
            this.bindingNavigatorPositionItem1.Text = "0";
            this.bindingNavigatorPositionItem1.ToolTipText = "Current position";
            // 
            // bindingNavigatorSeparator4
            // 
            this.bindingNavigatorSeparator4.Name = "bindingNavigatorSeparator4";
            this.bindingNavigatorSeparator4.Size = new System.Drawing.Size(6, 25);
            // 
            // bindingNavigatorMoveNextItem1
            // 
            this.bindingNavigatorMoveNextItem1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMoveNextItem1.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveNextItem1.Image")));
            this.bindingNavigatorMoveNextItem1.Name = "bindingNavigatorMoveNextItem1";
            this.bindingNavigatorMoveNextItem1.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMoveNextItem1.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorMoveNextItem1.Text = "Move next";
            // 
            // bindingNavigatorMoveLastItem1
            // 
            this.bindingNavigatorMoveLastItem1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMoveLastItem1.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveLastItem1.Image")));
            this.bindingNavigatorMoveLastItem1.Name = "bindingNavigatorMoveLastItem1";
            this.bindingNavigatorMoveLastItem1.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMoveLastItem1.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorMoveLastItem1.Text = "Move last";
            // 
            // bindingNavigatorSeparator5
            // 
            this.bindingNavigatorSeparator5.Name = "bindingNavigatorSeparator5";
            this.bindingNavigatorSeparator5.Size = new System.Drawing.Size(6, 25);
            // 
            // computersBindingNavigatorSaveItem
            // 
            this.computersBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.computersBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("computersBindingNavigatorSaveItem.Image")));
            this.computersBindingNavigatorSaveItem.Name = "computersBindingNavigatorSaveItem";
            this.computersBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.computersBindingNavigatorSaveItem.Text = "Save Data";
            this.computersBindingNavigatorSaveItem.Click += new System.EventHandler(this.computersBindingNavigatorSaveItem_Click);
            // 
            // computersBindingNavigatorRefreshItem
            // 
            this.computersBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.computersBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("computersBindingNavigatorRefreshItem.Image")));
            this.computersBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.computersBindingNavigatorRefreshItem.Name = "computersBindingNavigatorRefreshItem";
            this.computersBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.computersBindingNavigatorRefreshItem.Text = "Refresh";
            this.computersBindingNavigatorRefreshItem.Click += new System.EventHandler(this.computersBindingNavigatorRefreshItem_Click);
            // 
            // authSystemsPage
            // 
            this.authSystemsPage.Controls.Add(this.authSystemsDataGridView);
            this.authSystemsPage.Controls.Add(this.authSystemsBindingNavigator);
            this.authSystemsPage.ImageIndex = 3;
            this.authSystemsPage.Location = new System.Drawing.Point(4, 31);
            this.authSystemsPage.Name = "authSystemsPage";
            this.authSystemsPage.Padding = new System.Windows.Forms.Padding(3);
            this.authSystemsPage.Size = new System.Drawing.Size(984, 594);
            this.authSystemsPage.TabIndex = 1;
            this.authSystemsPage.Text = "Authentication systems";
            this.authSystemsPage.UseVisualStyleBackColor = true;
            // 
            // authSystemsDataGridView
            // 
            this.authSystemsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.authSystemsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.authSystemTypeColumn,
            this.authSystemNameColumn,
            this.onDeleteActionColumn,
            this.onInsertActionColumn,
            this.onUpdateActionColumn,
            this.moveGroupUsersColumn});
            this.authSystemsDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.authSystemsDataGridView.Location = new System.Drawing.Point(3, 28);
            this.authSystemsDataGridView.Name = "authSystemsDataGridView";
            this.authSystemsDataGridView.Size = new System.Drawing.Size(978, 563);
            this.authSystemsDataGridView.TabIndex = 34;
            this.authSystemsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            // 
            // authSystemTypeColumn
            // 
            this.authSystemTypeColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.authSystemTypeColumn.HeaderText = "System type";
            this.authSystemTypeColumn.Name = "authSystemTypeColumn";
            this.authSystemTypeColumn.Width = 200;
            // 
            // authSystemNameColumn
            // 
            this.authSystemNameColumn.HeaderText = "System name";
            this.authSystemNameColumn.Name = "authSystemNameColumn";
            this.authSystemNameColumn.Width = 250;
            // 
            // onDeleteActionColumn
            // 
            this.onDeleteActionColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.onDeleteActionColumn.HeaderText = "On delete";
            this.onDeleteActionColumn.Name = "onDeleteActionColumn";
            this.onDeleteActionColumn.Width = 150;
            // 
            // onInsertActionColumn
            // 
            this.onInsertActionColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.onInsertActionColumn.HeaderText = "On insert";
            this.onInsertActionColumn.Name = "onInsertActionColumn";
            this.onInsertActionColumn.Width = 150;
            // 
            // onUpdateActionColumn
            // 
            this.onUpdateActionColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.onUpdateActionColumn.HeaderText = "On update";
            this.onUpdateActionColumn.Name = "onUpdateActionColumn";
            this.onUpdateActionColumn.Width = 150;
            // 
            // moveGroupUsersColumn
            // 
            this.moveGroupUsersColumn.FalseValue = "0";
            this.moveGroupUsersColumn.HeaderText = "Move users in groups";
            this.moveGroupUsersColumn.Name = "moveGroupUsersColumn";
            this.moveGroupUsersColumn.TrueValue = "1";
            this.moveGroupUsersColumn.Width = 150;
            // 
            // authSystemsBindingNavigator
            // 
            this.authSystemsBindingNavigator.AddNewItem = this.toolStripButton66;
            this.authSystemsBindingNavigator.CountItem = this.toolStripLabel14;
            this.authSystemsBindingNavigator.DeleteItem = this.toolStripButton73;
            this.authSystemsBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton74,
            this.toolStripButton75,
            this.toolStripSeparator40,
            this.toolStripTextBox14,
            this.toolStripLabel14,
            this.toolStripSeparator41,
            this.toolStripButton76,
            this.toolStripButton77,
            this.toolStripSeparator42,
            this.toolStripButton66,
            this.toolStripButton73,
            this.authSystemsBindingNavigatorSaveItem,
            this.authSystemsBindingNavigatorRefreshItem,
            this.toolStripSeparator56,
            this.authSystemsBindingNavigatorConfigureItem});
            this.authSystemsBindingNavigator.Location = new System.Drawing.Point(3, 3);
            this.authSystemsBindingNavigator.MoveFirstItem = this.toolStripButton74;
            this.authSystemsBindingNavigator.MoveLastItem = this.toolStripButton77;
            this.authSystemsBindingNavigator.MoveNextItem = this.toolStripButton76;
            this.authSystemsBindingNavigator.MovePreviousItem = this.toolStripButton75;
            this.authSystemsBindingNavigator.Name = "authSystemsBindingNavigator";
            this.authSystemsBindingNavigator.PositionItem = this.toolStripTextBox14;
            this.authSystemsBindingNavigator.Size = new System.Drawing.Size(978, 25);
            this.authSystemsBindingNavigator.TabIndex = 33;
            // 
            // toolStripButton66
            // 
            this.toolStripButton66.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton66.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton66.Image")));
            this.toolStripButton66.Name = "toolStripButton66";
            this.toolStripButton66.RightToLeftAutoMirrorImage = true;
            this.toolStripButton66.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton66.Text = "Add new";
            // 
            // toolStripLabel14
            // 
            this.toolStripLabel14.Name = "toolStripLabel14";
            this.toolStripLabel14.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel14.Text = "для {0}";
            this.toolStripLabel14.ToolTipText = "Total number of items";
            // 
            // toolStripButton73
            // 
            this.toolStripButton73.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton73.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton73.Image")));
            this.toolStripButton73.Name = "toolStripButton73";
            this.toolStripButton73.RightToLeftAutoMirrorImage = true;
            this.toolStripButton73.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton73.Text = "Delete";
            // 
            // toolStripButton74
            // 
            this.toolStripButton74.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton74.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton74.Image")));
            this.toolStripButton74.Name = "toolStripButton74";
            this.toolStripButton74.RightToLeftAutoMirrorImage = true;
            this.toolStripButton74.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton74.Text = "Move first";
            // 
            // toolStripButton75
            // 
            this.toolStripButton75.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton75.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton75.Image")));
            this.toolStripButton75.Name = "toolStripButton75";
            this.toolStripButton75.RightToLeftAutoMirrorImage = true;
            this.toolStripButton75.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton75.Text = "Move previous";
            // 
            // toolStripSeparator40
            // 
            this.toolStripSeparator40.Name = "toolStripSeparator40";
            this.toolStripSeparator40.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox14
            // 
            this.toolStripTextBox14.AccessibleName = "Position";
            this.toolStripTextBox14.AutoSize = false;
            this.toolStripTextBox14.Name = "toolStripTextBox14";
            this.toolStripTextBox14.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox14.Text = "0";
            this.toolStripTextBox14.ToolTipText = "Current position";
            // 
            // toolStripSeparator41
            // 
            this.toolStripSeparator41.Name = "toolStripSeparator41";
            this.toolStripSeparator41.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton76
            // 
            this.toolStripButton76.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton76.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton76.Image")));
            this.toolStripButton76.Name = "toolStripButton76";
            this.toolStripButton76.RightToLeftAutoMirrorImage = true;
            this.toolStripButton76.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton76.Text = "Move next";
            // 
            // toolStripButton77
            // 
            this.toolStripButton77.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton77.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton77.Image")));
            this.toolStripButton77.Name = "toolStripButton77";
            this.toolStripButton77.RightToLeftAutoMirrorImage = true;
            this.toolStripButton77.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton77.Text = "Move last";
            // 
            // toolStripSeparator42
            // 
            this.toolStripSeparator42.Name = "toolStripSeparator42";
            this.toolStripSeparator42.Size = new System.Drawing.Size(6, 25);
            // 
            // authSystemsBindingNavigatorSaveItem
            // 
            this.authSystemsBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.authSystemsBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("authSystemsBindingNavigatorSaveItem.Image")));
            this.authSystemsBindingNavigatorSaveItem.Name = "authSystemsBindingNavigatorSaveItem";
            this.authSystemsBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.authSystemsBindingNavigatorSaveItem.Text = "Save Data";
            this.authSystemsBindingNavigatorSaveItem.Click += new System.EventHandler(this.authSystemsBindingNavigatorSaveItem_Click);
            // 
            // authSystemsBindingNavigatorRefreshItem
            // 
            this.authSystemsBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.authSystemsBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("authSystemsBindingNavigatorRefreshItem.Image")));
            this.authSystemsBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.authSystemsBindingNavigatorRefreshItem.Name = "authSystemsBindingNavigatorRefreshItem";
            this.authSystemsBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.authSystemsBindingNavigatorRefreshItem.Text = "Refresh";
            this.authSystemsBindingNavigatorRefreshItem.Click += new System.EventHandler(this.authSystemsBindingNavigatorRefreshItem_Click);
            // 
            // toolStripSeparator56
            // 
            this.toolStripSeparator56.Name = "toolStripSeparator56";
            this.toolStripSeparator56.Size = new System.Drawing.Size(6, 25);
            // 
            // authSystemsBindingNavigatorConfigureItem
            // 
            this.authSystemsBindingNavigatorConfigureItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.authSystemsBindingNavigatorConfigureItem.Image = ((System.Drawing.Image)(resources.GetObject("authSystemsBindingNavigatorConfigureItem.Image")));
            this.authSystemsBindingNavigatorConfigureItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.authSystemsBindingNavigatorConfigureItem.Name = "authSystemsBindingNavigatorConfigureItem";
            this.authSystemsBindingNavigatorConfigureItem.Size = new System.Drawing.Size(23, 22);
            this.authSystemsBindingNavigatorConfigureItem.Text = "Configure current authentication system";
            this.authSystemsBindingNavigatorConfigureItem.Click += new System.EventHandler(this.btnSettingsString_Click);
            // 
            // usersTabImageList
            // 
            this.usersTabImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("usersTabImageList.ImageStream")));
            this.usersTabImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.usersTabImageList.Images.SetKeyName(0, "user.png");
            this.usersTabImageList.Images.SetKeyName(1, "users.png");
            this.usersTabImageList.Images.SetKeyName(2, "clients.png");
            this.usersTabImageList.Images.SetKeyName(3, "server_id_card.png");
            // 
            // presetTabPage
            // 
            this.presetTabPage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.presetTabPage.Controls.Add(this.presetSplitContainer);
            this.presetTabPage.ImageIndex = 1;
            this.presetTabPage.Location = new System.Drawing.Point(4, 42);
            this.presetTabPage.Name = "presetTabPage";
            this.presetTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.presetTabPage.Size = new System.Drawing.Size(1000, 637);
            this.presetTabPage.TabIndex = 1;
            this.presetTabPage.Text = "User screen design";
            this.presetTabPage.UseVisualStyleBackColor = true;
            // 
            // presetSplitContainer
            // 
            this.presetSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.presetSplitContainer.Location = new System.Drawing.Point(3, 3);
            this.presetSplitContainer.Name = "presetSplitContainer";
            // 
            // presetSplitContainer.Panel1
            // 
            this.presetSplitContainer.Panel1.Controls.Add(this.presetDetailsMainPanel);
            // 
            // presetSplitContainer.Panel2
            // 
            this.presetSplitContainer.Panel2.Controls.Add(this.screenObjectsPanel);
            this.presetSplitContainer.Size = new System.Drawing.Size(992, 629);
            this.presetSplitContainer.SplitterDistance = 499;
            this.presetSplitContainer.TabIndex = 3;
            // 
            // presetDetailsMainPanel
            // 
            this.presetDetailsMainPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.presetDetailsMainPanel.Controls.Add(this.presetDetailsSubPanel);
            this.presetDetailsMainPanel.Controls.Add(this.presetBindingNavigator);
            this.presetDetailsMainPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.presetDetailsMainPanel.Location = new System.Drawing.Point(0, 0);
            this.presetDetailsMainPanel.Name = "presetDetailsMainPanel";
            this.presetDetailsMainPanel.Size = new System.Drawing.Size(499, 629);
            this.presetDetailsMainPanel.TabIndex = 0;
            // 
            // presetDetailsSubPanel
            // 
            this.presetDetailsSubPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.presetDetailsSubPanel.Controls.Add(this.presetScreenObjectsGroupBox);
            this.presetDetailsSubPanel.Controls.Add(this.splitter3);
            this.presetDetailsSubPanel.Controls.Add(this.presetScreensGroupBox);
            this.presetDetailsSubPanel.Controls.Add(this.splitter2);
            this.presetDetailsSubPanel.Controls.Add(this.presetNamesGroupBox);
            this.presetDetailsSubPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.presetDetailsSubPanel.Location = new System.Drawing.Point(0, 25);
            this.presetDetailsSubPanel.Name = "presetDetailsSubPanel";
            this.presetDetailsSubPanel.Size = new System.Drawing.Size(497, 602);
            this.presetDetailsSubPanel.TabIndex = 8;
            // 
            // presetScreenObjectsGroupBox
            // 
            this.presetScreenObjectsGroupBox.Controls.Add(this.presetScreenObjectsDataGridView);
            this.presetScreenObjectsGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.presetScreenObjectsGroupBox.Location = new System.Drawing.Point(0, 377);
            this.presetScreenObjectsGroupBox.Name = "presetScreenObjectsGroupBox";
            this.presetScreenObjectsGroupBox.Size = new System.Drawing.Size(495, 223);
            this.presetScreenObjectsGroupBox.TabIndex = 7;
            this.presetScreenObjectsGroupBox.TabStop = false;
            this.presetScreenObjectsGroupBox.Text = "Preset screen objects";
            // 
            // presetScreenObjectsDataGridView
            // 
            this.presetScreenObjectsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.presetScreenObjectsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.presetScreenObjectNameColumn,
            this.presetScreenObjectOrderColumn,
            this.presetScreenObjectScopeColumn});
            this.presetScreenObjectsDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.presetScreenObjectsDataGridView.Location = new System.Drawing.Point(3, 16);
            this.presetScreenObjectsDataGridView.Name = "presetScreenObjectsDataGridView";
            this.presetScreenObjectsDataGridView.Size = new System.Drawing.Size(489, 204);
            this.presetScreenObjectsDataGridView.TabIndex = 0;
            this.presetScreenObjectsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.presetScreenObjectsDataGridView.Enter += new System.EventHandler(this.presetScreenObjectsDataGridView_Enter);
            this.presetScreenObjectsDataGridView.Leave += new System.EventHandler(this.presetScreenObjectsDataGridView_Leave);
            // 
            // presetScreenObjectNameColumn
            // 
            this.presetScreenObjectNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.presetScreenObjectNameColumn.HeaderText = "Screen object name";
            this.presetScreenObjectNameColumn.Name = "presetScreenObjectNameColumn";
            this.presetScreenObjectNameColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.presetScreenObjectNameColumn.Width = 200;
            // 
            // presetScreenObjectOrderColumn
            // 
            this.presetScreenObjectOrderColumn.HeaderText = "Screen objects order";
            this.presetScreenObjectOrderColumn.Name = "presetScreenObjectOrderColumn";
            this.presetScreenObjectOrderColumn.Width = 150;
            // 
            // presetScreenObjectScopeColumn
            // 
            this.presetScreenObjectScopeColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.presetScreenObjectScopeColumn.HeaderText = "Scope";
            this.presetScreenObjectScopeColumn.Name = "presetScreenObjectScopeColumn";
            this.presetScreenObjectScopeColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.presetScreenObjectScopeColumn.Width = 150;
            // 
            // splitter3
            // 
            this.splitter3.Dock = System.Windows.Forms.DockStyle.Top;
            this.splitter3.Location = new System.Drawing.Point(0, 374);
            this.splitter3.Name = "splitter3";
            this.splitter3.Size = new System.Drawing.Size(495, 3);
            this.splitter3.TabIndex = 6;
            this.splitter3.TabStop = false;
            // 
            // presetScreensGroupBox
            // 
            this.presetScreensGroupBox.Controls.Add(this.presetScreensDataGridView);
            this.presetScreensGroupBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.presetScreensGroupBox.Location = new System.Drawing.Point(0, 168);
            this.presetScreensGroupBox.Name = "presetScreensGroupBox";
            this.presetScreensGroupBox.Size = new System.Drawing.Size(495, 206);
            this.presetScreensGroupBox.TabIndex = 5;
            this.presetScreensGroupBox.TabStop = false;
            this.presetScreensGroupBox.Text = "Preset screens";
            // 
            // presetScreensDataGridView
            // 
            this.presetScreensDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.presetScreensDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.presetScreenNameColumn,
            this.presetScreenScopeColumn});
            this.presetScreensDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.presetScreensDataGridView.Location = new System.Drawing.Point(3, 16);
            this.presetScreensDataGridView.Name = "presetScreensDataGridView";
            this.presetScreensDataGridView.Size = new System.Drawing.Size(489, 187);
            this.presetScreensDataGridView.TabIndex = 0;
            this.presetScreensDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.presetScreensDataGridView.RowsRemoved += new System.Windows.Forms.DataGridViewRowsRemovedEventHandler(this.presetScreensDataGridView_RowsRemoved);
            this.presetScreensDataGridView.Enter += new System.EventHandler(this.presetNamesDataGridView_Enter);
            this.presetScreensDataGridView.Leave += new System.EventHandler(this.presetScreensDataGridView_Leave);
            // 
            // presetScreenNameColumn
            // 
            this.presetScreenNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.presetScreenNameColumn.HeaderText = "Screen name";
            this.presetScreenNameColumn.Name = "presetScreenNameColumn";
            this.presetScreenNameColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.presetScreenNameColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.presetScreenNameColumn.Width = 250;
            // 
            // presetScreenScopeColumn
            // 
            this.presetScreenScopeColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.presetScreenScopeColumn.HeaderText = "Scope";
            this.presetScreenScopeColumn.Name = "presetScreenScopeColumn";
            this.presetScreenScopeColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.presetScreenScopeColumn.Width = 150;
            // 
            // splitter2
            // 
            this.splitter2.Dock = System.Windows.Forms.DockStyle.Top;
            this.splitter2.Location = new System.Drawing.Point(0, 165);
            this.splitter2.Name = "splitter2";
            this.splitter2.Size = new System.Drawing.Size(495, 3);
            this.splitter2.TabIndex = 4;
            this.splitter2.TabStop = false;
            // 
            // presetNamesGroupBox
            // 
            this.presetNamesGroupBox.Controls.Add(this.presetNamesDataGridView);
            this.presetNamesGroupBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.presetNamesGroupBox.Location = new System.Drawing.Point(0, 0);
            this.presetNamesGroupBox.Name = "presetNamesGroupBox";
            this.presetNamesGroupBox.Size = new System.Drawing.Size(495, 165);
            this.presetNamesGroupBox.TabIndex = 3;
            this.presetNamesGroupBox.TabStop = false;
            this.presetNamesGroupBox.Text = "Preset";
            // 
            // presetNamesDataGridView
            // 
            this.presetNamesDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.presetNamesDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.presetNameColumn,
            this.presetDateColumn,
            this.presetDescriptionColumn});
            this.presetNamesDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.presetNamesDataGridView.Location = new System.Drawing.Point(3, 16);
            this.presetNamesDataGridView.Name = "presetNamesDataGridView";
            this.presetNamesDataGridView.Size = new System.Drawing.Size(489, 146);
            this.presetNamesDataGridView.TabIndex = 0;
            this.presetNamesDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.presetNamesDataGridView.Enter += new System.EventHandler(this.presetNamesDataGridView_Enter);
            this.presetNamesDataGridView.Leave += new System.EventHandler(this.presetNamesDataGridView_Leave);
            // 
            // presetNameColumn
            // 
            this.presetNameColumn.HeaderText = "Preset name";
            this.presetNameColumn.Name = "presetNameColumn";
            this.presetNameColumn.Width = 200;
            // 
            // presetDateColumn
            // 
            this.presetDateColumn.HeaderText = "Date";
            this.presetDateColumn.Name = "presetDateColumn";
            this.presetDateColumn.Width = 150;
            // 
            // presetDescriptionColumn
            // 
            this.presetDescriptionColumn.HeaderText = "Description";
            this.presetDescriptionColumn.Name = "presetDescriptionColumn";
            this.presetDescriptionColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.presetDescriptionColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.presetDescriptionColumn.Width = 300;
            // 
            // presetBindingNavigator
            // 
            this.presetBindingNavigator.AddNewItem = this.toolStripButton7;
            this.presetBindingNavigator.CountItem = this.toolStripLabel2;
            this.presetBindingNavigator.DeleteItem = this.toolStripButton8;
            this.presetBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton9,
            this.toolStripButton10,
            this.toolStripSeparator4,
            this.toolStripTextBox2,
            this.toolStripLabel2,
            this.toolStripSeparator5,
            this.toolStripButton11,
            this.toolStripButton12,
            this.toolStripSeparator6,
            this.toolStripButton7,
            this.toolStripButton8,
            this.presetBindingNavigatorSaveItem,
            this.presetBindingNavigatorRefreshItem,
            this.toolStripSeparator37,
            this.presetBindingNavigatorHookupIten});
            this.presetBindingNavigator.Location = new System.Drawing.Point(0, 0);
            this.presetBindingNavigator.MoveFirstItem = this.toolStripButton9;
            this.presetBindingNavigator.MoveLastItem = this.toolStripButton12;
            this.presetBindingNavigator.MoveNextItem = this.toolStripButton11;
            this.presetBindingNavigator.MovePreviousItem = this.toolStripButton10;
            this.presetBindingNavigator.Name = "presetBindingNavigator";
            this.presetBindingNavigator.PositionItem = this.toolStripTextBox2;
            this.presetBindingNavigator.Size = new System.Drawing.Size(497, 25);
            this.presetBindingNavigator.TabIndex = 9;
            // 
            // toolStripButton7
            // 
            this.toolStripButton7.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton7.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton7.Image")));
            this.toolStripButton7.Name = "toolStripButton7";
            this.toolStripButton7.RightToLeftAutoMirrorImage = true;
            this.toolStripButton7.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton7.Text = "Add new";
            // 
            // toolStripLabel2
            // 
            this.toolStripLabel2.Name = "toolStripLabel2";
            this.toolStripLabel2.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel2.Text = "для {0}";
            this.toolStripLabel2.ToolTipText = "Total number of items";
            // 
            // toolStripButton8
            // 
            this.toolStripButton8.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton8.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton8.Image")));
            this.toolStripButton8.Name = "toolStripButton8";
            this.toolStripButton8.RightToLeftAutoMirrorImage = true;
            this.toolStripButton8.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton8.Text = "Delete";
            // 
            // toolStripButton9
            // 
            this.toolStripButton9.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton9.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton9.Image")));
            this.toolStripButton9.Name = "toolStripButton9";
            this.toolStripButton9.RightToLeftAutoMirrorImage = true;
            this.toolStripButton9.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton9.Text = "Move first";
            // 
            // toolStripButton10
            // 
            this.toolStripButton10.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton10.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton10.Image")));
            this.toolStripButton10.Name = "toolStripButton10";
            this.toolStripButton10.RightToLeftAutoMirrorImage = true;
            this.toolStripButton10.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton10.Text = "Move previous";
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox2
            // 
            this.toolStripTextBox2.AccessibleName = "Position";
            this.toolStripTextBox2.AutoSize = false;
            this.toolStripTextBox2.Name = "toolStripTextBox2";
            this.toolStripTextBox2.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox2.Text = "0";
            this.toolStripTextBox2.ToolTipText = "Current position";
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton11
            // 
            this.toolStripButton11.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton11.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton11.Image")));
            this.toolStripButton11.Name = "toolStripButton11";
            this.toolStripButton11.RightToLeftAutoMirrorImage = true;
            this.toolStripButton11.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton11.Text = "Move next";
            // 
            // toolStripButton12
            // 
            this.toolStripButton12.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton12.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton12.Image")));
            this.toolStripButton12.Name = "toolStripButton12";
            this.toolStripButton12.RightToLeftAutoMirrorImage = true;
            this.toolStripButton12.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton12.Text = "Move last";
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            this.toolStripSeparator6.Size = new System.Drawing.Size(6, 25);
            // 
            // presetBindingNavigatorSaveItem
            // 
            this.presetBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.presetBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("presetBindingNavigatorSaveItem.Image")));
            this.presetBindingNavigatorSaveItem.Name = "presetBindingNavigatorSaveItem";
            this.presetBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.presetBindingNavigatorSaveItem.Text = "Save Data";
            this.presetBindingNavigatorSaveItem.Click += new System.EventHandler(this.presetsBindingNavigatorSaveItem_Click);
            // 
            // presetBindingNavigatorRefreshItem
            // 
            this.presetBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.presetBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("presetBindingNavigatorRefreshItem.Image")));
            this.presetBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.presetBindingNavigatorRefreshItem.Name = "presetBindingNavigatorRefreshItem";
            this.presetBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.presetBindingNavigatorRefreshItem.Text = "Refresh";
            this.presetBindingNavigatorRefreshItem.Click += new System.EventHandler(this.presetBindingNavigatorRefreshItem_Click);
            // 
            // toolStripSeparator37
            // 
            this.toolStripSeparator37.Name = "toolStripSeparator37";
            this.toolStripSeparator37.Size = new System.Drawing.Size(6, 25);
            // 
            // presetBindingNavigatorHookupIten
            // 
            this.presetBindingNavigatorHookupIten.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.presetBindingNavigatorHookupIten.Image = ((System.Drawing.Image)(resources.GetObject("presetBindingNavigatorHookupIten.Image")));
            this.presetBindingNavigatorHookupIten.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.presetBindingNavigatorHookupIten.Name = "presetBindingNavigatorHookupIten";
            this.presetBindingNavigatorHookupIten.Size = new System.Drawing.Size(23, 22);
            this.presetBindingNavigatorHookupIten.Text = "Preset hookup";
            this.presetBindingNavigatorHookupIten.Click += new System.EventHandler(this.presetBindingNavigatorHookupIten_Click);
            // 
            // screenObjectsPanel
            // 
            this.screenObjectsPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.screenObjectsPanel.Controls.Add(this.screenObjectsGroupBox);
            this.screenObjectsPanel.Controls.Add(this.splitter1);
            this.screenObjectsPanel.Controls.Add(this.screenObjectValuesTabControl);
            this.screenObjectsPanel.Controls.Add(this.splitter4);
            this.screenObjectsPanel.Controls.Add(this.screensGroupBox);
            this.screenObjectsPanel.Controls.Add(this.screenObjectsBindingNavigator);
            this.screenObjectsPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.screenObjectsPanel.Location = new System.Drawing.Point(0, 0);
            this.screenObjectsPanel.Name = "screenObjectsPanel";
            this.screenObjectsPanel.Size = new System.Drawing.Size(489, 629);
            this.screenObjectsPanel.TabIndex = 9;
            // 
            // screenObjectsGroupBox
            // 
            this.screenObjectsGroupBox.Controls.Add(this.screenObjectsDataGridView);
            this.screenObjectsGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.screenObjectsGroupBox.Location = new System.Drawing.Point(0, 180);
            this.screenObjectsGroupBox.Name = "screenObjectsGroupBox";
            this.screenObjectsGroupBox.Size = new System.Drawing.Size(487, 156);
            this.screenObjectsGroupBox.TabIndex = 2;
            this.screenObjectsGroupBox.TabStop = false;
            this.screenObjectsGroupBox.Text = "General user screen objects list";
            // 
            // screenObjectsDataGridView
            // 
            this.screenObjectsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.screenObjectsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.screenObjectNameColumn,
            this.screenObjectCaptionColumn,
            this.screenObjectTypeIDColumn,
            this.screenObjectStrValueColumn,
            this.screenObjectLocationXColumn,
            this.screenObjectLocationYColumn,
            this.screenObjectLocationXPersColumn,
            this.screenObjectLocationYPersColumn,
            this.screenObjectWidthColumn,
            this.screenObjectHeightColumn,
            this.screenObjectWidthPersColumn,
            this.screenObjectHeightPersColumn,
            this.screenObjectColorColumn,
            this.screenObjectFontSizeColumn,
            this.screenObjectTextColorColumn});
            this.screenObjectsDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.screenObjectsDataGridView.Location = new System.Drawing.Point(3, 16);
            this.screenObjectsDataGridView.Name = "screenObjectsDataGridView";
            this.screenObjectsDataGridView.Size = new System.Drawing.Size(481, 137);
            this.screenObjectsDataGridView.TabIndex = 1;
            this.screenObjectsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.screenObjectsDataGridView.Enter += new System.EventHandler(this.screensDataGridView_Enter);
            // 
            // screenObjectNameColumn
            // 
            this.screenObjectNameColumn.HeaderText = "Name";
            this.screenObjectNameColumn.Name = "screenObjectNameColumn";
            this.screenObjectNameColumn.Width = 200;
            // 
            // screenObjectCaptionColumn
            // 
            this.screenObjectCaptionColumn.HeaderText = "Caption";
            this.screenObjectCaptionColumn.Name = "screenObjectCaptionColumn";
            this.screenObjectCaptionColumn.Width = 200;
            // 
            // screenObjectTypeIDColumn
            // 
            this.screenObjectTypeIDColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.screenObjectTypeIDColumn.HeaderText = "Type";
            this.screenObjectTypeIDColumn.Name = "screenObjectTypeIDColumn";
            this.screenObjectTypeIDColumn.Width = 200;
            // 
            // screenObjectStrValueColumn
            // 
            this.screenObjectStrValueColumn.HeaderText = "String value";
            this.screenObjectStrValueColumn.Name = "screenObjectStrValueColumn";
            this.screenObjectStrValueColumn.Width = 200;
            // 
            // screenObjectLocationXColumn
            // 
            this.screenObjectLocationXColumn.HeaderText = "Location (X), Pixels";
            this.screenObjectLocationXColumn.Name = "screenObjectLocationXColumn";
            this.screenObjectLocationXColumn.Width = 200;
            // 
            // screenObjectLocationYColumn
            // 
            this.screenObjectLocationYColumn.HeaderText = "Location (Y), Pixels";
            this.screenObjectLocationYColumn.Name = "screenObjectLocationYColumn";
            this.screenObjectLocationYColumn.Width = 200;
            // 
            // screenObjectLocationXPersColumn
            // 
            this.screenObjectLocationXPersColumn.HeaderText = "Location (X), %";
            this.screenObjectLocationXPersColumn.Name = "screenObjectLocationXPersColumn";
            this.screenObjectLocationXPersColumn.Width = 200;
            // 
            // screenObjectLocationYPersColumn
            // 
            this.screenObjectLocationYPersColumn.HeaderText = "Location (Y), %";
            this.screenObjectLocationYPersColumn.Name = "screenObjectLocationYPersColumn";
            this.screenObjectLocationYPersColumn.Width = 200;
            // 
            // screenObjectWidthColumn
            // 
            this.screenObjectWidthColumn.HeaderText = "Width, pixels";
            this.screenObjectWidthColumn.Name = "screenObjectWidthColumn";
            this.screenObjectWidthColumn.Width = 200;
            // 
            // screenObjectHeightColumn
            // 
            this.screenObjectHeightColumn.HeaderText = "Height, pixels";
            this.screenObjectHeightColumn.Name = "screenObjectHeightColumn";
            this.screenObjectHeightColumn.Width = 200;
            // 
            // screenObjectWidthPersColumn
            // 
            this.screenObjectWidthPersColumn.HeaderText = "Width, %";
            this.screenObjectWidthPersColumn.Name = "screenObjectWidthPersColumn";
            this.screenObjectWidthPersColumn.Width = 200;
            // 
            // screenObjectHeightPersColumn
            // 
            this.screenObjectHeightPersColumn.HeaderText = "Height, %";
            this.screenObjectHeightPersColumn.Name = "screenObjectHeightPersColumn";
            this.screenObjectHeightPersColumn.Width = 200;
            // 
            // screenObjectColorColumn
            // 
            this.screenObjectColorColumn.HeaderText = "Color";
            this.screenObjectColorColumn.Name = "screenObjectColorColumn";
            this.screenObjectColorColumn.Width = 200;
            // 
            // screenObjectFontSizeColumn
            // 
            this.screenObjectFontSizeColumn.HeaderText = "Font size";
            this.screenObjectFontSizeColumn.Name = "screenObjectFontSizeColumn";
            this.screenObjectFontSizeColumn.Width = 200;
            // 
            // screenObjectTextColorColumn
            // 
            this.screenObjectTextColorColumn.HeaderText = "Text color";
            this.screenObjectTextColorColumn.Name = "screenObjectTextColorColumn";
            this.screenObjectTextColorColumn.Width = 200;
            // 
            // splitter1
            // 
            this.splitter1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.splitter1.Location = new System.Drawing.Point(0, 336);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(487, 3);
            this.splitter1.TabIndex = 1;
            this.splitter1.TabStop = false;
            // 
            // screenObjectValuesTabControl
            // 
            this.screenObjectValuesTabControl.Controls.Add(this.tabScreenObjectText);
            this.screenObjectValuesTabControl.Controls.Add(this.tabScreenObjectImage);
            this.screenObjectValuesTabControl.Controls.Add(this.tabScreenObjectListValues);
            this.screenObjectValuesTabControl.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.screenObjectValuesTabControl.ImageList = this.screenObjValuesImageList;
            this.screenObjectValuesTabControl.Location = new System.Drawing.Point(0, 339);
            this.screenObjectValuesTabControl.Name = "screenObjectValuesTabControl";
            this.screenObjectValuesTabControl.SelectedIndex = 0;
            this.screenObjectValuesTabControl.Size = new System.Drawing.Size(487, 288);
            this.screenObjectValuesTabControl.TabIndex = 1;
            // 
            // tabScreenObjectText
            // 
            this.tabScreenObjectText.Controls.Add(this.screenObjectTextPanel);
            this.tabScreenObjectText.ImageIndex = 2;
            this.tabScreenObjectText.Location = new System.Drawing.Point(4, 23);
            this.tabScreenObjectText.Name = "tabScreenObjectText";
            this.tabScreenObjectText.Padding = new System.Windows.Forms.Padding(3);
            this.tabScreenObjectText.Size = new System.Drawing.Size(479, 261);
            this.tabScreenObjectText.TabIndex = 0;
            this.tabScreenObjectText.Text = "Screen object text";
            this.tabScreenObjectText.UseVisualStyleBackColor = true;
            // 
            // screenObjectTextPanel
            // 
            this.screenObjectTextPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.screenObjectTextPanel.Controls.Add(this.screenObjectTextClearButton);
            this.screenObjectTextPanel.Controls.Add(this.screenObjectRichTextBox);
            this.screenObjectTextPanel.Controls.Add(this.loadScreenObjecTextButton);
            this.screenObjectTextPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.screenObjectTextPanel.Location = new System.Drawing.Point(3, 3);
            this.screenObjectTextPanel.Name = "screenObjectTextPanel";
            this.screenObjectTextPanel.Size = new System.Drawing.Size(473, 255);
            this.screenObjectTextPanel.TabIndex = 2;
            // 
            // screenObjectTextClearButton
            // 
            this.screenObjectTextClearButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.screenObjectTextClearButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.screenObjectTextClearButton.Image = ((System.Drawing.Image)(resources.GetObject("screenObjectTextClearButton.Image")));
            this.screenObjectTextClearButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.screenObjectTextClearButton.Location = new System.Drawing.Point(5, 205);
            this.screenObjectTextClearButton.Name = "screenObjectTextClearButton";
            this.screenObjectTextClearButton.Size = new System.Drawing.Size(100, 41);
            this.screenObjectTextClearButton.TabIndex = 3;
            this.screenObjectTextClearButton.Text = "Clear";
            this.screenObjectTextClearButton.UseVisualStyleBackColor = true;
            this.screenObjectTextClearButton.Click += new System.EventHandler(this.scrennObjectTextClearButton_Click);
            // 
            // screenObjectRichTextBox
            // 
            this.screenObjectRichTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.screenObjectRichTextBox.Location = new System.Drawing.Point(4, 5);
            this.screenObjectRichTextBox.Name = "screenObjectRichTextBox";
            this.screenObjectRichTextBox.Size = new System.Drawing.Size(464, 192);
            this.screenObjectRichTextBox.TabIndex = 0;
            this.screenObjectRichTextBox.Text = "";
            this.screenObjectRichTextBox.Enter += new System.EventHandler(this.screenObjectRichTextBox_Enter);
            // 
            // loadScreenObjecTextButton
            // 
            this.loadScreenObjecTextButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.loadScreenObjecTextButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.loadScreenObjecTextButton.Image = ((System.Drawing.Image)(resources.GetObject("loadScreenObjecTextButton.Image")));
            this.loadScreenObjecTextButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.loadScreenObjecTextButton.Location = new System.Drawing.Point(111, 205);
            this.loadScreenObjecTextButton.Name = "loadScreenObjecTextButton";
            this.loadScreenObjecTextButton.Size = new System.Drawing.Size(100, 41);
            this.loadScreenObjecTextButton.TabIndex = 2;
            this.loadScreenObjecTextButton.Text = "Open";
            this.loadScreenObjecTextButton.UseVisualStyleBackColor = true;
            this.loadScreenObjecTextButton.Click += new System.EventHandler(this.loadscreenObjecTextButton_Click);
            // 
            // tabScreenObjectImage
            // 
            this.tabScreenObjectImage.Controls.Add(this.screenObjectImagePanel);
            this.tabScreenObjectImage.ImageIndex = 0;
            this.tabScreenObjectImage.Location = new System.Drawing.Point(4, 23);
            this.tabScreenObjectImage.Name = "tabScreenObjectImage";
            this.tabScreenObjectImage.Padding = new System.Windows.Forms.Padding(3);
            this.tabScreenObjectImage.Size = new System.Drawing.Size(479, 261);
            this.tabScreenObjectImage.TabIndex = 1;
            this.tabScreenObjectImage.Text = "Screen object image";
            this.tabScreenObjectImage.UseVisualStyleBackColor = true;
            // 
            // screenObjectImagePanel
            // 
            this.screenObjectImagePanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.screenObjectImagePanel.Controls.Add(this.scrennObjectImageClearButton);
            this.screenObjectImagePanel.Controls.Add(this.loadScreenObjectImageButton);
            this.screenObjectImagePanel.Controls.Add(this.screenObjectPictureBox);
            this.screenObjectImagePanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.screenObjectImagePanel.Location = new System.Drawing.Point(3, 3);
            this.screenObjectImagePanel.Name = "screenObjectImagePanel";
            this.screenObjectImagePanel.Size = new System.Drawing.Size(473, 255);
            this.screenObjectImagePanel.TabIndex = 0;
            // 
            // scrennObjectImageClearButton
            // 
            this.scrennObjectImageClearButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.scrennObjectImageClearButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.scrennObjectImageClearButton.Image = ((System.Drawing.Image)(resources.GetObject("scrennObjectImageClearButton.Image")));
            this.scrennObjectImageClearButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.scrennObjectImageClearButton.Location = new System.Drawing.Point(5, 205);
            this.scrennObjectImageClearButton.Name = "scrennObjectImageClearButton";
            this.scrennObjectImageClearButton.Size = new System.Drawing.Size(100, 40);
            this.scrennObjectImageClearButton.TabIndex = 2;
            this.scrennObjectImageClearButton.Text = "Clear";
            this.scrennObjectImageClearButton.UseVisualStyleBackColor = true;
            this.scrennObjectImageClearButton.Click += new System.EventHandler(this.scrennObjectImageClearButton_Click);
            // 
            // loadScreenObjectImageButton
            // 
            this.loadScreenObjectImageButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.loadScreenObjectImageButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.loadScreenObjectImageButton.Image = ((System.Drawing.Image)(resources.GetObject("loadScreenObjectImageButton.Image")));
            this.loadScreenObjectImageButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.loadScreenObjectImageButton.Location = new System.Drawing.Point(111, 205);
            this.loadScreenObjectImageButton.Name = "loadScreenObjectImageButton";
            this.loadScreenObjectImageButton.Size = new System.Drawing.Size(100, 40);
            this.loadScreenObjectImageButton.TabIndex = 1;
            this.loadScreenObjectImageButton.Text = "Open";
            this.loadScreenObjectImageButton.UseVisualStyleBackColor = true;
            this.loadScreenObjectImageButton.Click += new System.EventHandler(this.loadscreenObjectImageButton_Click);
            // 
            // screenObjectPictureBox
            // 
            this.screenObjectPictureBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.screenObjectPictureBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.screenObjectPictureBox.Location = new System.Drawing.Point(4, 6);
            this.screenObjectPictureBox.Name = "screenObjectPictureBox";
            this.screenObjectPictureBox.Size = new System.Drawing.Size(461, 192);
            this.screenObjectPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.screenObjectPictureBox.TabIndex = 0;
            this.screenObjectPictureBox.TabStop = false;
            this.screenObjectPictureBox.Click += new System.EventHandler(this.screenObjectPictureBox_Click);
            // 
            // tabScreenObjectListValues
            // 
            this.tabScreenObjectListValues.Controls.Add(this.screenObjectListValuesPanel);
            this.tabScreenObjectListValues.ImageIndex = 1;
            this.tabScreenObjectListValues.Location = new System.Drawing.Point(4, 23);
            this.tabScreenObjectListValues.Name = "tabScreenObjectListValues";
            this.tabScreenObjectListValues.Padding = new System.Windows.Forms.Padding(3);
            this.tabScreenObjectListValues.Size = new System.Drawing.Size(479, 261);
            this.tabScreenObjectListValues.TabIndex = 2;
            this.tabScreenObjectListValues.Text = "Screen object list values";
            this.tabScreenObjectListValues.UseVisualStyleBackColor = true;
            // 
            // screenObjectListValuesPanel
            // 
            this.screenObjectListValuesPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.screenObjectListValuesPanel.Controls.Add(this.screenObjectListValuesDataGridView);
            this.screenObjectListValuesPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.screenObjectListValuesPanel.Location = new System.Drawing.Point(3, 3);
            this.screenObjectListValuesPanel.Name = "screenObjectListValuesPanel";
            this.screenObjectListValuesPanel.Size = new System.Drawing.Size(473, 255);
            this.screenObjectListValuesPanel.TabIndex = 5;
            // 
            // screenObjectListValuesDataGridView
            // 
            this.screenObjectListValuesDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.screenObjectListValuesDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.screenObjectListValuesColumn});
            this.screenObjectListValuesDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.screenObjectListValuesDataGridView.Location = new System.Drawing.Point(0, 0);
            this.screenObjectListValuesDataGridView.Name = "screenObjectListValuesDataGridView";
            this.screenObjectListValuesDataGridView.Size = new System.Drawing.Size(471, 253);
            this.screenObjectListValuesDataGridView.TabIndex = 2;
            this.screenObjectListValuesDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.screenObjectListValuesDataGridView.Enter += new System.EventHandler(this.screenObjectListValuesDataGridView_Enter);
            // 
            // screenObjectListValuesColumn
            // 
            this.screenObjectListValuesColumn.HeaderText = "List values";
            this.screenObjectListValuesColumn.Name = "screenObjectListValuesColumn";
            this.screenObjectListValuesColumn.Width = 300;
            // 
            // screenObjValuesImageList
            // 
            this.screenObjValuesImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("screenObjValuesImageList.ImageStream")));
            this.screenObjValuesImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.screenObjValuesImageList.Images.SetKeyName(0, "photo_scenery.png");
            this.screenObjValuesImageList.Images.SetKeyName(1, "text_align_justified.png");
            this.screenObjValuesImageList.Images.SetKeyName(2, "note.png");
            // 
            // splitter4
            // 
            this.splitter4.Dock = System.Windows.Forms.DockStyle.Top;
            this.splitter4.Location = new System.Drawing.Point(0, 177);
            this.splitter4.Name = "splitter4";
            this.splitter4.Size = new System.Drawing.Size(487, 3);
            this.splitter4.TabIndex = 11;
            this.splitter4.TabStop = false;
            // 
            // screensGroupBox
            // 
            this.screensGroupBox.Controls.Add(this.screensDataGridView);
            this.screensGroupBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.screensGroupBox.Location = new System.Drawing.Point(0, 25);
            this.screensGroupBox.Name = "screensGroupBox";
            this.screensGroupBox.Size = new System.Drawing.Size(487, 152);
            this.screensGroupBox.TabIndex = 0;
            this.screensGroupBox.TabStop = false;
            this.screensGroupBox.Text = "General user screens list";
            // 
            // screensDataGridView
            // 
            this.screensDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.screensDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.screenNameColumn,
            this.screenCaptionColumn,
            this.screenTypeIDColumn,
            this.screenLocationXColumn,
            this.screenLocationYColumn,
            this.screenLocationXPersColumn,
            this.screenLocationYPersColumn,
            this.screenWidthColumn,
            this.screenHeightColumn,
            this.screenWidthPersColumn,
            this.screenHeightPersColumn,
            this.screenColorColumn,
            this.screenFontSizeColumn,
            this.screenTextColorColumn});
            this.screensDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.screensDataGridView.Location = new System.Drawing.Point(3, 16);
            this.screensDataGridView.Name = "screensDataGridView";
            this.screensDataGridView.Size = new System.Drawing.Size(481, 133);
            this.screensDataGridView.TabIndex = 0;
            this.screensDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.screensDataGridView.Enter += new System.EventHandler(this.screensDataGridView_Enter);
            this.screensDataGridView.Leave += new System.EventHandler(this.screensDataGridView_Leave);
            // 
            // screenNameColumn
            // 
            this.screenNameColumn.HeaderText = "Name";
            this.screenNameColumn.Name = "screenNameColumn";
            this.screenNameColumn.Width = 200;
            // 
            // screenCaptionColumn
            // 
            this.screenCaptionColumn.HeaderText = "Caption";
            this.screenCaptionColumn.Name = "screenCaptionColumn";
            this.screenCaptionColumn.Width = 200;
            // 
            // screenTypeIDColumn
            // 
            this.screenTypeIDColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.screenTypeIDColumn.HeaderText = "Type";
            this.screenTypeIDColumn.Name = "screenTypeIDColumn";
            this.screenTypeIDColumn.Width = 200;
            // 
            // screenLocationXColumn
            // 
            this.screenLocationXColumn.HeaderText = "Location (X), Pixels";
            this.screenLocationXColumn.Name = "screenLocationXColumn";
            this.screenLocationXColumn.Width = 200;
            // 
            // screenLocationYColumn
            // 
            this.screenLocationYColumn.HeaderText = "Location (Y), Pixels";
            this.screenLocationYColumn.Name = "screenLocationYColumn";
            this.screenLocationYColumn.Width = 200;
            // 
            // screenLocationXPersColumn
            // 
            this.screenLocationXPersColumn.HeaderText = "Location (X), %";
            this.screenLocationXPersColumn.Name = "screenLocationXPersColumn";
            this.screenLocationXPersColumn.Width = 200;
            // 
            // screenLocationYPersColumn
            // 
            this.screenLocationYPersColumn.HeaderText = "Location (Y), %";
            this.screenLocationYPersColumn.Name = "screenLocationYPersColumn";
            this.screenLocationYPersColumn.Width = 200;
            // 
            // screenWidthColumn
            // 
            this.screenWidthColumn.HeaderText = "Width, pixels";
            this.screenWidthColumn.Name = "screenWidthColumn";
            this.screenWidthColumn.Width = 200;
            // 
            // screenHeightColumn
            // 
            this.screenHeightColumn.HeaderText = "Height, pixels";
            this.screenHeightColumn.Name = "screenHeightColumn";
            this.screenHeightColumn.Width = 200;
            // 
            // screenWidthPersColumn
            // 
            this.screenWidthPersColumn.HeaderText = "Width, %";
            this.screenWidthPersColumn.Name = "screenWidthPersColumn";
            this.screenWidthPersColumn.Width = 200;
            // 
            // screenHeightPersColumn
            // 
            this.screenHeightPersColumn.HeaderText = "Height, %";
            this.screenHeightPersColumn.Name = "screenHeightPersColumn";
            this.screenHeightPersColumn.Width = 200;
            // 
            // screenColorColumn
            // 
            this.screenColorColumn.HeaderText = "Color";
            this.screenColorColumn.Name = "screenColorColumn";
            this.screenColorColumn.Width = 200;
            // 
            // screenFontSizeColumn
            // 
            this.screenFontSizeColumn.HeaderText = "Font size";
            this.screenFontSizeColumn.Name = "screenFontSizeColumn";
            this.screenFontSizeColumn.Width = 200;
            // 
            // screenTextColorColumn
            // 
            this.screenTextColorColumn.HeaderText = "Text color";
            this.screenTextColorColumn.Name = "screenTextColorColumn";
            this.screenTextColorColumn.Width = 200;
            // 
            // screenObjectsBindingNavigator
            // 
            this.screenObjectsBindingNavigator.AddNewItem = this.toolStripButton1;
            this.screenObjectsBindingNavigator.CountItem = this.toolStripLabel1;
            this.screenObjectsBindingNavigator.DeleteItem = this.toolStripButton2;
            this.screenObjectsBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton3,
            this.toolStripButton4,
            this.toolStripSeparator1,
            this.toolStripTextBox1,
            this.toolStripLabel1,
            this.toolStripSeparator2,
            this.toolStripButton5,
            this.toolStripButton6,
            this.toolStripSeparator3,
            this.toolStripButton1,
            this.toolStripButton2,
            this.screenObjectsBindingNavigatorSaveItem,
            this.screenObjectsBindingNavigatorRefreshItem});
            this.screenObjectsBindingNavigator.Location = new System.Drawing.Point(0, 0);
            this.screenObjectsBindingNavigator.MoveFirstItem = this.toolStripButton3;
            this.screenObjectsBindingNavigator.MoveLastItem = this.toolStripButton6;
            this.screenObjectsBindingNavigator.MoveNextItem = this.toolStripButton5;
            this.screenObjectsBindingNavigator.MovePreviousItem = this.toolStripButton4;
            this.screenObjectsBindingNavigator.Name = "screenObjectsBindingNavigator";
            this.screenObjectsBindingNavigator.PositionItem = this.toolStripTextBox1;
            this.screenObjectsBindingNavigator.Size = new System.Drawing.Size(487, 25);
            this.screenObjectsBindingNavigator.TabIndex = 10;
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.RightToLeftAutoMirrorImage = true;
            this.toolStripButton1.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton1.Text = "Add new";
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel1.Text = "для {0}";
            this.toolStripLabel1.ToolTipText = "Total number of items";
            // 
            // toolStripButton2
            // 
            this.toolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton2.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton2.Image")));
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.RightToLeftAutoMirrorImage = true;
            this.toolStripButton2.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton2.Text = "Delete";
            // 
            // toolStripButton3
            // 
            this.toolStripButton3.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton3.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton3.Image")));
            this.toolStripButton3.Name = "toolStripButton3";
            this.toolStripButton3.RightToLeftAutoMirrorImage = true;
            this.toolStripButton3.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton3.Text = "Move first";
            // 
            // toolStripButton4
            // 
            this.toolStripButton4.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton4.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton4.Image")));
            this.toolStripButton4.Name = "toolStripButton4";
            this.toolStripButton4.RightToLeftAutoMirrorImage = true;
            this.toolStripButton4.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton4.Text = "Move previous";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox1
            // 
            this.toolStripTextBox1.AccessibleName = "Position";
            this.toolStripTextBox1.AutoSize = false;
            this.toolStripTextBox1.Name = "toolStripTextBox1";
            this.toolStripTextBox1.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox1.Text = "0";
            this.toolStripTextBox1.ToolTipText = "Current position";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton5
            // 
            this.toolStripButton5.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton5.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton5.Image")));
            this.toolStripButton5.Name = "toolStripButton5";
            this.toolStripButton5.RightToLeftAutoMirrorImage = true;
            this.toolStripButton5.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton5.Text = "Move next";
            // 
            // toolStripButton6
            // 
            this.toolStripButton6.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton6.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton6.Image")));
            this.toolStripButton6.Name = "toolStripButton6";
            this.toolStripButton6.RightToLeftAutoMirrorImage = true;
            this.toolStripButton6.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton6.Text = "Move last";
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
            // 
            // screenObjectsBindingNavigatorSaveItem
            // 
            this.screenObjectsBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.screenObjectsBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("screenObjectsBindingNavigatorSaveItem.Image")));
            this.screenObjectsBindingNavigatorSaveItem.Name = "screenObjectsBindingNavigatorSaveItem";
            this.screenObjectsBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.screenObjectsBindingNavigatorSaveItem.Text = "Save Data";
            this.screenObjectsBindingNavigatorSaveItem.Click += new System.EventHandler(this.screenObjectsBindingNavigatorSaveItem_Click);
            // 
            // screenObjectsBindingNavigatorRefreshItem
            // 
            this.screenObjectsBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.screenObjectsBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("screenObjectsBindingNavigatorRefreshItem.Image")));
            this.screenObjectsBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.screenObjectsBindingNavigatorRefreshItem.Name = "screenObjectsBindingNavigatorRefreshItem";
            this.screenObjectsBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.screenObjectsBindingNavigatorRefreshItem.Text = "Refresh";
            this.screenObjectsBindingNavigatorRefreshItem.Click += new System.EventHandler(this.screenObjectsBindingNavigatorRefreshItem_Click);
            // 
            // educationTabPage
            // 
            this.educationTabPage.Controls.Add(this.educationMainPanel);
            this.educationTabPage.ImageIndex = 2;
            this.educationTabPage.Location = new System.Drawing.Point(4, 42);
            this.educationTabPage.Name = "educationTabPage";
            this.educationTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.educationTabPage.Size = new System.Drawing.Size(1000, 637);
            this.educationTabPage.TabIndex = 2;
            this.educationTabPage.Text = "Education management";
            this.educationTabPage.UseVisualStyleBackColor = true;
            // 
            // educationMainPanel
            // 
            this.educationMainPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.educationMainPanel.Controls.Add(this.educationMainSplitContainer);
            this.educationMainPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.educationMainPanel.Location = new System.Drawing.Point(3, 3);
            this.educationMainPanel.Name = "educationMainPanel";
            this.educationMainPanel.Size = new System.Drawing.Size(994, 631);
            this.educationMainPanel.TabIndex = 0;
            // 
            // educationMainSplitContainer
            // 
            this.educationMainSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.educationMainSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.educationMainSplitContainer.Name = "educationMainSplitContainer";
            this.educationMainSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // educationMainSplitContainer.Panel1
            // 
            this.educationMainSplitContainer.Panel1.Controls.Add(this.eduEditorPanel);
            this.educationMainSplitContainer.Panel1.Controls.Add(this.eduButtonsBottomPanel);
            // 
            // educationMainSplitContainer.Panel2
            // 
            this.educationMainSplitContainer.Panel2.Controls.Add(this.eduTabControl);
            this.educationMainSplitContainer.Size = new System.Drawing.Size(992, 629);
            this.educationMainSplitContainer.SplitterDistance = 342;
            this.educationMainSplitContainer.TabIndex = 0;
            // 
            // eduEditorPanel
            // 
            this.eduEditorPanel.Controls.Add(this.eduLessonsTabControl);
            this.eduEditorPanel.Controls.Add(this.splitter8);
            this.eduEditorPanel.Controls.Add(this.eduCategoriesGroupBox);
            this.eduEditorPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduEditorPanel.Location = new System.Drawing.Point(0, 0);
            this.eduEditorPanel.Name = "eduEditorPanel";
            this.eduEditorPanel.Size = new System.Drawing.Size(992, 305);
            this.eduEditorPanel.TabIndex = 5;
            // 
            // eduLessonsTabControl
            // 
            this.eduLessonsTabControl.Controls.Add(this.tabLessons);
            this.eduLessonsTabControl.Controls.Add(this.tabQuestions);
            this.eduLessonsTabControl.Controls.Add(this.tabAnswers);
            this.eduLessonsTabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduLessonsTabControl.ImageList = this.eduLessonsImageList;
            this.eduLessonsTabControl.Location = new System.Drawing.Point(324, 0);
            this.eduLessonsTabControl.Name = "eduLessonsTabControl";
            this.eduLessonsTabControl.SelectedIndex = 0;
            this.eduLessonsTabControl.Size = new System.Drawing.Size(668, 305);
            this.eduLessonsTabControl.TabIndex = 6;
            this.eduLessonsTabControl.SelectedIndexChanged += new System.EventHandler(this.eduLessonsTabControl_SelectedIndexChanged);
            // 
            // tabLessons
            // 
            this.tabLessons.Controls.Add(this.eduLessonSplitContainer);
            this.tabLessons.Controls.Add(this.splitter9);
            this.tabLessons.Controls.Add(this.lessonsOrderPanel);
            this.tabLessons.Controls.Add(this.eduLessonsBindingNavigator);
            this.tabLessons.ImageIndex = 0;
            this.tabLessons.Location = new System.Drawing.Point(4, 23);
            this.tabLessons.Name = "tabLessons";
            this.tabLessons.Padding = new System.Windows.Forms.Padding(3);
            this.tabLessons.Size = new System.Drawing.Size(660, 278);
            this.tabLessons.TabIndex = 0;
            this.tabLessons.Text = "Lessons";
            this.tabLessons.UseVisualStyleBackColor = true;
            // 
            // eduLessonSplitContainer
            // 
            this.eduLessonSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduLessonSplitContainer.Location = new System.Drawing.Point(6, 75);
            this.eduLessonSplitContainer.Name = "eduLessonSplitContainer";
            // 
            // eduLessonSplitContainer.Panel1
            // 
            this.eduLessonSplitContainer.Panel1.Controls.Add(this.eduLessonImagePanel);
            // 
            // eduLessonSplitContainer.Panel2
            // 
            this.eduLessonSplitContainer.Panel2.Controls.Add(this.eduLessonTextPanel);
            this.eduLessonSplitContainer.Size = new System.Drawing.Size(651, 200);
            this.eduLessonSplitContainer.SplitterDistance = 314;
            this.eduLessonSplitContainer.TabIndex = 16;
            // 
            // eduLessonImagePanel
            // 
            this.eduLessonImagePanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduLessonImagePanel.Controls.Add(this.eduLessonImageClearButton);
            this.eduLessonImagePanel.Controls.Add(this.eduLessonImageOpenButton);
            this.eduLessonImagePanel.Controls.Add(this.eduLessonPictureBox);
            this.eduLessonImagePanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduLessonImagePanel.Location = new System.Drawing.Point(0, 0);
            this.eduLessonImagePanel.Name = "eduLessonImagePanel";
            this.eduLessonImagePanel.Size = new System.Drawing.Size(314, 200);
            this.eduLessonImagePanel.TabIndex = 13;
            // 
            // eduLessonImageClearButton
            // 
            this.eduLessonImageClearButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.eduLessonImageClearButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.eduLessonImageClearButton.Image = ((System.Drawing.Image)(resources.GetObject("eduLessonImageClearButton.Image")));
            this.eduLessonImageClearButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.eduLessonImageClearButton.Location = new System.Drawing.Point(4, 147);
            this.eduLessonImageClearButton.Name = "eduLessonImageClearButton";
            this.eduLessonImageClearButton.Size = new System.Drawing.Size(114, 44);
            this.eduLessonImageClearButton.TabIndex = 2;
            this.eduLessonImageClearButton.Text = "Clear";
            this.eduLessonImageClearButton.UseVisualStyleBackColor = true;
            this.eduLessonImageClearButton.Click += new System.EventHandler(this.eduLessonImageClearButton_Click);
            // 
            // eduLessonImageOpenButton
            // 
            this.eduLessonImageOpenButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.eduLessonImageOpenButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.eduLessonImageOpenButton.Image = ((System.Drawing.Image)(resources.GetObject("eduLessonImageOpenButton.Image")));
            this.eduLessonImageOpenButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.eduLessonImageOpenButton.Location = new System.Drawing.Point(123, 147);
            this.eduLessonImageOpenButton.Name = "eduLessonImageOpenButton";
            this.eduLessonImageOpenButton.Size = new System.Drawing.Size(108, 44);
            this.eduLessonImageOpenButton.TabIndex = 1;
            this.eduLessonImageOpenButton.Text = "Open";
            this.eduLessonImageOpenButton.UseVisualStyleBackColor = true;
            this.eduLessonImageOpenButton.Click += new System.EventHandler(this.eduLessonImageOpenButton_Click);
            // 
            // eduLessonPictureBox
            // 
            this.eduLessonPictureBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.eduLessonPictureBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduLessonPictureBox.Location = new System.Drawing.Point(4, 6);
            this.eduLessonPictureBox.Name = "eduLessonPictureBox";
            this.eduLessonPictureBox.Size = new System.Drawing.Size(302, 135);
            this.eduLessonPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.eduLessonPictureBox.TabIndex = 0;
            this.eduLessonPictureBox.TabStop = false;
            // 
            // eduLessonTextPanel
            // 
            this.eduLessonTextPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduLessonTextPanel.Controls.Add(this.eduLessonTextClearButton);
            this.eduLessonTextPanel.Controls.Add(this.eduLessonRichTextBox);
            this.eduLessonTextPanel.Controls.Add(this.eduLessonTextOpenButton);
            this.eduLessonTextPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduLessonTextPanel.Location = new System.Drawing.Point(0, 0);
            this.eduLessonTextPanel.Name = "eduLessonTextPanel";
            this.eduLessonTextPanel.Size = new System.Drawing.Size(333, 200);
            this.eduLessonTextPanel.TabIndex = 14;
            // 
            // eduLessonTextClearButton
            // 
            this.eduLessonTextClearButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.eduLessonTextClearButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.eduLessonTextClearButton.Image = ((System.Drawing.Image)(resources.GetObject("eduLessonTextClearButton.Image")));
            this.eduLessonTextClearButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.eduLessonTextClearButton.Location = new System.Drawing.Point(5, 147);
            this.eduLessonTextClearButton.Name = "eduLessonTextClearButton";
            this.eduLessonTextClearButton.Size = new System.Drawing.Size(116, 44);
            this.eduLessonTextClearButton.TabIndex = 3;
            this.eduLessonTextClearButton.Text = "Clear";
            this.eduLessonTextClearButton.UseVisualStyleBackColor = true;
            this.eduLessonTextClearButton.Click += new System.EventHandler(this.eduLessonTextClearButton_Click);
            // 
            // eduLessonRichTextBox
            // 
            this.eduLessonRichTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.eduLessonRichTextBox.Location = new System.Drawing.Point(4, 5);
            this.eduLessonRichTextBox.Name = "eduLessonRichTextBox";
            this.eduLessonRichTextBox.Size = new System.Drawing.Size(320, 136);
            this.eduLessonRichTextBox.TabIndex = 0;
            this.eduLessonRichTextBox.Text = "";
            // 
            // eduLessonTextOpenButton
            // 
            this.eduLessonTextOpenButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.eduLessonTextOpenButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.eduLessonTextOpenButton.Image = ((System.Drawing.Image)(resources.GetObject("eduLessonTextOpenButton.Image")));
            this.eduLessonTextOpenButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.eduLessonTextOpenButton.Location = new System.Drawing.Point(127, 147);
            this.eduLessonTextOpenButton.Name = "eduLessonTextOpenButton";
            this.eduLessonTextOpenButton.Size = new System.Drawing.Size(111, 44);
            this.eduLessonTextOpenButton.TabIndex = 2;
            this.eduLessonTextOpenButton.Text = "Open";
            this.eduLessonTextOpenButton.UseVisualStyleBackColor = true;
            this.eduLessonTextOpenButton.Click += new System.EventHandler(this.eduLessonTextOpenButton_Click);
            // 
            // splitter9
            // 
            this.splitter9.Location = new System.Drawing.Point(3, 75);
            this.splitter9.Name = "splitter9";
            this.splitter9.Size = new System.Drawing.Size(3, 200);
            this.splitter9.TabIndex = 15;
            this.splitter9.TabStop = false;
            // 
            // lessonsOrderPanel
            // 
            this.lessonsOrderPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lessonsOrderPanel.Controls.Add(lessonOrderLabel);
            this.lessonsOrderPanel.Controls.Add(this.eduLessonOrderTextBox);
            this.lessonsOrderPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.lessonsOrderPanel.Location = new System.Drawing.Point(3, 28);
            this.lessonsOrderPanel.Name = "lessonsOrderPanel";
            this.lessonsOrderPanel.Size = new System.Drawing.Size(654, 47);
            this.lessonsOrderPanel.TabIndex = 12;
            // 
            // eduLessonOrderTextBox
            // 
            this.eduLessonOrderTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduLessonOrderTextBox.Location = new System.Drawing.Point(112, 13);
            this.eduLessonOrderTextBox.Name = "eduLessonOrderTextBox";
            this.eduLessonOrderTextBox.Size = new System.Drawing.Size(88, 20);
            this.eduLessonOrderTextBox.TabIndex = 13;
            // 
            // eduLessonsBindingNavigator
            // 
            this.eduLessonsBindingNavigator.AddNewItem = this.eduLessonsBindingNavigatorAddNewItem;
            this.eduLessonsBindingNavigator.CountItem = this.toolStripLabel4;
            this.eduLessonsBindingNavigator.DeleteItem = this.eduLessonsBindingNavigatorRemoveItem;
            this.eduLessonsBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton21,
            this.toolStripButton22,
            this.toolStripSeparator10,
            this.toolStripTextBox4,
            this.toolStripLabel4,
            this.toolStripSeparator11,
            this.toolStripButton23,
            this.toolStripButton24,
            this.toolStripSeparator12,
            this.eduLessonsBindingNavigatorAddNewItem,
            this.eduLessonsBindingNavigatorRemoveItem,
            this.eduLessonsBindingNavigatorSaveItem,
            this.eduLessonsBindingNavigatorRefreshItem});
            this.eduLessonsBindingNavigator.Location = new System.Drawing.Point(3, 3);
            this.eduLessonsBindingNavigator.MoveFirstItem = this.toolStripButton21;
            this.eduLessonsBindingNavigator.MoveLastItem = this.toolStripButton24;
            this.eduLessonsBindingNavigator.MoveNextItem = this.toolStripButton23;
            this.eduLessonsBindingNavigator.MovePreviousItem = this.toolStripButton22;
            this.eduLessonsBindingNavigator.Name = "eduLessonsBindingNavigator";
            this.eduLessonsBindingNavigator.PositionItem = this.toolStripTextBox4;
            this.eduLessonsBindingNavigator.Size = new System.Drawing.Size(654, 25);
            this.eduLessonsBindingNavigator.TabIndex = 11;
            // 
            // eduLessonsBindingNavigatorAddNewItem
            // 
            this.eduLessonsBindingNavigatorAddNewItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduLessonsBindingNavigatorAddNewItem.Image = ((System.Drawing.Image)(resources.GetObject("eduLessonsBindingNavigatorAddNewItem.Image")));
            this.eduLessonsBindingNavigatorAddNewItem.Name = "eduLessonsBindingNavigatorAddNewItem";
            this.eduLessonsBindingNavigatorAddNewItem.RightToLeftAutoMirrorImage = true;
            this.eduLessonsBindingNavigatorAddNewItem.Size = new System.Drawing.Size(23, 22);
            this.eduLessonsBindingNavigatorAddNewItem.Text = "Add new";
            // 
            // toolStripLabel4
            // 
            this.toolStripLabel4.Name = "toolStripLabel4";
            this.toolStripLabel4.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel4.Text = "для {0}";
            this.toolStripLabel4.ToolTipText = "Total number of items";
            // 
            // eduLessonsBindingNavigatorRemoveItem
            // 
            this.eduLessonsBindingNavigatorRemoveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduLessonsBindingNavigatorRemoveItem.Image = ((System.Drawing.Image)(resources.GetObject("eduLessonsBindingNavigatorRemoveItem.Image")));
            this.eduLessonsBindingNavigatorRemoveItem.Name = "eduLessonsBindingNavigatorRemoveItem";
            this.eduLessonsBindingNavigatorRemoveItem.RightToLeftAutoMirrorImage = true;
            this.eduLessonsBindingNavigatorRemoveItem.Size = new System.Drawing.Size(23, 22);
            this.eduLessonsBindingNavigatorRemoveItem.Text = "Delete";
            // 
            // toolStripButton21
            // 
            this.toolStripButton21.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton21.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton21.Image")));
            this.toolStripButton21.Name = "toolStripButton21";
            this.toolStripButton21.RightToLeftAutoMirrorImage = true;
            this.toolStripButton21.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton21.Text = "Move first";
            // 
            // toolStripButton22
            // 
            this.toolStripButton22.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton22.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton22.Image")));
            this.toolStripButton22.Name = "toolStripButton22";
            this.toolStripButton22.RightToLeftAutoMirrorImage = true;
            this.toolStripButton22.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton22.Text = "Move previous";
            // 
            // toolStripSeparator10
            // 
            this.toolStripSeparator10.Name = "toolStripSeparator10";
            this.toolStripSeparator10.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox4
            // 
            this.toolStripTextBox4.AccessibleName = "Position";
            this.toolStripTextBox4.AutoSize = false;
            this.toolStripTextBox4.Name = "toolStripTextBox4";
            this.toolStripTextBox4.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox4.Text = "0";
            this.toolStripTextBox4.ToolTipText = "Current position";
            // 
            // toolStripSeparator11
            // 
            this.toolStripSeparator11.Name = "toolStripSeparator11";
            this.toolStripSeparator11.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton23
            // 
            this.toolStripButton23.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton23.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton23.Image")));
            this.toolStripButton23.Name = "toolStripButton23";
            this.toolStripButton23.RightToLeftAutoMirrorImage = true;
            this.toolStripButton23.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton23.Text = "Move next";
            // 
            // toolStripButton24
            // 
            this.toolStripButton24.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton24.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton24.Image")));
            this.toolStripButton24.Name = "toolStripButton24";
            this.toolStripButton24.RightToLeftAutoMirrorImage = true;
            this.toolStripButton24.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton24.Text = "Move last";
            // 
            // toolStripSeparator12
            // 
            this.toolStripSeparator12.Name = "toolStripSeparator12";
            this.toolStripSeparator12.Size = new System.Drawing.Size(6, 25);
            // 
            // eduLessonsBindingNavigatorSaveItem
            // 
            this.eduLessonsBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduLessonsBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("eduLessonsBindingNavigatorSaveItem.Image")));
            this.eduLessonsBindingNavigatorSaveItem.Name = "eduLessonsBindingNavigatorSaveItem";
            this.eduLessonsBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.eduLessonsBindingNavigatorSaveItem.Text = "Save Data";
            this.eduLessonsBindingNavigatorSaveItem.Click += new System.EventHandler(this.eduLessonsBindingNavigatorSaveItem_Click);
            // 
            // eduLessonsBindingNavigatorRefreshItem
            // 
            this.eduLessonsBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduLessonsBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("eduLessonsBindingNavigatorRefreshItem.Image")));
            this.eduLessonsBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.eduLessonsBindingNavigatorRefreshItem.Name = "eduLessonsBindingNavigatorRefreshItem";
            this.eduLessonsBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.eduLessonsBindingNavigatorRefreshItem.Text = "Refresh";
            this.eduLessonsBindingNavigatorRefreshItem.Click += new System.EventHandler(this.eduLessonsBindingNavigatorRefreshItem_Click);
            // 
            // tabQuestions
            // 
            this.tabQuestions.Controls.Add(this.eduQuestionSplitContainer);
            this.tabQuestions.ImageIndex = 1;
            this.tabQuestions.Location = new System.Drawing.Point(4, 23);
            this.tabQuestions.Name = "tabQuestions";
            this.tabQuestions.Padding = new System.Windows.Forms.Padding(3);
            this.tabQuestions.Size = new System.Drawing.Size(660, 278);
            this.tabQuestions.TabIndex = 1;
            this.tabQuestions.Text = "Questions";
            this.tabQuestions.UseVisualStyleBackColor = true;
            // 
            // eduQuestionSplitContainer
            // 
            this.eduQuestionSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduQuestionSplitContainer.Location = new System.Drawing.Point(3, 3);
            this.eduQuestionSplitContainer.Name = "eduQuestionSplitContainer";
            // 
            // eduQuestionSplitContainer.Panel1
            // 
            this.eduQuestionSplitContainer.Panel1.Controls.Add(this.eduQuestionTextPanel);
            this.eduQuestionSplitContainer.Panel1.Controls.Add(this.questionOrderPanel);
            this.eduQuestionSplitContainer.Panel1.Controls.Add(this.eduQuestionsBindingNavigator);
            // 
            // eduQuestionSplitContainer.Panel2
            // 
            this.eduQuestionSplitContainer.Panel2.Controls.Add(this.eduAnswersDataGridView);
            this.eduQuestionSplitContainer.Panel2.Controls.Add(this.eduAnswersBindingNavigator);
            this.eduQuestionSplitContainer.Size = new System.Drawing.Size(654, 272);
            this.eduQuestionSplitContainer.SplitterDistance = 322;
            this.eduQuestionSplitContainer.TabIndex = 5;
            // 
            // eduQuestionTextPanel
            // 
            this.eduQuestionTextPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduQuestionTextPanel.Controls.Add(this.eduQuestionTextClearButton);
            this.eduQuestionTextPanel.Controls.Add(this.eduQuestionRichTextBox);
            this.eduQuestionTextPanel.Controls.Add(this.eduQuestionTextOpenButton);
            this.eduQuestionTextPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduQuestionTextPanel.Location = new System.Drawing.Point(0, 110);
            this.eduQuestionTextPanel.Name = "eduQuestionTextPanel";
            this.eduQuestionTextPanel.Size = new System.Drawing.Size(322, 162);
            this.eduQuestionTextPanel.TabIndex = 27;
            // 
            // eduQuestionTextClearButton
            // 
            this.eduQuestionTextClearButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.eduQuestionTextClearButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.eduQuestionTextClearButton.Image = ((System.Drawing.Image)(resources.GetObject("eduQuestionTextClearButton.Image")));
            this.eduQuestionTextClearButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.eduQuestionTextClearButton.Location = new System.Drawing.Point(5, 107);
            this.eduQuestionTextClearButton.Name = "eduQuestionTextClearButton";
            this.eduQuestionTextClearButton.Size = new System.Drawing.Size(118, 44);
            this.eduQuestionTextClearButton.TabIndex = 3;
            this.eduQuestionTextClearButton.Text = "Clear";
            this.eduQuestionTextClearButton.UseVisualStyleBackColor = true;
            // 
            // eduQuestionRichTextBox
            // 
            this.eduQuestionRichTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.eduQuestionRichTextBox.Location = new System.Drawing.Point(4, 5);
            this.eduQuestionRichTextBox.Name = "eduQuestionRichTextBox";
            this.eduQuestionRichTextBox.Size = new System.Drawing.Size(313, 93);
            this.eduQuestionRichTextBox.TabIndex = 0;
            this.eduQuestionRichTextBox.Text = "";
            // 
            // eduQuestionTextOpenButton
            // 
            this.eduQuestionTextOpenButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.eduQuestionTextOpenButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.eduQuestionTextOpenButton.Image = ((System.Drawing.Image)(resources.GetObject("eduQuestionTextOpenButton.Image")));
            this.eduQuestionTextOpenButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.eduQuestionTextOpenButton.Location = new System.Drawing.Point(129, 107);
            this.eduQuestionTextOpenButton.Name = "eduQuestionTextOpenButton";
            this.eduQuestionTextOpenButton.Size = new System.Drawing.Size(111, 44);
            this.eduQuestionTextOpenButton.TabIndex = 2;
            this.eduQuestionTextOpenButton.Text = "Open";
            this.eduQuestionTextOpenButton.UseVisualStyleBackColor = true;
            // 
            // questionOrderPanel
            // 
            this.questionOrderPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.questionOrderPanel.Controls.Add(rightAnswerIDLabel);
            this.questionOrderPanel.Controls.Add(this.rightAnswerComboBox);
            this.questionOrderPanel.Controls.Add(questionOrderLabel);
            this.questionOrderPanel.Controls.Add(this.eduQuestionOrderTextBox);
            this.questionOrderPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.questionOrderPanel.Location = new System.Drawing.Point(0, 25);
            this.questionOrderPanel.Name = "questionOrderPanel";
            this.questionOrderPanel.Size = new System.Drawing.Size(322, 85);
            this.questionOrderPanel.TabIndex = 26;
            // 
            // rightAnswerComboBox
            // 
            this.rightAnswerComboBox.FormattingEnabled = true;
            this.rightAnswerComboBox.Location = new System.Drawing.Point(102, 44);
            this.rightAnswerComboBox.Name = "rightAnswerComboBox";
            this.rightAnswerComboBox.Size = new System.Drawing.Size(138, 21);
            this.rightAnswerComboBox.TabIndex = 28;
            // 
            // eduQuestionOrderTextBox
            // 
            this.eduQuestionOrderTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduQuestionOrderTextBox.Location = new System.Drawing.Point(102, 18);
            this.eduQuestionOrderTextBox.Name = "eduQuestionOrderTextBox";
            this.eduQuestionOrderTextBox.Size = new System.Drawing.Size(80, 20);
            this.eduQuestionOrderTextBox.TabIndex = 26;
            // 
            // eduQuestionsBindingNavigator
            // 
            this.eduQuestionsBindingNavigator.AddNewItem = this.eduQuestionsBindingNavigatorAddNewItem;
            this.eduQuestionsBindingNavigator.CountItem = this.toolStripLabel5;
            this.eduQuestionsBindingNavigator.DeleteItem = this.eduQuestionsBindingNavigatorRemoveItem;
            this.eduQuestionsBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton27,
            this.toolStripButton28,
            this.toolStripSeparator13,
            this.toolStripTextBox5,
            this.toolStripLabel5,
            this.toolStripSeparator14,
            this.toolStripButton29,
            this.toolStripButton30,
            this.toolStripSeparator15,
            this.eduQuestionsBindingNavigatorAddNewItem,
            this.eduQuestionsBindingNavigatorRemoveItem,
            this.eduQuestionsBindingNavigatorSaveItem,
            this.eduQuestionsBindingNavigatorRefreshItem});
            this.eduQuestionsBindingNavigator.Location = new System.Drawing.Point(0, 0);
            this.eduQuestionsBindingNavigator.MoveFirstItem = this.toolStripButton27;
            this.eduQuestionsBindingNavigator.MoveLastItem = this.toolStripButton30;
            this.eduQuestionsBindingNavigator.MoveNextItem = this.toolStripButton29;
            this.eduQuestionsBindingNavigator.MovePreviousItem = this.toolStripButton28;
            this.eduQuestionsBindingNavigator.Name = "eduQuestionsBindingNavigator";
            this.eduQuestionsBindingNavigator.PositionItem = this.toolStripTextBox5;
            this.eduQuestionsBindingNavigator.Size = new System.Drawing.Size(322, 25);
            this.eduQuestionsBindingNavigator.TabIndex = 13;
            // 
            // eduQuestionsBindingNavigatorAddNewItem
            // 
            this.eduQuestionsBindingNavigatorAddNewItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduQuestionsBindingNavigatorAddNewItem.Image = ((System.Drawing.Image)(resources.GetObject("eduQuestionsBindingNavigatorAddNewItem.Image")));
            this.eduQuestionsBindingNavigatorAddNewItem.Name = "eduQuestionsBindingNavigatorAddNewItem";
            this.eduQuestionsBindingNavigatorAddNewItem.RightToLeftAutoMirrorImage = true;
            this.eduQuestionsBindingNavigatorAddNewItem.Size = new System.Drawing.Size(23, 22);
            this.eduQuestionsBindingNavigatorAddNewItem.Text = "Add new";
            // 
            // toolStripLabel5
            // 
            this.toolStripLabel5.Name = "toolStripLabel5";
            this.toolStripLabel5.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel5.Text = "для {0}";
            this.toolStripLabel5.ToolTipText = "Total number of items";
            // 
            // eduQuestionsBindingNavigatorRemoveItem
            // 
            this.eduQuestionsBindingNavigatorRemoveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduQuestionsBindingNavigatorRemoveItem.Image = ((System.Drawing.Image)(resources.GetObject("eduQuestionsBindingNavigatorRemoveItem.Image")));
            this.eduQuestionsBindingNavigatorRemoveItem.Name = "eduQuestionsBindingNavigatorRemoveItem";
            this.eduQuestionsBindingNavigatorRemoveItem.RightToLeftAutoMirrorImage = true;
            this.eduQuestionsBindingNavigatorRemoveItem.Size = new System.Drawing.Size(23, 22);
            this.eduQuestionsBindingNavigatorRemoveItem.Text = "Delete";
            // 
            // toolStripButton27
            // 
            this.toolStripButton27.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton27.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton27.Image")));
            this.toolStripButton27.Name = "toolStripButton27";
            this.toolStripButton27.RightToLeftAutoMirrorImage = true;
            this.toolStripButton27.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton27.Text = "Move first";
            // 
            // toolStripButton28
            // 
            this.toolStripButton28.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton28.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton28.Image")));
            this.toolStripButton28.Name = "toolStripButton28";
            this.toolStripButton28.RightToLeftAutoMirrorImage = true;
            this.toolStripButton28.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton28.Text = "Move previous";
            // 
            // toolStripSeparator13
            // 
            this.toolStripSeparator13.Name = "toolStripSeparator13";
            this.toolStripSeparator13.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox5
            // 
            this.toolStripTextBox5.AccessibleName = "Position";
            this.toolStripTextBox5.AutoSize = false;
            this.toolStripTextBox5.Name = "toolStripTextBox5";
            this.toolStripTextBox5.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox5.Text = "0";
            this.toolStripTextBox5.ToolTipText = "Current position";
            // 
            // toolStripSeparator14
            // 
            this.toolStripSeparator14.Name = "toolStripSeparator14";
            this.toolStripSeparator14.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton29
            // 
            this.toolStripButton29.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton29.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton29.Image")));
            this.toolStripButton29.Name = "toolStripButton29";
            this.toolStripButton29.RightToLeftAutoMirrorImage = true;
            this.toolStripButton29.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton29.Text = "Move next";
            // 
            // toolStripButton30
            // 
            this.toolStripButton30.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton30.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton30.Image")));
            this.toolStripButton30.Name = "toolStripButton30";
            this.toolStripButton30.RightToLeftAutoMirrorImage = true;
            this.toolStripButton30.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton30.Text = "Move last";
            // 
            // toolStripSeparator15
            // 
            this.toolStripSeparator15.Name = "toolStripSeparator15";
            this.toolStripSeparator15.Size = new System.Drawing.Size(6, 25);
            // 
            // eduQuestionsBindingNavigatorSaveItem
            // 
            this.eduQuestionsBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduQuestionsBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("eduQuestionsBindingNavigatorSaveItem.Image")));
            this.eduQuestionsBindingNavigatorSaveItem.Name = "eduQuestionsBindingNavigatorSaveItem";
            this.eduQuestionsBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.eduQuestionsBindingNavigatorSaveItem.Text = "Save Data";
            this.eduQuestionsBindingNavigatorSaveItem.Click += new System.EventHandler(this.eduQuestionsBindingNavigatorSaveItem_Click);
            // 
            // eduQuestionsBindingNavigatorRefreshItem
            // 
            this.eduQuestionsBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduQuestionsBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("eduQuestionsBindingNavigatorRefreshItem.Image")));
            this.eduQuestionsBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.eduQuestionsBindingNavigatorRefreshItem.Name = "eduQuestionsBindingNavigatorRefreshItem";
            this.eduQuestionsBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.eduQuestionsBindingNavigatorRefreshItem.Text = "Refresh";
            this.eduQuestionsBindingNavigatorRefreshItem.Click += new System.EventHandler(this.eduQuestionsBindingNavigatorRefreshItem_Click);
            // 
            // eduAnswersDataGridView
            // 
            this.eduAnswersDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.eduAnswersDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.eduQuestionAnswerTextColumn,
            this.eduQuestionAnswerOrderColumn});
            this.eduAnswersDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduAnswersDataGridView.Location = new System.Drawing.Point(0, 25);
            this.eduAnswersDataGridView.Name = "eduAnswersDataGridView";
            this.eduAnswersDataGridView.Size = new System.Drawing.Size(328, 247);
            this.eduAnswersDataGridView.TabIndex = 20;
            // 
            // eduQuestionAnswerTextColumn
            // 
            this.eduQuestionAnswerTextColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.eduQuestionAnswerTextColumn.HeaderText = "Answer text";
            this.eduQuestionAnswerTextColumn.Name = "eduQuestionAnswerTextColumn";
            this.eduQuestionAnswerTextColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.eduQuestionAnswerTextColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.eduQuestionAnswerTextColumn.Width = 150;
            // 
            // eduQuestionAnswerOrderColumn
            // 
            this.eduQuestionAnswerOrderColumn.HeaderText = "Order";
            this.eduQuestionAnswerOrderColumn.Name = "eduQuestionAnswerOrderColumn";
            // 
            // eduAnswersBindingNavigator
            // 
            this.eduAnswersBindingNavigator.AddNewItem = this.eduAnswersBindingNavigatorAddItem;
            this.eduAnswersBindingNavigator.CountItem = this.toolStripLabel23;
            this.eduAnswersBindingNavigator.DeleteItem = this.eduAnswersBindingNavigatorRemoveItem;
            this.eduAnswersBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton123,
            this.toolStripButton124,
            this.toolStripSeparator71,
            this.toolStripTextBox23,
            this.toolStripLabel23,
            this.toolStripSeparator72,
            this.toolStripButton125,
            this.toolStripButton126,
            this.toolStripSeparator73,
            this.eduAnswersBindingNavigatorAddItem,
            this.eduAnswersBindingNavigatorRemoveItem,
            this.eduAnswersBindingNavigatorSaveItem,
            this.eduAnswersBindingNavigatorRefreshItem});
            this.eduAnswersBindingNavigator.Location = new System.Drawing.Point(0, 0);
            this.eduAnswersBindingNavigator.MoveFirstItem = this.toolStripButton123;
            this.eduAnswersBindingNavigator.MoveLastItem = this.toolStripButton126;
            this.eduAnswersBindingNavigator.MoveNextItem = this.toolStripButton125;
            this.eduAnswersBindingNavigator.MovePreviousItem = this.toolStripButton124;
            this.eduAnswersBindingNavigator.Name = "eduAnswersBindingNavigator";
            this.eduAnswersBindingNavigator.PositionItem = this.toolStripTextBox23;
            this.eduAnswersBindingNavigator.Size = new System.Drawing.Size(328, 25);
            this.eduAnswersBindingNavigator.TabIndex = 14;
            // 
            // eduAnswersBindingNavigatorAddItem
            // 
            this.eduAnswersBindingNavigatorAddItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduAnswersBindingNavigatorAddItem.Image = ((System.Drawing.Image)(resources.GetObject("eduAnswersBindingNavigatorAddItem.Image")));
            this.eduAnswersBindingNavigatorAddItem.Name = "eduAnswersBindingNavigatorAddItem";
            this.eduAnswersBindingNavigatorAddItem.RightToLeftAutoMirrorImage = true;
            this.eduAnswersBindingNavigatorAddItem.Size = new System.Drawing.Size(23, 22);
            this.eduAnswersBindingNavigatorAddItem.Text = "Add new";
            // 
            // toolStripLabel23
            // 
            this.toolStripLabel23.Name = "toolStripLabel23";
            this.toolStripLabel23.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel23.Text = "для {0}";
            this.toolStripLabel23.ToolTipText = "Total number of items";
            // 
            // eduAnswersBindingNavigatorRemoveItem
            // 
            this.eduAnswersBindingNavigatorRemoveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduAnswersBindingNavigatorRemoveItem.Image = ((System.Drawing.Image)(resources.GetObject("eduAnswersBindingNavigatorRemoveItem.Image")));
            this.eduAnswersBindingNavigatorRemoveItem.Name = "eduAnswersBindingNavigatorRemoveItem";
            this.eduAnswersBindingNavigatorRemoveItem.RightToLeftAutoMirrorImage = true;
            this.eduAnswersBindingNavigatorRemoveItem.Size = new System.Drawing.Size(23, 22);
            this.eduAnswersBindingNavigatorRemoveItem.Text = "Delete";
            // 
            // toolStripButton123
            // 
            this.toolStripButton123.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton123.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton123.Image")));
            this.toolStripButton123.Name = "toolStripButton123";
            this.toolStripButton123.RightToLeftAutoMirrorImage = true;
            this.toolStripButton123.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton123.Text = "Move first";
            // 
            // toolStripButton124
            // 
            this.toolStripButton124.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton124.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton124.Image")));
            this.toolStripButton124.Name = "toolStripButton124";
            this.toolStripButton124.RightToLeftAutoMirrorImage = true;
            this.toolStripButton124.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton124.Text = "Move previous";
            // 
            // toolStripSeparator71
            // 
            this.toolStripSeparator71.Name = "toolStripSeparator71";
            this.toolStripSeparator71.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox23
            // 
            this.toolStripTextBox23.AccessibleName = "Position";
            this.toolStripTextBox23.AutoSize = false;
            this.toolStripTextBox23.Name = "toolStripTextBox23";
            this.toolStripTextBox23.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox23.Text = "0";
            this.toolStripTextBox23.ToolTipText = "Current position";
            // 
            // toolStripSeparator72
            // 
            this.toolStripSeparator72.Name = "toolStripSeparator72";
            this.toolStripSeparator72.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton125
            // 
            this.toolStripButton125.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton125.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton125.Image")));
            this.toolStripButton125.Name = "toolStripButton125";
            this.toolStripButton125.RightToLeftAutoMirrorImage = true;
            this.toolStripButton125.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton125.Text = "Move next";
            // 
            // toolStripButton126
            // 
            this.toolStripButton126.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton126.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton126.Image")));
            this.toolStripButton126.Name = "toolStripButton126";
            this.toolStripButton126.RightToLeftAutoMirrorImage = true;
            this.toolStripButton126.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton126.Text = "Move last";
            // 
            // toolStripSeparator73
            // 
            this.toolStripSeparator73.Name = "toolStripSeparator73";
            this.toolStripSeparator73.Size = new System.Drawing.Size(6, 25);
            // 
            // eduAnswersBindingNavigatorSaveItem
            // 
            this.eduAnswersBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduAnswersBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("eduAnswersBindingNavigatorSaveItem.Image")));
            this.eduAnswersBindingNavigatorSaveItem.Name = "eduAnswersBindingNavigatorSaveItem";
            this.eduAnswersBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.eduAnswersBindingNavigatorSaveItem.Text = "Save Data";
            this.eduAnswersBindingNavigatorSaveItem.Click += new System.EventHandler(this.eduAnswersBindingNavigatorSaveItem_Click);
            // 
            // eduAnswersBindingNavigatorRefreshItem
            // 
            this.eduAnswersBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduAnswersBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("eduAnswersBindingNavigatorRefreshItem.Image")));
            this.eduAnswersBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.eduAnswersBindingNavigatorRefreshItem.Name = "eduAnswersBindingNavigatorRefreshItem";
            this.eduAnswersBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.eduAnswersBindingNavigatorRefreshItem.Text = "Refresh";
            this.eduAnswersBindingNavigatorRefreshItem.Click += new System.EventHandler(this.eduAnswersBindingNavigatorRefreshItem_Click);
            // 
            // tabAnswers
            // 
            this.tabAnswers.Controls.Add(this.generalAnswersListDataGridView);
            this.tabAnswers.Controls.Add(this.eduAllAnswersBindingNavigator);
            this.tabAnswers.ImageIndex = 2;
            this.tabAnswers.Location = new System.Drawing.Point(4, 23);
            this.tabAnswers.Name = "tabAnswers";
            this.tabAnswers.Padding = new System.Windows.Forms.Padding(3);
            this.tabAnswers.Size = new System.Drawing.Size(660, 278);
            this.tabAnswers.TabIndex = 2;
            this.tabAnswers.Text = "Answers";
            this.tabAnswers.UseVisualStyleBackColor = true;
            // 
            // generalAnswersListDataGridView
            // 
            this.generalAnswersListDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.generalAnswersListDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.eduGeneralAnswerTextColumn});
            this.generalAnswersListDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.generalAnswersListDataGridView.Location = new System.Drawing.Point(3, 28);
            this.generalAnswersListDataGridView.Name = "generalAnswersListDataGridView";
            this.generalAnswersListDataGridView.Size = new System.Drawing.Size(654, 247);
            this.generalAnswersListDataGridView.TabIndex = 22;
            // 
            // eduGeneralAnswerTextColumn
            // 
            this.eduGeneralAnswerTextColumn.HeaderText = "Answer text";
            this.eduGeneralAnswerTextColumn.Name = "eduGeneralAnswerTextColumn";
            this.eduGeneralAnswerTextColumn.Width = 300;
            // 
            // eduAllAnswersBindingNavigator
            // 
            this.eduAllAnswersBindingNavigator.AddNewItem = this.eduAllAnswersBindingNavigatorAddItem;
            this.eduAllAnswersBindingNavigator.CountItem = this.toolStripLabel24;
            this.eduAllAnswersBindingNavigator.DeleteItem = this.eduAllAnswersBindingNavigatorRemoveItem;
            this.eduAllAnswersBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton131,
            this.toolStripButton132,
            this.toolStripSeparator74,
            this.toolStripTextBox24,
            this.toolStripLabel24,
            this.toolStripSeparator75,
            this.toolStripButton133,
            this.toolStripButton134,
            this.toolStripSeparator76,
            this.eduAllAnswersBindingNavigatorAddItem,
            this.eduAllAnswersBindingNavigatorRemoveItem,
            this.eduAllAnswersBindingNavigatorSaveItem,
            this.eduAllAnswersBindingNavigatorRefreshItem});
            this.eduAllAnswersBindingNavigator.Location = new System.Drawing.Point(3, 3);
            this.eduAllAnswersBindingNavigator.MoveFirstItem = this.toolStripButton131;
            this.eduAllAnswersBindingNavigator.MoveLastItem = this.toolStripButton134;
            this.eduAllAnswersBindingNavigator.MoveNextItem = this.toolStripButton133;
            this.eduAllAnswersBindingNavigator.MovePreviousItem = this.toolStripButton132;
            this.eduAllAnswersBindingNavigator.Name = "eduAllAnswersBindingNavigator";
            this.eduAllAnswersBindingNavigator.PositionItem = this.toolStripTextBox24;
            this.eduAllAnswersBindingNavigator.Size = new System.Drawing.Size(654, 25);
            this.eduAllAnswersBindingNavigator.TabIndex = 21;
            // 
            // eduAllAnswersBindingNavigatorAddItem
            // 
            this.eduAllAnswersBindingNavigatorAddItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduAllAnswersBindingNavigatorAddItem.Image = ((System.Drawing.Image)(resources.GetObject("eduAllAnswersBindingNavigatorAddItem.Image")));
            this.eduAllAnswersBindingNavigatorAddItem.Name = "eduAllAnswersBindingNavigatorAddItem";
            this.eduAllAnswersBindingNavigatorAddItem.RightToLeftAutoMirrorImage = true;
            this.eduAllAnswersBindingNavigatorAddItem.Size = new System.Drawing.Size(23, 22);
            this.eduAllAnswersBindingNavigatorAddItem.Text = "Add new";
            // 
            // toolStripLabel24
            // 
            this.toolStripLabel24.Name = "toolStripLabel24";
            this.toolStripLabel24.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel24.Text = "для {0}";
            this.toolStripLabel24.ToolTipText = "Total number of items";
            // 
            // eduAllAnswersBindingNavigatorRemoveItem
            // 
            this.eduAllAnswersBindingNavigatorRemoveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduAllAnswersBindingNavigatorRemoveItem.Image = ((System.Drawing.Image)(resources.GetObject("eduAllAnswersBindingNavigatorRemoveItem.Image")));
            this.eduAllAnswersBindingNavigatorRemoveItem.Name = "eduAllAnswersBindingNavigatorRemoveItem";
            this.eduAllAnswersBindingNavigatorRemoveItem.RightToLeftAutoMirrorImage = true;
            this.eduAllAnswersBindingNavigatorRemoveItem.Size = new System.Drawing.Size(23, 22);
            this.eduAllAnswersBindingNavigatorRemoveItem.Text = "Delete";
            // 
            // toolStripButton131
            // 
            this.toolStripButton131.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton131.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton131.Image")));
            this.toolStripButton131.Name = "toolStripButton131";
            this.toolStripButton131.RightToLeftAutoMirrorImage = true;
            this.toolStripButton131.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton131.Text = "Move first";
            // 
            // toolStripButton132
            // 
            this.toolStripButton132.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton132.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton132.Image")));
            this.toolStripButton132.Name = "toolStripButton132";
            this.toolStripButton132.RightToLeftAutoMirrorImage = true;
            this.toolStripButton132.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton132.Text = "Move previous";
            // 
            // toolStripSeparator74
            // 
            this.toolStripSeparator74.Name = "toolStripSeparator74";
            this.toolStripSeparator74.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox24
            // 
            this.toolStripTextBox24.AccessibleName = "Position";
            this.toolStripTextBox24.AutoSize = false;
            this.toolStripTextBox24.Name = "toolStripTextBox24";
            this.toolStripTextBox24.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox24.Text = "0";
            this.toolStripTextBox24.ToolTipText = "Current position";
            // 
            // toolStripSeparator75
            // 
            this.toolStripSeparator75.Name = "toolStripSeparator75";
            this.toolStripSeparator75.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton133
            // 
            this.toolStripButton133.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton133.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton133.Image")));
            this.toolStripButton133.Name = "toolStripButton133";
            this.toolStripButton133.RightToLeftAutoMirrorImage = true;
            this.toolStripButton133.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton133.Text = "Move next";
            // 
            // toolStripButton134
            // 
            this.toolStripButton134.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton134.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton134.Image")));
            this.toolStripButton134.Name = "toolStripButton134";
            this.toolStripButton134.RightToLeftAutoMirrorImage = true;
            this.toolStripButton134.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton134.Text = "Move last";
            // 
            // toolStripSeparator76
            // 
            this.toolStripSeparator76.Name = "toolStripSeparator76";
            this.toolStripSeparator76.Size = new System.Drawing.Size(6, 25);
            // 
            // eduAllAnswersBindingNavigatorSaveItem
            // 
            this.eduAllAnswersBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduAllAnswersBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("eduAllAnswersBindingNavigatorSaveItem.Image")));
            this.eduAllAnswersBindingNavigatorSaveItem.Name = "eduAllAnswersBindingNavigatorSaveItem";
            this.eduAllAnswersBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.eduAllAnswersBindingNavigatorSaveItem.Text = "Save Data";
            this.eduAllAnswersBindingNavigatorSaveItem.Click += new System.EventHandler(this.eduAllAnswersBindingNavigatorSaveItem_Click);
            // 
            // eduAllAnswersBindingNavigatorRefreshItem
            // 
            this.eduAllAnswersBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduAllAnswersBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("eduAllAnswersBindingNavigatorRefreshItem.Image")));
            this.eduAllAnswersBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.eduAllAnswersBindingNavigatorRefreshItem.Name = "eduAllAnswersBindingNavigatorRefreshItem";
            this.eduAllAnswersBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.eduAllAnswersBindingNavigatorRefreshItem.Text = "Refresh";
            this.eduAllAnswersBindingNavigatorRefreshItem.Click += new System.EventHandler(this.eduAllAnswersBindingNavigatorRefreshItem_Click);
            // 
            // splitter8
            // 
            this.splitter8.Location = new System.Drawing.Point(321, 0);
            this.splitter8.Name = "splitter8";
            this.splitter8.Size = new System.Drawing.Size(3, 305);
            this.splitter8.TabIndex = 5;
            this.splitter8.TabStop = false;
            // 
            // eduCategoriesGroupBox
            // 
            this.eduCategoriesGroupBox.Controls.Add(this.eduCategoriesDataGridView);
            this.eduCategoriesGroupBox.Controls.Add(this.eduCategoriesBindingNavigator);
            this.eduCategoriesGroupBox.Dock = System.Windows.Forms.DockStyle.Left;
            this.eduCategoriesGroupBox.Location = new System.Drawing.Point(0, 0);
            this.eduCategoriesGroupBox.Name = "eduCategoriesGroupBox";
            this.eduCategoriesGroupBox.Size = new System.Drawing.Size(321, 305);
            this.eduCategoriesGroupBox.TabIndex = 0;
            this.eduCategoriesGroupBox.TabStop = false;
            this.eduCategoriesGroupBox.Text = "Categories";
            // 
            // eduCategoriesDataGridView
            // 
            this.eduCategoriesDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.eduCategoriesDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.eduCategoriesNameColumn});
            this.eduCategoriesDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduCategoriesDataGridView.Location = new System.Drawing.Point(3, 41);
            this.eduCategoriesDataGridView.Name = "eduCategoriesDataGridView";
            this.eduCategoriesDataGridView.Size = new System.Drawing.Size(315, 261);
            this.eduCategoriesDataGridView.TabIndex = 0;
            this.eduCategoriesDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            // 
            // eduCategoriesNameColumn
            // 
            this.eduCategoriesNameColumn.HeaderText = "Category name";
            this.eduCategoriesNameColumn.Name = "eduCategoriesNameColumn";
            this.eduCategoriesNameColumn.Width = 200;
            // 
            // eduCategoriesBindingNavigator
            // 
            this.eduCategoriesBindingNavigator.AddNewItem = this.toolStripButton13;
            this.eduCategoriesBindingNavigator.CountItem = this.toolStripLabel3;
            this.eduCategoriesBindingNavigator.DeleteItem = this.toolStripButton14;
            this.eduCategoriesBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton15,
            this.toolStripButton16,
            this.toolStripSeparator7,
            this.toolStripTextBox3,
            this.toolStripLabel3,
            this.toolStripSeparator8,
            this.toolStripButton17,
            this.toolStripButton18,
            this.toolStripSeparator9,
            this.toolStripButton13,
            this.toolStripButton14,
            this.eduCategoriesBindingNavigatorSaveItem,
            this.eduCategoriesBindingNavigatorRefreshItem});
            this.eduCategoriesBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.eduCategoriesBindingNavigator.MoveFirstItem = this.toolStripButton15;
            this.eduCategoriesBindingNavigator.MoveLastItem = this.toolStripButton18;
            this.eduCategoriesBindingNavigator.MoveNextItem = this.toolStripButton17;
            this.eduCategoriesBindingNavigator.MovePreviousItem = this.toolStripButton16;
            this.eduCategoriesBindingNavigator.Name = "eduCategoriesBindingNavigator";
            this.eduCategoriesBindingNavigator.PositionItem = this.toolStripTextBox3;
            this.eduCategoriesBindingNavigator.Size = new System.Drawing.Size(315, 25);
            this.eduCategoriesBindingNavigator.TabIndex = 12;
            // 
            // toolStripButton13
            // 
            this.toolStripButton13.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton13.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton13.Image")));
            this.toolStripButton13.Name = "toolStripButton13";
            this.toolStripButton13.RightToLeftAutoMirrorImage = true;
            this.toolStripButton13.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton13.Text = "Add new";
            // 
            // toolStripLabel3
            // 
            this.toolStripLabel3.Name = "toolStripLabel3";
            this.toolStripLabel3.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel3.Text = "для {0}";
            this.toolStripLabel3.ToolTipText = "Total number of items";
            // 
            // toolStripButton14
            // 
            this.toolStripButton14.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton14.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton14.Image")));
            this.toolStripButton14.Name = "toolStripButton14";
            this.toolStripButton14.RightToLeftAutoMirrorImage = true;
            this.toolStripButton14.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton14.Text = "Delete";
            // 
            // toolStripButton15
            // 
            this.toolStripButton15.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton15.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton15.Image")));
            this.toolStripButton15.Name = "toolStripButton15";
            this.toolStripButton15.RightToLeftAutoMirrorImage = true;
            this.toolStripButton15.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton15.Text = "Move first";
            // 
            // toolStripButton16
            // 
            this.toolStripButton16.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton16.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton16.Image")));
            this.toolStripButton16.Name = "toolStripButton16";
            this.toolStripButton16.RightToLeftAutoMirrorImage = true;
            this.toolStripButton16.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton16.Text = "Move previous";
            // 
            // toolStripSeparator7
            // 
            this.toolStripSeparator7.Name = "toolStripSeparator7";
            this.toolStripSeparator7.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox3
            // 
            this.toolStripTextBox3.AccessibleName = "Position";
            this.toolStripTextBox3.AutoSize = false;
            this.toolStripTextBox3.Name = "toolStripTextBox3";
            this.toolStripTextBox3.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox3.Text = "0";
            this.toolStripTextBox3.ToolTipText = "Current position";
            // 
            // toolStripSeparator8
            // 
            this.toolStripSeparator8.Name = "toolStripSeparator8";
            this.toolStripSeparator8.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton17
            // 
            this.toolStripButton17.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton17.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton17.Image")));
            this.toolStripButton17.Name = "toolStripButton17";
            this.toolStripButton17.RightToLeftAutoMirrorImage = true;
            this.toolStripButton17.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton17.Text = "Move next";
            // 
            // toolStripButton18
            // 
            this.toolStripButton18.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton18.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton18.Image")));
            this.toolStripButton18.Name = "toolStripButton18";
            this.toolStripButton18.RightToLeftAutoMirrorImage = true;
            this.toolStripButton18.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton18.Text = "Move last";
            // 
            // toolStripSeparator9
            // 
            this.toolStripSeparator9.Name = "toolStripSeparator9";
            this.toolStripSeparator9.Size = new System.Drawing.Size(6, 25);
            // 
            // eduCategoriesBindingNavigatorSaveItem
            // 
            this.eduCategoriesBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduCategoriesBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("eduCategoriesBindingNavigatorSaveItem.Image")));
            this.eduCategoriesBindingNavigatorSaveItem.Name = "eduCategoriesBindingNavigatorSaveItem";
            this.eduCategoriesBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.eduCategoriesBindingNavigatorSaveItem.Text = "Save Data";
            this.eduCategoriesBindingNavigatorSaveItem.Click += new System.EventHandler(this.eduCategoriesBindingNavigatorSaveItem_Click);
            // 
            // eduCategoriesBindingNavigatorRefreshItem
            // 
            this.eduCategoriesBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduCategoriesBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("eduCategoriesBindingNavigatorRefreshItem.Image")));
            this.eduCategoriesBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.eduCategoriesBindingNavigatorRefreshItem.Name = "eduCategoriesBindingNavigatorRefreshItem";
            this.eduCategoriesBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.eduCategoriesBindingNavigatorRefreshItem.Text = "Refresh";
            this.eduCategoriesBindingNavigatorRefreshItem.Click += new System.EventHandler(this.eduCategoriesBindingNavigatorRefreshItem_Click);
            // 
            // eduButtonsBottomPanel
            // 
            this.eduButtonsBottomPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduButtonsBottomPanel.Controls.Add(this.eduImportFromDBButton);
            this.eduButtonsBottomPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.eduButtonsBottomPanel.Location = new System.Drawing.Point(0, 305);
            this.eduButtonsBottomPanel.Name = "eduButtonsBottomPanel";
            this.eduButtonsBottomPanel.Size = new System.Drawing.Size(992, 37);
            this.eduButtonsBottomPanel.TabIndex = 6;
            // 
            // eduImportFromDBButton
            // 
            this.eduImportFromDBButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.eduImportFromDBButton.Image = ((System.Drawing.Image)(resources.GetObject("eduImportFromDBButton.Image")));
            this.eduImportFromDBButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.eduImportFromDBButton.Location = new System.Drawing.Point(7, 6);
            this.eduImportFromDBButton.Name = "eduImportFromDBButton";
            this.eduImportFromDBButton.Size = new System.Drawing.Size(253, 23);
            this.eduImportFromDBButton.TabIndex = 2;
            this.eduImportFromDBButton.Text = "Import from external database";
            this.eduImportFromDBButton.UseVisualStyleBackColor = true;
            this.eduImportFromDBButton.Click += new System.EventHandler(this.eduImportFromDBButton_Click);
            // 
            // eduTabControl
            // 
            this.eduTabControl.Controls.Add(this.usrEduTabPage);
            this.eduTabControl.Controls.Add(this.usrGroupEduTabPage);
            this.eduTabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduTabControl.ImageList = this.eduImageList;
            this.eduTabControl.Location = new System.Drawing.Point(0, 0);
            this.eduTabControl.Name = "eduTabControl";
            this.eduTabControl.SelectedIndex = 0;
            this.eduTabControl.Size = new System.Drawing.Size(992, 283);
            this.eduTabControl.TabIndex = 4;
            // 
            // usrEduTabPage
            // 
            this.usrEduTabPage.Controls.Add(this.userEducationSplitContainer);
            this.usrEduTabPage.Controls.Add(this.splitter12);
            this.usrEduTabPage.Controls.Add(this.eduUsersGroupBox);
            this.usrEduTabPage.ImageIndex = 0;
            this.usrEduTabPage.Location = new System.Drawing.Point(4, 23);
            this.usrEduTabPage.Name = "usrEduTabPage";
            this.usrEduTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.usrEduTabPage.Size = new System.Drawing.Size(984, 256);
            this.usrEduTabPage.TabIndex = 0;
            this.usrEduTabPage.Text = "User education";
            this.usrEduTabPage.UseVisualStyleBackColor = true;
            // 
            // userEducationSplitContainer
            // 
            this.userEducationSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userEducationSplitContainer.Location = new System.Drawing.Point(259, 3);
            this.userEducationSplitContainer.Name = "userEducationSplitContainer";
            // 
            // userEducationSplitContainer.Panel1
            // 
            this.userEducationSplitContainer.Panel1.Controls.Add(this.eduUserCategoriesGroupBox);
            // 
            // userEducationSplitContainer.Panel2
            // 
            this.userEducationSplitContainer.Panel2.Controls.Add(this.eduUserHistoryGroupBox);
            this.userEducationSplitContainer.Size = new System.Drawing.Size(722, 250);
            this.userEducationSplitContainer.SplitterDistance = 378;
            this.userEducationSplitContainer.TabIndex = 6;
            // 
            // eduUserCategoriesGroupBox
            // 
            this.eduUserCategoriesGroupBox.Controls.Add(this.eduUserCategoriesDataGridView);
            this.eduUserCategoriesGroupBox.Controls.Add(this.eduUserCategoriesBindingNavigator);
            this.eduUserCategoriesGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduUserCategoriesGroupBox.Location = new System.Drawing.Point(0, 0);
            this.eduUserCategoriesGroupBox.Name = "eduUserCategoriesGroupBox";
            this.eduUserCategoriesGroupBox.Size = new System.Drawing.Size(378, 250);
            this.eduUserCategoriesGroupBox.TabIndex = 2;
            this.eduUserCategoriesGroupBox.TabStop = false;
            this.eduUserCategoriesGroupBox.Text = "User categories";
            // 
            // eduUserCategoriesDataGridView
            // 
            this.eduUserCategoriesDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.eduUserCategoriesDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.eduUserCategoryNameColumn,
            this.eduRandomCategoryQuestionsColumn,
            this.eduUserCategOrderColumn});
            this.eduUserCategoriesDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduUserCategoriesDataGridView.Location = new System.Drawing.Point(3, 41);
            this.eduUserCategoriesDataGridView.Name = "eduUserCategoriesDataGridView";
            this.eduUserCategoriesDataGridView.Size = new System.Drawing.Size(372, 206);
            this.eduUserCategoriesDataGridView.TabIndex = 0;
            this.eduUserCategoriesDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            // 
            // eduUserCategoryNameColumn
            // 
            this.eduUserCategoryNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.eduUserCategoryNameColumn.HeaderText = "Category name";
            this.eduUserCategoryNameColumn.Name = "eduUserCategoryNameColumn";
            this.eduUserCategoryNameColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.eduUserCategoryNameColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.eduUserCategoryNameColumn.Width = 200;
            // 
            // eduRandomCategoryQuestionsColumn
            // 
            this.eduRandomCategoryQuestionsColumn.HeaderText = "Random questions";
            this.eduRandomCategoryQuestionsColumn.Name = "eduRandomCategoryQuestionsColumn";
            this.eduRandomCategoryQuestionsColumn.Width = 120;
            // 
            // eduUserCategOrderColumn
            // 
            this.eduUserCategOrderColumn.HeaderText = "Order";
            this.eduUserCategOrderColumn.Name = "eduUserCategOrderColumn";
            // 
            // eduUserCategoriesBindingNavigator
            // 
            this.eduUserCategoriesBindingNavigator.AddNewItem = this.toolStripButton37;
            this.eduUserCategoriesBindingNavigator.CountItem = this.toolStripLabel7;
            this.eduUserCategoriesBindingNavigator.DeleteItem = this.toolStripButton38;
            this.eduUserCategoriesBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton39,
            this.toolStripButton40,
            this.toolStripSeparator19,
            this.toolStripTextBox7,
            this.toolStripLabel7,
            this.toolStripSeparator20,
            this.toolStripButton41,
            this.toolStripButton42,
            this.toolStripSeparator21,
            this.toolStripButton37,
            this.toolStripButton38,
            this.eduUserCategoriesBindingNavigatorSaveItem,
            this.eduUserCategoriesBindingNavigatorRefreshItem});
            this.eduUserCategoriesBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.eduUserCategoriesBindingNavigator.MoveFirstItem = this.toolStripButton39;
            this.eduUserCategoriesBindingNavigator.MoveLastItem = this.toolStripButton42;
            this.eduUserCategoriesBindingNavigator.MoveNextItem = this.toolStripButton41;
            this.eduUserCategoriesBindingNavigator.MovePreviousItem = this.toolStripButton40;
            this.eduUserCategoriesBindingNavigator.Name = "eduUserCategoriesBindingNavigator";
            this.eduUserCategoriesBindingNavigator.PositionItem = this.toolStripTextBox7;
            this.eduUserCategoriesBindingNavigator.Size = new System.Drawing.Size(372, 25);
            this.eduUserCategoriesBindingNavigator.TabIndex = 10;
            // 
            // toolStripButton37
            // 
            this.toolStripButton37.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton37.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton37.Image")));
            this.toolStripButton37.Name = "toolStripButton37";
            this.toolStripButton37.RightToLeftAutoMirrorImage = true;
            this.toolStripButton37.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton37.Text = "Add new";
            // 
            // toolStripLabel7
            // 
            this.toolStripLabel7.Name = "toolStripLabel7";
            this.toolStripLabel7.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel7.Text = "для {0}";
            this.toolStripLabel7.ToolTipText = "Total number of items";
            // 
            // toolStripButton38
            // 
            this.toolStripButton38.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton38.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton38.Image")));
            this.toolStripButton38.Name = "toolStripButton38";
            this.toolStripButton38.RightToLeftAutoMirrorImage = true;
            this.toolStripButton38.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton38.Text = "Delete";
            // 
            // toolStripButton39
            // 
            this.toolStripButton39.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton39.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton39.Image")));
            this.toolStripButton39.Name = "toolStripButton39";
            this.toolStripButton39.RightToLeftAutoMirrorImage = true;
            this.toolStripButton39.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton39.Text = "Move first";
            // 
            // toolStripButton40
            // 
            this.toolStripButton40.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton40.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton40.Image")));
            this.toolStripButton40.Name = "toolStripButton40";
            this.toolStripButton40.RightToLeftAutoMirrorImage = true;
            this.toolStripButton40.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton40.Text = "Move previous";
            // 
            // toolStripSeparator19
            // 
            this.toolStripSeparator19.Name = "toolStripSeparator19";
            this.toolStripSeparator19.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox7
            // 
            this.toolStripTextBox7.AccessibleName = "Position";
            this.toolStripTextBox7.AutoSize = false;
            this.toolStripTextBox7.Name = "toolStripTextBox7";
            this.toolStripTextBox7.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox7.Text = "0";
            this.toolStripTextBox7.ToolTipText = "Current position";
            // 
            // toolStripSeparator20
            // 
            this.toolStripSeparator20.Name = "toolStripSeparator20";
            this.toolStripSeparator20.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton41
            // 
            this.toolStripButton41.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton41.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton41.Image")));
            this.toolStripButton41.Name = "toolStripButton41";
            this.toolStripButton41.RightToLeftAutoMirrorImage = true;
            this.toolStripButton41.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton41.Text = "Move next";
            // 
            // toolStripButton42
            // 
            this.toolStripButton42.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton42.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton42.Image")));
            this.toolStripButton42.Name = "toolStripButton42";
            this.toolStripButton42.RightToLeftAutoMirrorImage = true;
            this.toolStripButton42.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton42.Text = "Move last";
            // 
            // toolStripSeparator21
            // 
            this.toolStripSeparator21.Name = "toolStripSeparator21";
            this.toolStripSeparator21.Size = new System.Drawing.Size(6, 25);
            // 
            // eduUserCategoriesBindingNavigatorSaveItem
            // 
            this.eduUserCategoriesBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduUserCategoriesBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("eduUserCategoriesBindingNavigatorSaveItem.Image")));
            this.eduUserCategoriesBindingNavigatorSaveItem.Name = "eduUserCategoriesBindingNavigatorSaveItem";
            this.eduUserCategoriesBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.eduUserCategoriesBindingNavigatorSaveItem.Text = "Save Data";
            this.eduUserCategoriesBindingNavigatorSaveItem.Click += new System.EventHandler(this.eduUserCategoriesBindingNavigatorSaveItem_Click);
            // 
            // eduUserCategoriesBindingNavigatorRefreshItem
            // 
            this.eduUserCategoriesBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduUserCategoriesBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("eduUserCategoriesBindingNavigatorRefreshItem.Image")));
            this.eduUserCategoriesBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.eduUserCategoriesBindingNavigatorRefreshItem.Name = "eduUserCategoriesBindingNavigatorRefreshItem";
            this.eduUserCategoriesBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.eduUserCategoriesBindingNavigatorRefreshItem.Text = "Refresh";
            this.eduUserCategoriesBindingNavigatorRefreshItem.Click += new System.EventHandler(this.eduUserCategoriesBindingNavigatorRefreshItem_Click);
            // 
            // eduUserHistoryGroupBox
            // 
            this.eduUserHistoryGroupBox.Controls.Add(this.eduUserHistoryDataGridView);
            this.eduUserHistoryGroupBox.Controls.Add(this.eduUserHistoryBindingNavigator);
            this.eduUserHistoryGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduUserHistoryGroupBox.Location = new System.Drawing.Point(0, 0);
            this.eduUserHistoryGroupBox.Name = "eduUserHistoryGroupBox";
            this.eduUserHistoryGroupBox.Size = new System.Drawing.Size(340, 250);
            this.eduUserHistoryGroupBox.TabIndex = 3;
            this.eduUserHistoryGroupBox.TabStop = false;
            this.eduUserHistoryGroupBox.Text = "User education history";
            // 
            // eduUserHistoryDataGridView
            // 
            this.eduUserHistoryDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.eduUserHistoryDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.eduUserQuestionTextColumn,
            this.eduUserAnswerTextColumn,
            this.eduUserCorrectAnswerColumn,
            this.eduUserAnswerDateColumn});
            this.eduUserHistoryDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduUserHistoryDataGridView.Location = new System.Drawing.Point(3, 41);
            this.eduUserHistoryDataGridView.Name = "eduUserHistoryDataGridView";
            this.eduUserHistoryDataGridView.Size = new System.Drawing.Size(334, 206);
            this.eduUserHistoryDataGridView.TabIndex = 11;
            this.eduUserHistoryDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            // 
            // eduUserQuestionTextColumn
            // 
            this.eduUserQuestionTextColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.eduUserQuestionTextColumn.HeaderText = "Question";
            this.eduUserQuestionTextColumn.Name = "eduUserQuestionTextColumn";
            this.eduUserQuestionTextColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.eduUserQuestionTextColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.eduUserQuestionTextColumn.Width = 200;
            // 
            // eduUserAnswerTextColumn
            // 
            this.eduUserAnswerTextColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.eduUserAnswerTextColumn.HeaderText = "Answer";
            this.eduUserAnswerTextColumn.Name = "eduUserAnswerTextColumn";
            this.eduUserAnswerTextColumn.Width = 200;
            // 
            // eduUserCorrectAnswerColumn
            // 
            this.eduUserCorrectAnswerColumn.HeaderText = "Correct";
            this.eduUserCorrectAnswerColumn.Name = "eduUserCorrectAnswerColumn";
            // 
            // eduUserAnswerDateColumn
            // 
            this.eduUserAnswerDateColumn.HeaderText = "Date";
            this.eduUserAnswerDateColumn.Name = "eduUserAnswerDateColumn";
            this.eduUserAnswerDateColumn.Width = 200;
            // 
            // eduUserHistoryBindingNavigator
            // 
            this.eduUserHistoryBindingNavigator.AddNewItem = this.toolStripButton43;
            this.eduUserHistoryBindingNavigator.CountItem = this.toolStripLabel8;
            this.eduUserHistoryBindingNavigator.DeleteItem = this.toolStripButton44;
            this.eduUserHistoryBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton45,
            this.toolStripButton46,
            this.toolStripSeparator22,
            this.toolStripTextBox8,
            this.toolStripLabel8,
            this.toolStripSeparator23,
            this.toolStripButton47,
            this.toolStripButton48,
            this.toolStripSeparator24,
            this.toolStripButton43,
            this.toolStripButton44,
            this.eduUserHistoryBindingNavigatorSaveItem,
            this.eduUserHistoryBindingNavigatorRefreshItem});
            this.eduUserHistoryBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.eduUserHistoryBindingNavigator.MoveFirstItem = this.toolStripButton45;
            this.eduUserHistoryBindingNavigator.MoveLastItem = this.toolStripButton48;
            this.eduUserHistoryBindingNavigator.MoveNextItem = this.toolStripButton47;
            this.eduUserHistoryBindingNavigator.MovePreviousItem = this.toolStripButton46;
            this.eduUserHistoryBindingNavigator.Name = "eduUserHistoryBindingNavigator";
            this.eduUserHistoryBindingNavigator.PositionItem = this.toolStripTextBox8;
            this.eduUserHistoryBindingNavigator.Size = new System.Drawing.Size(334, 25);
            this.eduUserHistoryBindingNavigator.TabIndex = 12;
            // 
            // toolStripButton43
            // 
            this.toolStripButton43.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton43.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton43.Image")));
            this.toolStripButton43.Name = "toolStripButton43";
            this.toolStripButton43.RightToLeftAutoMirrorImage = true;
            this.toolStripButton43.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton43.Text = "Add new";
            // 
            // toolStripLabel8
            // 
            this.toolStripLabel8.Name = "toolStripLabel8";
            this.toolStripLabel8.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel8.Text = "для {0}";
            this.toolStripLabel8.ToolTipText = "Total number of items";
            // 
            // toolStripButton44
            // 
            this.toolStripButton44.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton44.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton44.Image")));
            this.toolStripButton44.Name = "toolStripButton44";
            this.toolStripButton44.RightToLeftAutoMirrorImage = true;
            this.toolStripButton44.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton44.Text = "Delete";
            // 
            // toolStripButton45
            // 
            this.toolStripButton45.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton45.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton45.Image")));
            this.toolStripButton45.Name = "toolStripButton45";
            this.toolStripButton45.RightToLeftAutoMirrorImage = true;
            this.toolStripButton45.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton45.Text = "Move first";
            // 
            // toolStripButton46
            // 
            this.toolStripButton46.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton46.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton46.Image")));
            this.toolStripButton46.Name = "toolStripButton46";
            this.toolStripButton46.RightToLeftAutoMirrorImage = true;
            this.toolStripButton46.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton46.Text = "Move previous";
            // 
            // toolStripSeparator22
            // 
            this.toolStripSeparator22.Name = "toolStripSeparator22";
            this.toolStripSeparator22.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox8
            // 
            this.toolStripTextBox8.AccessibleName = "Position";
            this.toolStripTextBox8.AutoSize = false;
            this.toolStripTextBox8.Name = "toolStripTextBox8";
            this.toolStripTextBox8.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox8.Text = "0";
            this.toolStripTextBox8.ToolTipText = "Current position";
            // 
            // toolStripSeparator23
            // 
            this.toolStripSeparator23.Name = "toolStripSeparator23";
            this.toolStripSeparator23.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton47
            // 
            this.toolStripButton47.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton47.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton47.Image")));
            this.toolStripButton47.Name = "toolStripButton47";
            this.toolStripButton47.RightToLeftAutoMirrorImage = true;
            this.toolStripButton47.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton47.Text = "Move next";
            // 
            // toolStripButton48
            // 
            this.toolStripButton48.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton48.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton48.Image")));
            this.toolStripButton48.Name = "toolStripButton48";
            this.toolStripButton48.RightToLeftAutoMirrorImage = true;
            this.toolStripButton48.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton48.Text = "Move last";
            // 
            // toolStripSeparator24
            // 
            this.toolStripSeparator24.Name = "toolStripSeparator24";
            this.toolStripSeparator24.Size = new System.Drawing.Size(6, 25);
            // 
            // eduUserHistoryBindingNavigatorSaveItem
            // 
            this.eduUserHistoryBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduUserHistoryBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("eduUserHistoryBindingNavigatorSaveItem.Image")));
            this.eduUserHistoryBindingNavigatorSaveItem.Name = "eduUserHistoryBindingNavigatorSaveItem";
            this.eduUserHistoryBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.eduUserHistoryBindingNavigatorSaveItem.Text = "Save Data";
            this.eduUserHistoryBindingNavigatorSaveItem.Click += new System.EventHandler(this.eduUserHistoryBindingNavigatorSaveItem_Click);
            // 
            // eduUserHistoryBindingNavigatorRefreshItem
            // 
            this.eduUserHistoryBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduUserHistoryBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("eduUserHistoryBindingNavigatorRefreshItem.Image")));
            this.eduUserHistoryBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.eduUserHistoryBindingNavigatorRefreshItem.Name = "eduUserHistoryBindingNavigatorRefreshItem";
            this.eduUserHistoryBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.eduUserHistoryBindingNavigatorRefreshItem.Text = "Refresh";
            this.eduUserHistoryBindingNavigatorRefreshItem.Click += new System.EventHandler(this.eduUserHistoryBindingNavigatorRefreshItem_Click);
            // 
            // splitter12
            // 
            this.splitter12.Location = new System.Drawing.Point(256, 3);
            this.splitter12.Name = "splitter12";
            this.splitter12.Size = new System.Drawing.Size(3, 250);
            this.splitter12.TabIndex = 4;
            this.splitter12.TabStop = false;
            // 
            // eduUsersGroupBox
            // 
            this.eduUsersGroupBox.Controls.Add(this.eduUsersDataGridView);
            this.eduUsersGroupBox.Controls.Add(this.eduUsersBindingNavigator);
            this.eduUsersGroupBox.Dock = System.Windows.Forms.DockStyle.Left;
            this.eduUsersGroupBox.Location = new System.Drawing.Point(3, 3);
            this.eduUsersGroupBox.Name = "eduUsersGroupBox";
            this.eduUsersGroupBox.Size = new System.Drawing.Size(253, 250);
            this.eduUsersGroupBox.TabIndex = 0;
            this.eduUsersGroupBox.TabStop = false;
            this.eduUsersGroupBox.Text = "Users";
            // 
            // eduUsersDataGridView
            // 
            this.eduUsersDataGridView.AllowUserToAddRows = false;
            this.eduUsersDataGridView.AllowUserToDeleteRows = false;
            this.eduUsersDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.eduUsersDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.eduUserNameColumn});
            this.eduUsersDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduUsersDataGridView.Location = new System.Drawing.Point(3, 41);
            this.eduUsersDataGridView.Name = "eduUsersDataGridView";
            this.eduUsersDataGridView.ReadOnly = true;
            this.eduUsersDataGridView.Size = new System.Drawing.Size(247, 206);
            this.eduUsersDataGridView.TabIndex = 12;
            this.eduUsersDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.eduUsersDataGridView_CellFormatting);
            this.eduUsersDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            // 
            // eduUserNameColumn
            // 
            this.eduUserNameColumn.HeaderText = "User name";
            this.eduUserNameColumn.Name = "eduUserNameColumn";
            this.eduUserNameColumn.ReadOnly = true;
            this.eduUserNameColumn.Width = 200;
            // 
            // eduUsersBindingNavigator
            // 
            this.eduUsersBindingNavigator.AddNewItem = null;
            this.eduUsersBindingNavigator.CountItem = this.toolStripLabel6;
            this.eduUsersBindingNavigator.DeleteItem = null;
            this.eduUsersBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton33,
            this.toolStripButton34,
            this.toolStripSeparator16,
            this.toolStripTextBox6,
            this.toolStripLabel6,
            this.toolStripSeparator17,
            this.toolStripButton35,
            this.toolStripButton36,
            this.toolStripSeparator18,
            this.eduUsersBindingNavigatorRefreshIntem});
            this.eduUsersBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.eduUsersBindingNavigator.MoveFirstItem = this.toolStripButton33;
            this.eduUsersBindingNavigator.MoveLastItem = this.toolStripButton36;
            this.eduUsersBindingNavigator.MoveNextItem = this.toolStripButton35;
            this.eduUsersBindingNavigator.MovePreviousItem = this.toolStripButton34;
            this.eduUsersBindingNavigator.Name = "eduUsersBindingNavigator";
            this.eduUsersBindingNavigator.PositionItem = this.toolStripTextBox6;
            this.eduUsersBindingNavigator.Size = new System.Drawing.Size(247, 25);
            this.eduUsersBindingNavigator.TabIndex = 11;
            // 
            // toolStripLabel6
            // 
            this.toolStripLabel6.Name = "toolStripLabel6";
            this.toolStripLabel6.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel6.Text = "для {0}";
            this.toolStripLabel6.ToolTipText = "Total number of items";
            // 
            // toolStripButton33
            // 
            this.toolStripButton33.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton33.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton33.Image")));
            this.toolStripButton33.Name = "toolStripButton33";
            this.toolStripButton33.RightToLeftAutoMirrorImage = true;
            this.toolStripButton33.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton33.Text = "Move first";
            // 
            // toolStripButton34
            // 
            this.toolStripButton34.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton34.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton34.Image")));
            this.toolStripButton34.Name = "toolStripButton34";
            this.toolStripButton34.RightToLeftAutoMirrorImage = true;
            this.toolStripButton34.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton34.Text = "Move previous";
            // 
            // toolStripSeparator16
            // 
            this.toolStripSeparator16.Name = "toolStripSeparator16";
            this.toolStripSeparator16.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox6
            // 
            this.toolStripTextBox6.AccessibleName = "Position";
            this.toolStripTextBox6.AutoSize = false;
            this.toolStripTextBox6.Name = "toolStripTextBox6";
            this.toolStripTextBox6.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox6.Text = "0";
            this.toolStripTextBox6.ToolTipText = "Current position";
            // 
            // toolStripSeparator17
            // 
            this.toolStripSeparator17.Name = "toolStripSeparator17";
            this.toolStripSeparator17.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton35
            // 
            this.toolStripButton35.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton35.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton35.Image")));
            this.toolStripButton35.Name = "toolStripButton35";
            this.toolStripButton35.RightToLeftAutoMirrorImage = true;
            this.toolStripButton35.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton35.Text = "Move next";
            // 
            // toolStripButton36
            // 
            this.toolStripButton36.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton36.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton36.Image")));
            this.toolStripButton36.Name = "toolStripButton36";
            this.toolStripButton36.RightToLeftAutoMirrorImage = true;
            this.toolStripButton36.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton36.Text = "Move last";
            // 
            // toolStripSeparator18
            // 
            this.toolStripSeparator18.Name = "toolStripSeparator18";
            this.toolStripSeparator18.Size = new System.Drawing.Size(6, 25);
            // 
            // eduUsersBindingNavigatorRefreshIntem
            // 
            this.eduUsersBindingNavigatorRefreshIntem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduUsersBindingNavigatorRefreshIntem.Image = ((System.Drawing.Image)(resources.GetObject("eduUsersBindingNavigatorRefreshIntem.Image")));
            this.eduUsersBindingNavigatorRefreshIntem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.eduUsersBindingNavigatorRefreshIntem.Name = "eduUsersBindingNavigatorRefreshIntem";
            this.eduUsersBindingNavigatorRefreshIntem.Size = new System.Drawing.Size(23, 22);
            this.eduUsersBindingNavigatorRefreshIntem.Text = "Refresh";
            this.eduUsersBindingNavigatorRefreshIntem.Click += new System.EventHandler(this.eduUsersBindingNavigatorRefreshIntem_Click);
            // 
            // usrGroupEduTabPage
            // 
            this.usrGroupEduTabPage.Controls.Add(this.eduUserGroupCategoriesGroupBox);
            this.usrGroupEduTabPage.Controls.Add(this.splitter31);
            this.usrGroupEduTabPage.Controls.Add(this.eduUserGroupsGroupBox);
            this.usrGroupEduTabPage.ImageIndex = 1;
            this.usrGroupEduTabPage.Location = new System.Drawing.Point(4, 23);
            this.usrGroupEduTabPage.Name = "usrGroupEduTabPage";
            this.usrGroupEduTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.usrGroupEduTabPage.Size = new System.Drawing.Size(984, 256);
            this.usrGroupEduTabPage.TabIndex = 1;
            this.usrGroupEduTabPage.Text = "User group education";
            this.usrGroupEduTabPage.UseVisualStyleBackColor = true;
            // 
            // eduUserGroupCategoriesGroupBox
            // 
            this.eduUserGroupCategoriesGroupBox.Controls.Add(this.eduUserGroupCategoriesDataGridView);
            this.eduUserGroupCategoriesGroupBox.Controls.Add(this.eduUserGroupCategoriesBindingNavigator);
            this.eduUserGroupCategoriesGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduUserGroupCategoriesGroupBox.Location = new System.Drawing.Point(465, 3);
            this.eduUserGroupCategoriesGroupBox.Name = "eduUserGroupCategoriesGroupBox";
            this.eduUserGroupCategoriesGroupBox.Size = new System.Drawing.Size(516, 250);
            this.eduUserGroupCategoriesGroupBox.TabIndex = 3;
            this.eduUserGroupCategoriesGroupBox.TabStop = false;
            this.eduUserGroupCategoriesGroupBox.Text = "User group categories";
            // 
            // eduUserGroupCategoriesDataGridView
            // 
            this.eduUserGroupCategoriesDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.eduUserGroupCategoriesDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.eduUserGroupCategoryNameColumn,
            this.eduUserGroupRandomCategoryQuestionsColumn,
            this.eduUserGroupCategOrderColumn});
            this.eduUserGroupCategoriesDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduUserGroupCategoriesDataGridView.Location = new System.Drawing.Point(3, 41);
            this.eduUserGroupCategoriesDataGridView.Name = "eduUserGroupCategoriesDataGridView";
            this.eduUserGroupCategoriesDataGridView.Size = new System.Drawing.Size(510, 206);
            this.eduUserGroupCategoriesDataGridView.TabIndex = 0;
            // 
            // eduUserGroupCategoryNameColumn
            // 
            this.eduUserGroupCategoryNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.eduUserGroupCategoryNameColumn.HeaderText = "Category name";
            this.eduUserGroupCategoryNameColumn.Name = "eduUserGroupCategoryNameColumn";
            this.eduUserGroupCategoryNameColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.eduUserGroupCategoryNameColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.eduUserGroupCategoryNameColumn.Width = 200;
            // 
            // eduUserGroupRandomCategoryQuestionsColumn
            // 
            this.eduUserGroupRandomCategoryQuestionsColumn.HeaderText = "Random questions";
            this.eduUserGroupRandomCategoryQuestionsColumn.Name = "eduUserGroupRandomCategoryQuestionsColumn";
            this.eduUserGroupRandomCategoryQuestionsColumn.Width = 120;
            // 
            // eduUserGroupCategOrderColumn
            // 
            this.eduUserGroupCategOrderColumn.HeaderText = "Order";
            this.eduUserGroupCategOrderColumn.Name = "eduUserGroupCategOrderColumn";
            // 
            // eduUserGroupCategoriesBindingNavigator
            // 
            this.eduUserGroupCategoriesBindingNavigator.AddNewItem = this.toolStripButton81;
            this.eduUserGroupCategoriesBindingNavigator.CountItem = this.toolStripLabel18;
            this.eduUserGroupCategoriesBindingNavigator.DeleteItem = this.toolStripButton82;
            this.eduUserGroupCategoriesBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton83,
            this.toolStripButton90,
            this.toolStripSeparator54,
            this.toolStripTextBox18,
            this.toolStripLabel18,
            this.toolStripSeparator55,
            this.toolStripButton97,
            this.toolStripButton98,
            this.toolStripSeparator57,
            this.toolStripButton81,
            this.toolStripButton82,
            this.eduUserGroupCategoriesBindingNavigatorSaveItem,
            this.eduUserGroupCategoriesBindingNavigatorRefreshItem});
            this.eduUserGroupCategoriesBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.eduUserGroupCategoriesBindingNavigator.MoveFirstItem = this.toolStripButton83;
            this.eduUserGroupCategoriesBindingNavigator.MoveLastItem = this.toolStripButton98;
            this.eduUserGroupCategoriesBindingNavigator.MoveNextItem = this.toolStripButton97;
            this.eduUserGroupCategoriesBindingNavigator.MovePreviousItem = this.toolStripButton90;
            this.eduUserGroupCategoriesBindingNavigator.Name = "eduUserGroupCategoriesBindingNavigator";
            this.eduUserGroupCategoriesBindingNavigator.PositionItem = this.toolStripTextBox18;
            this.eduUserGroupCategoriesBindingNavigator.Size = new System.Drawing.Size(510, 25);
            this.eduUserGroupCategoriesBindingNavigator.TabIndex = 10;
            // 
            // toolStripButton81
            // 
            this.toolStripButton81.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton81.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton81.Image")));
            this.toolStripButton81.Name = "toolStripButton81";
            this.toolStripButton81.RightToLeftAutoMirrorImage = true;
            this.toolStripButton81.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton81.Text = "Add new";
            // 
            // toolStripLabel18
            // 
            this.toolStripLabel18.Name = "toolStripLabel18";
            this.toolStripLabel18.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel18.Text = "для {0}";
            this.toolStripLabel18.ToolTipText = "Total number of items";
            // 
            // toolStripButton82
            // 
            this.toolStripButton82.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton82.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton82.Image")));
            this.toolStripButton82.Name = "toolStripButton82";
            this.toolStripButton82.RightToLeftAutoMirrorImage = true;
            this.toolStripButton82.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton82.Text = "Delete";
            // 
            // toolStripButton83
            // 
            this.toolStripButton83.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton83.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton83.Image")));
            this.toolStripButton83.Name = "toolStripButton83";
            this.toolStripButton83.RightToLeftAutoMirrorImage = true;
            this.toolStripButton83.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton83.Text = "Move first";
            // 
            // toolStripButton90
            // 
            this.toolStripButton90.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton90.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton90.Image")));
            this.toolStripButton90.Name = "toolStripButton90";
            this.toolStripButton90.RightToLeftAutoMirrorImage = true;
            this.toolStripButton90.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton90.Text = "Move previous";
            // 
            // toolStripSeparator54
            // 
            this.toolStripSeparator54.Name = "toolStripSeparator54";
            this.toolStripSeparator54.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox18
            // 
            this.toolStripTextBox18.AccessibleName = "Position";
            this.toolStripTextBox18.AutoSize = false;
            this.toolStripTextBox18.Name = "toolStripTextBox18";
            this.toolStripTextBox18.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox18.Text = "0";
            this.toolStripTextBox18.ToolTipText = "Current position";
            // 
            // toolStripSeparator55
            // 
            this.toolStripSeparator55.Name = "toolStripSeparator55";
            this.toolStripSeparator55.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton97
            // 
            this.toolStripButton97.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton97.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton97.Image")));
            this.toolStripButton97.Name = "toolStripButton97";
            this.toolStripButton97.RightToLeftAutoMirrorImage = true;
            this.toolStripButton97.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton97.Text = "Move next";
            // 
            // toolStripButton98
            // 
            this.toolStripButton98.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton98.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton98.Image")));
            this.toolStripButton98.Name = "toolStripButton98";
            this.toolStripButton98.RightToLeftAutoMirrorImage = true;
            this.toolStripButton98.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton98.Text = "Move last";
            // 
            // toolStripSeparator57
            // 
            this.toolStripSeparator57.Name = "toolStripSeparator57";
            this.toolStripSeparator57.Size = new System.Drawing.Size(6, 25);
            // 
            // eduUserGroupCategoriesBindingNavigatorSaveItem
            // 
            this.eduUserGroupCategoriesBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduUserGroupCategoriesBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("eduUserGroupCategoriesBindingNavigatorSaveItem.Image")));
            this.eduUserGroupCategoriesBindingNavigatorSaveItem.Name = "eduUserGroupCategoriesBindingNavigatorSaveItem";
            this.eduUserGroupCategoriesBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.eduUserGroupCategoriesBindingNavigatorSaveItem.Text = "Save Data";
            this.eduUserGroupCategoriesBindingNavigatorSaveItem.Click += new System.EventHandler(this.eduUserGroupCategoriesBindingNavigatorSaveItem_Click);
            // 
            // eduUserGroupCategoriesBindingNavigatorRefreshItem
            // 
            this.eduUserGroupCategoriesBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduUserGroupCategoriesBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("eduUserGroupCategoriesBindingNavigatorRefreshItem.Image")));
            this.eduUserGroupCategoriesBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.eduUserGroupCategoriesBindingNavigatorRefreshItem.Name = "eduUserGroupCategoriesBindingNavigatorRefreshItem";
            this.eduUserGroupCategoriesBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.eduUserGroupCategoriesBindingNavigatorRefreshItem.Text = "Refresh";
            this.eduUserGroupCategoriesBindingNavigatorRefreshItem.Click += new System.EventHandler(this.eduUserGroupCategoriesBindingNavigatorRefreshItem_Click);
            // 
            // splitter31
            // 
            this.splitter31.Location = new System.Drawing.Point(462, 3);
            this.splitter31.Name = "splitter31";
            this.splitter31.Size = new System.Drawing.Size(3, 250);
            this.splitter31.TabIndex = 2;
            this.splitter31.TabStop = false;
            // 
            // eduUserGroupsGroupBox
            // 
            this.eduUserGroupsGroupBox.Controls.Add(this.eduUserGroupsDataGridView);
            this.eduUserGroupsGroupBox.Controls.Add(this.eduUserGroupsBindingNavigator);
            this.eduUserGroupsGroupBox.Dock = System.Windows.Forms.DockStyle.Left;
            this.eduUserGroupsGroupBox.Location = new System.Drawing.Point(3, 3);
            this.eduUserGroupsGroupBox.Name = "eduUserGroupsGroupBox";
            this.eduUserGroupsGroupBox.Size = new System.Drawing.Size(459, 250);
            this.eduUserGroupsGroupBox.TabIndex = 1;
            this.eduUserGroupsGroupBox.TabStop = false;
            this.eduUserGroupsGroupBox.Text = "User groups";
            // 
            // eduUserGroupsDataGridView
            // 
            this.eduUserGroupsDataGridView.AllowUserToAddRows = false;
            this.eduUserGroupsDataGridView.AllowUserToDeleteRows = false;
            this.eduUserGroupsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.eduUserGroupsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.eduGroupNameColumn,
            this.eduGroupDescriptionColumn});
            this.eduUserGroupsDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eduUserGroupsDataGridView.Location = new System.Drawing.Point(3, 41);
            this.eduUserGroupsDataGridView.Name = "eduUserGroupsDataGridView";
            this.eduUserGroupsDataGridView.ReadOnly = true;
            this.eduUserGroupsDataGridView.Size = new System.Drawing.Size(453, 206);
            this.eduUserGroupsDataGridView.TabIndex = 12;
            this.eduUserGroupsDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.eduUserGroupsDataGridView_CellFormatting);
            this.eduUserGroupsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            // 
            // eduGroupNameColumn
            // 
            this.eduGroupNameColumn.HeaderText = "Group name";
            this.eduGroupNameColumn.Name = "eduGroupNameColumn";
            this.eduGroupNameColumn.ReadOnly = true;
            this.eduGroupNameColumn.Width = 150;
            // 
            // eduGroupDescriptionColumn
            // 
            this.eduGroupDescriptionColumn.HeaderText = "Description";
            this.eduGroupDescriptionColumn.Name = "eduGroupDescriptionColumn";
            this.eduGroupDescriptionColumn.ReadOnly = true;
            this.eduGroupDescriptionColumn.Width = 250;
            // 
            // eduUserGroupsBindingNavigator
            // 
            this.eduUserGroupsBindingNavigator.AddNewItem = null;
            this.eduUserGroupsBindingNavigator.CountItem = this.toolStripLabel15;
            this.eduUserGroupsBindingNavigator.DeleteItem = null;
            this.eduUserGroupsBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton72,
            this.toolStripButton78,
            this.toolStripSeparator45,
            this.toolStripTextBox15,
            this.toolStripLabel15,
            this.toolStripSeparator46,
            this.toolStripButton79,
            this.toolStripButton80,
            this.toolStripSeparator53,
            this.eduUserGroupsBindingNavigatorRefreshIntem});
            this.eduUserGroupsBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.eduUserGroupsBindingNavigator.MoveFirstItem = this.toolStripButton72;
            this.eduUserGroupsBindingNavigator.MoveLastItem = this.toolStripButton80;
            this.eduUserGroupsBindingNavigator.MoveNextItem = this.toolStripButton79;
            this.eduUserGroupsBindingNavigator.MovePreviousItem = this.toolStripButton78;
            this.eduUserGroupsBindingNavigator.Name = "eduUserGroupsBindingNavigator";
            this.eduUserGroupsBindingNavigator.PositionItem = this.toolStripTextBox15;
            this.eduUserGroupsBindingNavigator.Size = new System.Drawing.Size(453, 25);
            this.eduUserGroupsBindingNavigator.TabIndex = 11;
            // 
            // toolStripLabel15
            // 
            this.toolStripLabel15.Name = "toolStripLabel15";
            this.toolStripLabel15.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel15.Text = "для {0}";
            this.toolStripLabel15.ToolTipText = "Total number of items";
            // 
            // toolStripButton72
            // 
            this.toolStripButton72.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton72.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton72.Image")));
            this.toolStripButton72.Name = "toolStripButton72";
            this.toolStripButton72.RightToLeftAutoMirrorImage = true;
            this.toolStripButton72.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton72.Text = "Move first";
            // 
            // toolStripButton78
            // 
            this.toolStripButton78.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton78.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton78.Image")));
            this.toolStripButton78.Name = "toolStripButton78";
            this.toolStripButton78.RightToLeftAutoMirrorImage = true;
            this.toolStripButton78.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton78.Text = "Move previous";
            // 
            // toolStripSeparator45
            // 
            this.toolStripSeparator45.Name = "toolStripSeparator45";
            this.toolStripSeparator45.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox15
            // 
            this.toolStripTextBox15.AccessibleName = "Position";
            this.toolStripTextBox15.AutoSize = false;
            this.toolStripTextBox15.Name = "toolStripTextBox15";
            this.toolStripTextBox15.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox15.Text = "0";
            this.toolStripTextBox15.ToolTipText = "Current position";
            // 
            // toolStripSeparator46
            // 
            this.toolStripSeparator46.Name = "toolStripSeparator46";
            this.toolStripSeparator46.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton79
            // 
            this.toolStripButton79.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton79.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton79.Image")));
            this.toolStripButton79.Name = "toolStripButton79";
            this.toolStripButton79.RightToLeftAutoMirrorImage = true;
            this.toolStripButton79.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton79.Text = "Move next";
            // 
            // toolStripButton80
            // 
            this.toolStripButton80.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton80.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton80.Image")));
            this.toolStripButton80.Name = "toolStripButton80";
            this.toolStripButton80.RightToLeftAutoMirrorImage = true;
            this.toolStripButton80.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton80.Text = "Move last";
            // 
            // toolStripSeparator53
            // 
            this.toolStripSeparator53.Name = "toolStripSeparator53";
            this.toolStripSeparator53.Size = new System.Drawing.Size(6, 25);
            // 
            // eduUserGroupsBindingNavigatorRefreshIntem
            // 
            this.eduUserGroupsBindingNavigatorRefreshIntem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.eduUserGroupsBindingNavigatorRefreshIntem.Image = ((System.Drawing.Image)(resources.GetObject("eduUserGroupsBindingNavigatorRefreshIntem.Image")));
            this.eduUserGroupsBindingNavigatorRefreshIntem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.eduUserGroupsBindingNavigatorRefreshIntem.Name = "eduUserGroupsBindingNavigatorRefreshIntem";
            this.eduUserGroupsBindingNavigatorRefreshIntem.Size = new System.Drawing.Size(23, 22);
            this.eduUserGroupsBindingNavigatorRefreshIntem.Text = "Refresh";
            this.eduUserGroupsBindingNavigatorRefreshIntem.Click += new System.EventHandler(this.eduUserGroupsBindingNavigatorRefreshIntem_Click);
            // 
            // eduImageList
            // 
            this.eduImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("eduImageList.ImageStream")));
            this.eduImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.eduImageList.Images.SetKeyName(0, "user.png");
            this.eduImageList.Images.SetKeyName(1, "users.png");
            // 
            // notificationTabPage
            // 
            this.notificationTabPage.Controls.Add(this.notificationSplitContainer);
            this.notificationTabPage.ImageIndex = 3;
            this.notificationTabPage.Location = new System.Drawing.Point(4, 42);
            this.notificationTabPage.Name = "notificationTabPage";
            this.notificationTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.notificationTabPage.Size = new System.Drawing.Size(1000, 637);
            this.notificationTabPage.TabIndex = 3;
            this.notificationTabPage.Text = "Notification management";
            this.notificationTabPage.UseVisualStyleBackColor = true;
            // 
            // notificationSplitContainer
            // 
            this.notificationSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.notificationSplitContainer.Location = new System.Drawing.Point(3, 3);
            this.notificationSplitContainer.Name = "notificationSplitContainer";
            this.notificationSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // notificationSplitContainer.Panel1
            // 
            this.notificationSplitContainer.Panel1.Controls.Add(this.splitter15);
            this.notificationSplitContainer.Panel1.Controls.Add(this.noticesImageTextPanel);
            this.notificationSplitContainer.Panel1.Controls.Add(this.noticesTopPanel);
            this.notificationSplitContainer.Panel1.Controls.Add(this.notificationBindingNavigator);
            // 
            // notificationSplitContainer.Panel2
            // 
            this.notificationSplitContainer.Panel2.Controls.Add(this.notificationsTabControl);
            this.notificationSplitContainer.Size = new System.Drawing.Size(994, 631);
            this.notificationSplitContainer.SplitterDistance = 277;
            this.notificationSplitContainer.TabIndex = 0;
            // 
            // splitter15
            // 
            this.splitter15.Location = new System.Drawing.Point(314, 25);
            this.splitter15.Name = "splitter15";
            this.splitter15.Size = new System.Drawing.Size(3, 252);
            this.splitter15.TabIndex = 15;
            this.splitter15.TabStop = false;
            // 
            // noticesImageTextPanel
            // 
            this.noticesImageTextPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.noticesImageTextPanel.Controls.Add(this.noticeValuesSplitContainer);
            this.noticesImageTextPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.noticesImageTextPanel.Location = new System.Drawing.Point(314, 25);
            this.noticesImageTextPanel.Name = "noticesImageTextPanel";
            this.noticesImageTextPanel.Size = new System.Drawing.Size(680, 252);
            this.noticesImageTextPanel.TabIndex = 0;
            // 
            // noticeValuesSplitContainer
            // 
            this.noticeValuesSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.noticeValuesSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.noticeValuesSplitContainer.Name = "noticeValuesSplitContainer";
            // 
            // noticeValuesSplitContainer.Panel1
            // 
            this.noticeValuesSplitContainer.Panel1.Controls.Add(this.notificationPicturePanel);
            // 
            // noticeValuesSplitContainer.Panel2
            // 
            this.noticeValuesSplitContainer.Panel2.Controls.Add(this.notificationTextPanel);
            this.noticeValuesSplitContainer.Size = new System.Drawing.Size(678, 250);
            this.noticeValuesSplitContainer.SplitterDistance = 337;
            this.noticeValuesSplitContainer.TabIndex = 18;
            // 
            // notificationPicturePanel
            // 
            this.notificationPicturePanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.notificationPicturePanel.Controls.Add(this.noticesImageClearBtn);
            this.notificationPicturePanel.Controls.Add(this.noticesImageOpenBtn);
            this.notificationPicturePanel.Controls.Add(this.notificationPictureBox);
            this.notificationPicturePanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.notificationPicturePanel.Location = new System.Drawing.Point(0, 0);
            this.notificationPicturePanel.Name = "notificationPicturePanel";
            this.notificationPicturePanel.Size = new System.Drawing.Size(337, 250);
            this.notificationPicturePanel.TabIndex = 15;
            // 
            // noticesImageClearBtn
            // 
            this.noticesImageClearBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.noticesImageClearBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.noticesImageClearBtn.Image = ((System.Drawing.Image)(resources.GetObject("noticesImageClearBtn.Image")));
            this.noticesImageClearBtn.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.noticesImageClearBtn.Location = new System.Drawing.Point(7, 198);
            this.noticesImageClearBtn.Name = "noticesImageClearBtn";
            this.noticesImageClearBtn.Size = new System.Drawing.Size(108, 44);
            this.noticesImageClearBtn.TabIndex = 2;
            this.noticesImageClearBtn.Text = "Clear";
            this.noticesImageClearBtn.UseVisualStyleBackColor = true;
            this.noticesImageClearBtn.Click += new System.EventHandler(this.noticesImageClearBtn_Click);
            // 
            // noticesImageOpenBtn
            // 
            this.noticesImageOpenBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.noticesImageOpenBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.noticesImageOpenBtn.Image = ((System.Drawing.Image)(resources.GetObject("noticesImageOpenBtn.Image")));
            this.noticesImageOpenBtn.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.noticesImageOpenBtn.Location = new System.Drawing.Point(121, 198);
            this.noticesImageOpenBtn.Name = "noticesImageOpenBtn";
            this.noticesImageOpenBtn.Size = new System.Drawing.Size(111, 44);
            this.noticesImageOpenBtn.TabIndex = 1;
            this.noticesImageOpenBtn.Text = "Open";
            this.noticesImageOpenBtn.UseVisualStyleBackColor = true;
            this.noticesImageOpenBtn.Click += new System.EventHandler(this.noticesImageOpenBtn_Click);
            // 
            // notificationPictureBox
            // 
            this.notificationPictureBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.notificationPictureBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.notificationPictureBox.Location = new System.Drawing.Point(4, 6);
            this.notificationPictureBox.Name = "notificationPictureBox";
            this.notificationPictureBox.Size = new System.Drawing.Size(325, 185);
            this.notificationPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.notificationPictureBox.TabIndex = 0;
            this.notificationPictureBox.TabStop = false;
            // 
            // notificationTextPanel
            // 
            this.notificationTextPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.notificationTextPanel.Controls.Add(this.noticesTextClearBtn);
            this.notificationTextPanel.Controls.Add(this.notificationRichTextBox);
            this.notificationTextPanel.Controls.Add(this.noticesTextOpenBtn);
            this.notificationTextPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.notificationTextPanel.Location = new System.Drawing.Point(0, 0);
            this.notificationTextPanel.Name = "notificationTextPanel";
            this.notificationTextPanel.Size = new System.Drawing.Size(337, 250);
            this.notificationTextPanel.TabIndex = 16;
            // 
            // noticesTextClearBtn
            // 
            this.noticesTextClearBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.noticesTextClearBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.noticesTextClearBtn.Image = ((System.Drawing.Image)(resources.GetObject("noticesTextClearBtn.Image")));
            this.noticesTextClearBtn.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.noticesTextClearBtn.Location = new System.Drawing.Point(7, 198);
            this.noticesTextClearBtn.Name = "noticesTextClearBtn";
            this.noticesTextClearBtn.Size = new System.Drawing.Size(111, 44);
            this.noticesTextClearBtn.TabIndex = 3;
            this.noticesTextClearBtn.Text = "Clear";
            this.noticesTextClearBtn.UseVisualStyleBackColor = true;
            this.noticesTextClearBtn.Click += new System.EventHandler(this.noticesTextClearBtn_Click);
            // 
            // notificationRichTextBox
            // 
            this.notificationRichTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.notificationRichTextBox.Location = new System.Drawing.Point(4, 5);
            this.notificationRichTextBox.Name = "notificationRichTextBox";
            this.notificationRichTextBox.Size = new System.Drawing.Size(325, 186);
            this.notificationRichTextBox.TabIndex = 0;
            this.notificationRichTextBox.Text = "";
            // 
            // noticesTextOpenBtn
            // 
            this.noticesTextOpenBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.noticesTextOpenBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.noticesTextOpenBtn.Image = ((System.Drawing.Image)(resources.GetObject("noticesTextOpenBtn.Image")));
            this.noticesTextOpenBtn.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.noticesTextOpenBtn.Location = new System.Drawing.Point(124, 198);
            this.noticesTextOpenBtn.Name = "noticesTextOpenBtn";
            this.noticesTextOpenBtn.Size = new System.Drawing.Size(111, 44);
            this.noticesTextOpenBtn.TabIndex = 2;
            this.noticesTextOpenBtn.Text = "Open";
            this.noticesTextOpenBtn.UseVisualStyleBackColor = true;
            this.noticesTextOpenBtn.Click += new System.EventHandler(this.noticesTextOpenBtn_Click);
            // 
            // noticesTopPanel
            // 
            this.noticesTopPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.noticesTopPanel.Controls.Add(this.noticeScopeLabel);
            this.noticesTopPanel.Controls.Add(this.noticeDisplayTypeLabel);
            this.noticesTopPanel.Controls.Add(this.noticeTypeLabel);
            this.noticesTopPanel.Controls.Add(this.noticeScopesComboBox);
            this.noticesTopPanel.Controls.Add(this.noticeDisplayTypeComboBox);
            this.noticesTopPanel.Controls.Add(this.noticeTypeComboBox);
            this.noticesTopPanel.Dock = System.Windows.Forms.DockStyle.Left;
            this.noticesTopPanel.Location = new System.Drawing.Point(0, 25);
            this.noticesTopPanel.Name = "noticesTopPanel";
            this.noticesTopPanel.Size = new System.Drawing.Size(314, 252);
            this.noticesTopPanel.TabIndex = 14;
            // 
            // noticeScopeLabel
            // 
            this.noticeScopeLabel.AutoSize = true;
            this.noticeScopeLabel.Location = new System.Drawing.Point(21, 126);
            this.noticeScopeLabel.Name = "noticeScopeLabel";
            this.noticeScopeLabel.Size = new System.Drawing.Size(73, 13);
            this.noticeScopeLabel.TabIndex = 5;
            this.noticeScopeLabel.Text = "Notice scope:";
            // 
            // noticeDisplayTypeLabel
            // 
            this.noticeDisplayTypeLabel.AutoSize = true;
            this.noticeDisplayTypeLabel.Location = new System.Drawing.Point(21, 79);
            this.noticeDisplayTypeLabel.Name = "noticeDisplayTypeLabel";
            this.noticeDisplayTypeLabel.Size = new System.Drawing.Size(67, 13);
            this.noticeDisplayTypeLabel.TabIndex = 4;
            this.noticeDisplayTypeLabel.Text = "Display type:";
            // 
            // noticeTypeLabel
            // 
            this.noticeTypeLabel.AutoSize = true;
            this.noticeTypeLabel.Location = new System.Drawing.Point(21, 29);
            this.noticeTypeLabel.Name = "noticeTypeLabel";
            this.noticeTypeLabel.Size = new System.Drawing.Size(64, 13);
            this.noticeTypeLabel.TabIndex = 3;
            this.noticeTypeLabel.Text = "Notice type:";
            // 
            // noticeScopesComboBox
            // 
            this.noticeScopesComboBox.FormattingEnabled = true;
            this.noticeScopesComboBox.Location = new System.Drawing.Point(103, 123);
            this.noticeScopesComboBox.Name = "noticeScopesComboBox";
            this.noticeScopesComboBox.Size = new System.Drawing.Size(184, 21);
            this.noticeScopesComboBox.TabIndex = 2;
            // 
            // noticeDisplayTypeComboBox
            // 
            this.noticeDisplayTypeComboBox.FormattingEnabled = true;
            this.noticeDisplayTypeComboBox.Location = new System.Drawing.Point(103, 76);
            this.noticeDisplayTypeComboBox.Name = "noticeDisplayTypeComboBox";
            this.noticeDisplayTypeComboBox.Size = new System.Drawing.Size(184, 21);
            this.noticeDisplayTypeComboBox.TabIndex = 1;
            // 
            // noticeTypeComboBox
            // 
            this.noticeTypeComboBox.FormattingEnabled = true;
            this.noticeTypeComboBox.Location = new System.Drawing.Point(103, 26);
            this.noticeTypeComboBox.Name = "noticeTypeComboBox";
            this.noticeTypeComboBox.Size = new System.Drawing.Size(184, 21);
            this.noticeTypeComboBox.TabIndex = 0;
            // 
            // notificationBindingNavigator
            // 
            this.notificationBindingNavigator.AddNewItem = this.toolStripButton19;
            this.notificationBindingNavigator.CountItem = this.toolStripLabel9;
            this.notificationBindingNavigator.DeleteItem = this.toolStripButton20;
            this.notificationBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton25,
            this.toolStripButton26,
            this.toolStripSeparator25,
            this.toolStripTextBox9,
            this.toolStripLabel9,
            this.toolStripSeparator26,
            this.toolStripButton31,
            this.toolStripButton32,
            this.toolStripSeparator27,
            this.toolStripButton19,
            this.toolStripButton20,
            this.notificationBindingNavigatorSaveItem,
            this.notificationBindingNavigatorRefreshItem});
            this.notificationBindingNavigator.Location = new System.Drawing.Point(0, 0);
            this.notificationBindingNavigator.MoveFirstItem = this.toolStripButton25;
            this.notificationBindingNavigator.MoveLastItem = this.toolStripButton32;
            this.notificationBindingNavigator.MoveNextItem = this.toolStripButton31;
            this.notificationBindingNavigator.MovePreviousItem = this.toolStripButton26;
            this.notificationBindingNavigator.Name = "notificationBindingNavigator";
            this.notificationBindingNavigator.PositionItem = this.toolStripTextBox9;
            this.notificationBindingNavigator.Size = new System.Drawing.Size(994, 25);
            this.notificationBindingNavigator.TabIndex = 13;
            // 
            // toolStripButton19
            // 
            this.toolStripButton19.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton19.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton19.Image")));
            this.toolStripButton19.Name = "toolStripButton19";
            this.toolStripButton19.RightToLeftAutoMirrorImage = true;
            this.toolStripButton19.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton19.Text = "Add new";
            // 
            // toolStripLabel9
            // 
            this.toolStripLabel9.Name = "toolStripLabel9";
            this.toolStripLabel9.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel9.Text = "для {0}";
            this.toolStripLabel9.ToolTipText = "Total number of items";
            // 
            // toolStripButton20
            // 
            this.toolStripButton20.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton20.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton20.Image")));
            this.toolStripButton20.Name = "toolStripButton20";
            this.toolStripButton20.RightToLeftAutoMirrorImage = true;
            this.toolStripButton20.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton20.Text = "Delete";
            // 
            // toolStripButton25
            // 
            this.toolStripButton25.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton25.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton25.Image")));
            this.toolStripButton25.Name = "toolStripButton25";
            this.toolStripButton25.RightToLeftAutoMirrorImage = true;
            this.toolStripButton25.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton25.Text = "Move first";
            // 
            // toolStripButton26
            // 
            this.toolStripButton26.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton26.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton26.Image")));
            this.toolStripButton26.Name = "toolStripButton26";
            this.toolStripButton26.RightToLeftAutoMirrorImage = true;
            this.toolStripButton26.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton26.Text = "Move previous";
            // 
            // toolStripSeparator25
            // 
            this.toolStripSeparator25.Name = "toolStripSeparator25";
            this.toolStripSeparator25.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox9
            // 
            this.toolStripTextBox9.AccessibleName = "Position";
            this.toolStripTextBox9.AutoSize = false;
            this.toolStripTextBox9.Name = "toolStripTextBox9";
            this.toolStripTextBox9.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox9.Text = "0";
            this.toolStripTextBox9.ToolTipText = "Current position";
            // 
            // toolStripSeparator26
            // 
            this.toolStripSeparator26.Name = "toolStripSeparator26";
            this.toolStripSeparator26.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton31
            // 
            this.toolStripButton31.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton31.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton31.Image")));
            this.toolStripButton31.Name = "toolStripButton31";
            this.toolStripButton31.RightToLeftAutoMirrorImage = true;
            this.toolStripButton31.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton31.Text = "Move next";
            // 
            // toolStripButton32
            // 
            this.toolStripButton32.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton32.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton32.Image")));
            this.toolStripButton32.Name = "toolStripButton32";
            this.toolStripButton32.RightToLeftAutoMirrorImage = true;
            this.toolStripButton32.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton32.Text = "Move last";
            // 
            // toolStripSeparator27
            // 
            this.toolStripSeparator27.Name = "toolStripSeparator27";
            this.toolStripSeparator27.Size = new System.Drawing.Size(6, 25);
            // 
            // notificationBindingNavigatorSaveItem
            // 
            this.notificationBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.notificationBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("notificationBindingNavigatorSaveItem.Image")));
            this.notificationBindingNavigatorSaveItem.Name = "notificationBindingNavigatorSaveItem";
            this.notificationBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.notificationBindingNavigatorSaveItem.Text = "Save Data";
            this.notificationBindingNavigatorSaveItem.Click += new System.EventHandler(this.notificationBindingNavigatorSaveItem_Click);
            // 
            // notificationBindingNavigatorRefreshItem
            // 
            this.notificationBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.notificationBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("notificationBindingNavigatorRefreshItem.Image")));
            this.notificationBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.notificationBindingNavigatorRefreshItem.Name = "notificationBindingNavigatorRefreshItem";
            this.notificationBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.notificationBindingNavigatorRefreshItem.Text = "Refresh";
            this.notificationBindingNavigatorRefreshItem.Click += new System.EventHandler(this.notificationBindingNavigatorRefreshItem_Click);
            // 
            // notificationsTabControl
            // 
            this.notificationsTabControl.Controls.Add(this.userNotificationsTabPage);
            this.notificationsTabControl.Controls.Add(this.userGroupNotificationsTabPage);
            this.notificationsTabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.notificationsTabControl.ImageList = this.eduImageList;
            this.notificationsTabControl.Location = new System.Drawing.Point(0, 0);
            this.notificationsTabControl.Name = "notificationsTabControl";
            this.notificationsTabControl.SelectedIndex = 0;
            this.notificationsTabControl.Size = new System.Drawing.Size(994, 350);
            this.notificationsTabControl.TabIndex = 9;
            // 
            // userNotificationsTabPage
            // 
            this.userNotificationsTabPage.Controls.Add(this.userNotificationSplitContainer);
            this.userNotificationsTabPage.Controls.Add(this.splitter17);
            this.userNotificationsTabPage.Controls.Add(this.notificationUsersGroupBox);
            this.userNotificationsTabPage.ImageIndex = 0;
            this.userNotificationsTabPage.Location = new System.Drawing.Point(4, 23);
            this.userNotificationsTabPage.Name = "userNotificationsTabPage";
            this.userNotificationsTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.userNotificationsTabPage.Size = new System.Drawing.Size(986, 323);
            this.userNotificationsTabPage.TabIndex = 0;
            this.userNotificationsTabPage.Text = "User notifications";
            this.userNotificationsTabPage.UseVisualStyleBackColor = true;
            // 
            // userNotificationSplitContainer
            // 
            this.userNotificationSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userNotificationSplitContainer.Location = new System.Drawing.Point(265, 3);
            this.userNotificationSplitContainer.Name = "userNotificationSplitContainer";
            // 
            // userNotificationSplitContainer.Panel1
            // 
            this.userNotificationSplitContainer.Panel1.Controls.Add(this.userNotificationGroupBox);
            // 
            // userNotificationSplitContainer.Panel2
            // 
            this.userNotificationSplitContainer.Panel2.Controls.Add(this.userNotificationHistoryGroupBox);
            this.userNotificationSplitContainer.Size = new System.Drawing.Size(718, 317);
            this.userNotificationSplitContainer.SplitterDistance = 380;
            this.userNotificationSplitContainer.TabIndex = 9;
            // 
            // userNotificationGroupBox
            // 
            this.userNotificationGroupBox.Controls.Add(this.userNotificationDataGridView);
            this.userNotificationGroupBox.Controls.Add(this.userNotificationBindingNavigator);
            this.userNotificationGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userNotificationGroupBox.Location = new System.Drawing.Point(0, 0);
            this.userNotificationGroupBox.Name = "userNotificationGroupBox";
            this.userNotificationGroupBox.Size = new System.Drawing.Size(380, 317);
            this.userNotificationGroupBox.TabIndex = 5;
            this.userNotificationGroupBox.TabStop = false;
            this.userNotificationGroupBox.Text = "User notifications";
            // 
            // userNotificationDataGridView
            // 
            this.userNotificationDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.userNotificationDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.userNotificationNoticeTextColumn,
            this.userNotificationDisplayTypeColumn});
            this.userNotificationDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userNotificationDataGridView.Location = new System.Drawing.Point(3, 41);
            this.userNotificationDataGridView.Name = "userNotificationDataGridView";
            this.userNotificationDataGridView.Size = new System.Drawing.Size(374, 273);
            this.userNotificationDataGridView.TabIndex = 11;
            // 
            // userNotificationNoticeTextColumn
            // 
            this.userNotificationNoticeTextColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userNotificationNoticeTextColumn.HeaderText = "Notice text";
            this.userNotificationNoticeTextColumn.Name = "userNotificationNoticeTextColumn";
            this.userNotificationNoticeTextColumn.Width = 250;
            // 
            // userNotificationDisplayTypeColumn
            // 
            this.userNotificationDisplayTypeColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userNotificationDisplayTypeColumn.HeaderText = "Notice display type";
            this.userNotificationDisplayTypeColumn.Name = "userNotificationDisplayTypeColumn";
            this.userNotificationDisplayTypeColumn.Width = 150;
            // 
            // userNotificationBindingNavigator
            // 
            this.userNotificationBindingNavigator.AddNewItem = this.toolStripButton54;
            this.userNotificationBindingNavigator.CountItem = this.toolStripLabel11;
            this.userNotificationBindingNavigator.DeleteItem = this.toolStripButton55;
            this.userNotificationBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton56,
            this.toolStripButton57,
            this.toolStripSeparator31,
            this.toolStripTextBox11,
            this.toolStripLabel11,
            this.toolStripSeparator32,
            this.toolStripButton58,
            this.toolStripButton59,
            this.toolStripSeparator33,
            this.toolStripButton54,
            this.toolStripButton55,
            this.userNotificationBindingNavigatorSaveItem,
            this.userNotificationBindingNavigatorRefreshItem});
            this.userNotificationBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.userNotificationBindingNavigator.MoveFirstItem = this.toolStripButton56;
            this.userNotificationBindingNavigator.MoveLastItem = this.toolStripButton59;
            this.userNotificationBindingNavigator.MoveNextItem = this.toolStripButton58;
            this.userNotificationBindingNavigator.MovePreviousItem = this.toolStripButton57;
            this.userNotificationBindingNavigator.Name = "userNotificationBindingNavigator";
            this.userNotificationBindingNavigator.PositionItem = this.toolStripTextBox11;
            this.userNotificationBindingNavigator.Size = new System.Drawing.Size(374, 25);
            this.userNotificationBindingNavigator.TabIndex = 12;
            // 
            // toolStripButton54
            // 
            this.toolStripButton54.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton54.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton54.Image")));
            this.toolStripButton54.Name = "toolStripButton54";
            this.toolStripButton54.RightToLeftAutoMirrorImage = true;
            this.toolStripButton54.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton54.Text = "Add new";
            // 
            // toolStripLabel11
            // 
            this.toolStripLabel11.Name = "toolStripLabel11";
            this.toolStripLabel11.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel11.Text = "для {0}";
            this.toolStripLabel11.ToolTipText = "Total number of items";
            // 
            // toolStripButton55
            // 
            this.toolStripButton55.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton55.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton55.Image")));
            this.toolStripButton55.Name = "toolStripButton55";
            this.toolStripButton55.RightToLeftAutoMirrorImage = true;
            this.toolStripButton55.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton55.Text = "Delete";
            // 
            // toolStripButton56
            // 
            this.toolStripButton56.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton56.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton56.Image")));
            this.toolStripButton56.Name = "toolStripButton56";
            this.toolStripButton56.RightToLeftAutoMirrorImage = true;
            this.toolStripButton56.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton56.Text = "Move first";
            // 
            // toolStripButton57
            // 
            this.toolStripButton57.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton57.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton57.Image")));
            this.toolStripButton57.Name = "toolStripButton57";
            this.toolStripButton57.RightToLeftAutoMirrorImage = true;
            this.toolStripButton57.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton57.Text = "Move previous";
            // 
            // toolStripSeparator31
            // 
            this.toolStripSeparator31.Name = "toolStripSeparator31";
            this.toolStripSeparator31.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox11
            // 
            this.toolStripTextBox11.AccessibleName = "Position";
            this.toolStripTextBox11.AutoSize = false;
            this.toolStripTextBox11.Name = "toolStripTextBox11";
            this.toolStripTextBox11.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox11.Text = "0";
            this.toolStripTextBox11.ToolTipText = "Current position";
            // 
            // toolStripSeparator32
            // 
            this.toolStripSeparator32.Name = "toolStripSeparator32";
            this.toolStripSeparator32.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton58
            // 
            this.toolStripButton58.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton58.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton58.Image")));
            this.toolStripButton58.Name = "toolStripButton58";
            this.toolStripButton58.RightToLeftAutoMirrorImage = true;
            this.toolStripButton58.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton58.Text = "Move next";
            // 
            // toolStripButton59
            // 
            this.toolStripButton59.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton59.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton59.Image")));
            this.toolStripButton59.Name = "toolStripButton59";
            this.toolStripButton59.RightToLeftAutoMirrorImage = true;
            this.toolStripButton59.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton59.Text = "Move last";
            // 
            // toolStripSeparator33
            // 
            this.toolStripSeparator33.Name = "toolStripSeparator33";
            this.toolStripSeparator33.Size = new System.Drawing.Size(6, 25);
            // 
            // userNotificationBindingNavigatorSaveItem
            // 
            this.userNotificationBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.userNotificationBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("userNotificationBindingNavigatorSaveItem.Image")));
            this.userNotificationBindingNavigatorSaveItem.Name = "userNotificationBindingNavigatorSaveItem";
            this.userNotificationBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.userNotificationBindingNavigatorSaveItem.Text = "Save Data";
            this.userNotificationBindingNavigatorSaveItem.Click += new System.EventHandler(this.userNotificationBindingNavigatorSaveItem_Click);
            // 
            // userNotificationBindingNavigatorRefreshItem
            // 
            this.userNotificationBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.userNotificationBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("userNotificationBindingNavigatorRefreshItem.Image")));
            this.userNotificationBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.userNotificationBindingNavigatorRefreshItem.Name = "userNotificationBindingNavigatorRefreshItem";
            this.userNotificationBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.userNotificationBindingNavigatorRefreshItem.Text = "Refresh";
            this.userNotificationBindingNavigatorRefreshItem.Click += new System.EventHandler(this.userNotificationBindingNavigatorRefreshItem_Click);
            // 
            // userNotificationHistoryGroupBox
            // 
            this.userNotificationHistoryGroupBox.Controls.Add(this.userNotificationHistoryDataGridView);
            this.userNotificationHistoryGroupBox.Controls.Add(this.userNotificationHistoryBindingNavigator);
            this.userNotificationHistoryGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userNotificationHistoryGroupBox.Location = new System.Drawing.Point(0, 0);
            this.userNotificationHistoryGroupBox.Name = "userNotificationHistoryGroupBox";
            this.userNotificationHistoryGroupBox.Size = new System.Drawing.Size(334, 317);
            this.userNotificationHistoryGroupBox.TabIndex = 8;
            this.userNotificationHistoryGroupBox.TabStop = false;
            this.userNotificationHistoryGroupBox.Text = "User notification history";
            // 
            // userNotificationHistoryDataGridView
            // 
            this.userNotificationHistoryDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.userNotificationHistoryDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.userNotificationHistoryNoticeTextColumn,
            this.userNotificationHistoryDateColumn});
            this.userNotificationHistoryDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userNotificationHistoryDataGridView.Location = new System.Drawing.Point(3, 41);
            this.userNotificationHistoryDataGridView.Name = "userNotificationHistoryDataGridView";
            this.userNotificationHistoryDataGridView.Size = new System.Drawing.Size(328, 273);
            this.userNotificationHistoryDataGridView.TabIndex = 11;
            // 
            // userNotificationHistoryNoticeTextColumn
            // 
            this.userNotificationHistoryNoticeTextColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userNotificationHistoryNoticeTextColumn.HeaderText = "Notice text";
            this.userNotificationHistoryNoticeTextColumn.Name = "userNotificationHistoryNoticeTextColumn";
            this.userNotificationHistoryNoticeTextColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.userNotificationHistoryNoticeTextColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.userNotificationHistoryNoticeTextColumn.Width = 250;
            // 
            // userNotificationHistoryDateColumn
            // 
            this.userNotificationHistoryDateColumn.HeaderText = "Date";
            this.userNotificationHistoryDateColumn.Name = "userNotificationHistoryDateColumn";
            this.userNotificationHistoryDateColumn.Width = 200;
            // 
            // userNotificationHistoryBindingNavigator
            // 
            this.userNotificationHistoryBindingNavigator.AddNewItem = this.toolStripButton49;
            this.userNotificationHistoryBindingNavigator.CountItem = this.toolStripLabel12;
            this.userNotificationHistoryBindingNavigator.DeleteItem = this.toolStripButton60;
            this.userNotificationHistoryBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton61,
            this.toolStripButton62,
            this.toolStripSeparator34,
            this.toolStripTextBox12,
            this.toolStripLabel12,
            this.toolStripSeparator35,
            this.toolStripButton63,
            this.toolStripButton64,
            this.toolStripSeparator36,
            this.toolStripButton49,
            this.toolStripButton60,
            this.userNotificationHistoryBindingNavigatorSaveItem,
            this.userNotificationHistoryBindingNavigatorRefreshItem});
            this.userNotificationHistoryBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.userNotificationHistoryBindingNavigator.MoveFirstItem = this.toolStripButton61;
            this.userNotificationHistoryBindingNavigator.MoveLastItem = this.toolStripButton64;
            this.userNotificationHistoryBindingNavigator.MoveNextItem = this.toolStripButton63;
            this.userNotificationHistoryBindingNavigator.MovePreviousItem = this.toolStripButton62;
            this.userNotificationHistoryBindingNavigator.Name = "userNotificationHistoryBindingNavigator";
            this.userNotificationHistoryBindingNavigator.PositionItem = this.toolStripTextBox12;
            this.userNotificationHistoryBindingNavigator.Size = new System.Drawing.Size(328, 25);
            this.userNotificationHistoryBindingNavigator.TabIndex = 12;
            // 
            // toolStripButton49
            // 
            this.toolStripButton49.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton49.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton49.Image")));
            this.toolStripButton49.Name = "toolStripButton49";
            this.toolStripButton49.RightToLeftAutoMirrorImage = true;
            this.toolStripButton49.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton49.Text = "Add new";
            // 
            // toolStripLabel12
            // 
            this.toolStripLabel12.Name = "toolStripLabel12";
            this.toolStripLabel12.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel12.Text = "для {0}";
            this.toolStripLabel12.ToolTipText = "Total number of items";
            // 
            // toolStripButton60
            // 
            this.toolStripButton60.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton60.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton60.Image")));
            this.toolStripButton60.Name = "toolStripButton60";
            this.toolStripButton60.RightToLeftAutoMirrorImage = true;
            this.toolStripButton60.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton60.Text = "Delete";
            // 
            // toolStripButton61
            // 
            this.toolStripButton61.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton61.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton61.Image")));
            this.toolStripButton61.Name = "toolStripButton61";
            this.toolStripButton61.RightToLeftAutoMirrorImage = true;
            this.toolStripButton61.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton61.Text = "Move first";
            // 
            // toolStripButton62
            // 
            this.toolStripButton62.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton62.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton62.Image")));
            this.toolStripButton62.Name = "toolStripButton62";
            this.toolStripButton62.RightToLeftAutoMirrorImage = true;
            this.toolStripButton62.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton62.Text = "Move previous";
            // 
            // toolStripSeparator34
            // 
            this.toolStripSeparator34.Name = "toolStripSeparator34";
            this.toolStripSeparator34.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox12
            // 
            this.toolStripTextBox12.AccessibleName = "Position";
            this.toolStripTextBox12.AutoSize = false;
            this.toolStripTextBox12.Name = "toolStripTextBox12";
            this.toolStripTextBox12.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox12.Text = "0";
            this.toolStripTextBox12.ToolTipText = "Current position";
            // 
            // toolStripSeparator35
            // 
            this.toolStripSeparator35.Name = "toolStripSeparator35";
            this.toolStripSeparator35.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton63
            // 
            this.toolStripButton63.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton63.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton63.Image")));
            this.toolStripButton63.Name = "toolStripButton63";
            this.toolStripButton63.RightToLeftAutoMirrorImage = true;
            this.toolStripButton63.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton63.Text = "Move next";
            // 
            // toolStripButton64
            // 
            this.toolStripButton64.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton64.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton64.Image")));
            this.toolStripButton64.Name = "toolStripButton64";
            this.toolStripButton64.RightToLeftAutoMirrorImage = true;
            this.toolStripButton64.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton64.Text = "Move last";
            // 
            // toolStripSeparator36
            // 
            this.toolStripSeparator36.Name = "toolStripSeparator36";
            this.toolStripSeparator36.Size = new System.Drawing.Size(6, 25);
            // 
            // userNotificationHistoryBindingNavigatorSaveItem
            // 
            this.userNotificationHistoryBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.userNotificationHistoryBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("userNotificationHistoryBindingNavigatorSaveItem.Image")));
            this.userNotificationHistoryBindingNavigatorSaveItem.Name = "userNotificationHistoryBindingNavigatorSaveItem";
            this.userNotificationHistoryBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.userNotificationHistoryBindingNavigatorSaveItem.Text = "Save Data";
            this.userNotificationHistoryBindingNavigatorSaveItem.Click += new System.EventHandler(this.userNotificationHistoryBindingNavigatorSaveItem_Click);
            // 
            // userNotificationHistoryBindingNavigatorRefreshItem
            // 
            this.userNotificationHistoryBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.userNotificationHistoryBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("userNotificationHistoryBindingNavigatorRefreshItem.Image")));
            this.userNotificationHistoryBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.userNotificationHistoryBindingNavigatorRefreshItem.Name = "userNotificationHistoryBindingNavigatorRefreshItem";
            this.userNotificationHistoryBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.userNotificationHistoryBindingNavigatorRefreshItem.Text = "Refresh";
            this.userNotificationHistoryBindingNavigatorRefreshItem.Click += new System.EventHandler(this.userNotificationHistoryBindingNavigatorRefreshItem_Click);
            // 
            // splitter17
            // 
            this.splitter17.Location = new System.Drawing.Point(262, 3);
            this.splitter17.Name = "splitter17";
            this.splitter17.Size = new System.Drawing.Size(3, 317);
            this.splitter17.TabIndex = 6;
            this.splitter17.TabStop = false;
            // 
            // notificationUsersGroupBox
            // 
            this.notificationUsersGroupBox.Controls.Add(this.notificationUsersDataGridView);
            this.notificationUsersGroupBox.Controls.Add(this.notificationUsersBindingNavigator);
            this.notificationUsersGroupBox.Dock = System.Windows.Forms.DockStyle.Left;
            this.notificationUsersGroupBox.Location = new System.Drawing.Point(3, 3);
            this.notificationUsersGroupBox.Name = "notificationUsersGroupBox";
            this.notificationUsersGroupBox.Size = new System.Drawing.Size(259, 317);
            this.notificationUsersGroupBox.TabIndex = 1;
            this.notificationUsersGroupBox.TabStop = false;
            this.notificationUsersGroupBox.Text = "Users";
            // 
            // notificationUsersDataGridView
            // 
            this.notificationUsersDataGridView.AllowUserToAddRows = false;
            this.notificationUsersDataGridView.AllowUserToDeleteRows = false;
            this.notificationUsersDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.notificationUsersDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.notificationUsersUserNameTextBoxColumn});
            this.notificationUsersDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.notificationUsersDataGridView.Location = new System.Drawing.Point(3, 41);
            this.notificationUsersDataGridView.Name = "notificationUsersDataGridView";
            this.notificationUsersDataGridView.ReadOnly = true;
            this.notificationUsersDataGridView.Size = new System.Drawing.Size(253, 273);
            this.notificationUsersDataGridView.TabIndex = 12;
            this.notificationUsersDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.notificationUsersDataGridView_CellFormatting);
            // 
            // notificationUsersUserNameTextBoxColumn
            // 
            this.notificationUsersUserNameTextBoxColumn.HeaderText = "User name";
            this.notificationUsersUserNameTextBoxColumn.Name = "notificationUsersUserNameTextBoxColumn";
            this.notificationUsersUserNameTextBoxColumn.ReadOnly = true;
            this.notificationUsersUserNameTextBoxColumn.Width = 200;
            // 
            // notificationUsersBindingNavigator
            // 
            this.notificationUsersBindingNavigator.AddNewItem = null;
            this.notificationUsersBindingNavigator.CountItem = this.toolStripLabel10;
            this.notificationUsersBindingNavigator.DeleteItem = null;
            this.notificationUsersBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton50,
            this.toolStripButton51,
            this.toolStripSeparator28,
            this.toolStripTextBox10,
            this.toolStripLabel10,
            this.toolStripSeparator29,
            this.toolStripButton52,
            this.toolStripButton53,
            this.toolStripSeparator30,
            this.notificationUsersBindingNavigatorRefreshItem});
            this.notificationUsersBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.notificationUsersBindingNavigator.MoveFirstItem = this.toolStripButton50;
            this.notificationUsersBindingNavigator.MoveLastItem = this.toolStripButton53;
            this.notificationUsersBindingNavigator.MoveNextItem = this.toolStripButton52;
            this.notificationUsersBindingNavigator.MovePreviousItem = this.toolStripButton51;
            this.notificationUsersBindingNavigator.Name = "notificationUsersBindingNavigator";
            this.notificationUsersBindingNavigator.PositionItem = this.toolStripTextBox10;
            this.notificationUsersBindingNavigator.Size = new System.Drawing.Size(253, 25);
            this.notificationUsersBindingNavigator.TabIndex = 11;
            // 
            // toolStripLabel10
            // 
            this.toolStripLabel10.Name = "toolStripLabel10";
            this.toolStripLabel10.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel10.Text = "для {0}";
            this.toolStripLabel10.ToolTipText = "Total number of items";
            // 
            // toolStripButton50
            // 
            this.toolStripButton50.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton50.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton50.Image")));
            this.toolStripButton50.Name = "toolStripButton50";
            this.toolStripButton50.RightToLeftAutoMirrorImage = true;
            this.toolStripButton50.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton50.Text = "Move first";
            // 
            // toolStripButton51
            // 
            this.toolStripButton51.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton51.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton51.Image")));
            this.toolStripButton51.Name = "toolStripButton51";
            this.toolStripButton51.RightToLeftAutoMirrorImage = true;
            this.toolStripButton51.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton51.Text = "Move previous";
            // 
            // toolStripSeparator28
            // 
            this.toolStripSeparator28.Name = "toolStripSeparator28";
            this.toolStripSeparator28.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox10
            // 
            this.toolStripTextBox10.AccessibleName = "Position";
            this.toolStripTextBox10.AutoSize = false;
            this.toolStripTextBox10.Name = "toolStripTextBox10";
            this.toolStripTextBox10.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox10.Text = "0";
            this.toolStripTextBox10.ToolTipText = "Current position";
            // 
            // toolStripSeparator29
            // 
            this.toolStripSeparator29.Name = "toolStripSeparator29";
            this.toolStripSeparator29.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton52
            // 
            this.toolStripButton52.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton52.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton52.Image")));
            this.toolStripButton52.Name = "toolStripButton52";
            this.toolStripButton52.RightToLeftAutoMirrorImage = true;
            this.toolStripButton52.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton52.Text = "Move next";
            // 
            // toolStripButton53
            // 
            this.toolStripButton53.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton53.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton53.Image")));
            this.toolStripButton53.Name = "toolStripButton53";
            this.toolStripButton53.RightToLeftAutoMirrorImage = true;
            this.toolStripButton53.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton53.Text = "Move last";
            // 
            // toolStripSeparator30
            // 
            this.toolStripSeparator30.Name = "toolStripSeparator30";
            this.toolStripSeparator30.Size = new System.Drawing.Size(6, 25);
            // 
            // notificationUsersBindingNavigatorRefreshItem
            // 
            this.notificationUsersBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.notificationUsersBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("notificationUsersBindingNavigatorRefreshItem.Image")));
            this.notificationUsersBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.notificationUsersBindingNavigatorRefreshItem.Name = "notificationUsersBindingNavigatorRefreshItem";
            this.notificationUsersBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.notificationUsersBindingNavigatorRefreshItem.Text = "Refresh";
            this.notificationUsersBindingNavigatorRefreshItem.Click += new System.EventHandler(this.eduUsersBindingNavigatorRefreshIntem_Click);
            // 
            // userGroupNotificationsTabPage
            // 
            this.userGroupNotificationsTabPage.Controls.Add(this.userGroupNotificationGroupBox);
            this.userGroupNotificationsTabPage.Controls.Add(this.splitter32);
            this.userGroupNotificationsTabPage.Controls.Add(this.notificationUserGroupsGroupBox);
            this.userGroupNotificationsTabPage.ImageIndex = 1;
            this.userGroupNotificationsTabPage.Location = new System.Drawing.Point(4, 23);
            this.userGroupNotificationsTabPage.Name = "userGroupNotificationsTabPage";
            this.userGroupNotificationsTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.userGroupNotificationsTabPage.Size = new System.Drawing.Size(986, 323);
            this.userGroupNotificationsTabPage.TabIndex = 1;
            this.userGroupNotificationsTabPage.Text = "User group notifications";
            this.userGroupNotificationsTabPage.UseVisualStyleBackColor = true;
            // 
            // userGroupNotificationGroupBox
            // 
            this.userGroupNotificationGroupBox.Controls.Add(this.userGroupNotificationDataGridView);
            this.userGroupNotificationGroupBox.Controls.Add(this.userGroupsNotificationBindingNavigator);
            this.userGroupNotificationGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userGroupNotificationGroupBox.Location = new System.Drawing.Point(463, 3);
            this.userGroupNotificationGroupBox.Name = "userGroupNotificationGroupBox";
            this.userGroupNotificationGroupBox.Size = new System.Drawing.Size(520, 317);
            this.userGroupNotificationGroupBox.TabIndex = 6;
            this.userGroupNotificationGroupBox.TabStop = false;
            this.userGroupNotificationGroupBox.Text = "User group notifications";
            // 
            // userGroupNotificationDataGridView
            // 
            this.userGroupNotificationDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.userGroupNotificationDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.userGroupNotificationNoticeTextColumn,
            this.userGroupNotificationDisplayTypeColumn});
            this.userGroupNotificationDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userGroupNotificationDataGridView.Location = new System.Drawing.Point(3, 41);
            this.userGroupNotificationDataGridView.Name = "userGroupNotificationDataGridView";
            this.userGroupNotificationDataGridView.Size = new System.Drawing.Size(514, 273);
            this.userGroupNotificationDataGridView.TabIndex = 11;
            // 
            // userGroupNotificationNoticeTextColumn
            // 
            this.userGroupNotificationNoticeTextColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userGroupNotificationNoticeTextColumn.HeaderText = "Notice text";
            this.userGroupNotificationNoticeTextColumn.Name = "userGroupNotificationNoticeTextColumn";
            this.userGroupNotificationNoticeTextColumn.Width = 300;
            // 
            // userGroupNotificationDisplayTypeColumn
            // 
            this.userGroupNotificationDisplayTypeColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userGroupNotificationDisplayTypeColumn.HeaderText = "Notice display type";
            this.userGroupNotificationDisplayTypeColumn.Name = "userGroupNotificationDisplayTypeColumn";
            this.userGroupNotificationDisplayTypeColumn.Width = 150;
            // 
            // userGroupsNotificationBindingNavigator
            // 
            this.userGroupsNotificationBindingNavigator.AddNewItem = this.toolStripButton104;
            this.userGroupsNotificationBindingNavigator.CountItem = this.toolStripLabel20;
            this.userGroupsNotificationBindingNavigator.DeleteItem = this.toolStripButton105;
            this.userGroupsNotificationBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton106,
            this.toolStripButton107,
            this.toolStripSeparator61,
            this.toolStripTextBox20,
            this.toolStripLabel20,
            this.toolStripSeparator62,
            this.toolStripButton108,
            this.toolStripButton109,
            this.toolStripSeparator63,
            this.toolStripButton104,
            this.toolStripButton105,
            this.userGroupNotificationBindingNavigatorSaveItem,
            this.userGroupNotificationBindingNavigatorRefreshItem});
            this.userGroupsNotificationBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.userGroupsNotificationBindingNavigator.MoveFirstItem = this.toolStripButton106;
            this.userGroupsNotificationBindingNavigator.MoveLastItem = this.toolStripButton109;
            this.userGroupsNotificationBindingNavigator.MoveNextItem = this.toolStripButton108;
            this.userGroupsNotificationBindingNavigator.MovePreviousItem = this.toolStripButton107;
            this.userGroupsNotificationBindingNavigator.Name = "userGroupsNotificationBindingNavigator";
            this.userGroupsNotificationBindingNavigator.PositionItem = this.toolStripTextBox20;
            this.userGroupsNotificationBindingNavigator.Size = new System.Drawing.Size(514, 25);
            this.userGroupsNotificationBindingNavigator.TabIndex = 12;
            // 
            // toolStripButton104
            // 
            this.toolStripButton104.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton104.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton104.Image")));
            this.toolStripButton104.Name = "toolStripButton104";
            this.toolStripButton104.RightToLeftAutoMirrorImage = true;
            this.toolStripButton104.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton104.Text = "Add new";
            // 
            // toolStripLabel20
            // 
            this.toolStripLabel20.Name = "toolStripLabel20";
            this.toolStripLabel20.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel20.Text = "для {0}";
            this.toolStripLabel20.ToolTipText = "Total number of items";
            // 
            // toolStripButton105
            // 
            this.toolStripButton105.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton105.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton105.Image")));
            this.toolStripButton105.Name = "toolStripButton105";
            this.toolStripButton105.RightToLeftAutoMirrorImage = true;
            this.toolStripButton105.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton105.Text = "Delete";
            // 
            // toolStripButton106
            // 
            this.toolStripButton106.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton106.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton106.Image")));
            this.toolStripButton106.Name = "toolStripButton106";
            this.toolStripButton106.RightToLeftAutoMirrorImage = true;
            this.toolStripButton106.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton106.Text = "Move first";
            // 
            // toolStripButton107
            // 
            this.toolStripButton107.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton107.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton107.Image")));
            this.toolStripButton107.Name = "toolStripButton107";
            this.toolStripButton107.RightToLeftAutoMirrorImage = true;
            this.toolStripButton107.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton107.Text = "Move previous";
            // 
            // toolStripSeparator61
            // 
            this.toolStripSeparator61.Name = "toolStripSeparator61";
            this.toolStripSeparator61.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox20
            // 
            this.toolStripTextBox20.AccessibleName = "Position";
            this.toolStripTextBox20.AutoSize = false;
            this.toolStripTextBox20.Name = "toolStripTextBox20";
            this.toolStripTextBox20.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox20.Text = "0";
            this.toolStripTextBox20.ToolTipText = "Current position";
            // 
            // toolStripSeparator62
            // 
            this.toolStripSeparator62.Name = "toolStripSeparator62";
            this.toolStripSeparator62.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton108
            // 
            this.toolStripButton108.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton108.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton108.Image")));
            this.toolStripButton108.Name = "toolStripButton108";
            this.toolStripButton108.RightToLeftAutoMirrorImage = true;
            this.toolStripButton108.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton108.Text = "Move next";
            // 
            // toolStripButton109
            // 
            this.toolStripButton109.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton109.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton109.Image")));
            this.toolStripButton109.Name = "toolStripButton109";
            this.toolStripButton109.RightToLeftAutoMirrorImage = true;
            this.toolStripButton109.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton109.Text = "Move last";
            // 
            // toolStripSeparator63
            // 
            this.toolStripSeparator63.Name = "toolStripSeparator63";
            this.toolStripSeparator63.Size = new System.Drawing.Size(6, 25);
            // 
            // userGroupNotificationBindingNavigatorSaveItem
            // 
            this.userGroupNotificationBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.userGroupNotificationBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("userGroupNotificationBindingNavigatorSaveItem.Image")));
            this.userGroupNotificationBindingNavigatorSaveItem.Name = "userGroupNotificationBindingNavigatorSaveItem";
            this.userGroupNotificationBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.userGroupNotificationBindingNavigatorSaveItem.Text = "Save Data";
            this.userGroupNotificationBindingNavigatorSaveItem.Click += new System.EventHandler(this.userGroupNotificationBindingNavigatorSaveItem_Click);
            // 
            // userGroupNotificationBindingNavigatorRefreshItem
            // 
            this.userGroupNotificationBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.userGroupNotificationBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("userGroupNotificationBindingNavigatorRefreshItem.Image")));
            this.userGroupNotificationBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.userGroupNotificationBindingNavigatorRefreshItem.Name = "userGroupNotificationBindingNavigatorRefreshItem";
            this.userGroupNotificationBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.userGroupNotificationBindingNavigatorRefreshItem.Text = "Refresh";
            this.userGroupNotificationBindingNavigatorRefreshItem.Click += new System.EventHandler(this.userGroupNotificationBindingNavigatorRefreshItem_Click);
            // 
            // splitter32
            // 
            this.splitter32.Location = new System.Drawing.Point(460, 3);
            this.splitter32.Name = "splitter32";
            this.splitter32.Size = new System.Drawing.Size(3, 317);
            this.splitter32.TabIndex = 3;
            this.splitter32.TabStop = false;
            // 
            // notificationUserGroupsGroupBox
            // 
            this.notificationUserGroupsGroupBox.Controls.Add(this.notificationUserGroupsDataGridView);
            this.notificationUserGroupsGroupBox.Controls.Add(this.notificationUserGroupsBindingNavigator);
            this.notificationUserGroupsGroupBox.Dock = System.Windows.Forms.DockStyle.Left;
            this.notificationUserGroupsGroupBox.Location = new System.Drawing.Point(3, 3);
            this.notificationUserGroupsGroupBox.Name = "notificationUserGroupsGroupBox";
            this.notificationUserGroupsGroupBox.Size = new System.Drawing.Size(457, 317);
            this.notificationUserGroupsGroupBox.TabIndex = 2;
            this.notificationUserGroupsGroupBox.TabStop = false;
            this.notificationUserGroupsGroupBox.Text = "User groups";
            // 
            // notificationUserGroupsDataGridView
            // 
            this.notificationUserGroupsDataGridView.AllowUserToAddRows = false;
            this.notificationUserGroupsDataGridView.AllowUserToDeleteRows = false;
            this.notificationUserGroupsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.notificationUserGroupsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.notificationGroupNameColumn,
            this.notificationGroupDescriptionColumn});
            this.notificationUserGroupsDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.notificationUserGroupsDataGridView.Location = new System.Drawing.Point(3, 41);
            this.notificationUserGroupsDataGridView.Name = "notificationUserGroupsDataGridView";
            this.notificationUserGroupsDataGridView.ReadOnly = true;
            this.notificationUserGroupsDataGridView.Size = new System.Drawing.Size(451, 273);
            this.notificationUserGroupsDataGridView.TabIndex = 12;
            this.notificationUserGroupsDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.notificationUserGroupsDataGridView_CellFormatting);
            this.notificationUserGroupsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            // 
            // notificationGroupNameColumn
            // 
            this.notificationGroupNameColumn.HeaderText = "Group name";
            this.notificationGroupNameColumn.Name = "notificationGroupNameColumn";
            this.notificationGroupNameColumn.ReadOnly = true;
            this.notificationGroupNameColumn.Width = 150;
            // 
            // notificationGroupDescriptionColumn
            // 
            this.notificationGroupDescriptionColumn.HeaderText = "Description";
            this.notificationGroupDescriptionColumn.Name = "notificationGroupDescriptionColumn";
            this.notificationGroupDescriptionColumn.ReadOnly = true;
            this.notificationGroupDescriptionColumn.Width = 250;
            // 
            // notificationUserGroupsBindingNavigator
            // 
            this.notificationUserGroupsBindingNavigator.AddNewItem = null;
            this.notificationUserGroupsBindingNavigator.CountItem = this.toolStripLabel19;
            this.notificationUserGroupsBindingNavigator.DeleteItem = null;
            this.notificationUserGroupsBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton99,
            this.toolStripButton100,
            this.toolStripSeparator58,
            this.toolStripTextBox19,
            this.toolStripLabel19,
            this.toolStripSeparator59,
            this.toolStripButton101,
            this.toolStripButton102,
            this.toolStripSeparator60,
            this.notificationUserGroupsBindingNavigatorRefreshItem});
            this.notificationUserGroupsBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.notificationUserGroupsBindingNavigator.MoveFirstItem = this.toolStripButton99;
            this.notificationUserGroupsBindingNavigator.MoveLastItem = this.toolStripButton102;
            this.notificationUserGroupsBindingNavigator.MoveNextItem = this.toolStripButton101;
            this.notificationUserGroupsBindingNavigator.MovePreviousItem = this.toolStripButton100;
            this.notificationUserGroupsBindingNavigator.Name = "notificationUserGroupsBindingNavigator";
            this.notificationUserGroupsBindingNavigator.PositionItem = this.toolStripTextBox19;
            this.notificationUserGroupsBindingNavigator.Size = new System.Drawing.Size(451, 25);
            this.notificationUserGroupsBindingNavigator.TabIndex = 11;
            // 
            // toolStripLabel19
            // 
            this.toolStripLabel19.Name = "toolStripLabel19";
            this.toolStripLabel19.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel19.Text = "для {0}";
            this.toolStripLabel19.ToolTipText = "Total number of items";
            // 
            // toolStripButton99
            // 
            this.toolStripButton99.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton99.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton99.Image")));
            this.toolStripButton99.Name = "toolStripButton99";
            this.toolStripButton99.RightToLeftAutoMirrorImage = true;
            this.toolStripButton99.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton99.Text = "Move first";
            // 
            // toolStripButton100
            // 
            this.toolStripButton100.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton100.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton100.Image")));
            this.toolStripButton100.Name = "toolStripButton100";
            this.toolStripButton100.RightToLeftAutoMirrorImage = true;
            this.toolStripButton100.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton100.Text = "Move previous";
            // 
            // toolStripSeparator58
            // 
            this.toolStripSeparator58.Name = "toolStripSeparator58";
            this.toolStripSeparator58.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox19
            // 
            this.toolStripTextBox19.AccessibleName = "Position";
            this.toolStripTextBox19.AutoSize = false;
            this.toolStripTextBox19.Name = "toolStripTextBox19";
            this.toolStripTextBox19.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox19.Text = "0";
            this.toolStripTextBox19.ToolTipText = "Current position";
            // 
            // toolStripSeparator59
            // 
            this.toolStripSeparator59.Name = "toolStripSeparator59";
            this.toolStripSeparator59.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton101
            // 
            this.toolStripButton101.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton101.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton101.Image")));
            this.toolStripButton101.Name = "toolStripButton101";
            this.toolStripButton101.RightToLeftAutoMirrorImage = true;
            this.toolStripButton101.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton101.Text = "Move next";
            // 
            // toolStripButton102
            // 
            this.toolStripButton102.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton102.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton102.Image")));
            this.toolStripButton102.Name = "toolStripButton102";
            this.toolStripButton102.RightToLeftAutoMirrorImage = true;
            this.toolStripButton102.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton102.Text = "Move last";
            // 
            // toolStripSeparator60
            // 
            this.toolStripSeparator60.Name = "toolStripSeparator60";
            this.toolStripSeparator60.Size = new System.Drawing.Size(6, 25);
            // 
            // notificationUserGroupsBindingNavigatorRefreshItem
            // 
            this.notificationUserGroupsBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.notificationUserGroupsBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("notificationUserGroupsBindingNavigatorRefreshItem.Image")));
            this.notificationUserGroupsBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.notificationUserGroupsBindingNavigatorRefreshItem.Name = "notificationUserGroupsBindingNavigatorRefreshItem";
            this.notificationUserGroupsBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.notificationUserGroupsBindingNavigatorRefreshItem.Text = "Refresh";
            this.notificationUserGroupsBindingNavigatorRefreshItem.Click += new System.EventHandler(this.notificationUserGroupsBindingNavigatorRefreshItem_Click);
            // 
            // licenseTabPage
            // 
            this.licenseTabPage.Controls.Add(this.licManagmentMainPanel);
            this.licenseTabPage.ImageIndex = 4;
            this.licenseTabPage.Location = new System.Drawing.Point(4, 42);
            this.licenseTabPage.Name = "licenseTabPage";
            this.licenseTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.licenseTabPage.Size = new System.Drawing.Size(1000, 637);
            this.licenseTabPage.TabIndex = 4;
            this.licenseTabPage.Text = "License management";
            this.licenseTabPage.UseVisualStyleBackColor = true;
            // 
            // licManagmentMainPanel
            // 
            this.licManagmentMainPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.licManagmentMainPanel.Controls.Add(this.licensePointsPanel);
            this.licManagmentMainPanel.Controls.Add(this.licenseBottomPanel);
            this.licManagmentMainPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.licManagmentMainPanel.Location = new System.Drawing.Point(3, 3);
            this.licManagmentMainPanel.Name = "licManagmentMainPanel";
            this.licManagmentMainPanel.Size = new System.Drawing.Size(994, 631);
            this.licManagmentMainPanel.TabIndex = 0;
            // 
            // licensePointsPanel
            // 
            this.licensePointsPanel.AutoScroll = true;
            this.licensePointsPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.licensePointsPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.licensePointsPanel.Location = new System.Drawing.Point(0, 0);
            this.licensePointsPanel.Name = "licensePointsPanel";
            this.licensePointsPanel.Size = new System.Drawing.Size(992, 577);
            this.licensePointsPanel.TabIndex = 11;
            // 
            // licenseBottomPanel
            // 
            this.licenseBottomPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.licenseBottomPanel.Controls.Add(this.btnClearLicenseInfo);
            this.licenseBottomPanel.Controls.Add(this.btnAddLicInfoRecord);
            this.licenseBottomPanel.Controls.Add(this.btnSaveLicenseInfo);
            this.licenseBottomPanel.Controls.Add(this.btnRefreshLicenseInfo);
            this.licenseBottomPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.licenseBottomPanel.Location = new System.Drawing.Point(0, 577);
            this.licenseBottomPanel.Name = "licenseBottomPanel";
            this.licenseBottomPanel.Size = new System.Drawing.Size(992, 52);
            this.licenseBottomPanel.TabIndex = 13;
            // 
            // btnClearLicenseInfo
            // 
            this.btnClearLicenseInfo.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnClearLicenseInfo.Image = ((System.Drawing.Image)(resources.GetObject("btnClearLicenseInfo.Image")));
            this.btnClearLicenseInfo.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnClearLicenseInfo.Location = new System.Drawing.Point(399, 10);
            this.btnClearLicenseInfo.Name = "btnClearLicenseInfo";
            this.btnClearLicenseInfo.Size = new System.Drawing.Size(190, 30);
            this.btnClearLicenseInfo.TabIndex = 13;
            this.btnClearLicenseInfo.Text = "Clear license information";
            this.btnClearLicenseInfo.UseVisualStyleBackColor = true;
            this.btnClearLicenseInfo.Click += new System.EventHandler(this.btnClearLicenseInfo_Click);
            // 
            // btnAddLicInfoRecord
            // 
            this.btnAddLicInfoRecord.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnAddLicInfoRecord.Image = ((System.Drawing.Image)(resources.GetObject("btnAddLicInfoRecord.Image")));
            this.btnAddLicInfoRecord.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnAddLicInfoRecord.Location = new System.Drawing.Point(10, 10);
            this.btnAddLicInfoRecord.Name = "btnAddLicInfoRecord";
            this.btnAddLicInfoRecord.Size = new System.Drawing.Size(190, 30);
            this.btnAddLicInfoRecord.TabIndex = 12;
            this.btnAddLicInfoRecord.Text = "Add license info point";
            this.btnAddLicInfoRecord.UseVisualStyleBackColor = true;
            this.btnAddLicInfoRecord.Click += new System.EventHandler(this.btnAddLicInfoRecord_Click);
            // 
            // btnSaveLicenseInfo
            // 
            this.btnSaveLicenseInfo.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSaveLicenseInfo.Image = ((System.Drawing.Image)(resources.GetObject("btnSaveLicenseInfo.Image")));
            this.btnSaveLicenseInfo.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnSaveLicenseInfo.Location = new System.Drawing.Point(205, 10);
            this.btnSaveLicenseInfo.Name = "btnSaveLicenseInfo";
            this.btnSaveLicenseInfo.Size = new System.Drawing.Size(190, 30);
            this.btnSaveLicenseInfo.TabIndex = 6;
            this.btnSaveLicenseInfo.Text = "Save license information";
            this.btnSaveLicenseInfo.UseVisualStyleBackColor = true;
            this.btnSaveLicenseInfo.Click += new System.EventHandler(this.btnSaveLicenseInfo_Click);
            // 
            // btnRefreshLicenseInfo
            // 
            this.btnRefreshLicenseInfo.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnRefreshLicenseInfo.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnRefreshLicenseInfo.Image = ((System.Drawing.Image)(resources.GetObject("btnRefreshLicenseInfo.Image")));
            this.btnRefreshLicenseInfo.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRefreshLicenseInfo.Location = new System.Drawing.Point(788, 10);
            this.btnRefreshLicenseInfo.Name = "btnRefreshLicenseInfo";
            this.btnRefreshLicenseInfo.Size = new System.Drawing.Size(190, 30);
            this.btnRefreshLicenseInfo.TabIndex = 7;
            this.btnRefreshLicenseInfo.Text = "Refresh license information";
            this.btnRefreshLicenseInfo.UseVisualStyleBackColor = true;
            this.btnRefreshLicenseInfo.Click += new System.EventHandler(this.btnRefreshLicenseInfo_Click);
            // 
            // logFilesTabPage
            // 
            this.logFilesTabPage.Controls.Add(this.logFileMainPanel);
            this.logFilesTabPage.Controls.Add(this.logFilesPanel);
            this.logFilesTabPage.ImageIndex = 6;
            this.logFilesTabPage.Location = new System.Drawing.Point(4, 42);
            this.logFilesTabPage.Name = "logFilesTabPage";
            this.logFilesTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.logFilesTabPage.Size = new System.Drawing.Size(1000, 637);
            this.logFilesTabPage.TabIndex = 5;
            this.logFilesTabPage.Text = "Log-files";
            this.logFilesTabPage.UseVisualStyleBackColor = true;
            // 
            // logFileMainPanel
            // 
            this.logFileMainPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.logFileMainPanel.Controls.Add(this.logFileRichTextBox);
            this.logFileMainPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.logFileMainPanel.Location = new System.Drawing.Point(3, 70);
            this.logFileMainPanel.Name = "logFileMainPanel";
            this.logFileMainPanel.Size = new System.Drawing.Size(994, 564);
            this.logFileMainPanel.TabIndex = 1;
            // 
            // logFileRichTextBox
            // 
            this.logFileRichTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.logFileRichTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.logFileRichTextBox.Location = new System.Drawing.Point(0, 0);
            this.logFileRichTextBox.Name = "logFileRichTextBox";
            this.logFileRichTextBox.Size = new System.Drawing.Size(992, 562);
            this.logFileRichTextBox.TabIndex = 0;
            this.logFileRichTextBox.Text = "";
            // 
            // logFilesPanel
            // 
            this.logFilesPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.logFilesPanel.Controls.Add(this.logFilePathLabel);
            this.logFilesPanel.Controls.Add(this.logFileClearButton);
            this.logFilesPanel.Controls.Add(this.logFileOpenButton);
            this.logFilesPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.logFilesPanel.Location = new System.Drawing.Point(3, 3);
            this.logFilesPanel.Name = "logFilesPanel";
            this.logFilesPanel.Size = new System.Drawing.Size(994, 67);
            this.logFilesPanel.TabIndex = 0;
            // 
            // logFilePathLabel
            // 
            this.logFilePathLabel.AutoSize = true;
            this.logFilePathLabel.Location = new System.Drawing.Point(284, 26);
            this.logFilePathLabel.Name = "logFilePathLabel";
            this.logFilePathLabel.Size = new System.Drawing.Size(85, 13);
            this.logFilePathLabel.TabIndex = 6;
            this.logFilePathLabel.Text = "logFilePathLabel";
            // 
            // logFileClearButton
            // 
            this.logFileClearButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.logFileClearButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.logFileClearButton.Image = ((System.Drawing.Image)(resources.GetObject("logFileClearButton.Image")));
            this.logFileClearButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.logFileClearButton.Location = new System.Drawing.Point(8, 10);
            this.logFileClearButton.Name = "logFileClearButton";
            this.logFileClearButton.Size = new System.Drawing.Size(116, 44);
            this.logFileClearButton.TabIndex = 5;
            this.logFileClearButton.Text = "Clear";
            this.logFileClearButton.UseVisualStyleBackColor = true;
            this.logFileClearButton.Click += new System.EventHandler(this.logFileClearButton_Click);
            // 
            // logFileOpenButton
            // 
            this.logFileOpenButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.logFileOpenButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.logFileOpenButton.Image = ((System.Drawing.Image)(resources.GetObject("logFileOpenButton.Image")));
            this.logFileOpenButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.logFileOpenButton.Location = new System.Drawing.Point(130, 10);
            this.logFileOpenButton.Name = "logFileOpenButton";
            this.logFileOpenButton.Size = new System.Drawing.Size(111, 44);
            this.logFileOpenButton.TabIndex = 4;
            this.logFileOpenButton.Text = "Open";
            this.logFileOpenButton.UseVisualStyleBackColor = true;
            this.logFileOpenButton.Click += new System.EventHandler(this.logFileOpenButton_Click);
            // 
            // confTabPage
            // 
            this.confTabPage.Controls.Add(this.confTabControl);
            this.confTabPage.Controls.Add(this.splitter28);
            this.confTabPage.Controls.Add(this.confTreeView);
            this.confTabPage.ImageIndex = 7;
            this.confTabPage.Location = new System.Drawing.Point(4, 42);
            this.confTabPage.Name = "confTabPage";
            this.confTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.confTabPage.Size = new System.Drawing.Size(1000, 637);
            this.confTabPage.TabIndex = 6;
            this.confTabPage.Text = "Configuration management";
            this.confTabPage.UseVisualStyleBackColor = true;
            // 
            // confTabControl
            // 
            this.confTabControl.Controls.Add(this.tabServiceControl);
            this.confTabControl.Controls.Add(this.tabIPCSettings);
            this.confTabControl.Controls.Add(this.tabDatabaseSettings);
            this.confTabControl.Controls.Add(this.tabMessagesSettings);
            this.confTabControl.Controls.Add(this.tabLOGSettings);
            this.confTabControl.Controls.Add(this.tabServicesConfiguration);
            this.confTabControl.Controls.Add(this.tabSynchronization);
            this.confTabControl.Controls.Add(this.tabPostLoginSettings);
            this.confTabControl.Controls.Add(this.tabProgramsControlSettings);
            this.confTabControl.Controls.Add(this.tabCommandsHistory);
            this.confTabControl.Controls.Add(this.tabFileTransferSettings);
            this.confTabControl.Controls.Add(this.tabUpdateSettings);
            this.confTabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.confTabControl.Location = new System.Drawing.Point(282, 3);
            this.confTabControl.Name = "confTabControl";
            this.confTabControl.SelectedIndex = 0;
            this.confTabControl.Size = new System.Drawing.Size(715, 631);
            this.confTabControl.TabIndex = 3;
            this.confTabControl.SelectedIndexChanged += new System.EventHandler(this.confTabControl_SelectedIndexChanged);
            // 
            // tabServiceControl
            // 
            this.tabServiceControl.Controls.Add(this.splitter29);
            this.tabServiceControl.Controls.Add(this.servicesGroupBox);
            this.tabServiceControl.Controls.Add(this.serviceDescriptionGroupBox);
            this.tabServiceControl.Location = new System.Drawing.Point(4, 22);
            this.tabServiceControl.Name = "tabServiceControl";
            this.tabServiceControl.Padding = new System.Windows.Forms.Padding(3);
            this.tabServiceControl.Size = new System.Drawing.Size(707, 605);
            this.tabServiceControl.TabIndex = 0;
            this.tabServiceControl.Text = "Service control";
            this.tabServiceControl.UseVisualStyleBackColor = true;
            // 
            // splitter29
            // 
            this.splitter29.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.splitter29.Location = new System.Drawing.Point(3, 431);
            this.splitter29.Name = "splitter29";
            this.splitter29.Size = new System.Drawing.Size(701, 3);
            this.splitter29.TabIndex = 2;
            this.splitter29.TabStop = false;
            // 
            // servicesGroupBox
            // 
            this.servicesGroupBox.Controls.Add(this.servicesListView);
            this.servicesGroupBox.Controls.Add(this.servicesButtonsPanel);
            this.servicesGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.servicesGroupBox.Location = new System.Drawing.Point(3, 3);
            this.servicesGroupBox.Name = "servicesGroupBox";
            this.servicesGroupBox.Size = new System.Drawing.Size(701, 431);
            this.servicesGroupBox.TabIndex = 0;
            this.servicesGroupBox.TabStop = false;
            this.servicesGroupBox.Text = "System services";
            // 
            // servicesListView
            // 
            this.servicesListView.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.servicesListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.nameColumnHeader,
            this.statusColumnHeader});
            this.servicesListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.servicesListView.Location = new System.Drawing.Point(3, 16);
            this.servicesListView.MultiSelect = false;
            this.servicesListView.Name = "servicesListView";
            this.servicesListView.Size = new System.Drawing.Size(695, 362);
            this.servicesListView.SmallImageList = this.confImageList;
            this.servicesListView.TabIndex = 1;
            this.servicesListView.UseCompatibleStateImageBehavior = false;
            this.servicesListView.View = System.Windows.Forms.View.Details;
            this.servicesListView.SelectedIndexChanged += new System.EventHandler(this.servicesListView_SelectedIndexChanged);
            // 
            // nameColumnHeader
            // 
            this.nameColumnHeader.Text = "Service name";
            this.nameColumnHeader.Width = 300;
            // 
            // statusColumnHeader
            // 
            this.statusColumnHeader.Text = "Status";
            this.statusColumnHeader.Width = 300;
            // 
            // confImageList
            // 
            this.confImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("confImageList.ImageStream")));
            this.confImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.confImageList.Images.SetKeyName(0, "admin_32.png");
            this.confImageList.Images.SetKeyName(1, "applications_32.png");
            this.confImageList.Images.SetKeyName(2, "client_network.png");
            this.confImageList.Images.SetKeyName(3, "data_preferences.png");
            this.confImageList.Images.SetKeyName(4, "mail_preferences.png");
            this.confImageList.Images.SetKeyName(5, "note_edit.png");
            this.confImageList.Images.SetKeyName(6, "data.png");
            this.confImageList.Images.SetKeyName(7, "mail.png");
            this.confImageList.Images.SetKeyName(8, "applications.png");
            this.confImageList.Images.SetKeyName(9, "gear_replace.png");
            this.confImageList.Images.SetKeyName(10, "replace2.png");
            this.confImageList.Images.SetKeyName(11, "date-time_preferences.png");
            this.confImageList.Images.SetKeyName(12, "gear_time.png");
            this.confImageList.Images.SetKeyName(13, "history.png");
            this.confImageList.Images.SetKeyName(14, "first-page.png");
            this.confImageList.Images.SetKeyName(15, "upload.png");
            // 
            // servicesButtonsPanel
            // 
            this.servicesButtonsPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.servicesButtonsPanel.Controls.Add(this.btnRefreshServicesList);
            this.servicesButtonsPanel.Controls.Add(this.btnRestart);
            this.servicesButtonsPanel.Controls.Add(this.btnPause);
            this.servicesButtonsPanel.Controls.Add(this.btnStop);
            this.servicesButtonsPanel.Controls.Add(this.btnStart);
            this.servicesButtonsPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.servicesButtonsPanel.Location = new System.Drawing.Point(3, 378);
            this.servicesButtonsPanel.Name = "servicesButtonsPanel";
            this.servicesButtonsPanel.Size = new System.Drawing.Size(695, 50);
            this.servicesButtonsPanel.TabIndex = 0;
            // 
            // btnRefreshServicesList
            // 
            this.btnRefreshServicesList.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnRefreshServicesList.Image = ((System.Drawing.Image)(resources.GetObject("btnRefreshServicesList.Image")));
            this.btnRefreshServicesList.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRefreshServicesList.Location = new System.Drawing.Point(496, 4);
            this.btnRefreshServicesList.Name = "btnRefreshServicesList";
            this.btnRefreshServicesList.Size = new System.Drawing.Size(193, 40);
            this.btnRefreshServicesList.TabIndex = 4;
            this.btnRefreshServicesList.Text = "Refresh services list";
            this.btnRefreshServicesList.UseVisualStyleBackColor = true;
            this.btnRefreshServicesList.Click += new System.EventHandler(this.btnRefreshServicesList_Click);
            // 
            // btnRestart
            // 
            this.btnRestart.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnRestart.Image = ((System.Drawing.Image)(resources.GetObject("btnRestart.Image")));
            this.btnRestart.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRestart.Location = new System.Drawing.Point(373, 4);
            this.btnRestart.Name = "btnRestart";
            this.btnRestart.Size = new System.Drawing.Size(120, 40);
            this.btnRestart.TabIndex = 3;
            this.btnRestart.Text = "Restart";
            this.btnRestart.UseVisualStyleBackColor = true;
            this.btnRestart.Click += new System.EventHandler(this.btnRestart_Click);
            // 
            // btnPause
            // 
            this.btnPause.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnPause.Image = ((System.Drawing.Image)(resources.GetObject("btnPause.Image")));
            this.btnPause.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnPause.Location = new System.Drawing.Point(250, 4);
            this.btnPause.Name = "btnPause";
            this.btnPause.Size = new System.Drawing.Size(120, 40);
            this.btnPause.TabIndex = 2;
            this.btnPause.Text = "Pause";
            this.btnPause.UseVisualStyleBackColor = true;
            this.btnPause.Click += new System.EventHandler(this.btnPause_Click);
            // 
            // btnStop
            // 
            this.btnStop.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnStop.Image = ((System.Drawing.Image)(resources.GetObject("btnStop.Image")));
            this.btnStop.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnStop.Location = new System.Drawing.Point(127, 4);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(120, 40);
            this.btnStop.TabIndex = 1;
            this.btnStop.Text = "Stop";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // btnStart
            // 
            this.btnStart.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnStart.Image = ((System.Drawing.Image)(resources.GetObject("btnStart.Image")));
            this.btnStart.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnStart.Location = new System.Drawing.Point(4, 4);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(120, 40);
            this.btnStart.TabIndex = 0;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // serviceDescriptionGroupBox
            // 
            this.serviceDescriptionGroupBox.Controls.Add(this.serviceDescriptionTextBox);
            this.serviceDescriptionGroupBox.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.serviceDescriptionGroupBox.Location = new System.Drawing.Point(3, 434);
            this.serviceDescriptionGroupBox.Name = "serviceDescriptionGroupBox";
            this.serviceDescriptionGroupBox.Size = new System.Drawing.Size(701, 168);
            this.serviceDescriptionGroupBox.TabIndex = 1;
            this.serviceDescriptionGroupBox.TabStop = false;
            this.serviceDescriptionGroupBox.Text = "Description";
            // 
            // serviceDescriptionTextBox
            // 
            this.serviceDescriptionTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.serviceDescriptionTextBox.Location = new System.Drawing.Point(3, 16);
            this.serviceDescriptionTextBox.Multiline = true;
            this.serviceDescriptionTextBox.Name = "serviceDescriptionTextBox";
            this.serviceDescriptionTextBox.Size = new System.Drawing.Size(695, 149);
            this.serviceDescriptionTextBox.TabIndex = 0;
            // 
            // tabIPCSettings
            // 
            this.tabIPCSettings.AutoScroll = true;
            this.tabIPCSettings.BackColor = System.Drawing.Color.White;
            this.tabIPCSettings.Controls.Add(this.globalServerPriorityLabel);
            this.tabIPCSettings.Controls.Add(this.globalServerPriorityNud);
            this.tabIPCSettings.Controls.Add(this.globalServerAddressTextBox);
            this.tabIPCSettings.Controls.Add(this.globalServerAddressLabel);
            this.tabIPCSettings.Controls.Add(this.globalServerPortTextBox);
            this.tabIPCSettings.Controls.Add(this.globalServerPortLabel);
            this.tabIPCSettings.Controls.Add(this.globalServerNameTextBox);
            this.tabIPCSettings.Controls.Add(this.globalServerNameLabel);
            this.tabIPCSettings.Controls.Add(this.globalServerTypeComboBox);
            this.tabIPCSettings.Controls.Add(this.globalServerTypeLabel);
            this.tabIPCSettings.Controls.Add(this.globalServerIDTextBox);
            this.tabIPCSettings.Controls.Add(this.globalServerIDLabel);
            this.tabIPCSettings.Controls.Add(this.label10);
            this.tabIPCSettings.Controls.Add(this.panel1);
            this.tabIPCSettings.Controls.Add(this.btnDelServer);
            this.tabIPCSettings.Controls.Add(this.btnAddServer);
            this.tabIPCSettings.Controls.Add(this.btnLastServer);
            this.tabIPCSettings.Controls.Add(this.btnNextServer);
            this.tabIPCSettings.Controls.Add(this.btnPrevServer);
            this.tabIPCSettings.Controls.Add(this.btnFirstServer);
            this.tabIPCSettings.Controls.Add(this.serverPriorityLabel);
            this.tabIPCSettings.Controls.Add(this.serverPriorityNud);
            this.tabIPCSettings.Controls.Add(this.serverAddressTextBox);
            this.tabIPCSettings.Controls.Add(this.serverAddressLabel);
            this.tabIPCSettings.Controls.Add(this.serverPortTextBox);
            this.tabIPCSettings.Controls.Add(this.serverPortLabel);
            this.tabIPCSettings.Controls.Add(this.serverNameTextBox);
            this.tabIPCSettings.Controls.Add(this.serverNameLabel);
            this.tabIPCSettings.Controls.Add(this.serverTypeComboBox);
            this.tabIPCSettings.Controls.Add(this.serverTypeLabel);
            this.tabIPCSettings.Controls.Add(this.serverIDTextBox);
            this.tabIPCSettings.Controls.Add(this.serverIDLabel);
            this.tabIPCSettings.Controls.Add(this.alternativeServersLabel);
            this.tabIPCSettings.Controls.Add(this.desktopStartingCheckBox);
            this.tabIPCSettings.Controls.Add(this.hubStartingCheckBox);
            this.tabIPCSettings.Controls.Add(this.hostStartingCheckBox);
            this.tabIPCSettings.Controls.Add(this.desktopServerPriorityLabel);
            this.tabIPCSettings.Controls.Add(this.desktopServerPriorityNud);
            this.tabIPCSettings.Controls.Add(this.desktopServerAddressTextBox);
            this.tabIPCSettings.Controls.Add(this.desktopServerAddressLabel);
            this.tabIPCSettings.Controls.Add(this.desktopServerPortTextBox);
            this.tabIPCSettings.Controls.Add(this.desktopServerPortLabel);
            this.tabIPCSettings.Controls.Add(this.desktopServerNameTextBox);
            this.tabIPCSettings.Controls.Add(this.desktopServerNameLabel);
            this.tabIPCSettings.Controls.Add(this.desktopServerTypeComboBox);
            this.tabIPCSettings.Controls.Add(this.desktopServerTypeLabel);
            this.tabIPCSettings.Controls.Add(this.desktopServerIDTextBox);
            this.tabIPCSettings.Controls.Add(this.desktopServerIDLabel);
            this.tabIPCSettings.Controls.Add(this.desktopServerLabel);
            this.tabIPCSettings.Controls.Add(this.hubServerPriorityLabel);
            this.tabIPCSettings.Controls.Add(this.hubServerPriorityNud);
            this.tabIPCSettings.Controls.Add(this.hubServerAddressTextBox);
            this.tabIPCSettings.Controls.Add(this.hubServerAddressLabel);
            this.tabIPCSettings.Controls.Add(this.hubServerPortTextBox);
            this.tabIPCSettings.Controls.Add(this.hubServerPortLabel);
            this.tabIPCSettings.Controls.Add(this.hubServerNameTextBox);
            this.tabIPCSettings.Controls.Add(this.hubServerNameLabel);
            this.tabIPCSettings.Controls.Add(this.hubServerTypeComboBox);
            this.tabIPCSettings.Controls.Add(this.hubServerTypeLabel);
            this.tabIPCSettings.Controls.Add(this.hubServerIDTextBox);
            this.tabIPCSettings.Controls.Add(this.hubServerIDLabel);
            this.tabIPCSettings.Controls.Add(this.hubServerLabel);
            this.tabIPCSettings.Controls.Add(this.ipcSplitPanel1);
            this.tabIPCSettings.Controls.Add(this.hostServerPriorityLabel);
            this.tabIPCSettings.Controls.Add(this.hostServerPriorityNud);
            this.tabIPCSettings.Controls.Add(this.hostServerAddressTextBox);
            this.tabIPCSettings.Controls.Add(this.hostServerAddressLabel);
            this.tabIPCSettings.Controls.Add(this.hostServerPortTextBox);
            this.tabIPCSettings.Controls.Add(this.hostServerPortLabel);
            this.tabIPCSettings.Controls.Add(this.hostServerNameTextBox);
            this.tabIPCSettings.Controls.Add(this.hostServerNameLabel);
            this.tabIPCSettings.Controls.Add(this.hostServerTypeComboBox);
            this.tabIPCSettings.Controls.Add(this.hostServerTypeLabel);
            this.tabIPCSettings.Controls.Add(this.hostServerIDTextBox);
            this.tabIPCSettings.Controls.Add(this.hostServerIDLabel);
            this.tabIPCSettings.Controls.Add(this.hostServerLabel);
            this.tabIPCSettings.Controls.Add(this.btnSaveIPCSettings);
            this.tabIPCSettings.Controls.Add(this.lblIPCTitle);
            this.tabIPCSettings.Location = new System.Drawing.Point(4, 22);
            this.tabIPCSettings.Name = "tabIPCSettings";
            this.tabIPCSettings.Padding = new System.Windows.Forms.Padding(3);
            this.tabIPCSettings.Size = new System.Drawing.Size(707, 605);
            this.tabIPCSettings.TabIndex = 1;
            this.tabIPCSettings.Text = "IPC";
            // 
            // globalServerPriorityLabel
            // 
            this.globalServerPriorityLabel.AutoSize = true;
            this.globalServerPriorityLabel.Location = new System.Drawing.Point(302, 478);
            this.globalServerPriorityLabel.Name = "globalServerPriorityLabel";
            this.globalServerPriorityLabel.Size = new System.Drawing.Size(41, 13);
            this.globalServerPriorityLabel.TabIndex = 91;
            this.globalServerPriorityLabel.Text = "Priority:";
            // 
            // globalServerPriorityNud
            // 
            this.globalServerPriorityNud.Location = new System.Drawing.Point(378, 476);
            this.globalServerPriorityNud.Name = "globalServerPriorityNud";
            this.globalServerPriorityNud.Size = new System.Drawing.Size(164, 20);
            this.globalServerPriorityNud.TabIndex = 90;
            // 
            // globalServerAddressTextBox
            // 
            this.globalServerAddressTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.globalServerAddressTextBox.Location = new System.Drawing.Point(378, 449);
            this.globalServerAddressTextBox.Name = "globalServerAddressTextBox";
            this.globalServerAddressTextBox.Size = new System.Drawing.Size(164, 20);
            this.globalServerAddressTextBox.TabIndex = 89;
            // 
            // globalServerAddressLabel
            // 
            this.globalServerAddressLabel.AutoSize = true;
            this.globalServerAddressLabel.Location = new System.Drawing.Point(302, 451);
            this.globalServerAddressLabel.Name = "globalServerAddressLabel";
            this.globalServerAddressLabel.Size = new System.Drawing.Size(48, 13);
            this.globalServerAddressLabel.TabIndex = 88;
            this.globalServerAddressLabel.Text = "Address:";
            // 
            // globalServerPortTextBox
            // 
            this.globalServerPortTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.globalServerPortTextBox.Location = new System.Drawing.Point(378, 423);
            this.globalServerPortTextBox.Name = "globalServerPortTextBox";
            this.globalServerPortTextBox.Size = new System.Drawing.Size(164, 20);
            this.globalServerPortTextBox.TabIndex = 87;
            // 
            // globalServerPortLabel
            // 
            this.globalServerPortLabel.AutoSize = true;
            this.globalServerPortLabel.Location = new System.Drawing.Point(302, 425);
            this.globalServerPortLabel.Name = "globalServerPortLabel";
            this.globalServerPortLabel.Size = new System.Drawing.Size(29, 13);
            this.globalServerPortLabel.TabIndex = 86;
            this.globalServerPortLabel.Text = "Port:";
            // 
            // globalServerNameTextBox
            // 
            this.globalServerNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.globalServerNameTextBox.Location = new System.Drawing.Point(378, 397);
            this.globalServerNameTextBox.Name = "globalServerNameTextBox";
            this.globalServerNameTextBox.Size = new System.Drawing.Size(164, 20);
            this.globalServerNameTextBox.TabIndex = 85;
            // 
            // globalServerNameLabel
            // 
            this.globalServerNameLabel.AutoSize = true;
            this.globalServerNameLabel.Location = new System.Drawing.Point(302, 399);
            this.globalServerNameLabel.Name = "globalServerNameLabel";
            this.globalServerNameLabel.Size = new System.Drawing.Size(70, 13);
            this.globalServerNameLabel.TabIndex = 84;
            this.globalServerNameLabel.Text = "Server name:";
            // 
            // globalServerTypeComboBox
            // 
            this.globalServerTypeComboBox.FormattingEnabled = true;
            this.globalServerTypeComboBox.Items.AddRange(new object[] {
            "Unknown",
            "HUB-server",
            "HOST-server",
            "DESKTOP-server"});
            this.globalServerTypeComboBox.Location = new System.Drawing.Point(378, 370);
            this.globalServerTypeComboBox.Name = "globalServerTypeComboBox";
            this.globalServerTypeComboBox.Size = new System.Drawing.Size(164, 21);
            this.globalServerTypeComboBox.TabIndex = 83;
            // 
            // globalServerTypeLabel
            // 
            this.globalServerTypeLabel.AutoSize = true;
            this.globalServerTypeLabel.Location = new System.Drawing.Point(302, 373);
            this.globalServerTypeLabel.Name = "globalServerTypeLabel";
            this.globalServerTypeLabel.Size = new System.Drawing.Size(64, 13);
            this.globalServerTypeLabel.TabIndex = 82;
            this.globalServerTypeLabel.Text = "Server type:";
            // 
            // globalServerIDTextBox
            // 
            this.globalServerIDTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.globalServerIDTextBox.Location = new System.Drawing.Point(378, 345);
            this.globalServerIDTextBox.Name = "globalServerIDTextBox";
            this.globalServerIDTextBox.Size = new System.Drawing.Size(164, 20);
            this.globalServerIDTextBox.TabIndex = 81;
            // 
            // globalServerIDLabel
            // 
            this.globalServerIDLabel.AutoSize = true;
            this.globalServerIDLabel.Location = new System.Drawing.Point(302, 347);
            this.globalServerIDLabel.Name = "globalServerIDLabel";
            this.globalServerIDLabel.Size = new System.Drawing.Size(55, 13);
            this.globalServerIDLabel.TabIndex = 80;
            this.globalServerIDLabel.Text = "Server ID:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label10.Location = new System.Drawing.Point(302, 311);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(177, 16);
            this.label10.TabIndex = 79;
            this.label10.Text = "GLOBAL-server settings:";
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Location = new System.Drawing.Point(279, 320);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(2, 190);
            this.panel1.TabIndex = 78;
            // 
            // btnDelServer
            // 
            this.btnDelServer.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnDelServer.Image = ((System.Drawing.Image)(resources.GetObject("btnDelServer.Image")));
            this.btnDelServer.Location = new System.Drawing.Point(449, 691);
            this.btnDelServer.Name = "btnDelServer";
            this.btnDelServer.Size = new System.Drawing.Size(80, 40);
            this.btnDelServer.TabIndex = 77;
            this.btnDelServer.UseVisualStyleBackColor = true;
            this.btnDelServer.Click += new System.EventHandler(this.btnDelServer_Click);
            // 
            // btnAddServer
            // 
            this.btnAddServer.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnAddServer.Image = ((System.Drawing.Image)(resources.GetObject("btnAddServer.Image")));
            this.btnAddServer.Location = new System.Drawing.Point(363, 691);
            this.btnAddServer.Name = "btnAddServer";
            this.btnAddServer.Size = new System.Drawing.Size(80, 40);
            this.btnAddServer.TabIndex = 76;
            this.btnAddServer.UseVisualStyleBackColor = true;
            this.btnAddServer.Click += new System.EventHandler(this.btnAddServer_Click);
            // 
            // btnLastServer
            // 
            this.btnLastServer.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnLastServer.Image = ((System.Drawing.Image)(resources.GetObject("btnLastServer.Image")));
            this.btnLastServer.Location = new System.Drawing.Point(277, 691);
            this.btnLastServer.Name = "btnLastServer";
            this.btnLastServer.Size = new System.Drawing.Size(80, 40);
            this.btnLastServer.TabIndex = 75;
            this.btnLastServer.UseVisualStyleBackColor = true;
            this.btnLastServer.Click += new System.EventHandler(this.btnLastServer_Click);
            // 
            // btnNextServer
            // 
            this.btnNextServer.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnNextServer.Image = ((System.Drawing.Image)(resources.GetObject("btnNextServer.Image")));
            this.btnNextServer.Location = new System.Drawing.Point(193, 691);
            this.btnNextServer.Name = "btnNextServer";
            this.btnNextServer.Size = new System.Drawing.Size(80, 40);
            this.btnNextServer.TabIndex = 74;
            this.btnNextServer.UseVisualStyleBackColor = true;
            this.btnNextServer.Click += new System.EventHandler(this.btnNextServer_Click);
            // 
            // btnPrevServer
            // 
            this.btnPrevServer.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnPrevServer.Image = ((System.Drawing.Image)(resources.GetObject("btnPrevServer.Image")));
            this.btnPrevServer.Location = new System.Drawing.Point(107, 691);
            this.btnPrevServer.Name = "btnPrevServer";
            this.btnPrevServer.Size = new System.Drawing.Size(80, 40);
            this.btnPrevServer.TabIndex = 73;
            this.btnPrevServer.UseVisualStyleBackColor = true;
            this.btnPrevServer.Click += new System.EventHandler(this.btnPrevServer_Click);
            // 
            // btnFirstServer
            // 
            this.btnFirstServer.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnFirstServer.Image = ((System.Drawing.Image)(resources.GetObject("btnFirstServer.Image")));
            this.btnFirstServer.Location = new System.Drawing.Point(21, 691);
            this.btnFirstServer.Name = "btnFirstServer";
            this.btnFirstServer.Size = new System.Drawing.Size(80, 40);
            this.btnFirstServer.TabIndex = 72;
            this.btnFirstServer.UseVisualStyleBackColor = true;
            this.btnFirstServer.Click += new System.EventHandler(this.btnFirstServer_Click);
            // 
            // serverPriorityLabel
            // 
            this.serverPriorityLabel.AutoSize = true;
            this.serverPriorityLabel.Location = new System.Drawing.Point(279, 652);
            this.serverPriorityLabel.Name = "serverPriorityLabel";
            this.serverPriorityLabel.Size = new System.Drawing.Size(41, 13);
            this.serverPriorityLabel.TabIndex = 71;
            this.serverPriorityLabel.Text = "Priority:";
            // 
            // serverPriorityNud
            // 
            this.serverPriorityNud.Location = new System.Drawing.Point(355, 650);
            this.serverPriorityNud.Name = "serverPriorityNud";
            this.serverPriorityNud.Size = new System.Drawing.Size(164, 20);
            this.serverPriorityNud.TabIndex = 70;
            // 
            // serverAddressTextBox
            // 
            this.serverAddressTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.serverAddressTextBox.Location = new System.Drawing.Point(355, 623);
            this.serverAddressTextBox.Name = "serverAddressTextBox";
            this.serverAddressTextBox.Size = new System.Drawing.Size(164, 20);
            this.serverAddressTextBox.TabIndex = 69;
            // 
            // serverAddressLabel
            // 
            this.serverAddressLabel.AutoSize = true;
            this.serverAddressLabel.Location = new System.Drawing.Point(279, 625);
            this.serverAddressLabel.Name = "serverAddressLabel";
            this.serverAddressLabel.Size = new System.Drawing.Size(48, 13);
            this.serverAddressLabel.TabIndex = 68;
            this.serverAddressLabel.Text = "Address:";
            // 
            // serverPortTextBox
            // 
            this.serverPortTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.serverPortTextBox.Location = new System.Drawing.Point(355, 597);
            this.serverPortTextBox.Name = "serverPortTextBox";
            this.serverPortTextBox.Size = new System.Drawing.Size(164, 20);
            this.serverPortTextBox.TabIndex = 67;
            // 
            // serverPortLabel
            // 
            this.serverPortLabel.AutoSize = true;
            this.serverPortLabel.Location = new System.Drawing.Point(279, 599);
            this.serverPortLabel.Name = "serverPortLabel";
            this.serverPortLabel.Size = new System.Drawing.Size(29, 13);
            this.serverPortLabel.TabIndex = 66;
            this.serverPortLabel.Text = "Port:";
            // 
            // serverNameTextBox
            // 
            this.serverNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.serverNameTextBox.Location = new System.Drawing.Point(94, 650);
            this.serverNameTextBox.Name = "serverNameTextBox";
            this.serverNameTextBox.Size = new System.Drawing.Size(164, 20);
            this.serverNameTextBox.TabIndex = 65;
            // 
            // serverNameLabel
            // 
            this.serverNameLabel.AutoSize = true;
            this.serverNameLabel.Location = new System.Drawing.Point(18, 652);
            this.serverNameLabel.Name = "serverNameLabel";
            this.serverNameLabel.Size = new System.Drawing.Size(70, 13);
            this.serverNameLabel.TabIndex = 64;
            this.serverNameLabel.Text = "Server name:";
            // 
            // serverTypeComboBox
            // 
            this.serverTypeComboBox.FormattingEnabled = true;
            this.serverTypeComboBox.Items.AddRange(new object[] {
            "Unknown",
            "HUB-server",
            "HOST-server",
            "DESKTOP-server"});
            this.serverTypeComboBox.Location = new System.Drawing.Point(94, 623);
            this.serverTypeComboBox.Name = "serverTypeComboBox";
            this.serverTypeComboBox.Size = new System.Drawing.Size(164, 21);
            this.serverTypeComboBox.TabIndex = 63;
            // 
            // serverTypeLabel
            // 
            this.serverTypeLabel.AutoSize = true;
            this.serverTypeLabel.Location = new System.Drawing.Point(18, 626);
            this.serverTypeLabel.Name = "serverTypeLabel";
            this.serverTypeLabel.Size = new System.Drawing.Size(64, 13);
            this.serverTypeLabel.TabIndex = 62;
            this.serverTypeLabel.Text = "Server type:";
            // 
            // serverIDTextBox
            // 
            this.serverIDTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.serverIDTextBox.Location = new System.Drawing.Point(94, 598);
            this.serverIDTextBox.Name = "serverIDTextBox";
            this.serverIDTextBox.Size = new System.Drawing.Size(164, 20);
            this.serverIDTextBox.TabIndex = 61;
            // 
            // serverIDLabel
            // 
            this.serverIDLabel.AutoSize = true;
            this.serverIDLabel.Location = new System.Drawing.Point(18, 600);
            this.serverIDLabel.Name = "serverIDLabel";
            this.serverIDLabel.Size = new System.Drawing.Size(55, 13);
            this.serverIDLabel.TabIndex = 60;
            this.serverIDLabel.Text = "Server ID:";
            // 
            // alternativeServersLabel
            // 
            this.alternativeServersLabel.AutoSize = true;
            this.alternativeServersLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.alternativeServersLabel.Location = new System.Drawing.Point(18, 555);
            this.alternativeServersLabel.Name = "alternativeServersLabel";
            this.alternativeServersLabel.Size = new System.Drawing.Size(247, 16);
            this.alternativeServersLabel.TabIndex = 59;
            this.alternativeServersLabel.Text = "Alternative HOST-servers settings:";
            // 
            // desktopStartingCheckBox
            // 
            this.desktopStartingCheckBox.AutoSize = true;
            this.desktopStartingCheckBox.Location = new System.Drawing.Point(21, 502);
            this.desktopStartingCheckBox.Name = "desktopStartingCheckBox";
            this.desktopStartingCheckBox.Size = new System.Drawing.Size(99, 17);
            this.desktopStartingCheckBox.TabIndex = 58;
            this.desktopStartingCheckBox.Text = "Start on this PC";
            this.desktopStartingCheckBox.UseVisualStyleBackColor = true;
            // 
            // hubStartingCheckBox
            // 
            this.hubStartingCheckBox.AutoSize = true;
            this.hubStartingCheckBox.Location = new System.Drawing.Point(305, 255);
            this.hubStartingCheckBox.Name = "hubStartingCheckBox";
            this.hubStartingCheckBox.Size = new System.Drawing.Size(99, 17);
            this.hubStartingCheckBox.TabIndex = 57;
            this.hubStartingCheckBox.Text = "Start on this PC";
            this.hubStartingCheckBox.UseVisualStyleBackColor = true;
            // 
            // hostStartingCheckBox
            // 
            this.hostStartingCheckBox.AutoSize = true;
            this.hostStartingCheckBox.Location = new System.Drawing.Point(21, 255);
            this.hostStartingCheckBox.Name = "hostStartingCheckBox";
            this.hostStartingCheckBox.Size = new System.Drawing.Size(99, 17);
            this.hostStartingCheckBox.TabIndex = 56;
            this.hostStartingCheckBox.Text = "Start on this PC";
            this.hostStartingCheckBox.UseVisualStyleBackColor = true;
            // 
            // desktopServerPriorityLabel
            // 
            this.desktopServerPriorityLabel.AutoSize = true;
            this.desktopServerPriorityLabel.Location = new System.Drawing.Point(18, 478);
            this.desktopServerPriorityLabel.Name = "desktopServerPriorityLabel";
            this.desktopServerPriorityLabel.Size = new System.Drawing.Size(41, 13);
            this.desktopServerPriorityLabel.TabIndex = 55;
            this.desktopServerPriorityLabel.Text = "Priority:";
            // 
            // desktopServerPriorityNud
            // 
            this.desktopServerPriorityNud.Location = new System.Drawing.Point(94, 476);
            this.desktopServerPriorityNud.Name = "desktopServerPriorityNud";
            this.desktopServerPriorityNud.Size = new System.Drawing.Size(164, 20);
            this.desktopServerPriorityNud.TabIndex = 54;
            // 
            // desktopServerAddressTextBox
            // 
            this.desktopServerAddressTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.desktopServerAddressTextBox.Location = new System.Drawing.Point(94, 449);
            this.desktopServerAddressTextBox.Name = "desktopServerAddressTextBox";
            this.desktopServerAddressTextBox.Size = new System.Drawing.Size(164, 20);
            this.desktopServerAddressTextBox.TabIndex = 53;
            // 
            // desktopServerAddressLabel
            // 
            this.desktopServerAddressLabel.AutoSize = true;
            this.desktopServerAddressLabel.Location = new System.Drawing.Point(18, 451);
            this.desktopServerAddressLabel.Name = "desktopServerAddressLabel";
            this.desktopServerAddressLabel.Size = new System.Drawing.Size(48, 13);
            this.desktopServerAddressLabel.TabIndex = 52;
            this.desktopServerAddressLabel.Text = "Address:";
            // 
            // desktopServerPortTextBox
            // 
            this.desktopServerPortTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.desktopServerPortTextBox.Location = new System.Drawing.Point(94, 423);
            this.desktopServerPortTextBox.Name = "desktopServerPortTextBox";
            this.desktopServerPortTextBox.Size = new System.Drawing.Size(164, 20);
            this.desktopServerPortTextBox.TabIndex = 51;
            // 
            // desktopServerPortLabel
            // 
            this.desktopServerPortLabel.AutoSize = true;
            this.desktopServerPortLabel.Location = new System.Drawing.Point(18, 425);
            this.desktopServerPortLabel.Name = "desktopServerPortLabel";
            this.desktopServerPortLabel.Size = new System.Drawing.Size(29, 13);
            this.desktopServerPortLabel.TabIndex = 50;
            this.desktopServerPortLabel.Text = "Port:";
            // 
            // desktopServerNameTextBox
            // 
            this.desktopServerNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.desktopServerNameTextBox.Location = new System.Drawing.Point(94, 397);
            this.desktopServerNameTextBox.Name = "desktopServerNameTextBox";
            this.desktopServerNameTextBox.Size = new System.Drawing.Size(164, 20);
            this.desktopServerNameTextBox.TabIndex = 49;
            // 
            // desktopServerNameLabel
            // 
            this.desktopServerNameLabel.AutoSize = true;
            this.desktopServerNameLabel.Location = new System.Drawing.Point(18, 399);
            this.desktopServerNameLabel.Name = "desktopServerNameLabel";
            this.desktopServerNameLabel.Size = new System.Drawing.Size(70, 13);
            this.desktopServerNameLabel.TabIndex = 48;
            this.desktopServerNameLabel.Text = "Server name:";
            // 
            // desktopServerTypeComboBox
            // 
            this.desktopServerTypeComboBox.FormattingEnabled = true;
            this.desktopServerTypeComboBox.Items.AddRange(new object[] {
            "Unknown",
            "HUB-server",
            "HOST-server",
            "DESKTOP-server"});
            this.desktopServerTypeComboBox.Location = new System.Drawing.Point(94, 370);
            this.desktopServerTypeComboBox.Name = "desktopServerTypeComboBox";
            this.desktopServerTypeComboBox.Size = new System.Drawing.Size(164, 21);
            this.desktopServerTypeComboBox.TabIndex = 47;
            // 
            // desktopServerTypeLabel
            // 
            this.desktopServerTypeLabel.AutoSize = true;
            this.desktopServerTypeLabel.Location = new System.Drawing.Point(18, 373);
            this.desktopServerTypeLabel.Name = "desktopServerTypeLabel";
            this.desktopServerTypeLabel.Size = new System.Drawing.Size(64, 13);
            this.desktopServerTypeLabel.TabIndex = 46;
            this.desktopServerTypeLabel.Text = "Server type:";
            // 
            // desktopServerIDTextBox
            // 
            this.desktopServerIDTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.desktopServerIDTextBox.Location = new System.Drawing.Point(94, 345);
            this.desktopServerIDTextBox.Name = "desktopServerIDTextBox";
            this.desktopServerIDTextBox.Size = new System.Drawing.Size(164, 20);
            this.desktopServerIDTextBox.TabIndex = 45;
            // 
            // desktopServerIDLabel
            // 
            this.desktopServerIDLabel.AutoSize = true;
            this.desktopServerIDLabel.Location = new System.Drawing.Point(18, 347);
            this.desktopServerIDLabel.Name = "desktopServerIDLabel";
            this.desktopServerIDLabel.Size = new System.Drawing.Size(55, 13);
            this.desktopServerIDLabel.TabIndex = 44;
            this.desktopServerIDLabel.Text = "Server ID:";
            // 
            // desktopServerLabel
            // 
            this.desktopServerLabel.AutoSize = true;
            this.desktopServerLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.desktopServerLabel.Location = new System.Drawing.Point(18, 311);
            this.desktopServerLabel.Name = "desktopServerLabel";
            this.desktopServerLabel.Size = new System.Drawing.Size(190, 16);
            this.desktopServerLabel.TabIndex = 43;
            this.desktopServerLabel.Text = "DESKTOP-server settings:";
            // 
            // hubServerPriorityLabel
            // 
            this.hubServerPriorityLabel.AutoSize = true;
            this.hubServerPriorityLabel.Location = new System.Drawing.Point(302, 231);
            this.hubServerPriorityLabel.Name = "hubServerPriorityLabel";
            this.hubServerPriorityLabel.Size = new System.Drawing.Size(41, 13);
            this.hubServerPriorityLabel.TabIndex = 41;
            this.hubServerPriorityLabel.Text = "Priority:";
            // 
            // hubServerPriorityNud
            // 
            this.hubServerPriorityNud.Location = new System.Drawing.Point(378, 229);
            this.hubServerPriorityNud.Name = "hubServerPriorityNud";
            this.hubServerPriorityNud.Size = new System.Drawing.Size(164, 20);
            this.hubServerPriorityNud.TabIndex = 40;
            // 
            // hubServerAddressTextBox
            // 
            this.hubServerAddressTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.hubServerAddressTextBox.Location = new System.Drawing.Point(378, 202);
            this.hubServerAddressTextBox.Name = "hubServerAddressTextBox";
            this.hubServerAddressTextBox.Size = new System.Drawing.Size(164, 20);
            this.hubServerAddressTextBox.TabIndex = 39;
            // 
            // hubServerAddressLabel
            // 
            this.hubServerAddressLabel.AutoSize = true;
            this.hubServerAddressLabel.Location = new System.Drawing.Point(302, 204);
            this.hubServerAddressLabel.Name = "hubServerAddressLabel";
            this.hubServerAddressLabel.Size = new System.Drawing.Size(48, 13);
            this.hubServerAddressLabel.TabIndex = 38;
            this.hubServerAddressLabel.Text = "Address:";
            // 
            // hubServerPortTextBox
            // 
            this.hubServerPortTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.hubServerPortTextBox.Location = new System.Drawing.Point(378, 176);
            this.hubServerPortTextBox.Name = "hubServerPortTextBox";
            this.hubServerPortTextBox.Size = new System.Drawing.Size(164, 20);
            this.hubServerPortTextBox.TabIndex = 37;
            // 
            // hubServerPortLabel
            // 
            this.hubServerPortLabel.AutoSize = true;
            this.hubServerPortLabel.Location = new System.Drawing.Point(302, 178);
            this.hubServerPortLabel.Name = "hubServerPortLabel";
            this.hubServerPortLabel.Size = new System.Drawing.Size(29, 13);
            this.hubServerPortLabel.TabIndex = 36;
            this.hubServerPortLabel.Text = "Port:";
            // 
            // hubServerNameTextBox
            // 
            this.hubServerNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.hubServerNameTextBox.Location = new System.Drawing.Point(378, 150);
            this.hubServerNameTextBox.Name = "hubServerNameTextBox";
            this.hubServerNameTextBox.Size = new System.Drawing.Size(164, 20);
            this.hubServerNameTextBox.TabIndex = 35;
            // 
            // hubServerNameLabel
            // 
            this.hubServerNameLabel.AutoSize = true;
            this.hubServerNameLabel.Location = new System.Drawing.Point(302, 152);
            this.hubServerNameLabel.Name = "hubServerNameLabel";
            this.hubServerNameLabel.Size = new System.Drawing.Size(70, 13);
            this.hubServerNameLabel.TabIndex = 34;
            this.hubServerNameLabel.Text = "Server name:";
            // 
            // hubServerTypeComboBox
            // 
            this.hubServerTypeComboBox.FormattingEnabled = true;
            this.hubServerTypeComboBox.Items.AddRange(new object[] {
            "Unknown",
            "HUB-server",
            "HOST-server",
            "DESKTOP-server"});
            this.hubServerTypeComboBox.Location = new System.Drawing.Point(378, 123);
            this.hubServerTypeComboBox.Name = "hubServerTypeComboBox";
            this.hubServerTypeComboBox.Size = new System.Drawing.Size(164, 21);
            this.hubServerTypeComboBox.TabIndex = 33;
            // 
            // hubServerTypeLabel
            // 
            this.hubServerTypeLabel.AutoSize = true;
            this.hubServerTypeLabel.Location = new System.Drawing.Point(302, 126);
            this.hubServerTypeLabel.Name = "hubServerTypeLabel";
            this.hubServerTypeLabel.Size = new System.Drawing.Size(64, 13);
            this.hubServerTypeLabel.TabIndex = 32;
            this.hubServerTypeLabel.Text = "Server type:";
            // 
            // hubServerIDTextBox
            // 
            this.hubServerIDTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.hubServerIDTextBox.Location = new System.Drawing.Point(378, 98);
            this.hubServerIDTextBox.Name = "hubServerIDTextBox";
            this.hubServerIDTextBox.Size = new System.Drawing.Size(164, 20);
            this.hubServerIDTextBox.TabIndex = 31;
            // 
            // hubServerIDLabel
            // 
            this.hubServerIDLabel.AutoSize = true;
            this.hubServerIDLabel.Location = new System.Drawing.Point(302, 100);
            this.hubServerIDLabel.Name = "hubServerIDLabel";
            this.hubServerIDLabel.Size = new System.Drawing.Size(55, 13);
            this.hubServerIDLabel.TabIndex = 30;
            this.hubServerIDLabel.Text = "Server ID:";
            // 
            // hubServerLabel
            // 
            this.hubServerLabel.AutoSize = true;
            this.hubServerLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.hubServerLabel.Location = new System.Drawing.Point(302, 64);
            this.hubServerLabel.Name = "hubServerLabel";
            this.hubServerLabel.Size = new System.Drawing.Size(151, 16);
            this.hubServerLabel.TabIndex = 29;
            this.hubServerLabel.Text = "HUB-server settings:";
            // 
            // ipcSplitPanel1
            // 
            this.ipcSplitPanel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ipcSplitPanel1.Location = new System.Drawing.Point(279, 85);
            this.ipcSplitPanel1.Name = "ipcSplitPanel1";
            this.ipcSplitPanel1.Size = new System.Drawing.Size(2, 190);
            this.ipcSplitPanel1.TabIndex = 28;
            // 
            // hostServerPriorityLabel
            // 
            this.hostServerPriorityLabel.AutoSize = true;
            this.hostServerPriorityLabel.Location = new System.Drawing.Point(18, 231);
            this.hostServerPriorityLabel.Name = "hostServerPriorityLabel";
            this.hostServerPriorityLabel.Size = new System.Drawing.Size(41, 13);
            this.hostServerPriorityLabel.TabIndex = 27;
            this.hostServerPriorityLabel.Text = "Priority:";
            // 
            // hostServerPriorityNud
            // 
            this.hostServerPriorityNud.Location = new System.Drawing.Point(94, 229);
            this.hostServerPriorityNud.Name = "hostServerPriorityNud";
            this.hostServerPriorityNud.Size = new System.Drawing.Size(164, 20);
            this.hostServerPriorityNud.TabIndex = 26;
            // 
            // hostServerAddressTextBox
            // 
            this.hostServerAddressTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.hostServerAddressTextBox.Location = new System.Drawing.Point(94, 202);
            this.hostServerAddressTextBox.Name = "hostServerAddressTextBox";
            this.hostServerAddressTextBox.Size = new System.Drawing.Size(164, 20);
            this.hostServerAddressTextBox.TabIndex = 25;
            // 
            // hostServerAddressLabel
            // 
            this.hostServerAddressLabel.AutoSize = true;
            this.hostServerAddressLabel.Location = new System.Drawing.Point(18, 204);
            this.hostServerAddressLabel.Name = "hostServerAddressLabel";
            this.hostServerAddressLabel.Size = new System.Drawing.Size(48, 13);
            this.hostServerAddressLabel.TabIndex = 24;
            this.hostServerAddressLabel.Text = "Address:";
            // 
            // hostServerPortTextBox
            // 
            this.hostServerPortTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.hostServerPortTextBox.Location = new System.Drawing.Point(94, 176);
            this.hostServerPortTextBox.Name = "hostServerPortTextBox";
            this.hostServerPortTextBox.Size = new System.Drawing.Size(164, 20);
            this.hostServerPortTextBox.TabIndex = 23;
            // 
            // hostServerPortLabel
            // 
            this.hostServerPortLabel.AutoSize = true;
            this.hostServerPortLabel.Location = new System.Drawing.Point(18, 178);
            this.hostServerPortLabel.Name = "hostServerPortLabel";
            this.hostServerPortLabel.Size = new System.Drawing.Size(29, 13);
            this.hostServerPortLabel.TabIndex = 22;
            this.hostServerPortLabel.Text = "Port:";
            // 
            // hostServerNameTextBox
            // 
            this.hostServerNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.hostServerNameTextBox.Location = new System.Drawing.Point(94, 150);
            this.hostServerNameTextBox.Name = "hostServerNameTextBox";
            this.hostServerNameTextBox.Size = new System.Drawing.Size(164, 20);
            this.hostServerNameTextBox.TabIndex = 21;
            // 
            // hostServerNameLabel
            // 
            this.hostServerNameLabel.AutoSize = true;
            this.hostServerNameLabel.Location = new System.Drawing.Point(18, 152);
            this.hostServerNameLabel.Name = "hostServerNameLabel";
            this.hostServerNameLabel.Size = new System.Drawing.Size(70, 13);
            this.hostServerNameLabel.TabIndex = 20;
            this.hostServerNameLabel.Text = "Server name:";
            // 
            // hostServerTypeComboBox
            // 
            this.hostServerTypeComboBox.FormattingEnabled = true;
            this.hostServerTypeComboBox.Items.AddRange(new object[] {
            "Unknown",
            "HUB-server",
            "HOST-server",
            "DESKTOP-server"});
            this.hostServerTypeComboBox.Location = new System.Drawing.Point(94, 123);
            this.hostServerTypeComboBox.Name = "hostServerTypeComboBox";
            this.hostServerTypeComboBox.Size = new System.Drawing.Size(164, 21);
            this.hostServerTypeComboBox.TabIndex = 19;
            // 
            // hostServerTypeLabel
            // 
            this.hostServerTypeLabel.AutoSize = true;
            this.hostServerTypeLabel.Location = new System.Drawing.Point(18, 126);
            this.hostServerTypeLabel.Name = "hostServerTypeLabel";
            this.hostServerTypeLabel.Size = new System.Drawing.Size(64, 13);
            this.hostServerTypeLabel.TabIndex = 11;
            this.hostServerTypeLabel.Text = "Server type:";
            // 
            // hostServerIDTextBox
            // 
            this.hostServerIDTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.hostServerIDTextBox.Location = new System.Drawing.Point(94, 98);
            this.hostServerIDTextBox.Name = "hostServerIDTextBox";
            this.hostServerIDTextBox.Size = new System.Drawing.Size(164, 20);
            this.hostServerIDTextBox.TabIndex = 10;
            // 
            // hostServerIDLabel
            // 
            this.hostServerIDLabel.AutoSize = true;
            this.hostServerIDLabel.Location = new System.Drawing.Point(18, 100);
            this.hostServerIDLabel.Name = "hostServerIDLabel";
            this.hostServerIDLabel.Size = new System.Drawing.Size(55, 13);
            this.hostServerIDLabel.TabIndex = 9;
            this.hostServerIDLabel.Text = "Server ID:";
            // 
            // hostServerLabel
            // 
            this.hostServerLabel.AutoSize = true;
            this.hostServerLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.hostServerLabel.Location = new System.Drawing.Point(18, 64);
            this.hostServerLabel.Name = "hostServerLabel";
            this.hostServerLabel.Size = new System.Drawing.Size(161, 16);
            this.hostServerLabel.TabIndex = 6;
            this.hostServerLabel.Text = "HOST-server settings:";
            // 
            // btnSaveIPCSettings
            // 
            this.btnSaveIPCSettings.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSaveIPCSettings.Image = ((System.Drawing.Image)(resources.GetObject("btnSaveIPCSettings.Image")));
            this.btnSaveIPCSettings.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnSaveIPCSettings.Location = new System.Drawing.Point(21, 776);
            this.btnSaveIPCSettings.Name = "btnSaveIPCSettings";
            this.btnSaveIPCSettings.Size = new System.Drawing.Size(210, 41);
            this.btnSaveIPCSettings.TabIndex = 5;
            this.btnSaveIPCSettings.Text = "Save settings";
            this.btnSaveIPCSettings.UseVisualStyleBackColor = true;
            this.btnSaveIPCSettings.Click += new System.EventHandler(this.btnSaveIPCSettings_Click);
            // 
            // lblIPCTitle
            // 
            this.lblIPCTitle.AutoSize = true;
            this.lblIPCTitle.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblIPCTitle.Location = new System.Drawing.Point(18, 25);
            this.lblIPCTitle.Name = "lblIPCTitle";
            this.lblIPCTitle.Size = new System.Drawing.Size(263, 16);
            this.lblIPCTitle.TabIndex = 0;
            this.lblIPCTitle.Text = "Interprocess communication settings:";
            // 
            // tabDatabaseSettings
            // 
            this.tabDatabaseSettings.AutoScroll = true;
            this.tabDatabaseSettings.BackColor = System.Drawing.Color.White;
            this.tabDatabaseSettings.Controls.Add(this.changeDBPwdLabel);
            this.tabDatabaseSettings.Controls.Add(this.onDelUserAccActionComboBox);
            this.tabDatabaseSettings.Controls.Add(this.lblUserAccountsOnDeleteAction);
            this.tabDatabaseSettings.Controls.Add(this.lblUserAccountsManagement);
            this.tabDatabaseSettings.Controls.Add(this.dbPasswordTextBox);
            this.tabDatabaseSettings.Controls.Add(this.lblDBPassword);
            this.tabDatabaseSettings.Controls.Add(this.dbUserNameTextBox);
            this.tabDatabaseSettings.Controls.Add(this.lblDBUserName);
            this.tabDatabaseSettings.Controls.Add(this.btnDataBaseAccessSettingsSave);
            this.tabDatabaseSettings.Controls.Add(this.dbNameTextBox);
            this.tabDatabaseSettings.Controls.Add(this.lblDBName);
            this.tabDatabaseSettings.Controls.Add(this.dbServerTextBox);
            this.tabDatabaseSettings.Controls.Add(this.lblDBServer);
            this.tabDatabaseSettings.Controls.Add(this.lblDatabaseAccessSettings);
            this.tabDatabaseSettings.Location = new System.Drawing.Point(4, 22);
            this.tabDatabaseSettings.Name = "tabDatabaseSettings";
            this.tabDatabaseSettings.Padding = new System.Windows.Forms.Padding(3);
            this.tabDatabaseSettings.Size = new System.Drawing.Size(707, 605);
            this.tabDatabaseSettings.TabIndex = 2;
            this.tabDatabaseSettings.Text = "Database";
            // 
            // changeDBPwdLabel
            // 
            this.changeDBPwdLabel.AutoSize = true;
            this.changeDBPwdLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.changeDBPwdLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.changeDBPwdLabel.ForeColor = System.Drawing.Color.Blue;
            this.changeDBPwdLabel.Location = new System.Drawing.Point(334, 233);
            this.changeDBPwdLabel.Name = "changeDBPwdLabel";
            this.changeDBPwdLabel.Size = new System.Drawing.Size(92, 13);
            this.changeDBPwdLabel.TabIndex = 23;
            this.changeDBPwdLabel.Text = "Change password";
            this.changeDBPwdLabel.Click += new System.EventHandler(this.changeDBPwdLabel_Click);
            // 
            // onDelUserAccActionComboBox
            // 
            this.onDelUserAccActionComboBox.FormattingEnabled = true;
            this.onDelUserAccActionComboBox.Items.AddRange(new object[] {
            "Delete",
            "Move to archive"});
            this.onDelUserAccActionComboBox.Location = new System.Drawing.Point(334, 336);
            this.onDelUserAccActionComboBox.Name = "onDelUserAccActionComboBox";
            this.onDelUserAccActionComboBox.Size = new System.Drawing.Size(164, 21);
            this.onDelUserAccActionComboBox.TabIndex = 18;
            // 
            // lblUserAccountsOnDeleteAction
            // 
            this.lblUserAccountsOnDeleteAction.AutoSize = true;
            this.lblUserAccountsOnDeleteAction.Location = new System.Drawing.Point(33, 340);
            this.lblUserAccountsOnDeleteAction.Name = "lblUserAccountsOnDeleteAction";
            this.lblUserAccountsOnDeleteAction.Size = new System.Drawing.Size(294, 13);
            this.lblUserAccountsOnDeleteAction.TabIndex = 17;
            this.lblUserAccountsOnDeleteAction.Text = "Action that must be performed when deleting user\'s accounts";
            // 
            // lblUserAccountsManagement
            // 
            this.lblUserAccountsManagement.AutoSize = true;
            this.lblUserAccountsManagement.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblUserAccountsManagement.Location = new System.Drawing.Point(30, 277);
            this.lblUserAccountsManagement.Name = "lblUserAccountsManagement";
            this.lblUserAccountsManagement.Size = new System.Drawing.Size(258, 16);
            this.lblUserAccountsManagement.TabIndex = 16;
            this.lblUserAccountsManagement.Text = "User accounts management settings";
            // 
            // dbPasswordTextBox
            // 
            this.dbPasswordTextBox.BackColor = System.Drawing.SystemColors.Window;
            this.dbPasswordTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.dbPasswordTextBox.Location = new System.Drawing.Point(161, 201);
            this.dbPasswordTextBox.Name = "dbPasswordTextBox";
            this.dbPasswordTextBox.PasswordChar = '*';
            this.dbPasswordTextBox.ReadOnly = true;
            this.dbPasswordTextBox.Size = new System.Drawing.Size(265, 20);
            this.dbPasswordTextBox.TabIndex = 15;
            this.dbPasswordTextBox.MouseHover += new System.EventHandler(this.dbPasswordTextBox_MouseHover);
            // 
            // lblDBPassword
            // 
            this.lblDBPassword.AutoSize = true;
            this.lblDBPassword.Location = new System.Drawing.Point(30, 204);
            this.lblDBPassword.Name = "lblDBPassword";
            this.lblDBPassword.Size = new System.Drawing.Size(104, 13);
            this.lblDBPassword.TabIndex = 14;
            this.lblDBPassword.Text = "Database password:";
            // 
            // dbUserNameTextBox
            // 
            this.dbUserNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.dbUserNameTextBox.Location = new System.Drawing.Point(161, 158);
            this.dbUserNameTextBox.Name = "dbUserNameTextBox";
            this.dbUserNameTextBox.Size = new System.Drawing.Size(265, 20);
            this.dbUserNameTextBox.TabIndex = 13;
            // 
            // lblDBUserName
            // 
            this.lblDBUserName.AutoSize = true;
            this.lblDBUserName.Location = new System.Drawing.Point(30, 161);
            this.lblDBUserName.Name = "lblDBUserName";
            this.lblDBUserName.Size = new System.Drawing.Size(108, 13);
            this.lblDBUserName.TabIndex = 12;
            this.lblDBUserName.Text = "Database user name:";
            // 
            // btnDataBaseAccessSettingsSave
            // 
            this.btnDataBaseAccessSettingsSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnDataBaseAccessSettingsSave.Image = ((System.Drawing.Image)(resources.GetObject("btnDataBaseAccessSettingsSave.Image")));
            this.btnDataBaseAccessSettingsSave.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnDataBaseAccessSettingsSave.Location = new System.Drawing.Point(30, 414);
            this.btnDataBaseAccessSettingsSave.Name = "btnDataBaseAccessSettingsSave";
            this.btnDataBaseAccessSettingsSave.Size = new System.Drawing.Size(210, 41);
            this.btnDataBaseAccessSettingsSave.TabIndex = 11;
            this.btnDataBaseAccessSettingsSave.Text = "Save settings";
            this.btnDataBaseAccessSettingsSave.UseVisualStyleBackColor = true;
            this.btnDataBaseAccessSettingsSave.Click += new System.EventHandler(this.btnDataBaseAccessSettingsSave_Click);
            // 
            // dbNameTextBox
            // 
            this.dbNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.dbNameTextBox.Location = new System.Drawing.Point(161, 118);
            this.dbNameTextBox.Name = "dbNameTextBox";
            this.dbNameTextBox.Size = new System.Drawing.Size(265, 20);
            this.dbNameTextBox.TabIndex = 10;
            // 
            // lblDBName
            // 
            this.lblDBName.AutoSize = true;
            this.lblDBName.Location = new System.Drawing.Point(30, 121);
            this.lblDBName.Name = "lblDBName";
            this.lblDBName.Size = new System.Drawing.Size(85, 13);
            this.lblDBName.TabIndex = 9;
            this.lblDBName.Text = "Database name:";
            // 
            // dbServerTextBox
            // 
            this.dbServerTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.dbServerTextBox.Location = new System.Drawing.Point(161, 75);
            this.dbServerTextBox.Name = "dbServerTextBox";
            this.dbServerTextBox.Size = new System.Drawing.Size(265, 20);
            this.dbServerTextBox.TabIndex = 8;
            // 
            // lblDBServer
            // 
            this.lblDBServer.AutoSize = true;
            this.lblDBServer.Location = new System.Drawing.Point(30, 78);
            this.lblDBServer.Name = "lblDBServer";
            this.lblDBServer.Size = new System.Drawing.Size(88, 13);
            this.lblDBServer.TabIndex = 7;
            this.lblDBServer.Text = "Database server:";
            // 
            // lblDatabaseAccessSettings
            // 
            this.lblDatabaseAccessSettings.AutoSize = true;
            this.lblDatabaseAccessSettings.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblDatabaseAccessSettings.Location = new System.Drawing.Point(27, 27);
            this.lblDatabaseAccessSettings.Name = "lblDatabaseAccessSettings";
            this.lblDatabaseAccessSettings.Size = new System.Drawing.Size(188, 16);
            this.lblDatabaseAccessSettings.TabIndex = 6;
            this.lblDatabaseAccessSettings.Text = "Database access settings";
            // 
            // tabMessagesSettings
            // 
            this.tabMessagesSettings.AutoScroll = true;
            this.tabMessagesSettings.BackColor = System.Drawing.Color.White;
            this.tabMessagesSettings.Controls.Add(this.changeGVoicePwdLabel);
            this.tabMessagesSettings.Controls.Add(this.changeEmailPwdLabel);
            this.tabMessagesSettings.Controls.Add(this.gvPasswordTextBox);
            this.tabMessagesSettings.Controls.Add(this.lblGVPassword);
            this.tabMessagesSettings.Controls.Add(this.gvLoginTextBox);
            this.tabMessagesSettings.Controls.Add(this.lblGVLogin);
            this.tabMessagesSettings.Controls.Add(this.lblGVSettings);
            this.tabMessagesSettings.Controls.Add(this.emailRecipientTextBox);
            this.tabMessagesSettings.Controls.Add(this.lblEmailRecipient);
            this.tabMessagesSettings.Controls.Add(this.emailSenderTextBox);
            this.tabMessagesSettings.Controls.Add(this.lblEmailSender);
            this.tabMessagesSettings.Controls.Add(this.emailPasswordTextBox);
            this.tabMessagesSettings.Controls.Add(this.lblEmailPassword);
            this.tabMessagesSettings.Controls.Add(this.emailLoginTextBox);
            this.tabMessagesSettings.Controls.Add(this.lblEmailLogin);
            this.tabMessagesSettings.Controls.Add(this.emailAuthCheckBox);
            this.tabMessagesSettings.Controls.Add(this.emailSecTypeComboBox);
            this.tabMessagesSettings.Controls.Add(this.lblEmailSecType);
            this.tabMessagesSettings.Controls.Add(this.btnMessagingSettingsSave);
            this.tabMessagesSettings.Controls.Add(this.emailPortTextBox);
            this.tabMessagesSettings.Controls.Add(this.lblEmailPort);
            this.tabMessagesSettings.Controls.Add(this.emailHostTextBox);
            this.tabMessagesSettings.Controls.Add(this.lblEMailHost);
            this.tabMessagesSettings.Controls.Add(this.lblEMailSettings);
            this.tabMessagesSettings.Location = new System.Drawing.Point(4, 22);
            this.tabMessagesSettings.Name = "tabMessagesSettings";
            this.tabMessagesSettings.Padding = new System.Windows.Forms.Padding(3);
            this.tabMessagesSettings.Size = new System.Drawing.Size(707, 605);
            this.tabMessagesSettings.TabIndex = 3;
            this.tabMessagesSettings.Text = "E-Mail";
            // 
            // changeGVoicePwdLabel
            // 
            this.changeGVoicePwdLabel.AutoSize = true;
            this.changeGVoicePwdLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.changeGVoicePwdLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.changeGVoicePwdLabel.ForeColor = System.Drawing.Color.Blue;
            this.changeGVoicePwdLabel.Location = new System.Drawing.Point(334, 488);
            this.changeGVoicePwdLabel.Name = "changeGVoicePwdLabel";
            this.changeGVoicePwdLabel.Size = new System.Drawing.Size(92, 13);
            this.changeGVoicePwdLabel.TabIndex = 42;
            this.changeGVoicePwdLabel.Text = "Change password";
            this.changeGVoicePwdLabel.Click += new System.EventHandler(this.changeGVoicePwdLabel_Click);
            // 
            // changeEmailPwdLabel
            // 
            this.changeEmailPwdLabel.AutoSize = true;
            this.changeEmailPwdLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.changeEmailPwdLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.changeEmailPwdLabel.ForeColor = System.Drawing.Color.Blue;
            this.changeEmailPwdLabel.Location = new System.Drawing.Point(334, 263);
            this.changeEmailPwdLabel.Name = "changeEmailPwdLabel";
            this.changeEmailPwdLabel.Size = new System.Drawing.Size(92, 13);
            this.changeEmailPwdLabel.TabIndex = 41;
            this.changeEmailPwdLabel.Text = "Change password";
            this.changeEmailPwdLabel.Click += new System.EventHandler(this.changeEmailPwdLabel_Click);
            // 
            // gvPasswordTextBox
            // 
            this.gvPasswordTextBox.BackColor = System.Drawing.SystemColors.Window;
            this.gvPasswordTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.gvPasswordTextBox.Location = new System.Drawing.Point(161, 463);
            this.gvPasswordTextBox.Name = "gvPasswordTextBox";
            this.gvPasswordTextBox.PasswordChar = '*';
            this.gvPasswordTextBox.ReadOnly = true;
            this.gvPasswordTextBox.Size = new System.Drawing.Size(265, 20);
            this.gvPasswordTextBox.TabIndex = 40;
            this.gvPasswordTextBox.MouseHover += new System.EventHandler(this.dbPasswordTextBox_MouseHover);
            // 
            // lblGVPassword
            // 
            this.lblGVPassword.AutoSize = true;
            this.lblGVPassword.Location = new System.Drawing.Point(30, 466);
            this.lblGVPassword.Name = "lblGVPassword";
            this.lblGVPassword.Size = new System.Drawing.Size(56, 13);
            this.lblGVPassword.TabIndex = 39;
            this.lblGVPassword.Text = "Password:";
            // 
            // gvLoginTextBox
            // 
            this.gvLoginTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.gvLoginTextBox.Location = new System.Drawing.Point(161, 431);
            this.gvLoginTextBox.Name = "gvLoginTextBox";
            this.gvLoginTextBox.Size = new System.Drawing.Size(265, 20);
            this.gvLoginTextBox.TabIndex = 38;
            // 
            // lblGVLogin
            // 
            this.lblGVLogin.AutoSize = true;
            this.lblGVLogin.Location = new System.Drawing.Point(30, 434);
            this.lblGVLogin.Name = "lblGVLogin";
            this.lblGVLogin.Size = new System.Drawing.Size(36, 13);
            this.lblGVLogin.TabIndex = 37;
            this.lblGVLogin.Text = "Login:";
            // 
            // lblGVSettings
            // 
            this.lblGVSettings.AutoSize = true;
            this.lblGVSettings.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblGVSettings.Location = new System.Drawing.Point(30, 396);
            this.lblGVSettings.Name = "lblGVSettings";
            this.lblGVSettings.Size = new System.Drawing.Size(159, 16);
            this.lblGVSettings.TabIndex = 36;
            this.lblGVSettings.Text = "Google voice settings";
            // 
            // emailRecipientTextBox
            // 
            this.emailRecipientTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.emailRecipientTextBox.Location = new System.Drawing.Point(161, 323);
            this.emailRecipientTextBox.Name = "emailRecipientTextBox";
            this.emailRecipientTextBox.Size = new System.Drawing.Size(265, 20);
            this.emailRecipientTextBox.TabIndex = 35;
            // 
            // lblEmailRecipient
            // 
            this.lblEmailRecipient.AutoSize = true;
            this.lblEmailRecipient.Location = new System.Drawing.Point(30, 326);
            this.lblEmailRecipient.Name = "lblEmailRecipient";
            this.lblEmailRecipient.Size = new System.Drawing.Size(95, 13);
            this.lblEmailRecipient.TabIndex = 34;
            this.lblEmailRecipient.Text = "Recipient address:";
            // 
            // emailSenderTextBox
            // 
            this.emailSenderTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.emailSenderTextBox.Location = new System.Drawing.Point(161, 291);
            this.emailSenderTextBox.Name = "emailSenderTextBox";
            this.emailSenderTextBox.Size = new System.Drawing.Size(265, 20);
            this.emailSenderTextBox.TabIndex = 33;
            // 
            // lblEmailSender
            // 
            this.lblEmailSender.AutoSize = true;
            this.lblEmailSender.Location = new System.Drawing.Point(30, 294);
            this.lblEmailSender.Name = "lblEmailSender";
            this.lblEmailSender.Size = new System.Drawing.Size(84, 13);
            this.lblEmailSender.TabIndex = 32;
            this.lblEmailSender.Text = "Sender address:";
            // 
            // emailPasswordTextBox
            // 
            this.emailPasswordTextBox.BackColor = System.Drawing.SystemColors.Window;
            this.emailPasswordTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.emailPasswordTextBox.Location = new System.Drawing.Point(161, 239);
            this.emailPasswordTextBox.Name = "emailPasswordTextBox";
            this.emailPasswordTextBox.PasswordChar = '*';
            this.emailPasswordTextBox.ReadOnly = true;
            this.emailPasswordTextBox.Size = new System.Drawing.Size(265, 20);
            this.emailPasswordTextBox.TabIndex = 31;
            this.emailPasswordTextBox.MouseHover += new System.EventHandler(this.dbPasswordTextBox_MouseHover);
            // 
            // lblEmailPassword
            // 
            this.lblEmailPassword.AutoSize = true;
            this.lblEmailPassword.Location = new System.Drawing.Point(30, 242);
            this.lblEmailPassword.Name = "lblEmailPassword";
            this.lblEmailPassword.Size = new System.Drawing.Size(56, 13);
            this.lblEmailPassword.TabIndex = 30;
            this.lblEmailPassword.Text = "Password:";
            // 
            // emailLoginTextBox
            // 
            this.emailLoginTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.emailLoginTextBox.Location = new System.Drawing.Point(161, 207);
            this.emailLoginTextBox.Name = "emailLoginTextBox";
            this.emailLoginTextBox.Size = new System.Drawing.Size(265, 20);
            this.emailLoginTextBox.TabIndex = 29;
            // 
            // lblEmailLogin
            // 
            this.lblEmailLogin.AutoSize = true;
            this.lblEmailLogin.Location = new System.Drawing.Point(30, 210);
            this.lblEmailLogin.Name = "lblEmailLogin";
            this.lblEmailLogin.Size = new System.Drawing.Size(36, 13);
            this.lblEmailLogin.TabIndex = 28;
            this.lblEmailLogin.Text = "Login:";
            // 
            // emailAuthCheckBox
            // 
            this.emailAuthCheckBox.AutoSize = true;
            this.emailAuthCheckBox.Location = new System.Drawing.Point(33, 163);
            this.emailAuthCheckBox.Name = "emailAuthCheckBox";
            this.emailAuthCheckBox.Size = new System.Drawing.Size(133, 17);
            this.emailAuthCheckBox.TabIndex = 27;
            this.emailAuthCheckBox.Text = "Authentication needed";
            this.emailAuthCheckBox.UseVisualStyleBackColor = true;
            this.emailAuthCheckBox.CheckedChanged += new System.EventHandler(this.emailAuthCheckBox_CheckedChanged);
            // 
            // emailSecTypeComboBox
            // 
            this.emailSecTypeComboBox.FormattingEnabled = true;
            this.emailSecTypeComboBox.Items.AddRange(new object[] {
            "No security",
            "Use TLS",
            "Use SSL",
            "Do not set"});
            this.emailSecTypeComboBox.Location = new System.Drawing.Point(161, 121);
            this.emailSecTypeComboBox.Name = "emailSecTypeComboBox";
            this.emailSecTypeComboBox.Size = new System.Drawing.Size(265, 21);
            this.emailSecTypeComboBox.TabIndex = 26;
            // 
            // lblEmailSecType
            // 
            this.lblEmailSecType.AutoSize = true;
            this.lblEmailSecType.Location = new System.Drawing.Point(30, 127);
            this.lblEmailSecType.Name = "lblEmailSecType";
            this.lblEmailSecType.Size = new System.Drawing.Size(71, 13);
            this.lblEmailSecType.TabIndex = 22;
            this.lblEmailSecType.Text = "Security type:";
            // 
            // btnMessagingSettingsSave
            // 
            this.btnMessagingSettingsSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnMessagingSettingsSave.Image = ((System.Drawing.Image)(resources.GetObject("btnMessagingSettingsSave.Image")));
            this.btnMessagingSettingsSave.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnMessagingSettingsSave.Location = new System.Drawing.Point(30, 538);
            this.btnMessagingSettingsSave.Name = "btnMessagingSettingsSave";
            this.btnMessagingSettingsSave.Size = new System.Drawing.Size(210, 41);
            this.btnMessagingSettingsSave.TabIndex = 21;
            this.btnMessagingSettingsSave.Text = "Save settings";
            this.btnMessagingSettingsSave.UseVisualStyleBackColor = true;
            this.btnMessagingSettingsSave.Click += new System.EventHandler(this.btnMessagingSettingsSave_Click);
            // 
            // emailPortTextBox
            // 
            this.emailPortTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.emailPortTextBox.Location = new System.Drawing.Point(161, 89);
            this.emailPortTextBox.Name = "emailPortTextBox";
            this.emailPortTextBox.Size = new System.Drawing.Size(265, 20);
            this.emailPortTextBox.TabIndex = 20;
            // 
            // lblEmailPort
            // 
            this.lblEmailPort.AutoSize = true;
            this.lblEmailPort.Location = new System.Drawing.Point(30, 92);
            this.lblEmailPort.Name = "lblEmailPort";
            this.lblEmailPort.Size = new System.Drawing.Size(61, 13);
            this.lblEmailPort.TabIndex = 19;
            this.lblEmailPort.Text = "SMTP port:";
            // 
            // emailHostTextBox
            // 
            this.emailHostTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.emailHostTextBox.Location = new System.Drawing.Point(161, 56);
            this.emailHostTextBox.Name = "emailHostTextBox";
            this.emailHostTextBox.Size = new System.Drawing.Size(265, 20);
            this.emailHostTextBox.TabIndex = 18;
            // 
            // lblEMailHost
            // 
            this.lblEMailHost.AutoSize = true;
            this.lblEMailHost.Location = new System.Drawing.Point(30, 59);
            this.lblEMailHost.Name = "lblEMailHost";
            this.lblEMailHost.Size = new System.Drawing.Size(63, 13);
            this.lblEMailHost.TabIndex = 17;
            this.lblEMailHost.Text = "SMTP host:";
            // 
            // lblEMailSettings
            // 
            this.lblEMailSettings.AutoSize = true;
            this.lblEMailSettings.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblEMailSettings.Location = new System.Drawing.Point(27, 24);
            this.lblEMailSettings.Name = "lblEMailSettings";
            this.lblEMailSettings.Size = new System.Drawing.Size(169, 16);
            this.lblEMailSettings.TabIndex = 16;
            this.lblEMailSettings.Text = "E-mail sending settings";
            // 
            // tabLOGSettings
            // 
            this.tabLOGSettings.AutoScroll = true;
            this.tabLOGSettings.BackColor = System.Drawing.Color.White;
            this.tabLOGSettings.Controls.Add(this.fixedSizeLabel);
            this.tabLOGSettings.Controls.Add(this.fixedSizeNumUpDown);
            this.tabLOGSettings.Controls.Add(this.fixedSizeCheckBox);
            this.tabLOGSettings.Controls.Add(this.logPathButton);
            this.tabLOGSettings.Controls.Add(this.logPathTextBox);
            this.tabLOGSettings.Controls.Add(this.logPathLabel);
            this.tabLOGSettings.Controls.Add(this.btnLogSettingsSave);
            this.tabLOGSettings.Controls.Add(this.logEmailCheckBox);
            this.tabLOGSettings.Controls.Add(this.logEncryptionCheckBox);
            this.tabLOGSettings.Controls.Add(this.lblLOGSettings);
            this.tabLOGSettings.Location = new System.Drawing.Point(4, 22);
            this.tabLOGSettings.Name = "tabLOGSettings";
            this.tabLOGSettings.Padding = new System.Windows.Forms.Padding(3);
            this.tabLOGSettings.Size = new System.Drawing.Size(707, 605);
            this.tabLOGSettings.TabIndex = 4;
            this.tabLOGSettings.Text = "LOG";
            // 
            // fixedSizeLabel
            // 
            this.fixedSizeLabel.AutoSize = true;
            this.fixedSizeLabel.Location = new System.Drawing.Point(453, 262);
            this.fixedSizeLabel.Name = "fixedSizeLabel";
            this.fixedSizeLabel.Size = new System.Drawing.Size(32, 13);
            this.fixedSizeLabel.TabIndex = 36;
            this.fixedSizeLabel.Text = "bytes";
            // 
            // fixedSizeNumUpDown
            // 
            this.fixedSizeNumUpDown.Location = new System.Drawing.Point(185, 259);
            this.fixedSizeNumUpDown.Maximum = new decimal(new int[] {
            2147483645,
            0,
            0,
            0});
            this.fixedSizeNumUpDown.Name = "fixedSizeNumUpDown";
            this.fixedSizeNumUpDown.Size = new System.Drawing.Size(261, 20);
            this.fixedSizeNumUpDown.TabIndex = 35;
            // 
            // fixedSizeCheckBox
            // 
            this.fixedSizeCheckBox.AutoSize = true;
            this.fixedSizeCheckBox.Location = new System.Drawing.Point(24, 260);
            this.fixedSizeCheckBox.Name = "fixedSizeCheckBox";
            this.fixedSizeCheckBox.Size = new System.Drawing.Size(130, 17);
            this.fixedSizeCheckBox.TabIndex = 34;
            this.fixedSizeCheckBox.Text = "Fixed size of LOG-files";
            this.fixedSizeCheckBox.UseVisualStyleBackColor = true;
            this.fixedSizeCheckBox.CheckedChanged += new System.EventHandler(this.fixedSizeCheckBox_CheckedChanged);
            // 
            // logPathButton
            // 
            this.logPathButton.Location = new System.Drawing.Point(448, 191);
            this.logPathButton.Name = "logPathButton";
            this.logPathButton.Size = new System.Drawing.Size(26, 23);
            this.logPathButton.TabIndex = 33;
            this.logPathButton.Text = "...";
            this.logPathButton.UseVisualStyleBackColor = true;
            this.logPathButton.Click += new System.EventHandler(this.logPathButton_Click);
            // 
            // logPathTextBox
            // 
            this.logPathTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.logPathTextBox.Location = new System.Drawing.Point(185, 193);
            this.logPathTextBox.Name = "logPathTextBox";
            this.logPathTextBox.Size = new System.Drawing.Size(261, 20);
            this.logPathTextBox.TabIndex = 32;
            // 
            // logPathLabel
            // 
            this.logPathLabel.AutoSize = true;
            this.logPathLabel.Location = new System.Drawing.Point(24, 196);
            this.logPathLabel.Name = "logPathLabel";
            this.logPathLabel.Size = new System.Drawing.Size(155, 13);
            this.logPathLabel.TabIndex = 31;
            this.logPathLabel.Text = "The path to the LOG-files vault:";
            // 
            // btnLogSettingsSave
            // 
            this.btnLogSettingsSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnLogSettingsSave.Image = ((System.Drawing.Image)(resources.GetObject("btnLogSettingsSave.Image")));
            this.btnLogSettingsSave.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnLogSettingsSave.Location = new System.Drawing.Point(24, 328);
            this.btnLogSettingsSave.Name = "btnLogSettingsSave";
            this.btnLogSettingsSave.Size = new System.Drawing.Size(210, 41);
            this.btnLogSettingsSave.TabIndex = 30;
            this.btnLogSettingsSave.Text = "Save settings";
            this.btnLogSettingsSave.UseVisualStyleBackColor = true;
            this.btnLogSettingsSave.Click += new System.EventHandler(this.btnLogSettingsSave_Click);
            // 
            // logEmailCheckBox
            // 
            this.logEmailCheckBox.AutoSize = true;
            this.logEmailCheckBox.Location = new System.Drawing.Point(24, 131);
            this.logEmailCheckBox.Name = "logEmailCheckBox";
            this.logEmailCheckBox.Size = new System.Drawing.Size(233, 17);
            this.logEmailCheckBox.TabIndex = 29;
            this.logEmailCheckBox.Text = "Send messages from the LOG-file by e-mail?";
            this.logEmailCheckBox.UseVisualStyleBackColor = true;
            // 
            // logEncryptionCheckBox
            // 
            this.logEncryptionCheckBox.AutoSize = true;
            this.logEncryptionCheckBox.Location = new System.Drawing.Point(24, 83);
            this.logEncryptionCheckBox.Name = "logEncryptionCheckBox";
            this.logEncryptionCheckBox.Size = new System.Drawing.Size(249, 17);
            this.logEncryptionCheckBox.TabIndex = 28;
            this.logEncryptionCheckBox.Text = "Store records in the LOG-file in encrypted form?";
            this.logEncryptionCheckBox.UseVisualStyleBackColor = true;
            // 
            // lblLOGSettings
            // 
            this.lblLOGSettings.AutoSize = true;
            this.lblLOGSettings.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblLOGSettings.Location = new System.Drawing.Point(21, 26);
            this.lblLOGSettings.Name = "lblLOGSettings";
            this.lblLOGSettings.Size = new System.Drawing.Size(200, 16);
            this.lblLOGSettings.TabIndex = 17;
            this.lblLOGSettings.Text = "LOG-files recording settings";
            // 
            // tabServicesConfiguration
            // 
            this.tabServicesConfiguration.AutoScroll = true;
            this.tabServicesConfiguration.BackColor = System.Drawing.Color.White;
            this.tabServicesConfiguration.Controls.Add(this.updateSettingsLabel);
            this.tabServicesConfiguration.Controls.Add(this.updateSettingsPictureBox);
            this.tabServicesConfiguration.Controls.Add(this.fileTransferLabel);
            this.tabServicesConfiguration.Controls.Add(this.fileTransferPictureBox);
            this.tabServicesConfiguration.Controls.Add(this.commandsHistorySettingsLabel);
            this.tabServicesConfiguration.Controls.Add(this.commandsHistorySettingsPictureBox);
            this.tabServicesConfiguration.Controls.Add(this.programsControlSettingsLabel);
            this.tabServicesConfiguration.Controls.Add(this.programsControlSettingsPictureBox);
            this.tabServicesConfiguration.Controls.Add(this.postLoginSettingsLabel);
            this.tabServicesConfiguration.Controls.Add(this.postLoginSettingsPictureBox);
            this.tabServicesConfiguration.Controls.Add(this.logSettingsLabel);
            this.tabServicesConfiguration.Controls.Add(this.logSettingsPictureBox);
            this.tabServicesConfiguration.Controls.Add(this.msgSettingsLabel);
            this.tabServicesConfiguration.Controls.Add(this.msgSettingsPictureBox);
            this.tabServicesConfiguration.Controls.Add(this.dbSettingsLabel);
            this.tabServicesConfiguration.Controls.Add(this.dbSettingsPictureBox);
            this.tabServicesConfiguration.Controls.Add(this.ipcSettingsLabel);
            this.tabServicesConfiguration.Controls.Add(this.ipcSettingsPictureBox);
            this.tabServicesConfiguration.Location = new System.Drawing.Point(4, 22);
            this.tabServicesConfiguration.Name = "tabServicesConfiguration";
            this.tabServicesConfiguration.Padding = new System.Windows.Forms.Padding(3);
            this.tabServicesConfiguration.Size = new System.Drawing.Size(707, 605);
            this.tabServicesConfiguration.TabIndex = 5;
            this.tabServicesConfiguration.Text = "Services configuration";
            // 
            // updateSettingsLabel
            // 
            this.updateSettingsLabel.AutoSize = true;
            this.updateSettingsLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.updateSettingsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.updateSettingsLabel.Location = new System.Drawing.Point(92, 473);
            this.updateSettingsLabel.Name = "updateSettingsLabel";
            this.updateSettingsLabel.Size = new System.Drawing.Size(122, 20);
            this.updateSettingsLabel.TabIndex = 17;
            this.updateSettingsLabel.Tag = "9";
            this.updateSettingsLabel.Text = "Update settings";
            this.updateSettingsLabel.Click += new System.EventHandler(this.ipcSettingsLabel_Click);
            // 
            // updateSettingsPictureBox
            // 
            this.updateSettingsPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("updateSettingsPictureBox.Image")));
            this.updateSettingsPictureBox.Location = new System.Drawing.Point(36, 464);
            this.updateSettingsPictureBox.Name = "updateSettingsPictureBox";
            this.updateSettingsPictureBox.Size = new System.Drawing.Size(37, 38);
            this.updateSettingsPictureBox.TabIndex = 16;
            this.updateSettingsPictureBox.TabStop = false;
            // 
            // fileTransferLabel
            // 
            this.fileTransferLabel.AutoSize = true;
            this.fileTransferLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.fileTransferLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.fileTransferLabel.Location = new System.Drawing.Point(92, 418);
            this.fileTransferLabel.Name = "fileTransferLabel";
            this.fileTransferLabel.Size = new System.Drawing.Size(153, 20);
            this.fileTransferLabel.TabIndex = 15;
            this.fileTransferLabel.Tag = "8";
            this.fileTransferLabel.Text = "File transfer settings";
            this.fileTransferLabel.Click += new System.EventHandler(this.ipcSettingsLabel_Click);
            // 
            // fileTransferPictureBox
            // 
            this.fileTransferPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("fileTransferPictureBox.Image")));
            this.fileTransferPictureBox.Location = new System.Drawing.Point(36, 409);
            this.fileTransferPictureBox.Name = "fileTransferPictureBox";
            this.fileTransferPictureBox.Size = new System.Drawing.Size(37, 38);
            this.fileTransferPictureBox.TabIndex = 14;
            this.fileTransferPictureBox.TabStop = false;
            // 
            // commandsHistorySettingsLabel
            // 
            this.commandsHistorySettingsLabel.AutoSize = true;
            this.commandsHistorySettingsLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.commandsHistorySettingsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.commandsHistorySettingsLabel.Location = new System.Drawing.Point(93, 365);
            this.commandsHistorySettingsLabel.Name = "commandsHistorySettingsLabel";
            this.commandsHistorySettingsLabel.Size = new System.Drawing.Size(205, 20);
            this.commandsHistorySettingsLabel.TabIndex = 13;
            this.commandsHistorySettingsLabel.Tag = "7";
            this.commandsHistorySettingsLabel.Text = "Commands logging settings";
            this.commandsHistorySettingsLabel.Click += new System.EventHandler(this.ipcSettingsLabel_Click);
            // 
            // commandsHistorySettingsPictureBox
            // 
            this.commandsHistorySettingsPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("commandsHistorySettingsPictureBox.Image")));
            this.commandsHistorySettingsPictureBox.Location = new System.Drawing.Point(37, 356);
            this.commandsHistorySettingsPictureBox.Name = "commandsHistorySettingsPictureBox";
            this.commandsHistorySettingsPictureBox.Size = new System.Drawing.Size(37, 38);
            this.commandsHistorySettingsPictureBox.TabIndex = 12;
            this.commandsHistorySettingsPictureBox.TabStop = false;
            // 
            // programsControlSettingsLabel
            // 
            this.programsControlSettingsLabel.AutoSize = true;
            this.programsControlSettingsLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.programsControlSettingsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.programsControlSettingsLabel.Location = new System.Drawing.Point(93, 312);
            this.programsControlSettingsLabel.Name = "programsControlSettingsLabel";
            this.programsControlSettingsLabel.Size = new System.Drawing.Size(189, 20);
            this.programsControlSettingsLabel.TabIndex = 11;
            this.programsControlSettingsLabel.Tag = "6";
            this.programsControlSettingsLabel.Text = "Programs control settings";
            this.programsControlSettingsLabel.Click += new System.EventHandler(this.ipcSettingsLabel_Click);
            // 
            // programsControlSettingsPictureBox
            // 
            this.programsControlSettingsPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("programsControlSettingsPictureBox.Image")));
            this.programsControlSettingsPictureBox.Location = new System.Drawing.Point(37, 303);
            this.programsControlSettingsPictureBox.Name = "programsControlSettingsPictureBox";
            this.programsControlSettingsPictureBox.Size = new System.Drawing.Size(37, 38);
            this.programsControlSettingsPictureBox.TabIndex = 10;
            this.programsControlSettingsPictureBox.TabStop = false;
            // 
            // postLoginSettingsLabel
            // 
            this.postLoginSettingsLabel.AutoSize = true;
            this.postLoginSettingsLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.postLoginSettingsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.postLoginSettingsLabel.Location = new System.Drawing.Point(93, 259);
            this.postLoginSettingsLabel.Name = "postLoginSettingsLabel";
            this.postLoginSettingsLabel.Size = new System.Drawing.Size(204, 20);
            this.postLoginSettingsLabel.TabIndex = 9;
            this.postLoginSettingsLabel.Tag = "5";
            this.postLoginSettingsLabel.Text = "Post Login process settings";
            this.postLoginSettingsLabel.Click += new System.EventHandler(this.ipcSettingsLabel_Click);
            // 
            // postLoginSettingsPictureBox
            // 
            this.postLoginSettingsPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("postLoginSettingsPictureBox.Image")));
            this.postLoginSettingsPictureBox.Location = new System.Drawing.Point(37, 250);
            this.postLoginSettingsPictureBox.Name = "postLoginSettingsPictureBox";
            this.postLoginSettingsPictureBox.Size = new System.Drawing.Size(37, 38);
            this.postLoginSettingsPictureBox.TabIndex = 8;
            this.postLoginSettingsPictureBox.TabStop = false;
            // 
            // logSettingsLabel
            // 
            this.logSettingsLabel.AutoSize = true;
            this.logSettingsLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.logSettingsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.logSettingsLabel.Location = new System.Drawing.Point(93, 208);
            this.logSettingsLabel.Name = "logSettingsLabel";
            this.logSettingsLabel.Size = new System.Drawing.Size(136, 20);
            this.logSettingsLabel.TabIndex = 7;
            this.logSettingsLabel.Tag = "4";
            this.logSettingsLabel.Text = "LOG-files settings";
            this.logSettingsLabel.Click += new System.EventHandler(this.ipcSettingsLabel_Click);
            // 
            // logSettingsPictureBox
            // 
            this.logSettingsPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("logSettingsPictureBox.Image")));
            this.logSettingsPictureBox.Location = new System.Drawing.Point(37, 198);
            this.logSettingsPictureBox.Name = "logSettingsPictureBox";
            this.logSettingsPictureBox.Size = new System.Drawing.Size(37, 38);
            this.logSettingsPictureBox.TabIndex = 6;
            this.logSettingsPictureBox.TabStop = false;
            // 
            // msgSettingsLabel
            // 
            this.msgSettingsLabel.AutoSize = true;
            this.msgSettingsLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.msgSettingsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.msgSettingsLabel.Location = new System.Drawing.Point(93, 156);
            this.msgSettingsLabel.Name = "msgSettingsLabel";
            this.msgSettingsLabel.Size = new System.Drawing.Size(146, 20);
            this.msgSettingsLabel.TabIndex = 5;
            this.msgSettingsLabel.Tag = "3";
            this.msgSettingsLabel.Text = "Messaging settings";
            this.msgSettingsLabel.Click += new System.EventHandler(this.ipcSettingsLabel_Click);
            // 
            // msgSettingsPictureBox
            // 
            this.msgSettingsPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("msgSettingsPictureBox.Image")));
            this.msgSettingsPictureBox.Location = new System.Drawing.Point(37, 146);
            this.msgSettingsPictureBox.Name = "msgSettingsPictureBox";
            this.msgSettingsPictureBox.Size = new System.Drawing.Size(37, 38);
            this.msgSettingsPictureBox.TabIndex = 4;
            this.msgSettingsPictureBox.TabStop = false;
            // 
            // dbSettingsLabel
            // 
            this.dbSettingsLabel.AutoSize = true;
            this.dbSettingsLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.dbSettingsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.dbSettingsLabel.Location = new System.Drawing.Point(93, 104);
            this.dbSettingsLabel.Name = "dbSettingsLabel";
            this.dbSettingsLabel.Size = new System.Drawing.Size(139, 20);
            this.dbSettingsLabel.TabIndex = 3;
            this.dbSettingsLabel.Tag = "2";
            this.dbSettingsLabel.Text = "Database settings";
            this.dbSettingsLabel.Click += new System.EventHandler(this.ipcSettingsLabel_Click);
            // 
            // dbSettingsPictureBox
            // 
            this.dbSettingsPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("dbSettingsPictureBox.Image")));
            this.dbSettingsPictureBox.Location = new System.Drawing.Point(37, 94);
            this.dbSettingsPictureBox.Name = "dbSettingsPictureBox";
            this.dbSettingsPictureBox.Size = new System.Drawing.Size(37, 38);
            this.dbSettingsPictureBox.TabIndex = 2;
            this.dbSettingsPictureBox.TabStop = false;
            // 
            // ipcSettingsLabel
            // 
            this.ipcSettingsLabel.AutoSize = true;
            this.ipcSettingsLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.ipcSettingsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ipcSettingsLabel.Location = new System.Drawing.Point(93, 53);
            this.ipcSettingsLabel.Name = "ipcSettingsLabel";
            this.ipcSettingsLabel.Size = new System.Drawing.Size(95, 20);
            this.ipcSettingsLabel.TabIndex = 1;
            this.ipcSettingsLabel.Tag = "1";
            this.ipcSettingsLabel.Text = "IPC settings";
            this.ipcSettingsLabel.Click += new System.EventHandler(this.ipcSettingsLabel_Click);
            // 
            // ipcSettingsPictureBox
            // 
            this.ipcSettingsPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("ipcSettingsPictureBox.Image")));
            this.ipcSettingsPictureBox.Location = new System.Drawing.Point(37, 43);
            this.ipcSettingsPictureBox.Name = "ipcSettingsPictureBox";
            this.ipcSettingsPictureBox.Size = new System.Drawing.Size(37, 38);
            this.ipcSettingsPictureBox.TabIndex = 0;
            this.ipcSettingsPictureBox.TabStop = false;
            // 
            // tabSynchronization
            // 
            this.tabSynchronization.AutoScroll = true;
            this.tabSynchronization.BackColor = System.Drawing.Color.White;
            this.tabSynchronization.Controls.Add(this.revLinkTabControl);
            this.tabSynchronization.Controls.Add(this.syncLogonCheckBox);
            this.tabSynchronization.Controls.Add(this.lblLogonSyncSettings);
            this.tabSynchronization.Controls.Add(this.revSyncAuthSystemsComboBox);
            this.tabSynchronization.Controls.Add(this.lblReverseSyncAuthSystem);
            this.tabSynchronization.Controls.Add(this.lblReverseSyncSettings);
            this.tabSynchronization.Controls.Add(this.btnForcedSync);
            this.tabSynchronization.Controls.Add(this.lblSyncTime);
            this.tabSynchronization.Controls.Add(this.btnSaveSyncSettings);
            this.tabSynchronization.Controls.Add(this.syncPeriodComboBox);
            this.tabSynchronization.Controls.Add(this.lblSyncPeriod);
            this.tabSynchronization.Controls.Add(this.periodicSyncOnOffCheckBox);
            this.tabSynchronization.Controls.Add(this.lblPeriodicSyncSet);
            this.tabSynchronization.Location = new System.Drawing.Point(4, 22);
            this.tabSynchronization.Name = "tabSynchronization";
            this.tabSynchronization.Padding = new System.Windows.Forms.Padding(3);
            this.tabSynchronization.Size = new System.Drawing.Size(707, 605);
            this.tabSynchronization.TabIndex = 6;
            this.tabSynchronization.Text = "Synchronization";
            // 
            // revLinkTabControl
            // 
            this.revLinkTabControl.Controls.Add(this.revLinkUsersTabPage);
            this.revLinkTabControl.Controls.Add(this.revLinkGroupsTabPage);
            this.revLinkTabControl.ImageList = this.usersImageList;
            this.revLinkTabControl.Location = new System.Drawing.Point(24, 333);
            this.revLinkTabControl.Name = "revLinkTabControl";
            this.revLinkTabControl.SelectedIndex = 0;
            this.revLinkTabControl.Size = new System.Drawing.Size(412, 462);
            this.revLinkTabControl.TabIndex = 34;
            // 
            // revLinkUsersTabPage
            // 
            this.revLinkUsersTabPage.Controls.Add(this.btnRefreshRevUsersList);
            this.revLinkUsersTabPage.Controls.Add(this.accountsListView);
            this.revLinkUsersTabPage.Controls.Add(this.btnReverseLink);
            this.revLinkUsersTabPage.ImageIndex = 0;
            this.revLinkUsersTabPage.Location = new System.Drawing.Point(4, 23);
            this.revLinkUsersTabPage.Name = "revLinkUsersTabPage";
            this.revLinkUsersTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.revLinkUsersTabPage.Size = new System.Drawing.Size(404, 435);
            this.revLinkUsersTabPage.TabIndex = 0;
            this.revLinkUsersTabPage.Text = "Reverse linking of user accounts";
            this.revLinkUsersTabPage.UseVisualStyleBackColor = true;
            // 
            // btnRefreshRevUsersList
            // 
            this.btnRefreshRevUsersList.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnRefreshRevUsersList.Image = ((System.Drawing.Image)(resources.GetObject("btnRefreshRevUsersList.Image")));
            this.btnRefreshRevUsersList.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRefreshRevUsersList.Location = new System.Drawing.Point(25, 18);
            this.btnRefreshRevUsersList.Name = "btnRefreshRevUsersList";
            this.btnRefreshRevUsersList.Size = new System.Drawing.Size(355, 41);
            this.btnRefreshRevUsersList.TabIndex = 33;
            this.btnRefreshRevUsersList.Text = "Refresh user accounts list";
            this.btnRefreshRevUsersList.UseVisualStyleBackColor = true;
            this.btnRefreshRevUsersList.Click += new System.EventHandler(this.btnRefreshRevUsersList_Click);
            // 
            // accountsListView
            // 
            this.accountsListView.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.accountsListView.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.accountsListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.userNameColumnHeader});
            this.accountsListView.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.accountsListView.FullRowSelect = true;
            this.accountsListView.Location = new System.Drawing.Point(25, 67);
            this.accountsListView.MultiSelect = false;
            this.accountsListView.Name = "accountsListView";
            this.accountsListView.Size = new System.Drawing.Size(355, 304);
            this.accountsListView.SmallImageList = this.usersImageList;
            this.accountsListView.TabIndex = 29;
            this.accountsListView.UseCompatibleStateImageBehavior = false;
            this.accountsListView.View = System.Windows.Forms.View.Details;
            this.accountsListView.DoubleClick += new System.EventHandler(this.btnReverseLink_Click);
            // 
            // userNameColumnHeader
            // 
            this.userNameColumnHeader.Text = "User name";
            this.userNameColumnHeader.Width = 336;
            // 
            // usersImageList
            // 
            this.usersImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("usersImageList.ImageStream")));
            this.usersImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.usersImageList.Images.SetKeyName(0, "user_16.png");
            this.usersImageList.Images.SetKeyName(1, "users.png");
            this.usersImageList.Images.SetKeyName(2, "users.png");
            // 
            // btnReverseLink
            // 
            this.btnReverseLink.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnReverseLink.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnReverseLink.Image = ((System.Drawing.Image)(resources.GetObject("btnReverseLink.Image")));
            this.btnReverseLink.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnReverseLink.Location = new System.Drawing.Point(28, 379);
            this.btnReverseLink.Name = "btnReverseLink";
            this.btnReverseLink.Size = new System.Drawing.Size(352, 41);
            this.btnReverseLink.TabIndex = 30;
            this.btnReverseLink.Text = "Link selected account";
            this.btnReverseLink.UseVisualStyleBackColor = true;
            this.btnReverseLink.Click += new System.EventHandler(this.btnReverseLink_Click);
            // 
            // revLinkGroupsTabPage
            // 
            this.revLinkGroupsTabPage.Controls.Add(this.btnRefreshRevGroupsList);
            this.revLinkGroupsTabPage.Controls.Add(this.groupsListView);
            this.revLinkGroupsTabPage.Controls.Add(this.btnReverseGroupLink);
            this.revLinkGroupsTabPage.ImageIndex = 1;
            this.revLinkGroupsTabPage.Location = new System.Drawing.Point(4, 23);
            this.revLinkGroupsTabPage.Name = "revLinkGroupsTabPage";
            this.revLinkGroupsTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.revLinkGroupsTabPage.Size = new System.Drawing.Size(404, 435);
            this.revLinkGroupsTabPage.TabIndex = 1;
            this.revLinkGroupsTabPage.Text = "Reverse linking of user groups";
            this.revLinkGroupsTabPage.UseVisualStyleBackColor = true;
            // 
            // btnRefreshRevGroupsList
            // 
            this.btnRefreshRevGroupsList.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnRefreshRevGroupsList.Image = ((System.Drawing.Image)(resources.GetObject("btnRefreshRevGroupsList.Image")));
            this.btnRefreshRevGroupsList.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRefreshRevGroupsList.Location = new System.Drawing.Point(24, 16);
            this.btnRefreshRevGroupsList.Name = "btnRefreshRevGroupsList";
            this.btnRefreshRevGroupsList.Size = new System.Drawing.Size(355, 41);
            this.btnRefreshRevGroupsList.TabIndex = 36;
            this.btnRefreshRevGroupsList.Text = "Refresh user groups list";
            this.btnRefreshRevGroupsList.UseVisualStyleBackColor = true;
            this.btnRefreshRevGroupsList.Click += new System.EventHandler(this.btnRefreshRevUsersList_Click);
            // 
            // groupsListView
            // 
            this.groupsListView.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.groupsListView.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.groupsListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.groupNameColumnHeader});
            this.groupsListView.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.groupsListView.FullRowSelect = true;
            this.groupsListView.Location = new System.Drawing.Point(24, 65);
            this.groupsListView.MultiSelect = false;
            this.groupsListView.Name = "groupsListView";
            this.groupsListView.Size = new System.Drawing.Size(355, 304);
            this.groupsListView.SmallImageList = this.usersImageList;
            this.groupsListView.TabIndex = 34;
            this.groupsListView.UseCompatibleStateImageBehavior = false;
            this.groupsListView.View = System.Windows.Forms.View.Details;
            // 
            // groupNameColumnHeader
            // 
            this.groupNameColumnHeader.Text = "Group name";
            this.groupNameColumnHeader.Width = 336;
            // 
            // btnReverseGroupLink
            // 
            this.btnReverseGroupLink.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnReverseGroupLink.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnReverseGroupLink.Image = ((System.Drawing.Image)(resources.GetObject("btnReverseGroupLink.Image")));
            this.btnReverseGroupLink.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnReverseGroupLink.Location = new System.Drawing.Point(27, 377);
            this.btnReverseGroupLink.Name = "btnReverseGroupLink";
            this.btnReverseGroupLink.Size = new System.Drawing.Size(352, 41);
            this.btnReverseGroupLink.TabIndex = 35;
            this.btnReverseGroupLink.Text = "Link selected group";
            this.btnReverseGroupLink.UseVisualStyleBackColor = true;
            this.btnReverseGroupLink.Click += new System.EventHandler(this.btnReverseGroupLink_Click);
            // 
            // syncLogonCheckBox
            // 
            this.syncLogonCheckBox.AutoSize = true;
            this.syncLogonCheckBox.Location = new System.Drawing.Point(23, 150);
            this.syncLogonCheckBox.Name = "syncLogonCheckBox";
            this.syncLogonCheckBox.Size = new System.Drawing.Size(301, 17);
            this.syncLogonCheckBox.TabIndex = 32;
            this.syncLogonCheckBox.Text = "Enable synchronization of user accounts during user logon";
            this.syncLogonCheckBox.UseVisualStyleBackColor = true;
            // 
            // lblLogonSyncSettings
            // 
            this.lblLogonSyncSettings.AutoSize = true;
            this.lblLogonSyncSettings.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblLogonSyncSettings.Location = new System.Drawing.Point(20, 121);
            this.lblLogonSyncSettings.Name = "lblLogonSyncSettings";
            this.lblLogonSyncSettings.Size = new System.Drawing.Size(241, 16);
            this.lblLogonSyncSettings.TabIndex = 31;
            this.lblLogonSyncSettings.Text = "Synchronization during user logon";
            // 
            // revSyncAuthSystemsComboBox
            // 
            this.revSyncAuthSystemsComboBox.FormattingEnabled = true;
            this.revSyncAuthSystemsComboBox.Location = new System.Drawing.Point(190, 298);
            this.revSyncAuthSystemsComboBox.Name = "revSyncAuthSystemsComboBox";
            this.revSyncAuthSystemsComboBox.Size = new System.Drawing.Size(238, 21);
            this.revSyncAuthSystemsComboBox.TabIndex = 28;
            this.revSyncAuthSystemsComboBox.SelectedIndexChanged += new System.EventHandler(this.revSyncAuthSystemsComboBox_SelectedIndexChanged);
            // 
            // lblReverseSyncAuthSystem
            // 
            this.lblReverseSyncAuthSystem.AutoSize = true;
            this.lblReverseSyncAuthSystem.Location = new System.Drawing.Point(21, 302);
            this.lblReverseSyncAuthSystem.Name = "lblReverseSyncAuthSystem";
            this.lblReverseSyncAuthSystem.Size = new System.Drawing.Size(151, 13);
            this.lblReverseSyncAuthSystem.TabIndex = 27;
            this.lblReverseSyncAuthSystem.Text = "Choose authentication system:";
            // 
            // lblReverseSyncSettings
            // 
            this.lblReverseSyncSettings.AutoSize = true;
            this.lblReverseSyncSettings.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblReverseSyncSettings.Location = new System.Drawing.Point(20, 276);
            this.lblReverseSyncSettings.Name = "lblReverseSyncSettings";
            this.lblReverseSyncSettings.Size = new System.Drawing.Size(116, 16);
            this.lblReverseSyncSettings.TabIndex = 26;
            this.lblReverseSyncSettings.Text = "Reverse linking";
            // 
            // btnForcedSync
            // 
            this.btnForcedSync.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnForcedSync.Image = ((System.Drawing.Image)(resources.GetObject("btnForcedSync.Image")));
            this.btnForcedSync.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnForcedSync.Location = new System.Drawing.Point(28, 839);
            this.btnForcedSync.Name = "btnForcedSync";
            this.btnForcedSync.Size = new System.Drawing.Size(301, 41);
            this.btnForcedSync.TabIndex = 24;
            this.btnForcedSync.Text = "Synchronize user accounts";
            this.btnForcedSync.UseVisualStyleBackColor = true;
            this.btnForcedSync.Click += new System.EventHandler(this.btnForcedSync_Click);
            // 
            // lblSyncTime
            // 
            this.lblSyncTime.AutoSize = true;
            this.lblSyncTime.Location = new System.Drawing.Point(25, 816);
            this.lblSyncTime.Name = "lblSyncTime";
            this.lblSyncTime.Size = new System.Drawing.Size(106, 13);
            this.lblSyncTime.TabIndex = 23;
            this.lblSyncTime.Text = "Last synchronization:";
            // 
            // btnSaveSyncSettings
            // 
            this.btnSaveSyncSettings.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSaveSyncSettings.Image = ((System.Drawing.Image)(resources.GetObject("btnSaveSyncSettings.Image")));
            this.btnSaveSyncSettings.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnSaveSyncSettings.Location = new System.Drawing.Point(23, 195);
            this.btnSaveSyncSettings.Name = "btnSaveSyncSettings";
            this.btnSaveSyncSettings.Size = new System.Drawing.Size(210, 41);
            this.btnSaveSyncSettings.TabIndex = 22;
            this.btnSaveSyncSettings.Text = "Save settings";
            this.btnSaveSyncSettings.UseVisualStyleBackColor = true;
            this.btnSaveSyncSettings.Click += new System.EventHandler(this.btnSaveSyncSettings_Click);
            // 
            // syncPeriodComboBox
            // 
            this.syncPeriodComboBox.FormattingEnabled = true;
            this.syncPeriodComboBox.Items.AddRange(new object[] {
            "Every hour",
            "Every day",
            "Every week"});
            this.syncPeriodComboBox.Location = new System.Drawing.Point(161, 73);
            this.syncPeriodComboBox.Name = "syncPeriodComboBox";
            this.syncPeriodComboBox.Size = new System.Drawing.Size(163, 21);
            this.syncPeriodComboBox.TabIndex = 21;
            // 
            // lblSyncPeriod
            // 
            this.lblSyncPeriod.AutoSize = true;
            this.lblSyncPeriod.Location = new System.Drawing.Point(20, 76);
            this.lblSyncPeriod.Name = "lblSyncPeriod";
            this.lblSyncPeriod.Size = new System.Drawing.Size(134, 13);
            this.lblSyncPeriod.TabIndex = 20;
            this.lblSyncPeriod.Text = "Set synchronization period:";
            // 
            // periodicSyncOnOffCheckBox
            // 
            this.periodicSyncOnOffCheckBox.AutoSize = true;
            this.periodicSyncOnOffCheckBox.Location = new System.Drawing.Point(23, 48);
            this.periodicSyncOnOffCheckBox.Name = "periodicSyncOnOffCheckBox";
            this.periodicSyncOnOffCheckBox.Size = new System.Drawing.Size(257, 17);
            this.periodicSyncOnOffCheckBox.TabIndex = 19;
            this.periodicSyncOnOffCheckBox.Text = "Enable periodic synchronization of user accounts";
            this.periodicSyncOnOffCheckBox.UseVisualStyleBackColor = true;
            // 
            // lblPeriodicSyncSet
            // 
            this.lblPeriodicSyncSet.AutoSize = true;
            this.lblPeriodicSyncSet.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblPeriodicSyncSet.Location = new System.Drawing.Point(20, 19);
            this.lblPeriodicSyncSet.Name = "lblPeriodicSyncSet";
            this.lblPeriodicSyncSet.Size = new System.Drawing.Size(235, 16);
            this.lblPeriodicSyncSet.TabIndex = 18;
            this.lblPeriodicSyncSet.Text = "Periodic synchronization settings";
            // 
            // tabPostLoginSettings
            // 
            this.tabPostLoginSettings.AutoScroll = true;
            this.tabPostLoginSettings.BackColor = System.Drawing.Color.White;
            this.tabPostLoginSettings.Controls.Add(this.postLoginPathButton);
            this.tabPostLoginSettings.Controls.Add(this.postLoginTimeLabel);
            this.tabPostLoginSettings.Controls.Add(this.postLoginPeriodNumUpDown);
            this.tabPostLoginSettings.Controls.Add(this.postLoginPeriodicCheckBox);
            this.tabPostLoginSettings.Controls.Add(this.postLoginPathTextBox);
            this.tabPostLoginSettings.Controls.Add(this.postLoginPathLabel);
            this.tabPostLoginSettings.Controls.Add(this.btnPostLoginSettingsSave);
            this.tabPostLoginSettings.Controls.Add(this.lblPostLoginSettings);
            this.tabPostLoginSettings.Location = new System.Drawing.Point(4, 22);
            this.tabPostLoginSettings.Name = "tabPostLoginSettings";
            this.tabPostLoginSettings.Padding = new System.Windows.Forms.Padding(3);
            this.tabPostLoginSettings.Size = new System.Drawing.Size(707, 605);
            this.tabPostLoginSettings.TabIndex = 7;
            this.tabPostLoginSettings.Text = "Post login";
            // 
            // postLoginPathButton
            // 
            this.postLoginPathButton.Location = new System.Drawing.Point(491, 84);
            this.postLoginPathButton.Name = "postLoginPathButton";
            this.postLoginPathButton.Size = new System.Drawing.Size(26, 23);
            this.postLoginPathButton.TabIndex = 44;
            this.postLoginPathButton.Text = "...";
            this.postLoginPathButton.UseVisualStyleBackColor = true;
            this.postLoginPathButton.Click += new System.EventHandler(this.postLoginPathButton_Click);
            // 
            // postLoginTimeLabel
            // 
            this.postLoginTimeLabel.AutoSize = true;
            this.postLoginTimeLabel.Location = new System.Drawing.Point(493, 141);
            this.postLoginTimeLabel.Name = "postLoginTimeLabel";
            this.postLoginTimeLabel.Size = new System.Drawing.Size(43, 13);
            this.postLoginTimeLabel.TabIndex = 43;
            this.postLoginTimeLabel.Text = "minutes";
            // 
            // postLoginPeriodNumUpDown
            // 
            this.postLoginPeriodNumUpDown.Location = new System.Drawing.Point(255, 137);
            this.postLoginPeriodNumUpDown.Maximum = new decimal(new int[] {
            2147483645,
            0,
            0,
            0});
            this.postLoginPeriodNumUpDown.Name = "postLoginPeriodNumUpDown";
            this.postLoginPeriodNumUpDown.Size = new System.Drawing.Size(232, 20);
            this.postLoginPeriodNumUpDown.TabIndex = 42;
            // 
            // postLoginPeriodicCheckBox
            // 
            this.postLoginPeriodicCheckBox.AutoSize = true;
            this.postLoginPeriodicCheckBox.Location = new System.Drawing.Point(31, 140);
            this.postLoginPeriodicCheckBox.Name = "postLoginPeriodicCheckBox";
            this.postLoginPeriodicCheckBox.Size = new System.Drawing.Size(218, 17);
            this.postLoginPeriodicCheckBox.TabIndex = 41;
            this.postLoginPeriodicCheckBox.Text = "Run post login process periodically every";
            this.postLoginPeriodicCheckBox.UseVisualStyleBackColor = true;
            this.postLoginPeriodicCheckBox.CheckedChanged += new System.EventHandler(this.postLoginPeriodicCheckBox_CheckedChanged);
            // 
            // postLoginPathTextBox
            // 
            this.postLoginPathTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.postLoginPathTextBox.Location = new System.Drawing.Point(229, 86);
            this.postLoginPathTextBox.Name = "postLoginPathTextBox";
            this.postLoginPathTextBox.Size = new System.Drawing.Size(261, 20);
            this.postLoginPathTextBox.TabIndex = 40;
            // 
            // postLoginPathLabel
            // 
            this.postLoginPathLabel.AutoSize = true;
            this.postLoginPathLabel.Location = new System.Drawing.Point(31, 88);
            this.postLoginPathLabel.Name = "postLoginPathLabel";
            this.postLoginPathLabel.Size = new System.Drawing.Size(192, 13);
            this.postLoginPathLabel.TabIndex = 39;
            this.postLoginPathLabel.Text = "The path to the Post Login process file:";
            // 
            // btnPostLoginSettingsSave
            // 
            this.btnPostLoginSettingsSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnPostLoginSettingsSave.Image = ((System.Drawing.Image)(resources.GetObject("btnPostLoginSettingsSave.Image")));
            this.btnPostLoginSettingsSave.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnPostLoginSettingsSave.Location = new System.Drawing.Point(31, 208);
            this.btnPostLoginSettingsSave.Name = "btnPostLoginSettingsSave";
            this.btnPostLoginSettingsSave.Size = new System.Drawing.Size(210, 41);
            this.btnPostLoginSettingsSave.TabIndex = 38;
            this.btnPostLoginSettingsSave.Text = "Save settings";
            this.btnPostLoginSettingsSave.UseVisualStyleBackColor = true;
            this.btnPostLoginSettingsSave.Click += new System.EventHandler(this.btnPostLoginSettingsSave_Click);
            // 
            // lblPostLoginSettings
            // 
            this.lblPostLoginSettings.AutoSize = true;
            this.lblPostLoginSettings.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblPostLoginSettings.Location = new System.Drawing.Point(19, 27);
            this.lblPostLoginSettings.Name = "lblPostLoginSettings";
            this.lblPostLoginSettings.Size = new System.Drawing.Size(216, 16);
            this.lblPostLoginSettings.TabIndex = 37;
            this.lblPostLoginSettings.Text = "POST LOGIN process settings";
            // 
            // tabProgramsControlSettings
            // 
            this.tabProgramsControlSettings.AutoScroll = true;
            this.tabProgramsControlSettings.BackColor = System.Drawing.Color.White;
            this.tabProgramsControlSettings.Controls.Add(this.chbProgramsControlEnabled);
            this.tabProgramsControlSettings.Controls.Add(this.btnProgramsControlSettingsSave);
            this.tabProgramsControlSettings.Controls.Add(this.lblProgramsControlSettings);
            this.tabProgramsControlSettings.Location = new System.Drawing.Point(4, 22);
            this.tabProgramsControlSettings.Name = "tabProgramsControlSettings";
            this.tabProgramsControlSettings.Padding = new System.Windows.Forms.Padding(3);
            this.tabProgramsControlSettings.Size = new System.Drawing.Size(707, 605);
            this.tabProgramsControlSettings.TabIndex = 8;
            this.tabProgramsControlSettings.Text = "Programs control";
            // 
            // chbProgramsControlEnabled
            // 
            this.chbProgramsControlEnabled.AutoSize = true;
            this.chbProgramsControlEnabled.Location = new System.Drawing.Point(47, 88);
            this.chbProgramsControlEnabled.Name = "chbProgramsControlEnabled";
            this.chbProgramsControlEnabled.Size = new System.Drawing.Size(140, 17);
            this.chbProgramsControlEnabled.TabIndex = 40;
            this.chbProgramsControlEnabled.Text = "Enable programs control";
            this.chbProgramsControlEnabled.UseVisualStyleBackColor = true;
            // 
            // btnProgramsControlSettingsSave
            // 
            this.btnProgramsControlSettingsSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnProgramsControlSettingsSave.Image = ((System.Drawing.Image)(resources.GetObject("btnProgramsControlSettingsSave.Image")));
            this.btnProgramsControlSettingsSave.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnProgramsControlSettingsSave.Location = new System.Drawing.Point(47, 152);
            this.btnProgramsControlSettingsSave.Name = "btnProgramsControlSettingsSave";
            this.btnProgramsControlSettingsSave.Size = new System.Drawing.Size(210, 41);
            this.btnProgramsControlSettingsSave.TabIndex = 39;
            this.btnProgramsControlSettingsSave.Text = "Save settings";
            this.btnProgramsControlSettingsSave.UseVisualStyleBackColor = true;
            this.btnProgramsControlSettingsSave.Click += new System.EventHandler(this.btnProgramsControlSettingsSave_Click);
            // 
            // lblProgramsControlSettings
            // 
            this.lblProgramsControlSettings.AutoSize = true;
            this.lblProgramsControlSettings.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblProgramsControlSettings.Location = new System.Drawing.Point(19, 27);
            this.lblProgramsControlSettings.Name = "lblProgramsControlSettings";
            this.lblProgramsControlSettings.Size = new System.Drawing.Size(184, 16);
            this.lblProgramsControlSettings.TabIndex = 38;
            this.lblProgramsControlSettings.Text = "Programs control settings";
            // 
            // tabCommandsHistory
            // 
            this.tabCommandsHistory.AutoScroll = true;
            this.tabCommandsHistory.BackColor = System.Drawing.Color.White;
            this.tabCommandsHistory.Controls.Add(this.snapshotCheckBox);
            this.tabCommandsHistory.Controls.Add(this.screenshotCheckBox);
            this.tabCommandsHistory.Controls.Add(this.currentUserNameCheckBox);
            this.tabCommandsHistory.Controls.Add(this.userEnviromentCheckBox);
            this.tabCommandsHistory.Controls.Add(this.commandsHistoryPathButton);
            this.tabCommandsHistory.Controls.Add(this.label3);
            this.tabCommandsHistory.Controls.Add(this.commandsHistoryPeriodNumUpDown);
            this.tabCommandsHistory.Controls.Add(this.commandsHistoryPeriodCheckBox);
            this.tabCommandsHistory.Controls.Add(this.commandsHistoryPathTextBox);
            this.tabCommandsHistory.Controls.Add(this.lblCommandsHistoryPath);
            this.tabCommandsHistory.Controls.Add(this.btnCommandsHistorySettingsSave);
            this.tabCommandsHistory.Controls.Add(this.lblCommandsHistorySettings);
            this.tabCommandsHistory.Location = new System.Drawing.Point(4, 22);
            this.tabCommandsHistory.Name = "tabCommandsHistory";
            this.tabCommandsHistory.Padding = new System.Windows.Forms.Padding(3);
            this.tabCommandsHistory.Size = new System.Drawing.Size(707, 605);
            this.tabCommandsHistory.TabIndex = 9;
            this.tabCommandsHistory.Text = "Commands history";
            // 
            // snapshotCheckBox
            // 
            this.snapshotCheckBox.AutoSize = true;
            this.snapshotCheckBox.Location = new System.Drawing.Point(37, 348);
            this.snapshotCheckBox.Name = "snapshotCheckBox";
            this.snapshotCheckBox.Size = new System.Drawing.Size(155, 17);
            this.snapshotCheckBox.TabIndex = 56;
            this.snapshotCheckBox.Text = "Get WEB-camera snapshot";
            this.snapshotCheckBox.UseVisualStyleBackColor = true;
            // 
            // screenshotCheckBox
            // 
            this.screenshotCheckBox.AutoSize = true;
            this.screenshotCheckBox.Location = new System.Drawing.Point(37, 305);
            this.screenshotCheckBox.Name = "screenshotCheckBox";
            this.screenshotCheckBox.Size = new System.Drawing.Size(98, 17);
            this.screenshotCheckBox.TabIndex = 55;
            this.screenshotCheckBox.Text = "Get screenshot";
            this.screenshotCheckBox.UseVisualStyleBackColor = true;
            // 
            // currentUserNameCheckBox
            // 
            this.currentUserNameCheckBox.AutoSize = true;
            this.currentUserNameCheckBox.Location = new System.Drawing.Point(37, 220);
            this.currentUserNameCheckBox.Name = "currentUserNameCheckBox";
            this.currentUserNameCheckBox.Size = new System.Drawing.Size(131, 17);
            this.currentUserNameCheckBox.TabIndex = 54;
            this.currentUserNameCheckBox.Text = "Get current user name";
            this.currentUserNameCheckBox.UseVisualStyleBackColor = true;
            // 
            // userEnviromentCheckBox
            // 
            this.userEnviromentCheckBox.AutoSize = true;
            this.userEnviromentCheckBox.Location = new System.Drawing.Point(37, 262);
            this.userEnviromentCheckBox.Name = "userEnviromentCheckBox";
            this.userEnviromentCheckBox.Size = new System.Drawing.Size(163, 17);
            this.userEnviromentCheckBox.TabIndex = 53;
            this.userEnviromentCheckBox.Text = "Get current user environment";
            this.userEnviromentCheckBox.UseVisualStyleBackColor = true;
            // 
            // commandsHistoryPathButton
            // 
            this.commandsHistoryPathButton.Location = new System.Drawing.Point(529, 93);
            this.commandsHistoryPathButton.Name = "commandsHistoryPathButton";
            this.commandsHistoryPathButton.Size = new System.Drawing.Size(26, 23);
            this.commandsHistoryPathButton.TabIndex = 52;
            this.commandsHistoryPathButton.Text = "...";
            this.commandsHistoryPathButton.UseVisualStyleBackColor = true;
            this.commandsHistoryPathButton.Click += new System.EventHandler(this.commandsHistoryPathButton_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(510, 148);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(43, 13);
            this.label3.TabIndex = 51;
            this.label3.Text = "minutes";
            // 
            // commandsHistoryPeriodNumUpDown
            // 
            this.commandsHistoryPeriodNumUpDown.Location = new System.Drawing.Point(269, 145);
            this.commandsHistoryPeriodNumUpDown.Maximum = new decimal(new int[] {
            2147483645,
            0,
            0,
            0});
            this.commandsHistoryPeriodNumUpDown.Name = "commandsHistoryPeriodNumUpDown";
            this.commandsHistoryPeriodNumUpDown.Size = new System.Drawing.Size(232, 20);
            this.commandsHistoryPeriodNumUpDown.TabIndex = 50;
            // 
            // commandsHistoryPeriodCheckBox
            // 
            this.commandsHistoryPeriodCheckBox.AutoSize = true;
            this.commandsHistoryPeriodCheckBox.Location = new System.Drawing.Point(37, 148);
            this.commandsHistoryPeriodCheckBox.Name = "commandsHistoryPeriodCheckBox";
            this.commandsHistoryPeriodCheckBox.Size = new System.Drawing.Size(230, 17);
            this.commandsHistoryPeriodCheckBox.TabIndex = 49;
            this.commandsHistoryPeriodCheckBox.Text = "Save current machine state to history every";
            this.commandsHistoryPeriodCheckBox.UseVisualStyleBackColor = true;
            this.commandsHistoryPeriodCheckBox.CheckedChanged += new System.EventHandler(this.commandsHistoryPeriodCheckBox_CheckedChanged);
            // 
            // commandsHistoryPathTextBox
            // 
            this.commandsHistoryPathTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.commandsHistoryPathTextBox.Location = new System.Drawing.Point(267, 94);
            this.commandsHistoryPathTextBox.Name = "commandsHistoryPathTextBox";
            this.commandsHistoryPathTextBox.Size = new System.Drawing.Size(261, 20);
            this.commandsHistoryPathTextBox.TabIndex = 48;
            // 
            // lblCommandsHistoryPath
            // 
            this.lblCommandsHistoryPath.AutoSize = true;
            this.lblCommandsHistoryPath.Location = new System.Drawing.Point(37, 96);
            this.lblCommandsHistoryPath.Name = "lblCommandsHistoryPath";
            this.lblCommandsHistoryPath.Size = new System.Drawing.Size(217, 13);
            this.lblCommandsHistoryPath.TabIndex = 47;
            this.lblCommandsHistoryPath.Text = "The path to the commands history database:";
            // 
            // btnCommandsHistorySettingsSave
            // 
            this.btnCommandsHistorySettingsSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnCommandsHistorySettingsSave.Image = ((System.Drawing.Image)(resources.GetObject("btnCommandsHistorySettingsSave.Image")));
            this.btnCommandsHistorySettingsSave.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnCommandsHistorySettingsSave.Location = new System.Drawing.Point(37, 430);
            this.btnCommandsHistorySettingsSave.Name = "btnCommandsHistorySettingsSave";
            this.btnCommandsHistorySettingsSave.Size = new System.Drawing.Size(210, 41);
            this.btnCommandsHistorySettingsSave.TabIndex = 46;
            this.btnCommandsHistorySettingsSave.Text = "Save settings";
            this.btnCommandsHistorySettingsSave.UseVisualStyleBackColor = true;
            this.btnCommandsHistorySettingsSave.Click += new System.EventHandler(this.btnCommandsHistorySettingsSave_Click);
            // 
            // lblCommandsHistorySettings
            // 
            this.lblCommandsHistorySettings.AutoSize = true;
            this.lblCommandsHistorySettings.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblCommandsHistorySettings.Location = new System.Drawing.Point(25, 35);
            this.lblCommandsHistorySettings.Name = "lblCommandsHistorySettings";
            this.lblCommandsHistorySettings.Size = new System.Drawing.Size(199, 16);
            this.lblCommandsHistorySettings.TabIndex = 45;
            this.lblCommandsHistorySettings.Text = "Commands logging settings";
            // 
            // tabFileTransferSettings
            // 
            this.tabFileTransferSettings.AutoScroll = true;
            this.tabFileTransferSettings.BackColor = System.Drawing.Color.White;
            this.tabFileTransferSettings.Controls.Add(this.tempDirectoryButton);
            this.tabFileTransferSettings.Controls.Add(this.tempDirectoryTextBox);
            this.tabFileTransferSettings.Controls.Add(this.lblTempDirectory);
            this.tabFileTransferSettings.Controls.Add(this.downloadDirectoryButton);
            this.tabFileTransferSettings.Controls.Add(this.downloadDirectoryTextBox);
            this.tabFileTransferSettings.Controls.Add(this.lblDownloadDirectory);
            this.tabFileTransferSettings.Controls.Add(this.uploadDirectoryButton);
            this.tabFileTransferSettings.Controls.Add(this.uploadDirectoryTextBox);
            this.tabFileTransferSettings.Controls.Add(this.lblUploadDirectory);
            this.tabFileTransferSettings.Controls.Add(this.btnFileTransferSettings);
            this.tabFileTransferSettings.Controls.Add(this.lblFileTransferSettings);
            this.tabFileTransferSettings.Location = new System.Drawing.Point(4, 22);
            this.tabFileTransferSettings.Name = "tabFileTransferSettings";
            this.tabFileTransferSettings.Padding = new System.Windows.Forms.Padding(3);
            this.tabFileTransferSettings.Size = new System.Drawing.Size(707, 605);
            this.tabFileTransferSettings.TabIndex = 10;
            this.tabFileTransferSettings.Text = "File transfer";
            // 
            // tempDirectoryButton
            // 
            this.tempDirectoryButton.Location = new System.Drawing.Point(418, 167);
            this.tempDirectoryButton.Name = "tempDirectoryButton";
            this.tempDirectoryButton.Size = new System.Drawing.Size(26, 23);
            this.tempDirectoryButton.TabIndex = 70;
            this.tempDirectoryButton.Tag = "3";
            this.tempDirectoryButton.Text = "...";
            this.tempDirectoryButton.UseVisualStyleBackColor = true;
            this.tempDirectoryButton.Click += new System.EventHandler(this.uploadDirectoryButton_Click);
            // 
            // tempDirectoryTextBox
            // 
            this.tempDirectoryTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tempDirectoryTextBox.Location = new System.Drawing.Point(156, 168);
            this.tempDirectoryTextBox.Name = "tempDirectoryTextBox";
            this.tempDirectoryTextBox.Size = new System.Drawing.Size(261, 20);
            this.tempDirectoryTextBox.TabIndex = 69;
            // 
            // lblTempDirectory
            // 
            this.lblTempDirectory.AutoSize = true;
            this.lblTempDirectory.Location = new System.Drawing.Point(45, 170);
            this.lblTempDirectory.Name = "lblTempDirectory";
            this.lblTempDirectory.Size = new System.Drawing.Size(103, 13);
            this.lblTempDirectory.TabIndex = 68;
            this.lblTempDirectory.Text = "Temporary directory:";
            // 
            // downloadDirectoryButton
            // 
            this.downloadDirectoryButton.Location = new System.Drawing.Point(418, 128);
            this.downloadDirectoryButton.Name = "downloadDirectoryButton";
            this.downloadDirectoryButton.Size = new System.Drawing.Size(26, 23);
            this.downloadDirectoryButton.TabIndex = 67;
            this.downloadDirectoryButton.Tag = "2";
            this.downloadDirectoryButton.Text = "...";
            this.downloadDirectoryButton.UseVisualStyleBackColor = true;
            this.downloadDirectoryButton.Click += new System.EventHandler(this.uploadDirectoryButton_Click);
            // 
            // downloadDirectoryTextBox
            // 
            this.downloadDirectoryTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.downloadDirectoryTextBox.Location = new System.Drawing.Point(156, 129);
            this.downloadDirectoryTextBox.Name = "downloadDirectoryTextBox";
            this.downloadDirectoryTextBox.Size = new System.Drawing.Size(261, 20);
            this.downloadDirectoryTextBox.TabIndex = 66;
            // 
            // lblDownloadDirectory
            // 
            this.lblDownloadDirectory.AutoSize = true;
            this.lblDownloadDirectory.Location = new System.Drawing.Point(45, 131);
            this.lblDownloadDirectory.Name = "lblDownloadDirectory";
            this.lblDownloadDirectory.Size = new System.Drawing.Size(101, 13);
            this.lblDownloadDirectory.TabIndex = 65;
            this.lblDownloadDirectory.Text = "Download directory:";
            // 
            // uploadDirectoryButton
            // 
            this.uploadDirectoryButton.Location = new System.Drawing.Point(418, 88);
            this.uploadDirectoryButton.Name = "uploadDirectoryButton";
            this.uploadDirectoryButton.Size = new System.Drawing.Size(26, 23);
            this.uploadDirectoryButton.TabIndex = 64;
            this.uploadDirectoryButton.Tag = "1";
            this.uploadDirectoryButton.Text = "...";
            this.uploadDirectoryButton.UseVisualStyleBackColor = true;
            this.uploadDirectoryButton.Click += new System.EventHandler(this.uploadDirectoryButton_Click);
            // 
            // uploadDirectoryTextBox
            // 
            this.uploadDirectoryTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.uploadDirectoryTextBox.Location = new System.Drawing.Point(156, 89);
            this.uploadDirectoryTextBox.Name = "uploadDirectoryTextBox";
            this.uploadDirectoryTextBox.Size = new System.Drawing.Size(261, 20);
            this.uploadDirectoryTextBox.TabIndex = 60;
            // 
            // lblUploadDirectory
            // 
            this.lblUploadDirectory.AutoSize = true;
            this.lblUploadDirectory.Location = new System.Drawing.Point(45, 91);
            this.lblUploadDirectory.Name = "lblUploadDirectory";
            this.lblUploadDirectory.Size = new System.Drawing.Size(87, 13);
            this.lblUploadDirectory.TabIndex = 59;
            this.lblUploadDirectory.Text = "Upload directory:";
            // 
            // btnFileTransferSettings
            // 
            this.btnFileTransferSettings.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnFileTransferSettings.Image = ((System.Drawing.Image)(resources.GetObject("btnFileTransferSettings.Image")));
            this.btnFileTransferSettings.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnFileTransferSettings.Location = new System.Drawing.Point(48, 237);
            this.btnFileTransferSettings.Name = "btnFileTransferSettings";
            this.btnFileTransferSettings.Size = new System.Drawing.Size(210, 41);
            this.btnFileTransferSettings.TabIndex = 58;
            this.btnFileTransferSettings.Text = "Save settings";
            this.btnFileTransferSettings.UseVisualStyleBackColor = true;
            this.btnFileTransferSettings.Click += new System.EventHandler(this.btnFileTransferSettings_Click);
            // 
            // lblFileTransferSettings
            // 
            this.lblFileTransferSettings.AutoSize = true;
            this.lblFileTransferSettings.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblFileTransferSettings.Location = new System.Drawing.Point(33, 30);
            this.lblFileTransferSettings.Name = "lblFileTransferSettings";
            this.lblFileTransferSettings.Size = new System.Drawing.Size(148, 16);
            this.lblFileTransferSettings.TabIndex = 57;
            this.lblFileTransferSettings.Text = "File transfer settings";
            // 
            // tabUpdateSettings
            // 
            this.tabUpdateSettings.AutoScroll = true;
            this.tabUpdateSettings.BackColor = System.Drawing.Color.White;
            this.tabUpdateSettings.Controls.Add(this.updateDirPathButton);
            this.tabUpdateSettings.Controls.Add(this.updateDirPathTextBox);
            this.tabUpdateSettings.Controls.Add(this.label2);
            this.tabUpdateSettings.Controls.Add(this.updaterPathButton);
            this.tabUpdateSettings.Controls.Add(this.updaterPathTextBox);
            this.tabUpdateSettings.Controls.Add(this.lblUpdaterPath);
            this.tabUpdateSettings.Controls.Add(this.lblUpdateHours);
            this.tabUpdateSettings.Controls.Add(this.updatesPeriodNumericUpDown);
            this.tabUpdateSettings.Controls.Add(this.updatesEnableCheckBox);
            this.tabUpdateSettings.Controls.Add(this.btnUpdateSettingsSave);
            this.tabUpdateSettings.Controls.Add(this.lblUpdateSettings);
            this.tabUpdateSettings.Location = new System.Drawing.Point(4, 22);
            this.tabUpdateSettings.Name = "tabUpdateSettings";
            this.tabUpdateSettings.Padding = new System.Windows.Forms.Padding(3);
            this.tabUpdateSettings.Size = new System.Drawing.Size(707, 605);
            this.tabUpdateSettings.TabIndex = 11;
            this.tabUpdateSettings.Text = "Update settings";
            // 
            // updateDirPathButton
            // 
            this.updateDirPathButton.Location = new System.Drawing.Point(529, 145);
            this.updateDirPathButton.Name = "updateDirPathButton";
            this.updateDirPathButton.Size = new System.Drawing.Size(26, 23);
            this.updateDirPathButton.TabIndex = 60;
            this.updateDirPathButton.Text = "...";
            this.updateDirPathButton.UseVisualStyleBackColor = true;
            this.updateDirPathButton.Click += new System.EventHandler(this.updateDirPathButton_Click);
            // 
            // updateDirPathTextBox
            // 
            this.updateDirPathTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.updateDirPathTextBox.Location = new System.Drawing.Point(267, 146);
            this.updateDirPathTextBox.Name = "updateDirPathTextBox";
            this.updateDirPathTextBox.Size = new System.Drawing.Size(261, 20);
            this.updateDirPathTextBox.TabIndex = 59;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(58, 148);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(144, 13);
            this.label2.TabIndex = 58;
            this.label2.Text = "The path to update directory:";
            // 
            // updaterPathButton
            // 
            this.updaterPathButton.Location = new System.Drawing.Point(529, 184);
            this.updaterPathButton.Name = "updaterPathButton";
            this.updaterPathButton.Size = new System.Drawing.Size(26, 23);
            this.updaterPathButton.TabIndex = 57;
            this.updaterPathButton.Text = "...";
            this.updaterPathButton.UseVisualStyleBackColor = true;
            this.updaterPathButton.Click += new System.EventHandler(this.updaterPathButton_Click);
            // 
            // updaterPathTextBox
            // 
            this.updaterPathTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.updaterPathTextBox.Location = new System.Drawing.Point(267, 185);
            this.updaterPathTextBox.Name = "updaterPathTextBox";
            this.updaterPathTextBox.Size = new System.Drawing.Size(261, 20);
            this.updaterPathTextBox.TabIndex = 56;
            // 
            // lblUpdaterPath
            // 
            this.lblUpdaterPath.AutoSize = true;
            this.lblUpdaterPath.Location = new System.Drawing.Point(58, 187);
            this.lblUpdaterPath.Name = "lblUpdaterPath";
            this.lblUpdaterPath.Size = new System.Drawing.Size(203, 13);
            this.lblUpdaterPath.TabIndex = 55;
            this.lblUpdaterPath.Text = "The path to the UI module of the updater ";
            // 
            // lblUpdateHours
            // 
            this.lblUpdateHours.AutoSize = true;
            this.lblUpdateHours.Location = new System.Drawing.Point(508, 107);
            this.lblUpdateHours.Name = "lblUpdateHours";
            this.lblUpdateHours.Size = new System.Drawing.Size(33, 13);
            this.lblUpdateHours.TabIndex = 54;
            this.lblUpdateHours.Text = "hours";
            // 
            // updatesPeriodNumericUpDown
            // 
            this.updatesPeriodNumericUpDown.Location = new System.Drawing.Point(267, 104);
            this.updatesPeriodNumericUpDown.Maximum = new decimal(new int[] {
            2147483645,
            0,
            0,
            0});
            this.updatesPeriodNumericUpDown.Name = "updatesPeriodNumericUpDown";
            this.updatesPeriodNumericUpDown.Size = new System.Drawing.Size(232, 20);
            this.updatesPeriodNumericUpDown.TabIndex = 53;
            // 
            // updatesEnableCheckBox
            // 
            this.updatesEnableCheckBox.AutoSize = true;
            this.updatesEnableCheckBox.Location = new System.Drawing.Point(61, 106);
            this.updatesEnableCheckBox.Name = "updatesEnableCheckBox";
            this.updatesEnableCheckBox.Size = new System.Drawing.Size(142, 17);
            this.updatesEnableCheckBox.TabIndex = 52;
            this.updatesEnableCheckBox.Text = "Check for updates every";
            this.updatesEnableCheckBox.UseVisualStyleBackColor = true;
            this.updatesEnableCheckBox.CheckedChanged += new System.EventHandler(this.updatesEnableCheckBox_CheckedChanged);
            // 
            // btnUpdateSettingsSave
            // 
            this.btnUpdateSettingsSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnUpdateSettingsSave.Image = ((System.Drawing.Image)(resources.GetObject("btnUpdateSettingsSave.Image")));
            this.btnUpdateSettingsSave.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnUpdateSettingsSave.Location = new System.Drawing.Point(61, 268);
            this.btnUpdateSettingsSave.Name = "btnUpdateSettingsSave";
            this.btnUpdateSettingsSave.Size = new System.Drawing.Size(210, 41);
            this.btnUpdateSettingsSave.TabIndex = 42;
            this.btnUpdateSettingsSave.Text = "Save settings";
            this.btnUpdateSettingsSave.UseVisualStyleBackColor = true;
            this.btnUpdateSettingsSave.Click += new System.EventHandler(this.btnUpdateSettingsSave_Click);
            // 
            // lblUpdateSettings
            // 
            this.lblUpdateSettings.AutoSize = true;
            this.lblUpdateSettings.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblUpdateSettings.Location = new System.Drawing.Point(17, 29);
            this.lblUpdateSettings.Name = "lblUpdateSettings";
            this.lblUpdateSettings.Size = new System.Drawing.Size(205, 16);
            this.lblUpdateSettings.TabIndex = 41;
            this.lblUpdateSettings.Text = "The update process settings";
            // 
            // splitter28
            // 
            this.splitter28.Location = new System.Drawing.Point(279, 3);
            this.splitter28.Name = "splitter28";
            this.splitter28.Size = new System.Drawing.Size(3, 631);
            this.splitter28.TabIndex = 2;
            this.splitter28.TabStop = false;
            // 
            // confTreeView
            // 
            this.confTreeView.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.confTreeView.Dock = System.Windows.Forms.DockStyle.Left;
            this.confTreeView.ImageIndex = 0;
            this.confTreeView.ImageList = this.confImageList;
            this.confTreeView.Location = new System.Drawing.Point(3, 3);
            this.confTreeView.Name = "confTreeView";
            treeNode1.ImageIndex = 1;
            treeNode1.Name = "nodeServicesControl";
            treeNode1.Text = "Services management";
            treeNode2.ImageIndex = 2;
            treeNode2.Name = "nodeIPC";
            treeNode2.Text = "IPC settings";
            treeNode3.ImageIndex = 6;
            treeNode3.Name = "nodeDatabase";
            treeNode3.Text = "Database settings";
            treeNode4.ImageIndex = 7;
            treeNode4.Name = "nodeMessages";
            treeNode4.Text = "Messaging settings";
            treeNode5.ImageIndex = 5;
            treeNode5.Name = "nodeLOG";
            treeNode5.Text = "LOG-files settings";
            treeNode6.ImageIndex = 12;
            treeNode6.Name = "nodePostLogin";
            treeNode6.Text = "Post Login process settings";
            treeNode7.ImageIndex = 11;
            treeNode7.Name = "nodeProgramsControl";
            treeNode7.Text = "Programs control";
            treeNode8.ImageIndex = 13;
            treeNode8.Name = "nodeCommandsHistory";
            treeNode8.Text = "Commands history";
            treeNode9.ImageIndex = 14;
            treeNode9.Name = "nodeFileTransferSettings";
            treeNode9.Text = "File transfer settings";
            treeNode10.ImageIndex = 15;
            treeNode10.Name = "nodeUpdateSettings";
            treeNode10.Text = "Update settings";
            treeNode11.ImageIndex = 0;
            treeNode11.Name = "nodeSettings";
            treeNode11.Text = "Services configuration";
            treeNode12.ImageIndex = 10;
            treeNode12.Name = "nodeSynchronization";
            treeNode12.Text = "User accounts synchronization";
            this.confTreeView.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode11,
            treeNode12});
            this.confTreeView.SelectedImageIndex = 0;
            this.confTreeView.ShowPlusMinus = false;
            this.confTreeView.Size = new System.Drawing.Size(276, 631);
            this.confTreeView.TabIndex = 1;
            this.confTreeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.confTreeView_AfterSelect);
            // 
            // personalTabPage
            // 
            this.personalTabPage.Controls.Add(this.personalPanel);
            this.personalTabPage.ImageIndex = 8;
            this.personalTabPage.Location = new System.Drawing.Point(4, 42);
            this.personalTabPage.Name = "personalTabPage";
            this.personalTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.personalTabPage.Size = new System.Drawing.Size(1000, 637);
            this.personalTabPage.TabIndex = 7;
            this.personalTabPage.Text = "Personal data";
            this.personalTabPage.UseVisualStyleBackColor = true;
            // 
            // personalPanel
            // 
            this.personalPanel.BackColor = System.Drawing.Color.White;
            this.personalPanel.Controls.Add(this.personalAccoutsParametersPanel);
            this.personalPanel.Controls.Add(this.personalPwdSettingsPanel);
            this.personalPanel.Controls.Add(this.personalPasswrodSettingLabel);
            this.personalPanel.Controls.Add(this.personalVerticalSplitPanel);
            this.personalPanel.Controls.Add(this.refreshUserButton);
            this.personalPanel.Controls.Add(this.saveUserButton);
            this.personalPanel.Controls.Add(this.personalGroupsLabel);
            this.personalPanel.Controls.Add(this.personalGroupsListView);
            this.personalPanel.Controls.Add(this.label1);
            this.personalPanel.Controls.Add(this.personalUserPhoneTextBox);
            this.personalPanel.Controls.Add(personalUserPhoneLabel);
            this.personalPanel.Controls.Add(personalUserNameLabel);
            this.personalPanel.Controls.Add(this.personalUserEmailTextBox);
            this.personalPanel.Controls.Add(this.personalUserNameTextBox);
            this.personalPanel.Controls.Add(personalUserEmailLabel);
            this.personalPanel.Controls.Add(personalFullNameLabel);
            this.personalPanel.Controls.Add(this.personalPwdAttemptsLabel);
            this.personalPanel.Controls.Add(this.personalFullNameTextBox);
            this.personalPanel.Controls.Add(this.personalMaxPwdAttemptsLabel);
            this.personalPanel.Controls.Add(this.personalLogonDateLabel);
            this.personalPanel.Controls.Add(this.personalEducationLabel);
            this.personalPanel.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.personalPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.personalPanel.Location = new System.Drawing.Point(3, 3);
            this.personalPanel.Name = "personalPanel";
            this.personalPanel.Size = new System.Drawing.Size(994, 631);
            this.personalPanel.TabIndex = 1;
            // 
            // personalAccoutsParametersPanel
            // 
            this.personalAccoutsParametersPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.personalAccoutsParametersPanel.Controls.Add(this.personalAccountsParametersSplitContainer);
            this.personalAccoutsParametersPanel.Location = new System.Drawing.Point(431, 329);
            this.personalAccoutsParametersPanel.Name = "personalAccoutsParametersPanel";
            this.personalAccoutsParametersPanel.Size = new System.Drawing.Size(558, 291);
            this.personalAccoutsParametersPanel.TabIndex = 146;
            // 
            // personalAccountsParametersSplitContainer
            // 
            this.personalAccountsParametersSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.personalAccountsParametersSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.personalAccountsParametersSplitContainer.Name = "personalAccountsParametersSplitContainer";
            this.personalAccountsParametersSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // personalAccountsParametersSplitContainer.Panel1
            // 
            this.personalAccountsParametersSplitContainer.Panel1.Controls.Add(this.personalUserAccountsGroupBox);
            this.personalAccountsParametersSplitContainer.Panel1.Controls.Add(this.personalAccountsHeaderPanel);
            // 
            // personalAccountsParametersSplitContainer.Panel2
            // 
            this.personalAccountsParametersSplitContainer.Panel2.Controls.Add(this.personalParametersGroupBox);
            this.personalAccountsParametersSplitContainer.Panel2.Controls.Add(this.personalCheckValuesHeaderPanel);
            this.personalAccountsParametersSplitContainer.Size = new System.Drawing.Size(558, 291);
            this.personalAccountsParametersSplitContainer.SplitterDistance = 143;
            this.personalAccountsParametersSplitContainer.TabIndex = 0;
            // 
            // personalUserAccountsGroupBox
            // 
            this.personalUserAccountsGroupBox.Controls.Add(this.personalAccountsDataGridView);
            this.personalUserAccountsGroupBox.Controls.Add(this.personalAccountsBindingNavigator);
            this.personalUserAccountsGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.personalUserAccountsGroupBox.Location = new System.Drawing.Point(0, 28);
            this.personalUserAccountsGroupBox.Name = "personalUserAccountsGroupBox";
            this.personalUserAccountsGroupBox.Size = new System.Drawing.Size(558, 115);
            this.personalUserAccountsGroupBox.TabIndex = 2;
            this.personalUserAccountsGroupBox.TabStop = false;
            this.personalUserAccountsGroupBox.Text = "User accounts";
            // 
            // personalAccountsDataGridView
            // 
            this.personalAccountsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.personalAccountsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.personalAuthSystemNameColumn,
            this.personalUserNameColumn,
            this.personalUserPasswordColumn,
            this.personalPassThruPwdColumn,
            this.personalLastLogonDateColumn});
            this.personalAccountsDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.personalAccountsDataGridView.Location = new System.Drawing.Point(3, 41);
            this.personalAccountsDataGridView.Name = "personalAccountsDataGridView";
            this.personalAccountsDataGridView.Size = new System.Drawing.Size(552, 71);
            this.personalAccountsDataGridView.TabIndex = 24;
            this.personalAccountsDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.personalAccountsDataGridView_CellFormatting);
            this.personalAccountsDataGridView.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.personalAccountsDataGridView_CellParsing);
            this.personalAccountsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            // 
            // personalAuthSystemNameColumn
            // 
            this.personalAuthSystemNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.personalAuthSystemNameColumn.HeaderText = "System";
            this.personalAuthSystemNameColumn.Name = "personalAuthSystemNameColumn";
            this.personalAuthSystemNameColumn.Width = 120;
            // 
            // personalUserNameColumn
            // 
            this.personalUserNameColumn.HeaderText = "User name";
            this.personalUserNameColumn.Name = "personalUserNameColumn";
            this.personalUserNameColumn.Width = 150;
            // 
            // personalUserPasswordColumn
            // 
            this.personalUserPasswordColumn.HeaderText = "Password";
            this.personalUserPasswordColumn.Name = "personalUserPasswordColumn";
            this.personalUserPasswordColumn.ReadOnly = true;
            this.personalUserPasswordColumn.Width = 150;
            // 
            // personalPassThruPwdColumn
            // 
            this.personalPassThruPwdColumn.HeaderText = "Pass password through";
            this.personalPassThruPwdColumn.Name = "personalPassThruPwdColumn";
            this.personalPassThruPwdColumn.Width = 130;
            // 
            // personalLastLogonDateColumn
            // 
            this.personalLastLogonDateColumn.HeaderText = "Date of last logon";
            this.personalLastLogonDateColumn.Name = "personalLastLogonDateColumn";
            this.personalLastLogonDateColumn.Width = 120;
            // 
            // personalAccountsBindingNavigator
            // 
            this.personalAccountsBindingNavigator.AddNewItem = this.toolStripButton84;
            this.personalAccountsBindingNavigator.CountItem = this.toolStripLabel16;
            this.personalAccountsBindingNavigator.DeleteItem = this.toolStripButton85;
            this.personalAccountsBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton86,
            this.toolStripButton87,
            this.toolStripSeparator47,
            this.toolStripTextBox16,
            this.toolStripLabel16,
            this.toolStripSeparator48,
            this.toolStripButton88,
            this.toolStripButton89,
            this.toolStripSeparator49,
            this.toolStripButton84,
            this.toolStripButton85,
            this.personalAccountsBindingNavigatorSaveItem,
            this.personalAccountsBindingNavigatorRefreshItem,
            this.toolStripSeparator44,
            this.personalAccountsBindingNavigatorChangePwdItem});
            this.personalAccountsBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.personalAccountsBindingNavigator.MoveFirstItem = this.toolStripButton86;
            this.personalAccountsBindingNavigator.MoveLastItem = this.toolStripButton89;
            this.personalAccountsBindingNavigator.MoveNextItem = this.toolStripButton88;
            this.personalAccountsBindingNavigator.MovePreviousItem = this.toolStripButton87;
            this.personalAccountsBindingNavigator.Name = "personalAccountsBindingNavigator";
            this.personalAccountsBindingNavigator.PositionItem = this.toolStripTextBox16;
            this.personalAccountsBindingNavigator.Size = new System.Drawing.Size(552, 25);
            this.personalAccountsBindingNavigator.TabIndex = 23;
            this.personalAccountsBindingNavigator.Text = "bindingNavigator2";
            // 
            // toolStripButton84
            // 
            this.toolStripButton84.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton84.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton84.Image")));
            this.toolStripButton84.Name = "toolStripButton84";
            this.toolStripButton84.RightToLeftAutoMirrorImage = true;
            this.toolStripButton84.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton84.Text = "Add new";
            // 
            // toolStripLabel16
            // 
            this.toolStripLabel16.Name = "toolStripLabel16";
            this.toolStripLabel16.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel16.Text = "для {0}";
            this.toolStripLabel16.ToolTipText = "Total number of items";
            // 
            // toolStripButton85
            // 
            this.toolStripButton85.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton85.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton85.Image")));
            this.toolStripButton85.Name = "toolStripButton85";
            this.toolStripButton85.RightToLeftAutoMirrorImage = true;
            this.toolStripButton85.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton85.Text = "Delete";
            // 
            // toolStripButton86
            // 
            this.toolStripButton86.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton86.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton86.Image")));
            this.toolStripButton86.Name = "toolStripButton86";
            this.toolStripButton86.RightToLeftAutoMirrorImage = true;
            this.toolStripButton86.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton86.Text = "Move first";
            // 
            // toolStripButton87
            // 
            this.toolStripButton87.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton87.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton87.Image")));
            this.toolStripButton87.Name = "toolStripButton87";
            this.toolStripButton87.RightToLeftAutoMirrorImage = true;
            this.toolStripButton87.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton87.Text = "Move previous";
            // 
            // toolStripSeparator47
            // 
            this.toolStripSeparator47.Name = "toolStripSeparator47";
            this.toolStripSeparator47.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox16
            // 
            this.toolStripTextBox16.AccessibleName = "Position";
            this.toolStripTextBox16.AutoSize = false;
            this.toolStripTextBox16.Name = "toolStripTextBox16";
            this.toolStripTextBox16.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox16.Text = "0";
            this.toolStripTextBox16.ToolTipText = "Current position";
            // 
            // toolStripSeparator48
            // 
            this.toolStripSeparator48.Name = "toolStripSeparator48";
            this.toolStripSeparator48.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton88
            // 
            this.toolStripButton88.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton88.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton88.Image")));
            this.toolStripButton88.Name = "toolStripButton88";
            this.toolStripButton88.RightToLeftAutoMirrorImage = true;
            this.toolStripButton88.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton88.Text = "Move next";
            // 
            // toolStripButton89
            // 
            this.toolStripButton89.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton89.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton89.Image")));
            this.toolStripButton89.Name = "toolStripButton89";
            this.toolStripButton89.RightToLeftAutoMirrorImage = true;
            this.toolStripButton89.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton89.Text = "Move last";
            // 
            // toolStripSeparator49
            // 
            this.toolStripSeparator49.Name = "toolStripSeparator49";
            this.toolStripSeparator49.Size = new System.Drawing.Size(6, 25);
            // 
            // personalAccountsBindingNavigatorSaveItem
            // 
            this.personalAccountsBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.personalAccountsBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("personalAccountsBindingNavigatorSaveItem.Image")));
            this.personalAccountsBindingNavigatorSaveItem.Name = "personalAccountsBindingNavigatorSaveItem";
            this.personalAccountsBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.personalAccountsBindingNavigatorSaveItem.Text = "Save Data";
            this.personalAccountsBindingNavigatorSaveItem.Click += new System.EventHandler(this.personalAccountsBindingNavigatorSaveItem_Click);
            // 
            // personalAccountsBindingNavigatorRefreshItem
            // 
            this.personalAccountsBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.personalAccountsBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("personalAccountsBindingNavigatorRefreshItem.Image")));
            this.personalAccountsBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.personalAccountsBindingNavigatorRefreshItem.Name = "personalAccountsBindingNavigatorRefreshItem";
            this.personalAccountsBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.personalAccountsBindingNavigatorRefreshItem.Text = "Refresh";
            this.personalAccountsBindingNavigatorRefreshItem.Click += new System.EventHandler(this.personalAccountsBindingNavigatorRefreshItem_Click);
            // 
            // toolStripSeparator44
            // 
            this.toolStripSeparator44.Name = "toolStripSeparator44";
            this.toolStripSeparator44.Size = new System.Drawing.Size(6, 25);
            // 
            // personalAccountsBindingNavigatorChangePwdItem
            // 
            this.personalAccountsBindingNavigatorChangePwdItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.personalAccountsBindingNavigatorChangePwdItem.Image = ((System.Drawing.Image)(resources.GetObject("personalAccountsBindingNavigatorChangePwdItem.Image")));
            this.personalAccountsBindingNavigatorChangePwdItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.personalAccountsBindingNavigatorChangePwdItem.Name = "personalAccountsBindingNavigatorChangePwdItem";
            this.personalAccountsBindingNavigatorChangePwdItem.Size = new System.Drawing.Size(23, 22);
            this.personalAccountsBindingNavigatorChangePwdItem.Text = "Change password of current user account";
            this.personalAccountsBindingNavigatorChangePwdItem.Click += new System.EventHandler(this.personalAccountsBindingNavigatorChangePwdItem_Click);
            // 
            // personalAccountsHeaderPanel
            // 
            this.personalAccountsHeaderPanel.Controls.Add(this.personalAccountsLabel);
            this.personalAccountsHeaderPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.personalAccountsHeaderPanel.Location = new System.Drawing.Point(0, 0);
            this.personalAccountsHeaderPanel.Name = "personalAccountsHeaderPanel";
            this.personalAccountsHeaderPanel.Size = new System.Drawing.Size(558, 28);
            this.personalAccountsHeaderPanel.TabIndex = 0;
            // 
            // personalAccountsLabel
            // 
            this.personalAccountsLabel.AutoSize = true;
            this.personalAccountsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.personalAccountsLabel.Location = new System.Drawing.Point(3, 6);
            this.personalAccountsLabel.Name = "personalAccountsLabel";
            this.personalAccountsLabel.Size = new System.Drawing.Size(185, 16);
            this.personalAccountsLabel.TabIndex = 144;
            this.personalAccountsLabel.Text = "Your accounts infomation:";
            // 
            // personalParametersGroupBox
            // 
            this.personalParametersGroupBox.Controls.Add(this.personalParametersDataGridView);
            this.personalParametersGroupBox.Controls.Add(this.personalParametersBindingNavigator);
            this.personalParametersGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.personalParametersGroupBox.Location = new System.Drawing.Point(0, 28);
            this.personalParametersGroupBox.Name = "personalParametersGroupBox";
            this.personalParametersGroupBox.Size = new System.Drawing.Size(558, 116);
            this.personalParametersGroupBox.TabIndex = 3;
            this.personalParametersGroupBox.TabStop = false;
            this.personalParametersGroupBox.Text = "Parameters for checking";
            // 
            // personalParametersDataGridView
            // 
            this.personalParametersDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.personalParametersDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.personalParameterNameColumn,
            this.personalParameterValueColumn});
            this.personalParametersDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.personalParametersDataGridView.Location = new System.Drawing.Point(3, 41);
            this.personalParametersDataGridView.Name = "personalParametersDataGridView";
            this.personalParametersDataGridView.Size = new System.Drawing.Size(552, 72);
            this.personalParametersDataGridView.TabIndex = 24;
            this.personalParametersDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.personalParametersDataGridView_CellFormatting);
            this.personalParametersDataGridView.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.personalParametersDataGridView_CellParsing);
            this.personalParametersDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            // 
            // personalParameterNameColumn
            // 
            this.personalParameterNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.personalParameterNameColumn.HeaderText = "Parameter for checking";
            this.personalParameterNameColumn.Name = "personalParameterNameColumn";
            this.personalParameterNameColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.personalParameterNameColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.personalParameterNameColumn.Width = 300;
            // 
            // personalParameterValueColumn
            // 
            this.personalParameterValueColumn.HeaderText = "Value";
            this.personalParameterValueColumn.Name = "personalParameterValueColumn";
            this.personalParameterValueColumn.Width = 300;
            // 
            // personalParametersBindingNavigator
            // 
            this.personalParametersBindingNavigator.AddNewItem = this.toolStripButton91;
            this.personalParametersBindingNavigator.CountItem = this.toolStripLabel17;
            this.personalParametersBindingNavigator.DeleteItem = this.toolStripButton92;
            this.personalParametersBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton93,
            this.toolStripButton94,
            this.toolStripSeparator50,
            this.toolStripTextBox17,
            this.toolStripLabel17,
            this.toolStripSeparator51,
            this.toolStripButton95,
            this.toolStripButton96,
            this.toolStripSeparator52,
            this.toolStripButton91,
            this.toolStripButton92,
            this.personalParametersBindingNavigatorSaveItem,
            this.personalParametersBindingNavigatorRefreshItem});
            this.personalParametersBindingNavigator.Location = new System.Drawing.Point(3, 16);
            this.personalParametersBindingNavigator.MoveFirstItem = this.toolStripButton93;
            this.personalParametersBindingNavigator.MoveLastItem = this.toolStripButton96;
            this.personalParametersBindingNavigator.MoveNextItem = this.toolStripButton95;
            this.personalParametersBindingNavigator.MovePreviousItem = this.toolStripButton94;
            this.personalParametersBindingNavigator.Name = "personalParametersBindingNavigator";
            this.personalParametersBindingNavigator.PositionItem = this.toolStripTextBox17;
            this.personalParametersBindingNavigator.Size = new System.Drawing.Size(552, 25);
            this.personalParametersBindingNavigator.TabIndex = 23;
            this.personalParametersBindingNavigator.Text = "bindingNavigator3";
            // 
            // toolStripButton91
            // 
            this.toolStripButton91.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton91.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton91.Image")));
            this.toolStripButton91.Name = "toolStripButton91";
            this.toolStripButton91.RightToLeftAutoMirrorImage = true;
            this.toolStripButton91.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton91.Text = "Add new";
            // 
            // toolStripLabel17
            // 
            this.toolStripLabel17.Name = "toolStripLabel17";
            this.toolStripLabel17.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel17.Text = "для {0}";
            this.toolStripLabel17.ToolTipText = "Total number of items";
            // 
            // toolStripButton92
            // 
            this.toolStripButton92.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton92.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton92.Image")));
            this.toolStripButton92.Name = "toolStripButton92";
            this.toolStripButton92.RightToLeftAutoMirrorImage = true;
            this.toolStripButton92.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton92.Text = "Delete";
            // 
            // toolStripButton93
            // 
            this.toolStripButton93.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton93.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton93.Image")));
            this.toolStripButton93.Name = "toolStripButton93";
            this.toolStripButton93.RightToLeftAutoMirrorImage = true;
            this.toolStripButton93.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton93.Text = "Move first";
            // 
            // toolStripButton94
            // 
            this.toolStripButton94.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton94.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton94.Image")));
            this.toolStripButton94.Name = "toolStripButton94";
            this.toolStripButton94.RightToLeftAutoMirrorImage = true;
            this.toolStripButton94.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton94.Text = "Move previous";
            // 
            // toolStripSeparator50
            // 
            this.toolStripSeparator50.Name = "toolStripSeparator50";
            this.toolStripSeparator50.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox17
            // 
            this.toolStripTextBox17.AccessibleName = "Position";
            this.toolStripTextBox17.AutoSize = false;
            this.toolStripTextBox17.Name = "toolStripTextBox17";
            this.toolStripTextBox17.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox17.Text = "0";
            this.toolStripTextBox17.ToolTipText = "Current position";
            // 
            // toolStripSeparator51
            // 
            this.toolStripSeparator51.Name = "toolStripSeparator51";
            this.toolStripSeparator51.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton95
            // 
            this.toolStripButton95.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton95.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton95.Image")));
            this.toolStripButton95.Name = "toolStripButton95";
            this.toolStripButton95.RightToLeftAutoMirrorImage = true;
            this.toolStripButton95.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton95.Text = "Move next";
            // 
            // toolStripButton96
            // 
            this.toolStripButton96.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton96.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton96.Image")));
            this.toolStripButton96.Name = "toolStripButton96";
            this.toolStripButton96.RightToLeftAutoMirrorImage = true;
            this.toolStripButton96.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton96.Text = "Move last";
            // 
            // toolStripSeparator52
            // 
            this.toolStripSeparator52.Name = "toolStripSeparator52";
            this.toolStripSeparator52.Size = new System.Drawing.Size(6, 25);
            // 
            // personalParametersBindingNavigatorSaveItem
            // 
            this.personalParametersBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.personalParametersBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("personalParametersBindingNavigatorSaveItem.Image")));
            this.personalParametersBindingNavigatorSaveItem.Name = "personalParametersBindingNavigatorSaveItem";
            this.personalParametersBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.personalParametersBindingNavigatorSaveItem.Text = "Save Data";
            this.personalParametersBindingNavigatorSaveItem.Click += new System.EventHandler(this.personalParametersBindingNavigatorSaveItem_Click);
            // 
            // personalParametersBindingNavigatorRefreshItem
            // 
            this.personalParametersBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.personalParametersBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("personalParametersBindingNavigatorRefreshItem.Image")));
            this.personalParametersBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.personalParametersBindingNavigatorRefreshItem.Name = "personalParametersBindingNavigatorRefreshItem";
            this.personalParametersBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.personalParametersBindingNavigatorRefreshItem.Text = "Refresh";
            this.personalParametersBindingNavigatorRefreshItem.Click += new System.EventHandler(this.personalParametersBindingNavigatorRefreshItem_Click);
            // 
            // personalCheckValuesHeaderPanel
            // 
            this.personalCheckValuesHeaderPanel.Controls.Add(this.personalCheckValuesHeaderLabel);
            this.personalCheckValuesHeaderPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.personalCheckValuesHeaderPanel.Location = new System.Drawing.Point(0, 0);
            this.personalCheckValuesHeaderPanel.Name = "personalCheckValuesHeaderPanel";
            this.personalCheckValuesHeaderPanel.Size = new System.Drawing.Size(558, 28);
            this.personalCheckValuesHeaderPanel.TabIndex = 1;
            // 
            // personalCheckValuesHeaderLabel
            // 
            this.personalCheckValuesHeaderLabel.AutoSize = true;
            this.personalCheckValuesHeaderLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.personalCheckValuesHeaderLabel.Location = new System.Drawing.Point(3, 6);
            this.personalCheckValuesHeaderLabel.Name = "personalCheckValuesHeaderLabel";
            this.personalCheckValuesHeaderLabel.Size = new System.Drawing.Size(237, 16);
            this.personalCheckValuesHeaderLabel.TabIndex = 144;
            this.personalCheckValuesHeaderLabel.Text = "Additional validation parameters:";
            // 
            // personalPwdSettingsPanel
            // 
            this.personalPwdSettingsPanel.Controls.Add(this.personalChangePasswordPanel);
            this.personalPwdSettingsPanel.Controls.Add(this.personalPwdResetSettingsPanel);
            this.personalPwdSettingsPanel.Controls.Add(this.personalPwdResetPanel);
            this.personalPwdSettingsPanel.Location = new System.Drawing.Point(438, 32);
            this.personalPwdSettingsPanel.Name = "personalPwdSettingsPanel";
            this.personalPwdSettingsPanel.Size = new System.Drawing.Size(551, 293);
            this.personalPwdSettingsPanel.TabIndex = 145;
            // 
            // personalChangePasswordPanel
            // 
            this.personalChangePasswordPanel.Controls.Add(this.changePasswordButton);
            this.personalChangePasswordPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.personalChangePasswordPanel.Location = new System.Drawing.Point(0, 233);
            this.personalChangePasswordPanel.Name = "personalChangePasswordPanel";
            this.personalChangePasswordPanel.Size = new System.Drawing.Size(551, 60);
            this.personalChangePasswordPanel.TabIndex = 2;
            // 
            // changePasswordButton
            // 
            this.changePasswordButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.changePasswordButton.Image = ((System.Drawing.Image)(resources.GetObject("changePasswordButton.Image")));
            this.changePasswordButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.changePasswordButton.Location = new System.Drawing.Point(35, 8);
            this.changePasswordButton.Name = "changePasswordButton";
            this.changePasswordButton.Size = new System.Drawing.Size(271, 45);
            this.changePasswordButton.TabIndex = 7;
            this.changePasswordButton.Text = "Change password";
            this.changePasswordButton.UseVisualStyleBackColor = true;
            this.changePasswordButton.Click += new System.EventHandler(this.changePasswordButton_Click);
            // 
            // personalPwdResetSettingsPanel
            // 
            this.personalPwdResetSettingsPanel.Controls.Add(this.personalPwdTypeLabel);
            this.personalPwdResetSettingsPanel.Controls.Add(this.personalPwdTypeComboBox);
            this.personalPwdResetSettingsPanel.Controls.Add(this.label4);
            this.personalPwdResetSettingsPanel.Controls.Add(this.personalSMSResetCheckBox);
            this.personalPwdResetSettingsPanel.Controls.Add(this.personalEmailResetCheckBox);
            this.personalPwdResetSettingsPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.personalPwdResetSettingsPanel.Location = new System.Drawing.Point(0, 117);
            this.personalPwdResetSettingsPanel.Name = "personalPwdResetSettingsPanel";
            this.personalPwdResetSettingsPanel.Size = new System.Drawing.Size(551, 116);
            this.personalPwdResetSettingsPanel.TabIndex = 0;
            // 
            // personalPwdTypeLabel
            // 
            this.personalPwdTypeLabel.AutoSize = true;
            this.personalPwdTypeLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.personalPwdTypeLabel.Location = new System.Drawing.Point(33, 85);
            this.personalPwdTypeLabel.Name = "personalPwdTypeLabel";
            this.personalPwdTypeLabel.Size = new System.Drawing.Size(93, 13);
            this.personalPwdTypeLabel.TabIndex = 146;
            this.personalPwdTypeLabel.Text = "Password type:";
            // 
            // personalPwdTypeComboBox
            // 
            this.personalPwdTypeComboBox.FormattingEnabled = true;
            this.personalPwdTypeComboBox.Location = new System.Drawing.Point(136, 82);
            this.personalPwdTypeComboBox.Name = "personalPwdTypeComboBox";
            this.personalPwdTypeComboBox.Size = new System.Drawing.Size(284, 21);
            this.personalPwdTypeComboBox.TabIndex = 145;
            this.personalPwdTypeComboBox.SelectedIndexChanged += new System.EventHandler(this.personalPwdTypeComboBox_SelectedIndexChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(33, 10);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(145, 13);
            this.label4.TabIndex = 144;
            this.label4.Text = "Password reset settings:";
            // 
            // personalSMSResetCheckBox
            // 
            this.personalSMSResetCheckBox.AutoSize = true;
            this.personalSMSResetCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.personalSMSResetCheckBox.Location = new System.Drawing.Point(82, 53);
            this.personalSMSResetCheckBox.Name = "personalSMSResetCheckBox";
            this.personalSMSResetCheckBox.Size = new System.Drawing.Size(281, 17);
            this.personalSMSResetCheckBox.TabIndex = 1;
            this.personalSMSResetCheckBox.Text = "Reset password and send instructions by phone (SMS)";
            this.personalSMSResetCheckBox.UseVisualStyleBackColor = true;
            // 
            // personalEmailResetCheckBox
            // 
            this.personalEmailResetCheckBox.AutoSize = true;
            this.personalEmailResetCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.personalEmailResetCheckBox.Location = new System.Drawing.Point(82, 29);
            this.personalEmailResetCheckBox.Name = "personalEmailResetCheckBox";
            this.personalEmailResetCheckBox.Size = new System.Drawing.Size(243, 17);
            this.personalEmailResetCheckBox.TabIndex = 0;
            this.personalEmailResetCheckBox.Text = "Reset password and send instructions by email";
            this.personalEmailResetCheckBox.UseVisualStyleBackColor = true;
            // 
            // personalPwdResetPanel
            // 
            this.personalPwdResetPanel.Controls.Add(this.personalPwdResetDateLabel);
            this.personalPwdResetPanel.Controls.Add(this.tempInstructionLabel1);
            this.personalPwdResetPanel.Controls.Add(this.personalPwdResetPeriodLabel);
            this.personalPwdResetPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.personalPwdResetPanel.Location = new System.Drawing.Point(0, 0);
            this.personalPwdResetPanel.Name = "personalPwdResetPanel";
            this.personalPwdResetPanel.Size = new System.Drawing.Size(551, 117);
            this.personalPwdResetPanel.TabIndex = 1;
            // 
            // personalPwdResetDateLabel
            // 
            this.personalPwdResetDateLabel.AutoSize = true;
            this.personalPwdResetDateLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.personalPwdResetDateLabel.ForeColor = System.Drawing.Color.Red;
            this.personalPwdResetDateLabel.Location = new System.Drawing.Point(12, 4);
            this.personalPwdResetDateLabel.Name = "personalPwdResetDateLabel";
            this.personalPwdResetDateLabel.Size = new System.Drawing.Size(294, 16);
            this.personalPwdResetDateLabel.TabIndex = 0;
            this.personalPwdResetDateLabel.Text = "ATTENTION! Your password was reseted";
            // 
            // tempInstructionLabel1
            // 
            this.tempInstructionLabel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tempInstructionLabel1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tempInstructionLabel1.ForeColor = System.Drawing.Color.Maroon;
            this.tempInstructionLabel1.Location = new System.Drawing.Point(12, 58);
            this.tempInstructionLabel1.Name = "tempInstructionLabel1";
            this.tempInstructionLabel1.Size = new System.Drawing.Size(527, 53);
            this.tempInstructionLabel1.TabIndex = 3;
            this.tempInstructionLabel1.Text = resources.GetString("tempInstructionLabel1.Text");
            // 
            // personalPwdResetPeriodLabel
            // 
            this.personalPwdResetPeriodLabel.AutoSize = true;
            this.personalPwdResetPeriodLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.personalPwdResetPeriodLabel.ForeColor = System.Drawing.Color.Red;
            this.personalPwdResetPeriodLabel.Location = new System.Drawing.Point(12, 31);
            this.personalPwdResetPeriodLabel.Name = "personalPwdResetPeriodLabel";
            this.personalPwdResetPeriodLabel.Size = new System.Drawing.Size(261, 16);
            this.personalPwdResetPeriodLabel.TabIndex = 1;
            this.personalPwdResetPeriodLabel.Text = "Period of temporary password use is";
            // 
            // personalPasswrodSettingLabel
            // 
            this.personalPasswrodSettingLabel.AutoSize = true;
            this.personalPasswrodSettingLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.personalPasswrodSettingLabel.Location = new System.Drawing.Point(434, 12);
            this.personalPasswrodSettingLabel.Name = "personalPasswrodSettingLabel";
            this.personalPasswrodSettingLabel.Size = new System.Drawing.Size(173, 16);
            this.personalPasswrodSettingLabel.TabIndex = 143;
            this.personalPasswrodSettingLabel.Text = "Your password settings:";
            // 
            // personalVerticalSplitPanel
            // 
            this.personalVerticalSplitPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.personalVerticalSplitPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.personalVerticalSplitPanel.Location = new System.Drawing.Point(422, 13);
            this.personalVerticalSplitPanel.Name = "personalVerticalSplitPanel";
            this.personalVerticalSplitPanel.Size = new System.Drawing.Size(2, 601);
            this.personalVerticalSplitPanel.TabIndex = 142;
            // 
            // refreshUserButton
            // 
            this.refreshUserButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.refreshUserButton.Image = ((System.Drawing.Image)(resources.GetObject("refreshUserButton.Image")));
            this.refreshUserButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.refreshUserButton.Location = new System.Drawing.Point(31, 482);
            this.refreshUserButton.Name = "refreshUserButton";
            this.refreshUserButton.Size = new System.Drawing.Size(271, 45);
            this.refreshUserButton.TabIndex = 6;
            this.refreshUserButton.Text = "Refresh personal information";
            this.refreshUserButton.UseVisualStyleBackColor = true;
            this.refreshUserButton.Click += new System.EventHandler(this.refreshUserButton_Click);
            // 
            // saveUserButton
            // 
            this.saveUserButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.saveUserButton.Image = ((System.Drawing.Image)(resources.GetObject("saveUserButton.Image")));
            this.saveUserButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.saveUserButton.Location = new System.Drawing.Point(31, 533);
            this.saveUserButton.Name = "saveUserButton";
            this.saveUserButton.Size = new System.Drawing.Size(271, 45);
            this.saveUserButton.TabIndex = 5;
            this.saveUserButton.Text = "Save personal information";
            this.saveUserButton.UseVisualStyleBackColor = true;
            this.saveUserButton.Click += new System.EventHandler(this.saveUserButton_Click);
            // 
            // personalGroupsLabel
            // 
            this.personalGroupsLabel.AutoSize = true;
            this.personalGroupsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.personalGroupsLabel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.personalGroupsLabel.Location = new System.Drawing.Point(28, 331);
            this.personalGroupsLabel.Name = "personalGroupsLabel";
            this.personalGroupsLabel.Size = new System.Drawing.Size(235, 13);
            this.personalGroupsLabel.TabIndex = 141;
            this.personalGroupsLabel.Text = "You are member of the following groups:";
            // 
            // personalGroupsListView
            // 
            this.personalGroupsListView.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.personalGroupsListView.Location = new System.Drawing.Point(31, 360);
            this.personalGroupsListView.MultiSelect = false;
            this.personalGroupsListView.Name = "personalGroupsListView";
            this.personalGroupsListView.Size = new System.Drawing.Size(375, 103);
            this.personalGroupsListView.SmallImageList = this.usersImageList;
            this.personalGroupsListView.TabIndex = 140;
            this.personalGroupsListView.UseCompatibleStateImageBehavior = false;
            this.personalGroupsListView.View = System.Windows.Forms.View.List;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(11, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(189, 16);
            this.label1.TabIndex = 139;
            this.label1.Text = "Your personal information:";
            // 
            // personalUserPhoneTextBox
            // 
            this.personalUserPhoneTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.personalUserPhoneTextBox.Location = new System.Drawing.Point(151, 133);
            this.personalUserPhoneTextBox.Name = "personalUserPhoneTextBox";
            this.personalUserPhoneTextBox.Size = new System.Drawing.Size(255, 20);
            this.personalUserPhoneTextBox.TabIndex = 137;
            // 
            // personalUserEmailTextBox
            // 
            this.personalUserEmailTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.personalUserEmailTextBox.Location = new System.Drawing.Point(151, 103);
            this.personalUserEmailTextBox.Name = "personalUserEmailTextBox";
            this.personalUserEmailTextBox.Size = new System.Drawing.Size(255, 20);
            this.personalUserEmailTextBox.TabIndex = 135;
            // 
            // personalUserNameTextBox
            // 
            this.personalUserNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.personalUserNameTextBox.Location = new System.Drawing.Point(151, 73);
            this.personalUserNameTextBox.Name = "personalUserNameTextBox";
            this.personalUserNameTextBox.Size = new System.Drawing.Size(255, 20);
            this.personalUserNameTextBox.TabIndex = 127;
            // 
            // personalPwdAttemptsLabel
            // 
            this.personalPwdAttemptsLabel.AutoSize = true;
            this.personalPwdAttemptsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.personalPwdAttemptsLabel.ForeColor = System.Drawing.Color.Navy;
            this.personalPwdAttemptsLabel.Location = new System.Drawing.Point(28, 215);
            this.personalPwdAttemptsLabel.Name = "personalPwdAttemptsLabel";
            this.personalPwdAttemptsLabel.Size = new System.Drawing.Size(292, 13);
            this.personalPwdAttemptsLabel.TabIndex = 131;
            this.personalPwdAttemptsLabel.Text = "Number of attempts to enter the correct password:";
            // 
            // personalFullNameTextBox
            // 
            this.personalFullNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.personalFullNameTextBox.Location = new System.Drawing.Point(151, 43);
            this.personalFullNameTextBox.Name = "personalFullNameTextBox";
            this.personalFullNameTextBox.Size = new System.Drawing.Size(255, 20);
            this.personalFullNameTextBox.TabIndex = 129;
            // 
            // personalMaxPwdAttemptsLabel
            // 
            this.personalMaxPwdAttemptsLabel.AutoSize = true;
            this.personalMaxPwdAttemptsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.personalMaxPwdAttemptsLabel.ForeColor = System.Drawing.Color.Maroon;
            this.personalMaxPwdAttemptsLabel.Location = new System.Drawing.Point(28, 240);
            this.personalMaxPwdAttemptsLabel.Name = "personalMaxPwdAttemptsLabel";
            this.personalMaxPwdAttemptsLabel.Size = new System.Drawing.Size(345, 13);
            this.personalMaxPwdAttemptsLabel.TabIndex = 132;
            this.personalMaxPwdAttemptsLabel.Text = "Maximum number of attempts to enter the correct password:";
            // 
            // personalLogonDateLabel
            // 
            this.personalLogonDateLabel.AutoSize = true;
            this.personalLogonDateLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.personalLogonDateLabel.ForeColor = System.Drawing.Color.Green;
            this.personalLogonDateLabel.Location = new System.Drawing.Point(28, 180);
            this.personalLogonDateLabel.Name = "personalLogonDateLabel";
            this.personalLogonDateLabel.Size = new System.Drawing.Size(116, 13);
            this.personalLogonDateLabel.TabIndex = 130;
            this.personalLogonDateLabel.Text = "Date of last log on:";
            // 
            // personalEducationLabel
            // 
            this.personalEducationLabel.AutoSize = true;
            this.personalEducationLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.personalEducationLabel.ForeColor = System.Drawing.Color.DarkGoldenrod;
            this.personalEducationLabel.Location = new System.Drawing.Point(28, 280);
            this.personalEducationLabel.Name = "personalEducationLabel";
            this.personalEducationLabel.Size = new System.Drawing.Size(68, 13);
            this.personalEducationLabel.TabIndex = 133;
            this.personalEducationLabel.Text = "Education:";
            // 
            // scheduleTabPage
            // 
            this.scheduleTabPage.Controls.Add(this.scheduleSplitContainer);
            this.scheduleTabPage.ImageIndex = 9;
            this.scheduleTabPage.Location = new System.Drawing.Point(4, 42);
            this.scheduleTabPage.Name = "scheduleTabPage";
            this.scheduleTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.scheduleTabPage.Size = new System.Drawing.Size(1000, 637);
            this.scheduleTabPage.TabIndex = 8;
            this.scheduleTabPage.Text = "Schedule management";
            this.scheduleTabPage.UseVisualStyleBackColor = true;
            // 
            // scheduleSplitContainer
            // 
            this.scheduleSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.scheduleSplitContainer.Location = new System.Drawing.Point(3, 3);
            this.scheduleSplitContainer.Name = "scheduleSplitContainer";
            // 
            // scheduleSplitContainer.Panel1
            // 
            this.scheduleSplitContainer.Panel1.Controls.Add(this.controlledProgramsDataGridView);
            this.scheduleSplitContainer.Panel1.Controls.Add(this.controlledProgramsBindingNavigator);
            // 
            // scheduleSplitContainer.Panel2
            // 
            this.scheduleSplitContainer.Panel2.Controls.Add(this.scheduleDataGridView);
            this.scheduleSplitContainer.Panel2.Controls.Add(this.scheduleBindingNavigator);
            this.scheduleSplitContainer.Size = new System.Drawing.Size(994, 631);
            this.scheduleSplitContainer.SplitterDistance = 337;
            this.scheduleSplitContainer.TabIndex = 0;
            // 
            // controlledProgramsDataGridView
            // 
            this.controlledProgramsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.controlledProgramsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.controlledProgramNameColumn,
            this.controlledProgramAllowedColumn});
            this.controlledProgramsDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.controlledProgramsDataGridView.Location = new System.Drawing.Point(0, 25);
            this.controlledProgramsDataGridView.Name = "controlledProgramsDataGridView";
            this.controlledProgramsDataGridView.Size = new System.Drawing.Size(337, 606);
            this.controlledProgramsDataGridView.TabIndex = 14;
            this.controlledProgramsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            // 
            // controlledProgramNameColumn
            // 
            this.controlledProgramNameColumn.HeaderText = "Program name";
            this.controlledProgramNameColumn.Name = "controlledProgramNameColumn";
            this.controlledProgramNameColumn.Width = 200;
            // 
            // controlledProgramAllowedColumn
            // 
            this.controlledProgramAllowedColumn.FalseValue = "0";
            this.controlledProgramAllowedColumn.HeaderText = "Allowed";
            this.controlledProgramAllowedColumn.IndeterminateValue = "0";
            this.controlledProgramAllowedColumn.Name = "controlledProgramAllowedColumn";
            this.controlledProgramAllowedColumn.TrueValue = "1";
            this.controlledProgramAllowedColumn.Width = 75;
            // 
            // controlledProgramsBindingNavigator
            // 
            this.controlledProgramsBindingNavigator.AddNewItem = this.toolStripButton103;
            this.controlledProgramsBindingNavigator.CountItem = this.toolStripLabel21;
            this.controlledProgramsBindingNavigator.DeleteItem = this.toolStripButton110;
            this.controlledProgramsBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton111,
            this.toolStripButton112,
            this.toolStripSeparator64,
            this.toolStripTextBox21,
            this.toolStripLabel21,
            this.toolStripSeparator65,
            this.toolStripButton113,
            this.toolStripButton114,
            this.toolStripSeparator66,
            this.toolStripButton103,
            this.toolStripButton110,
            this.controlledProgramsBindingNavigatorSaveItem,
            this.controlledProgramsBindingNavigatorRefreshItem});
            this.controlledProgramsBindingNavigator.Location = new System.Drawing.Point(0, 0);
            this.controlledProgramsBindingNavigator.MoveFirstItem = this.toolStripButton111;
            this.controlledProgramsBindingNavigator.MoveLastItem = this.toolStripButton114;
            this.controlledProgramsBindingNavigator.MoveNextItem = this.toolStripButton113;
            this.controlledProgramsBindingNavigator.MovePreviousItem = this.toolStripButton112;
            this.controlledProgramsBindingNavigator.Name = "controlledProgramsBindingNavigator";
            this.controlledProgramsBindingNavigator.PositionItem = this.toolStripTextBox21;
            this.controlledProgramsBindingNavigator.Size = new System.Drawing.Size(337, 25);
            this.controlledProgramsBindingNavigator.TabIndex = 13;
            // 
            // toolStripButton103
            // 
            this.toolStripButton103.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton103.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton103.Image")));
            this.toolStripButton103.Name = "toolStripButton103";
            this.toolStripButton103.RightToLeftAutoMirrorImage = true;
            this.toolStripButton103.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton103.Text = "Add new";
            // 
            // toolStripLabel21
            // 
            this.toolStripLabel21.Name = "toolStripLabel21";
            this.toolStripLabel21.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel21.Text = "для {0}";
            this.toolStripLabel21.ToolTipText = "Total number of items";
            // 
            // toolStripButton110
            // 
            this.toolStripButton110.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton110.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton110.Image")));
            this.toolStripButton110.Name = "toolStripButton110";
            this.toolStripButton110.RightToLeftAutoMirrorImage = true;
            this.toolStripButton110.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton110.Text = "Delete";
            // 
            // toolStripButton111
            // 
            this.toolStripButton111.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton111.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton111.Image")));
            this.toolStripButton111.Name = "toolStripButton111";
            this.toolStripButton111.RightToLeftAutoMirrorImage = true;
            this.toolStripButton111.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton111.Text = "Move first";
            // 
            // toolStripButton112
            // 
            this.toolStripButton112.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton112.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton112.Image")));
            this.toolStripButton112.Name = "toolStripButton112";
            this.toolStripButton112.RightToLeftAutoMirrorImage = true;
            this.toolStripButton112.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton112.Text = "Move previous";
            // 
            // toolStripSeparator64
            // 
            this.toolStripSeparator64.Name = "toolStripSeparator64";
            this.toolStripSeparator64.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox21
            // 
            this.toolStripTextBox21.AccessibleName = "Position";
            this.toolStripTextBox21.AutoSize = false;
            this.toolStripTextBox21.Name = "toolStripTextBox21";
            this.toolStripTextBox21.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox21.Text = "0";
            this.toolStripTextBox21.ToolTipText = "Current position";
            // 
            // toolStripSeparator65
            // 
            this.toolStripSeparator65.Name = "toolStripSeparator65";
            this.toolStripSeparator65.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton113
            // 
            this.toolStripButton113.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton113.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton113.Image")));
            this.toolStripButton113.Name = "toolStripButton113";
            this.toolStripButton113.RightToLeftAutoMirrorImage = true;
            this.toolStripButton113.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton113.Text = "Move next";
            // 
            // toolStripButton114
            // 
            this.toolStripButton114.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton114.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton114.Image")));
            this.toolStripButton114.Name = "toolStripButton114";
            this.toolStripButton114.RightToLeftAutoMirrorImage = true;
            this.toolStripButton114.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton114.Text = "Move last";
            // 
            // toolStripSeparator66
            // 
            this.toolStripSeparator66.Name = "toolStripSeparator66";
            this.toolStripSeparator66.Size = new System.Drawing.Size(6, 25);
            // 
            // controlledProgramsBindingNavigatorSaveItem
            // 
            this.controlledProgramsBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.controlledProgramsBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("controlledProgramsBindingNavigatorSaveItem.Image")));
            this.controlledProgramsBindingNavigatorSaveItem.Name = "controlledProgramsBindingNavigatorSaveItem";
            this.controlledProgramsBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.controlledProgramsBindingNavigatorSaveItem.Text = "Save Data";
            this.controlledProgramsBindingNavigatorSaveItem.Click += new System.EventHandler(this.controlledProgramsBindingNavigatorSaveItem_Click);
            // 
            // controlledProgramsBindingNavigatorRefreshItem
            // 
            this.controlledProgramsBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.controlledProgramsBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("controlledProgramsBindingNavigatorRefreshItem.Image")));
            this.controlledProgramsBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.controlledProgramsBindingNavigatorRefreshItem.Name = "controlledProgramsBindingNavigatorRefreshItem";
            this.controlledProgramsBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.controlledProgramsBindingNavigatorRefreshItem.Text = "Refresh";
            this.controlledProgramsBindingNavigatorRefreshItem.Click += new System.EventHandler(this.controlledProgramsBindingNavigatorRefreshItem_Click);
            // 
            // scheduleDataGridView
            // 
            this.scheduleDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.scheduleDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.scheduleUserIDColumn,
            this.scheduleGroupIDColumn,
            this.scheduleUserNameColumn,
            this.scheduleGroupNameColumn,
            this.scheduleComputerNameColumn,
            this.scheduleProgramNameColumn,
            this.scheduleFunctionNameColumn,
            this.scheduleActionNameColumn,
            this.scheduleIncrementValuesColumn,
            this.scheduleConditionStringColumn});
            this.scheduleDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.scheduleDataGridView.Location = new System.Drawing.Point(0, 25);
            this.scheduleDataGridView.Name = "scheduleDataGridView";
            this.scheduleDataGridView.Size = new System.Drawing.Size(653, 606);
            this.scheduleDataGridView.TabIndex = 15;
            this.scheduleDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.scheduleDataGridView_CellFormatting);
            this.scheduleDataGridView.CellValidating += new System.Windows.Forms.DataGridViewCellValidatingEventHandler(this.scheduleDataGridView_CellValidating);
            this.scheduleDataGridView.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.scheduleDataGridView_CellValueChanged);
            this.scheduleDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userCheckValuesDataGridView_DataError);
            this.scheduleDataGridView.EditingControlShowing += new System.Windows.Forms.DataGridViewEditingControlShowingEventHandler(this.scheduleDataGridView_EditingControlShowing);
            // 
            // scheduleUserIDColumn
            // 
            this.scheduleUserIDColumn.HeaderText = "UserID";
            this.scheduleUserIDColumn.Name = "scheduleUserIDColumn";
            this.scheduleUserIDColumn.Visible = false;
            // 
            // scheduleGroupIDColumn
            // 
            this.scheduleGroupIDColumn.HeaderText = "GroupID";
            this.scheduleGroupIDColumn.Name = "scheduleGroupIDColumn";
            this.scheduleGroupIDColumn.Visible = false;
            // 
            // scheduleUserNameColumn
            // 
            this.scheduleUserNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.scheduleUserNameColumn.HeaderText = "User name";
            this.scheduleUserNameColumn.Name = "scheduleUserNameColumn";
            this.scheduleUserNameColumn.Width = 150;
            // 
            // scheduleGroupNameColumn
            // 
            this.scheduleGroupNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.scheduleGroupNameColumn.HeaderText = "Group name";
            this.scheduleGroupNameColumn.Name = "scheduleGroupNameColumn";
            this.scheduleGroupNameColumn.Width = 150;
            // 
            // scheduleComputerNameColumn
            // 
            this.scheduleComputerNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.scheduleComputerNameColumn.HeaderText = "Computer name";
            this.scheduleComputerNameColumn.Name = "scheduleComputerNameColumn";
            this.scheduleComputerNameColumn.Width = 150;
            // 
            // scheduleProgramNameColumn
            // 
            this.scheduleProgramNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.scheduleProgramNameColumn.HeaderText = "Program";
            this.scheduleProgramNameColumn.Name = "scheduleProgramNameColumn";
            this.scheduleProgramNameColumn.Width = 150;
            // 
            // scheduleFunctionNameColumn
            // 
            this.scheduleFunctionNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.scheduleFunctionNameColumn.HeaderText = "Function";
            this.scheduleFunctionNameColumn.Name = "scheduleFunctionNameColumn";
            this.scheduleFunctionNameColumn.Width = 150;
            // 
            // scheduleActionNameColumn
            // 
            this.scheduleActionNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.scheduleActionNameColumn.HeaderText = "Action";
            this.scheduleActionNameColumn.Name = "scheduleActionNameColumn";
            // 
            // scheduleIncrementValuesColumn
            // 
            this.scheduleIncrementValuesColumn.FalseValue = "0";
            this.scheduleIncrementValuesColumn.HeaderText = "Increase values";
            this.scheduleIncrementValuesColumn.IndeterminateValue = "0";
            this.scheduleIncrementValuesColumn.Name = "scheduleIncrementValuesColumn";
            this.scheduleIncrementValuesColumn.TrueValue = "1";
            this.scheduleIncrementValuesColumn.Width = 90;
            // 
            // scheduleConditionStringColumn
            // 
            this.scheduleConditionStringColumn.HeaderText = "Contidion string";
            this.scheduleConditionStringColumn.Name = "scheduleConditionStringColumn";
            this.scheduleConditionStringColumn.Width = 350;
            // 
            // scheduleBindingNavigator
            // 
            this.scheduleBindingNavigator.AddNewItem = this.toolStripButton115;
            this.scheduleBindingNavigator.CountItem = this.toolStripLabel22;
            this.scheduleBindingNavigator.DeleteItem = this.toolStripButton116;
            this.scheduleBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton117,
            this.toolStripButton118,
            this.toolStripSeparator67,
            this.toolStripTextBox22,
            this.toolStripLabel22,
            this.toolStripSeparator68,
            this.toolStripButton119,
            this.toolStripButton120,
            this.toolStripSeparator69,
            this.toolStripButton115,
            this.toolStripButton116,
            this.scheduleBindingNavigatorSaveItem,
            this.scheduleBindingNavigatorRefreshItem,
            this.toolStripSeparator70,
            this.scheduleConditionBuilderItem});
            this.scheduleBindingNavigator.Location = new System.Drawing.Point(0, 0);
            this.scheduleBindingNavigator.MoveFirstItem = this.toolStripButton117;
            this.scheduleBindingNavigator.MoveLastItem = this.toolStripButton120;
            this.scheduleBindingNavigator.MoveNextItem = this.toolStripButton119;
            this.scheduleBindingNavigator.MovePreviousItem = this.toolStripButton118;
            this.scheduleBindingNavigator.Name = "scheduleBindingNavigator";
            this.scheduleBindingNavigator.PositionItem = this.toolStripTextBox22;
            this.scheduleBindingNavigator.Size = new System.Drawing.Size(653, 25);
            this.scheduleBindingNavigator.TabIndex = 14;
            // 
            // toolStripButton115
            // 
            this.toolStripButton115.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton115.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton115.Image")));
            this.toolStripButton115.Name = "toolStripButton115";
            this.toolStripButton115.RightToLeftAutoMirrorImage = true;
            this.toolStripButton115.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton115.Text = "Add new";
            // 
            // toolStripLabel22
            // 
            this.toolStripLabel22.Name = "toolStripLabel22";
            this.toolStripLabel22.Size = new System.Drawing.Size(43, 22);
            this.toolStripLabel22.Text = "для {0}";
            this.toolStripLabel22.ToolTipText = "Total number of items";
            // 
            // toolStripButton116
            // 
            this.toolStripButton116.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton116.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton116.Image")));
            this.toolStripButton116.Name = "toolStripButton116";
            this.toolStripButton116.RightToLeftAutoMirrorImage = true;
            this.toolStripButton116.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton116.Text = "Delete";
            // 
            // toolStripButton117
            // 
            this.toolStripButton117.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton117.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton117.Image")));
            this.toolStripButton117.Name = "toolStripButton117";
            this.toolStripButton117.RightToLeftAutoMirrorImage = true;
            this.toolStripButton117.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton117.Text = "Move first";
            // 
            // toolStripButton118
            // 
            this.toolStripButton118.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton118.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton118.Image")));
            this.toolStripButton118.Name = "toolStripButton118";
            this.toolStripButton118.RightToLeftAutoMirrorImage = true;
            this.toolStripButton118.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton118.Text = "Move previous";
            // 
            // toolStripSeparator67
            // 
            this.toolStripSeparator67.Name = "toolStripSeparator67";
            this.toolStripSeparator67.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripTextBox22
            // 
            this.toolStripTextBox22.AccessibleName = "Position";
            this.toolStripTextBox22.AutoSize = false;
            this.toolStripTextBox22.Name = "toolStripTextBox22";
            this.toolStripTextBox22.Size = new System.Drawing.Size(50, 23);
            this.toolStripTextBox22.Text = "0";
            this.toolStripTextBox22.ToolTipText = "Current position";
            // 
            // toolStripSeparator68
            // 
            this.toolStripSeparator68.Name = "toolStripSeparator68";
            this.toolStripSeparator68.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton119
            // 
            this.toolStripButton119.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton119.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton119.Image")));
            this.toolStripButton119.Name = "toolStripButton119";
            this.toolStripButton119.RightToLeftAutoMirrorImage = true;
            this.toolStripButton119.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton119.Text = "Move next";
            // 
            // toolStripButton120
            // 
            this.toolStripButton120.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton120.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton120.Image")));
            this.toolStripButton120.Name = "toolStripButton120";
            this.toolStripButton120.RightToLeftAutoMirrorImage = true;
            this.toolStripButton120.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton120.Text = "Move last";
            // 
            // toolStripSeparator69
            // 
            this.toolStripSeparator69.Name = "toolStripSeparator69";
            this.toolStripSeparator69.Size = new System.Drawing.Size(6, 25);
            // 
            // scheduleBindingNavigatorSaveItem
            // 
            this.scheduleBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.scheduleBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("scheduleBindingNavigatorSaveItem.Image")));
            this.scheduleBindingNavigatorSaveItem.Name = "scheduleBindingNavigatorSaveItem";
            this.scheduleBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.scheduleBindingNavigatorSaveItem.Text = "Save Data";
            this.scheduleBindingNavigatorSaveItem.Click += new System.EventHandler(this.scheduleBindingNavigatorSaveItem_Click);
            // 
            // scheduleBindingNavigatorRefreshItem
            // 
            this.scheduleBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.scheduleBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("scheduleBindingNavigatorRefreshItem.Image")));
            this.scheduleBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.scheduleBindingNavigatorRefreshItem.Name = "scheduleBindingNavigatorRefreshItem";
            this.scheduleBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.scheduleBindingNavigatorRefreshItem.Text = "Refresh";
            this.scheduleBindingNavigatorRefreshItem.Click += new System.EventHandler(this.scheduleBindingNavigatorRefreshItem_Click);
            // 
            // toolStripSeparator70
            // 
            this.toolStripSeparator70.Name = "toolStripSeparator70";
            this.toolStripSeparator70.Size = new System.Drawing.Size(6, 25);
            // 
            // scheduleConditionBuilderItem
            // 
            this.scheduleConditionBuilderItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.scheduleConditionBuilderItem.Image = ((System.Drawing.Image)(resources.GetObject("scheduleConditionBuilderItem.Image")));
            this.scheduleConditionBuilderItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.scheduleConditionBuilderItem.Name = "scheduleConditionBuilderItem";
            this.scheduleConditionBuilderItem.Size = new System.Drawing.Size(23, 22);
            this.scheduleConditionBuilderItem.Text = "Condition builder";
            this.scheduleConditionBuilderItem.Click += new System.EventHandler(this.scheduleConditionBuilderItem_Click);
            // 
            // mainPanelImageList
            // 
            this.mainPanelImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("mainPanelImageList.ImageStream")));
            this.mainPanelImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.mainPanelImageList.Images.SetKeyName(0, "user1_monitor.png");
            this.mainPanelImageList.Images.SetKeyName(1, "large icons.png");
            this.mainPanelImageList.Images.SetKeyName(2, "notepad.png");
            this.mainPanelImageList.Images.SetKeyName(3, "bookmark.png");
            this.mainPanelImageList.Images.SetKeyName(4, "document_certificate.png");
            this.mainPanelImageList.Images.SetKeyName(5, "chat_32.png");
            this.mainPanelImageList.Images.SetKeyName(6, "Fatcow-Farm-Fresh-File-extension-log.ico");
            this.mainPanelImageList.Images.SetKeyName(7, "preferences.png");
            this.mainPanelImageList.Images.SetKeyName(8, "address book.png");
            this.mainPanelImageList.Images.SetKeyName(9, "calendar.png");
            // 
            // openImageDialog
            // 
            this.openImageDialog.Filter = "Image Files (*.bmp, *.jpg)|*.bmp;*.jpg";
            // 
            // openTextFileDialog
            // 
            this.openTextFileDialog.DefaultExt = "txt";
            this.openTextFileDialog.Filter = "Text files (*.txt)|*.txt";
            // 
            // openLogFileDialog
            // 
            this.openLogFileDialog.DefaultExt = "txt";
            this.openLogFileDialog.Filter = "Log files (*.log)|*.log";
            // 
            // pwdToolTip
            // 
            this.pwdToolTip.AutoPopDelay = 2000;
            this.pwdToolTip.InitialDelay = 200;
            this.pwdToolTip.ReshowDelay = 100;
            // 
            // logFilesFolderBrowserDialog
            // 
            this.logFilesFolderBrowserDialog.Description = "The path to the LOG-files vault:";
            // 
            // postLoginOpenFileDialog
            // 
            this.postLoginOpenFileDialog.Filter = "Executable files (*.exe)|*.exe";
            // 
            // commandHistoryOpenFileDialog
            // 
            this.commandHistoryOpenFileDialog.Filter = "Database files (*.db)|*.db";
            // 
            // directoriesBrowserDialog
            // 
            this.directoriesBrowserDialog.Description = "Directory:";
            // 
            // openUpdaterFileDialog
            // 
            this.openUpdaterFileDialog.DefaultExt = "exe";
            this.openUpdaterFileDialog.Filter = "Executable files (*.exe)|*.exe";
            // 
            // updateDirBrowserDialog
            // 
            this.updateDirBrowserDialog.Description = "The path to the update directory:";
            // 
            // eduLessonsImageList
            // 
            this.eduLessonsImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("eduLessonsImageList.ImageStream")));
            this.eduLessonsImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.eduLessonsImageList.Images.SetKeyName(0, "info2.png");
            this.eduLessonsImageList.Images.SetKeyName(1, "help.png");
            this.eduLessonsImageList.Images.SetKeyName(2, "file_apply.png");
            // 
            // fmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1008, 729);
            this.Controls.Add(this.mainPanel);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.mainMenu);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.mainMenu;
            this.Name = "fmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "NovaTend management tool";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.fmMain_FormClosing);
            this.Load += new System.EventHandler(this.fmMain_Load);
            this.Shown += new System.EventHandler(this.fmMain_Shown);
            this.mainMenu.ResumeLayout(false);
            this.mainMenu.PerformLayout();
            this.mainPanel.ResumeLayout(false);
            this.mainTabControl.ResumeLayout(false);
            this.usersTabPage.ResumeLayout(false);
            this.userManagementTabControl.ResumeLayout(false);
            this.userPage.ResumeLayout(false);
            this.userPage.PerformLayout();
            this.userDetailsTabControl.ResumeLayout(false);
            this.mainUsrInfoPage.ResumeLayout(false);
            this.mainUsrInfoPage.PerformLayout();
            this.usrGroupsInfoPage.ResumeLayout(false);
            this.usrGroupsInfoPage.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userGroupsDataGridView)).EndInit();
            this.usrPermissionsPage.ResumeLayout(false);
            this.usrPermissionsPage.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userPermissionsDataGridView)).EndInit();
            this.userPwdPage.ResumeLayout(false);
            this.userPwdPage.PerformLayout();
            this.usrEduPage.ResumeLayout(false);
            this.usrEduPage.PerformLayout();
            this.usrAccountsPage.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.userAccountsDataGridView)).EndInit();
            this.usrAccListTitlePanel.ResumeLayout(false);
            this.usrAccListTitlePanel.PerformLayout();
            this.usrCheckParamsPage.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.userCheckValuesDataGridView)).EndInit();
            this.checkParamTitlePanel.ResumeLayout(false);
            this.checkParamTitlePanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userNamesDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.usersBindingNavigator)).EndInit();
            this.usersBindingNavigator.ResumeLayout(false);
            this.usersBindingNavigator.PerformLayout();
            this.userGroupsPage.ResumeLayout(false);
            this.userGroupsPage.PerformLayout();
            this.groupDetailsPanel.ResumeLayout(false);
            this.groupUsersGroupBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.usersGroupDataGridView)).EndInit();
            this.groupAuthSystemsGroupBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.groupGroupAuthSystemsDataGridView)).EndInit();
            this.groupReferencesPanel.ResumeLayout(false);
            this.groupPermissionsGroupBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.groupPermissionsDataGridView)).EndInit();
            this.groupListGroupBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.groupsDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.groupsBindingNavigator)).EndInit();
            this.groupsBindingNavigator.ResumeLayout(false);
            this.groupsBindingNavigator.PerformLayout();
            this.computersPage.ResumeLayout(false);
            this.computersPage.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.computersDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.computersBindingNavigator)).EndInit();
            this.computersBindingNavigator.ResumeLayout(false);
            this.computersBindingNavigator.PerformLayout();
            this.authSystemsPage.ResumeLayout(false);
            this.authSystemsPage.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.authSystemsDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.authSystemsBindingNavigator)).EndInit();
            this.authSystemsBindingNavigator.ResumeLayout(false);
            this.authSystemsBindingNavigator.PerformLayout();
            this.presetTabPage.ResumeLayout(false);
            this.presetSplitContainer.Panel1.ResumeLayout(false);
            this.presetSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.presetSplitContainer)).EndInit();
            this.presetSplitContainer.ResumeLayout(false);
            this.presetDetailsMainPanel.ResumeLayout(false);
            this.presetDetailsMainPanel.PerformLayout();
            this.presetDetailsSubPanel.ResumeLayout(false);
            this.presetScreenObjectsGroupBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.presetScreenObjectsDataGridView)).EndInit();
            this.presetScreensGroupBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.presetScreensDataGridView)).EndInit();
            this.presetNamesGroupBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.presetNamesDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.presetBindingNavigator)).EndInit();
            this.presetBindingNavigator.ResumeLayout(false);
            this.presetBindingNavigator.PerformLayout();
            this.screenObjectsPanel.ResumeLayout(false);
            this.screenObjectsPanel.PerformLayout();
            this.screenObjectsGroupBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.screenObjectsDataGridView)).EndInit();
            this.screenObjectValuesTabControl.ResumeLayout(false);
            this.tabScreenObjectText.ResumeLayout(false);
            this.screenObjectTextPanel.ResumeLayout(false);
            this.tabScreenObjectImage.ResumeLayout(false);
            this.screenObjectImagePanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.screenObjectPictureBox)).EndInit();
            this.tabScreenObjectListValues.ResumeLayout(false);
            this.screenObjectListValuesPanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.screenObjectListValuesDataGridView)).EndInit();
            this.screensGroupBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.screensDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.screenObjectsBindingNavigator)).EndInit();
            this.screenObjectsBindingNavigator.ResumeLayout(false);
            this.screenObjectsBindingNavigator.PerformLayout();
            this.educationTabPage.ResumeLayout(false);
            this.educationMainPanel.ResumeLayout(false);
            this.educationMainSplitContainer.Panel1.ResumeLayout(false);
            this.educationMainSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.educationMainSplitContainer)).EndInit();
            this.educationMainSplitContainer.ResumeLayout(false);
            this.eduEditorPanel.ResumeLayout(false);
            this.eduLessonsTabControl.ResumeLayout(false);
            this.tabLessons.ResumeLayout(false);
            this.tabLessons.PerformLayout();
            this.eduLessonSplitContainer.Panel1.ResumeLayout(false);
            this.eduLessonSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.eduLessonSplitContainer)).EndInit();
            this.eduLessonSplitContainer.ResumeLayout(false);
            this.eduLessonImagePanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.eduLessonPictureBox)).EndInit();
            this.eduLessonTextPanel.ResumeLayout(false);
            this.lessonsOrderPanel.ResumeLayout(false);
            this.lessonsOrderPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduLessonsBindingNavigator)).EndInit();
            this.eduLessonsBindingNavigator.ResumeLayout(false);
            this.eduLessonsBindingNavigator.PerformLayout();
            this.tabQuestions.ResumeLayout(false);
            this.eduQuestionSplitContainer.Panel1.ResumeLayout(false);
            this.eduQuestionSplitContainer.Panel1.PerformLayout();
            this.eduQuestionSplitContainer.Panel2.ResumeLayout(false);
            this.eduQuestionSplitContainer.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduQuestionSplitContainer)).EndInit();
            this.eduQuestionSplitContainer.ResumeLayout(false);
            this.eduQuestionTextPanel.ResumeLayout(false);
            this.questionOrderPanel.ResumeLayout(false);
            this.questionOrderPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduQuestionsBindingNavigator)).EndInit();
            this.eduQuestionsBindingNavigator.ResumeLayout(false);
            this.eduQuestionsBindingNavigator.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduAnswersDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduAnswersBindingNavigator)).EndInit();
            this.eduAnswersBindingNavigator.ResumeLayout(false);
            this.eduAnswersBindingNavigator.PerformLayout();
            this.tabAnswers.ResumeLayout(false);
            this.tabAnswers.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.generalAnswersListDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduAllAnswersBindingNavigator)).EndInit();
            this.eduAllAnswersBindingNavigator.ResumeLayout(false);
            this.eduAllAnswersBindingNavigator.PerformLayout();
            this.eduCategoriesGroupBox.ResumeLayout(false);
            this.eduCategoriesGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduCategoriesDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduCategoriesBindingNavigator)).EndInit();
            this.eduCategoriesBindingNavigator.ResumeLayout(false);
            this.eduCategoriesBindingNavigator.PerformLayout();
            this.eduButtonsBottomPanel.ResumeLayout(false);
            this.eduTabControl.ResumeLayout(false);
            this.usrEduTabPage.ResumeLayout(false);
            this.userEducationSplitContainer.Panel1.ResumeLayout(false);
            this.userEducationSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.userEducationSplitContainer)).EndInit();
            this.userEducationSplitContainer.ResumeLayout(false);
            this.eduUserCategoriesGroupBox.ResumeLayout(false);
            this.eduUserCategoriesGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserCategoriesDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserCategoriesBindingNavigator)).EndInit();
            this.eduUserCategoriesBindingNavigator.ResumeLayout(false);
            this.eduUserCategoriesBindingNavigator.PerformLayout();
            this.eduUserHistoryGroupBox.ResumeLayout(false);
            this.eduUserHistoryGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserHistoryDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserHistoryBindingNavigator)).EndInit();
            this.eduUserHistoryBindingNavigator.ResumeLayout(false);
            this.eduUserHistoryBindingNavigator.PerformLayout();
            this.eduUsersGroupBox.ResumeLayout(false);
            this.eduUsersGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduUsersDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduUsersBindingNavigator)).EndInit();
            this.eduUsersBindingNavigator.ResumeLayout(false);
            this.eduUsersBindingNavigator.PerformLayout();
            this.usrGroupEduTabPage.ResumeLayout(false);
            this.eduUserGroupCategoriesGroupBox.ResumeLayout(false);
            this.eduUserGroupCategoriesGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserGroupCategoriesDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserGroupCategoriesBindingNavigator)).EndInit();
            this.eduUserGroupCategoriesBindingNavigator.ResumeLayout(false);
            this.eduUserGroupCategoriesBindingNavigator.PerformLayout();
            this.eduUserGroupsGroupBox.ResumeLayout(false);
            this.eduUserGroupsGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserGroupsDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eduUserGroupsBindingNavigator)).EndInit();
            this.eduUserGroupsBindingNavigator.ResumeLayout(false);
            this.eduUserGroupsBindingNavigator.PerformLayout();
            this.notificationTabPage.ResumeLayout(false);
            this.notificationSplitContainer.Panel1.ResumeLayout(false);
            this.notificationSplitContainer.Panel1.PerformLayout();
            this.notificationSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.notificationSplitContainer)).EndInit();
            this.notificationSplitContainer.ResumeLayout(false);
            this.noticesImageTextPanel.ResumeLayout(false);
            this.noticeValuesSplitContainer.Panel1.ResumeLayout(false);
            this.noticeValuesSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.noticeValuesSplitContainer)).EndInit();
            this.noticeValuesSplitContainer.ResumeLayout(false);
            this.notificationPicturePanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.notificationPictureBox)).EndInit();
            this.notificationTextPanel.ResumeLayout(false);
            this.noticesTopPanel.ResumeLayout(false);
            this.noticesTopPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.notificationBindingNavigator)).EndInit();
            this.notificationBindingNavigator.ResumeLayout(false);
            this.notificationBindingNavigator.PerformLayout();
            this.notificationsTabControl.ResumeLayout(false);
            this.userNotificationsTabPage.ResumeLayout(false);
            this.userNotificationSplitContainer.Panel1.ResumeLayout(false);
            this.userNotificationSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.userNotificationSplitContainer)).EndInit();
            this.userNotificationSplitContainer.ResumeLayout(false);
            this.userNotificationGroupBox.ResumeLayout(false);
            this.userNotificationGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userNotificationDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.userNotificationBindingNavigator)).EndInit();
            this.userNotificationBindingNavigator.ResumeLayout(false);
            this.userNotificationBindingNavigator.PerformLayout();
            this.userNotificationHistoryGroupBox.ResumeLayout(false);
            this.userNotificationHistoryGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userNotificationHistoryDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.userNotificationHistoryBindingNavigator)).EndInit();
            this.userNotificationHistoryBindingNavigator.ResumeLayout(false);
            this.userNotificationHistoryBindingNavigator.PerformLayout();
            this.notificationUsersGroupBox.ResumeLayout(false);
            this.notificationUsersGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.notificationUsersDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.notificationUsersBindingNavigator)).EndInit();
            this.notificationUsersBindingNavigator.ResumeLayout(false);
            this.notificationUsersBindingNavigator.PerformLayout();
            this.userGroupNotificationsTabPage.ResumeLayout(false);
            this.userGroupNotificationGroupBox.ResumeLayout(false);
            this.userGroupNotificationGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userGroupNotificationDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.userGroupsNotificationBindingNavigator)).EndInit();
            this.userGroupsNotificationBindingNavigator.ResumeLayout(false);
            this.userGroupsNotificationBindingNavigator.PerformLayout();
            this.notificationUserGroupsGroupBox.ResumeLayout(false);
            this.notificationUserGroupsGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.notificationUserGroupsDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.notificationUserGroupsBindingNavigator)).EndInit();
            this.notificationUserGroupsBindingNavigator.ResumeLayout(false);
            this.notificationUserGroupsBindingNavigator.PerformLayout();
            this.licenseTabPage.ResumeLayout(false);
            this.licManagmentMainPanel.ResumeLayout(false);
            this.licenseBottomPanel.ResumeLayout(false);
            this.logFilesTabPage.ResumeLayout(false);
            this.logFileMainPanel.ResumeLayout(false);
            this.logFilesPanel.ResumeLayout(false);
            this.logFilesPanel.PerformLayout();
            this.confTabPage.ResumeLayout(false);
            this.confTabControl.ResumeLayout(false);
            this.tabServiceControl.ResumeLayout(false);
            this.servicesGroupBox.ResumeLayout(false);
            this.servicesButtonsPanel.ResumeLayout(false);
            this.serviceDescriptionGroupBox.ResumeLayout(false);
            this.serviceDescriptionGroupBox.PerformLayout();
            this.tabIPCSettings.ResumeLayout(false);
            this.tabIPCSettings.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.globalServerPriorityNud)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.serverPriorityNud)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.desktopServerPriorityNud)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.hubServerPriorityNud)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.hostServerPriorityNud)).EndInit();
            this.tabDatabaseSettings.ResumeLayout(false);
            this.tabDatabaseSettings.PerformLayout();
            this.tabMessagesSettings.ResumeLayout(false);
            this.tabMessagesSettings.PerformLayout();
            this.tabLOGSettings.ResumeLayout(false);
            this.tabLOGSettings.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fixedSizeNumUpDown)).EndInit();
            this.tabServicesConfiguration.ResumeLayout(false);
            this.tabServicesConfiguration.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.updateSettingsPictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fileTransferPictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.commandsHistorySettingsPictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.programsControlSettingsPictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.postLoginSettingsPictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.logSettingsPictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.msgSettingsPictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dbSettingsPictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ipcSettingsPictureBox)).EndInit();
            this.tabSynchronization.ResumeLayout(false);
            this.tabSynchronization.PerformLayout();
            this.revLinkTabControl.ResumeLayout(false);
            this.revLinkUsersTabPage.ResumeLayout(false);
            this.revLinkGroupsTabPage.ResumeLayout(false);
            this.tabPostLoginSettings.ResumeLayout(false);
            this.tabPostLoginSettings.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.postLoginPeriodNumUpDown)).EndInit();
            this.tabProgramsControlSettings.ResumeLayout(false);
            this.tabProgramsControlSettings.PerformLayout();
            this.tabCommandsHistory.ResumeLayout(false);
            this.tabCommandsHistory.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.commandsHistoryPeriodNumUpDown)).EndInit();
            this.tabFileTransferSettings.ResumeLayout(false);
            this.tabFileTransferSettings.PerformLayout();
            this.tabUpdateSettings.ResumeLayout(false);
            this.tabUpdateSettings.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.updatesPeriodNumericUpDown)).EndInit();
            this.personalTabPage.ResumeLayout(false);
            this.personalPanel.ResumeLayout(false);
            this.personalPanel.PerformLayout();
            this.personalAccoutsParametersPanel.ResumeLayout(false);
            this.personalAccountsParametersSplitContainer.Panel1.ResumeLayout(false);
            this.personalAccountsParametersSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.personalAccountsParametersSplitContainer)).EndInit();
            this.personalAccountsParametersSplitContainer.ResumeLayout(false);
            this.personalUserAccountsGroupBox.ResumeLayout(false);
            this.personalUserAccountsGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.personalAccountsDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.personalAccountsBindingNavigator)).EndInit();
            this.personalAccountsBindingNavigator.ResumeLayout(false);
            this.personalAccountsBindingNavigator.PerformLayout();
            this.personalAccountsHeaderPanel.ResumeLayout(false);
            this.personalAccountsHeaderPanel.PerformLayout();
            this.personalParametersGroupBox.ResumeLayout(false);
            this.personalParametersGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.personalParametersDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.personalParametersBindingNavigator)).EndInit();
            this.personalParametersBindingNavigator.ResumeLayout(false);
            this.personalParametersBindingNavigator.PerformLayout();
            this.personalCheckValuesHeaderPanel.ResumeLayout(false);
            this.personalCheckValuesHeaderPanel.PerformLayout();
            this.personalPwdSettingsPanel.ResumeLayout(false);
            this.personalChangePasswordPanel.ResumeLayout(false);
            this.personalPwdResetSettingsPanel.ResumeLayout(false);
            this.personalPwdResetSettingsPanel.PerformLayout();
            this.personalPwdResetPanel.ResumeLayout(false);
            this.personalPwdResetPanel.PerformLayout();
            this.scheduleTabPage.ResumeLayout(false);
            this.scheduleSplitContainer.Panel1.ResumeLayout(false);
            this.scheduleSplitContainer.Panel1.PerformLayout();
            this.scheduleSplitContainer.Panel2.ResumeLayout(false);
            this.scheduleSplitContainer.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.scheduleSplitContainer)).EndInit();
            this.scheduleSplitContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.controlledProgramsDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.controlledProgramsBindingNavigator)).EndInit();
            this.controlledProgramsBindingNavigator.ResumeLayout(false);
            this.controlledProgramsBindingNavigator.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.scheduleDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.scheduleBindingNavigator)).EndInit();
            this.scheduleBindingNavigator.ResumeLayout(false);
            this.scheduleBindingNavigator.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip mainMenu;
        private System.Windows.Forms.ToolStripMenuItem connectionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.Panel mainPanel;
        private System.Windows.Forms.TabControl mainTabControl;
        private System.Windows.Forms.TabPage usersTabPage;
        private System.Windows.Forms.TabPage presetTabPage;
        private System.Windows.Forms.ImageList mainPanelImageList;
        private System.Windows.Forms.ToolStripMenuItem connectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem disconnectToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.DataGridView userCheckValuesDataGridView;
        private System.Windows.Forms.TextBox userPwdAttemptsCountTextBox;
        private System.Windows.Forms.TextBox userMaxPwdAttemptsCountTextBox;
        private System.Windows.Forms.CheckBox userNeedStudyCheckBox;
        private System.Windows.Forms.CheckBox userRandomEduCategCheckBox;
        private System.Windows.Forms.DataGridView userNamesDataGridView;
        private System.Windows.Forms.BindingNavigator usersBindingNavigator;
        private System.Windows.Forms.ToolStripButton bindingNavigatorAddNewItem;
        private System.Windows.Forms.ToolStripLabel bindingNavigatorCountItem;
        private System.Windows.Forms.ToolStripButton bindingNavigatorDeleteItem;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMoveFirstItem;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMovePreviousItem;
        private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator;
        private System.Windows.Forms.ToolStripTextBox bindingNavigatorPositionItem;
        private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator1;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMoveNextItem;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMoveLastItem;
        private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator2;
        private System.Windows.Forms.ToolStripButton usersBindingNavigatorSaveItem;
        private System.Windows.Forms.BindingNavigator computersBindingNavigator;
        private System.Windows.Forms.ToolStripButton bindingNavigatorAddNewItem1;
        private System.Windows.Forms.ToolStripLabel bindingNavigatorCountItem1;
        private System.Windows.Forms.ToolStripButton bindingNavigatorDeleteItem1;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMoveFirstItem1;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMovePreviousItem1;
        private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator3;
        private System.Windows.Forms.ToolStripTextBox bindingNavigatorPositionItem1;
        private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator4;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMoveNextItem1;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMoveLastItem1;
        private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator5;
        private System.Windows.Forms.ToolStripButton computersBindingNavigatorSaveItem;
        private System.Windows.Forms.DataGridView computersDataGridView;
        private System.Windows.Forms.DataGridViewComboBoxColumn userCheckValueObjectIDColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn userCheckValueColumn;
        private System.Windows.Forms.Panel presetDetailsMainPanel;
        private System.Windows.Forms.Panel screenObjectsPanel;
        private System.Windows.Forms.Panel screenObjectTextPanel;
        private System.Windows.Forms.Button loadScreenObjecTextButton;
        private System.Windows.Forms.RichTextBox screenObjectRichTextBox;
        private System.Windows.Forms.Panel screenObjectImagePanel;
        private System.Windows.Forms.Button loadScreenObjectImageButton;
        private System.Windows.Forms.PictureBox screenObjectPictureBox;
        private System.Windows.Forms.GroupBox screenObjectsGroupBox;
        private System.Windows.Forms.GroupBox screensGroupBox;
        private System.Windows.Forms.DataGridView screensDataGridView;
        private System.Windows.Forms.Panel presetDetailsSubPanel;
        private System.Windows.Forms.GroupBox presetScreenObjectsGroupBox;
        private System.Windows.Forms.DataGridView presetScreenObjectsDataGridView;
        private System.Windows.Forms.Splitter splitter3;
        private System.Windows.Forms.GroupBox presetScreensGroupBox;
        private System.Windows.Forms.DataGridView presetScreensDataGridView;
        private System.Windows.Forms.Splitter splitter2;
        private System.Windows.Forms.GroupBox presetNamesGroupBox;
        private System.Windows.Forms.DataGridView presetNamesDataGridView;
        private System.Windows.Forms.BindingNavigator presetBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton7;
        private System.Windows.Forms.ToolStripLabel toolStripLabel2;
        private System.Windows.Forms.ToolStripButton toolStripButton8;
        private System.Windows.Forms.ToolStripButton toolStripButton9;
        private System.Windows.Forms.ToolStripButton toolStripButton10;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox2;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
        private System.Windows.Forms.ToolStripButton toolStripButton11;
        private System.Windows.Forms.ToolStripButton toolStripButton12;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator6;
        private System.Windows.Forms.ToolStripButton presetBindingNavigatorSaveItem;
        private System.Windows.Forms.DataGridView screenObjectsDataGridView;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectCaptionColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn screenObjectTypeIDColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectStrValueColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectLocationXColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectLocationYColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectLocationXPersColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectLocationYPersColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectWidthColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectHeightColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectWidthPersColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectHeightPersColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectColorColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectFontSizeColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectTextColorColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenCaptionColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn screenTypeIDColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenLocationXColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenLocationYColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenLocationXPersColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenLocationYPersColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenWidthColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenHeightColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenWidthPersColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenHeightPersColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenColorColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenFontSizeColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenTextColorColumn;
        private System.Windows.Forms.Panel screenObjectListValuesPanel;
        private System.Windows.Forms.OpenFileDialog openImageDialog;
        private System.Windows.Forms.OpenFileDialog openTextFileDialog;
        private System.Windows.Forms.Button scrennObjectImageClearButton;
        private System.Windows.Forms.Button screenObjectTextClearButton;
        private System.Windows.Forms.BindingNavigator screenObjectsBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.Windows.Forms.ToolStripButton toolStripButton2;
        private System.Windows.Forms.ToolStripButton toolStripButton3;
        private System.Windows.Forms.ToolStripButton toolStripButton4;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton toolStripButton5;
        private System.Windows.Forms.ToolStripButton toolStripButton6;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripButton screenObjectsBindingNavigatorSaveItem;
        private System.Windows.Forms.DataGridView screenObjectListValuesDataGridView;
        private System.Windows.Forms.Splitter splitter4;
        private System.Windows.Forms.TabPage educationTabPage;
        private System.Windows.Forms.Panel educationMainPanel;
        private System.Windows.Forms.SplitContainer educationMainSplitContainer;
        private System.Windows.Forms.GroupBox eduCategoriesGroupBox;
        private System.Windows.Forms.DataGridView eduCategoriesDataGridView;
        private System.Windows.Forms.BindingNavigator eduLessonsBindingNavigator;
        private System.Windows.Forms.ToolStripButton eduLessonsBindingNavigatorAddNewItem;
        private System.Windows.Forms.ToolStripLabel toolStripLabel4;
        private System.Windows.Forms.ToolStripButton eduLessonsBindingNavigatorRemoveItem;
        private System.Windows.Forms.ToolStripButton toolStripButton21;
        private System.Windows.Forms.ToolStripButton toolStripButton22;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator10;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox4;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator11;
        private System.Windows.Forms.ToolStripButton toolStripButton23;
        private System.Windows.Forms.ToolStripButton toolStripButton24;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator12;
        private System.Windows.Forms.ToolStripButton eduLessonsBindingNavigatorSaveItem;
        private System.Windows.Forms.Panel eduLessonImagePanel;
        private System.Windows.Forms.Button eduLessonImageClearButton;
        private System.Windows.Forms.Button eduLessonImageOpenButton;
        private System.Windows.Forms.PictureBox eduLessonPictureBox;
        private System.Windows.Forms.Panel lessonsOrderPanel;
        private System.Windows.Forms.TextBox eduLessonOrderTextBox;
        private System.Windows.Forms.Panel eduLessonTextPanel;
        private System.Windows.Forms.Button eduLessonTextClearButton;
        private System.Windows.Forms.RichTextBox eduLessonRichTextBox;
        private System.Windows.Forms.Button eduLessonTextOpenButton;
        private System.Windows.Forms.Splitter splitter9;
        private System.Windows.Forms.DataGridViewTextBoxColumn eduCategoriesNameColumn;
        private System.Windows.Forms.GroupBox eduUserHistoryGroupBox;
        private System.Windows.Forms.DataGridView eduUserHistoryDataGridView;
        private System.Windows.Forms.BindingNavigator eduUserHistoryBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton43;
        private System.Windows.Forms.ToolStripLabel toolStripLabel8;
        private System.Windows.Forms.ToolStripButton toolStripButton44;
        private System.Windows.Forms.ToolStripButton toolStripButton45;
        private System.Windows.Forms.ToolStripButton toolStripButton46;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator22;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox8;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator23;
        private System.Windows.Forms.ToolStripButton toolStripButton47;
        private System.Windows.Forms.ToolStripButton toolStripButton48;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator24;
        private System.Windows.Forms.ToolStripButton eduUserHistoryBindingNavigatorSaveItem;
        private System.Windows.Forms.GroupBox eduUserCategoriesGroupBox;
        private System.Windows.Forms.DataGridView eduUserCategoriesDataGridView;
        private System.Windows.Forms.BindingNavigator eduUserCategoriesBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton37;
        private System.Windows.Forms.ToolStripLabel toolStripLabel7;
        private System.Windows.Forms.ToolStripButton toolStripButton38;
        private System.Windows.Forms.ToolStripButton toolStripButton39;
        private System.Windows.Forms.ToolStripButton toolStripButton40;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator19;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox7;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator20;
        private System.Windows.Forms.ToolStripButton toolStripButton41;
        private System.Windows.Forms.ToolStripButton toolStripButton42;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator21;
        private System.Windows.Forms.ToolStripButton eduUserCategoriesBindingNavigatorSaveItem;
        private System.Windows.Forms.GroupBox eduUsersGroupBox;
        private System.Windows.Forms.DataGridView eduUsersDataGridView;
        private System.Windows.Forms.BindingNavigator eduUsersBindingNavigator;
        private System.Windows.Forms.ToolStripLabel toolStripLabel6;
        private System.Windows.Forms.ToolStripButton toolStripButton33;
        private System.Windows.Forms.ToolStripButton toolStripButton34;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator16;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox6;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator17;
        private System.Windows.Forms.ToolStripButton toolStripButton35;
        private System.Windows.Forms.ToolStripButton toolStripButton36;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator18;
        private System.Windows.Forms.DataGridViewComboBoxColumn eduUserQuestionTextColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn eduUserAnswerTextColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn eduUserCorrectAnswerColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn eduUserAnswerDateColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn eduUserNameColumn;
        private System.Windows.Forms.TabPage notificationTabPage;
        private System.Windows.Forms.SplitContainer notificationSplitContainer;
        private System.Windows.Forms.Panel noticesImageTextPanel;
        private System.Windows.Forms.Panel notificationTextPanel;
        private System.Windows.Forms.Button noticesTextClearBtn;
        private System.Windows.Forms.RichTextBox notificationRichTextBox;
        private System.Windows.Forms.Button noticesTextOpenBtn;
        private System.Windows.Forms.Panel notificationPicturePanel;
        private System.Windows.Forms.Button noticesImageClearBtn;
        private System.Windows.Forms.PictureBox notificationPictureBox;
        private System.Windows.Forms.BindingNavigator notificationBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton19;
        private System.Windows.Forms.ToolStripLabel toolStripLabel9;
        private System.Windows.Forms.ToolStripButton toolStripButton20;
        private System.Windows.Forms.ToolStripButton toolStripButton25;
        private System.Windows.Forms.ToolStripButton toolStripButton26;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator25;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox9;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator26;
        private System.Windows.Forms.ToolStripButton toolStripButton31;
        private System.Windows.Forms.ToolStripButton toolStripButton32;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator27;
        private System.Windows.Forms.ToolStripButton notificationBindingNavigatorSaveItem;
        private System.Windows.Forms.Panel noticesTopPanel;
        private System.Windows.Forms.Splitter splitter15;
        private System.Windows.Forms.Label noticeScopeLabel;
        private System.Windows.Forms.Label noticeDisplayTypeLabel;
        private System.Windows.Forms.Label noticeTypeLabel;
        private System.Windows.Forms.ComboBox noticeScopesComboBox;
        private System.Windows.Forms.ComboBox noticeDisplayTypeComboBox;
        private System.Windows.Forms.ComboBox noticeTypeComboBox;
        private System.Windows.Forms.GroupBox userNotificationGroupBox;
        private System.Windows.Forms.DataGridView userNotificationDataGridView;
        private System.Windows.Forms.BindingNavigator userNotificationBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton54;
        private System.Windows.Forms.ToolStripLabel toolStripLabel11;
        private System.Windows.Forms.ToolStripButton toolStripButton55;
        private System.Windows.Forms.ToolStripButton toolStripButton56;
        private System.Windows.Forms.ToolStripButton toolStripButton57;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator31;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox11;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator32;
        private System.Windows.Forms.ToolStripButton toolStripButton58;
        private System.Windows.Forms.ToolStripButton toolStripButton59;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator33;
        private System.Windows.Forms.ToolStripButton userNotificationBindingNavigatorSaveItem;
        private System.Windows.Forms.GroupBox notificationUsersGroupBox;
        private System.Windows.Forms.DataGridView notificationUsersDataGridView;
        private System.Windows.Forms.BindingNavigator notificationUsersBindingNavigator;
        private System.Windows.Forms.ToolStripLabel toolStripLabel10;
        private System.Windows.Forms.ToolStripButton toolStripButton50;
        private System.Windows.Forms.ToolStripButton toolStripButton51;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator28;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox10;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator29;
        private System.Windows.Forms.ToolStripButton toolStripButton52;
        private System.Windows.Forms.ToolStripButton toolStripButton53;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator30;
        private System.Windows.Forms.Button noticesImageOpenBtn;
        private System.Windows.Forms.DataGridViewTextBoxColumn notificationUsersUserNameTextBoxColumn;
        private System.Windows.Forms.GroupBox userNotificationHistoryGroupBox;
        private System.Windows.Forms.DataGridView userNotificationHistoryDataGridView;
        private System.Windows.Forms.BindingNavigator userNotificationHistoryBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton49;
        private System.Windows.Forms.ToolStripLabel toolStripLabel12;
        private System.Windows.Forms.ToolStripButton toolStripButton60;
        private System.Windows.Forms.ToolStripButton toolStripButton61;
        private System.Windows.Forms.ToolStripButton toolStripButton62;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator34;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox12;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator35;
        private System.Windows.Forms.ToolStripButton toolStripButton63;
        private System.Windows.Forms.ToolStripButton toolStripButton64;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator36;
        private System.Windows.Forms.ToolStripButton userNotificationHistoryBindingNavigatorSaveItem;
        private System.Windows.Forms.TabPage licenseTabPage;
        private System.Windows.Forms.Panel licManagmentMainPanel;
        private System.Windows.Forms.Button btnSaveLicenseInfo;
        private System.Windows.Forms.TabPage logFilesTabPage;
        private System.Windows.Forms.Panel logFileMainPanel;
        private System.Windows.Forms.RichTextBox logFileRichTextBox;
        private System.Windows.Forms.Panel logFilesPanel;
        private System.Windows.Forms.Label logFilePathLabel;
        private System.Windows.Forms.Button logFileClearButton;
        private System.Windows.Forms.Button logFileOpenButton;
        private System.Windows.Forms.OpenFileDialog openLogFileDialog;
        private System.Windows.Forms.DataGridView userPermissionsDataGridView;
        private System.Windows.Forms.TabPage confTabPage;
        private System.Windows.Forms.TreeView confTreeView;
        private System.Windows.Forms.ImageList confImageList;
        private System.Windows.Forms.Splitter splitter28;
        private System.Windows.Forms.TabControl confTabControl;
        private System.Windows.Forms.TabPage tabServiceControl;
        private System.Windows.Forms.Splitter splitter29;
        private System.Windows.Forms.GroupBox servicesGroupBox;
        private System.Windows.Forms.ListView servicesListView;
        private System.Windows.Forms.GroupBox serviceDescriptionGroupBox;
        private System.Windows.Forms.TextBox serviceDescriptionTextBox;
        private System.Windows.Forms.TabPage tabIPCSettings;
        private System.Windows.Forms.TabPage tabDatabaseSettings;
        private System.Windows.Forms.TabPage tabMessagesSettings;
        private System.Windows.Forms.TabPage tabLOGSettings;
        private System.Windows.Forms.ColumnHeader nameColumnHeader;
        private System.Windows.Forms.ColumnHeader statusColumnHeader;
        private System.Windows.Forms.Button btnSaveIPCSettings;
        private System.Windows.Forms.Label lblIPCTitle;
        private System.Windows.Forms.TextBox dbPasswordTextBox;
        private System.Windows.Forms.Label lblDBPassword;
        private System.Windows.Forms.TextBox dbUserNameTextBox;
        private System.Windows.Forms.Label lblDBUserName;
        private System.Windows.Forms.Button btnDataBaseAccessSettingsSave;
        private System.Windows.Forms.TextBox dbNameTextBox;
        private System.Windows.Forms.Label lblDBName;
        private System.Windows.Forms.TextBox dbServerTextBox;
        private System.Windows.Forms.Label lblDBServer;
        private System.Windows.Forms.Label lblDatabaseAccessSettings;
        private System.Windows.Forms.Label lblEmailSecType;
        private System.Windows.Forms.Button btnMessagingSettingsSave;
        private System.Windows.Forms.TextBox emailPortTextBox;
        private System.Windows.Forms.Label lblEmailPort;
        private System.Windows.Forms.TextBox emailHostTextBox;
        private System.Windows.Forms.Label lblEMailHost;
        private System.Windows.Forms.Label lblEMailSettings;
        private System.Windows.Forms.CheckBox emailAuthCheckBox;
        private System.Windows.Forms.ComboBox emailSecTypeComboBox;
        private System.Windows.Forms.TextBox emailRecipientTextBox;
        private System.Windows.Forms.Label lblEmailRecipient;
        private System.Windows.Forms.TextBox emailSenderTextBox;
        private System.Windows.Forms.Label lblEmailSender;
        private System.Windows.Forms.TextBox emailPasswordTextBox;
        private System.Windows.Forms.Label lblEmailPassword;
        private System.Windows.Forms.TextBox emailLoginTextBox;
        private System.Windows.Forms.Label lblEmailLogin;
        private System.Windows.Forms.Button btnLogSettingsSave;
        private System.Windows.Forms.CheckBox logEmailCheckBox;
        private System.Windows.Forms.CheckBox logEncryptionCheckBox;
        private System.Windows.Forms.Label lblLOGSettings;
        private System.Windows.Forms.TextBox userNameTextBox;
        private System.Windows.Forms.DateTimePicker lastLogOnDateTimePicker;
        private System.Windows.Forms.Label dateOfLastLogOnLabel;
        private System.Windows.Forms.DataGridView authSystemsDataGridView;
        private System.Windows.Forms.BindingNavigator authSystemsBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton66;
        private System.Windows.Forms.ToolStripLabel toolStripLabel14;
        private System.Windows.Forms.ToolStripButton toolStripButton73;
        private System.Windows.Forms.ToolStripButton toolStripButton74;
        private System.Windows.Forms.ToolStripButton toolStripButton75;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator40;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox14;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator41;
        private System.Windows.Forms.ToolStripButton toolStripButton76;
        private System.Windows.Forms.ToolStripButton toolStripButton77;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator42;
        private System.Windows.Forms.ToolStripButton authSystemsBindingNavigatorSaveItem;
        private System.Windows.Forms.DataGridView userAccountsDataGridView;
        private System.Windows.Forms.ComboBox onDelUserAccActionComboBox;
        private System.Windows.Forms.Label lblUserAccountsOnDeleteAction;
        private System.Windows.Forms.Label lblUserAccountsManagement;
        private System.Windows.Forms.TabPage tabServicesConfiguration;
        private System.Windows.Forms.Label logSettingsLabel;
        private System.Windows.Forms.PictureBox logSettingsPictureBox;
        private System.Windows.Forms.Label msgSettingsLabel;
        private System.Windows.Forms.PictureBox msgSettingsPictureBox;
        private System.Windows.Forms.Label dbSettingsLabel;
        private System.Windows.Forms.PictureBox dbSettingsPictureBox;
        private System.Windows.Forms.Label ipcSettingsLabel;
        private System.Windows.Forms.PictureBox ipcSettingsPictureBox;
        private System.Windows.Forms.TabPage tabSynchronization;
        private System.Windows.Forms.Label lblPeriodicSyncSet;
        private System.Windows.Forms.ComboBox syncPeriodComboBox;
        private System.Windows.Forms.Label lblSyncPeriod;
        private System.Windows.Forms.CheckBox periodicSyncOnOffCheckBox;
        private System.Windows.Forms.Button btnSaveSyncSettings;
        private System.Windows.Forms.Button btnForcedSync;
        private System.Windows.Forms.Label lblSyncTime;
        private System.Windows.Forms.ComboBox revSyncAuthSystemsComboBox;
        private System.Windows.Forms.Label lblReverseSyncAuthSystem;
        private System.Windows.Forms.Label lblReverseSyncSettings;
        private System.Windows.Forms.Button btnReverseLink;
        private System.Windows.Forms.ListView accountsListView;
        private System.Windows.Forms.ColumnHeader userNameColumnHeader;
        private System.Windows.Forms.CheckBox syncLogonCheckBox;
        private System.Windows.Forms.Label lblLogonSyncSettings;
        private System.Windows.Forms.Button btnRefreshRevUsersList;
        private System.Windows.Forms.ImageList usersImageList;
        private System.Windows.Forms.TabPage personalTabPage;
        private System.Windows.Forms.Panel personalPanel;
        private System.Windows.Forms.Panel servicesButtonsPanel;
        private System.Windows.Forms.Button btnRefreshServicesList;
        private System.Windows.Forms.Button btnRestart;
        private System.Windows.Forms.Button btnPause;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Label personalLogonDateLabel;
        private System.Windows.Forms.TextBox personalFullNameTextBox;
        private System.Windows.Forms.TextBox personalUserNameTextBox;
        private System.Windows.Forms.Button saveUserButton;
        private System.Windows.Forms.Label personalPwdAttemptsLabel;
        private System.Windows.Forms.Label personalMaxPwdAttemptsLabel;
        private System.Windows.Forms.Label personalEducationLabel;
        private System.Windows.Forms.TextBox personalUserPhoneTextBox;
        private System.Windows.Forms.TextBox personalUserEmailTextBox;
        private System.Windows.Forms.CheckBox personalSMSResetCheckBox;
        private System.Windows.Forms.CheckBox personalEmailResetCheckBox;
        private System.Windows.Forms.Label personalPwdResetPeriodLabel;
        private System.Windows.Forms.Label personalPwdResetDateLabel;
        private System.Windows.Forms.GroupBox personalUserAccountsGroupBox;
        private System.Windows.Forms.DataGridView personalAccountsDataGridView;
        private System.Windows.Forms.BindingNavigator personalAccountsBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton84;
        private System.Windows.Forms.ToolStripLabel toolStripLabel16;
        private System.Windows.Forms.ToolStripButton toolStripButton85;
        private System.Windows.Forms.ToolStripButton toolStripButton86;
        private System.Windows.Forms.ToolStripButton toolStripButton87;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator47;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox16;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator48;
        private System.Windows.Forms.ToolStripButton toolStripButton88;
        private System.Windows.Forms.ToolStripButton toolStripButton89;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator49;
        private System.Windows.Forms.ToolStripButton personalAccountsBindingNavigatorSaveItem;
        private System.Windows.Forms.GroupBox personalParametersGroupBox;
        private System.Windows.Forms.DataGridView personalParametersDataGridView;
        private System.Windows.Forms.DataGridViewComboBoxColumn personalParameterNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn personalParameterValueColumn;
        private System.Windows.Forms.BindingNavigator personalParametersBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton91;
        private System.Windows.Forms.ToolStripLabel toolStripLabel17;
        private System.Windows.Forms.ToolStripButton toolStripButton92;
        private System.Windows.Forms.ToolStripButton toolStripButton93;
        private System.Windows.Forms.ToolStripButton toolStripButton94;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator50;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox17;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator51;
        private System.Windows.Forms.ToolStripButton toolStripButton95;
        private System.Windows.Forms.ToolStripButton toolStripButton96;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator52;
        private System.Windows.Forms.ToolStripButton personalParametersBindingNavigatorSaveItem;
        private System.Windows.Forms.Label tempInstructionLabel1;
        private System.Windows.Forms.Button refreshUserButton;
        private System.Windows.Forms.ToolStripButton personalAccountsBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton personalParametersBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton usersBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton authSystemsBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton computersBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton screenObjectsBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton presetBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton eduLessonsBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton eduUserHistoryBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton eduUserCategoriesBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton eduUsersBindingNavigatorRefreshIntem;
        private System.Windows.Forms.BindingNavigator eduCategoriesBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton13;
        private System.Windows.Forms.ToolStripLabel toolStripLabel3;
        private System.Windows.Forms.ToolStripButton toolStripButton14;
        private System.Windows.Forms.ToolStripButton toolStripButton15;
        private System.Windows.Forms.ToolStripButton toolStripButton16;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator7;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox3;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator8;
        private System.Windows.Forms.ToolStripButton toolStripButton17;
        private System.Windows.Forms.ToolStripButton toolStripButton18;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator9;
        private System.Windows.Forms.ToolStripButton eduCategoriesBindingNavigatorSaveItem;
        private System.Windows.Forms.ToolStripButton eduCategoriesBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton notificationBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton userNotificationHistoryBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton userNotificationBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripButton notificationUsersBindingNavigatorRefreshItem;
        private System.Windows.Forms.Button btnRefreshLicenseInfo;
        private System.Windows.Forms.TextBox gvPasswordTextBox;
        private System.Windows.Forms.Label lblGVPassword;
        private System.Windows.Forms.TextBox gvLoginTextBox;
        private System.Windows.Forms.Label lblGVLogin;
        private System.Windows.Forms.Label lblGVSettings;
        private System.Windows.Forms.TextBox userPhoneTextBox;
        private System.Windows.Forms.TextBox userEmailTextBox;
        private System.Windows.Forms.CheckBox userSMSPwdResetCheckBox;
        private System.Windows.Forms.CheckBox userEmailPwdResetCheckBox;
        private System.Windows.Forms.CheckBox userLockedCheckBox;
        private System.Windows.Forms.Label hoursLabel;
        private System.Windows.Forms.TextBox userPwdResetPeriodTextBox;
        private System.Windows.Forms.DateTimePicker userPwdResetDateTimePicker;
        private System.Windows.Forms.Label userPwdResetDateLabel;
        private System.Windows.Forms.CheckBox userPwdResetedCheckBox;
        private System.Windows.Forms.Label userPwdTypeLabel;
        private System.Windows.Forms.ComboBox userPwdTypeComboBox;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator56;
        private System.Windows.Forms.ToolStripButton authSystemsBindingNavigatorConfigureItem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label personalGroupsLabel;
        private System.Windows.Forms.ListView personalGroupsListView;
        private System.Windows.Forms.Panel personalVerticalSplitPanel;
        private System.Windows.Forms.Panel personalPwdSettingsPanel;
        private System.Windows.Forms.Panel personalPwdResetPanel;
        private System.Windows.Forms.Panel personalPwdResetSettingsPanel;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label personalPasswrodSettingLabel;
        private System.Windows.Forms.Label personalPwdTypeLabel;
        private System.Windows.Forms.ComboBox personalPwdTypeComboBox;
        private System.Windows.Forms.Panel personalChangePasswordPanel;
        private System.Windows.Forms.Button changePasswordButton;
        private System.Windows.Forms.Panel personalAccoutsParametersPanel;
        private System.Windows.Forms.SplitContainer personalAccountsParametersSplitContainer;
        private System.Windows.Forms.Panel personalAccountsHeaderPanel;
        private System.Windows.Forms.Label personalAccountsLabel;
        private System.Windows.Forms.Panel personalCheckValuesHeaderPanel;
        private System.Windows.Forms.Label personalCheckValuesHeaderLabel;
        private System.Windows.Forms.DataGridViewComboBoxColumn personalAuthSystemNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn personalUserNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn personalUserPasswordColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn personalPassThruPwdColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn personalLastLogonDateColumn;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator44;
        private System.Windows.Forms.ToolStripButton personalAccountsBindingNavigatorChangePwdItem;
        private System.Windows.Forms.Label changeDBPwdLabel;
        private System.Windows.Forms.Label changeEmailPwdLabel;
        private System.Windows.Forms.Label changeGVoicePwdLabel;
        private System.Windows.Forms.ToolTip pwdToolTip;
        private System.Windows.Forms.Button logPathButton;
        private System.Windows.Forms.TextBox logPathTextBox;
        private System.Windows.Forms.Label logPathLabel;
        private System.Windows.Forms.FolderBrowserDialog logFilesFolderBrowserDialog;
        private System.Windows.Forms.DataGridViewTextBoxColumn presetNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn presetDateColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn presetDescriptionColumn;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator37;
        private System.Windows.Forms.ToolStripButton presetBindingNavigatorHookupIten;
        private System.Windows.Forms.DataGridViewComboBoxColumn presetScreenObjectNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn presetScreenObjectOrderColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn presetScreenObjectScopeColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn presetScreenNameColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn presetScreenScopeColumn;
        private System.Windows.Forms.ComboBox hostServerTypeComboBox;
        private System.Windows.Forms.Label hostServerTypeLabel;
        private System.Windows.Forms.TextBox hostServerIDTextBox;
        private System.Windows.Forms.Label hostServerIDLabel;
        private System.Windows.Forms.Label hostServerLabel;
        private System.Windows.Forms.Label hostServerPriorityLabel;
        private System.Windows.Forms.NumericUpDown hostServerPriorityNud;
        private System.Windows.Forms.TextBox hostServerAddressTextBox;
        private System.Windows.Forms.Label hostServerAddressLabel;
        private System.Windows.Forms.TextBox hostServerPortTextBox;
        private System.Windows.Forms.Label hostServerPortLabel;
        private System.Windows.Forms.TextBox hostServerNameTextBox;
        private System.Windows.Forms.Label hostServerNameLabel;
        private System.Windows.Forms.Label desktopServerPriorityLabel;
        private System.Windows.Forms.NumericUpDown desktopServerPriorityNud;
        private System.Windows.Forms.TextBox desktopServerAddressTextBox;
        private System.Windows.Forms.Label desktopServerAddressLabel;
        private System.Windows.Forms.TextBox desktopServerPortTextBox;
        private System.Windows.Forms.Label desktopServerPortLabel;
        private System.Windows.Forms.TextBox desktopServerNameTextBox;
        private System.Windows.Forms.Label desktopServerNameLabel;
        private System.Windows.Forms.ComboBox desktopServerTypeComboBox;
        private System.Windows.Forms.Label desktopServerTypeLabel;
        private System.Windows.Forms.TextBox desktopServerIDTextBox;
        private System.Windows.Forms.Label desktopServerIDLabel;
        private System.Windows.Forms.Label desktopServerLabel;
        private System.Windows.Forms.Label hubServerPriorityLabel;
        private System.Windows.Forms.NumericUpDown hubServerPriorityNud;
        private System.Windows.Forms.TextBox hubServerAddressTextBox;
        private System.Windows.Forms.Label hubServerAddressLabel;
        private System.Windows.Forms.TextBox hubServerPortTextBox;
        private System.Windows.Forms.Label hubServerPortLabel;
        private System.Windows.Forms.TextBox hubServerNameTextBox;
        private System.Windows.Forms.Label hubServerNameLabel;
        private System.Windows.Forms.ComboBox hubServerTypeComboBox;
        private System.Windows.Forms.Label hubServerTypeLabel;
        private System.Windows.Forms.TextBox hubServerIDTextBox;
        private System.Windows.Forms.Label hubServerIDLabel;
        private System.Windows.Forms.Label hubServerLabel;
        private System.Windows.Forms.Panel ipcSplitPanel1;
        private System.Windows.Forms.CheckBox desktopStartingCheckBox;
        private System.Windows.Forms.CheckBox hubStartingCheckBox;
        private System.Windows.Forms.CheckBox hostStartingCheckBox;
        private System.Windows.Forms.Label serverPriorityLabel;
        private System.Windows.Forms.NumericUpDown serverPriorityNud;
        private System.Windows.Forms.TextBox serverAddressTextBox;
        private System.Windows.Forms.Label serverAddressLabel;
        private System.Windows.Forms.TextBox serverPortTextBox;
        private System.Windows.Forms.Label serverPortLabel;
        private System.Windows.Forms.TextBox serverNameTextBox;
        private System.Windows.Forms.Label serverNameLabel;
        private System.Windows.Forms.ComboBox serverTypeComboBox;
        private System.Windows.Forms.Label serverTypeLabel;
        private System.Windows.Forms.TextBox serverIDTextBox;
        private System.Windows.Forms.Label serverIDLabel;
        private System.Windows.Forms.Label alternativeServersLabel;
        private System.Windows.Forms.Button btnDelServer;
        private System.Windows.Forms.Button btnAddServer;
        private System.Windows.Forms.Button btnLastServer;
        private System.Windows.Forms.Button btnNextServer;
        private System.Windows.Forms.Button btnPrevServer;
        private System.Windows.Forms.Button btnFirstServer;
        private System.Windows.Forms.TabControl userManagementTabControl;
        private System.Windows.Forms.TabPage userPage;
        private System.Windows.Forms.TabPage authSystemsPage;
        private System.Windows.Forms.TabPage userGroupsPage;
        private System.Windows.Forms.TabPage computersPage;
        private System.Windows.Forms.TabControl userDetailsTabControl;
        private System.Windows.Forms.TabPage mainUsrInfoPage;
        private System.Windows.Forms.TabPage usrGroupsInfoPage;
        private System.Windows.Forms.TabPage usrPermissionsPage;
        private System.Windows.Forms.TabPage userPwdPage;
        private System.Windows.Forms.TabPage usrEduPage;
        private System.Windows.Forms.TabPage usrAccountsPage;
        private System.Windows.Forms.TabPage usrCheckParamsPage;
        private System.Windows.Forms.ImageList usersInfoImageList;
        private System.Windows.Forms.ImageList usersTabImageList;
        private System.Windows.Forms.DataGridViewTextBoxColumn computerNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn computerDescriptionColumn;
        private System.Windows.Forms.Label permissionTitleLabel;
        private System.Windows.Forms.Label novaUserAccessLabel;
        private System.Windows.Forms.Label generalUserTitleLabel;
        private System.Windows.Forms.Button resetPwdButton;
        private System.Windows.Forms.Label pwdResetTitleLabel;
        private System.Windows.Forms.Button changePwdSettingsButton;
        private System.Windows.Forms.Label pwdUserSettingsTitleLabel;
        private System.Windows.Forms.Panel checkParamTitlePanel;
        private System.Windows.Forms.Panel usrAccListTitlePanel;
        private System.Windows.Forms.Button userAccountsArchiveButton;
        private System.Windows.Forms.Button changeUserAccountButton;
        private System.Windows.Forms.Button userAccountGroupsButton;
        private System.Windows.Forms.DataGridViewComboBoxColumn authSystemTypeNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn accountUserNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn accountPasswordColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn passThruColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn lastSignInDateColumn;
        private System.Windows.Forms.DataGridView userGroupsDataGridView;
        private System.Windows.Forms.BindingNavigator groupsBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton65;
        private System.Windows.Forms.ToolStripLabel toolStripLabel13;
        private System.Windows.Forms.ToolStripButton toolStripButton67;
        private System.Windows.Forms.ToolStripButton toolStripButton68;
        private System.Windows.Forms.ToolStripButton toolStripButton69;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator38;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox13;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator39;
        private System.Windows.Forms.ToolStripButton toolStripButton70;
        private System.Windows.Forms.ToolStripButton toolStripButton71;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator43;
        private System.Windows.Forms.ToolStripButton groupsBindingNavigatorSaveItem;
        private System.Windows.Forms.ToolStripButton groupsBindingNavigatorRefreshItem;
        private System.Windows.Forms.DataGridView groupsDataGridView;
        private System.Windows.Forms.Panel groupDetailsPanel;
        private System.Windows.Forms.DataGridView groupPermissionsDataGridView;
        private System.Windows.Forms.GroupBox groupUsersGroupBox;
        private System.Windows.Forms.DataGridView usersGroupDataGridView;
        private System.Windows.Forms.Splitter splitter30;
        private System.Windows.Forms.GroupBox groupAuthSystemsGroupBox;
        private System.Windows.Forms.DataGridView groupGroupAuthSystemsDataGridView;
        private System.Windows.Forms.DataGridViewComboBoxColumn groupAuthSystemColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn authGroupNameColumn;
        private System.Windows.Forms.Splitter splitter27;
        private System.Windows.Forms.GroupBox groupPermissionsGroupBox;
        private System.Windows.Forms.Splitter splitter26;
        private System.Windows.Forms.GroupBox groupListGroupBox;
        private System.Windows.Forms.DataGridViewTextBoxColumn groupNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn groupDescriptionColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn userNameColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn userGroupNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn userGroupIDColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn userPermissionNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn userPermissionIDColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn groupUserNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn groupUserIDColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn groupPermissionsColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn groupPermissionIDColumn;
        private System.Windows.Forms.TabControl eduTabControl;
        private System.Windows.Forms.TabPage usrEduTabPage;
        private System.Windows.Forms.DataGridViewComboBoxColumn eduUserCategoryNameColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn eduRandomCategoryQuestionsColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn eduUserCategOrderColumn;
        private System.Windows.Forms.Splitter splitter12;
        private System.Windows.Forms.TabPage usrGroupEduTabPage;
        private System.Windows.Forms.ImageList eduImageList;
        private System.Windows.Forms.GroupBox eduUserGroupCategoriesGroupBox;
        private System.Windows.Forms.DataGridView eduUserGroupCategoriesDataGridView;
        private System.Windows.Forms.BindingNavigator eduUserGroupCategoriesBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton81;
        private System.Windows.Forms.ToolStripLabel toolStripLabel18;
        private System.Windows.Forms.ToolStripButton toolStripButton82;
        private System.Windows.Forms.ToolStripButton toolStripButton83;
        private System.Windows.Forms.ToolStripButton toolStripButton90;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator54;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox18;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator55;
        private System.Windows.Forms.ToolStripButton toolStripButton97;
        private System.Windows.Forms.ToolStripButton toolStripButton98;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator57;
        private System.Windows.Forms.ToolStripButton eduUserGroupCategoriesBindingNavigatorSaveItem;
        private System.Windows.Forms.ToolStripButton eduUserGroupCategoriesBindingNavigatorRefreshItem;
        private System.Windows.Forms.Splitter splitter31;
        private System.Windows.Forms.GroupBox eduUserGroupsGroupBox;
        private System.Windows.Forms.DataGridView eduUserGroupsDataGridView;
        private System.Windows.Forms.BindingNavigator eduUserGroupsBindingNavigator;
        private System.Windows.Forms.ToolStripLabel toolStripLabel15;
        private System.Windows.Forms.ToolStripButton toolStripButton72;
        private System.Windows.Forms.ToolStripButton toolStripButton78;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator45;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox15;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator46;
        private System.Windows.Forms.ToolStripButton toolStripButton79;
        private System.Windows.Forms.ToolStripButton toolStripButton80;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator53;
        private System.Windows.Forms.ToolStripButton eduUserGroupsBindingNavigatorRefreshIntem;
        private System.Windows.Forms.DataGridViewComboBoxColumn eduUserGroupCategoryNameColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn eduUserGroupRandomCategoryQuestionsColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn eduUserGroupCategOrderColumn;
        private System.Windows.Forms.TabControl notificationsTabControl;
        private System.Windows.Forms.TabPage userNotificationsTabPage;
        private System.Windows.Forms.Splitter splitter17;
        private System.Windows.Forms.TabPage userGroupNotificationsTabPage;
        private System.Windows.Forms.GroupBox userGroupNotificationGroupBox;
        private System.Windows.Forms.DataGridView userGroupNotificationDataGridView;
        private System.Windows.Forms.BindingNavigator userGroupsNotificationBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton104;
        private System.Windows.Forms.ToolStripLabel toolStripLabel20;
        private System.Windows.Forms.ToolStripButton toolStripButton105;
        private System.Windows.Forms.ToolStripButton toolStripButton106;
        private System.Windows.Forms.ToolStripButton toolStripButton107;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator61;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox20;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator62;
        private System.Windows.Forms.ToolStripButton toolStripButton108;
        private System.Windows.Forms.ToolStripButton toolStripButton109;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator63;
        private System.Windows.Forms.ToolStripButton userGroupNotificationBindingNavigatorSaveItem;
        private System.Windows.Forms.ToolStripButton userGroupNotificationBindingNavigatorRefreshItem;
        private System.Windows.Forms.Splitter splitter32;
        private System.Windows.Forms.GroupBox notificationUserGroupsGroupBox;
        private System.Windows.Forms.DataGridView notificationUserGroupsDataGridView;
        private System.Windows.Forms.BindingNavigator notificationUserGroupsBindingNavigator;
        private System.Windows.Forms.ToolStripLabel toolStripLabel19;
        private System.Windows.Forms.ToolStripButton toolStripButton99;
        private System.Windows.Forms.ToolStripButton toolStripButton100;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator58;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox19;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator59;
        private System.Windows.Forms.ToolStripButton toolStripButton101;
        private System.Windows.Forms.ToolStripButton toolStripButton102;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator60;
        private System.Windows.Forms.ToolStripButton notificationUserGroupsBindingNavigatorRefreshItem;
        private System.Windows.Forms.Panel groupReferencesPanel;
        private System.Windows.Forms.Button userGroupSettingsButton;
        private System.Windows.Forms.Button groupUsersButton;
        private System.Windows.Forms.TabControl revLinkTabControl;
        private System.Windows.Forms.TabPage revLinkUsersTabPage;
        private System.Windows.Forms.TabPage revLinkGroupsTabPage;
        private System.Windows.Forms.Button btnRefreshRevGroupsList;
        private System.Windows.Forms.ListView groupsListView;
        private System.Windows.Forms.ColumnHeader groupNameColumnHeader;
        private System.Windows.Forms.Button btnReverseGroupLink;
        private System.Windows.Forms.DataGridViewComboBoxColumn authSystemTypeColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn authSystemNameColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn onDeleteActionColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn onInsertActionColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn onUpdateActionColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn moveGroupUsersColumn;
        private System.Windows.Forms.NumericUpDown fixedSizeNumUpDown;
        private System.Windows.Forms.CheckBox fixedSizeCheckBox;
        private System.Windows.Forms.Label fixedSizeLabel;
        private System.Windows.Forms.Label postLoginSettingsLabel;
        private System.Windows.Forms.PictureBox postLoginSettingsPictureBox;
        private System.Windows.Forms.TabPage tabPostLoginSettings;
        private System.Windows.Forms.Button postLoginPathButton;
        private System.Windows.Forms.Label postLoginTimeLabel;
        private System.Windows.Forms.NumericUpDown postLoginPeriodNumUpDown;
        private System.Windows.Forms.CheckBox postLoginPeriodicCheckBox;
        private System.Windows.Forms.TextBox postLoginPathTextBox;
        private System.Windows.Forms.Label postLoginPathLabel;
        private System.Windows.Forms.Button btnPostLoginSettingsSave;
        private System.Windows.Forms.Label lblPostLoginSettings;
        private System.Windows.Forms.OpenFileDialog postLoginOpenFileDialog;
        private System.Windows.Forms.Panel eduEditorPanel;
        private System.Windows.Forms.Splitter splitter8;
        private System.Windows.Forms.Panel eduButtonsBottomPanel;
        private System.Windows.Forms.Button eduImportFromDBButton;
        private System.Windows.Forms.TabPage scheduleTabPage;
        private System.Windows.Forms.SplitContainer scheduleSplitContainer;
        private System.Windows.Forms.DataGridView controlledProgramsDataGridView;
        private System.Windows.Forms.BindingNavigator controlledProgramsBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton103;
        private System.Windows.Forms.ToolStripLabel toolStripLabel21;
        private System.Windows.Forms.ToolStripButton toolStripButton110;
        private System.Windows.Forms.ToolStripButton toolStripButton111;
        private System.Windows.Forms.ToolStripButton toolStripButton112;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator64;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox21;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator65;
        private System.Windows.Forms.ToolStripButton toolStripButton113;
        private System.Windows.Forms.ToolStripButton toolStripButton114;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator66;
        private System.Windows.Forms.ToolStripButton controlledProgramsBindingNavigatorSaveItem;
        private System.Windows.Forms.ToolStripButton controlledProgramsBindingNavigatorRefreshItem;
        private System.Windows.Forms.DataGridView scheduleDataGridView;
        private System.Windows.Forms.BindingNavigator scheduleBindingNavigator;
        private System.Windows.Forms.ToolStripButton toolStripButton115;
        private System.Windows.Forms.ToolStripLabel toolStripLabel22;
        private System.Windows.Forms.ToolStripButton toolStripButton116;
        private System.Windows.Forms.ToolStripButton toolStripButton117;
        private System.Windows.Forms.ToolStripButton toolStripButton118;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator67;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox22;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator68;
        private System.Windows.Forms.ToolStripButton toolStripButton119;
        private System.Windows.Forms.ToolStripButton toolStripButton120;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator69;
        private System.Windows.Forms.ToolStripButton scheduleBindingNavigatorSaveItem;
        private System.Windows.Forms.ToolStripButton scheduleBindingNavigatorRefreshItem;
        private System.Windows.Forms.TabPage tabProgramsControlSettings;
        private System.Windows.Forms.CheckBox chbProgramsControlEnabled;
        private System.Windows.Forms.Button btnProgramsControlSettingsSave;
        private System.Windows.Forms.Label lblProgramsControlSettings;
        private System.Windows.Forms.Label programsControlSettingsLabel;
        private System.Windows.Forms.PictureBox programsControlSettingsPictureBox;
        private System.Windows.Forms.Label globalServerPriorityLabel;
        private System.Windows.Forms.NumericUpDown globalServerPriorityNud;
        private System.Windows.Forms.TextBox globalServerAddressTextBox;
        private System.Windows.Forms.Label globalServerAddressLabel;
        private System.Windows.Forms.TextBox globalServerPortTextBox;
        private System.Windows.Forms.Label globalServerPortLabel;
        private System.Windows.Forms.TextBox globalServerNameTextBox;
        private System.Windows.Forms.Label globalServerNameLabel;
        private System.Windows.Forms.ComboBox globalServerTypeComboBox;
        private System.Windows.Forms.Label globalServerTypeLabel;
        private System.Windows.Forms.TextBox globalServerIDTextBox;
        private System.Windows.Forms.Label globalServerIDLabel;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TabPage tabCommandsHistory;
        private System.Windows.Forms.Button commandsHistoryPathButton;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown commandsHistoryPeriodNumUpDown;
        private System.Windows.Forms.CheckBox commandsHistoryPeriodCheckBox;
        private System.Windows.Forms.TextBox commandsHistoryPathTextBox;
        private System.Windows.Forms.Label lblCommandsHistoryPath;
        private System.Windows.Forms.Button btnCommandsHistorySettingsSave;
        private System.Windows.Forms.Label lblCommandsHistorySettings;
        private System.Windows.Forms.CheckBox snapshotCheckBox;
        private System.Windows.Forms.CheckBox screenshotCheckBox;
        private System.Windows.Forms.CheckBox currentUserNameCheckBox;
        private System.Windows.Forms.CheckBox userEnviromentCheckBox;
        private System.Windows.Forms.Label commandsHistorySettingsLabel;
        private System.Windows.Forms.PictureBox commandsHistorySettingsPictureBox;
        private System.Windows.Forms.OpenFileDialog commandHistoryOpenFileDialog;
        private System.Windows.Forms.Label fileTransferLabel;
        private System.Windows.Forms.PictureBox fileTransferPictureBox;
        private System.Windows.Forms.TabPage tabFileTransferSettings;
        private System.Windows.Forms.Button tempDirectoryButton;
        private System.Windows.Forms.TextBox tempDirectoryTextBox;
        private System.Windows.Forms.Label lblTempDirectory;
        private System.Windows.Forms.Button downloadDirectoryButton;
        private System.Windows.Forms.TextBox downloadDirectoryTextBox;
        private System.Windows.Forms.Label lblDownloadDirectory;
        private System.Windows.Forms.Button uploadDirectoryButton;
        private System.Windows.Forms.TextBox uploadDirectoryTextBox;
        private System.Windows.Forms.Label lblUploadDirectory;
        private System.Windows.Forms.Button btnFileTransferSettings;
        private System.Windows.Forms.Label lblFileTransferSettings;
        private System.Windows.Forms.FolderBrowserDialog directoriesBrowserDialog;
        private System.Windows.Forms.TabPage tabUpdateSettings;
        private System.Windows.Forms.Button btnUpdateSettingsSave;
        private System.Windows.Forms.Label lblUpdateSettings;
        private System.Windows.Forms.Label lblUpdateHours;
        private System.Windows.Forms.NumericUpDown updatesPeriodNumericUpDown;
        private System.Windows.Forms.CheckBox updatesEnableCheckBox;
        private System.Windows.Forms.Button updaterPathButton;
        private System.Windows.Forms.TextBox updaterPathTextBox;
        private System.Windows.Forms.Label lblUpdaterPath;
        private System.Windows.Forms.Label updateSettingsLabel;
        private System.Windows.Forms.PictureBox updateSettingsPictureBox;
        private System.Windows.Forms.OpenFileDialog openUpdaterFileDialog;
        private System.Windows.Forms.Button updateDirPathButton;
        private System.Windows.Forms.TextBox updateDirPathTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.FolderBrowserDialog updateDirBrowserDialog;
        private System.Windows.Forms.Button btnAddLicInfoRecord;
        private System.Windows.Forms.Panel licensePointsPanel;
        private System.Windows.Forms.Panel licenseBottomPanel;
        private System.Windows.Forms.Button btnClearLicenseInfo;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator70;
        private System.Windows.Forms.ToolStripButton scheduleConditionBuilderItem;
        private System.Windows.Forms.DataGridViewTextBoxColumn controlledProgramNameColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn controlledProgramAllowedColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn scheduleUserIDColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn scheduleGroupIDColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn scheduleUserNameColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn scheduleGroupNameColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn scheduleComputerNameColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn scheduleProgramNameColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn scheduleFunctionNameColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn scheduleActionNameColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn scheduleIncrementValuesColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn scheduleConditionStringColumn;
        private System.Windows.Forms.SplitContainer presetSplitContainer;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.TabControl screenObjectValuesTabControl;
        private System.Windows.Forms.TabPage tabScreenObjectText;
        private System.Windows.Forms.TabPage tabScreenObjectImage;
        private System.Windows.Forms.TabPage tabScreenObjectListValues;
        private System.Windows.Forms.DataGridViewTextBoxColumn screenObjectListValuesColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn userGroupNotificationNoticeTextColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn userGroupNotificationDisplayTypeColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn notificationGroupNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn notificationGroupDescriptionColumn;
        private System.Windows.Forms.SplitContainer noticeValuesSplitContainer;
        private System.Windows.Forms.SplitContainer userNotificationSplitContainer;
        private System.Windows.Forms.DataGridViewComboBoxColumn userNotificationNoticeTextColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn userNotificationDisplayTypeColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn userNotificationHistoryNoticeTextColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn userNotificationHistoryDateColumn;
        private System.Windows.Forms.ImageList screenObjValuesImageList;
        private System.Windows.Forms.SplitContainer userEducationSplitContainer;
        private System.Windows.Forms.DataGridViewTextBoxColumn eduGroupNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn eduGroupDescriptionColumn;
        private System.Windows.Forms.TabControl eduLessonsTabControl;
        private System.Windows.Forms.TabPage tabLessons;
        private System.Windows.Forms.SplitContainer eduLessonSplitContainer;
        private System.Windows.Forms.TabPage tabQuestions;
        private System.Windows.Forms.TabPage tabAnswers;
        private System.Windows.Forms.SplitContainer eduQuestionSplitContainer;
        private System.Windows.Forms.Panel eduQuestionTextPanel;
        private System.Windows.Forms.Button eduQuestionTextClearButton;
        private System.Windows.Forms.RichTextBox eduQuestionRichTextBox;
        private System.Windows.Forms.Button eduQuestionTextOpenButton;
        private System.Windows.Forms.Panel questionOrderPanel;
        private System.Windows.Forms.ComboBox rightAnswerComboBox;
        private System.Windows.Forms.TextBox eduQuestionOrderTextBox;
        private System.Windows.Forms.BindingNavigator eduQuestionsBindingNavigator;
        private System.Windows.Forms.ToolStripButton eduQuestionsBindingNavigatorAddNewItem;
        private System.Windows.Forms.ToolStripLabel toolStripLabel5;
        private System.Windows.Forms.ToolStripButton eduQuestionsBindingNavigatorRemoveItem;
        private System.Windows.Forms.ToolStripButton toolStripButton27;
        private System.Windows.Forms.ToolStripButton toolStripButton28;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator13;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox5;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator14;
        private System.Windows.Forms.ToolStripButton toolStripButton29;
        private System.Windows.Forms.ToolStripButton toolStripButton30;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator15;
        private System.Windows.Forms.ToolStripButton eduQuestionsBindingNavigatorSaveItem;
        private System.Windows.Forms.ToolStripButton eduQuestionsBindingNavigatorRefreshItem;
        private System.Windows.Forms.DataGridView eduAnswersDataGridView;
        private System.Windows.Forms.DataGridViewComboBoxColumn eduQuestionAnswerTextColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn eduQuestionAnswerOrderColumn;
        private System.Windows.Forms.BindingNavigator eduAnswersBindingNavigator;
        private System.Windows.Forms.ToolStripButton eduAnswersBindingNavigatorAddItem;
        private System.Windows.Forms.ToolStripLabel toolStripLabel23;
        private System.Windows.Forms.ToolStripButton eduAnswersBindingNavigatorRemoveItem;
        private System.Windows.Forms.ToolStripButton toolStripButton123;
        private System.Windows.Forms.ToolStripButton toolStripButton124;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator71;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox23;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator72;
        private System.Windows.Forms.ToolStripButton toolStripButton125;
        private System.Windows.Forms.ToolStripButton toolStripButton126;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator73;
        private System.Windows.Forms.ToolStripButton eduAnswersBindingNavigatorSaveItem;
        private System.Windows.Forms.ToolStripButton eduAnswersBindingNavigatorRefreshItem;
        private System.Windows.Forms.DataGridView generalAnswersListDataGridView;
        private System.Windows.Forms.DataGridViewTextBoxColumn eduGeneralAnswerTextColumn;
        private System.Windows.Forms.BindingNavigator eduAllAnswersBindingNavigator;
        private System.Windows.Forms.ToolStripButton eduAllAnswersBindingNavigatorAddItem;
        private System.Windows.Forms.ToolStripLabel toolStripLabel24;
        private System.Windows.Forms.ToolStripButton eduAllAnswersBindingNavigatorRemoveItem;
        private System.Windows.Forms.ToolStripButton toolStripButton131;
        private System.Windows.Forms.ToolStripButton toolStripButton132;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator74;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox24;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator75;
        private System.Windows.Forms.ToolStripButton toolStripButton133;
        private System.Windows.Forms.ToolStripButton toolStripButton134;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator76;
        private System.Windows.Forms.ToolStripButton eduAllAnswersBindingNavigatorSaveItem;
        private System.Windows.Forms.ToolStripButton eduAllAnswersBindingNavigatorRefreshItem;
        private System.Windows.Forms.ImageList eduLessonsImageList;
    }
}

