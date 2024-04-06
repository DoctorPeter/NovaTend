namespace Dashboard
{
    partial class ClientInfoCard
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.clientIDCheckBox = new System.Windows.Forms.CheckBox();
            this.userNameLabel = new System.Windows.Forms.Label();
            this.fullUserNameLabel = new System.Windows.Forms.Label();
            this.sysUserNameLabel = new System.Windows.Forms.Label();
            this.userDowntimeLabel = new System.Windows.Forms.Label();
            this.authSystemNameLabel = new System.Windows.Forms.Label();
            this.userInfoPanel = new System.Windows.Forms.Panel();
            this.UserInfoTitleLabel = new System.Windows.Forms.Label();
            this.softwareInfoPanel = new System.Windows.Forms.Panel();
            this.softwareInfoTextBox = new System.Windows.Forms.TextBox();
            this.softwareInfoTileLabel = new System.Windows.Forms.Label();
            this.hardwareInfoPanel = new System.Windows.Forms.Panel();
            this.hardwareInfoTextBox = new System.Windows.Forms.TextBox();
            this.hardwareInfoTitleLabel = new System.Windows.Forms.Label();
            this.clientInfoSplitContainer1 = new System.Windows.Forms.SplitContainer();
            this.clientInfoSplitContainer2 = new System.Windows.Forms.SplitContainer();
            this.userInfoPanel.SuspendLayout();
            this.softwareInfoPanel.SuspendLayout();
            this.hardwareInfoPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.clientInfoSplitContainer1)).BeginInit();
            this.clientInfoSplitContainer1.Panel1.SuspendLayout();
            this.clientInfoSplitContainer1.Panel2.SuspendLayout();
            this.clientInfoSplitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.clientInfoSplitContainer2)).BeginInit();
            this.clientInfoSplitContainer2.Panel1.SuspendLayout();
            this.clientInfoSplitContainer2.Panel2.SuspendLayout();
            this.clientInfoSplitContainer2.SuspendLayout();
            this.SuspendLayout();
            // 
            // clientIDCheckBox
            // 
            this.clientIDCheckBox.AutoSize = true;
            this.clientIDCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.clientIDCheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.clientIDCheckBox.Location = new System.Drawing.Point(12, 9);
            this.clientIDCheckBox.Name = "clientIDCheckBox";
            this.clientIDCheckBox.Size = new System.Drawing.Size(72, 17);
            this.clientIDCheckBox.TabIndex = 0;
            this.clientIDCheckBox.Text = "Client ID";
            this.clientIDCheckBox.UseVisualStyleBackColor = true;
            // 
            // userNameLabel
            // 
            this.userNameLabel.AutoSize = true;
            this.userNameLabel.ForeColor = System.Drawing.Color.DarkGreen;
            this.userNameLabel.Location = new System.Drawing.Point(7, 37);
            this.userNameLabel.Name = "userNameLabel";
            this.userNameLabel.Size = new System.Drawing.Size(64, 13);
            this.userNameLabel.TabIndex = 1;
            this.userNameLabel.Text = "User name: ";
            // 
            // fullUserNameLabel
            // 
            this.fullUserNameLabel.AutoSize = true;
            this.fullUserNameLabel.ForeColor = System.Drawing.Color.DarkGreen;
            this.fullUserNameLabel.Location = new System.Drawing.Point(7, 63);
            this.fullUserNameLabel.Name = "fullUserNameLabel";
            this.fullUserNameLabel.Size = new System.Drawing.Size(81, 13);
            this.fullUserNameLabel.TabIndex = 2;
            this.fullUserNameLabel.Text = "Full user name: ";
            // 
            // sysUserNameLabel
            // 
            this.sysUserNameLabel.AutoSize = true;
            this.sysUserNameLabel.ForeColor = System.Drawing.Color.DarkGreen;
            this.sysUserNameLabel.Location = new System.Drawing.Point(7, 88);
            this.sysUserNameLabel.Name = "sysUserNameLabel";
            this.sysUserNameLabel.Size = new System.Drawing.Size(99, 13);
            this.sysUserNameLabel.TabIndex = 3;
            this.sysUserNameLabel.Text = "System user name: ";
            // 
            // userDowntimeLabel
            // 
            this.userDowntimeLabel.AutoSize = true;
            this.userDowntimeLabel.ForeColor = System.Drawing.Color.Maroon;
            this.userDowntimeLabel.Location = new System.Drawing.Point(7, 150);
            this.userDowntimeLabel.Name = "userDowntimeLabel";
            this.userDowntimeLabel.Size = new System.Drawing.Size(80, 13);
            this.userDowntimeLabel.TabIndex = 4;
            this.userDowntimeLabel.Text = "User downtime:";
            // 
            // authSystemNameLabel
            // 
            this.authSystemNameLabel.AutoSize = true;
            this.authSystemNameLabel.ForeColor = System.Drawing.Color.MidnightBlue;
            this.authSystemNameLabel.Location = new System.Drawing.Point(7, 118);
            this.authSystemNameLabel.Name = "authSystemNameLabel";
            this.authSystemNameLabel.Size = new System.Drawing.Size(145, 13);
            this.authSystemNameLabel.TabIndex = 5;
            this.authSystemNameLabel.Text = "Authentication system name: ";
            // 
            // userInfoPanel
            // 
            this.userInfoPanel.BackColor = System.Drawing.Color.FloralWhite;
            this.userInfoPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.userInfoPanel.Controls.Add(this.userNameLabel);
            this.userInfoPanel.Controls.Add(this.authSystemNameLabel);
            this.userInfoPanel.Controls.Add(this.UserInfoTitleLabel);
            this.userInfoPanel.Controls.Add(this.fullUserNameLabel);
            this.userInfoPanel.Controls.Add(this.sysUserNameLabel);
            this.userInfoPanel.Controls.Add(this.userDowntimeLabel);
            this.userInfoPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userInfoPanel.Location = new System.Drawing.Point(0, 0);
            this.userInfoPanel.Name = "userInfoPanel";
            this.userInfoPanel.Size = new System.Drawing.Size(350, 181);
            this.userInfoPanel.TabIndex = 12;
            // 
            // UserInfoTitleLabel
            // 
            this.UserInfoTitleLabel.AutoSize = true;
            this.UserInfoTitleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.UserInfoTitleLabel.Location = new System.Drawing.Point(4, 8);
            this.UserInfoTitleLabel.Name = "UserInfoTitleLabel";
            this.UserInfoTitleLabel.Size = new System.Drawing.Size(58, 13);
            this.UserInfoTitleLabel.TabIndex = 0;
            this.UserInfoTitleLabel.Text = "User info";
            // 
            // softwareInfoPanel
            // 
            this.softwareInfoPanel.BackColor = System.Drawing.Color.DarkSeaGreen;
            this.softwareInfoPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.softwareInfoPanel.Controls.Add(this.softwareInfoTextBox);
            this.softwareInfoPanel.Controls.Add(this.softwareInfoTileLabel);
            this.softwareInfoPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.softwareInfoPanel.Location = new System.Drawing.Point(0, 0);
            this.softwareInfoPanel.Name = "softwareInfoPanel";
            this.softwareInfoPanel.Size = new System.Drawing.Size(263, 181);
            this.softwareInfoPanel.TabIndex = 13;
            // 
            // softwareInfoTextBox
            // 
            this.softwareInfoTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.softwareInfoTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.softwareInfoTextBox.Location = new System.Drawing.Point(3, 27);
            this.softwareInfoTextBox.Multiline = true;
            this.softwareInfoTextBox.Name = "softwareInfoTextBox";
            this.softwareInfoTextBox.ReadOnly = true;
            this.softwareInfoTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.softwareInfoTextBox.Size = new System.Drawing.Size(254, 147);
            this.softwareInfoTextBox.TabIndex = 0;
            // 
            // softwareInfoTileLabel
            // 
            this.softwareInfoTileLabel.AutoSize = true;
            this.softwareInfoTileLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.softwareInfoTileLabel.Location = new System.Drawing.Point(4, 8);
            this.softwareInfoTileLabel.Name = "softwareInfoTileLabel";
            this.softwareInfoTileLabel.Size = new System.Drawing.Size(82, 13);
            this.softwareInfoTileLabel.TabIndex = 0;
            this.softwareInfoTileLabel.Text = "Software info";
            // 
            // hardwareInfoPanel
            // 
            this.hardwareInfoPanel.BackColor = System.Drawing.Color.Peru;
            this.hardwareInfoPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.hardwareInfoPanel.Controls.Add(this.hardwareInfoTextBox);
            this.hardwareInfoPanel.Controls.Add(this.hardwareInfoTitleLabel);
            this.hardwareInfoPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.hardwareInfoPanel.Location = new System.Drawing.Point(0, 0);
            this.hardwareInfoPanel.Name = "hardwareInfoPanel";
            this.hardwareInfoPanel.Size = new System.Drawing.Size(276, 181);
            this.hardwareInfoPanel.TabIndex = 14;
            // 
            // hardwareInfoTextBox
            // 
            this.hardwareInfoTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.hardwareInfoTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.hardwareInfoTextBox.Location = new System.Drawing.Point(3, 27);
            this.hardwareInfoTextBox.Multiline = true;
            this.hardwareInfoTextBox.Name = "hardwareInfoTextBox";
            this.hardwareInfoTextBox.ReadOnly = true;
            this.hardwareInfoTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.hardwareInfoTextBox.Size = new System.Drawing.Size(268, 147);
            this.hardwareInfoTextBox.TabIndex = 1;
            // 
            // hardwareInfoTitleLabel
            // 
            this.hardwareInfoTitleLabel.AutoSize = true;
            this.hardwareInfoTitleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.hardwareInfoTitleLabel.Location = new System.Drawing.Point(4, 8);
            this.hardwareInfoTitleLabel.Name = "hardwareInfoTitleLabel";
            this.hardwareInfoTitleLabel.Size = new System.Drawing.Size(86, 13);
            this.hardwareInfoTitleLabel.TabIndex = 0;
            this.hardwareInfoTitleLabel.Text = "Hardware info";
            // 
            // clientInfoSplitContainer1
            // 
            this.clientInfoSplitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.clientInfoSplitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.clientInfoSplitContainer1.Location = new System.Drawing.Point(3, 34);
            this.clientInfoSplitContainer1.Name = "clientInfoSplitContainer1";
            // 
            // clientInfoSplitContainer1.Panel1
            // 
            this.clientInfoSplitContainer1.Panel1.Controls.Add(this.userInfoPanel);
            // 
            // clientInfoSplitContainer1.Panel2
            // 
            this.clientInfoSplitContainer1.Panel2.Controls.Add(this.clientInfoSplitContainer2);
            this.clientInfoSplitContainer1.Size = new System.Drawing.Size(901, 183);
            this.clientInfoSplitContainer1.SplitterDistance = 352;
            this.clientInfoSplitContainer1.TabIndex = 9;
            // 
            // clientInfoSplitContainer2
            // 
            this.clientInfoSplitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.clientInfoSplitContainer2.Location = new System.Drawing.Point(0, 0);
            this.clientInfoSplitContainer2.Name = "clientInfoSplitContainer2";
            // 
            // clientInfoSplitContainer2.Panel1
            // 
            this.clientInfoSplitContainer2.Panel1.Controls.Add(this.softwareInfoPanel);
            // 
            // clientInfoSplitContainer2.Panel2
            // 
            this.clientInfoSplitContainer2.Panel2.Controls.Add(this.hardwareInfoPanel);
            this.clientInfoSplitContainer2.Size = new System.Drawing.Size(543, 181);
            this.clientInfoSplitContainer2.SplitterDistance = 263;
            this.clientInfoSplitContainer2.TabIndex = 0;
            // 
            // ClientInfoCard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.LightGoldenrodYellow;
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Controls.Add(this.clientInfoSplitContainer1);
            this.Controls.Add(this.clientIDCheckBox);
            this.Name = "ClientInfoCard";
            this.Size = new System.Drawing.Size(907, 223);
            this.userInfoPanel.ResumeLayout(false);
            this.userInfoPanel.PerformLayout();
            this.softwareInfoPanel.ResumeLayout(false);
            this.softwareInfoPanel.PerformLayout();
            this.hardwareInfoPanel.ResumeLayout(false);
            this.hardwareInfoPanel.PerformLayout();
            this.clientInfoSplitContainer1.Panel1.ResumeLayout(false);
            this.clientInfoSplitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.clientInfoSplitContainer1)).EndInit();
            this.clientInfoSplitContainer1.ResumeLayout(false);
            this.clientInfoSplitContainer2.Panel1.ResumeLayout(false);
            this.clientInfoSplitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.clientInfoSplitContainer2)).EndInit();
            this.clientInfoSplitContainer2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox clientIDCheckBox;
        private System.Windows.Forms.Label userNameLabel;
        private System.Windows.Forms.Label fullUserNameLabel;
        private System.Windows.Forms.Label sysUserNameLabel;
        private System.Windows.Forms.Label userDowntimeLabel;
        private System.Windows.Forms.Label authSystemNameLabel;
        private System.Windows.Forms.Panel userInfoPanel;
        private System.Windows.Forms.Label UserInfoTitleLabel;
        private System.Windows.Forms.Panel softwareInfoPanel;
        private System.Windows.Forms.TextBox softwareInfoTextBox;
        private System.Windows.Forms.Label softwareInfoTileLabel;
        private System.Windows.Forms.Panel hardwareInfoPanel;
        private System.Windows.Forms.TextBox hardwareInfoTextBox;
        private System.Windows.Forms.Label hardwareInfoTitleLabel;
        private System.Windows.Forms.SplitContainer clientInfoSplitContainer1;
        private System.Windows.Forms.SplitContainer clientInfoSplitContainer2;
    }
}
