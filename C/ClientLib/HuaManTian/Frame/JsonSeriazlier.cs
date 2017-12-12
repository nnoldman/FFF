using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Frame {
public class JsonSeriazlier : ISerializer {
    private static UTF8Encoding sUTF8NBOM = new UTF8Encoding(false);
    public static T From<T>(string content, bool zip = false) {
        T ret = default(T);
        try {
            if(zip) {
                var data = Zip7Helper.DecompressLZMA(sUTF8NBOM.GetBytes(content));
                content = sUTF8NBOM.GetString(data);
            }
            ret = UnityEngine.JsonUtility.FromJson<T>(content);
        } catch(Exception exc) {
            UnityEngine.Debug.LogWarning(content + exc.Message);
        }
        return ret;
    }

    public static T LoadFrom<T>(string path, bool zip = false) {
        T ret = default(T);
        try {
            var text = System.IO.File.ReadAllText(path);
            ret = From<T>(text, zip);
        } catch (Exception exc) {
            UnityEngine.Debug.LogWarning(exc.Message);
        }
        return ret;
    }

    public static string ToText<T>(T obj, bool zip = false, bool pretty = true) {
        string ret = string.Empty;
        try {
            ret = UnityEngine.JsonUtility.ToJson(obj, pretty);
            if (zip) {
                var zipcontent = Zip7Helper.CompressLZMA(sUTF8NBOM.GetBytes(ret));
                ret = sUTF8NBOM.GetString(zipcontent);
            }
        } catch (Exception exc) {
            UnityEngine.Debug.LogWarning(exc.Message);
        }
        return ret;
    }
}
}
