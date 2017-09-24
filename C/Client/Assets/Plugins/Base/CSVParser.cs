using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Reflection;
using UnityEngine;

public static class CSVParser
{
    public static Func<string, TextAsset> loader;

    static void ParsePropertyValue<T>(T obj, FieldInfo fieldInfo, string valueStr)
    {
        System.Object value = null;
        if (fieldInfo.FieldType.IsEnum)
            value = Enum.Parse(fieldInfo.FieldType, valueStr);
        else
        {
            if (fieldInfo.FieldType == typeof(int))
                value = int.Parse(valueStr);
            else if (fieldInfo.FieldType == typeof(Int64))
                value = Int64.Parse(valueStr);
            else if (fieldInfo.FieldType == typeof(float))
                value = float.Parse(valueStr);
            else if (fieldInfo.FieldType == typeof(double))
                value = double.Parse(valueStr);
            else if (fieldInfo.FieldType == typeof(string))
                value = valueStr.Replace("\\n", "\n");
        }

        if (value == null)
            return;

        fieldInfo.SetValue(obj, value);
    }
    static void ParseLine<T>(T obj,string line,FieldInfo prop, string[] headers,string[] values)
    {
        for (int i = 0; i < headers.Length; ++i)
        {
            var header = headers[i];
            if (header == prop.Name)
            {
                string value = values[i];
                if (string.IsNullOrEmpty(value))
                    continue;
                try
                {
                    ParsePropertyValue(obj, prop, value);
                }
                catch (Exception ex)
                {
                    Debug.LogError("line:" + line + " for: " + prop.Name);
                    throw ex;
                }
            }
        }
    }
    static T ParseObject<T>(string line, FieldInfo[] propertyInfos, string[] headers)
    {
        T obj = Activator.CreateInstance<T>();
        string[] values = line.Split('\t');
        for (int j = 0; j < propertyInfos.Length ; j++)
        {
            var prop = propertyInfos[j];
            if (propertyInfos[j] == null)
                continue;
            ParseLine(obj, line, prop, headers, values);
        }
        return obj;
    }

    static FieldInfo[] GetPropertyInfos<T>(string memberLine)
    {
        Type objType = typeof(T);

        string[] members = memberLine.Split("\t".ToCharArray(), StringSplitOptions.RemoveEmptyEntries);
        FieldInfo[] propertyInfos = new FieldInfo[members.Length];
        for (int i = 0; i < members.Length; i++)
        {
            propertyInfos[i] = objType.GetField(members[i]);
            //if (propertyInfos[i] == null)
            //Debug.LogError("GetField is None!" + members[i]);
        }

        return propertyInfos;
    }
    static string[] GetHeaders(string line)
    {
        string[] headers = line.Split("\t".ToCharArray(), StringSplitOptions.RemoveEmptyEntries);
        return headers;
    }
    static public T[] Parse<T>(string name)
    {
        // here we load the text asset.
        //TextAsset textAsset = (TextAsset)(tabelBundle !=null ? tabelBundle.Load(name) : Resources.Load(name));
        TextAsset textAsset = null;
        if (loader != null)
        {
            textAsset = loader.Invoke(name);
        }
        else
        {
#if UNITY_EDITOR
            textAsset = UnityEditor.AssetDatabase.LoadAssetAtPath<TextAsset>(name);
#endif
        }
        if (textAsset == null)
        {
            Debug.LogError("无法加载表格文件：" + name);
            return null;
        }

        // try parse the table lines.
        string[] lines = textAsset.text.Split("\n\r".ToCharArray(), StringSplitOptions.RemoveEmptyEntries);
        if (lines.Length < 2)
        {
            Debug.LogError("表格文件行数错误，【1】属性名称【2】变量名称【3-...】值：" + name);
            return null;
        }

        // fetch all of the field infos.
        FieldInfo[] propertyInfos = GetPropertyInfos<T>(lines[0]);
        var headers = GetHeaders(lines[0]);

        List<T> ret = new List<T>(lines.Length - 1);
        for (int i = 0; i < lines.Length - 1; i++)
        {
            var line = lines[i + 1];
            if (line.Length == 0)
                continue;
            if(line.Length >= 2)
            {
                if (line[0] == '/' && line[1] == '/')
                    continue;
            }
            ret.Add(ParseObject<T>(line, propertyInfos,headers));
        }
        return ret.ToArray();
    }
}
