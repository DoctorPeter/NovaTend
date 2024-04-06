namespace ManagementTool
{
    partial class fmChangePassword
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fmChangePassword));
            this.mainPanel = new System.Windows.Forms.Panel();
            this.confirmPwdTextBox = new System.Windows.Forms.TextBox();
            this.newPwdTextBox = new System.Windows.Forms.TextBox();
            this.confirmPwdLabel = new System.Windows.Forms.Label();
            this.newPwdLabel = new System.Windows.Forms.Label();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.pwdToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.mainPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainPanel
            // 
            this.mainPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.mainPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.mainPanel.Controls.Add(this.confirmPwdTextBox);
            this.mainPanel.Controls.Add(this.newPwdTextBox);
            this.mainPanel.Controls.Add(this.confirmPwdLabel);
            this.mainPanel.Controls.Add(this.newPwdLabel);
            this.mainPanel.Location = new System.Drawing.Point(3, 4);
            this.mainPanel.Name = "mainPanel";
            this.mainPanel.Size = new System.Drawing.Size(343, 104);
            this.mainPanel.TabIndex = 0;
            // 
            // confirmPwdTextBox
            // 
            this.confirmPwdTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.confirmPwdTextBox.Location = new System.Drawing.Point(123, 58);
            this.confirmPwdTextBox.Name = "confirmPwdTextBox";
            this.confirmPwdTextBox.PasswordChar = '*';
            this.confirmPwdTextBox.Size = new System.Drawing.Size(200, 20);
            this.confirmPwdTextBox.TabIndex = 3;
            this.confirmPwdTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.newPwdTextBox_KeyDown);
            this.confirmPwdTextBox.MouseHover += new System.EventHandler(this.newPwdTextBox_MouseHover);
            // 
            // newPwdTextBox
            // 
            this.newPwdTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.newPwdTextBox.Location = new System.Drawing.Point(123, 17);
            this.newPwdTextBox.Name = "newPwdTextBox";
            this.newPwdTextBox.PasswordChar = '*';
            this.newPwdTextBox.Size = new System.Drawing.Size(200, 20);
            this.newPwdTextBox.TabIndex = 2;
            this.newPwdTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.newPwdTextBox_KeyDown);
            this.newPwdTextBox.MouseHover += new System.EventHandler(this.newPwdTextBox_MouseHover);
            // 
            // confirmPwdLabel
            // 
            this.confirmPwdLabel.AutoSize = true;
            this.confirmPwdLabel.Location = new System.Drawing.Point(8, 60);
            this.confirmPwdLabel.Name = "confirmPwdLabel";
            this.confirmPwdLabel.Size = new System.Drawing.Size(93, 13);
            this.confirmPwdLabel.TabIndex = 1;
            this.confirmPwdLabel.Text = "Confirm password:";
            // 
            // newPwdLabel
            // 
            this.newPwdLabel.AutoSize = true;
            this.newPwdLabel.Location = new System.Drawing.Point(9, 20);
            this.newPwdLabel.Name = "newPwdLabel";
            this.newPwdLabel.Size = new System.Drawing.Size(80, 13);
            this.newPwdLabel.TabIndex = 0;
            this.newPwdLabel.Text = "New password:";
            // 
            // btnCancel
            // 
            this.btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnCancel.Image = ((System.Drawing.Image)(resources.GetObject("btnCancel.Image")));
            this.btnCancel.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnCancel.Location = new System.Drawing.Point(228, 115);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(115, 33);
            this.btnCancel.TabIndex = 8;
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
            this.btnOK.Location = new System.Drawing.Point(105, 115);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(115, 33);
            this.btnOK.TabIndex = 7;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // pwdToolTip
            // 
            this.pwdToolTip.AutoPopDelay = 2000;
            this.pwdToolTip.InitialDelay = 200;
            this.pwdToolTip.ReshowDelay = 100;
            // 
            // fmChangePassword
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(351, 154);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.mainPanel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "fmChangePassword";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Change password";
            this.mainPanel.ResumeLayout(false);
            this.mainPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel mainPanel;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.TextBox confirmPwdTextBox;
        private System.Windows.Forms.TextBox newPwdTextBox;
        private System.Windows.Forms.Label confirmPwdLabel;
        private System.Windows.Forms.Label newPwdLabel;
        private System.Windows.Forms.ToolTip pwdToolTip;
    }
}