/// <summary>
///   Solution : NovaTend
///   Project : WriteLog.dll
///   Module : LogWriter.cs
///   Description :  logging module
/// </summary>
/// 
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Encryption;

namespace WriteLog
{
    /// <summary>
    /// LOG-file messages 
    /// writer class
    /// </summary>
    public class LogWriter
    {

        #region Constants

        // LogWriter modes definition
        
        // Write messages to log file
        public const byte LOG_MODE_WRITE_TO_FILE        = 0x001;

        // Write messages to console (for DEBUG)
        public const byte LOG_MODE_WRITE_TO_CONSOLE     = 0x002;

        // Send messaes by e-mail
        public const byte LOG_MODE_SEND_MAIL            = 0x004;

        // Encrypt messages before writting
        public const byte LOG_MODE_ENCRYPT_MESSAGES     = 0x008;


        
        // Definition of errors

        // Succesfull write log result
        public const int  LOG_FILE_WRITE_OK	        = 0x000;

        // Error of Log-file opening
        public const int LOG_FILE_OPEN_ERROR = 0x001;

        // Error of Log-file writing
        public const int LOG_FILE_WRITE_ERROR = 0x002;

        // Error of encryptor
        public const int LOG_ENCRYPTION_ERROR = 0x004;

        // Error of sending mail
        public const int LOG_SEND_MAIL_ERROR = 0x008;



        // Separator of encrypted message
        public const byte LOG_ENCRYPTION_SEPARATOR      = 0xFF;


        #endregion

        #region Encryption

        // Encryptor instance
        private Encryptor _encryptor;

        // Encryptor property
        public Encryptor encryptor
        {
            get
            {
                if (_encryptor == null)
                {
                    _encryptor = new Encryptor();
                }

                return _encryptor;
            }

            set
            {
                _encryptor = value;
            }
        }

        /// <summary>
        /// Encrypt string
        /// </summary>
        /// <param name="str">Input string</param>
        /// <returns>Encrypted data. Array of bytes</returns>
        public byte[] EncryptString(string str)
        {
            byte[] decData = System.Text.Encoding.ASCII.GetBytes(str);
            byte[] encData = null;
            encryptor.EncryptAndPackSecurityData(decData, ref encData);
            return encData;
        }

        /// <summary>
        /// Decrypt string
        /// </summary>
        /// <param name="bytes">Input array of bytes</param>
        /// <returns>Decrypted string</returns>
        public string DecryptString(byte[] bytes)
        {
            byte[] encData = bytes;
            byte[] decData = null;
            encryptor.UnPackAndDecryptSecurityData(encData, ref decData);
            return System.Text.Encoding.ASCII.GetString(decData);
        }

        #endregion

        #region Constructing

        // Log file name
        private string fileName;

