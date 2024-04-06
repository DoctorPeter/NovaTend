/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmEduDBImport.cs
///   Description :  DB import module
/// </summary>

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using DataModule;

namespace ManagementTool
{
    /// <summary>
    /// DB import window class
    /// </summary>
    public partial class fmEduDBImport : Form
    {
        #region Database

        // Database manager instance
        private DataBaseManager dbManager;

        #endregion

        #region Constructing

        public fmEduDBImport(DataBaseManager dbManager)
        {
            this.dbManager = dbManager;

            InitializeComponent();

            // Bind category ID combo box
            eduLessonCategIDComboBox.DataBindings.Add(new System.Windows.Forms.Binding("SelectedValue", dbManager.importEduCategoriesBindingSource, "ID", true));
            eduLessonCategIDComboBox.DataSource = dbManager.importEduCategoriesBindingSource;
            eduLessonCategIDComboBox.DisplayMember = "Name";
            eduLessonCategIDComboBox.FormattingEnabled = true;
            eduLessonCategIDComboBox.ValueMember = "ID";

            // Bind lesson ID combo box
            eduQuestLessonIDComboBox.DataBindings.Add(new System.Windows.Forms.Binding("SelectedValue", dbManager.importEduLessonsBindingSource, "ID", true));
            eduQuestLessonIDComboBox.DataSource = dbManager.importEduLessonsBindingSource;
            eduQuestLessonIDComboBox.DisplayMember = "LessonText";
            eduQuestLessonIDComboBox.FormattingEnabled = true;
            eduQuestLessonIDComboBox.ValueMember = "ID";

            // Bind right answer ID combo box
            eduQuestRightAnswerIDComboBox.DataBindings.Add(new System.Windows.Forms.Binding("SelectedValue", dbManager.importEduAnswersBindingSource, "ID", true));
            eduQuestRightAnswerIDComboBox.DataSource = dbManager.importEduAnswersBindingSource;
            eduQuestRightAnswerIDComboBox.DisplayMember = "AnswerText";
            eduQuestRightAnswerIDComboBox.FormattingEnabled = true;
            eduQuestRightAnswerIDComboBox.ValueMember = "ID";

            // Bind question ID combo box
            eduAnswersQuestIDComboBox.DataBindings.Add(new System.Windows.Forms.Binding("SelectedValue", dbManager.importEduQuestionsBindingSource, "ID", true));
            eduAnswersQuestIDComboBox.DataSource = dbManager.importEduQuestionsBindingSource;
            eduAnswersQuestIDComboBox.DisplayMember = "QuestionText";
            eduAnswersQuestIDComboBox.FormattingEnabled = true;
            eduAnswersQuestIDComboBox.ValueMember = "ID";
        }

        #endregion

        #region SQL statements

        /// <summary>
        /// Create SQL query
        /// </summary>
        /// <param name="tableName">table name</param>
        /// <param name="columnName">column name</param>
        /// <param name="condString">contidion string</param>
        /// <returns>SQL query string</returns>
        private string CreateSQLQuery(string tableName, string columnName, string condString)
        {
            string sqlQuery = "SELECT " + columnName + " FROM " + tableName;
            if (condString != String.Empty)
                sqlQuery = sqlQuery + " WHERE " + condString;
            
            return sqlQuery;
        }

        /// <summary>
        /// Create SQL query
        /// </summary>
        /// <param name="tableName">table name</param>
        /// <param name="columnName">column name</param>
        /// <param name="condString">contidion string</param>
        /// <returns>SQL query string</returns>
        private string CreateSQLQuery(string tableName, string columnName1, string columnName2, string condString)
        {
            string sqlQuery = "SELECT " + columnName1 + ", " + columnName2 + " FROM " + tableName;
            if (condString != String.Empty)
                sqlQuery = sqlQuery + " WHERE " + condString;

            return sqlQuery;
        }

        #endregion

        #region Buttons

        /// <summary>
        /// Close button string
        /// </summary>
        private void closeButton_Click(object sender, System.EventArgs e)
        {
            Close();
        }

