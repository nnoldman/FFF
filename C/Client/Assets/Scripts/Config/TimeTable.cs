using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//
//@author:nn
//@time:2017/10/23 14:56:35
//工具生成，请勿修改！
//

public class TimeTableRecord
{
    public int level;
    public string period;
    public string era;
    public Int64 start;
    public int speed;
    public string intro;
}

public partial class TimeTable : TableManager<TimeTableRecord>
{
    public static TimeTable Instance;
    public override string TableName()
    {
        return "TimeTable.txt";
    }
}


