/// <summary>
///   Solution : NovaTend
///   Project : LicenseManager.dll
///   Module : LicensePointCard.cs
///   Description :  implements the methods of class LicensePointCard
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
    /// Management of license point info
    /// </summary>
    public partial class LicensePointCard : UserControl
    {
        // Private values
        private string _id;
        private string _name;
        private string _description;
        private LicensePointType _type;

        private List<LicensePointValue> _licensePointValues;

        private LicensePoint _licensePoint;

        // Properties

        // License point type
        public LicensePointType type
        {
            get
            {
                _type = (LicensePointType)(licensePointTypeComboBox.SelectedIndex);
                return _type;
            }

            set
            {
                _type = value;
                licensePointTypeComboBox.SelectedIndex = (int)_type;
            }
        }

        // ID
        public string ID
        {
            get
            {
                _id = licensePointIDTextBox.Text;
                return _id;
            }

            set
            {
                _id = value;
                licensePointIDTextBox.Text = _id;
            }
        }

        // Name
        public string Name
        {
            get
            {
                _name = licensePointNameTextBox.Text;
                return _name;
            }

            set
            {
                _name = value;
                licensePointNameTextBox.Text = _name;
            }
        }

        // Description
        public string Description
        {
            get
            {
                _description = licensePointDescriptionTextBox.Text;
                return _description;
            }

            set
            {
                _description = value;
                licensePointDescriptionTextBox.Text = _description;
            }
        }

        // License points list
        public List<LicensePointValue> licensePointValues
        {
            get
            {
                if (_licensePointValues == null)
                    _licensePointValues = new List<LicensePointValue>();
                else
                    _licensePointValues.Clear();

                foreach(Control ctrl in valuesListPanel.Controls)
                    if (ctrl is LicensePointValueCard)
                        _licensePointValues.Add((ctrl as LicensePointValueCard).licensePointValue);

                return _licensePointValues;
            }

            set
            {
                _licensePointValues = value;
            }
        }

        // Value instance property
        public LicensePoint licensePoint
        {
            get
            {
                if (_licensePoint == null)
                {
                    _licensePoint = new LicensePoint(ID, Name, Description, type, licensePointValues);
                }
                else
                {
                    _licensePoint.licensePointID = ID;
                    _licensePoint.licensePointType = type;
                    _licensePoint.licensePointName = Name;
                    _licensePoint.licensePointDescription = Description;
                    _licensePoint.valuesList = licensePointValues;
                }

                return _licensePoint;
            }

            set
            {
                _licensePoint = value;
            }
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public LicensePointCard(LicensePoint licPoint)
        {
            InitializeComponent();

            this._licensePoint = licPoint;

            this.ID = licPoint.licensePointID;
            this.Name = licPoint.licensePointName;
            this.Description = licPoint.licensePointDescription;
            this.type = licPoint.licensePointType;

            this._licensePointValues = licPoint.valuesList;

            CreateLicensePointValuesCards();
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public LicensePointCard(string id, string name, string description, LicensePointType type, List<LicensePointValue> licensePointValues)
        {
            InitializeComponent();

            this.ID = id;
            this.Name = name;
            this.Description = description;
            this.type = type;

            this._licensePointValues = licensePointValues;

            CreateLicensePointValuesCards();
        }

        /// <summary>
        /// Add button click
        /// </summary>
        private void addNewValueButton_Click(object sender, EventArgs e)
        {
            LicensePointValue licensePointValue = new LicensePointValue();
            LicensePointValueCard newCard = new LicensePointValueCard(licensePointValue);
            AddLicensePointValuesCard(newCard);
            valuesListPanel.VerticalScroll.Value = valuesListPanel.VerticalScroll.Maximum;
        }

        /// <summary>
        /// Close button click
        /// </summary>
        private void closeButton_Click(object sender, EventArgs e)
        {
            this.Parent.Controls.Remove(this);
        }

        /// <summary>
        /// Create cards list
        /// </summary>
        private void CreateLicensePointValuesCards()
        {
            valuesListPanel.Controls.Clear();
            foreach (LicensePointValue licensePointValue in _licensePointValues)
                AddLicensePointValuesCard(new LicensePointValueCard(licensePointValue));
            valuesListPanel.VerticalScroll.Value = 0;
        }

        /// <summary>
        /// Add license point value card to panel
        /// </summary>
        /// <param name="newCard">license point value card</param>
        private void AddLicensePointValuesCard(LicensePointValueCard newCard)
        {
            newCard.Width = valuesListPanel.Width - 2;
            newCard.Anchor = (System.Windows.Forms.AnchorStyles)(System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right);
            newCard.Location = GetLicensePointValueCardLocation();
            valuesListPanel.Controls.Add(newCard);
            newCard.Dock = DockStyle.Top;
            newCard.BringToFront();
        }

        /// <summary>
        /// Get location of new license point value card
        /// </summary>
        private Point GetLicensePointValueCardLocation()
        {
            Point result = new Point(0, 0);
            LicensePointValueCard licensePointValueCard = null;

            for (int i = valuesListPanel.Controls.Count - 1; i >= 0; i--)
            {
                if (valuesListPanel.Controls[i] is LicensePointValueCard)
                    licensePointValueCard = (valuesListPanel.Controls[i] as LicensePointValueCard);
            }

            for (int i = valuesListPanel.Controls.Count - 1; i >= 0; i--)
            {
                if ((valuesListPanel.Controls[i] is LicensePointValueCard) &&
                    (valuesListPanel.Controls[i].Location.Y > licensePointValueCard.Location.Y))
                    licensePointValueCard = (valuesListPanel.Controls[i] as LicensePointValueCard);
            }

            if (licensePointValueCard != null)
            {
                result = licensePointValueCard.Location;
                result.Y += licensePointValueCard.Height;
            }

            return result;
        }

        /// <summary>
        /// Clear button click
        /// </summary>
        private void clearValuesListButton_Click(object sender, EventArgs e)
        {
            valuesListPanel.Controls.Clear();
        }
    }
}
