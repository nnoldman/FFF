using System.Collections;
using System.Collections.Generic;
using System;
/// <summary>
/// 副本管理器
/// </summary>
public class DungeonMgr
{
    public List<GeneralInfo> generals = new List<GeneralInfo>();

    private static DungeonMgr _instance = null;

    public static DungeonMgr Cur
    {
        get
        {
            if (_instance == null)
                _instance = new DungeonMgr();
            return _instance;
        }
    }

    public int AddGeneralInfo(GeneralInfo inf)
    {
        if (!generals.Contains(inf))
            generals.Add(inf);
        return generals.Count;
    }

    public GeneralInfo GetGeneralInfo(int idx)
    {
        int index = generals.FindIndex((info) => info.id == idx);
        GeneralInfo inf = null;
        try
        {
            inf = generals[index];
        }
        catch (Exception)
        {
            ALog.logWarning("DungeonMgr=> Error General ID: " + idx.ToString());
        }
        return inf;
    }
    public void Clear()
    {
        generals.Clear();
    }
}