        // Log writer mode
        private byte mode;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="fileName">LOG-file name</param>
        public LogWriter(string fileName)
        {
            _encryptor = null;
            mode = LOG_MODE_WRITE_TO_FILE;
            this.fileName = fileName;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="fileName">LOG-file name</param>
        /// <param name="mode">mode</param>
        public LogWriter(string fileName, byte mode)
        {
            this.fileName = fileName;
            _encryptor = null;
            mode = LOG_MODE_WRITE_TO_FILE;
            SetMode(mode);
        }

        #endregion

        #region Mode

        /// <summary>
        /// Set mode
        /// </summary>
        /// <param name="mode">new mode value</param>
        /// <returns>old mode value</returns>
        public byte SetMode(byte mode)
        {
            byte oldMode = this.mode;
	        this.mode = mode;
	        return oldMode;
        }

        /// <summary>
        /// Get mode
        /// </summary>
        /// <returns>mode value</returns>
        public byte GetMode()
        {
            return mode;
        }

        /// <summary>
        /// Add new mode value
        /// </summary>
        /// <param name="mode">new mode value</param>
        /// <returns>result mode value</returns>
        public byte AddMode(byte mode)
        {
            this.mode |= mode;
            return this.mode;
        }

        /// <summary>
        /// Remove mode value
        /// </summary>
        /// <param name="mode">mode value for removing</param>
        /// <returns>result mode value</returns>
        public byte RemoveMode(byte mode)
        {
            this.mode ^= mode;
            return this.mode;
        }

        #endregion

        #region Write to file

        // Object for critical section synchronization
        private static object criticalSection = new object();

        /// <summary>
        /// Write text message to file
        /// </summary>
        /// <param name="message">message</param>
        /// <returns>error code</returns>
        private int WriteToFile(string message)
        {
            try
            {
                /*
                // Get LOG file path
                string pathToLog = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Log");

                // Create directory if needed
                if (!Directory.Exists(pathToLog)) Directory.CreateDirectory(pathToLog);

                // Prepare file name
                string filename = Path.Combine(pathToLog, this.fileName);
                */
                // Enter to critical section
                lock (criticalSection)
                {
                    // Append text message to the file end
                    File.AppendAllText(this.fileName, message, Encoding.GetEncoding("Windows-1251"));
                }

                return LOG_FILE_WRITE_OK;
            }
            catch
            {
                // General error processing
                return LOG_FILE_WRITE_ERROR;
            }
        }


        /// <summary>
        /// Encrypt text message and save to file
        /// </summary>
        /// <param name="message">message</param>
        /// <returns>error code</returns>
        private int WriteToFileWithEncryption(string message)
        {
            try
            {
                // Get LOG file path
                string pathToLog = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Log");

                // Create directory if needed
                if (!Directory.Exists(pathToLog)) Directory.CreateDirectory(pathToLog);

                // Prepare file name
                string filename = Path.Combine(pathToLog, this.fileName);

                // Encrypt message
                byte[] encMessage = EncryptString(message);

                //Preapare message buffer
                int bufferSize = encMessage.Length + sizeof(int) + sizeof(byte);
                byte[] buffer = new byte[bufferSize];

                // Set encrypted message separator
                buffer[0] = LOG_ENCRYPTION_SEPARATOR;

                // Save message size
                byte[] bufferSizeBytes = BitConverter.GetBytes(encMessage.Length);
                //if (BitConverter.IsLittleEndian) Array.Reverse(bufferSizeBytes);
                byte[] resultBufferSizeBytes = bufferSizeBytes;
                
                // Copy binary data
                Array.Copy(resultBufferSizeBytes, 0, buffer, 1, resultBufferSizeBytes.Length);
                Array.Copy(encMessage, 0, buffer, resultBufferSizeBytes.Length + 1, encMessage.Length);

                // Enter to critical section
                lock (criticalSection)
                {
                    FileInfo fInf = new FileInfo(filename);

                    // Save binary data (append)
                    BinaryWriter fw = new BinaryWriter(fInf.Open(FileMode.OpenOrCreate, FileAccess.Write, FileShare.None));
                    fw.Seek(0, SeekOrigin.End);
                    fw.Write(buffer);
                    fw.Close();
                }

                return LOG_FILE_WRITE_OK;
            }
            catch
            {
                // General error processing
                return LOG_FILE_WRITE_ERROR;
            }
        }

        /// <summary>
        /// Write message to LOG-file
        /// </summary>
        /// <param name="message">message</param>
        /// <returns>error code</returns>
        public int WriteToLog(string message)
        {
            int iResult = LOG_FILE_WRITE_OK;

            // Formating message string
            string mesText = String.Format("[{0:MM.dd.yy hh:mm:ss}] >> {1} \n", DateTime.Now, message);

            //Out to console
            if ((this.mode & LOG_MODE_WRITE_TO_CONSOLE) == LOG_MODE_WRITE_TO_CONSOLE)
            {
                Console.Write(mesText);
            }

            //Write to file
            if ((mode & LOG_MODE_WRITE_TO_FILE) == LOG_MODE_WRITE_TO_FILE)
            {
                if ((mode & LOG_MODE_ENCRYPT_MESSAGES) == LOG_MODE_ENCRYPT_MESSAGES)
                    //With encryption
                    iResult |= WriteToFileWithEncryption(mesText);
                else
                    //Without ecnryption
                    iResult |= WriteToFile(mesText);
            }

            //Send e-mail
            if ((mode & LOG_MODE_SEND_MAIL) == LOG_MODE_SEND_MAIL)
            {
                //iResult |= SendMail(recordText);
            }
                       
            return iResult;
        }

        #endregion

    }
}
