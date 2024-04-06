namespace ManagementTool
{
    partial class fmAddRevGroup
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fmAddRevGroup));
            this.panel1 = new System.Windows.Forms.Panel();
            this.lblAuthSystem = new System.Windows.Forms.Label();
            this.lblServiceGroupName = new System.Windows.Forms.Label();
            this.lblGroupName = new System.Windows.Forms.Label();
            this.groupNameComboBox = new System.Windows.Forms.ComboBox();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.pwdToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.lblAuthSystem);
            this.panel1.Controls.Add(this.lblServiceGroupName);
            this.panel1.Controls.Add(this.lblGroupName);
            this.panel1.Controls.Add(this.groupNameComboBox);
            this.panel1.Location = new System.Drawing.Point(7, 6);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(380, 127);
            this.panel1.TabIndex = 9;
            // 
            // lblAuthSystem
            // 
            this.lblAuthSystem.AutoSize = true;
            this.lblAuthSystem.Location = new System.Drawing.Point(11, 13);
            this.lblAuthSystem.Name = "lblAuthSystem";
            this.lblAuthSystem.Size = new System.Drawing.Size(113, 13);
            this.lblAuthSystem.TabIndex = 5;
            this.lblAuthSystem.Text = "Authentication system:";
            // 
            // lblServiceGroupName
            // 
            this.lblServiceGroupName.AutoSize = true;
            this.lblServiceGroupName.Location = new System.Drawing.Point(11, 43);
            this.lblServiceGroupName.Name = "lblServiceGroupName";
            this.lblServiceGroupName.Size = new System.Drawing.Size(103, 13);
            this.lblServiceGroupName.TabIndex = 4;
            this.lblServiceGroupName.Text = "System group name:";
            // 
            // lblGroupName
            // 
            this.lblGroupName.AutoSize = true;
            this.lblGroupName.Location = new System.Drawing.Point(8, 83);
            this.lblGroupName.Name = "lblGroupName";
            this.lblGroupName.Size = new System.Drawing.Size(68, 13);
            this.lblGroupName.TabIndex = 1;
            this.lblGroupName.Text = "Group name:";
            // 
            // groupNameComboBox
            // 
            this.groupNameComboBox.FormattingEnabled = true;
            this.groupNameComboBox.Location = new System.Drawing.Point(107, 80);
            this.groupNameComboBox.Name = "groupNameComboBox";
            this.groupNameComboBox.Size = new System.Drawing.Size(263, 21);
            this.groupNameComboBox.TabIndex = 0;
            this.groupNameComboBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.btnOK_KeyDown);
            // 
            // btnCancel
            // 
            this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnCancel.Image = ((System.Drawing.Image)(resources.GetObject("btnCancel.Image")));
            this.btnCancel.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnCancel.Location = new System.Drawing.Point(272, 146);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(115, 33);
            this.btnCancel.TabIndex = 11;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnOK
            // 
            this.btnOK.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnOK.Image = ((System.Drawing.Image)(resources.GetObject("btnOK.Image")));
            this.btnOK.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnOK.Location = new System.Drawing.Point(149, 146);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(115, 33);
            this.btnOK.TabIndex = 10;
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
            // fmAddRevGroup
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(396, 185);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "fmAddRevGroup";
            this.Text = "Link user group";
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label lblAuthSystem;
        private System.Windows.Forms.Label lblServiceGroupName;
        private System.Windows.Forms.Label lblGroupName;
        private System.Windows.Forms.ComboBox groupNameComboBox;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.ToolTip pwdToolTip;
    }
}