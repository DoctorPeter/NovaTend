/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : BuildScheduleConditionForm.cs
///   Description :  Editor of schedule condition tree
/// </summary>
/// 

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Scheduler
{
    /// <summary>
    /// Form of editor of schedule condition tree
    /// </summary>
    public partial class BuildScheduleConditionForm : Form
    {

        #region Properties

        // Flag of pressing of button "Cancel"
        public bool Canceled { get; set; }

        // Flag of pressing of button "OK"
        public bool Accepted { get; set; }

        
        #endregion

        #region Schedule condition

        // Root of condition tree
        private ScheduleCondition scheduleCondition;
        
        // Schedule condition tree
        public string ScheduleConditionString
        {
            get
            {
                if (scheduleCondition != null)
                {
                    return scheduleCondition.ToString();
                }
                else
                    return String.Empty;
            }
        }

        #endregion

        #region Construction

        /// <summary>
        /// Constructor
        /// </summary>
        public BuildScheduleConditionForm()
        {
            InitializeComponent();
            Canceled = true;
            Accepted = false;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public BuildScheduleConditionForm(string conditionString)
        {
            InitializeComponent();

            // Parse input string
            scheduleCondition = ScheduleCondition.ParseString(conditionString);

            // Build tree view according to condition tree
            FillTreeView(scheduleCondition, null);
            conditionTreeView.ExpandAll();

            Canceled = true;
            Accepted = false;
        }

        #endregion

        #region Checking

        /// <summary>
        /// Check possibility of new node addition
        /// </summary>
        /// <returns>TRUE - if node can be added</returns>
        private bool CheckAddPossibility()
        {
            try
            {
                // If tree view is empty
                if (conditionTreeView.Nodes.Count == 0)
                    return true;
                else
                    // Add child to selected node
                    if (conditionTreeView.SelectedNode != null)
                    {
                        ScheduleCondition currentScheduleCondition = (ScheduleCondition)(conditionTreeView.SelectedNode.Tag);

                        // Check condition item type
                        switch (currentScheduleCondition.conditionItemType)
                        {
                            // Leaf nodes
                            case ScheduleConditionType.TIME_PERIOD_CONDITION:
                            case ScheduleConditionType.DATE_PERIOD_CONDITION:
                            case ScheduleConditionType.DAYS_PERIOD_CONDITION:
                            case ScheduleConditionType.COUNT_CONDITION:
                                {
                                    MessageBox.Show("You can not add child to this node!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                    return false;
                                }

                            // Binary operator
                            case ScheduleConditionType.AND_OPERATION:
                                {
                                    if (conditionTreeView.SelectedNode.Nodes.Count >= 2)
                                    {
                                        MessageBox.Show("AND is a binary operator! You can add only two child!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                        return false;
                                    }

                                    break;
                                }

                            // Binary operator
                            case ScheduleConditionType.OR_OPERATION:
                                {
                                    if (conditionTreeView.SelectedNode.Nodes.Count >= 2)
                                    {
                                        MessageBox.Show("OR is a binary operator! You can add only two child!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                        return false;
                                    }

                                    break;
                                }

                            // Unary operator
                            case ScheduleConditionType.NOT_OPERATION:
                                {
                                    if (conditionTreeView.SelectedNode.Nodes.Count >= 1)
                                    {
                                        MessageBox.Show("NOT is a unary operator! You can add only one child!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                        return false;
                                    }

                                    break;
                                }

                            default: return false;

                        }

                        return true;
                    }
                    else
                        return false;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Check possibility of edits
        /// </summary>
        /// <param name="scheduleCondition">chedule condition item</param>
        /// <param name="treeNode">tree node</param>
        /// <returns>TRUE if edits is correct</returns>
        private bool EditsIsCorrect(ScheduleCondition scheduleCondition, TreeNode treeNode)
        {
            bool result = false;

            // Check condition item type
            switch (scheduleCondition.conditionItemType)
            {
                // Unary poerator
                case ScheduleConditionType.NOT_OPERATION:
                    {
                        if (treeNode.Nodes.Count <= 1) result = true;
                        break;
                    }

                // Binary operator
                case ScheduleConditionType.AND_OPERATION:
                case ScheduleConditionType.OR_OPERATION:
                    {
                        result = true;
                        break;
                    }

                // Laef nodes
                case ScheduleConditionType.TIME_PERIOD_CONDITION:
                case ScheduleConditionType.DATE_PERIOD_CONDITION:
                case ScheduleConditionType.DAYS_PERIOD_CONDITION:
                case ScheduleConditionType.COUNT_CONDITION:
                    {
                        if (treeNode.Nodes.Count == 0) result = true;
                        break;
                    }
            }

            return result;
        }

        #endregion

        #region Tree view

        /// <summary>
        /// Tree view after select event handler
        /// </summary>
        private void conditionTreeView_AfterSelect(object sender, TreeViewEventArgs e)
        {
            conditionTreeView.SelectedImageIndex = e.Node.ImageIndex;
        }

        /// <summary>
        /// Build tree view according to condition tree
        /// </summary>
        /// <param name="scheduleCondition">condition tree node item</param>
        /// <param name="node">tree view node</param>
        private void FillTreeView(ScheduleCondition scheduleCondition, TreeNode node)
        {
            if (scheduleCondition != null)
            {
                TreeNode treeNode = null;

                // If tree view is empty
                if (node == null)
                    treeNode = conditionTreeView.Nodes.Add(scheduleCondition.ToStringOne());
                else
                    treeNode = node.Nodes.Add(scheduleCondition.ToStringOne());
                
                // Tree node image
                treeNode.ImageIndex = ((int)scheduleCondition.conditionItemType) - 1;

                // Schdeule condition item to tree view item Tag
                treeNode.Tag = scheduleCondition;

                // Recursive detour
                FillTreeView(scheduleCondition.left, treeNode);
                FillTreeView(scheduleCondition.right, treeNode);
            }
        }


        /// <summary>
        /// Add new node to tree
        /// </summary>
        /// <param name="type">type of node</param>
        /// <returns>tree node</returns>
        private TreeNode AddNewNode(ScheduleConditionType type)
        {
            TreeNode treeNode = null;

            switch(type)
            {
                // Operators
                case ScheduleConditionType.NOT_OPERATION:
                case ScheduleConditionType.AND_OPERATION:
                case ScheduleConditionType.OR_OPERATION:
                    {
                        // Create schedule condition item
                        ScheduleCondition scheduleCondition = new ScheduleCondition(type, null, null);
                        
                        // Create tree node
                        treeNode = new TreeNode(scheduleCondition.ToStringOne());
                        treeNode.Tag = scheduleCondition;
                        break;
                    }

                // Leaf nodes
                case ScheduleConditionType.TIME_PERIOD_CONDITION:
                case ScheduleConditionType.DATE_PERIOD_CONDITION:
                case ScheduleConditionType.DAYS_PERIOD_CONDITION:
                case ScheduleConditionType.COUNT_CONDITION:
                    {
                        // Create schedule condition item
                        ScheduleCondition scheduleCondition = new ScheduleCondition(type, null, null);

                        // Show node editor
                        NodeEditorForm nodeEditor = new NodeEditorForm(scheduleCondition);
                        nodeEditor.ShowDialog();
                        if (nodeEditor.Accepted)
                        {
                            // Create tree node
                            treeNode = new TreeNode(scheduleCondition.ToStringOne());
                            treeNode.Tag = scheduleCondition;
                        }
                        break;
                    }
            }

            if (treeNode != null)
            {
                // Tree node image
                treeNode.ImageIndex = (int)type - 1;

                // Add root node
                if (conditionTreeView.Nodes.Count == 0)
                {
                    conditionTreeView.Nodes.Add(treeNode);
                    conditionTreeView.ExpandAll();
                }
                else
                    // Add child to selected node
                    if (conditionTreeView.SelectedNode != null)
                    {
                        conditionTreeView.SelectedNode.Nodes.Add(treeNode);
                        conditionTreeView.SelectedNode.ExpandAll();
                    }

                // Select new node
                conditionTreeView.SelectedNode = treeNode;
            }

            return treeNode;
        }

        /// <summary>
        /// Get root of tree view
        /// </summary>
        /// <returns>root node</returns>
        private TreeNode GetRoot()
        {
            TreeNode treeNode = null;

            if (conditionTreeView.Nodes.Count > 0)
            {
                treeNode = conditionTreeView.Nodes[0];

                while (treeNode.Parent != null)
                {
                    treeNode = treeNode.Parent;
                }
            }

            return treeNode;
        }

        /// <summary>
        /// Rebuild condition tree
        /// </summary>
        /// <returns>root of condition tree</returns>
        private ScheduleCondition RemakeRelations()
        {
            // Get tree root
            TreeNode root = GetRoot();
            ScheduleCondition scheduleCondition = null;

            if (root != null)
            {
                // Rebuild condition tree
                RemakeRelations(root);

                // root of condition tree to TAG
                scheduleCondition = (ScheduleCondition)root.Tag;
            }

            return scheduleCondition;
        }

        /// <summary>
        /// Rebuild condition tree
        /// </summary>
        /// <param name="node">node of tree view</param>
        private void RemakeRelations(TreeNode node)
        {
            if (node != null)
            {
                // Get schedule condition item
                ScheduleCondition scheduleCondition = (ScheduleCondition)node.Tag;
                scheduleCondition.left = null;
                scheduleCondition.right = null;

                // Check child count
                if (node.Nodes.Count >= 1)
                {
                    // Left child
                    ScheduleCondition leftCondition = (ScheduleCondition)node.Nodes[0].Tag;
                    scheduleCondition.left = leftCondition;
                    RemakeRelations(node.Nodes[0]);

                    // Check child count
                    if (node.Nodes.Count >= 2)
                    {
                        // Right child
                        ScheduleCondition rightCondition = (ScheduleCondition)node.Nodes[1].Tag;
                        scheduleCondition.right = rightCondition;
                        RemakeRelations(node.Nodes[1]);
                    }
                }
            }
        }

        #endregion

        #region Buttons

        /// <summary>
        /// Add button click
        /// </summary>
        private void addButton_Click(object sender, EventArgs e)
        {
            // If addition is possible
            if (CheckAddPossibility())
            {
                ScheduleConditionType type = ScheduleConditionType.NOT_OPERATION;

                // Get type of new node from button tag
                if (sender is Button)
                    type = (ScheduleConditionType)(Convert.ToInt32((sender as Button).Tag));
                else
                    if (sender is ToolStripMenuItem)
                        type = (ScheduleConditionType)(Convert.ToInt32((sender as ToolStripMenuItem).Tag));

                // Add new node
                AddNewNode(type);
            }
        }

        /// <summary>
        /// OK button click
        /// </summary>
        private void OkButton_Click(object sender, EventArgs e)
        {
            // Rebuild schedule condition tree
            scheduleCondition = RemakeRelations();

            if (scheduleCondition != null)
            {
                // Convert tree to string
                string conditionStr = scheduleCondition.ToString();

                // Check for syntax errors
                scheduleCondition = ScheduleCondition.ParseString(conditionStr);
            }

            // if there are errors!
            if ((scheduleCondition == null) && (conditionTreeView.Nodes.Count > 0))
            {
                MessageBox.Show("Expression of condition was built with errors! Please, try again!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                Canceled = true;
                Accepted = false;
            }
            else
            {
                Canceled = false;
                Accepted = true;
                Close();
            }
        }

        /// <summary>
        /// Cancel button click
        /// </summary>
        private void cancelButton_Click(object sender, EventArgs e)
        {
            Canceled = true;
            Accepted = false;
            Close();
        }

        /// <summary>
        /// Delete button click
        /// </summary>
        private void delButton_Click(object sender, EventArgs e)
        {
            if (conditionTreeView.SelectedNode != null)
                conditionTreeView.Nodes.Remove(conditionTreeView.SelectedNode);
        }

        /// <summary>
        /// Edit button click
        /// </summary>
        private void editButton_Click(object sender, EventArgs e)
        {
            // Edit selected node
            if (conditionTreeView.SelectedNode != null)
            {
                // Get schedule condition item
                ScheduleCondition scheduleCondition = (ScheduleCondition)conditionTreeView.SelectedNode.Tag;

                // Clone schedule condition item
                ScheduleCondition cloneCondition = ScheduleCondition.MakeConditionNode(scheduleCondition.left, scheduleCondition.right,
                                                                                       scheduleCondition.conditionItemType, 
                                                                                       scheduleCondition.firstDateTime, scheduleCondition.secondDateTime,
                                                                                       scheduleCondition.firstDay, scheduleCondition.secondDay,
                                                                                       scheduleCondition.countMaxValue, scheduleCondition.countCurrentValue);

                // Show node editor 
                NodeEditorForm nodeEditor = new NodeEditorForm(cloneCondition);
                nodeEditor.ShowDialog();

                if (nodeEditor.Accepted)
                {
                    // Check possibility of edits
                    if (EditsIsCorrect(cloneCondition, conditionTreeView.SelectedNode))
                    {
                        conditionTreeView.SelectedNode.Text = cloneCondition.ToStringOne();
                        conditionTreeView.SelectedNode.Tag = cloneCondition;
                        conditionTreeView.SelectedNode.ImageIndex = (int)cloneCondition.conditionItemType - 1;
                        conditionTreeView.SelectedImageIndex = conditionTreeView.SelectedNode.ImageIndex;
                    }
                    else
                        MessageBox.Show("You can not make these changes!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }

            }
        }

        #endregion

    }
}
