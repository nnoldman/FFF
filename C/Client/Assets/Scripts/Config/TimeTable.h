using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//
//@author:nn
//@time:2017/9/24 17:16:37
//工具生成，请勿修改！
//

public TimeTableRecord
{
	public int level;
	public string period;
	public string era;
	public Int64 start;
	public string intro;
}

public partial class TimeTable : TableManager<TimeTableRecord>
{
    public static TimeTable Instance;
    public override string TableName()
    {
        return @qTimeTable.txt@q;
    }
}


