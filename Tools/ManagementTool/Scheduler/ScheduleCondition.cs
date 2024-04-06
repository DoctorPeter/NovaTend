/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : ScheduleCondition.cs
///   Description :  schedule condition tree description
/// </summary>
/// 

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using QUT.Gppg;

namespace Scheduler
{
    // Condition types
    public enum ScheduleConditionType
    {
        // Logical operations types

        // Operation NOT
        NOT_OPERATION = 1,

        // Operation AND
        AND_OPERATION = 2,

        // Operation OR
        OR_OPERATION = 3,

        // Leaf types

        // Time period condition. Example [17:00:00 - 18:00:00]
        TIME_PERIOD_CONDITION = 4,

        // Date period condition. Example [08/01/2015 - 08/30/2015]
        DATE_PERIOD_CONDITION = 5,

        // Day period condition. Example [MON - FRI]
        DAYS_PERIOD_CONDITION = 6,

        // Count condition (Current - Maximum). Example [0 - 10]
        COUNT_CONDITION = 7
    }

    /// <summary>
    /// Structute of condition item (node of tree)
    /// </summary>
    public class ScheduleCondition
    {
        #region Properties

        // Item type
        public ScheduleConditionType conditionItemType {get; set;}
        
        // First date
        public DateTime firstDateTime {get; set;}

        // Second date
        public DateTime secondDateTime {get; set;}

        // First day
        public DayOfWeek firstDay {get; set;}

        // Second day
        public DayOfWeek secondDay {get; set;}
        
        // Count maximum value
	    public int countMaxValue {get; set;}

	    // Count current value
	    public int countCurrentValue {get; set;}

        // Left child
        public ScheduleCondition left { get; set; }

        // Right child
        public ScheduleCondition right { get; set; }

        #endregion

