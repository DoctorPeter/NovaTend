namespace Scheduler
{
    partial class NodeEditorForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(NodeEditorForm));
            this.bottomPanel = new System.Windows.Forms.Panel();
            this.OkButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.mainPanel = new System.Windows.Forms.Panel();
            this.typeLabel = new System.Windows.Forms.Label();
            this.nodeTypeComboBox = new System.Windows.Forms.ComboBox();
            this.maxNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.currentNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.secondDayComboBox = new System.Windows.Forms.ComboBox();
            this.firstDayComboBox = new System.Windows.Forms.ComboBox();
            this.secondLabel = new System.Windows.Forms.Label();
            this.firstLabel = new System.Windows.Forms.Label();
            this.secondDateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.firstDateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.bottomPanel.SuspendLayout();
            this.mainPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.maxNumericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.currentNumericUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // bottomPanel
            // 
            this.bottomPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.bottomPanel.Controls.Add(this.OkButton);
            this.bottomPanel.Controls.Add(this.cancelButton);
            this.bottomPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.bottomPanel.Location = new System.Drawing.Point(0, 309);
            this.bottomPanel.Name = "bottomPanel";
            this.bottomPanel.Size = new System.Drawing.Size(407, 61);
            this.bottomPanel.TabIndex = 3;
            // 
            // OkButton
            // 
            this.OkButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.OkButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.OkButton.Image = ((System.Drawing.Image)(resources.GetObject("OkButton.Image")));
            this.OkButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.OkButton.Location = new System.Drawing.Point(129, 11);
            this.OkButton.Name = "OkButton";
            this.OkButton.Size = new System.Drawing.Size(131, 38);
            this.OkButton.TabIndex = 1;
            this.OkButton.Text = "OK";
            this.OkButton.UseVisualStyleBackColor = true;
            this.OkButton.Click += new System.EventHandler(this.OkButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cancelButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cancelButton.Image = ((System.Drawing.Image)(resources.GetObject("cancelButton.Image")));
            this.cancelButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.cancelButton.Location = new System.Drawing.Point(266, 11);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(131, 38);
            this.cancelButton.TabIndex = 0;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // mainPanel
            // 
            this.mainPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.mainPanel.Controls.Add(this.typeLabel);
            this.mainPanel.Controls.Add(this.nodeTypeComboBox);
            this.mainPanel.Controls.Add(this.maxNumericUpDown);
            this.mainPanel.Controls.Add(this.currentNumericUpDown);
            this.mainPanel.Controls.Add(this.secondDayComboBox);
            this.mainPanel.Controls.Add(this.firstDayComboBox);
            this.mainPanel.Controls.Add(this.secondLabel);
            this.mainPanel.Controls.Add(this.firstLabel);
            this.mainPanel.Controls.Add(this.secondDateTimePicker);
            this.mainPanel.Controls.Add(this.firstDateTimePicker);
            this.mainPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainPanel.Location = new System.Drawing.Point(0, 0);
            this.mainPanel.Name = "mainPanel";
            this.mainPanel.Size = new System.Drawing.Size(407, 309);
            this.mainPanel.TabIndex = 4;
            // 
            // typeLabel
            // 
            this.typeLabel.AutoSize = true;
            this.typeLabel.Location = new System.Drawing.Point(20, 23);
            this.typeLabel.Name = "typeLabel";
            this.typeLabel.Size = new System.Drawing.Size(73, 13);
            this.typeLabel.TabIndex = 9;
            this.typeLabel.Text = "Type of node:";
            // 
            // nodeTypeComboBox
            // 
            this.nodeTypeComboBox.FormattingEnabled = true;
            this.nodeTypeComboBox.Items.AddRange(new object[] {
            "NOT",
            "AND",
            "OR",
            "TIME",
            "DATE",
            "DAYS",
            "COUNT"});
            this.nodeTypeComboBox.Location = new System.Drawing.Point(176, 20);
            this.nodeTypeComboBox.Name = "nodeTypeComboBox";
            this.nodeTypeComboBox.Size = new System.Drawing.Size(200, 21);
            this.nodeTypeComboBox.TabIndex = 8;
            this.nodeTypeComboBox.SelectedIndexChanged += new System.EventHandler(this.nodeTypeComboBox_SelectedIndexChanged);
            // 
            // maxNumericUpDown
            // 
            this.maxNumericUpDown.Location = new System.Drawing.Point(176, 246);
            this.maxNumericUpDown.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.maxNumericUpDown.Name = "maxNumericUpDown";
            this.maxNumericUpDown.Size = new System.Drawing.Size(200, 20);
            this.maxNumericUpDown.TabIndex = 7;
            // 
            // currentNumericUpDown
            // 
            this.currentNumericUpDown.Location = new System.Drawing.Point(176, 211);
            this.currentNumericUpDown.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.currentNumericUpDown.Name = "currentNumericUpDown";
            this.currentNumericUpDown.Size = new System.Drawing.Size(200, 20);
            this.currentNumericUpDown.TabIndex = 6;
            // 
            // secondDayComboBox
            // 
            this.secondDayComboBox.FormattingEnabled = true;
            this.secondDayComboBox.Items.AddRange(new object[] {
            "SUN",
            "MON",
            "TUE",
            "WED",
            "THU",
            "FRI",
            "SAT"});
            this.secondDayComboBox.Location = new System.Drawing.Point(176, 172);
            this.secondDayComboBox.Name = "secondDayComboBox";
            this.secondDayComboBox.Size = new System.Drawing.Size(203, 21);
            this.secondDayComboBox.TabIndex = 5;
            // 
            // firstDayComboBox
            // 
            this.firstDayComboBox.FormattingEnabled = true;
            this.firstDayComboBox.Items.AddRange(new object[] {
            "SUN",
            "MON",
            "TUE",
            "WED",
            "THU",
            "FRI",
            "SAT"});
            this.firstDayComboBox.Location = new System.Drawing.Point(176, 135);
            this.firstDayComboBox.Name = "firstDayComboBox";
            this.firstDayComboBox.Size = new System.Drawing.Size(200, 21);
            this.firstDayComboBox.TabIndex = 4;
            // 
            // secondLabel
            // 
            this.secondLabel.AutoSize = true;
            this.secondLabel.Location = new System.Drawing.Point(20, 104);
            this.secondLabel.Name = "secondLabel";
            this.secondLabel.Size = new System.Drawing.Size(44, 13);
            this.secondLabel.TabIndex = 3;
            this.secondLabel.Text = "Second";
            // 
            // firstLabel
            // 
            this.firstLabel.AutoSize = true;
            this.firstLabel.Location = new System.Drawing.Point(20, 73);
            this.firstLabel.Name = "firstLabel";
            this.firstLabel.Size = new System.Drawing.Size(26, 13);
            this.firstLabel.TabIndex = 2;
            this.firstLabel.Text = "First";
            // 
            // secondDateTimePicker
            // 
            this.secondDateTimePicker.Location = new System.Drawing.Point(176, 98);
            this.secondDateTimePicker.Name = "secondDateTimePicker";
            this.secondDateTimePicker.Size = new System.Drawing.Size(200, 20);
            this.secondDateTimePicker.TabIndex = 1;
            // 
            // firstDateTimePicker
            // 
            this.firstDateTimePicker.Location = new System.Drawing.Point(176, 67);
            this.firstDateTimePicker.Name = "firstDateTimePicker";
            this.firstDateTimePicker.Size = new System.Drawing.Size(200, 20);
            this.firstDateTimePicker.TabIndex = 0;
            // 
            // NodeEditorForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(407, 370);
            this.Controls.Add(this.mainPanel);
            this.Controls.Add(this.bottomPanel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "NodeEditorForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Node editor";
            this.Load += new System.EventHandler(this.NodeEditorForm_Load);
            this.bottomPanel.ResumeLayout(false);
            this.mainPanel.ResumeLayout(false);
            this.mainPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.maxNumericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.currentNumericUpDown)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel bottomPanel;
        private System.Windows.Forms.Button OkButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Panel mainPanel;
        private System.Windows.Forms.NumericUpDown maxNumericUpDown;
        private System.Windows.Forms.NumericUpDown currentNumericUpDown;
        private System.Windows.Forms.ComboBox secondDayComboBox;
        private System.Windows.Forms.ComboBox firstDayComboBox;
        private System.Windows.Forms.Label secondLabel;
        private System.Windows.Forms.Label firstLabel;
        private System.Windows.Forms.DateTimePicker secondDateTimePicker;
        private System.Windows.Forms.DateTimePicker firstDateTimePicker;
        private System.Windows.Forms.Label typeLabel;
        private System.Windows.Forms.ComboBox nodeTypeComboBox;

    }
}