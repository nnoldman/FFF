using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
public partial class TimeTable : TableManager<TimeTableRecord>
{
    public override int MakeKey(TimeTableRecord obj)
    {
        return obj.level;
    }
}
