using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
/// <summary>
/// 道具类型
/// </summary>
public enum ItemType
{
    None = 0,           ///无
    Consumables = 1,    ///消耗品
    Material = 2,       ///材料
    Jewel = 3,          ///宝石
    Function = 4,       ///功能
    Other = 5,          ///其他
}

public enum ItemQuality
{
    None,
    White,      ///白
    Green,      ///绿
    Blue,       ///蓝
    Purple,     ///紫
    Golden,     ///金
    Count = Golden,
}

//public class Data.ItemCount
//{
//    public int id;
//    public int count;
//    public void Parse(string str)
//    {
//        string[] res = str.Split(':');
//        if (res.Length >= 1)
//            id = int.Parse(res[0]);
//        if (res.Length >= 2)
//            count = int.Parse(res[1]);
//    }

//    public GameData.ObjectBase define
//    {
//        get
//        {
//            return GameData.ObjectBase.Get(id);
//        }
//    }
//}