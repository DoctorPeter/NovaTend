namespace License
{
    partial class LicensePointValueCard
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LicensePointValueCard));
            this.valueTypeLabel = new System.Windows.Forms.Label();
            this.licensePointComboBox = new System.Windows.Forms.ComboBox();
            this.licPointValueLabel = new System.Windows.Forms.Label();
            this.valueTextBox = new System.Windows.Forms.TextBox();
            this.valueNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.valueDateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.accessCheckBox = new System.Windows.Forms.CheckBox();
            this.closeButton = new System.Windows.Forms.Button();
            this.topPanel = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.valueNumericUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // valueTypeLabel
            // 
            this.valueTypeLabel.AutoSize = true;
            this.valueTypeLabel.Location = new System.Drawing.Point(15, 30);
            this.valueTypeLabel.Name = "valueTypeLabel";
            this.valueTypeLabel.Size = new System.Drawing.Size(75, 13);
            this.valueTypeLabel.TabIndex = 0;
            this.valueTypeLabel.Text = "Type of value:";
            // 
            // licensePointComboBox
            // 
            this.licensePointComboBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.licensePointComboBox.FormattingEnabled = true;
            this.licensePointComboBox.Items.AddRange(new object[] {
            "Unknown",
            "Integer number",
            "Text data",
            "Date and time"});
            this.licensePointComboBox.Location = new System.Drawing.Point(97, 27);
            this.licensePointComboBox.Name = "licensePointComboBox";
            this.licensePointComboBox.Size = new System.Drawing.Size(278, 21);
            this.licensePointComboBox.TabIndex = 1;
            this.licensePointComboBox.SelectedIndexChanged += new System.EventHandler(this.licensePointComboBox_SelectedIndexChanged);
            // 
            // licPointValueLabel
            // 
            this.licPointValueLabel.AutoSize = true;
            this.licPointValueLabel.Location = new System.Drawing.Point(15, 66);
            this.licPointValueLabel.Name = "licPointValueLabel";
            this.licPointValueLabel.Size = new System.Drawing.Size(37, 13);
            this.licPointValueLabel.TabIndex = 2;
            this.licPointValueLabel.Text = "Value:";
            // 
            // valueTextBox
            // 
            this.valueTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.valueTextBox.Location = new System.Drawing.Point(97, 63);
            this.valueTextBox.Name = "valueTextBox";
            this.valueTextBox.Size = new System.Drawing.Size(278, 20);
            this.valueTextBox.TabIndex = 3;
            // 
            // valueNumericUpDown
            // 
            this.valueNumericUpDown.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.valueNumericUpDown.Location = new System.Drawing.Point(97, 102);
            this.valueNumericUpDown.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.valueNumericUpDown.Name = "valueNumericUpDown";
            this.valueNumericUpDown.Size = new System.Drawing.Size(278, 20);
            this.valueNumericUpDown.TabIndex = 4;
            // 
            // valueDateTimePicker
            // 
            this.valueDateTimePicker.Location = new System.Drawing.Point(97, 144);
            this.valueDateTimePicker.Name = "valueDateTimePicker";
            this.valueDateTimePicker.Size = new System.Drawing.Size(278, 20);
            this.valueDateTimePicker.TabIndex = 5;
            // 
            // accessCheckBox
            // 
            this.accessCheckBox.AutoSize = true;
            this.accessCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.accessCheckBox.Location = new System.Drawing.Point(18, 183);
            this.accessCheckBox.Name = "accessCheckBox";
            this.accessCheckBox.Size = new System.Drawing.Size(73, 17);
            this.accessCheckBox.TabIndex = 6;
            this.accessCheckBox.Text = "accessible";
            this.accessCheckBox.UseVisualStyleBackColor = true;
            // 
            // closeButton
            // 
            this.closeButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.closeButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.closeButton.Image = ((System.Drawing.Image)(resources.GetObject("closeButton.Image")));
            this.closeButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.closeButton.Location = new System.Drawing.Point(402, 8);
            this.closeButton.Name = "closeButton";
            this.closeButton.Size = new System.Drawing.Size(25, 25);
            this.closeButton.TabIndex = 15;
            this.closeButton.UseVisualStyleBackColor = true;
            this.closeButton.Click += new System.EventHandler(this.closeButton_Click);
            // 
            // topPanel
            // 
            this.topPanel.BackColor = System.Drawing.Color.SkyBlue;
            this.topPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.topPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.topPanel.Location = new System.Drawing.Point(0, 0);
            this.topPanel.Name = "topPanel";
            this.topPanel.Size = new System.Drawing.Size(430, 5);
            this.topPanel.TabIndex = 16;
            // 
            // LicensePointValueCard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Controls.Add(this.topPanel);
            this.Controls.Add(this.closeButton);
            this.Controls.Add(this.accessCheckBox);
            this.Controls.Add(this.valueDateTimePicker);
            this.Controls.Add(this.valueNumericUpDown);
            this.Controls.Add(this.valueTextBox);
            this.Controls.Add(this.licPointValueLabel);
            this.Controls.Add(this.licensePointComboBox);
            this.Controls.Add(this.valueTypeLabel);
            this.Name = "LicensePointValueCard";
            this.Size = new System.Drawing.Size(430, 216);
            ((System.ComponentModel.ISupportInitialize)(this.valueNumericUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label valueTypeLabel;
        private System.Windows.Forms.ComboBox licensePointComboBox;
        private System.Windows.Forms.Label licPointValueLabel;
        private System.Windows.Forms.TextBox valueTextBox;
        private System.Windows.Forms.NumericUpDown valueNumericUpDown;
        private System.Windows.Forms.DateTimePicker valueDateTimePicker;
        private System.Windows.Forms.CheckBox accessCheckBox;
        private System.Windows.Forms.Button closeButton;
        private System.Windows.Forms.Panel topPanel;
    }
}
