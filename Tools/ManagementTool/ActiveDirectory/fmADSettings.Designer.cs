namespace ManagementTool
{
    partial class fmADSettings
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fmADSettings));
            this.serviceUserPasswordTextBox = new System.Windows.Forms.TextBox();
            this.serviceUserNameTextBox = new System.Windows.Forms.TextBox();
            this.defaultRootOUTextBox = new System.Windows.Forms.TextBox();
            this.defaultOUTextBox = new System.Windows.Forms.TextBox();
            this.domainTextBox = new System.Windows.Forms.TextBox();
            this.lblServiceUserPassword = new System.Windows.Forms.Label();
            this.lblServiceUserName = new System.Windows.Forms.Label();
            this.lblDefaultRootOU = new System.Windows.Forms.Label();
            this.lblDefaultOU = new System.Windows.Forms.Label();
            this.lblDomain = new System.Windows.Forms.Label();
            this.btnSave = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.changePwdLabel = new System.Windows.Forms.Label();
            this.pwdToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.SuspendLayout();
            // 
            // serviceUserPasswordTextBox
            // 
            this.serviceUserPasswordTextBox.BackColor = System.Drawing.SystemColors.Window;
            this.serviceUserPasswordTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.serviceUserPasswordTextBox.Location = new System.Drawing.Point(145, 192);
            this.serviceUserPasswordTextBox.Name = "serviceUserPasswordTextBox";
            this.serviceUserPasswordTextBox.PasswordChar = '*';
            this.serviceUserPasswordTextBox.ReadOnly = true;
            this.serviceUserPasswordTextBox.Size = new System.Drawing.Size(190, 20);
            this.serviceUserPasswordTextBox.TabIndex = 19;
            this.serviceUserPasswordTextBox.Text = "4pk2work";
            this.serviceUserPasswordTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.serviceUserPasswordTextBox_KeyDown);
            this.serviceUserPasswordTextBox.MouseHover += new System.EventHandler(this.serviceUserPasswordTextBox_MouseHover);
            // 
            // serviceUserNameTextBox
            // 
            this.serviceUserNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.serviceUserNameTextBox.Location = new System.Drawing.Point(145, 153);
            this.serviceUserNameTextBox.Name = "serviceUserNameTextBox";
            this.serviceUserNameTextBox.Size = new System.Drawing.Size(190, 20);
            this.serviceUserNameTextBox.TabIndex = 18;
            this.serviceUserNameTextBox.Text = "peter";
            this.serviceUserNameTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.serviceUserPasswordTextBox_KeyDown);
            // 
            // defaultRootOUTextBox
            // 
            this.defaultRootOUTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.defaultRootOUTextBox.Location = new System.Drawing.Point(145, 92);
            this.defaultRootOUTextBox.Name = "defaultRootOUTextBox";
            this.defaultRootOUTextBox.Size = new System.Drawing.Size(190, 20);
            this.defaultRootOUTextBox.TabIndex = 17;
            this.defaultRootOUTextBox.Text = "DC=dc1,DC=local";
            this.defaultRootOUTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.serviceUserPasswordTextBox_KeyDown);
            // 
            // defaultOUTextBox
            // 
            this.defaultOUTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.defaultOUTextBox.Location = new System.Drawing.Point(145, 56);
            this.defaultOUTextBox.Name = "defaultOUTextBox";
            this.defaultOUTextBox.Size = new System.Drawing.Size(190, 20);
            this.defaultOUTextBox.TabIndex = 16;
            this.defaultOUTextBox.Text = "OU=WorkUsers,DC=dc1,DC=local";
            this.defaultOUTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.serviceUserPasswordTextBox_KeyDown);
            // 
            // domainTextBox
            // 
            this.domainTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.domainTextBox.Location = new System.Drawing.Point(145, 20);
            this.domainTextBox.Name = "domainTextBox";
            this.domainTextBox.Size = new System.Drawing.Size(190, 20);
            this.domainTextBox.TabIndex = 15;
            this.domainTextBox.Text = "dc1.local";
            this.domainTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.serviceUserPasswordTextBox_KeyDown);
            // 
            // lblServiceUserPassword
            // 
            this.lblServiceUserPassword.AutoSize = true;
            this.lblServiceUserPassword.Location = new System.Drawing.Point(17, 194);
            this.lblServiceUserPassword.Name = "lblServiceUserPassword";
            this.lblServiceUserPassword.Size = new System.Drawing.Size(117, 13);
            this.lblServiceUserPassword.TabIndex = 14;
            this.lblServiceUserPassword.Text = "Service user password:";
            // 
            // lblServiceUserName
            // 
            this.lblServiceUserName.AutoSize = true;
            this.lblServiceUserName.Location = new System.Drawing.Point(18, 155);
            this.lblServiceUserName.Name = "lblServiceUserName";
            this.lblServiceUserName.Size = new System.Drawing.Size(98, 13);
            this.lblServiceUserName.TabIndex = 13;
            this.lblServiceUserName.Text = "Service user name:";
            // 
            // lblDefaultRootOU
            // 
            this.lblDefaultRootOU.AutoSize = true;
            this.lblDefaultRootOU.Location = new System.Drawing.Point(17, 97);
            this.lblDefaultRootOU.Name = "lblDefaultRootOU";
            this.lblDefaultRootOU.Size = new System.Drawing.Size(84, 13);
            this.lblDefaultRootOU.TabIndex = 12;
            this.lblDefaultRootOU.Text = "Default root OU:";
            // 
            // lblDefaultOU
            // 
            this.lblDefaultOU.AutoSize = true;
            this.lblDefaultOU.Location = new System.Drawing.Point(17, 59);
            this.lblDefaultOU.Name = "lblDefaultOU";
            this.lblDefaultOU.Size = new System.Drawing.Size(63, 13);
            this.lblDefaultOU.TabIndex = 11;
            this.lblDefaultOU.Text = "Default OU:";
            // 
            // lblDomain
            // 
            this.lblDomain.AutoSize = true;
            this.lblDomain.Location = new System.Drawing.Point(18, 20);
            this.lblDomain.Name = "lblDomain";
            this.lblDomain.Size = new System.Drawing.Size(75, 13);
            this.lblDomain.TabIndex = 10;
            this.lblDomain.Text = "Domian name:";
            // 
            // btnSave
            // 
            this.btnSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSave.Image = ((System.Drawing.Image)(resources.GetObject("btnSave.Image")));
            this.btnSave.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnSave.Location = new System.Drawing.Point(21, 249);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(155, 39);
            this.btnSave.TabIndex = 20;
            this.btnSave.Text = "Save";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnCancel.Image = ((System.Drawing.Image)(resources.GetObject("btnCancel.Image")));
            this.btnCancel.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnCancel.Location = new System.Drawing.Point(182, 249);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(153, 39);
            this.btnCancel.TabIndex = 21;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // changePwdLabel
            // 
            this.changePwdLabel.AutoSize = true;
            this.changePwdLabel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.changePwdLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.changePwdLabel.ForeColor = System.Drawing.Color.Blue;
            this.changePwdLabel.Location = new System.Drawing.Point(248, 219);
            this.changePwdLabel.Name = "changePwdLabel";
            this.changePwdLabel.Size = new System.Drawing.Size(92, 13);
            this.changePwdLabel.TabIndex = 22;
            this.changePwdLabel.Text = "Change password";
            this.changePwdLabel.Click += new System.EventHandler(this.changePwdLabel_Click);
            // 
            // pwdToolTip
            // 
            this.pwdToolTip.AutoPopDelay = 2000;
            this.pwdToolTip.InitialDelay = 200;
            this.pwdToolTip.ReshowDelay = 100;
            // 
            // fmADSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(351, 301);
            this.Controls.Add(this.changePwdLabel);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.serviceUserPasswordTextBox);
            this.Controls.Add(this.serviceUserNameTextBox);
            this.Controls.Add(this.defaultRootOUTextBox);
            this.Controls.Add(this.defaultOUTextBox);
            this.Controls.Add(this.domainTextBox);
            this.Controls.Add(this.lblServiceUserPassword);
            this.Controls.Add(this.lblServiceUserName);
            this.Controls.Add(this.lblDefaultRootOU);
            this.Controls.Add(this.lblDefaultOU);
            this.Controls.Add(this.lblDomain);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "fmADSettings";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Active Directory settings";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox serviceUserPasswordTextBox;
        private System.Windows.Forms.TextBox serviceUserNameTextBox;
        private System.Windows.Forms.TextBox defaultRootOUTextBox;
        private System.Windows.Forms.TextBox defaultOUTextBox;
        private System.Windows.Forms.TextBox domainTextBox;
        private System.Windows.Forms.Label lblServiceUserPassword;
        private System.Windows.Forms.Label lblServiceUserName;
        private System.Windows.Forms.Label lblDefaultRootOU;
        private System.Windows.Forms.Label lblDefaultOU;
        private System.Windows.Forms.Label lblDomain;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Label changePwdLabel;
        private System.Windows.Forms.ToolTip pwdToolTip;
    }
}