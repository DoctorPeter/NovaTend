namespace ManagementTool
{
    partial class fmADGroupSettings
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fmADGroupSettings));
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.groupScopeComboBox = new System.Windows.Forms.ComboBox();
            this.groupTypeComboBox = new System.Windows.Forms.ComboBox();
            this.groupScopeLabel = new System.Windows.Forms.Label();
            this.groupTypeLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnCancel
            // 
            this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnCancel.Image = ((System.Drawing.Image)(resources.GetObject("btnCancel.Image")));
            this.btnCancel.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnCancel.Location = new System.Drawing.Point(166, 145);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(153, 39);
            this.btnCancel.TabIndex = 23;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnSave
            // 
            this.btnSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSave.Image = ((System.Drawing.Image)(resources.GetObject("btnSave.Image")));
            this.btnSave.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnSave.Location = new System.Drawing.Point(5, 145);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(155, 39);
            this.btnSave.TabIndex = 22;
            this.btnSave.Text = "Save";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // groupScopeComboBox
            // 
            this.groupScopeComboBox.FormattingEnabled = true;
            this.groupScopeComboBox.Items.AddRange(new object[] {
            "Local",
            "Global",
            "Universal"});
            this.groupScopeComboBox.Location = new System.Drawing.Point(12, 42);
            this.groupScopeComboBox.Name = "groupScopeComboBox";
            this.groupScopeComboBox.Size = new System.Drawing.Size(299, 21);
            this.groupScopeComboBox.TabIndex = 24;
            this.groupScopeComboBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.groupScopeComboBox_KeyDown);
            // 
            // groupTypeComboBox
            // 
            this.groupTypeComboBox.FormattingEnabled = true;
            this.groupTypeComboBox.Items.AddRange(new object[] {
            "Security",
            "Distribution"});
            this.groupTypeComboBox.Location = new System.Drawing.Point(12, 105);
            this.groupTypeComboBox.Name = "groupTypeComboBox";
            this.groupTypeComboBox.Size = new System.Drawing.Size(299, 21);
            this.groupTypeComboBox.TabIndex = 25;
            this.groupTypeComboBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.groupScopeComboBox_KeyDown);
            // 
            // groupScopeLabel
            // 
            this.groupScopeLabel.AutoSize = true;
            this.groupScopeLabel.Location = new System.Drawing.Point(12, 21);
            this.groupScopeLabel.Name = "groupScopeLabel";
            this.groupScopeLabel.Size = new System.Drawing.Size(71, 13);
            this.groupScopeLabel.TabIndex = 26;
            this.groupScopeLabel.Text = "Group scope:";
            // 
            // groupTypeLabel
            // 
            this.groupTypeLabel.AutoSize = true;
            this.groupTypeLabel.Location = new System.Drawing.Point(12, 84);
            this.groupTypeLabel.Name = "groupTypeLabel";
            this.groupTypeLabel.Size = new System.Drawing.Size(62, 13);
            this.groupTypeLabel.TabIndex = 27;
            this.groupTypeLabel.Text = "Group type:";
            // 
            // fmADGroupSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(323, 192);
            this.Controls.Add(this.groupTypeLabel);
            this.Controls.Add(this.groupScopeLabel);
            this.Controls.Add(this.groupTypeComboBox);
            this.Controls.Add(this.groupScopeComboBox);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnSave);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "fmADGroupSettings";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Active directory group settings";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.ComboBox groupScopeComboBox;
        private System.Windows.Forms.ComboBox groupTypeComboBox;
        private System.Windows.Forms.Label groupScopeLabel;
        private System.Windows.Forms.Label groupTypeLabel;
    }
}