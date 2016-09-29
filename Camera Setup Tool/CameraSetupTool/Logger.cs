using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace CameraSetupTool
{
    /// <summary>
    /// Lists the severity levels of the system events
    /// </summary>
    public enum Severity
    {
        /// <summary>
        /// Informative message
        /// </summary>
        Information,
        /// <summary>
        /// Warning message
        /// </summary>
        Warning,
        /// <summary>
        /// Error Message
        /// </summary>
        Error,
        /// <summary>
        /// Debug Message
        /// </summary>
        Debug
    }

    /// <summary>
    /// Represents user interface element that displays the system events and logs the same to a log file.
    /// </summary>
    public class Logger
    {
        /// <summary>
        /// Textual description for each severity of severity
        /// </summary>
        static string[] sevirityStr =
            new string[4]{
                "Information",
                "Warning",
                "Error",
                "Debug"
            };

        /// <summary>
        ///  full name of the log file
        /// </summary>
        private static string logFileName;

        /// <summary>
        /// Logger instance
        /// </summary>
        private static Logger logger;

        /// <summary>
        /// Gets singleton instance of LogViewer.
        /// </summary>
        /// <returns></returns>
        public static Logger GetLogger()
        {
            if (logger == null)
            {
                logger = new Logger();
            }
            return logger;
        }

        /// <summary>
        /// Gets or sets the filename of the GUI log.
        /// </summary>
        public static string LogFileName
        {
            get
            {
                if (logFileName == null)
                {
                    logFileName = Globals.LogFilePath;
                }
                return Logger.logFileName;
            }
            set { Logger.logFileName = value; }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Logger"/> class.
        /// </summary>
        private Logger()
        {
            logFileName = Globals.LogFilePath;
        }

        /// <summary>
        /// Defines the prototype for the log appending function
        /// </summary>
        delegate void LogAppender(Severity severity, string message);

        /// <summary>
        /// Appends given message to the system log implementing thread safety.
        /// </summary>
        /// <param name="severity">The severity of the message.</param>
        /// <param name="message">The message text.</param>
        public void AppendLog(Severity severity, string message)
        {
            try
            {
                System.IO.File.AppendAllText(logFileName,
                    System.DateTime.Now.ToString() + "\t" +
                    Logger.sevirityStr[(int)severity].PadRight(20) + "\t" +
                    message + "\r\n");
            }
            catch (Exception)
            {
                // TODO: Since there could be more than one threads trying to write to the file, 
                //  an exception is expected here. This is to be replaced with a 'logging serivce' mechanism.
            }
        }
    }
}
