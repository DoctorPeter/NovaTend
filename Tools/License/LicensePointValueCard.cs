/// <summary>
///   Solution : NovaTend
///   Project : LicenseManager.dll
///   Module : LicensePointValueCard.cs
///   Description :  implements the methods of class LicensePointValueCard
/// </summary>


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace License
{
    /// <summary>
    /// Management of license point value
    /// </summary>
    public partial class LicensePointValueCard : UserControl
    {
        
        // Private values
        private LicensePointValueType _type;
        private string _strValue;
        private int _intValue;
        private DateTime _tmValue;
        private bool _accessible;

        private LicensePointValue _licensePointValue;


        // Properties

        // License point value type
        public LicensePointValueType type
        {
            get
            {
                _type = (LicensePointValueType)(licensePointComboBox.SelectedIndex);
                return _type;
            }

            set
            {
                _type = value;
                licensePointComboBox.SelectedIndex = (int)_type;
            }
        }

        // String value
        public string strValue
        { 
            get 
            {
                _strValue = valueTextBox.Text;
                return _strValue;
            }

            set 
            {
                _strValue = value;
                valueTextBox.Text = _strValue;
            } 
        }

        // Integer value
        public int intValue
        {
            get
            {
                _intValue = (int)valueNumericUpDown.Value;
                return _intValue;
            }

            set
            {
                _intValue = value;
                valueNumericUpDown.Value = _intValue;
            }
        }

        // Datetime value
        public DateTime tmValue
        {
            get
            {
                _tmValue = valueDateTimePicker.Value;
                return _tmValue;
            }

            set
            {
                _tmValue = value;
                valueDateTimePicker.Value = _tmValue;
            }
        }

        // Access flag
        public bool accessible
        {
            get
            {
                _accessible = accessCheckBox.Checked;
                return _accessible;
            }

            set
            {
                _accessible = value;
                accessCheckBox.Checked = _accessible;
            }
        }

        // Value instance property
        public LicensePointValue licensePointValue
        {
            get
            {
                string result = "";

                switch (type)
                {
                    case LicensePointValueType.LPV_TYPE_UNKNOWN:
                    case LicensePointValueType.LPV_TYPE_STRING:
                        {
                            result = strValue;
                            break;
                        }

                    case LicensePointValueType.LPV_TYPE_INTEGER:
                        {
                            result = intValue.ToString();
                            break;
                        }

                    case LicensePointValueType.LPV_TYPE_DATETIME:
                        {
                            result = tmValue.ToString("yyyy:MM:dd:HH:mm:ss");
                            break;
                        }
                }

                if (_licensePointValue == null)
                {
                    _licensePointValue = new LicensePointValue(type, result, accessible);
                }
                else
                {
                    _licensePointValue.value = result;
                    _licensePointValue.valueType = type;
                    _licensePointValue.accessible = accessible;
                }

                return _licensePointValue;
            }

            set
            {
                _licensePointValue = value;
            }
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public LicensePointValueCard(LicensePointValueType type, string strValue, int intValue, DateTime tmValue, bool accessible)
        {
            InitializeComponent();
            this.Height = 132;

            this.type = type;
            this.strValue = strValue;
            this.intValue = intValue;
            this.tmValue = tmValue;
            this.accessible = accessible;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public LicensePointValueCard(LicensePointValue licensePointValue)
        {
            InitializeComponent();
            this.Height = 132;

            this.type = licensePointValue.valueType;
            this.strValue = licensePointValue.value;
            this.intValue = licensePointValue.intValue;
            this.tmValue = licensePointValue.tmValue;
            this.accessible = licensePointValue.accessible;

            this._licensePointValue = licensePointValue;
        }

        /// <summary>
        /// License point combo box index changed
        /// </summary>
        private void licensePointComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (type)
            {
                case LicensePointValueType.LPV_TYPE_UNKNOWN :
                case LicensePointValueType.LPV_TYPE_STRING :
                    {
                        valueTextBox.Visible = true;
                        valueNumericUpDown.Visible = false;
                        valueDateTimePicker.Visible = false;
                        valueTextBox.Location = new Point(97, 63);
                        accessCheckBox.Location = new Point(18, 102);
                        break;
                    }

                case LicensePointValueType.LPV_TYPE_INTEGER :
                    {
                        valueTextBox.Visible = false;
                        valueDateTimePicker.Visible = false;
                        valueNumericUpDown.Visible = true;
                        valueNumericUpDown.Location = new Point(97, 63);
                        accessCheckBox.Location = new Point(18, 102);
                        break;
                    }

                case LicensePointValueType.LPV_TYPE_DATETIME :
                    {
                        valueTextBox.Visible = false;
                        valueDateTimePicker.Visible = true;
                        valueNumericUpDown.Visible = false;
                        valueDateTimePicker.Location = new Point(97, 63);
                        accessCheckBox.Location = new Point(18, 102);
                        break;
                    }
            }
        }

        /// <summary>
        /// Close button click
        /// </summary>
        private void closeButton_Click(object sender, EventArgs e)
        {
            this.Parent.Controls.Remove(this);
        }


    }
}
