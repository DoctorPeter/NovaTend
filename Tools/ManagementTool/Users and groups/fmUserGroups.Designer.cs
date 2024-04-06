namespace ManagementTool
{
    partial class fmUserGroups
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fmUserGroups));
            this.lblAuthSystem = new System.Windows.Forms.Label();
            this.lblServiceUserName = new System.Windows.Forms.Label();
            this.topPanel = new System.Windows.Forms.Panel();
            this.bottomPanel = new System.Windows.Forms.Panel();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.userGroupsPanel = new System.Windows.Forms.Panel();
            this.userGroupsListView = new System.Windows.Forms.ListView();
            this.userGroupNameColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.imageList = new System.Windows.Forms.ImageList(this.components);
            this.userGroupsCountPanel = new System.Windows.Forms.Panel();
            this.lblUserGroupsCount = new System.Windows.Forms.Label();
            this.userNamePanel = new System.Windows.Forms.Panel();
            this.moveButtonsPanel = new System.Windows.Forms.Panel();
            this.moveRightButton = new System.Windows.Forms.Button();
            this.moveLeftButton = new System.Windows.Forms.Button();
            this.groupsPanel = new System.Windows.Forms.Panel();
            this.groupsListView = new System.Windows.Forms.ListView();
            this.groupNameColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.groupsCountPanel = new System.Windows.Forms.Panel();
            this.lblGroupsCount = new System.Windows.Forms.Label();
            this.groupsTitlePanel = new System.Windows.Forms.Panel();
            this.GroupsTitleLabel = new System.Windows.Forms.Label();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.splitter2 = new System.Windows.Forms.Splitter();
            this.topPanel.SuspendLayout();
            this.bottomPanel.SuspendLayout();
            this.userGroupsPanel.SuspendLayout();
            this.userGroupsCountPanel.SuspendLayout();
            this.userNamePanel.SuspendLayout();
            this.moveButtonsPanel.SuspendLayout();
            this.groupsPanel.SuspendLayout();
            this.groupsCountPanel.SuspendLayout();
            this.groupsTitlePanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblAuthSystem
            // 
            this.lblAuthSystem.AutoSize = true;
            this.lblAuthSystem.Location = new System.Drawing.Point(11, 13);
            this.lblAuthSystem.Name = "lblAuthSystem";
            this.lblAuthSystem.Size = new System.Drawing.Size(113, 13);
            this.lblAuthSystem.TabIndex = 7;
            this.lblAuthSystem.Text = "Authentication system:";
            // 
            // lblServiceUserName
            // 
            this.lblServiceUserName.AutoSize = true;
            this.lblServiceUserName.Location = new System.Drawing.Point(12, 15);
            this.lblServiceUserName.Name = "lblServiceUserName";
            this.lblServiceUserName.Size = new System.Drawing.Size(96, 13);
            this.lblServiceUserName.TabIndex = 6;
            this.lblServiceUserName.Text = "System user name:";
            // 
            // topPanel
            // 
            this.topPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.topPanel.Controls.Add(this.lblAuthSystem);
            this.topPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.topPanel.Location = new System.Drawing.Point(0, 0);
            this.topPanel.Name = "topPanel";
            this.topPanel.Size = new System.Drawing.Size(776, 42);
            this.topPanel.TabIndex = 8;
            // 
            // bottomPanel
            // 
            this.bottomPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.bottomPanel.Controls.Add(this.btnCancel);
            this.bottomPanel.Controls.Add(this.btnOK);
            this.bottomPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.bottomPanel.Location = new System.Drawing.Point(0, 451);
            this.bottomPanel.Name = "bottomPanel";
            this.bottomPanel.Size = new System.Drawing.Size(776, 59);
            this.bottomPanel.TabIndex = 9;
            // 
            // btnCancel
            // 
            this.btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnCancel.Image = ((System.Drawing.Image)(resources.GetObject("btnCancel.Image")));
            this.btnCancel.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnCancel.Location = new System.Drawing.Point(644, 13);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(115, 33);
            this.btnCancel.TabIndex = 10;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnOK
            // 
            this.btnOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnOK.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnOK.Image = ((System.Drawing.Image)(resources.GetObject("btnOK.Image")));
            this.btnOK.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnOK.Location = new System.Drawing.Point(521, 13);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(115, 33);
            this.btnOK.TabIndex = 9;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // userGroupsPanel
            // 
            this.userGroupsPanel.Controls.Add(this.userGroupsListView);
            this.userGroupsPanel.Controls.Add(this.userGroupsCountPanel);
            this.userGroupsPanel.Controls.Add(this.userNamePanel);
            this.userGroupsPanel.Dock = System.Windows.Forms.DockStyle.Left;
            this.userGroupsPanel.Location = new System.Drawing.Point(0, 42);
            this.userGroupsPanel.Name = "userGroupsPanel";
            this.userGroupsPanel.Size = new System.Drawing.Size(344, 409);
            this.userGroupsPanel.TabIndex = 10;
            // 
            // userGroupsListView
            // 
            this.userGroupsListView.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.userGroupsListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.userGroupNameColumnHeader});
            this.userGroupsListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userGroupsListView.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.userGroupsListView.FullRowSelect = true;
            this.userGroupsListView.Location = new System.Drawing.Point(0, 46);
            this.userGroupsListView.Name = "userGroupsListView";
            this.userGroupsListView.Size = new System.Drawing.Size(344, 316);
            this.userGroupsListView.SmallImageList = this.imageList;
            this.userGroupsListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.userGroupsListView.TabIndex = 30;
            this.userGroupsListView.UseCompatibleStateImageBehavior = false;
            this.userGroupsListView.View = System.Windows.Forms.View.Details;
            // 
            // userGroupNameColumnHeader
            // 
            this.userGroupNameColumnHeader.Text = "Group name";
            this.userGroupNameColumnHeader.Width = 336;
            // 
            // imageList
            // 
            this.imageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList.ImageStream")));
            this.imageList.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList.Images.SetKeyName(0, "group_16.png");
            // 
            // userGroupsCountPanel
            // 
            this.userGroupsCountPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.userGroupsCountPanel.Controls.Add(this.lblUserGroupsCount);
            this.userGroupsCountPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.userGroupsCountPanel.Location = new System.Drawing.Point(0, 362);
            this.userGroupsCountPanel.Name = "userGroupsCountPanel";
            this.userGroupsCountPanel.Size = new System.Drawing.Size(344, 47);
            this.userGroupsCountPanel.TabIndex = 31;
            // 
            // lblUserGroupsCount
            // 
            this.lblUserGroupsCount.AutoSize = true;
            this.lblUserGroupsCount.Location = new System.Drawing.Point(12, 17);
            this.lblUserGroupsCount.Name = "lblUserGroupsCount";
            this.lblUserGroupsCount.Size = new System.Drawing.Size(38, 13);
            this.lblUserGroupsCount.TabIndex = 8;
            this.lblUserGroupsCount.Text = "Count:";
            // 
            // userNamePanel
            // 
            this.userNamePanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.userNamePanel.Controls.Add(this.lblServiceUserName);
            this.userNamePanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.userNamePanel.Location = new System.Drawing.Point(0, 0);
            this.userNamePanel.Name = "userNamePanel";
            this.userNamePanel.Size = new System.Drawing.Size(344, 46);
            this.userNamePanel.TabIndex = 0;
            // 
            // moveButtonsPanel
            // 
            this.moveButtonsPanel.Controls.Add(this.moveRightButton);
            this.moveButtonsPanel.Controls.Add(this.moveLeftButton);
            this.moveButtonsPanel.Dock = System.Windows.Forms.DockStyle.Left;
            this.moveButtonsPanel.Location = new System.Drawing.Point(347, 42);
            this.moveButtonsPanel.Name = "moveButtonsPanel";
            this.moveButtonsPanel.Size = new System.Drawing.Size(80, 409);
            this.moveButtonsPanel.TabIndex = 11;
            // 
            // moveRightButton
            // 
            this.moveRightButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.moveRightButton.Image = ((System.Drawing.Image)(resources.GetObject("moveRightButton.Image")));
            this.moveRightButton.Location = new System.Drawing.Point(9, 126);
            this.moveRightButton.Name = "moveRightButton";
            this.moveRightButton.Size = new System.Drawing.Size(63, 51);
            this.moveRightButton.TabIndex = 11;
            this.moveRightButton.UseVisualStyleBackColor = true;
            this.moveRightButton.Click += new System.EventHandler(this.moveRightButton_Click);
            // 
            // moveLeftButton
            // 
            this.moveLeftButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.moveLeftButton.Image = ((System.Drawing.Image)(resources.GetObject("moveLeftButton.Image")));
            this.moveLeftButton.Location = new System.Drawing.Point(9, 196);
            this.moveLeftButton.Name = "moveLeftButton";
            this.moveLeftButton.Size = new System.Drawing.Size(63, 51);
            this.moveLeftButton.TabIndex = 10;
            this.moveLeftButton.UseVisualStyleBackColor = true;
            this.moveLeftButton.Click += new System.EventHandler(this.moveLeftButton_Click);
            // 
            // groupsPanel
            // 
            this.groupsPanel.Controls.Add(this.groupsListView);
            this.groupsPanel.Controls.Add(this.groupsCountPanel);
            this.groupsPanel.Controls.Add(this.groupsTitlePanel);
            this.groupsPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupsPanel.Location = new System.Drawing.Point(430, 42);
            this.groupsPanel.Name = "groupsPanel";
            this.groupsPanel.Size = new System.Drawing.Size(346, 409);
            this.groupsPanel.TabIndex = 12;
            // 
            // groupsListView
            // 
            this.groupsListView.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.groupsListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.groupNameColumnHeader});
            this.groupsListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupsListView.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.groupsListView.FullRowSelect = true;
            this.groupsListView.Location = new System.Drawing.Point(0, 46);
            this.groupsListView.Name = "groupsListView";
            this.groupsListView.Size = new System.Drawing.Size(346, 316);
            this.groupsListView.SmallImageList = this.imageList;
            this.groupsListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.groupsListView.TabIndex = 31;
            this.groupsListView.UseCompatibleStateImageBehavior = false;
            this.groupsListView.View = System.Windows.Forms.View.Details;
            // 
            // groupNameColumnHeader
            // 
            this.groupNameColumnHeader.Text = "Group name";
            this.groupNameColumnHeader.Width = 336;
            // 
            // groupsCountPanel
            // 
            this.groupsCountPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.groupsCountPanel.Controls.Add(this.lblGroupsCount);
            this.groupsCountPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.groupsCountPanel.Location = new System.Drawing.Point(0, 362);
            this.groupsCountPanel.Name = "groupsCountPanel";
            this.groupsCountPanel.Size = new System.Drawing.Size(346, 47);
            this.groupsCountPanel.TabIndex = 32;
            // 
            // lblGroupsCount
            // 
            this.lblGroupsCount.AutoSize = true;
            this.lblGroupsCount.Location = new System.Drawing.Point(15, 17);
            this.lblGroupsCount.Name = "lblGroupsCount";
            this.lblGroupsCount.Size = new System.Drawing.Size(38, 13);
            this.lblGroupsCount.TabIndex = 9;
            this.lblGroupsCount.Text = "Count:";
            // 
            // groupsTitlePanel
            // 
            this.groupsTitlePanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.groupsTitlePanel.Controls.Add(this.GroupsTitleLabel);
            this.groupsTitlePanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupsTitlePanel.Location = new System.Drawing.Point(0, 0);
            this.groupsTitlePanel.Name = "groupsTitlePanel";
            this.groupsTitlePanel.Size = new System.Drawing.Size(346, 46);
            this.groupsTitlePanel.TabIndex = 1;
            // 
            // GroupsTitleLabel
            // 
            this.GroupsTitleLabel.AutoSize = true;
            this.GroupsTitleLabel.Location = new System.Drawing.Point(15, 15);
            this.GroupsTitleLabel.Name = "GroupsTitleLabel";
            this.GroupsTitleLabel.Size = new System.Drawing.Size(96, 13);
            this.GroupsTitleLabel.TabIndex = 0;
            this.GroupsTitleLabel.Text = "List of user groups:";
            // 
            // splitter1
            // 
            this.splitter1.Location = new System.Drawing.Point(344, 42);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(3, 409);
            this.splitter1.TabIndex = 13;
            this.splitter1.TabStop = false;
            // 
            // splitter2
            // 
            this.splitter2.Location = new System.Drawing.Point(427, 42);
            this.splitter2.Name = "splitter2";
            this.splitter2.Size = new System.Drawing.Size(3, 409);
            this.splitter2.TabIndex = 14;
            this.splitter2.TabStop = false;
            // 
            // fmUserGroups
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(776, 510);
            this.Controls.Add(this.groupsPanel);
            this.Controls.Add(this.splitter2);
            this.Controls.Add(this.moveButtonsPanel);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.userGroupsPanel);
            this.Controls.Add(this.bottomPanel);
            this.Controls.Add(this.topPanel);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "fmUserGroups";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Groups";
            this.topPanel.ResumeLayout(false);
            this.topPanel.PerformLayout();
            this.bottomPanel.ResumeLayout(false);
            this.userGroupsPanel.ResumeLayout(false);
            this.userGroupsCountPanel.ResumeLayout(false);
            this.userGroupsCountPanel.PerformLayout();
            this.userNamePanel.ResumeLayout(false);
            this.userNamePanel.PerformLayout();
            this.moveButtonsPanel.ResumeLayout(false);
            this.groupsPanel.ResumeLayout(false);
            this.groupsCountPanel.ResumeLayout(false);
            this.groupsCountPanel.PerformLayout();
            this.groupsTitlePanel.ResumeLayout(false);
            this.groupsTitlePanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label lblAuthSystem;
        private System.Windows.Forms.Label lblServiceUserName;
        private System.Windows.Forms.Panel topPanel;
        private System.Windows.Forms.Panel bottomPanel;
        private System.Windows.Forms.Panel userGroupsPanel;
        private System.Windows.Forms.Panel moveButtonsPanel;
        private System.Windows.Forms.Panel groupsPanel;
        private System.Windows.Forms.Panel userNamePanel;
        private System.Windows.Forms.Panel groupsTitlePanel;
        private System.Windows.Forms.Label GroupsTitleLabel;
        private System.Windows.Forms.ListView userGroupsListView;
        private System.Windows.Forms.ColumnHeader userGroupNameColumnHeader;
        private System.Windows.Forms.ListView groupsListView;
        private System.Windows.Forms.ColumnHeader groupNameColumnHeader;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Button moveRightButton;
        private System.Windows.Forms.Button moveLeftButton;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.Splitter splitter2;
        private System.Windows.Forms.Panel userGroupsCountPanel;
        private System.Windows.Forms.Label lblUserGroupsCount;
        private System.Windows.Forms.Panel groupsCountPanel;
        private System.Windows.Forms.Label lblGroupsCount;
        private System.Windows.Forms.ImageList imageList;
    }
}