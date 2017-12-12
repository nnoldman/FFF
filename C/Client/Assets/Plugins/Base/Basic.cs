using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Basic {
public static class Assist {
    public static string TrimExtension(string path) {
        int pos = path.IndexOf('.');
        if (pos == -1)
            return path;
        return path.Substring(0, pos);
    }

    public static bool WithExtension(string name, string[] extensions) {
        if (extensions == null)
            return false;
        for (int i = 0; i < extensions.Length; ++i) {
            if (name.EndsWith(extensions[i]))
                return true;
        }
        return false;
    }

    public static bool WithExtension(string name, HashSet<String> extensions) {
        if (extensions == null)
            return false;
        var ext = Path.GetExtension(name);
        if (ext == string.Empty)
            return false;
        ext = ext.ToLower();
        if (extensions.Contains(ext.ToLower()))
            return true;
        return false;
    }

    /// <summary>
    /// Combine a,b Replace('\\', '/');
    /// </summary>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <returns></returns>
    public static string CombineWithSlash(params string[] args) {
        string path = string.Empty;
        if (args.Length > 0) {
            int i = 0;
            do {
                path = path + args[i].Replace('\\', '/');
                if (i == args.Length - 1)
                    break;
                path += '/';
                ++i;
            } while (i < args.Length);
        }
        return path.Replace("//", "/");
    }

    public static string CombineWithSlash(bool replace2SlashTo1, params string[] args) {
        string path = string.Empty;
        if (args.Length > 0) {
            int i = 0;
            do {
                path = path + args[i].Replace('\\', '/');
                if (i == args.Length - 1)
                    break;
                path += '/';
                ++i;
            } while (i < args.Length);
        }
        if (replace2SlashTo1)
            return path.Replace("//", "/");
        return path;
    }

    /// <summary>
    /// Combine Replace('/', '\\');
    /// </summary>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <returns></returns>
    public static string CombineWithBSlash(params string[] args) {
        string path = string.Empty;
        if (args.Length > 0) {
            int i = 0;
            do {
                path = path + args[i].Replace('/', '\\');
                if (i == args.Length - 1)
                    break;
                path += '\\';
                ++i;
            } while (i < args.Length);
        }
        return path.Replace("\\\\", "\\");
    }

    public static string[] GetFileWithUnityDataPath(string datapath, string path, string pattern, SearchOption option) {
        string abpath = path;
        if (!path.StartsWith(datapath))
            abpath = CombineWithSlash(datapath, path);
        DirectoryInfo directory = new DirectoryInfo(abpath);
        if (directory.Exists) {
            FileInfo[] files = directory.GetFiles(pattern, option);
            List<string> names = new List<string>();
            if (files != null) {
                foreach (var f in files) {
                    names.Add(f.FullName.Substring(datapath.Length));
                }
            }
            return names.ToArray();
        }
        return null;
    }

    public static void CreateDirectoryIfNotExist(string dir) {
        if (!Directory.Exists(dir))
            Directory.CreateDirectory(dir);
    }

    public static void DeleteFolder(string dir) {
        foreach (string d in Directory.GetFileSystemEntries(dir)) {
            if (System.IO.File.Exists(d)) {
                FileInfo fi = new FileInfo(d);
                if (fi.Attributes.ToString().IndexOf("ReadOnly") != -1)
                    fi.Attributes = FileAttributes.Normal;
                System.IO.File.Delete(d);//直接删除其中的文件
            } else
                DeleteFolder(d);//递归删除子文件夹
        }
        Directory.Delete(dir);//删除已空文件夹
    }


    public static void DeleteDir(string path) {
        if (path.Trim() == "" || !Directory.Exists(path))
            return;
        DirectoryInfo dirInfo = new DirectoryInfo(path);

        FileInfo[] fileInfos = dirInfo.GetFiles();
        if (fileInfos != null && fileInfos.Length > 0) {
            foreach (FileInfo fileInfo in fileInfos) {
                //DateTime.Compare( fileInfo.LastWriteTime,DateTime.Now);
                System.IO.File.Delete(fileInfo.FullName); //删除文件
            }
        }

        DirectoryInfo[] dirInfos = dirInfo.GetDirectories();
        if (dirInfos != null && dirInfos.Length > 0) {
            foreach (DirectoryInfo childDirInfo in dirInfos) {
                DeleteDir(childDirInfo.FullName); //递归
            }
        }
        Directory.Delete(dirInfo.FullName, true); //删除目录
    }
    static bool IsIgnoreFile(string[] ignoreExtensions, string fileName) {
        if (ignoreExtensions != null) {
            foreach (var ig in ignoreExtensions)
                if (fileName.EndsWith(ig))
                    return true;
        }
        return false;
    }
    public static void CopyFloder(string src, string dest, bool includeSub, bool createNew, bool overWrite, string[] ignoreExtensions) {
        DirectoryInfo dir = new DirectoryInfo(src);
        DirectoryInfo[] dirs = dir.GetDirectories();

        if (!dir.Exists) {
            return;
        }

        if (!Directory.Exists(dest)) {
            Directory.CreateDirectory(dest);
        } else if (createNew) {
            DeleteFolder(dest);
            DirectoryInfo destDir = new DirectoryInfo(dest);
            destDir.Create();
        }

        FileInfo[] files = dir.GetFiles();
        foreach (FileInfo file in files) {
            if (IsIgnoreFile(ignoreExtensions, file.Name))
                continue;
            string temppath = System.IO.Path.Combine(dest, file.Name);
            try {
                file.CopyTo(temppath, overWrite);
            } catch (Exception exc) {
            }
        }

        if (includeSub) {
            foreach (DirectoryInfo subdir in dirs) {
                string temppath = System.IO.Path.Combine(dest, subdir.Name);
                CopyFloder(subdir.FullName, temppath, includeSub, createNew, overWrite, ignoreExtensions);
            }
        }
    }

    /// <summary>
    /// use shell
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    public static void OpenFloder(string path) {
        Process p = new Process();
        p.StartInfo = new ProcessStartInfo();
        p.StartInfo.Arguments = path;

        if (!Directory.Exists(p.StartInfo.Arguments))
            Directory.CreateDirectory(p.StartInfo.Arguments);

        p.StartInfo.FileName = "explorer.exe";
        p.Start();
    }


    public static void OpenText(string path) {
        Process p = new Process();
        p.StartInfo = new ProcessStartInfo();
        p.StartInfo.Arguments = path;
        p.StartInfo.FileName = "notepad++.exe";
        p.Start();
    }

    public static string EnsureNameWithExtenision(string name, string ext) {
        if (name.IndexOf(ext) == -1)
            name += ext;
        return name;
    }
    public static string EnsureNameWithXML(string name) {
        return EnsureNameWithExtenision(name, ".xml");
    }

    public static string EnsureNameWithOutExtenision(string name) {
        int pos1 = name.LastIndexOf('.');
        if (pos1 == -1)
            return name;
        return name.Substring(0, pos1);
    }
    private static UTF8Encoding sUTF8NBOM = new UTF8Encoding(false);

    public static bool SaveJsonObject<T>(T obj, string path, bool zip = false) {
        try {
            string content = JsonUtility.ToJson(obj, true);
            if (zip) {
                var zipcontent = Zip7Helper.CompressLZMA(sUTF8NBOM.GetBytes(content));
                System.IO.File.WriteAllBytes(path, zipcontent);
            } else {
                System.IO.File.WriteAllText(path, content, new UTF8Encoding(false));
            }
        } catch (Exception exc) {
            return false;
        }
        return true;
    }

    public static T LoadJsonObject<T>(string path, bool zip = false) {
        try {
            if (zip) {
                var raw = System.IO.File.ReadAllBytes(path);
                var data = Zip7Helper.DecompressLZMA(raw);
                return JsonUtility.FromJson<T>(sUTF8NBOM.GetString(data));
            } else {
                var content = System.IO.File.ReadAllText(path, sUTF8NBOM);
                return JsonUtility.FromJson<T>(content);
            }
        } catch (Exception exc) {
        }
        return default(T);
    }

    public static T FromJsonWithZip<T>(byte[] content, bool zip = false) {
        if (zip) {
            var data = Zip7Helper.DecompressLZMA(content);
            return JsonUtility.FromJson<T>(sUTF8NBOM.GetString(data));
        }
        return JsonUtility.FromJson<T>(sUTF8NBOM.GetString(content));
    }

    public static string ConvertToPathStartWithAsset(string path) {
        string datapath = Application.dataPath;
        path = path.Replace('\\', '/');
        string parent = Path.GetDirectoryName(datapath);
        int pos = path.IndexOf(parent);
        if (pos != -1) {
            return path.Substring(pos + parent.Length + 1);
        }
        return path;
    }

    internal class Watcher {
        public string tag;
        public DateTime time;
        public override string ToString() {
            TimeSpan t = DateTime.Now - time;
            return string.Format("=>{0} {1:00}:{2:00}:{3:00}:{4:000}", tag, t.Hours, t.Minutes, t.Seconds, t.Milliseconds);
        }
    }

    static Stack<Watcher> mWatchers = new Stack<Watcher>();

    public static void BeginWatch(string tag) {
        Watcher w = new Watcher();
        w.tag = tag;
        w.time = DateTime.Now;
        mWatchers.Push(w);
    }

    public static void EndWatch() {
        if (mWatchers.Count == 0)
            return;
        Watcher w = mWatchers.Pop();
        Basic.Logger.LogWarning(w.ToString());
    }

    public static void Watch(Action act, string tag = "") {
        if (act == null)
            return;
        if (string.IsNullOrEmpty(tag))
            tag = act.Method.Name;

        Watcher w = new Watcher();
        w.tag = tag;
        w.time = DateTime.Now;
        act();
        Basic.Logger.LogWarning(w.ToString());
    }
}
}
