/*----------------------------------------------------------------
// 模块名：LanguageData
// 模块描述：本地化语言信息数据模块
//----------------------------------------------------------------*/

using System.Collections;
using System.Collections.Generic;
using System;

namespace GameData
{
    public class LanguageData 
        //: GameData<LanguageData>
    {
        public string content;
        //static public readonly string fileName = "xml/ChineseData";

        public static int Money = 3;    //"钻石"
        public static int RMB = 13;     //"元"

        public LanguageData()
        {
            content = string.Empty;
        }

        public string Format(params object[] args)
        {
            return string.Format(content, args);
        }
        public static string GetContent(int id, params object[] args)
        {
            return string.Format(GetContent(id), args);
        }
        public static string MoneyString
        {
            get
            {
                return Localization.Get(Money);
            }
        }
        public static string RMBString
        {
            get
            {
                return Localization.Get(RMB);
            }
        }
        public static string GetLevel(int num)
        {
            return "LV:" + num.ToString();
        }
        public static string GetLevel(uint num)
        {
            return "LV:" + num.ToString();
        }
        public static string GetChineseNum(int num)
        {
            int start=10610;
            string snum = num.ToString();
            string res = string.Empty;
            if (num < 20)
            {
                if (num > 10)
                    res += Localization.Get(start +  10);
                if (num >0)
                    res += Localization.Get(start + num % 10);
            }
            return res;
        }

    }
}
