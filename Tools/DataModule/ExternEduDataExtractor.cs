/// <summary>
///   Solution : NovaTend
///   Project : DataModule.dll
///   Module : ExternEduDataExtractor.cs
///   Description :  implements the methods of class ExternEduDataExtractor
/// </summary>

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;

namespace DataModule
{
    /// <summary>
    /// Extractor of external educational data
    /// </summary>
    public class ExternEduDataExtractor
    {
        #region DB connection

        // Connection string
        private string _connectionString;

        // Connection string property
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;

                try
                {
                    connection.Close();
                }
                finally
                {
                    connection.ConnectionString = _connectionString;
                }
            }
        }

        // Connection instance
        private OdbcConnection _connection;

        // Connection property
        public OdbcConnection connection
        {
            get
            {
                if (_connection == null)
                    _connection = new OdbcConnection();

                return _connection;
            }

            set
            {
                _connection = value;
            }
        }

        /// <summary>
        /// Connect to database
        /// </summary>
        /// <returns>TRUE - if connected</returns>
        public bool Connect()
        {
            if (Connected)
                return true;

            try
            {
                connection.Open();
                return true;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Connect to database
        /// </summary>
        /// <param name="connectionString">connection string</param>
        /// <returns>TRUE - if connected</returns>
        public bool Connect(string connectionString)
        {
            this.connectionString = connectionString;
            return Connect();
        }

        /// <summary>
        /// Disconnect from database
        /// </summary>
        /// <returns>TRUE - if disconnected</returns>
        public bool Disconnect()
        {
            if (!Connected)
                return true;

            try
            {
                connection.Close();
                return true;
            }
            catch
            {
                return false;
            }
        }

        // Connected property
        public bool Connected
        {
            get
            {
                return ((connection.State == System.Data.ConnectionState.Open) ||
                        (connection.State == System.Data.ConnectionState.Executing) ||
                        (connection.State == System.Data.ConnectionState.Fetching));
            }
        }

        #endregion

        #region Constructing

        /// <summary>
        /// Constructor
        /// </summary>
        public ExternEduDataExtractor()
        {
            // For future use
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public ExternEduDataExtractor(string connectionString)
        {
            Connect(connectionString);
        }

        /// <summary>
        /// Destructor
        /// </summary>
        ~ExternEduDataExtractor()
        {
            Disconnect();
        }

        #endregion

        #region SQL queries execution

        /// <summary>
        /// Get list of strings from DB
        /// </summary>
        /// <param name="sqlStatemets">SQL query</param>
        /// <returns>list of strings</returns>
        public List<string> GetTextValues(string sqlStatemets)
        {
            try
            {
                // Create DB command
                OdbcCommand command = connection.CreateCommand();

                // Set text of SQL query
                command.CommandText = sqlStatemets;

                // Execute query
                OdbcDataReader dataReader = command.ExecuteReader();

                // Create result list
                List<string> resultList = new List<string>();

                // Check fields count
                if (dataReader.FieldCount > 0)
                {
                    // Retrieve of strings from DB
                    while (dataReader.Read())
                    {
                        resultList.Add(dataReader.GetString(0));
                    }
                }

                dataReader.Close();
                command.Dispose();

                return resultList;
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Class of two typed values: text and image
        /// </summary>
        public class TextAndImageValue
        {
            // Text value
            public string text;

            // Image value
            public byte[] image;
        }

        /// <summary>
        /// Get text and image values from DB
        /// </summary>
        /// <param name="sqlStatemets">SQL query</param>
        /// <returns>List of values</returns>
        public List<TextAndImageValue> GetTextAndImageValues(string sqlStatemets)
        {
            try
            {
                // Create DB command
                OdbcCommand command = connection.CreateCommand();

                // Set text of SQL query
                command.CommandText = sqlStatemets;

                // Execute query
                OdbcDataReader dataReader = command.ExecuteReader();

                // Create result list
                List<TextAndImageValue> resultList = new List<TextAndImageValue>();

                // Check fields count
                if (dataReader.FieldCount > 0)
                {
                    // Retrieve of values from DB
                    while (dataReader.Read())
                    {
                        TextAndImageValue newValue = new TextAndImageValue();
                        newValue.text = dataReader.GetString(0);
                        newValue.image = (byte[])dataReader.GetValue(1);
                        resultList.Add(newValue);
                    }
                }

                dataReader.Close();
                command.Dispose();

                return resultList;
            }
            catch
            {
                return null;
            }
        }

        #endregion

        #region Educational data

        /// <summary>
        /// Get names of education categories
        /// </summary>
        /// <param name="sqlStatement">SQL query</param>
        /// <returns>list of education categories names</returns>
        public List<string> GetEduCategories(string sqlStatement)
        {
            return GetTextValues(sqlStatement);
        }

        /// <summary>
        /// Get values foe eduction lessons:
        /// images and text strings
        /// </summary>
        /// <param name="sqlStatement">SQL query</param>
        /// <returns>list of education lessons values</returns>
        public List<TextAndImageValue> GetEduLessons(string sqlStatement)
        {
            return GetTextAndImageValues(sqlStatement);
        }

        /// <summary>
        /// Get text values of education questions
        /// </summary>
        /// <param name="sqlStatement">SQL query</param>
        /// <returns>list of questions</returns>
        public List<string> GetEducationQuestions(string sqlStatement)
        {
            return GetTextValues(sqlStatement);
        }

        /// <summary>
        /// Get text values of education answers
        /// </summary>
        /// <param name="sqlStatement">SQL query</param>
        /// <returns>list of answers</returns>
        public List<string> GetEducationAnswers(string sqlStatement)
        {
            return GetTextValues(sqlStatement);
        }

        #endregion
    }
}