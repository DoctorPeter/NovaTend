namespace ManagementTool
{
    partial class fmPresetHookup
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fmPresetHookup));
            this.presetPanel = new System.Windows.Forms.Panel();
            this.presetDataGridView = new System.Windows.Forms.DataGridView();
            this.presetNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.presetBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
            this.toolStripLabel6 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton33 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton34 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator16 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox6 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator17 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton35 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton36 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator18 = new System.Windows.Forms.ToolStripSeparator();
            this.presetBindingNavigatorRefreshIntem = new System.Windows.Forms.ToolStripButton();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.hookupPanel = new System.Windows.Forms.Panel();
            this.presetHookupDataGridView = new System.Windows.Forms.DataGridView();
            this.presetHookupBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
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
            this.presetHookupBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
            this.presetHookupBindingNavigatorRefreshItem = new System.Windows.Forms.ToolStripButton();
            this.groupNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.userGroupIDColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.userNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.userIDColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.computerNameColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.osTypeColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.presetPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.presetDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.presetBindingNavigator)).BeginInit();
            this.presetBindingNavigator.SuspendLayout();
            this.hookupPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.presetHookupDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.presetHookupBindingNavigator)).BeginInit();
            this.presetHookupBindingNavigator.SuspendLayout();
            this.SuspendLayout();
            // 
            // presetPanel
            // 
            this.presetPanel.Controls.Add(this.presetDataGridView);
            this.presetPanel.Controls.Add(this.presetBindingNavigator);
            this.presetPanel.Dock = System.Windows.Forms.DockStyle.Left;
            this.presetPanel.Location = new System.Drawing.Point(0, 0);
            this.presetPanel.Name = "presetPanel";
            this.presetPanel.Size = new System.Drawing.Size(258, 436);
            this.presetPanel.TabIndex = 0;
            // 
            // presetDataGridView
            // 
            this.presetDataGridView.AllowUserToAddRows = false;
            this.presetDataGridView.AllowUserToDeleteRows = false;
            this.presetDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.presetDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.presetNameColumn});
            this.presetDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.presetDataGridView.Location = new System.Drawing.Point(0, 25);
            this.presetDataGridView.Name = "presetDataGridView";
            this.presetDataGridView.ReadOnly = true;
            this.presetDataGridView.Size = new System.Drawing.Size(258, 411);
            this.presetDataGridView.TabIndex = 13;
            this.presetDataGridView.CellValidating += new System.Windows.Forms.DataGridViewCellValidatingEventHandler(this.presetHookupDataGridView_CellValidating);
            this.presetDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.presetDataGridView_DataError);
            this.presetDataGridView.EditingControlShowing += new System.Windows.Forms.DataGridViewEditingControlShowingEventHandler(this.presetHookupDataGridView_EditingControlShowing);
            // 
            // presetNameColumn
            // 
            this.presetNameColumn.HeaderText = "Preset name";
            this.presetNameColumn.Name = "presetNameColumn";
            this.presetNameColumn.ReadOnly = true;
            this.presetNameColumn.Width = 200;
            // 
            // presetBindingNavigator
            // 
            this.presetBindingNavigator.AddNewItem = null;
            this.presetBindingNavigator.CountItem = this.toolStripLabel6;
            this.presetBindingNavigator.DeleteItem = null;
            this.presetBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton33,
            this.toolStripButton34,
            this.toolStripSeparator16,
            this.toolStripTextBox6,
            this.toolStripLabel6,
            this.toolStripSeparator17,
            this.toolStripButton35,
            this.toolStripButton36,
            this.toolStripSeparator18,
            this.presetBindingNavigatorRefreshIntem});
            this.presetBindingNavigator.Location = new System.Drawing.Point(0, 0);
            this.presetBindingNavigator.MoveFirstItem = this.toolStripButton33;
            this.presetBindingNavigator.MoveLastItem = this.toolStripButton36;
            this.presetBindingNavigator.MoveNextItem = this.toolStripButton35;
            this.presetBindingNavigator.MovePreviousItem = this.toolStripButton34;
            this.presetBindingNavigator.Name = "presetBindingNavigator";
            this.presetBindingNavigator.PositionItem = this.toolStripTextBox6;
            this.presetBindingNavigator.Size = new System.Drawing.Size(258, 25);
            this.presetBindingNavigator.TabIndex = 12;
            // 
            // toolStripLabel6
            // 
            this.toolStripLabel6.Name = "toolStripLabel6";
            this.toolStripLabel6.Size = new System.Drawing.Size(35, 22);
            this.toolStripLabel6.Text = "of {0}";
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
            // presetBindingNavigatorRefreshIntem
            // 
            this.presetBindingNavigatorRefreshIntem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.presetBindingNavigatorRefreshIntem.Image = ((System.Drawing.Image)(resources.GetObject("presetBindingNavigatorRefreshIntem.Image")));
            this.presetBindingNavigatorRefreshIntem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.presetBindingNavigatorRefreshIntem.Name = "presetBindingNavigatorRefreshIntem";
            this.presetBindingNavigatorRefreshIntem.Size = new System.Drawing.Size(23, 22);
            this.presetBindingNavigatorRefreshIntem.Text = "Refresh";
            this.presetBindingNavigatorRefreshIntem.Click += new System.EventHandler(this.presetBindingNavigatorRefreshIntem_Click);
            // 
            // splitter1
            // 
            this.splitter1.Location = new System.Drawing.Point(258, 0);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(3, 436);
            this.splitter1.TabIndex = 1;
            this.splitter1.TabStop = false;
            // 
            // hookupPanel
            // 
            this.hookupPanel.Controls.Add(this.presetHookupDataGridView);
            this.hookupPanel.Controls.Add(this.presetHookupBindingNavigator);
            this.hookupPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.hookupPanel.Location = new System.Drawing.Point(261, 0);
            this.hookupPanel.Name = "hookupPanel";
            this.hookupPanel.Size = new System.Drawing.Size(658, 436);
            this.hookupPanel.TabIndex = 2;
            // 
            // presetHookupDataGridView
            // 
            this.presetHookupDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.presetHookupDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.groupNameColumn,
            this.userGroupIDColumn,
            this.userNameColumn,
            this.userIDColumn,
            this.computerNameColumn,
            this.osTypeColumn});
            this.presetHookupDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.presetHookupDataGridView.Location = new System.Drawing.Point(0, 25);
            this.presetHookupDataGridView.Name = "presetHookupDataGridView";
            this.presetHookupDataGridView.Size = new System.Drawing.Size(658, 411);
            this.presetHookupDataGridView.TabIndex = 14;
            this.presetHookupDataGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.presetHookupDataGridView_CellFormatting);
            this.presetHookupDataGridView.CellValidating += new System.Windows.Forms.DataGridViewCellValidatingEventHandler(this.presetHookupDataGridView_CellValidating);
            this.presetHookupDataGridView.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.presetHookupDataGridView_CellValueChanged);
            this.presetHookupDataGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.presetDataGridView_DataError);
            this.presetHookupDataGridView.EditingControlShowing += new System.Windows.Forms.DataGridViewEditingControlShowingEventHandler(this.presetHookupDataGridView_EditingControlShowing);
            // 
            // presetHookupBindingNavigator
            // 
            this.presetHookupBindingNavigator.AddNewItem = this.toolStripButton37;
            this.presetHookupBindingNavigator.CountItem = this.toolStripLabel7;
            this.presetHookupBindingNavigator.DeleteItem = this.toolStripButton38;
            this.presetHookupBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
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
            this.presetHookupBindingNavigatorSaveItem,
            this.presetHookupBindingNavigatorRefreshItem});
            this.presetHookupBindingNavigator.Location = new System.Drawing.Point(0, 0);
            this.presetHookupBindingNavigator.MoveFirstItem = this.toolStripButton39;
            this.presetHookupBindingNavigator.MoveLastItem = this.toolStripButton42;
            this.presetHookupBindingNavigator.MoveNextItem = this.toolStripButton41;
            this.presetHookupBindingNavigator.MovePreviousItem = this.toolStripButton40;
            this.presetHookupBindingNavigator.Name = "presetHookupBindingNavigator";
            this.presetHookupBindingNavigator.PositionItem = this.toolStripTextBox7;
            this.presetHookupBindingNavigator.Size = new System.Drawing.Size(658, 25);
            this.presetHookupBindingNavigator.TabIndex = 11;
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
            this.toolStripLabel7.Size = new System.Drawing.Size(35, 22);
            this.toolStripLabel7.Text = "of {0}";
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
            // presetHookupBindingNavigatorSaveItem
            // 
            this.presetHookupBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.presetHookupBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("presetHookupBindingNavigatorSaveItem.Image")));
            this.presetHookupBindingNavigatorSaveItem.Name = "presetHookupBindingNavigatorSaveItem";
            this.presetHookupBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 22);
            this.presetHookupBindingNavigatorSaveItem.Text = "Save Data";
            this.presetHookupBindingNavigatorSaveItem.Click += new System.EventHandler(this.presetHookupBindingNavigatorSaveItem_Click);
            // 
            // presetHookupBindingNavigatorRefreshItem
            // 
            this.presetHookupBindingNavigatorRefreshItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.presetHookupBindingNavigatorRefreshItem.Image = ((System.Drawing.Image)(resources.GetObject("presetHookupBindingNavigatorRefreshItem.Image")));
            this.presetHookupBindingNavigatorRefreshItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.presetHookupBindingNavigatorRefreshItem.Name = "presetHookupBindingNavigatorRefreshItem";
            this.presetHookupBindingNavigatorRefreshItem.Size = new System.Drawing.Size(23, 22);
            this.presetHookupBindingNavigatorRefreshItem.Text = "Refresh";
            this.presetHookupBindingNavigatorRefreshItem.Click += new System.EventHandler(this.presetHookupBindingNavigatorRefreshItem_Click);
            // 
            // groupNameColumn
            // 
            this.groupNameColumn.DisplayStyle = System.Windows.Forms.DataGridViewComboBoxDisplayStyle.ComboBox;
            this.groupNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.groupNameColumn.HeaderText = "User group";
            this.groupNameColumn.Name = "groupNameColumn";
            this.groupNameColumn.Width = 150;
            // 
            // userGroupIDColumn
            // 
            this.userGroupIDColumn.HeaderText = "GroupID";
            this.userGroupIDColumn.Name = "userGroupIDColumn";
            this.userGroupIDColumn.Visible = false;
            // 
            // userNameColumn
            // 
            this.userNameColumn.DisplayStyle = System.Windows.Forms.DataGridViewComboBoxDisplayStyle.ComboBox;
            this.userNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.userNameColumn.HeaderText = "User";
            this.userNameColumn.Name = "userNameColumn";
            this.userNameColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.userNameColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.userNameColumn.Width = 150;
            // 
            // userIDColumn
            // 
            this.userIDColumn.HeaderText = "UserID";
            this.userIDColumn.Name = "userIDColumn";
            this.userIDColumn.ReadOnly = true;
            this.userIDColumn.Visible = false;
            // 
            // computerNameColumn
            // 
            this.computerNameColumn.DisplayStyle = System.Windows.Forms.DataGridViewComboBoxDisplayStyle.ComboBox;
            this.computerNameColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.computerNameColumn.HeaderText = "Computer";
            this.computerNameColumn.Name = "computerNameColumn";
            this.computerNameColumn.Width = 150;
            // 
            // osTypeColumn
            // 
            this.osTypeColumn.DisplayStyle = System.Windows.Forms.DataGridViewComboBoxDisplayStyle.ComboBox;
            this.osTypeColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.osTypeColumn.HeaderText = "OS version";
            this.osTypeColumn.Name = "osTypeColumn";
            this.osTypeColumn.Width = 150;
            // 
            // fmPresetHookup
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(919, 436);
            this.Controls.Add(this.hookupPanel);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.presetPanel);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "fmPresetHookup";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Preset hookup";
            this.Load += new System.EventHandler(this.fmPresetHookup_Load);
            this.presetPanel.ResumeLayout(false);
            this.presetPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.presetDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.presetBindingNavigator)).EndInit();
            this.presetBindingNavigator.ResumeLayout(false);
            this.presetBindingNavigator.PerformLayout();
            this.hookupPanel.ResumeLayout(false);
            this.hookupPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.presetHookupDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.presetHookupBindingNavigator)).EndInit();
            this.presetHookupBindingNavigator.ResumeLayout(false);
            this.presetHookupBindingNavigator.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel presetPanel;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.Panel hookupPanel;
        private System.Windows.Forms.BindingNavigator presetBindingNavigator;
        private System.Windows.Forms.ToolStripLabel toolStripLabel6;
        private System.Windows.Forms.ToolStripButton toolStripButton33;
        private System.Windows.Forms.ToolStripButton toolStripButton34;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator16;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox6;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator17;
        private System.Windows.Forms.ToolStripButton toolStripButton35;
        private System.Windows.Forms.ToolStripButton toolStripButton36;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator18;
        private System.Windows.Forms.ToolStripButton presetBindingNavigatorRefreshIntem;
        private System.Windows.Forms.DataGridView presetDataGridView;
        private System.Windows.Forms.DataGridViewTextBoxColumn presetNameColumn;
        private System.Windows.Forms.BindingNavigator presetHookupBindingNavigator;
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
        private System.Windows.Forms.ToolStripButton presetHookupBindingNavigatorSaveItem;
        private System.Windows.Forms.ToolStripButton presetHookupBindingNavigatorRefreshItem;
        private System.Windows.Forms.DataGridView presetHookupDataGridView;
        private System.Windows.Forms.DataGridViewComboBoxColumn groupNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn userGroupIDColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn userNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn userIDColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn computerNameColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn osTypeColumn;
    }
}