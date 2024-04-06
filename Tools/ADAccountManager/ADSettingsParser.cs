/// <summary>
///   Solution : NovaTend
///   Project : ADAccountManager.dll
///   Module : ADSettingsParser.cs
///   Description :  implements the methods of class ADSettingsParser
/// </summary>

using System;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ADAccountManagement
{
    /// <summary>
    /// Parser for AD settings string
    /// 
    /// Example of AD settings string: <domain: DC1.LOCAL><defaultOU: OU = WorkUsers, DC=DC1, DC=local>
    /// <defaultRootOU: DC=dc1, DC=local><sUserName:peter><sUserPassword: 4pk2work>
    /// 
    /// Example of AD group settings string: <groupScope: global><groupType: security>
    /// 
    /// </summary>
    public class ADSettingsParser
    {

        /// <summary>
        /// Read one field of AD settings from the input settings string
        /// </summary>
        /// <param name="settingsString">settings string</param>
        /// <returns>AD settings field string</returns>
        private string GetField(string settingsString)
        {
            string fieldString = "";

            int beginPos = settingsString.IndexOf("<");
            int endPos = settingsString.IndexOf(">");

            if ((beginPos != -1) && (endPos != -1) && (beginPos < endPos))
            {
                int fieldLength = endPos - beginPos + 1;
                fieldString = settingsString.Substring(beginPos, fieldLength);
            }

            return fieldString;
        }

        /// <summary>
        /// Read one key marked field of AD settings 
        /// from the input settings string
        /// </summary>
        /// <param name="settingsString">settings string</param>
        /// <param name="keyString">key</param>
        /// <returns>AD settings field string</returns>
        private string GetFieldByKey(string settingsString, string keyString)
        {
            string _settingsString = settingsString;
            _settingsString = Regex.Replace(_settingsString, @"\s+", "");

            string valueString = "";
            bool found = false;
            int pos = -1;

            do
            {
                string fieldString = GetField(_settingsString);
                pos = CheckField(fieldString, keyString);

                if (pos != -1)
                {
                    pos += keyString.Length;
                    valueString = fieldString.Substring(pos);
                    valueString = valueString.Remove(valueString.Length - 1, 1);

                    found = true;
                }
                else
                {
                    pos = _settingsString.IndexOf(fieldString);

                    if (pos != -1)
                        _settingsString = _settingsString.Remove(pos, fieldString.Length);
                }
                                
            } while ((!found) && (_settingsString.Length > 0));

            return valueString;
        }

        /// <summary>
        /// Check field settings string. Compare it with
        /// key marked field string
        /// </summary>
        /// <param name="fieldString">field settings string</param>
        /// <param name="fieldKey">key</param>
        /// <returns>index of key</returns>
        private int CheckField(string fieldString, string fieldKey)
        {
            return fieldString.IndexOf(fieldKey);
        }

        /// <summary>
        /// Get AD service user name
        /// </summary>
        /// <param name="settingsString">settings string</param>
        /// <returns>service user name</returns>
        public string GetServiceUserName(string settingsString)
        {
            return GetFieldByKey(settingsString, "sUserName:");
        }

        /// <summary>
        /// Get AD service user password
        /// </summary>
        /// <param name="settingsString">settings string</param>
        /// <returns>service user password</returns>
        public string GetServiceUserPassword(string settingsString)
        {
            return GetFieldByKey(settingsString, "sUserPassword:");
        }

        /// <summary>
        /// Get AD domain name
        /// </summary>
        /// <param name="settingsString">settings string</param>
        /// <returns>domain name</returns>
        public string GetDomainName(string settingsString)
        {
            return GetFieldByKey(settingsString, "domain:");
        }

        /// <summary>
        /// Get AD default OU for user accounts management
        /// </summary>
        /// <param name="settingsString">settings string</param>
        /// <returns>default OU</returns>
        public string GetDefaultOU(string settingsString)
        {
            return GetFieldByKey(settingsString, "defaultOU:");
        }

        /// <summary>
        /// Get AD default root OU for user accounts management
        /// </summary>
        /// <param name="settingsString">settings string</param>
        /// <returns>default root OU</returns>
        public string GetDefaultRootOU(string settingsString)
        {
            return GetFieldByKey(settingsString, "defaultRootOU:");
        }

        /// <summary>
        /// Get AD group scope
        /// </summary>
        /// <param name="groupSettingsString">group settings string</param>
        /// <returns>group scope name</returns>
        public string GetGroupScope(string groupSettingsString)
        {
            return GetFieldByKey(groupSettingsString, "groupScope:");
        }

        /// <summary>
        /// Get AD group type name
        /// </summary>
        /// <param name="groupSettingsString">group settings string</param>
        /// <returns>group type name string</returns>
        public string GetGroupTypeName(string groupSettingsString)
        {
            return GetFieldByKey(groupSettingsString, "groupType:");
        }
    }
}
