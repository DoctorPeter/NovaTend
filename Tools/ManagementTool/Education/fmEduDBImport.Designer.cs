namespace ManagementTool
{
    partial class fmEduDBImport
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fmEduDBImport));
            this.mainTabControl = new System.Windows.Forms.TabControl();
            this.eduCategTabPage = new System.Windows.Forms.TabPage();
            this.eduLessonsTabPage = new System.Windows.Forms.TabPage();
            this.eduQuestTabPage = new System.Windows.Forms.TabPage();
            this.eduAnswersTabPage = new System.Windows.Forms.TabPage();
            this.eduImageList = new System.Windows.Forms.ImageList(this.components);
            this.bottomPanel = new System.Windows.Forms.Panel();
            this.closeButton = new System.Windows.Forms.Button();
            this.importButton = new System.Windows.Forms.Button();
            this.lblEduCategConnectionString = new System.Windows.Forms.Label();
            this.eduCategConStrTextBox = new System.Windows.Forms.TextBox();
            this.lblEduCategTableName = new System.Windows.Forms.Label();
            this.eduCategTableNameTextBox = new System.Windows.Forms.TextBox();
            this.eduCategColumnNameTextBox = new System.Windows.Forms.TextBox();
            this.lblEduCategColumnName = new System.Windows.Forms.Label();
            this.eduCategAddCondTextBox = new System.Windows.Forms.TextBox();
            this.lblEduCategAdditionalConditions = new System.Windows.Forms.Label();
            this.lblEduLessonsCategoryID = new System.Windows.Forms.Label();
            this.eduLessonCategIDComboBox = new System.Windows.Forms.ComboBox();
            this.eduLessonAddCondTextBox = new System.Windows.Forms.TextBox();
            this.lblEduLessonAdditionalConditions = new System.Windows.Forms.Label();
            this.eduLessonColumnNameTextBox = new System.Windows.Forms.TextBox();
            this.lblEduLessonColumnName = new System.Windows.Forms.Label();
            this.eduLessonTableNameTextBox = new System.Windows.Forms.TextBox();
            this.lblEduLessonTableName = new System.Windows.Forms.Label();
            this.eduLessonConStrTextBox = new System.Windows.Forms.TextBox();
            this.lblEduLessonConnectionString = new System.Windows.Forms.Label();
            this.eduQuestLessonIDComboBox = new System.Windows.Forms.ComboBox();
            this.lblEduQuestLessonID = new System.Windows.Forms.Label();
            this.eduQuestRightAnswerIDComboBox = new System.Windows.Forms.ComboBox();
            this.lblEduQuestRightAnswerID = new System.Windows.Forms.Label();
            this.eduQuestAddCondTextBox = new System.Windows.Forms.TextBox();
            this.lblEquQuestAddCond = new System.Windows.Forms.Label();
            this.eduQuestColumnNameTextBox = new System.Windows.Forms.TextBox();
            this.lblEduQuestColumnName = new System.Windows.Forms.Label();
            this.eduQuestTableNameTextBox = new System.Windows.Forms.TextBox();
            this.lblEduQuestTableName = new System.Windows.Forms.Label();
            this.eduQuestConStrTextBox = new System.Windows.Forms.TextBox();
            this.lblEduQuestConStr = new System.Windows.Forms.Label();
            this.lblEduQuestNOTE = new System.Windows.Forms.Label();
            this.eduAnswersAddCondTextBox = new System.Windows.Forms.TextBox();
            this.lblEduAnswersAddCond = new System.Windows.Forms.Label();
            this.eduAnswersColumnNameTextBox = new System.Windows.Forms.TextBox();
            this.lblEduAnswersColumnName = new System.Windows.Forms.Label();
            this.eduAnswersTableNameTextBox = new System.Windows.Forms.TextBox();
            this.lblEduAnswersTableName = new System.Windows.Forms.Label();
            this.eduAnswersConStrTextBox = new System.Windows.Forms.TextBox();
            this.lblEduAnswersConStr = new System.Windows.Forms.Label();
            this.eduAnswersQuestIDComboBox = new System.Windows.Forms.ComboBox();
            this.lblEduAnswersQuestID = new System.Windows.Forms.Label();
            this.eduLessonImageColumnNameTextBox = new System.Windows.Forms.TextBox();
            this.lblEduLessonImageColumnName = new System.Windows.Forms.Label();
            this.mainTabControl.SuspendLayout();
            this.eduCategTabPage.SuspendLayout();
            this.eduLessonsTabPage.SuspendLayout();
            this.eduQuestTabPage.SuspendLayout();
            this.eduAnswersTabPage.SuspendLayout();
            this.bottomPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainTabControl
            // 
            this.mainTabControl.Controls.Add(this.eduCategTabPage);
            this.mainTabControl.Controls.Add(this.eduLessonsTabPage);
            this.mainTabControl.Controls.Add(this.eduQuestTabPage);
            this.mainTabControl.Controls.Add(this.eduAnswersTabPage);
            this.mainTabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainTabControl.ImageList = this.eduImageList;
            this.mainTabControl.Location = new System.Drawing.Point(0, 0);
            this.mainTabControl.Name = "mainTabControl";
            this.mainTabControl.SelectedIndex = 0;
            this.mainTabControl.Size = new System.Drawing.Size(649, 323);
            this.mainTabControl.TabIndex = 0;
            // 
            // eduCategTabPage
            // 
            this.eduCategTabPage.Controls.Add(this.eduCategAddCondTextBox);
            this.eduCategTabPage.Controls.Add(this.lblEduCategAdditionalConditions);
            this.eduCategTabPage.Controls.Add(this.eduCategColumnNameTextBox);
            this.eduCategTabPage.Controls.Add(this.lblEduCategColumnName);
            this.eduCategTabPage.Controls.Add(this.eduCategTableNameTextBox);
            this.eduCategTabPage.Controls.Add(this.lblEduCategTableName);
            this.eduCategTabPage.Controls.Add(this.eduCategConStrTextBox);
            this.eduCategTabPage.Controls.Add(this.lblEduCategConnectionString);
            this.eduCategTabPage.ImageIndex = 0;
            this.eduCategTabPage.Location = new System.Drawing.Point(4, 31);
            this.eduCategTabPage.Name = "eduCategTabPage";
            this.eduCategTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.eduCategTabPage.Size = new System.Drawing.Size(641, 288);
            this.eduCategTabPage.TabIndex = 0;
            this.eduCategTabPage.Text = "Categories";
            this.eduCategTabPage.UseVisualStyleBackColor = true;
            // 
            // eduLessonsTabPage
            // 
            this.eduLessonsTabPage.Controls.Add(this.eduLessonImageColumnNameTextBox);
            this.eduLessonsTabPage.Controls.Add(this.lblEduLessonImageColumnName);
            this.eduLessonsTabPage.Controls.Add(this.eduLessonAddCondTextBox);
            this.eduLessonsTabPage.Controls.Add(this.lblEduLessonAdditionalConditions);
            this.eduLessonsTabPage.Controls.Add(this.eduLessonColumnNameTextBox);
            this.eduLessonsTabPage.Controls.Add(this.lblEduLessonColumnName);
            this.eduLessonsTabPage.Controls.Add(this.eduLessonTableNameTextBox);
            this.eduLessonsTabPage.Controls.Add(this.lblEduLessonTableName);
            this.eduLessonsTabPage.Controls.Add(this.eduLessonConStrTextBox);
            this.eduLessonsTabPage.Controls.Add(this.lblEduLessonConnectionString);
            this.eduLessonsTabPage.Controls.Add(this.eduLessonCategIDComboBox);
            this.eduLessonsTabPage.Controls.Add(this.lblEduLessonsCategoryID);
            this.eduLessonsTabPage.ImageIndex = 1;
            this.eduLessonsTabPage.Location = new System.Drawing.Point(4, 31);
            this.eduLessonsTabPage.Name = "eduLessonsTabPage";
            this.eduLessonsTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.eduLessonsTabPage.Size = new System.Drawing.Size(641, 288);
            this.eduLessonsTabPage.TabIndex = 1;
            this.eduLessonsTabPage.Text = "Lessons";
            this.eduLessonsTabPage.UseVisualStyleBackColor = true;
            // 
            // eduQuestTabPage
            // 
            this.eduQuestTabPage.Controls.Add(this.lblEduQuestNOTE);
            this.eduQuestTabPage.Controls.Add(this.eduQuestAddCondTextBox);
            this.eduQuestTabPage.Controls.Add(this.lblEquQuestAddCond);
            this.eduQuestTabPage.Controls.Add(this.eduQuestColumnNameTextBox);
            this.eduQuestTabPage.Controls.Add(this.lblEduQuestColumnName);
            this.eduQuestTabPage.Controls.Add(this.eduQuestTableNameTextBox);
            this.eduQuestTabPage.Controls.Add(this.lblEduQuestTableName);
            this.eduQuestTabPage.Controls.Add(this.eduQuestConStrTextBox);
            this.eduQuestTabPage.Controls.Add(this.lblEduQuestConStr);
            this.eduQuestTabPage.Controls.Add(this.eduQuestRightAnswerIDComboBox);
            this.eduQuestTabPage.Controls.Add(this.lblEduQuestRightAnswerID);
            this.eduQuestTabPage.Controls.Add(this.eduQuestLessonIDComboBox);
            this.eduQuestTabPage.Controls.Add(this.lblEduQuestLessonID);
            this.eduQuestTabPage.ImageIndex = 2;
            this.eduQuestTabPage.Location = new System.Drawing.Point(4, 31);
            this.eduQuestTabPage.Name = "eduQuestTabPage";
            this.eduQuestTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.eduQuestTabPage.Size = new System.Drawing.Size(641, 288);
            this.eduQuestTabPage.TabIndex = 2;
            this.eduQuestTabPage.Text = "Questions";
            this.eduQuestTabPage.UseVisualStyleBackColor = true;
            // 
            // eduAnswersTabPage
            // 
            this.eduAnswersTabPage.Controls.Add(this.eduAnswersAddCondTextBox);
            this.eduAnswersTabPage.Controls.Add(this.lblEduAnswersAddCond);
            this.eduAnswersTabPage.Controls.Add(this.eduAnswersColumnNameTextBox);
            this.eduAnswersTabPage.Controls.Add(this.lblEduAnswersColumnName);
            this.eduAnswersTabPage.Controls.Add(this.eduAnswersTableNameTextBox);
            this.eduAnswersTabPage.Controls.Add(this.lblEduAnswersTableName);
            this.eduAnswersTabPage.Controls.Add(this.eduAnswersConStrTextBox);
            this.eduAnswersTabPage.Controls.Add(this.lblEduAnswersConStr);
            this.eduAnswersTabPage.Controls.Add(this.eduAnswersQuestIDComboBox);
            this.eduAnswersTabPage.Controls.Add(this.lblEduAnswersQuestID);
            this.eduAnswersTabPage.ImageIndex = 3;
            this.eduAnswersTabPage.Location = new System.Drawing.Point(4, 31);
            this.eduAnswersTabPage.Name = "eduAnswersTabPage";
            this.eduAnswersTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.eduAnswersTabPage.Size = new System.Drawing.Size(641, 288);
            this.eduAnswersTabPage.TabIndex = 3;
            this.eduAnswersTabPage.Text = "Answers";
            this.eduAnswersTabPage.UseVisualStyleBackColor = true;
            // 
            // eduImageList
            // 
            this.eduImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("eduImageList.ImageStream")));
            this.eduImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.eduImageList.Images.SetKeyName(0, "adreess book.png");
            this.eduImageList.Images.SetKeyName(1, "book_24.png");
            this.eduImageList.Images.SetKeyName(2, "unknow.png");
            this.eduImageList.Images.SetKeyName(3, "documents_preferences.png");
            this.eduImageList.Images.SetKeyName(4, "book_blue.png");
            // 
            // bottomPanel
            // 
            this.bottomPanel.Controls.Add(this.importButton);
            this.bottomPanel.Controls.Add(this.closeButton);
            this.bottomPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.bottomPanel.Location = new System.Drawing.Point(0, 323);
            this.bottomPanel.Name = "bottomPanel";
            this.bottomPanel.Size = new System.Drawing.Size(649, 57);
            this.bottomPanel.TabIndex = 1;
            // 
            // closeButton
            // 
            this.closeButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.closeButton.Image = ((System.Drawing.Image)(resources.GetObject("closeButton.Image")));
            this.closeButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.closeButton.Location = new System.Drawing.Point(512, 7);
            this.closeButton.Name = "closeButton";
            this.closeButton.Size = new System.Drawing.Size(128, 42);
            this.closeButton.TabIndex = 0;
            this.closeButton.Text = "Close";
            this.closeButton.UseVisualStyleBackColor = true;
            this.closeButton.Click += new System.EventHandler(this.closeButton_Click);
            // 
            // importButton
            // 
            this.importButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.importButton.Image = ((System.Drawing.Image)(resources.GetObject("importButton.Image")));
            this.importButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.importButton.Location = new System.Drawing.Point(378, 7);
            this.importButton.Name = "importButton";
            this.importButton.Size = new System.Drawing.Size(128, 42);
            this.importButton.TabIndex = 1;
            this.importButton.Text = "Import";
            this.importButton.UseVisualStyleBackColor = true;
            this.importButton.Click += new System.EventHandler(this.importButton_Click);
            // 
            // lblEduCategConnectionString
            // 
            this.lblEduCategConnectionString.AutoSize = true;
            this.lblEduCategConnectionString.Location = new System.Drawing.Point(13, 44);
            this.lblEduCategConnectionString.Name = "lblEduCategConnectionString";
            this.lblEduCategConnectionString.Size = new System.Drawing.Size(92, 13);
            this.lblEduCategConnectionString.TabIndex = 0;
            this.lblEduCategConnectionString.Text = "Connection string:";
            // 
            // eduCategConStrTextBox
            // 
            this.eduCategConStrTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduCategConStrTextBox.Location = new System.Drawing.Point(112, 42);
            this.eduCategConStrTextBox.Name = "eduCategConStrTextBox";
            this.eduCategConStrTextBox.Size = new System.Drawing.Size(514, 20);
            this.eduCategConStrTextBox.TabIndex = 1;
            // 
            // lblEduCategTableName
            // 
            this.lblEduCategTableName.AutoSize = true;
            this.lblEduCategTableName.Location = new System.Drawing.Point(13, 100);
            this.lblEduCategTableName.Name = "lblEduCategTableName";
            this.lblEduCategTableName.Size = new System.Drawing.Size(240, 13);
            this.lblEduCategTableName.TabIndex = 2;
            this.lblEduCategTableName.Text = "Enter name of table with the names of categories:";
            // 
            // eduCategTableNameTextBox
            // 
            this.eduCategTableNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduCategTableNameTextBox.Location = new System.Drawing.Point(270, 96);
            this.eduCategTableNameTextBox.Name = "eduCategTableNameTextBox";
            this.eduCategTableNameTextBox.Size = new System.Drawing.Size(356, 20);
            this.eduCategTableNameTextBox.TabIndex = 3;
            // 
            // eduCategColumnNameTextBox
            // 
            this.eduCategColumnNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduCategColumnNameTextBox.Location = new System.Drawing.Point(270, 143);
            this.eduCategColumnNameTextBox.Name = "eduCategColumnNameTextBox";
            this.eduCategColumnNameTextBox.Size = new System.Drawing.Size(356, 20);
            this.eduCategColumnNameTextBox.TabIndex = 5;
            // 
            // lblEduCategColumnName
            // 
            this.lblEduCategColumnName.AutoSize = true;
            this.lblEduCategColumnName.Location = new System.Drawing.Point(13, 147);
            this.lblEduCategColumnName.Name = "lblEduCategColumnName";
            this.lblEduCategColumnName.Size = new System.Drawing.Size(251, 13);
            this.lblEduCategColumnName.TabIndex = 4;
            this.lblEduCategColumnName.Text = "Enter name of column with the names of categories:";
            // 
            // eduCategAddCondTextBox
            // 
            this.eduCategAddCondTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduCategAddCondTextBox.Location = new System.Drawing.Point(216, 194);
            this.eduCategAddCondTextBox.Name = "eduCategAddCondTextBox";
            this.eduCategAddCondTextBox.Size = new System.Drawing.Size(410, 20);
            this.eduCategAddCondTextBox.TabIndex = 7;
            // 
            // lblEduCategAdditionalConditions
            // 
            this.lblEduCategAdditionalConditions.AutoSize = true;
            this.lblEduCategAdditionalConditions.Location = new System.Drawing.Point(13, 198);
            this.lblEduCategAdditionalConditions.Name = "lblEduCategAdditionalConditions";
            this.lblEduCategAdditionalConditions.Size = new System.Drawing.Size(197, 13);
            this.lblEduCategAdditionalConditions.TabIndex = 6;
            this.lblEduCategAdditionalConditions.Text = "Enter the additional selection conditions:";
            // 
            // lblEduLessonsCategoryID
            // 
            this.lblEduLessonsCategoryID.AutoSize = true;
            this.lblEduLessonsCategoryID.Location = new System.Drawing.Point(13, 37);
            this.lblEduLessonsCategoryID.Name = "lblEduLessonsCategoryID";
            this.lblEduLessonsCategoryID.Size = new System.Drawing.Size(90, 13);
            this.lblEduLessonsCategoryID.TabIndex = 0;
            this.lblEduLessonsCategoryID.Text = "Choose category:";
            // 
            // eduLessonCategIDComboBox
            // 
            this.eduLessonCategIDComboBox.FormattingEnabled = true;
            this.eduLessonCategIDComboBox.Location = new System.Drawing.Point(112, 34);
            this.eduLessonCategIDComboBox.Name = "eduLessonCategIDComboBox";
            this.eduLessonCategIDComboBox.Size = new System.Drawing.Size(514, 21);
            this.eduLessonCategIDComboBox.TabIndex = 1;
            // 
            // eduLessonAddCondTextBox
            // 
            this.eduLessonAddCondTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduLessonAddCondTextBox.Location = new System.Drawing.Point(216, 236);
            this.eduLessonAddCondTextBox.Name = "eduLessonAddCondTextBox";
            this.eduLessonAddCondTextBox.Size = new System.Drawing.Size(410, 20);
            this.eduLessonAddCondTextBox.TabIndex = 15;
            // 
            // lblEduLessonAdditionalConditions
            // 
            this.lblEduLessonAdditionalConditions.AutoSize = true;
            this.lblEduLessonAdditionalConditions.Location = new System.Drawing.Point(13, 240);
            this.lblEduLessonAdditionalConditions.Name = "lblEduLessonAdditionalConditions";
            this.lblEduLessonAdditionalConditions.Size = new System.Drawing.Size(197, 13);
            this.lblEduLessonAdditionalConditions.TabIndex = 14;
            this.lblEduLessonAdditionalConditions.Text = "Enter the additional selection conditions:";
            // 
            // eduLessonColumnNameTextBox
            // 
            this.eduLessonColumnNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduLessonColumnNameTextBox.Location = new System.Drawing.Point(258, 158);
            this.eduLessonColumnNameTextBox.Name = "eduLessonColumnNameTextBox";
            this.eduLessonColumnNameTextBox.Size = new System.Drawing.Size(368, 20);
            this.eduLessonColumnNameTextBox.TabIndex = 13;
            // 
            // lblEduLessonColumnName
            // 
            this.lblEduLessonColumnName.AutoSize = true;
            this.lblEduLessonColumnName.Location = new System.Drawing.Point(13, 162);
            this.lblEduLessonColumnName.Name = "lblEduLessonColumnName";
            this.lblEduLessonColumnName.Size = new System.Drawing.Size(223, 13);
            this.lblEduLessonColumnName.TabIndex = 12;
            this.lblEduLessonColumnName.Text = "Enter name of column with text of the lessons:";
            // 
            // eduLessonTableNameTextBox
            // 
            this.eduLessonTableNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduLessonTableNameTextBox.Location = new System.Drawing.Point(242, 118);
            this.eduLessonTableNameTextBox.Name = "eduLessonTableNameTextBox";
            this.eduLessonTableNameTextBox.Size = new System.Drawing.Size(384, 20);
            this.eduLessonTableNameTextBox.TabIndex = 11;
            // 
            // lblEduLessonTableName
            // 
            this.lblEduLessonTableName.AutoSize = true;
            this.lblEduLessonTableName.Location = new System.Drawing.Point(13, 122);
            this.lblEduLessonTableName.Name = "lblEduLessonTableName";
            this.lblEduLessonTableName.Size = new System.Drawing.Size(212, 13);
            this.lblEduLessonTableName.TabIndex = 10;
            this.lblEduLessonTableName.Text = "Enter name of table with text of the lessons:";
            // 
            // eduLessonConStrTextBox
            // 
            this.eduLessonConStrTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduLessonConStrTextBox.Location = new System.Drawing.Point(112, 73);
            this.eduLessonConStrTextBox.Name = "eduLessonConStrTextBox";
            this.eduLessonConStrTextBox.Size = new System.Drawing.Size(514, 20);
            this.eduLessonConStrTextBox.TabIndex = 9;
            // 
            // lblEduLessonConnectionString
            // 
            this.lblEduLessonConnectionString.AutoSize = true;
            this.lblEduLessonConnectionString.Location = new System.Drawing.Point(13, 75);
            this.lblEduLessonConnectionString.Name = "lblEduLessonConnectionString";
            this.lblEduLessonConnectionString.Size = new System.Drawing.Size(92, 13);
            this.lblEduLessonConnectionString.TabIndex = 8;
            this.lblEduLessonConnectionString.Text = "Connection string:";
            // 
            // eduQuestLessonIDComboBox
            // 
            this.eduQuestLessonIDComboBox.FormattingEnabled = true;
            this.eduQuestLessonIDComboBox.Location = new System.Drawing.Point(123, 17);
            this.eduQuestLessonIDComboBox.Name = "eduQuestLessonIDComboBox";
            this.eduQuestLessonIDComboBox.Size = new System.Drawing.Size(501, 21);
            this.eduQuestLessonIDComboBox.TabIndex = 3;
            // 
            // lblEduQuestLessonID
            // 
            this.lblEduQuestLessonID.AutoSize = true;
            this.lblEduQuestLessonID.Location = new System.Drawing.Point(11, 20);
            this.lblEduQuestLessonID.Name = "lblEduQuestLessonID";
            this.lblEduQuestLessonID.Size = new System.Drawing.Size(79, 13);
            this.lblEduQuestLessonID.TabIndex = 2;
            this.lblEduQuestLessonID.Text = "Choose lesson:";
            // 
            // eduQuestRightAnswerIDComboBox
            // 
            this.eduQuestRightAnswerIDComboBox.FormattingEnabled = true;
            this.eduQuestRightAnswerIDComboBox.Location = new System.Drawing.Point(123, 53);
            this.eduQuestRightAnswerIDComboBox.Name = "eduQuestRightAnswerIDComboBox";
            this.eduQuestRightAnswerIDComboBox.Size = new System.Drawing.Size(501, 21);
            this.eduQuestRightAnswerIDComboBox.TabIndex = 5;
            // 
            // lblEduQuestRightAnswerID
            // 
            this.lblEduQuestRightAnswerID.AutoSize = true;
            this.lblEduQuestRightAnswerID.Location = new System.Drawing.Point(11, 56);
            this.lblEduQuestRightAnswerID.Name = "lblEduQuestRightAnswerID";
            this.lblEduQuestRightAnswerID.Size = new System.Drawing.Size(106, 13);
            this.lblEduQuestRightAnswerID.TabIndex = 4;
            this.lblEduQuestRightAnswerID.Text = "Choose right answer:";
            // 
            // eduQuestAddCondTextBox
            // 
            this.eduQuestAddCondTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduQuestAddCondTextBox.Location = new System.Drawing.Point(214, 190);
            this.eduQuestAddCondTextBox.Name = "eduQuestAddCondTextBox";
            this.eduQuestAddCondTextBox.Size = new System.Drawing.Size(410, 20);
            this.eduQuestAddCondTextBox.TabIndex = 23;
            // 
            // lblEquQuestAddCond
            // 
            this.lblEquQuestAddCond.AutoSize = true;
            this.lblEquQuestAddCond.Location = new System.Drawing.Point(11, 194);
            this.lblEquQuestAddCond.Name = "lblEquQuestAddCond";
            this.lblEquQuestAddCond.Size = new System.Drawing.Size(197, 13);
            this.lblEquQuestAddCond.TabIndex = 22;
            this.lblEquQuestAddCond.Text = "Enter the additional selection conditions:";
            // 
            // eduQuestColumnNameTextBox
            // 
            this.eduQuestColumnNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduQuestColumnNameTextBox.Location = new System.Drawing.Point(251, 159);
            this.eduQuestColumnNameTextBox.Name = "eduQuestColumnNameTextBox";
            this.eduQuestColumnNameTextBox.Size = new System.Drawing.Size(373, 20);
            this.eduQuestColumnNameTextBox.TabIndex = 21;
            // 
            // lblEduQuestColumnName
            // 
            this.lblEduQuestColumnName.AutoSize = true;
            this.lblEduQuestColumnName.Location = new System.Drawing.Point(11, 163);
            this.lblEduQuestColumnName.Name = "lblEduQuestColumnName";
            this.lblEduQuestColumnName.Size = new System.Drawing.Size(233, 13);
            this.lblEduQuestColumnName.TabIndex = 20;
            this.lblEduQuestColumnName.Text = "Enter name of column with text of the questions:";
            // 
            // eduQuestTableNameTextBox
            // 
            this.eduQuestTableNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduQuestTableNameTextBox.Location = new System.Drawing.Point(251, 127);
            this.eduQuestTableNameTextBox.Name = "eduQuestTableNameTextBox";
            this.eduQuestTableNameTextBox.Size = new System.Drawing.Size(373, 20);
            this.eduQuestTableNameTextBox.TabIndex = 19;
            // 
            // lblEduQuestTableName
            // 
            this.lblEduQuestTableName.AutoSize = true;
            this.lblEduQuestTableName.Location = new System.Drawing.Point(11, 131);
            this.lblEduQuestTableName.Name = "lblEduQuestTableName";
            this.lblEduQuestTableName.Size = new System.Drawing.Size(222, 13);
            this.lblEduQuestTableName.TabIndex = 18;
            this.lblEduQuestTableName.Text = "Enter name of table with text of the questions:";
            // 
            // eduQuestConStrTextBox
            // 
            this.eduQuestConStrTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduQuestConStrTextBox.Location = new System.Drawing.Point(110, 95);
            this.eduQuestConStrTextBox.Name = "eduQuestConStrTextBox";
            this.eduQuestConStrTextBox.Size = new System.Drawing.Size(514, 20);
            this.eduQuestConStrTextBox.TabIndex = 17;
            // 
            // lblEduQuestConStr
            // 
            this.lblEduQuestConStr.AutoSize = true;
            this.lblEduQuestConStr.Location = new System.Drawing.Point(11, 97);
            this.lblEduQuestConStr.Name = "lblEduQuestConStr";
            this.lblEduQuestConStr.Size = new System.Drawing.Size(92, 13);
            this.lblEduQuestConStr.TabIndex = 16;
            this.lblEduQuestConStr.Text = "Connection string:";
            // 
            // lblEduQuestNOTE
            // 
            this.lblEduQuestNOTE.AutoSize = true;
            this.lblEduQuestNOTE.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblEduQuestNOTE.ForeColor = System.Drawing.Color.Red;
            this.lblEduQuestNOTE.Location = new System.Drawing.Point(10, 236);
            this.lblEduQuestNOTE.MaximumSize = new System.Drawing.Size(620, 0);
            this.lblEduQuestNOTE.Name = "lblEduQuestNOTE";
            this.lblEduQuestNOTE.Size = new System.Drawing.Size(618, 26);
            this.lblEduQuestNOTE.TabIndex = 24;
            this.lblEduQuestNOTE.Text = "NOTE: The right answer that you choosed will be set for all questions which will " +
    "be imported. If this answer is not suitable for all questions, please edit it by" +
    " using editor.";
            // 
            // eduAnswersAddCondTextBox
            // 
            this.eduAnswersAddCondTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduAnswersAddCondTextBox.Location = new System.Drawing.Point(214, 224);
            this.eduAnswersAddCondTextBox.Name = "eduAnswersAddCondTextBox";
            this.eduAnswersAddCondTextBox.Size = new System.Drawing.Size(410, 20);
            this.eduAnswersAddCondTextBox.TabIndex = 25;
            // 
            // lblEduAnswersAddCond
            // 
            this.lblEduAnswersAddCond.AutoSize = true;
            this.lblEduAnswersAddCond.Location = new System.Drawing.Point(11, 228);
            this.lblEduAnswersAddCond.Name = "lblEduAnswersAddCond";
            this.lblEduAnswersAddCond.Size = new System.Drawing.Size(197, 13);
            this.lblEduAnswersAddCond.TabIndex = 24;
            this.lblEduAnswersAddCond.Text = "Enter the additional selection conditions:";
            // 
            // eduAnswersColumnNameTextBox
            // 
            this.eduAnswersColumnNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduAnswersColumnNameTextBox.Location = new System.Drawing.Point(240, 174);
            this.eduAnswersColumnNameTextBox.Name = "eduAnswersColumnNameTextBox";
            this.eduAnswersColumnNameTextBox.Size = new System.Drawing.Size(384, 20);
            this.eduAnswersColumnNameTextBox.TabIndex = 23;
            // 
            // lblEduAnswersColumnName
            // 
            this.lblEduAnswersColumnName.AutoSize = true;
            this.lblEduAnswersColumnName.Location = new System.Drawing.Point(11, 178);
            this.lblEduAnswersColumnName.Name = "lblEduAnswersColumnName";
            this.lblEduAnswersColumnName.Size = new System.Drawing.Size(227, 13);
            this.lblEduAnswersColumnName.TabIndex = 22;
            this.lblEduAnswersColumnName.Text = "Enter name of column with text of the answers:";
            // 
            // eduAnswersTableNameTextBox
            // 
            this.eduAnswersTableNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduAnswersTableNameTextBox.Location = new System.Drawing.Point(240, 129);
            this.eduAnswersTableNameTextBox.Name = "eduAnswersTableNameTextBox";
            this.eduAnswersTableNameTextBox.Size = new System.Drawing.Size(384, 20);
            this.eduAnswersTableNameTextBox.TabIndex = 21;
            // 
            // lblEduAnswersTableName
            // 
            this.lblEduAnswersTableName.AutoSize = true;
            this.lblEduAnswersTableName.Location = new System.Drawing.Point(11, 133);
            this.lblEduAnswersTableName.Name = "lblEduAnswersTableName";
            this.lblEduAnswersTableName.Size = new System.Drawing.Size(216, 13);
            this.lblEduAnswersTableName.TabIndex = 20;
            this.lblEduAnswersTableName.Text = "Enter name of table with text of the answers:";
            // 
            // eduAnswersConStrTextBox
            // 
            this.eduAnswersConStrTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduAnswersConStrTextBox.Location = new System.Drawing.Point(110, 82);
            this.eduAnswersConStrTextBox.Name = "eduAnswersConStrTextBox";
            this.eduAnswersConStrTextBox.Size = new System.Drawing.Size(514, 20);
            this.eduAnswersConStrTextBox.TabIndex = 19;
            // 
            // lblEduAnswersConStr
            // 
            this.lblEduAnswersConStr.AutoSize = true;
            this.lblEduAnswersConStr.Location = new System.Drawing.Point(11, 84);
            this.lblEduAnswersConStr.Name = "lblEduAnswersConStr";
            this.lblEduAnswersConStr.Size = new System.Drawing.Size(92, 13);
            this.lblEduAnswersConStr.TabIndex = 18;
            this.lblEduAnswersConStr.Text = "Connection string:";
            // 
            // eduAnswersQuestIDComboBox
            // 
            this.eduAnswersQuestIDComboBox.FormattingEnabled = true;
            this.eduAnswersQuestIDComboBox.Location = new System.Drawing.Point(108, 34);
            this.eduAnswersQuestIDComboBox.Name = "eduAnswersQuestIDComboBox";
            this.eduAnswersQuestIDComboBox.Size = new System.Drawing.Size(514, 21);
            this.eduAnswersQuestIDComboBox.TabIndex = 17;
            // 
            // lblEduAnswersQuestID
            // 
            this.lblEduAnswersQuestID.AutoSize = true;
            this.lblEduAnswersQuestID.Location = new System.Drawing.Point(13, 37);
            this.lblEduAnswersQuestID.Name = "lblEduAnswersQuestID";
            this.lblEduAnswersQuestID.Size = new System.Drawing.Size(89, 13);
            this.lblEduAnswersQuestID.TabIndex = 16;
            this.lblEduAnswersQuestID.Text = "Choose question:";
            // 
            // eduLessonImageColumnNameTextBox
            // 
            this.eduLessonImageColumnNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.eduLessonImageColumnNameTextBox.Location = new System.Drawing.Point(258, 196);
            this.eduLessonImageColumnNameTextBox.Name = "eduLessonImageColumnNameTextBox";
            this.eduLessonImageColumnNameTextBox.Size = new System.Drawing.Size(368, 20);
            this.eduLessonImageColumnNameTextBox.TabIndex = 17;
            // 
            // lblEduLessonImageColumnName
            // 
            this.lblEduLessonImageColumnName.AutoSize = true;
            this.lblEduLessonImageColumnName.Location = new System.Drawing.Point(13, 200);
            this.lblEduLessonImageColumnName.Name = "lblEduLessonImageColumnName";
            this.lblEduLessonImageColumnName.Size = new System.Drawing.Size(239, 13);
            this.lblEduLessonImageColumnName.TabIndex = 16;
            this.lblEduLessonImageColumnName.Text = "Enter name of column with images of the lessons:";
            // 
            // fmEduDBImport
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(649, 380);
            this.Controls.Add(this.mainTabControl);
            this.Controls.Add(this.bottomPanel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "fmEduDBImport";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Import from database";
            this.mainTabControl.ResumeLayout(false);
            this.eduCategTabPage.ResumeLayout(false);
            this.eduCategTabPage.PerformLayout();
            this.eduLessonsTabPage.ResumeLayout(false);
            this.eduLessonsTabPage.PerformLayout();
            this.eduQuestTabPage.ResumeLayout(false);
            this.eduQuestTabPage.PerformLayout();
            this.eduAnswersTabPage.ResumeLayout(false);
            this.eduAnswersTabPage.PerformLayout();
            this.bottomPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl mainTabControl;
        private System.Windows.Forms.TabPage eduCategTabPage;
        private System.Windows.Forms.TabPage eduLessonsTabPage;
        private System.Windows.Forms.TabPage eduQuestTabPage;
        private System.Windows.Forms.TabPage eduAnswersTabPage;
        private System.Windows.Forms.ImageList eduImageList;
        private System.Windows.Forms.Panel bottomPanel;
        private System.Windows.Forms.Button importButton;
        private System.Windows.Forms.Button closeButton;
        private System.Windows.Forms.TextBox eduCategAddCondTextBox;
        private System.Windows.Forms.Label lblEduCategAdditionalConditions;
        private System.Windows.Forms.TextBox eduCategColumnNameTextBox;
        private System.Windows.Forms.Label lblEduCategColumnName;
        private System.Windows.Forms.TextBox eduCategTableNameTextBox;
        private System.Windows.Forms.Label lblEduCategTableName;
        private System.Windows.Forms.TextBox eduCategConStrTextBox;
        private System.Windows.Forms.Label lblEduCategConnectionString;
        private System.Windows.Forms.TextBox eduLessonAddCondTextBox;
        private System.Windows.Forms.Label lblEduLessonAdditionalConditions;
        private System.Windows.Forms.TextBox eduLessonColumnNameTextBox;
        private System.Windows.Forms.Label lblEduLessonColumnName;
        private System.Windows.Forms.TextBox eduLessonTableNameTextBox;
        private System.Windows.Forms.Label lblEduLessonTableName;
        private System.Windows.Forms.TextBox eduLessonConStrTextBox;
        private System.Windows.Forms.Label lblEduLessonConnectionString;
        private System.Windows.Forms.ComboBox eduLessonCategIDComboBox;
        private System.Windows.Forms.Label lblEduLessonsCategoryID;
        private System.Windows.Forms.Label lblEduQuestNOTE;
        private System.Windows.Forms.TextBox eduQuestAddCondTextBox;
        private System.Windows.Forms.Label lblEquQuestAddCond;
        private System.Windows.Forms.TextBox eduQuestColumnNameTextBox;
        private System.Windows.Forms.Label lblEduQuestColumnName;
        private System.Windows.Forms.TextBox eduQuestTableNameTextBox;
        private System.Windows.Forms.Label lblEduQuestTableName;
        private System.Windows.Forms.TextBox eduQuestConStrTextBox;
        private System.Windows.Forms.Label lblEduQuestConStr;
        private System.Windows.Forms.ComboBox eduQuestRightAnswerIDComboBox;
        private System.Windows.Forms.Label lblEduQuestRightAnswerID;
        private System.Windows.Forms.ComboBox eduQuestLessonIDComboBox;
        private System.Windows.Forms.Label lblEduQuestLessonID;
        private System.Windows.Forms.TextBox eduAnswersAddCondTextBox;
        private System.Windows.Forms.Label lblEduAnswersAddCond;
        private System.Windows.Forms.TextBox eduAnswersColumnNameTextBox;
        private System.Windows.Forms.Label lblEduAnswersColumnName;
        private System.Windows.Forms.TextBox eduAnswersTableNameTextBox;
        private System.Windows.Forms.Label lblEduAnswersTableName;
        private System.Windows.Forms.TextBox eduAnswersConStrTextBox;
        private System.Windows.Forms.Label lblEduAnswersConStr;
        private System.Windows.Forms.ComboBox eduAnswersQuestIDComboBox;
        private System.Windows.Forms.Label lblEduAnswersQuestID;
        private System.Windows.Forms.TextBox eduLessonImageColumnNameTextBox;
        private System.Windows.Forms.Label lblEduLessonImageColumnName;
    }
}