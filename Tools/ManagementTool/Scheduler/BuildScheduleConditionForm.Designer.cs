namespace Scheduler
{
    partial class BuildScheduleConditionForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BuildScheduleConditionForm));
            this.conditionsButtonsPanel = new System.Windows.Forms.Panel();
            this.delButton = new System.Windows.Forms.Button();
            this.editButton = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.addOrButton = new System.Windows.Forms.Button();
            this.addAndButton = new System.Windows.Forms.Button();
            this.addNotButton = new System.Windows.Forms.Button();
            this.splitPanel2 = new System.Windows.Forms.Panel();
            this.addCountButton = new System.Windows.Forms.Button();
            this.addDayButton = new System.Windows.Forms.Button();
            this.addDateButton = new System.Windows.Forms.Button();
            this.addTimeButton = new System.Windows.Forms.Button();
            this.conditionsListPanel = new System.Windows.Forms.Panel();
            this.conditionTreeView = new System.Windows.Forms.TreeView();
            this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.addTimeConditionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addDateConditionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addDayConditionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addCountConditionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.addNOTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addANDToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addORToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.bottomPanel = new System.Windows.Forms.Panel();
            this.OkButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.imageList = new System.Windows.Forms.ImageList(this.components);
            this.conditionsButtonsPanel.SuspendLayout();
            this.conditionsListPanel.SuspendLayout();
            this.contextMenuStrip.SuspendLayout();
            this.bottomPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // conditionsButtonsPanel
            // 
            this.conditionsButtonsPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.conditionsButtonsPanel.Controls.Add(this.delButton);
            this.conditionsButtonsPanel.Controls.Add(this.editButton);
            this.conditionsButtonsPanel.Controls.Add(this.panel1);
            this.conditionsButtonsPanel.Controls.Add(this.addOrButton);
            this.conditionsButtonsPanel.Controls.Add(this.addAndButton);
            this.conditionsButtonsPanel.Controls.Add(this.addNotButton);
            this.conditionsButtonsPanel.Controls.Add(this.splitPanel2);
            this.conditionsButtonsPanel.Controls.Add(this.addCountButton);
            this.conditionsButtonsPanel.Controls.Add(this.addDayButton);
            this.conditionsButtonsPanel.Controls.Add(this.addDateButton);
            this.conditionsButtonsPanel.Controls.Add(this.addTimeButton);
            this.conditionsButtonsPanel.Dock = System.Windows.Forms.DockStyle.Right;
            this.conditionsButtonsPanel.Location = new System.Drawing.Point(441, 0);
            this.conditionsButtonsPanel.Name = "conditionsButtonsPanel";
            this.conditionsButtonsPanel.Size = new System.Drawing.Size(209, 470);
            this.conditionsButtonsPanel.TabIndex = 0;
            // 
            // delButton
            // 
            this.delButton.Dock = System.Windows.Forms.DockStyle.Top;
            this.delButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.delButton.Image = ((System.Drawing.Image)(resources.GetObject("delButton.Image")));
            this.delButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.delButton.Location = new System.Drawing.Point(0, 412);
            this.delButton.Name = "delButton";
            this.delButton.Size = new System.Drawing.Size(207, 50);
            this.delButton.TabIndex = 7;
            this.delButton.Text = "Delete";
            this.delButton.UseVisualStyleBackColor = true;
            this.delButton.Click += new System.EventHandler(this.delButton_Click);
            // 
            // editButton
            // 
            this.editButton.Dock = System.Windows.Forms.DockStyle.Top;
            this.editButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.editButton.Image = ((System.Drawing.Image)(resources.GetObject("editButton.Image")));
            this.editButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.editButton.Location = new System.Drawing.Point(0, 362);
            this.editButton.Name = "editButton";
            this.editButton.Size = new System.Drawing.Size(207, 50);
            this.editButton.TabIndex = 10;
            this.editButton.Text = "Edit";
            this.editButton.UseVisualStyleBackColor = true;
            this.editButton.Click += new System.EventHandler(this.editButton_Click);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 356);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(207, 6);
            this.panel1.TabIndex = 8;
            // 
            // addOrButton
            // 
            this.addOrButton.Dock = System.Windows.Forms.DockStyle.Top;
            this.addOrButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.addOrButton.Image = ((System.Drawing.Image)(resources.GetObject("addOrButton.Image")));
            this.addOrButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.addOrButton.Location = new System.Drawing.Point(0, 306);
            this.addOrButton.Name = "addOrButton";
            this.addOrButton.Size = new System.Drawing.Size(207, 50);
            this.addOrButton.TabIndex = 6;
            this.addOrButton.Tag = "3";
            this.addOrButton.Text = "Add OR";
            this.addOrButton.UseVisualStyleBackColor = true;
            this.addOrButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // addAndButton
            // 
            this.addAndButton.Dock = System.Windows.Forms.DockStyle.Top;
            this.addAndButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.addAndButton.Image = ((System.Drawing.Image)(resources.GetObject("addAndButton.Image")));
            this.addAndButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.addAndButton.Location = new System.Drawing.Point(0, 256);
            this.addAndButton.Name = "addAndButton";
            this.addAndButton.Size = new System.Drawing.Size(207, 50);
            this.addAndButton.TabIndex = 5;
            this.addAndButton.Tag = "2";
            this.addAndButton.Text = "Add AND";
            this.addAndButton.UseVisualStyleBackColor = true;
            this.addAndButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // addNotButton
            // 
            this.addNotButton.Dock = System.Windows.Forms.DockStyle.Top;
            this.addNotButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.addNotButton.Image = ((System.Drawing.Image)(resources.GetObject("addNotButton.Image")));
            this.addNotButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.addNotButton.Location = new System.Drawing.Point(0, 206);
            this.addNotButton.Name = "addNotButton";
            this.addNotButton.Size = new System.Drawing.Size(207, 50);
            this.addNotButton.TabIndex = 4;
            this.addNotButton.Tag = "1";
            this.addNotButton.Text = "Add NOT";
            this.addNotButton.UseVisualStyleBackColor = true;
            this.addNotButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // splitPanel2
            // 
            this.splitPanel2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.splitPanel2.Dock = System.Windows.Forms.DockStyle.Top;
            this.splitPanel2.Location = new System.Drawing.Point(0, 200);
            this.splitPanel2.Name = "splitPanel2";
            this.splitPanel2.Size = new System.Drawing.Size(207, 6);
            this.splitPanel2.TabIndex = 9;
            // 
            // addCountButton
            // 
            this.addCountButton.Dock = System.Windows.Forms.DockStyle.Top;
            this.addCountButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.addCountButton.Image = ((System.Drawing.Image)(resources.GetObject("addCountButton.Image")));
            this.addCountButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.addCountButton.Location = new System.Drawing.Point(0, 150);
            this.addCountButton.Name = "addCountButton";
            this.addCountButton.Size = new System.Drawing.Size(207, 50);
            this.addCountButton.TabIndex = 3;
            this.addCountButton.Tag = "7";
            this.addCountButton.Text = "Add count condition";
            this.addCountButton.UseVisualStyleBackColor = true;
            this.addCountButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // addDayButton
            // 
            this.addDayButton.Dock = System.Windows.Forms.DockStyle.Top;
            this.addDayButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.addDayButton.Image = ((System.Drawing.Image)(resources.GetObject("addDayButton.Image")));
            this.addDayButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.addDayButton.Location = new System.Drawing.Point(0, 100);
            this.addDayButton.Name = "addDayButton";
            this.addDayButton.Size = new System.Drawing.Size(207, 50);
            this.addDayButton.TabIndex = 2;
            this.addDayButton.Tag = "6";
            this.addDayButton.Text = "Add day condition";
            this.addDayButton.UseVisualStyleBackColor = true;
            this.addDayButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // addDateButton
            // 
            this.addDateButton.Dock = System.Windows.Forms.DockStyle.Top;
            this.addDateButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.addDateButton.Image = ((System.Drawing.Image)(resources.GetObject("addDateButton.Image")));
            this.addDateButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.addDateButton.Location = new System.Drawing.Point(0, 50);
            this.addDateButton.Name = "addDateButton";
            this.addDateButton.Size = new System.Drawing.Size(207, 50);
            this.addDateButton.TabIndex = 1;
            this.addDateButton.Tag = "5";
            this.addDateButton.Text = "Add date condition";
            this.addDateButton.UseVisualStyleBackColor = true;
            this.addDateButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // addTimeButton
            // 
            this.addTimeButton.Dock = System.Windows.Forms.DockStyle.Top;
            this.addTimeButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.addTimeButton.Image = ((System.Drawing.Image)(resources.GetObject("addTimeButton.Image")));
            this.addTimeButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.addTimeButton.Location = new System.Drawing.Point(0, 0);
            this.addTimeButton.Name = "addTimeButton";
            this.addTimeButton.Size = new System.Drawing.Size(207, 50);
            this.addTimeButton.TabIndex = 0;
            this.addTimeButton.Tag = "4";
            this.addTimeButton.Text = "Add time condition";
            this.addTimeButton.UseVisualStyleBackColor = true;
            this.addTimeButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // conditionsListPanel
            // 
            this.conditionsListPanel.AutoScroll = true;
            this.conditionsListPanel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.conditionsListPanel.Controls.Add(this.conditionTreeView);
            this.conditionsListPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.conditionsListPanel.Location = new System.Drawing.Point(0, 0);
            this.conditionsListPanel.Name = "conditionsListPanel";
            this.conditionsListPanel.Size = new System.Drawing.Size(441, 470);
            this.conditionsListPanel.TabIndex = 1;
            // 
            // conditionTreeView
            // 
            this.conditionTreeView.ContextMenuStrip = this.contextMenuStrip;
            this.conditionTreeView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.conditionTreeView.HideSelection = false;
            this.conditionTreeView.ImageIndex = 0;
            this.conditionTreeView.ImageList = this.imageList;
            this.conditionTreeView.Location = new System.Drawing.Point(0, 0);
            this.conditionTreeView.Name = "conditionTreeView";
            this.conditionTreeView.SelectedImageIndex = 0;
            this.conditionTreeView.Size = new System.Drawing.Size(437, 466);
            this.conditionTreeView.TabIndex = 0;
            this.conditionTreeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.conditionTreeView_AfterSelect);
            this.conditionTreeView.DoubleClick += new System.EventHandler(this.editButton_Click);
            // 
            // contextMenuStrip
            // 
            this.contextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addTimeConditionToolStripMenuItem,
            this.addDateConditionToolStripMenuItem,
            this.addDayConditionToolStripMenuItem,
            this.addCountConditionToolStripMenuItem,
            this.toolStripSeparator1,
            this.addNOTToolStripMenuItem,
            this.addANDToolStripMenuItem,
            this.addORToolStripMenuItem,
            this.toolStripSeparator2,
            this.editToolStripMenuItem,
            this.deleteToolStripMenuItem});
            this.contextMenuStrip.Name = "contextMenuStrip";
            this.contextMenuStrip.Size = new System.Drawing.Size(185, 214);
            // 
            // addTimeConditionToolStripMenuItem
            // 
            this.addTimeConditionToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("addTimeConditionToolStripMenuItem.Image")));
            this.addTimeConditionToolStripMenuItem.Name = "addTimeConditionToolStripMenuItem";
            this.addTimeConditionToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.addTimeConditionToolStripMenuItem.Tag = "4";
            this.addTimeConditionToolStripMenuItem.Text = "Add time condition";
            this.addTimeConditionToolStripMenuItem.Click += new System.EventHandler(this.addButton_Click);
            // 
            // addDateConditionToolStripMenuItem
            // 
            this.addDateConditionToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("addDateConditionToolStripMenuItem.Image")));
            this.addDateConditionToolStripMenuItem.Name = "addDateConditionToolStripMenuItem";
            this.addDateConditionToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.addDateConditionToolStripMenuItem.Tag = "5";
            this.addDateConditionToolStripMenuItem.Text = "Add date condition";
            this.addDateConditionToolStripMenuItem.Click += new System.EventHandler(this.addButton_Click);
            // 
            // addDayConditionToolStripMenuItem
            // 
            this.addDayConditionToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("addDayConditionToolStripMenuItem.Image")));
            this.addDayConditionToolStripMenuItem.Name = "addDayConditionToolStripMenuItem";
            this.addDayConditionToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.addDayConditionToolStripMenuItem.Tag = "6";
            this.addDayConditionToolStripMenuItem.Text = "Add day condition";
            this.addDayConditionToolStripMenuItem.Click += new System.EventHandler(this.addButton_Click);
            // 
            // addCountConditionToolStripMenuItem
            // 
            this.addCountConditionToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("addCountConditionToolStripMenuItem.Image")));
            this.addCountConditionToolStripMenuItem.Name = "addCountConditionToolStripMenuItem";
            this.addCountConditionToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.addCountConditionToolStripMenuItem.Tag = "7";
            this.addCountConditionToolStripMenuItem.Text = "Add count condition";
            this.addCountConditionToolStripMenuItem.Click += new System.EventHandler(this.addButton_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(181, 6);
            this.toolStripSeparator1.Click += new System.EventHandler(this.addButton_Click);
            // 
            // addNOTToolStripMenuItem
            // 
            this.addNOTToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("addNOTToolStripMenuItem.Image")));
            this.addNOTToolStripMenuItem.Name = "addNOTToolStripMenuItem";
            this.addNOTToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.addNOTToolStripMenuItem.Tag = "1";
            this.addNOTToolStripMenuItem.Text = "Add NOT";
            this.addNOTToolStripMenuItem.Click += new System.EventHandler(this.addButton_Click);
            // 
            // addANDToolStripMenuItem
            // 
            this.addANDToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("addANDToolStripMenuItem.Image")));
            this.addANDToolStripMenuItem.Name = "addANDToolStripMenuItem";
            this.addANDToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.addANDToolStripMenuItem.Tag = "2";
            this.addANDToolStripMenuItem.Text = "Add AND";
            this.addANDToolStripMenuItem.Click += new System.EventHandler(this.addButton_Click);
            // 
            // addORToolStripMenuItem
            // 
            this.addORToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("addORToolStripMenuItem.Image")));
            this.addORToolStripMenuItem.Name = "addORToolStripMenuItem";
            this.addORToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.addORToolStripMenuItem.Tag = "3";
            this.addORToolStripMenuItem.Text = "Add OR";
            this.addORToolStripMenuItem.Click += new System.EventHandler(this.addButton_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(181, 6);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("editToolStripMenuItem.Image")));
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.editToolStripMenuItem.Text = "Edit";
            this.editToolStripMenuItem.Click += new System.EventHandler(this.editButton_Click);
            // 
            // deleteToolStripMenuItem
            // 
            this.deleteToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("deleteToolStripMenuItem.Image")));
            this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
            this.deleteToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.deleteToolStripMenuItem.Text = "Delete";
            this.deleteToolStripMenuItem.Click += new System.EventHandler(this.delButton_Click);
            // 
            // bottomPanel
            // 
            this.bottomPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.bottomPanel.Controls.Add(this.OkButton);
            this.bottomPanel.Controls.Add(this.cancelButton);
            this.bottomPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.bottomPanel.Location = new System.Drawing.Point(0, 470);
            this.bottomPanel.Name = "bottomPanel";
            this.bottomPanel.Size = new System.Drawing.Size(650, 61);
            this.bottomPanel.TabIndex = 2;
            // 
            // OkButton
            // 
            this.OkButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.OkButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.OkButton.Image = ((System.Drawing.Image)(resources.GetObject("OkButton.Image")));
            this.OkButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.OkButton.Location = new System.Drawing.Point(372, 12);
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
            this.cancelButton.Location = new System.Drawing.Point(509, 12);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(131, 38);
            this.cancelButton.TabIndex = 0;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // imageList
            // 
            this.imageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList.ImageStream")));
            this.imageList.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList.Images.SetKeyName(0, "not_16.png");
            this.imageList.Images.SetKeyName(1, "_and_16.png");
            this.imageList.Images.SetKeyName(2, "_or_16.png");
            this.imageList.Images.SetKeyName(3, "clock_16.png");
            this.imageList.Images.SetKeyName(4, "cal_16.png");
            this.imageList.Images.SetKeyName(5, "calendar_16.png");
            this.imageList.Images.SetKeyName(6, "calculator_16.png");
            // 
            // BuildScheduleConditionForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(650, 531);
            this.Controls.Add(this.conditionsListPanel);
            this.Controls.Add(this.conditionsButtonsPanel);
            this.Controls.Add(this.bottomPanel);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "BuildScheduleConditionForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Builder";
            this.conditionsButtonsPanel.ResumeLayout(false);
            this.conditionsListPanel.ResumeLayout(false);
            this.contextMenuStrip.ResumeLayout(false);
            this.bottomPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel conditionsButtonsPanel;
        private System.Windows.Forms.Button addOrButton;
        private System.Windows.Forms.Button addAndButton;
        private System.Windows.Forms.Button addNotButton;
        private System.Windows.Forms.Button addCountButton;
        private System.Windows.Forms.Button addDayButton;
        private System.Windows.Forms.Button addDateButton;
        private System.Windows.Forms.Button addTimeButton;
        private System.Windows.Forms.Panel conditionsListPanel;
        private System.Windows.Forms.TreeView conditionTreeView;
        private System.Windows.Forms.Panel bottomPanel;
        private System.Windows.Forms.Button OkButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button delButton;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem addTimeConditionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addDateConditionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addDayConditionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addCountConditionToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem addNOTToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addANDToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addORToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem;
        private System.Windows.Forms.Panel splitPanel2;
        private System.Windows.Forms.Button editButton;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ImageList imageList;
    }
}