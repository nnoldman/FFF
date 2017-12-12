using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

public class BuildLog {
    static FileStream mLogger;
    static FileStream Logger {
        get {
            if (mLogger == null) {
                mLogger = new FileStream(LogFile, FileMode.Append);
            }
            return mLogger;
        }
    }

    static string LogFile {
        get {
            return Path.Combine(GameOption.BuildOption.build_floder, "log.txt");
        }
    }

    static UTF8Encoding mEncoding = new UTF8Encoding(false);

    static public void WriteLine(string content) {
        string ret = DateTime.Now.ToString() + "::" + content + "\n";
        WriteInner(ret);
    }
    static void WriteInner(string content) {
        var data = mEncoding.GetBytes(content);
        Logger.Write(data, 0, data.Length);
    }
    static public void Write(string content) {
        WriteInner(content);
    }
    static public void WriteWithTime(string content) {
        string ret = DateTime.Now.ToString() + content;
        WriteInner(ret);
    }

    public static void OutPut() {
        Logger.Close();
        Frame.Helper.OpenText(LogFile);
        mLogger = null;
    }
}
