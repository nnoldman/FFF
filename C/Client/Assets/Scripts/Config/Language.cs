using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//
//@author:nn
//@time:2017/11/2 12:15:41
//工具生成，请勿修改！
//

public class LanguageRecord
{
    public int id;
    public string text;
}

public partial class Language : TableManager<LanguageRecord>
{
    public static Language Instance;

    public override string TableName()
    {
        return "Language.txt";
    }
}


