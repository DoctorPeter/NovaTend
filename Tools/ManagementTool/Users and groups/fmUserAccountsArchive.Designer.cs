namespace ManagementTool
{
    partial class fmUserAccountsArchive
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fmUserAccountsArchive));
            this.usersBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
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
            this.usersBindingNavigatorRestoreItem = new System.Windows.Forms.ToolStripButton();
            this.usersGroupBox = new System.Windows.Forms.GroupBox();
            this.userNamesDataGridView = new System.Windows.Forms.DataGridView();
            this.userNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.userAccountsGroupBox = new System.Windows.Forms.GroupBox();
            this.userAccountsDataGridView = new System.Windows.Forms.DataGridView();
            this.authSystemTypeNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.accountUserNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.accountPasswordColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.passThruColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.lastSignInDateColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.usersBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            ((System.ComponentModel.ISupportInitialize)(this.usersBindingNavigator)).BeginInit();
            this.usersBindingNavigator.SuspendLayout();
            this.usersGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userNamesDataGridView)).BeginInit();
            this.userAccountsGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userAccountsDataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // usersBindingNavigator
            // 
            this.usersBindingNavigator.AddNewItem = null;
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
            this.bindingNavigatorDeleteItem,
            this.usersBindingNavigatorSaveItem,
            this.usersBindingNavigatorRefreshItem,
            this.toolStripSeparator1,
            this.usersBindingNavigatorRestoreItem});
            this.usersBindingNavigator.Location = new System.Drawing.Point(0, 0);
            this.usersBindingNavigator.MoveFirstItem = this.bindingNavigatorMoveFirstItem;
            this.usersBindingNavigator.MoveLastItem = this.bindingNavigatorMoveLastItem;
            this.usersBindingNavigator.MoveNextItem = this.bindingNavigatorMoveNextItem;
            this.usersBindingNavigator.MovePreviousItem = this.bindingNavigatorMovePreviousItem;
            this.usersBindingNavigator.Name = "usersBindingNavigator";
            this.usersBindingNavigator.PositionItem = this.bindingNavigatorPositionItem;
            this.usersBindingNavigator.Size = new System.Drawing.Size(1016, 25);
            this.usersBindingNavigator.TabIndex = 22;
            this.usersBindingNavigator.Text = "bindingNavigator1";
            // 
            // bindingNavigatorCountItem
            // 
            this.bindingNavigatorCountItem.Name = "bindingNavigatorCountItem";
            this.bindingNavigatorCountItem.Size = new System.Drawing.Size(35, 22);
            this.bindingNavigatorCountItem.Text = "of {0}";
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
            // usersBindingNavigatorRestoreItem
            // 
            this.usersBindingNavigatorRestoreItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.usersBindingNavigatorRestoreItem.Image = ((System.Drawing.Image)(resources.GetObject("usersBindingNavigatorRestoreItem.Image")));
            this.usersBindingNavigatorRestoreItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.usersBindingNavigatorRestoreItem.Name = "usersBindingNavigatorRestoreItem";
            this.usersBindingNavigatorRestoreItem.Size = new System.Drawing.Size(23, 22);
            this.usersBindingNavigatorRestoreItem.Text = "Restore account";
            this.usersBindingNavigatorRestoreItem.Click += new System.EventHandler(this.usersBindingNavigatorRestoreItem_Click);
            // 
            // usersGroupBox
            // 
            this.usersGroupBox.Controls.Add(this.userNamesDataGridView);
            this.usersGroupBox.Dock = System.Windows.Forms.DockStyle.Left;
            this.usersGroupBox.Location = new System.Drawing.Point(0, 25);
            this.usersGroupBox.Name = "usersGroupBox";
            this.usersGroupBox.Size = new System.Drawing.Size(208, 464);
            this.usersGroupBox.TabIndex = 23;
            this.usersGroupBox.TabStop = false;
            this.usersGroupBox.Text = "Users";
            // 
            // userNamesDataGridView
            // 
            this.userNamesDataGridView.AllowUserToAddRows = false;
            this.userNamesDataGridView.AllowUserToDeleteRows = false;
            this.userNamesDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.userNamesDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.userNameColumn});
            this.userNamesDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userNamesDataGridView.Location = new System.Drawing.Point(3, 16);
            this.userNamesDataGridView.Name = "userNamesDataGridView";
            this.userNamesDataGridView.ReadOnly = true;
            this.userNamesDataGridView.Size = new System.Drawing.Size(202, 445);
            this.userNamesDataGridView.TabIndex = 111;
            this.userNamesDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.userNamesDataGridView_CellFormatting);
            this.userNamesDataGridView.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.userNamesDataGridView_CellParsing);
            this.userNamesDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userAccountsDataGridView_DataError);
            this.userNamesDataGridView.Enter += new System.EventHandler(this.userNamesDataGridView_Enter);
            // 
            // userNameColumn
            // 
            this.userNameColumn.HeaderText = "Name";
            this.userNameColumn.Name = "userNameColumn";
            this.userNameColumn.ReadOnly = true;
            this.userNameColumn.Width = 150;
            // 
            // userAccountsGroupBox
            // 
            this.userAccountsGroupBox.Controls.Add(this.userAccountsDataGridView);
            this.userAccountsGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userAccountsGroupBox.Location = new System.Drawing.Point(208, 25);
            this.userAccountsGroupBox.Name = "userAccountsGroupBox";
            this.userAccountsGroupBox.Size = new System.Drawing.Size(808, 464);
            this.userAccountsGroupBox.TabIndex = 24;
            this.userAccountsGroupBox.TabStop = false;
            this.userAccountsGroupBox.Text = "User accounts";
            // 
            // userAccountsDataGridView
            // 
            this.userAccountsDataGridView.AllowUserToAddRows = false;
            this.userAccountsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.userAccountsDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.authSystemTypeNameColumn,
            this.accountUserNameColumn,
            this.accountPasswordColumn,
            this.passThruColumn,
            this.lastSignInDateColumn});
            this.userAccountsDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userAccountsDataGridView.Location = new System.Drawing.Point(3, 16);
            this.userAccountsDataGridView.Name = "userAccountsDataGridView";
            this.userAccountsDataGridView.ReadOnly = true;
            this.userAccountsDataGridView.Size = new System.Drawing.Size(802, 445);
            this.userAccountsDataGridView.TabIndex = 6;
            this.userAccountsDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.userAccountsDataGridView_CellFormatting);
            this.userAccountsDataGridView.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.userAccountsDataGridView_CellParsing);
            this.userAccountsDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.userAccountsDataGridView_DataError);
            this.userAccountsDataGridView.Enter += new System.EventHandler(this.userAccountsDataGridView_Enter);
            // 
            // authSystemTypeNameColumn
            // 
            this.authSystemTypeNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.authSystemTypeNameColumn.HeaderText = "System";
            this.authSystemTypeNameColumn.Name = "authSystemTypeNameColumn";
            this.authSystemTypeNameColumn.ReadOnly = true;
            this.authSystemTypeNameColumn.Width = 150;
            // 
            // accountUserNameColumn
            // 
            this.accountUserNameColumn.HeaderText = "User name";
            this.accountUserNameColumn.Name = "accountUserNameColumn";
            this.accountUserNameColumn.ReadOnly = true;
            this.accountUserNameColumn.Width = 150;
            // 
            // accountPasswordColumn
            // 
            this.accountPasswordColumn.HeaderText = "Password";
            this.accountPasswordColumn.Name = "accountPasswordColumn";
            this.accountPasswordColumn.ReadOnly = true;
            this.accountPasswordColumn.Width = 150;
            // 
            // passThruColumn
            // 
            this.passThruColumn.HeaderText = "Pass password through";
            this.passThruColumn.Name = "passThruColumn";
            this.passThruColumn.ReadOnly = true;
            this.passThruColumn.Width = 150;
            // 
            // lastSignInDateColumn
            // 
            this.lastSignInDateColumn.HeaderText = "Date of last logon";
            this.lastSignInDateColumn.Name = "lastSignInDateColumn";
            this.lastSignInDateColumn.ReadOnly = true;
            this.lastSignInDateColumn.Width = 150;
            // 
            // splitter1
            // 
            this.splitter1.Location = new System.Drawing.Point(208, 25);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(3, 464);
            this.splitter1.TabIndex = 25;
            this.splitter1.TabStop = false;
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
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // fmUserAccountsArchive
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1016, 489);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.userAccountsGroupBox);
            this.Controls.Add(this.usersGroupBox);
            this.Controls.Add(this.usersBindingNavigator);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "fmUserAccountsArchive";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "User accounts archive";
            ((System.ComponentModel.ISupportInitialize)(this.usersBindingNavigator)).EndInit();
            this.usersBindingNavigator.ResumeLayout(false);
            this.usersBindingNavigator.PerformLayout();
            this.usersGroupBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.userNamesDataGridView)).EndInit();
            this.userAccountsGroupBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.userAccountsDataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.BindingNavigator usersBindingNavigator;
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
        private System.Windows.Forms.ToolStripButton usersBindingNavigatorRestoreItem;
        private System.Windows.Forms.GroupBox usersGroupBox;
        private System.Windows.Forms.GroupBox userAccountsGroupBox;
        private System.Windows.Forms.DataGridView userNamesDataGridView;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.DataGridView userAccountsDataGridView;
        private System.Windows.Forms.DataGridViewComboBoxColumn authSystemTypeNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn accountUserNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn accountPasswordColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn passThruColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn lastSignInDateColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn userNameColumn;
        private System.Windows.Forms.ToolStripButton usersBindingNavigatorRefreshItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;

    }
}