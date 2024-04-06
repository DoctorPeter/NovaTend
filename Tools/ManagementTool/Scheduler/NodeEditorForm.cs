/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : NodeEditorForm.cs
///   Description :  Editor of one node of schedule condition tree
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
    /// Form of editor of one node of schedule condition tree
    /// </summary>
    public partial class NodeEditorForm : Form
    {
        // Flag of pressing of button "Cancel"
        public bool Canceled { get; set; }

        // Flag of pressing of button "OK"
        public bool Accepted { get; set; }

        // Schedule condition item
        public ScheduleCondition scheduleCondition { get; set; }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="scheduleCondition">Schedule condition item</param>
        public NodeEditorForm(ScheduleCondition scheduleCondition)
        {
            InitializeComponent();

            this.scheduleCondition = scheduleCondition;

            Canceled = true;
            Accepted = false;
        }

        /// <summary>
        /// Prepare screen according to schedule condition item type
        /// </summary>
        private void PrepareScreen()
        {
            // Set item type value to type combo box
            nodeTypeComboBox.SelectedIndex = (int)(scheduleCondition.conditionItemType - 1);

            // Check item type
            switch(scheduleCondition.conditionItemType)
            {
                // Time period condition
                case ScheduleConditionType.TIME_PERIOD_CONDITION :
                    {
                        firstDateTimePicker.Visible = true;
                        secondDateTimePicker.Visible = true;
                        firstDayComboBox.Visible = false;
                        secondDayComboBox.Visible = false;
                        currentNumericUpDown.Visible = false;
                        maxNumericUpDown.Visible = false;

                        firstDateTimePicker.Format = DateTimePickerFormat.Time;
                        secondDateTimePicker.Format = DateTimePickerFormat.Time;

                        firstDateTimePicker.Value = scheduleCondition.firstDateTime;
                        secondDateTimePicker.Value = scheduleCondition.secondDateTime;

                        firstLabel.Text = "Enter first time value:";
                        secondLabel.Text = "Enter second time value:";

                        this.Height = 235;

                        break;
                    }

                // Date period condition
                case ScheduleConditionType.DATE_PERIOD_CONDITION:
                    {
                        firstDateTimePicker.Visible = true;
                        secondDateTimePicker.Visible = true;
                        firstDayComboBox.Visible = false;
                        secondDayComboBox.Visible = false;
                        currentNumericUpDown.Visible = false;
                        maxNumericUpDown.Visible = false;

                        firstDateTimePicker.Format = DateTimePickerFormat.Long;
                        secondDateTimePicker.Format = DateTimePickerFormat.Long;

                        firstDateTimePicker.Value = scheduleCondition.firstDateTime;
                        secondDateTimePicker.Value = scheduleCondition.secondDateTime;

                        firstLabel.Text = "Enter first date:";
                        secondLabel.Text = "Enter second date:";

                        this.Height = 235;

                        break;
                    }

                // Days period condition
                case ScheduleConditionType.DAYS_PERIOD_CONDITION:
                    {
                        firstDateTimePicker.Visible = false;
                        secondDateTimePicker.Visible = false;
                        firstDayComboBox.Visible = true;
                        secondDayComboBox.Visible = true;
                        currentNumericUpDown.Visible = false;
                        maxNumericUpDown.Visible = false;

                        firstDayComboBox.SelectedIndex = (int)scheduleCondition.firstDay;
                        secondDayComboBox.SelectedIndex = (int)scheduleCondition.secondDay;

                        firstDayComboBox.Location = firstDateTimePicker.Location;
                        secondDayComboBox.Location = secondDateTimePicker.Location;

                        firstLabel.Text = "Enter first day of week:";
                        secondLabel.Text = "Enter second day of week:";

                        this.Height = 235;

                        break;
                    }
                
                // Count condition
                case ScheduleConditionType.COUNT_CONDITION:
                    {
                        firstDateTimePicker.Visible = false;
                        secondDateTimePicker.Visible = false;
                        firstDayComboBox.Visible = false;
                        secondDayComboBox.Visible = false;
                        currentNumericUpDown.Visible = true;
                        maxNumericUpDown.Visible = true;

                        currentNumericUpDown.Value = scheduleCondition.countCurrentValue;
                        maxNumericUpDown.Value = scheduleCondition.countMaxValue;

                        currentNumericUpDown.Location = firstDateTimePicker.Location;
                        maxNumericUpDown.Location = secondDateTimePicker.Location;
                        
                        firstLabel.Text = "Enter current count value:";
                        secondLabel.Text = "Enter maximum count value:";

                        this.Height = 235;

                        break;
                    }

                // Operation NOT, AND, OR
                case ScheduleConditionType.NOT_OPERATION:
                case ScheduleConditionType.AND_OPERATION:
                case ScheduleConditionType.OR_OPERATION:
                    {
                        firstDateTimePicker.Visible = false;
                        secondDateTimePicker.Visible = false;
                        firstDayComboBox.Visible = false;
                        secondDayComboBox.Visible = false;
                        currentNumericUpDown.Visible = false;
                        maxNumericUpDown.Visible = false;

                        this.Height = 160;

                        break;
                    }

            }
        }

        /// <summary>
        /// Form load event handler
        /// </summary>
        private void NodeEditorForm_Load(object sender, EventArgs e)
        {
            PrepareScreen();
        }

        /// <summary>
        /// Node type combo box slected index changed event handler
        /// </summary>
        private void nodeTypeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            scheduleCondition.conditionItemType = (ScheduleConditionType)(nodeTypeComboBox.SelectedIndex + 1);
            PrepareScreen();
        }

        /// <summary>
        /// OK button click
        /// </summary>
        private void OkButton_Click(object sender, EventArgs e)
        {
            scheduleCondition.firstDateTime = firstDateTimePicker.Value;
            scheduleCondition.secondDateTime = secondDateTimePicker.Value;
            scheduleCondition.firstDay = (DayOfWeek)firstDayComboBox.SelectedIndex;
            scheduleCondition.secondDay = (DayOfWeek)secondDayComboBox.SelectedIndex;
            scheduleCondition.countCurrentValue = (int)currentNumericUpDown.Value;
            scheduleCondition.countMaxValue = (int)maxNumericUpDown.Value;

            Canceled = false;
            Accepted = true;
            Close();
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

    }
}
