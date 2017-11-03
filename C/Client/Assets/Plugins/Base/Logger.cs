using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
namespace Basic
{
    public class Logger
    {
        public delegate void LogHandler(string msg);
        private static LogHandler InfoHandler;
        private static LogHandler WarningHandler;
        private static LogHandler ErrorHandler;
        public static bool enabled = true;

        public static void SetErrorHandler(LogHandler handler)
        {
            InfoHandler = handler;
        }
        public static void SetInfoHandler(LogHandler handler)
        {
            WarningHandler = handler;
        }
        public static void SetWarningHandler(LogHandler handler)
        {
            ErrorHandler = handler;
        }

        public static void LogWarning(string msg)
        {
            if (WarningHandler != null && enabled)
                WarningHandler(msg);
        }
        public static void Log(string msg)
        {
            if (InfoHandler != null && enabled)
                InfoHandler(msg);
        }
        public static void LogError(string msg)
        {
            if (ErrorHandler != null && enabled)
                ErrorHandler(msg);
        }
        public static void LogExcept(Exception exc)
        {
            if (ErrorHandler != null && enabled)
                ErrorHandler(exc.Message);
        }
        public static void Debug(string msg)
        {
            if (InfoHandler != null && enabled)
                InfoHandler(msg);
        }
    }
}
