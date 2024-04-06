namespace License
{
    partial class LicensePointCard
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LicensePointCard));
            this.licensePointInfoPanel = new System.Windows.Forms.Panel();
            this.licensePointDescriptionTextBox = new System.Windows.Forms.TextBox();
            this.descriptionLabel = new System.Windows.Forms.Label();
            this.typeLabel = new System.Windows.Forms.Label();
            this.licensePointTypeComboBox = new System.Windows.Forms.ComboBox();
            this.licensePointNameTextBox = new System.Windows.Forms.TextBox();
            this.nameLabel = new System.Windows.Forms.Label();
            this.licensePointIDTextBox = new System.Windows.Forms.TextBox();
            this.idLabel = new System.Windows.Forms.Label();
            this.licensePointValueInfoPanel = new System.Windows.Forms.Panel();
            this.valuesListPanel = new System.Windows.Forms.Panel();
            this.titlePanel = new System.Windows.Forms.Panel();
            this.addNewValueButton = new System.Windows.Forms.Button();
            this.closeButton = new System.Windows.Forms.Button();
            this.valuesListLabel = new System.Windows.Forms.Label();
            this.topPanel = new System.Windows.Forms.Panel();
            this.splitContainer = new System.Windows.Forms.SplitContainer();
            this.clearValuesListButton = new System.Windows.Forms.Button();
            this.licensePointInfoPanel.SuspendLayout();
            this.licensePointValueInfoPanel.SuspendLayout();
            this.titlePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer)).BeginInit();
            this.splitContainer.Panel1.SuspendLayout();
            this.splitContainer.Panel2.SuspendLayout();
            this.splitContainer.SuspendLayout();
            this.SuspendLayout();
            // 
            // licensePointInfoPanel
            // 
            this.licensePointInfoPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.licensePointInfoPanel.Controls.Add(this.licensePointDescriptionTextBox);
            this.licensePointInfoPanel.Controls.Add(this.descriptionLabel);
            this.licensePointInfoPanel.Controls.Add(this.typeLabel);
            this.licensePointInfoPanel.Controls.Add(this.licensePointTypeComboBox);
            this.licensePointInfoPanel.Controls.Add(this.licensePointNameTextBox);
            this.licensePointInfoPanel.Controls.Add(this.nameLabel);
            this.licensePointInfoPanel.Controls.Add(this.licensePointIDTextBox);
            this.licensePointInfoPanel.Controls.Add(this.idLabel);
            this.licensePointInfoPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.licensePointInfoPanel.Location = new System.Drawing.Point(0, 0);
            this.licensePointInfoPanel.Name = "licensePointInfoPanel";
            this.licensePointInfoPanel.Size = new System.Drawing.Size(353, 319);
            this.licensePointInfoPanel.TabIndex = 0;
            // 
            // licensePointDescriptionTextBox
            // 
            this.licensePointDescriptionTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.licensePointDescriptionTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.licensePointDescriptionTextBox.Location = new System.Drawing.Point(13, 146);
            this.licensePointDescriptionTextBox.Multiline = true;
            this.licensePointDescriptionTextBox.Name = "licensePointDescriptionTextBox";
            this.licensePointDescriptionTextBox.Size = new System.Drawing.Size(325, 156);
            this.licensePointDescriptionTextBox.TabIndex = 7;
            // 
            // descriptionLabel
            // 
            this.descriptionLabel.AutoSize = true;
            this.descriptionLabel.Location = new System.Drawing.Point(21, 120);
            this.descriptionLabel.Name = "descriptionLabel";
            this.descriptionLabel.Size = new System.Drawing.Size(63, 13);
            this.descriptionLabel.TabIndex = 6;
            this.descriptionLabel.Text = "Description:";
            // 
            // typeLabel
            // 
            this.typeLabel.AutoSize = true;
            this.typeLabel.Location = new System.Drawing.Point(18, 89);
            this.typeLabel.Name = "typeLabel";
            this.typeLabel.Size = new System.Drawing.Size(34, 13);
            this.typeLabel.TabIndex = 5;
            this.typeLabel.Text = "Type:";
            // 
            // licensePointTypeComboBox
            // 
            this.licensePointTypeComboBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.licensePointTypeComboBox.FormattingEnabled = true;
            this.licensePointTypeComboBox.Items.AddRange(new object[] {
            "Unknown",
            "Exact match",
            "Comparator for greater than or less",
            "Storage of specified value"});
            this.licensePointTypeComboBox.Location = new System.Drawing.Point(62, 86);
            this.licensePointTypeComboBox.Name = "licensePointTypeComboBox";
            this.licensePointTypeComboBox.Size = new System.Drawing.Size(252, 21);
            this.licensePointTypeComboBox.TabIndex = 4;
            // 
            // licensePointNameTextBox
            // 
            this.licensePointNameTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.licensePointNameTextBox.Location = new System.Drawing.Point(62, 55);
            this.licensePointNameTextBox.Name = "licensePointNameTextBox";
            this.licensePointNameTextBox.Size = new System.Drawing.Size(253, 20);
            this.licensePointNameTextBox.TabIndex = 3;
            // 
            // nameLabel
            // 
            this.nameLabel.AutoSize = true;
            this.nameLabel.Location = new System.Drawing.Point(18, 57);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(38, 13);
            this.nameLabel.TabIndex = 2;
            this.nameLabel.Text = "Name:";
            // 
            // licensePointIDTextBox
            // 
            this.licensePointIDTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.licensePointIDTextBox.Location = new System.Drawing.Point(62, 26);
            this.licensePointIDTextBox.Name = "licensePointIDTextBox";
            this.licensePointIDTextBox.Size = new System.Drawing.Size(253, 20);
            this.licensePointIDTextBox.TabIndex = 1;
            // 
            // idLabel
            // 
            this.idLabel.AutoSize = true;
            this.idLabel.Location = new System.Drawing.Point(18, 30);
            this.idLabel.Name = "idLabel";
            this.idLabel.Size = new System.Drawing.Size(21, 13);
            this.idLabel.TabIndex = 0;
            this.idLabel.Text = "ID:";
            // 
            // licensePointValueInfoPanel
            // 
            this.licensePointValueInfoPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.licensePointValueInfoPanel.Controls.Add(this.valuesListPanel);
            this.licensePointValueInfoPanel.Controls.Add(this.titlePanel);
            this.licensePointValueInfoPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.licensePointValueInfoPanel.Location = new System.Drawing.Point(0, 0);
            this.licensePointValueInfoPanel.Name = "licensePointValueInfoPanel";
            this.licensePointValueInfoPanel.Size = new System.Drawing.Size(454, 319);
            this.licensePointValueInfoPanel.TabIndex = 0;
            // 
            // valuesListPanel
            // 
            this.valuesListPanel.AutoScroll = true;
            this.valuesListPanel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.valuesListPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.valuesListPanel.Location = new System.Drawing.Point(0, 43);
            this.valuesListPanel.Name = "valuesListPanel";
            this.valuesListPanel.Size = new System.Drawing.Size(452, 274);
            this.valuesListPanel.TabIndex = 1;
            // 
            // titlePanel
            // 
            this.titlePanel.Controls.Add(this.clearValuesListButton);
            this.titlePanel.Controls.Add(this.addNewValueButton);
            this.titlePanel.Controls.Add(this.closeButton);
            this.titlePanel.Controls.Add(this.valuesListLabel);
            this.titlePanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.titlePanel.Location = new System.Drawing.Point(0, 0);
            this.titlePanel.Name = "titlePanel";
            this.titlePanel.Size = new System.Drawing.Size(452, 43);
            this.titlePanel.TabIndex = 0;
            // 
            // addNewValueButton
            // 
            this.addNewValueButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.addNewValueButton.Image = ((System.Drawing.Image)(resources.GetObject("addNewValueButton.Image")));
            this.addNewValueButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.addNewValueButton.Location = new System.Drawing.Point(141, 10);
            this.addNewValueButton.Name = "addNewValueButton";
            this.addNewValueButton.Size = new System.Drawing.Size(133, 23);
            this.addNewValueButton.TabIndex = 15;
            this.addNewValueButton.Text = "Add new value";
            this.addNewValueButton.UseVisualStyleBackColor = true;
            this.addNewValueButton.Click += new System.EventHandler(this.addNewValueButton_Click);
            // 
            // closeButton
            // 
            this.closeButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.closeButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.closeButton.Image = ((System.Drawing.Image)(resources.GetObject("closeButton.Image")));
            this.closeButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.closeButton.Location = new System.Drawing.Point(424, 3);
            this.closeButton.Name = "closeButton";
            this.closeButton.Size = new System.Drawing.Size(25, 25);
            this.closeButton.TabIndex = 14;
            this.closeButton.UseVisualStyleBackColor = true;
            this.closeButton.Click += new System.EventHandler(this.closeButton_Click);
            // 
            // valuesListLabel
            // 
            this.valuesListLabel.AutoSize = true;
            this.valuesListLabel.Location = new System.Drawing.Point(8, 15);
            this.valuesListLabel.Name = "valuesListLabel";
            this.valuesListLabel.Size = new System.Drawing.Size(127, 13);
            this.valuesListLabel.TabIndex = 0;
            this.valuesListLabel.Text = "License info point values:";
            // 
            // topPanel
            // 
            this.topPanel.BackColor = System.Drawing.Color.LemonChiffon;
            this.topPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.topPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.topPanel.Location = new System.Drawing.Point(0, 0);
            this.topPanel.Name = "topPanel";
            this.topPanel.Size = new System.Drawing.Size(811, 5);
            this.topPanel.TabIndex = 1;
            // 
            // splitContainer
            // 
            this.splitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer.Location = new System.Drawing.Point(0, 5);
            this.splitContainer.Name = "splitContainer";
            // 
            // splitContainer.Panel1
            // 
            this.splitContainer.Panel1.Controls.Add(this.licensePointInfoPanel);
            // 
            // splitContainer.Panel2
            // 
            this.splitContainer.Panel2.Controls.Add(this.licensePointValueInfoPanel);
            this.splitContainer.Size = new System.Drawing.Size(811, 319);
            this.splitContainer.SplitterDistance = 353;
            this.splitContainer.TabIndex = 3;
            // 
            // clearValuesListButton
            // 
            this.clearValuesListButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.clearValuesListButton.Image = ((System.Drawing.Image)(resources.GetObject("clearValuesListButton.Image")));
            this.clearValuesListButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.clearValuesListButton.Location = new System.Drawing.Point(280, 10);
            this.clearValuesListButton.Name = "clearValuesListButton";
            this.clearValuesListButton.Size = new System.Drawing.Size(133, 23);
            this.clearValuesListButton.TabIndex = 16;
            this.clearValuesListButton.Text = "Clear values list";
            this.clearValuesListButton.UseVisualStyleBackColor = true;
            this.clearValuesListButton.Click += new System.EventHandler(this.clearValuesListButton_Click);
            // 
            // LicensePointCard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer);
            this.Controls.Add(this.topPanel);
            this.Name = "LicensePointCard";
            this.Size = new System.Drawing.Size(811, 324);
            this.licensePointInfoPanel.ResumeLayout(false);
            this.licensePointInfoPanel.PerformLayout();
            this.licensePointValueInfoPanel.ResumeLayout(false);
            this.titlePanel.ResumeLayout(false);
            this.titlePanel.PerformLayout();
            this.splitContainer.Panel1.ResumeLayout(false);
            this.splitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer)).EndInit();
            this.splitContainer.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel licensePointInfoPanel;
        private System.Windows.Forms.Panel licensePointValueInfoPanel;
        private System.Windows.Forms.TextBox licensePointIDTextBox;
        private System.Windows.Forms.Label idLabel;
        private System.Windows.Forms.TextBox licensePointNameTextBox;
        private System.Windows.Forms.Label nameLabel;
        private System.Windows.Forms.Label typeLabel;
        private System.Windows.Forms.ComboBox licensePointTypeComboBox;
        private System.Windows.Forms.TextBox licensePointDescriptionTextBox;
        private System.Windows.Forms.Label descriptionLabel;
        private System.Windows.Forms.Panel titlePanel;
        private System.Windows.Forms.Label valuesListLabel;
        private System.Windows.Forms.Button closeButton;
        private System.Windows.Forms.Panel valuesListPanel;
        private System.Windows.Forms.Button addNewValueButton;
        private System.Windows.Forms.Panel topPanel;
        private System.Windows.Forms.SplitContainer splitContainer;
        private System.Windows.Forms.Button clearValuesListButton;
    }
}
