/// <summary>
///   Solution : NovaTend
///   Project : LicenseManager.dll
///   Module : LicenseManager.cs
///   Description :  implements the methods of class LicenseManager
/// </summary>

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;

using SystemData.ComplexDataType;

namespace License
{
    /// <summary>
    /// License point values types enum
    /// </summary>
    public enum LicensePointValueType
    {
        // Unknown type
        LPV_TYPE_UNKNOWN,

        // Integer value
        LPV_TYPE_INTEGER,

        // String value
        LPV_TYPE_STRING,

        // Datetime value
        LPV_TYPE_DATETIME
    }

    /// <summary>
    /// License point value relations types enum
    /// </summary>
    public enum LicensePointValueRelationType
    {
        // Equal
        REL_TYPE_EQUAL,

        // More
        REL_TYPE_MORE,

        // Less
        REL_TYPE_LESS
    }

    /// <summary>
    /// License point types enum
    /// </summary>
    public enum LicensePointType
    {
        // Unknown type
        LP_TYPE_UNKNOWN,

        // The value is checked for an exact match
        LP_EXACT_MATCH,

        // The value is tested for more or less
        LP_MORE_LESS,

        // The point stores the specified value
        LP_SPECIFIED
    }

    /// <summary>
    /// Class : LicensePointValue
    /// Description : Descriptor of license point value
    /// </summary>
    public class LicensePointValue
    {
        // Type of value
        public LicensePointValueType valueType {get; set;}

        // License point value
        public string value { get; set; }

        // TRUE - if this value is accessible
        public bool accessible { get; set; }

        // Convert to integer
        public int intValue
        {
            get
            {
                int _intValue;
                if (Int32.TryParse(this.value, out _intValue))
                    return _intValue;
                else
                    return 0;
            }

            set
            {
                this.value = value.ToString();
            }
        }

