/*----------------------------------------------------------------
// 模块名：DailyTaskData
// 模块描述：日常任务
//----------------------------------------------------------------*/
using System.Collections;
using System.Collections.Generic;
using System;
namespace GameData
{
    public class DailyTaskData : GameData<DailyTaskData>
    {
        static public readonly string fileName = "xml/DailyTaskData";

        public List<Task.BaseInfo> taskList;

        public static Task.BaseInfo Get(int id, int childid)
        {
            DailyTaskData data = Get(id);
            if (data != null && data.taskList.Count >= childid)
            {
                return data.taskList[childid - 1];
            }
            else
            {
                ALog.logError(string.Format("Daily Task Error: doesnt has ID:{0},childID:{1}!", id, childid));
            }
            return null;
        }
    }
}