        /// <summary>
        /// Import button string
        /// </summary>
        private void importButton_Click(object sender, System.EventArgs e)
        {
            ExternEduDataExtractor dataExtractor = new ExternEduDataExtractor();

            if (mainTabControl.SelectedTab != null)
            {
                switch (mainTabControl.SelectedTab.Name)
                {
                    case "eduCategTabPage":
                        {
                            // Connect ot external database
                            if (!(dataExtractor.Connect(eduCategConStrTextBox.Text)))
                            {
                                MessageBox.Show("Can't connect to external database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                return;
                            }
                            
                            // Prepare SQL statement
                            string sqlStatemet = CreateSQLQuery(eduCategTableNameTextBox.Text, eduCategColumnNameTextBox.Text, eduCategAddCondTextBox.Text);

                            // Get categories names
                            List<string> eduCategNamesList = dataExtractor.GetEduCategories(sqlStatemet);

                            if ((eduCategNamesList == null) || (eduCategNamesList.Count == 0))
                            {
                                MessageBox.Show("Cannot extract categories from external database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                dataExtractor.Disconnect();
                                return;
                            }

                            // Disconnect from external database
                            dataExtractor.Disconnect();

                            // Insert data to our databae
                            if (dbManager.ImportEduCategories(eduCategNamesList))
                                MessageBox.Show("Categories successfully extracted!", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            else
                                MessageBox.Show("Can't insert categories names to internal database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                            break;
                        }

                    case "eduLessonsTabPage":
                        {
                            // Connect ot external database
                            if (!(dataExtractor.Connect(eduLessonConStrTextBox.Text)))
                            {
                                MessageBox.Show("Can't connect to external database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                return;
                            }

                            // Prepare SQL statement
                            string sqlStatement = CreateSQLQuery(eduLessonTableNameTextBox.Text, eduLessonColumnNameTextBox.Text, eduLessonImageColumnNameTextBox.Text, eduLessonAddCondTextBox.Text);

                            // Get lessons values
                            List<ExternEduDataExtractor.TextAndImageValue> eduLessonsList = dataExtractor.GetEduLessons(sqlStatement);

                            if ((eduLessonsList == null) || (eduLessonsList.Count == 0))
                            {
                                MessageBox.Show("Cannot extract lessons from external database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                dataExtractor.Disconnect();
                                return;
                            }

                            // Disconnect from external database
                            dataExtractor.Disconnect();

                            // Insert data to our database
                            if (dbManager.ImportEduLessons(eduLessonsList))
                                MessageBox.Show("Lessons successfully extracted!", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            else
                                MessageBox.Show("Can't insert lessons values to internal database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                            break;
                        }

                    case "eduQuestTabPage":
                        {
                            // Connect ot external database
                            if (!(dataExtractor.Connect(eduQuestConStrTextBox.Text)))
                            {
                                MessageBox.Show("Can't connect to external database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                return;
                            }

                            // Prepare SQL statement
                            string sqlStatement = CreateSQLQuery(eduQuestTableNameTextBox.Text, eduQuestColumnNameTextBox.Text, eduQuestAddCondTextBox.Text);

                            // Get questions values
                            List<string> eduQuestList = dataExtractor.GetEducationQuestions(sqlStatement);

                            if ((eduQuestList == null) || (eduQuestList.Count == 0))
                            {
                                MessageBox.Show("Cannot extract questions from external database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                dataExtractor.Disconnect();
                                return;
                            }

                            // Disconnect from external database
                            dataExtractor.Disconnect();

                            // Insert data to our database
                            if (dbManager.ImportEduQuestions(eduQuestList))
                                MessageBox.Show("Questions successfully extracted!", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            else
                                MessageBox.Show("Can't insert questions values to internal database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                            break;
                        }

                    case "eduAnswersTabPage":
                        {
                            // Connect ot external database
                            if (!(dataExtractor.Connect(eduAnswersConStrTextBox.Text)))
                            {
                                MessageBox.Show("Can't connect to external database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                return;
                            }

                            // Prepare SQL statement
                            string sqlStatement = CreateSQLQuery(eduAnswersTableNameTextBox.Text, eduAnswersColumnNameTextBox.Text, eduAnswersAddCondTextBox.Text);

                            // Get answers values
                            List<string> eduAnswersList = dataExtractor.GetEducationAnswers(sqlStatement);

                            if ((eduAnswersList == null) || (eduAnswersList.Count == 0))
                            {
                                MessageBox.Show("Cannot extract answers from external database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                dataExtractor.Disconnect();
                                return;
                            }

                            // Disconnect from external database
                            dataExtractor.Disconnect();

                            // Insert data to our database
                            if (dbManager.ImportEduAnswers(eduAnswersList))
                                MessageBox.Show("Answers successfully extracted!", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            else
                                MessageBox.Show("Can't insert answers values to internal database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                            break;
                        }

                }
            }
        }

        #endregion

    }
}