        // Convert to timeinfo structure
        public DateTime tmValue
        {
            get
            {
                DateTime _tmValue;
                if (DateTime.TryParseExact(this.value, "yyyy:MM:dd:HH:mm:ss", CultureInfo.InvariantCulture,  DateTimeStyles.None,  out _tmValue))
                    return _tmValue;
                else
                    return DateTime.Now;
            }

            set
            {
                this.value = value.ToString("yyyy:MM:dd:HH:mm:ss");
            }
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public LicensePointValue()
        {
            valueType = LicensePointValueType.LPV_TYPE_UNKNOWN;
            value = "";
            accessible = false;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public LicensePointValue(LicensePointValueType valueType, string value, bool accessible)
        {
            this.valueType = valueType;
            this.value = value;
            this.accessible = accessible;
        }
    }

    /// <summary>
    /// Class : LicensePoint
    /// Description : Describes one item of license info
    /// </summary>
    public class LicensePoint
    {
        // License point ID
		public string licensePointID {get; set;}

		// License point name
        public string licensePointName { get; set; }

		// License point name
        public string licensePointDescription { get; set; }
		
		// License point type
        public LicensePointType licensePointType { get; set; }

        // Values list
        private List<LicensePointValue> _valuesList;

        // Values list property
        public List<LicensePointValue> valuesList
        {
            get
            {
                if (_valuesList == null)
                    _valuesList = new List<LicensePointValue>();
                return _valuesList;
            }

            set
            {
                _valuesList = value;
            }
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public LicensePoint()
        {
            licensePointType = LicensePointType.LP_TYPE_UNKNOWN;
            licensePointID = "";
            licensePointName = "";
            licensePointDescription = "";
            _valuesList = null;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="licensePointID">License point ID</param>
        /// <param name="licensePointName">License point name</param>
        /// <param name="licensePointDescription">License point description</param>
        /// <param name="licensePointType">License point type</param>
        /// <param name="valuesList">Values list</param>
        public LicensePoint(string licensePointID, string licensePointName, string licensePointDescription, LicensePointType licensePointType, List<LicensePointValue> valuesList)
        {
            this.licensePointID = licensePointID;
            this.licensePointName = licensePointName;
            this.licensePointDescription = licensePointDescription;
            this.licensePointType = licensePointType;
            this.valuesList = valuesList;
        }

        /// <summary>
        /// Check string value
        /// </summary>
        /// <param name="strValue">value</param>
        /// <param name="index">index</param>
        /// <param name="relType">type of relation</param>
        /// <returns>TRUE - if accessible</returns>
        public bool CheckValue(string strValue, int index = -1, LicensePointValueRelationType relType = LicensePointValueRelationType.REL_TYPE_EQUAL)
        {
            bool result = false;

		    switch (licensePointType)
		    {
			    //The value is checked for an exact match
			    case LicensePointType. LP_EXACT_MATCH :
			    // Or point stores the specified value
			    case LicensePointType .LP_SPECIFIED :
			    {
				    // Index specified
				    if ((index >= 0) && (index < valuesList.Count) && (strValue == valuesList[index].value))
				    {
					    result = valuesList[index].accessible;
				    }
				    else
					    // Index not specified - search value
					    for (int i = 0; i < valuesList.Count; i++)
					    {
						    if (strValue == valuesList[index].value)
						    {
							    result = valuesList[i].accessible;
							    break;
						    }
					    }

				    break;
			    }

			    // The value is tested for more or less
			    case LicensePointType.LP_MORE_LESS :
			    {
				    if ((index >= 0) && (index < valuesList.Count))
				    {
					    if (relType == LicensePointValueRelationType.REL_TYPE_MORE)
                            result = (String.Compare(strValue, valuesList[index].value) > 0) && valuesList[index].accessible;
					    else
						    if (relType == LicensePointValueRelationType. REL_TYPE_LESS)
                                result = (String.Compare(strValue, valuesList[index].value) < 0) && valuesList[index].accessible;
				    }

				    break;
			    }
		
		    }

    	    return result;
        }

        /// <summary>
        /// Check value
        /// </summary>
        /// <param name="intValue">int value</param>
        /// <param name="index">int </param>
        /// <param name="relType">relation type</param>
        /// <returns>TRUE - if accessible</returns>
        public bool CheckValue(int intValue, int index = -1, LicensePointValueRelationType relType = LicensePointValueRelationType.REL_TYPE_EQUAL)
        {
            bool result = false;

            switch (licensePointType)
            {
                //The value is checked for an exact match
                case LicensePointType.LP_EXACT_MATCH:
                // Or point stores the specified value
                case LicensePointType.LP_SPECIFIED:
                    {
                        // Index specified
                        if ((index >= 0) && (index < valuesList.Count) && (intValue == valuesList[index].intValue))
                        {
                            result = valuesList[index].accessible;
                        }
                        else
                            // Index not specified - search value
                            for (int i = 0; i < valuesList.Count; i++)
                            {
                                if (intValue == valuesList[index].intValue)
                                {
                                    result = valuesList[i].accessible;
                                    break;
                                }
                            }

                        break;
                    }

                // The value is tested for more or less
                case LicensePointType.LP_MORE_LESS:
                    {
                        if ((index >= 0) && (index < valuesList.Count))
                        {
                            if (relType == LicensePointValueRelationType.REL_TYPE_MORE)
                                result = (intValue > valuesList[index].intValue) && valuesList[index].accessible;
                            else
                                if (relType == LicensePointValueRelationType.REL_TYPE_LESS)
                                    result = (intValue < valuesList[index].intValue) && valuesList[index].accessible;
                        }

                        break;
                    }

            }

            return result;
        }

        /// <summary>
        /// Check value
        /// </summary>
        /// <param name="tmValue">date time structure</param>
        /// <param name="index">index</param>
        /// <param name="relType">relation type</param>
        /// <returns>TRUE - if accessible</returns>
        public bool CheckValue(DateTime tmValue, int index = -1, LicensePointValueRelationType relType = LicensePointValueRelationType.REL_TYPE_EQUAL)
        {
            bool result = false;

            switch (licensePointType)
            {
                //The value is checked for an exact match
                case LicensePointType.LP_EXACT_MATCH:
                // Or point stores the specified value
                case LicensePointType.LP_SPECIFIED:
                    {
                        // Index specified
                        if ((index >= 0) && (index < valuesList.Count) && (tmValue == valuesList[index].tmValue))
                        {
                            result = valuesList[index].accessible;
                        }
                        else
                            // Index not specified - search value
                            for (int i = 0; i < valuesList.Count; i++)
                            {
                                if (tmValue == valuesList[index].tmValue)
                                {
                                    result = valuesList[i].accessible;
                                    break;
                                }
                            }

                        break;
                    }

                // The value is tested for more or less
                case LicensePointType.LP_MORE_LESS:
                    {
                        if ((index >= 0) && (index < valuesList.Count))
                        {
                            if (relType == LicensePointValueRelationType.REL_TYPE_MORE)
                                result = (tmValue > valuesList[index].tmValue) && valuesList[index].accessible;
                            else
                                if (relType == LicensePointValueRelationType.REL_TYPE_LESS)
                                    result = (tmValue < valuesList[index].tmValue) && valuesList[index].accessible;
                        }

                        break;
                    }

            }

            return result;
        }
    }


    /// <summary>
    ///  Class : LicenseManager
    /// Description : Responsible for licensing management
    /// </summary>
    public class LicenseManager
    {
        // New filed of license info
        const int NEW_LICENSE_POINT = 1;

        // New value of current filed of license info
        const int NEW_LICENSE_POINT_VALUE = 2;
        
        // Last value of current filed of license info
        const int LAST_LICENSE_POINT_VALUE = 3;
        
        // License info fields delimits
        private char [] pointDelimit = {'%', '&', '$', '>', '<'};//{ '!', '(', ')', '%', '?', '{', '}' };
        
        // License info values delimits
        private char [] valueDelimit = {'`', '~', '#', '@', '|'};//{'[', ']', '+', '&', '-'};

        // License points list
        private List<LicensePoint> _licensePoints;

        // License points property
        public List<LicensePoint> licensePoints
        {
            get
            {
                if (_licensePoints == null)
                    _licensePoints = new List<LicensePoint>();
                return _licensePoints;
            }

            set
            {
                _licensePoints = value;
            }
        }

        /// <summary>
        /// Parse license string 
        /// </summary>
        /// <param name="licenseString">license string </param>
        /// <returns>TRUE - if success</returns>
        public bool ParseLicenseString(string licenseString)
        {
            try
            {
                char[] licenseStringData = licenseString.ToCharArray();

                licensePoints.Clear();

                int delKind = NEW_LICENSE_POINT_VALUE;
                int pos = 0;

                // While not loaded last value
                while (delKind != LAST_LICENSE_POINT_VALUE)
                {
                    // Create new license point
                    LicensePoint licensePoint = new LicensePoint();
                    licensePoints.Add(licensePoint);

                    delKind = NEW_LICENSE_POINT_VALUE;
                    int valNumber = 0;

                    // Load values of current field
                    while (delKind == NEW_LICENSE_POINT_VALUE)
                    {
                        // Get value
                        char[] outStr = new char[256];
                        pos = GetFieldValue(licenseStringData, pos, ref outStr, ref delKind);
                        string outputString = new string(outStr);
                        outputString = outputString.Trim('\0');

                        // All values are strictly followed in order
                        switch (valNumber)
                        {
                            // Get license point ID
                            case 0:
                                {
                                    licensePoint.licensePointID = outputString;
                                    break;
                                }

                            // Get license point name
                            case 1:
                                {
                                    licensePoint.licensePointName = outputString;
                                    break;
                                }

                            // Get license point description
                            case 2:
                                {
                                    licensePoint.licensePointDescription = outputString;
                                    break;
                                }

                            // Get license point type
                            case 3:
                                {
                                    licensePoint.licensePointType = (LicensePointType)(Convert.ToInt32(outputString, 10));
                                    break;
                                }

                            // Get count of values of license point
                            case 4:
                                {
                                    int valuesCount = Convert.ToInt32(outputString, 10);
                                    for (int i = 0; i < valuesCount; i++)
                                        licensePoint.valuesList.Add(new LicensePointValue());
                                    break;
                                }

                            // Get all values of license info of license point
                            default:
                                {
                                    if ((valNumber % 2) == 1)
                                    {
                                        licensePoint.valuesList[(valNumber - 5) / 2].valueType = (LicensePointValueType)(Convert.ToInt32(outputString, 10));
                                    }
                                    else
                                    {
                                        licensePoint.valuesList[(valNumber - 6) / 2].accessible = outputString.EndsWith("*");
                                        outputString = outputString.Substring(0, outputString.Length - 1);
                                        licensePoint.valuesList[(valNumber - 6) / 2].value = outputString;
                                    }

                                    break;
                                }
                        }

                        valNumber++;
                    }
                }

                licensePoints.Remove(licensePoints.Last());
            }
            catch
            {
                return false;
            }

		    return true;
        }

        /// <summary>
        /// Make license string 
        /// </summary>
        /// <returns>license string</returns>
        public string MakeLicenseString()
        {
            try
            {
                string outStr = "";
                string delStr = "";

                foreach (LicensePoint licensePoint in licensePoints)
                {
                    // ID
                    outStr += licensePoint.licensePointID;
                    delStr = GenerateDelimitString(valueDelimit);
                    outStr += delStr;

                    // Name
                    outStr += licensePoint.licensePointName;
                    delStr = GenerateDelimitString(valueDelimit);
                    outStr += delStr;

                    // Description
                    outStr += licensePoint.licensePointDescription;
                    delStr = GenerateDelimitString(valueDelimit);
                    outStr += delStr;

                    // License point type
                    outStr += ((int)(licensePoint.licensePointType)).ToString();
                    delStr = GenerateDelimitString(valueDelimit);
                    outStr += delStr;

                    // License point values count
                    outStr += licensePoint.valuesList.Count.ToString();
                    delStr = GenerateDelimitString(valueDelimit);
                    outStr += delStr;

                    // Values list
                    foreach (LicensePointValue licensePointValue in licensePoint.valuesList)
                    {
                        // License point value type
                        outStr += ((int)(licensePointValue.valueType)).ToString();
                        delStr = GenerateDelimitString(valueDelimit);
                        outStr += delStr;

                        // Value and access flag
                        outStr += licensePointValue.value;
                        if (licensePointValue.accessible) outStr += "*";
                        else outStr += "^";
                        delStr = GenerateDelimitString(valueDelimit);
                        outStr += delStr;
                    }

                    outStr = outStr.Substring(0, outStr.Length - 1);
                    delStr = GenerateDelimitString(pointDelimit);
                    outStr += delStr;
                }

                return outStr;
            }
            catch
            {
                return String.Empty;
            }

        }
            
        /// <summary>
        /// Find license point value
        /// </summary>
        /// <param name="id">license point ID</param>
        /// <returns>license point index</returns>
        public int FindLicensePoint(string id)
        {
            int index = -1;

            for (int i = 0; i < licensePoints.Count; i++)
            {
                if (licensePoints[i].licensePointID == id)
                {
                    index = i;
                    break;
                }
            }

            return index;
        }

        /// <summary>
        /// Delete license point
        /// </summary>
        /// <param name="id">license point ID</param>
        /// <returns>TRUE - if success</returns>
        public bool DeleteLicensePoint(string id)
        {
            try
            {
                licensePoints.RemoveAt(FindLicensePoint(id));
                return true;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Check license point value by ID
        /// </summary>
        /// <param name="id">license point ID</param>
        /// <param name="strValue">value </param>
        /// <param name="index">index </param>
        /// <param name="relType">relation type</param>
        /// <returns>TRUE - if success</returns>
        public bool CheckLicensePointValue(string id, string strValue, int index = -1, LicensePointValueRelationType relType = LicensePointValueRelationType.REL_TYPE_EQUAL)
        {
            try
            {
                return licensePoints[FindLicensePoint(id)].CheckValue(strValue, index, relType);
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Check license point value by ID
        /// </summary>
        /// <param name="id">license point ID</param>
        /// <param name="intValue">value </param>
        /// <param name="index">index </param>
        /// <param name="relType">relation type</param>
        /// <returns>TRUE - if success</returns>
        public bool CheckLicensePointValue(string id, int intValue, int index = -1, LicensePointValueRelationType relType = LicensePointValueRelationType.REL_TYPE_EQUAL)
        {
            try
            {
                return licensePoints[FindLicensePoint(id)].CheckValue(intValue, index, relType);
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Check license point value by ID
        /// </summary>
        /// <param name="id">license point ID</param>
        /// <param name="tmValue">value </param>
        /// <param name="index">index </param>
        /// <param name="relType">relation type</param>
        /// <returns>TRUE - if success</returns>
        public bool CheckLicensePointValue(string id, DateTime tmValue, int index = -1, LicensePointValueRelationType relType = LicensePointValueRelationType.REL_TYPE_EQUAL)
        {
            try
            {
                return licensePoints[FindLicensePoint(id)].CheckValue(tmValue, index, relType);
            }
            catch
            {
                return false;
            }
        }
        
        /// <summary>
        /// Get license point value
        /// </summary>
        /// <param name="id">license point ID</param>
        /// <param name="index">index</param>
        /// <returns>value</returns>
        public string GetLicensePointValue(string id, int index = 0)
        {
            try
            {
                return licensePoints[FindLicensePoint(id)].valuesList[index].value;
            }
            catch
            {
                return String.Empty;
            }
        }

        /// <summary>
        /// Get license point value
        /// </summary>
        /// <param name="id">license point ID</param>
        /// <param name="index">index</param>
        /// <returns>value</returns>
        public int GetLicensePointIntValue(string id, int index = 0)
        {
            try
            {
                return licensePoints[FindLicensePoint(id)].valuesList[index].intValue;
            }
            catch
            {
                return 0;
            }
        }

        /// <summary>
        /// Get license point value
        /// </summary>
        /// <param name="id">license point ID</param>
        /// <param name="index">index</param>
        /// <returns>value</returns>
        public DateTime GetLicensePointDateTimeValue(string id, int index = 0)
        {
            try
            {
                return licensePoints[FindLicensePoint(id)].valuesList[index].tmValue;
            }
            catch
            {
                return DateTime.Now;
            }
        }
        
        /// <summary>
        /// Define delimit char
        /// </summary>
        /// <param name="c">Input char</param>
        /// <param name="delLst">Delimit symbols list</param>
        /// <returns>Checking result</returns>
        private bool IsDelimit(char c, char[] delLst)
        {
            if (delLst != null)
                for (int i = 0; i < delLst.Length; i++)
                    if (c == delLst[i])
                        return true;

            return false;
        }

        /// <summary>
        /// Get current value of license info field
        /// </summary>
        /// <param name="inpStr">Input string</param>
        /// <param name="pos">Input position</param>
        /// <param name="outStr">Result string</param>
        /// <param name="retFlag">Kind of result</param>
        /// <returns>Current position</returns>
        private int GetFieldValue(char[] inpStr, int pos, ref char[] outStr, ref int retFlag)
        {
            // Check input data
            if ((inpStr == null) || (outStr == null))
                return -1;

            int resPos = pos;
             
            // Pasre input string
            for (int i = pos; i < inpStr.Length; i++)
            {
                resPos = i;

                // Check field delimiters
                if (IsDelimit(inpStr[i], pointDelimit))
                {
                    outStr[i - pos] = '\0';
                    retFlag = NEW_LICENSE_POINT;

                    return resPos + 1;
                }

                // Check value delimiters
                if (IsDelimit(inpStr[i], valueDelimit))
                {
                    outStr[i - pos] = '\0';
                    retFlag = NEW_LICENSE_POINT_VALUE;

                    return resPos + 1;
                }

                outStr[i - pos] = inpStr[i];
            }

            // Last value
            outStr[resPos - pos + 1] = '\0';
            retFlag = LAST_LICENSE_POINT_VALUE;

            return resPos + 1;

        }

        // Generator of random numbers
        private Random randGen;

        /// <summary>
        /// Prepare delimeter as string
        /// </summary>
        /// <param name="delList">Delimiters list</param>
        /// <returns>Result string</returns>
        private string GenerateDelimitString(char [] delList)
        {
            // Get random position
            int pos = (int)randGen.Next(0, delList.Length - 1);
            
            // Prepare result string
            string resultString = new string(delList[pos], 1);

            // Return result string
            return resultString;
        }
        
        /// <summary>
        /// Constructor
        /// </summary>
        public LicenseManager()
        {
            _licensePoints = null;
            randGen = new Random();
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public LicenseManager(List<LicensePoint> licensePointList)
        {
            randGen = new Random();
            this.licensePoints = licensePointList;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public LicenseManager(string licenseString)
        {
            _licensePoints = null;
            randGen = new Random();
            ParseLicenseString(licenseString);
        }
    }
}