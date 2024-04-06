namespace ManagementTool
{
    partial class fmGroupUsers
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fmGroupUsers));
            this.usersTitleLabel = new System.Windows.Forms.Label();
            this.usersTitlePanel = new System.Windows.Forms.Panel();
            this.lblUsersCount = new System.Windows.Forms.Label();
            this.usersCountPanel = new System.Windows.Forms.Panel();
            this.userNameColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.usersListView = new System.Windows.Forms.ListView();
            this.imageList = new System.Windows.Forms.ImageList(this.components);
            this.groupsPanel = new System.Windows.Forms.Panel();
            this.groupUsersListView = new System.Windows.Forms.ListView();
            this.groupUserNameColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.moveLeftButton = new System.Windows.Forms.Button();
            this.groupUsersCountPanel = new System.Windows.Forms.Panel();
            this.lblGroupUsersCount = new System.Windows.Forms.Label();
            this.moveRightButton = new System.Windows.Forms.Button();
            this.moveButtonsPanel = new System.Windows.Forms.Panel();
            this.groupNamePanel = new System.Windows.Forms.Panel();
            this.lblServiceGroupName = new System.Windows.Forms.Label();
            this.userGroupsPanel = new System.Windows.Forms.Panel();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.bottomPanel = new System.Windows.Forms.Panel();
            this.topPanel = new System.Windows.Forms.Panel();
            this.lblAuthSystem = new System.Windows.Forms.Label();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.splitter2 = new System.Windows.Forms.Splitter();
            this.usersTitlePanel.SuspendLayout();
            this.usersCountPanel.SuspendLayout();
            this.groupsPanel.SuspendLayout();
            this.groupUsersCountPanel.SuspendLayout();
            this.moveButtonsPanel.SuspendLayout();
            this.groupNamePanel.SuspendLayout();
            this.userGroupsPanel.SuspendLayout();
            this.bottomPanel.SuspendLayout();
            this.topPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // usersTitleLabel
            // 
            this.usersTitleLabel.AutoSize = true;
            this.usersTitleLabel.Location = new System.Drawing.Point(15, 15);
            this.usersTitleLabel.Name = "usersTitleLabel";
            this.usersTitleLabel.Size = new System.Drawing.Size(66, 13);
            this.usersTitleLabel.TabIndex = 0;
            this.usersTitleLabel.Text = "List of users:";
            // 
            // usersTitlePanel
            // 
            this.usersTitlePanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.usersTitlePanel.Controls.Add(this.usersTitleLabel);
            this.usersTitlePanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.usersTitlePanel.Location = new System.Drawing.Point(0, 0);
            this.usersTitlePanel.Name = "usersTitlePanel";
            this.usersTitlePanel.Size = new System.Drawing.Size(347, 46);
            this.usersTitlePanel.TabIndex = 1;
            // 
            // lblUsersCount
            // 
            this.lblUsersCount.AutoSize = true;
            this.lblUsersCount.Location = new System.Drawing.Point(15, 17);
            this.lblUsersCount.Name = "lblUsersCount";
            this.lblUsersCount.Size = new System.Drawing.Size(38, 13);
            this.lblUsersCount.TabIndex = 9;
            this.lblUsersCount.Text = "Count:";
            // 
            // usersCountPanel
            // 
            this.usersCountPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.usersCountPanel.Controls.Add(this.lblUsersCount);
            this.usersCountPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.usersCountPanel.Location = new System.Drawing.Point(0, 351);
            this.usersCountPanel.Name = "usersCountPanel";
            this.usersCountPanel.Size = new System.Drawing.Size(347, 47);
            this.usersCountPanel.TabIndex = 32;
            // 
            // userNameColumnHeader
            // 
            this.userNameColumnHeader.Text = "User name";
            this.userNameColumnHeader.Width = 336;
            // 
            // usersListView
            // 
            this.usersListView.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.usersListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.userNameColumnHeader});
            this.usersListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.usersListView.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.usersListView.FullRowSelect = true;
            this.usersListView.Location = new System.Drawing.Point(0, 46);
            this.usersListView.Name = "usersListView";
            this.usersListView.Size = new System.Drawing.Size(347, 305);
            this.usersListView.SmallImageList = this.imageList;
            this.usersListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.usersListView.TabIndex = 31;
            this.usersListView.UseCompatibleStateImageBehavior = false;
            this.usersListView.View = System.Windows.Forms.View.Details;
            // 
            // imageList
            // 
            this.imageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList.ImageStream")));
            this.imageList.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList.Images.SetKeyName(0, "user_16.png");
            // 
            // groupsPanel
            // 
            this.groupsPanel.Controls.Add(this.usersListView);
            this.groupsPanel.Controls.Add(this.usersCountPanel);
            this.groupsPanel.Controls.Add(this.usersTitlePanel);
            this.groupsPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupsPanel.Location = new System.Drawing.Point(430, 42);
            this.groupsPanel.Name = "groupsPanel";
            this.groupsPanel.Size = new System.Drawing.Size(347, 398);
            this.groupsPanel.TabIndex = 19;
            // 
            // groupUsersListView
            // 
            this.groupUsersListView.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.groupUsersListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.groupUserNameColumnHeader});
            this.groupUsersListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupUsersListView.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.groupUsersListView.FullRowSelect = true;
            this.groupUsersListView.Location = new System.Drawing.Point(0, 46);
            this.groupUsersListView.Name = "groupUsersListView";
            this.groupUsersListView.Size = new System.Drawing.Size(344, 305);
            this.groupUsersListView.SmallImageList = this.imageList;
            this.groupUsersListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.groupUsersListView.TabIndex = 30;
            this.groupUsersListView.UseCompatibleStateImageBehavior = false;
            this.groupUsersListView.View = System.Windows.Forms.View.Details;
            // 
            // groupUserNameColumnHeader
            // 
            this.groupUserNameColumnHeader.Text = "User name";
            this.groupUserNameColumnHeader.Width = 336;
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
            // groupUsersCountPanel
            // 
            this.groupUsersCountPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.groupUsersCountPanel.Controls.Add(this.lblGroupUsersCount);
            this.groupUsersCountPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.groupUsersCountPanel.Location = new System.Drawing.Point(0, 351);
            this.groupUsersCountPanel.Name = "groupUsersCountPanel";
            this.groupUsersCountPanel.Size = new System.Drawing.Size(344, 47);
            this.groupUsersCountPanel.TabIndex = 31;
            // 
            // lblGroupUsersCount
            // 
            this.lblGroupUsersCount.AutoSize = true;
            this.lblGroupUsersCount.Location = new System.Drawing.Point(12, 17);
            this.lblGroupUsersCount.Name = "lblGroupUsersCount";
            this.lblGroupUsersCount.Size = new System.Drawing.Size(38, 13);
            this.lblGroupUsersCount.TabIndex = 8;
            this.lblGroupUsersCount.Text = "Count:";
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
            // moveButtonsPanel
            // 
            this.moveButtonsPanel.Controls.Add(this.moveRightButton);
            this.moveButtonsPanel.Controls.Add(this.moveLeftButton);
            this.moveButtonsPanel.Dock = System.Windows.Forms.DockStyle.Left;
            this.moveButtonsPanel.Location = new System.Drawing.Point(347, 42);
            this.moveButtonsPanel.Name = "moveButtonsPanel";
            this.moveButtonsPanel.Size = new System.Drawing.Size(80, 398);
            this.moveButtonsPanel.TabIndex = 18;
            // 
            // groupNamePanel
            // 
            this.groupNamePanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.groupNamePanel.Controls.Add(this.lblServiceGroupName);
            this.groupNamePanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupNamePanel.Location = new System.Drawing.Point(0, 0);
            this.groupNamePanel.Name = "groupNamePanel";
            this.groupNamePanel.Size = new System.Drawing.Size(344, 46);
            this.groupNamePanel.TabIndex = 0;
            // 
            // lblServiceGroupName
            // 
            this.lblServiceGroupName.AutoSize = true;
            this.lblServiceGroupName.Location = new System.Drawing.Point(12, 15);
            this.lblServiceGroupName.Name = "lblServiceGroupName";
            this.lblServiceGroupName.Size = new System.Drawing.Size(103, 13);
            this.lblServiceGroupName.TabIndex = 6;
            this.lblServiceGroupName.Text = "System group name:";
            // 
            // userGroupsPanel
            // 
            this.userGroupsPanel.Controls.Add(this.groupUsersListView);
            this.userGroupsPanel.Controls.Add(this.groupUsersCountPanel);
            this.userGroupsPanel.Controls.Add(this.groupNamePanel);
            this.userGroupsPanel.Dock = System.Windows.Forms.DockStyle.Left;
            this.userGroupsPanel.Location = new System.Drawing.Point(0, 42);
            this.userGroupsPanel.Name = "userGroupsPanel";
            this.userGroupsPanel.Size = new System.Drawing.Size(344, 398);
            this.userGroupsPanel.TabIndex = 17;
            // 
            // btnCancel
            // 
            this.btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnCancel.Image = ((System.Drawing.Image)(resources.GetObject("btnCancel.Image")));
            this.btnCancel.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnCancel.Location = new System.Drawing.Point(645, 13);
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
            this.btnOK.Location = new System.Drawing.Point(522, 13);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(115, 33);
            this.btnOK.TabIndex = 9;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // bottomPanel
            // 
            this.bottomPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.bottomPanel.Controls.Add(this.btnCancel);
            this.bottomPanel.Controls.Add(this.btnOK);
            this.bottomPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.bottomPanel.Location = new System.Drawing.Point(0, 440);
            this.bottomPanel.Name = "bottomPanel";
            this.bottomPanel.Size = new System.Drawing.Size(777, 59);
            this.bottomPanel.TabIndex = 16;
            // 
            // topPanel
            // 
            this.topPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.topPanel.Controls.Add(this.lblAuthSystem);
            this.topPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.topPanel.Location = new System.Drawing.Point(0, 0);
            this.topPanel.Name = "topPanel";
            this.topPanel.Size = new System.Drawing.Size(777, 42);
            this.topPanel.TabIndex = 15;
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
            // splitter1
            // 
            this.splitter1.Location = new System.Drawing.Point(344, 42);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(3, 398);
            this.splitter1.TabIndex = 20;
            this.splitter1.TabStop = false;
            // 
            // splitter2
            // 
            this.splitter2.Location = new System.Drawing.Point(427, 42);
            this.splitter2.Name = "splitter2";
            this.splitter2.Size = new System.Drawing.Size(3, 398);
            this.splitter2.TabIndex = 21;
            this.splitter2.TabStop = false;
            // 
            // fmGroupUsers
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(777, 499);
            this.Controls.Add(this.groupsPanel);
            this.Controls.Add(this.splitter2);
            this.Controls.Add(this.moveButtonsPanel);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.userGroupsPanel);
            this.Controls.Add(this.bottomPanel);
            this.Controls.Add(this.topPanel);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "fmGroupUsers";
            this.Text = "Users";
            this.usersTitlePanel.ResumeLayout(false);
            this.usersTitlePanel.PerformLayout();
            this.usersCountPanel.ResumeLayout(false);
            this.usersCountPanel.PerformLayout();
            this.groupsPanel.ResumeLayout(false);
            this.groupUsersCountPanel.ResumeLayout(false);
            this.groupUsersCountPanel.PerformLayout();
            this.moveButtonsPanel.ResumeLayout(false);
            this.groupNamePanel.ResumeLayout(false);
            this.groupNamePanel.PerformLayout();
            this.userGroupsPanel.ResumeLayout(false);
            this.bottomPanel.ResumeLayout(false);
            this.topPanel.ResumeLayout(false);
            this.topPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label usersTitleLabel;
        private System.Windows.Forms.Panel usersTitlePanel;
        private System.Windows.Forms.Label lblUsersCount;
        private System.Windows.Forms.Panel usersCountPanel;
        private System.Windows.Forms.ColumnHeader userNameColumnHeader;
        private System.Windows.Forms.ListView usersListView;
        private System.Windows.Forms.ImageList imageList;
        private System.Windows.Forms.Panel groupsPanel;
        private System.Windows.Forms.ListView groupUsersListView;
        private System.Windows.Forms.ColumnHeader groupUserNameColumnHeader;
        private System.Windows.Forms.Button moveLeftButton;
        private System.Windows.Forms.Panel groupUsersCountPanel;
        private System.Windows.Forms.Label lblGroupUsersCount;
        private System.Windows.Forms.Button moveRightButton;
        private System.Windows.Forms.Panel moveButtonsPanel;
        private System.Windows.Forms.Panel groupNamePanel;
        private System.Windows.Forms.Label lblServiceGroupName;
        private System.Windows.Forms.Panel userGroupsPanel;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Panel bottomPanel;
        private System.Windows.Forms.Panel topPanel;
        private System.Windows.Forms.Label lblAuthSystem;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.Splitter splitter2;
    }
}