        #region Constructor

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="type">condition item type</param>
        /// <param name="left">left child</param>
        /// <param name="right">right child</param>
        public ScheduleCondition(ScheduleConditionType type, ScheduleCondition left, ScheduleCondition right)
        {
            this.conditionItemType = type;
            this.firstDateTime = DateTime.Now;
            this.secondDateTime = DateTime.Now;
            this.left = left;
            this.right = right;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="type">condition type of item</param>
        /// <param name="firstDateTimeValue">first  date time</param>
        /// <param name="secondDateTimeValue">second date time</param>
        /// <param name="left">left child</param>
        /// <param name="right">right child</param>
        public ScheduleCondition(ScheduleConditionType type, DateTime firstDateTimeValue, DateTime secondDateTimeValue, ScheduleCondition left, ScheduleCondition right)
        {
            this.conditionItemType = type;
            this.firstDateTime = firstDateTimeValue;
            this.secondDateTime = secondDateTimeValue;
            this.firstDay = DayOfWeek.Sunday;
            this.secondDay = DayOfWeek.Sunday;
            this.left = left;
            this.right = right;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="firstDayOfWeek">first day of week</param>
        /// <param name="secondDayOfWeek">second day of week</param>
        /// <param name="left">left child</param>
        /// <param name="right">right child</param>
        public ScheduleCondition(DayOfWeek firstDayOfWeek, DayOfWeek secondDayOfWeek, ScheduleCondition left, ScheduleCondition right)
        {
            this.conditionItemType = ScheduleConditionType.DAYS_PERIOD_CONDITION;
            this.firstDay = firstDayOfWeek;
            this.secondDay = secondDayOfWeek;
            this.firstDateTime = DateTime.Now;
            this.secondDateTime = DateTime.Now;
            this.left = left;
            this.right = right;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="countMaxValue">maximum value</param>
        /// <param name="countCurrentValue">current value</param>
        /// <param name="left">left child</param>
        /// <param name="right">right child</param>
        public ScheduleCondition(int countMaxValue, int countCurrentValue, ScheduleCondition left, ScheduleCondition right)
        {
            this.conditionItemType = ScheduleConditionType.COUNT_CONDITION;
            this.countCurrentValue = countCurrentValue;
            this.countMaxValue = countMaxValue;
            this.firstDateTime = DateTime.Now;
            this.secondDateTime = DateTime.Now;
            this.firstDay = DayOfWeek.Sunday;
            this.secondDay = DayOfWeek.Sunday;
            this.left = left;
            this.right = right;
        }

        #endregion

        #region ToString

        // Condition string
        private string conditionString;

        /// <summary>
        /// Convert condition tree to string
        /// </summary>
        /// <returns>condition string</returns>
        override public string ToString()
        {
            conditionString = "";
            ToString(this);
            return conditionString;
        }

        /// <summary>
        /// Convert condition tree to string
        /// </summary>
        private void ToString(ScheduleCondition scheduleCondition)
        {
            if (scheduleCondition != null)
            {
                conditionString = conditionString + "(";

                // NOT operation is unary!
                if (scheduleCondition.conditionItemType == ScheduleConditionType.NOT_OPERATION)
                {
                    conditionString = conditionString + ToStringOne(scheduleCondition);
                    ToString(scheduleCondition.left);
                    ToString(scheduleCondition.right);
                }
                else
                {
                    ToString(scheduleCondition.left);
                    conditionString = conditionString + ToStringOne(scheduleCondition);
                    ToString(scheduleCondition.right);
                }
                conditionString = conditionString + ")";
            }
        }

        /// <summary>
        /// Day of week to string
        /// </summary>
        /// <param name="day">day of week</param>
        /// <returns>day of week string</returns>
        private string DayToString(DayOfWeek day)
        {
            switch (day)
            {
                case DayOfWeek.Sunday: return "SUN";
                case DayOfWeek.Monday: return "MON";
                case DayOfWeek.Tuesday: return "TUE";
                case DayOfWeek.Wednesday: return "WED";
                case DayOfWeek.Thursday: return "THU";
                case DayOfWeek.Friday: return "FRI";
                case DayOfWeek.Saturday: return "SAT";
                default: return String.Empty;
            }
        }

        /// <summary>
        /// Convert condition item to string
        /// </summary>
        /// <returns>condition item string</returns>
        public string ToStringOne()
        {
            return ToStringOne(this);
        }

        /// <summary>
        /// Convert condition item to string
        /// </summary>
        /// <returns>condition item string</returns>
        public string ToStringOne(ScheduleCondition scheduleCondition)
        {
            // result string
            string result = String.Empty;

            // Check item type
            switch (scheduleCondition.conditionItemType)
            {
                // Operation AND
                case ScheduleConditionType.AND_OPERATION:
                    {
                        result = "AND";
                        break;
                    }

                // Operation OR
                case ScheduleConditionType.OR_OPERATION:
                    {
                        result = "OR";
                        break;
                    }

                // Operation NOT
                case ScheduleConditionType.NOT_OPERATION:
                    {
                        result = "NOT";
                        break;
                    }

                // Time period condition. Example TIME[17:00:00 - 18:00:00]
                case ScheduleConditionType.TIME_PERIOD_CONDITION:
                    {
                        string firstTimeStr = scheduleCondition.firstDateTime.ToString(@"HH:mm:ss");
                        string secondTimeStr = scheduleCondition.secondDateTime.ToString(@"HH:mm:ss");
                        result = "TIME[" + firstTimeStr + "-" + secondTimeStr + "]";
                        break;
                    }

                // Date period condition. Example DATE[08/01/2015 - 08/30/2015]
                case ScheduleConditionType.DATE_PERIOD_CONDITION:
                    {
                        string firstDateStr = scheduleCondition.firstDateTime.ToString("MM") + "/" + scheduleCondition.firstDateTime.ToString("dd") + "/" + scheduleCondition.firstDateTime.ToString("yyyy");
                        string secondDateStr = scheduleCondition.secondDateTime.ToString("MM") + "/" + scheduleCondition.secondDateTime.ToString("dd") + "/" + scheduleCondition.secondDateTime.ToString("yyyy");
                        result = "DATE[" + firstDateStr + "-" + secondDateStr + "]";
                        break;
                    }

                // Day period condition. Example DAY[MON - FRI]
                case ScheduleConditionType.DAYS_PERIOD_CONDITION:
                    {
                        string firstDayStr = DayToString(scheduleCondition.firstDay);
                        string secondDayStr = DayToString(scheduleCondition.secondDay);
                        result = "DAY[" + firstDayStr + "-" + secondDayStr + "]";
                        break;
                    }

                // Count condition (Current - Maximum). Example COUNT[0 - 10]
                case ScheduleConditionType.COUNT_CONDITION:
                    {
                        string currentStr = scheduleCondition.countCurrentValue.ToString();
                        string maxStr = scheduleCondition.countMaxValue.ToString();
                        result = "COUNT[" + currentStr + "-" + maxStr + "]";
                        break;
                    }
            }

            return result;
        }

        #endregion

        #region Static

        /// <summary>
        /// Create condition tree node
        /// </summary>
        /// <param name="left">left child</param>
        /// <param name="right">right child</param>
        /// <param name="type">node type</param>
        /// <param name="firstDateTimeValue">first date time value</param>
        /// <param name="secondDateTimeValue">second date time value</param>
        /// <param name="firstDayOfWeek">first day of week</param>
        /// <param name="secondDayOfWeek">second day of week</param>
        /// <param name="countMaxValue">max count value</param>
        /// <param name="countCurrentValue">current count value</param>
        /// <returns>condition tree node</returns>
        static public ScheduleCondition MakeConditionNode(ScheduleCondition left, ScheduleCondition right,
                                                               ScheduleConditionType type,
                                                               DateTime firstDateTimeValue, DateTime secondDateTimeValue,
                                                               DayOfWeek firstDayOfWeek, DayOfWeek secondDayOfWeek,
                                                               int countMaxValue, int countCurrentValue)
        {
            switch (type)
            {
                case ScheduleConditionType.DATE_PERIOD_CONDITION:
                case ScheduleConditionType.TIME_PERIOD_CONDITION: return new ScheduleCondition(type, firstDateTimeValue, secondDateTimeValue, left, right);
                case ScheduleConditionType.DAYS_PERIOD_CONDITION: return new ScheduleCondition(firstDayOfWeek, secondDayOfWeek, left, right);
                case ScheduleConditionType.COUNT_CONDITION: return new ScheduleCondition(countMaxValue, countCurrentValue, left, right);
                default: return new ScheduleCondition(type, left, right);
            }
        }

        /// <summary>
        /// Parse string and build condition tree
        /// </summary>
        /// <param name="input">condition string</param>
        /// <returns>root of condition tree</returns>
        static public ScheduleCondition ParseString(string input)
        {
            Scanner scanner = new Scanner();
            scanner.SetSource(input.ToUpper(), 0);
            Parser parser = new Parser(scanner);
            if (parser.Parse())
                return parser.root;
            else
                return null;
        }

        #endregion
    }
}
