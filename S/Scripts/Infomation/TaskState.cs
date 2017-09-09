using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
namespace Task
{

    public enum TaskOperator
    {
        None,                   ///无     
        BuyFromShop,            ///从商城购买
        Count,
    }
    public enum TaskType
    {
        None,               ///无
        Daily,              ///日常
    }

    public class StateDataOfDaily : StatTask
    {
        public BaseInfo baseinfo
        {
            get
            {
                return GameData.DailyTaskData.Get(taskid, childID);
            }
        }
        public TaskState Next()
        {
            BaseInfo info = baseinfo;
            switch (state)
            {
                case TaskState.None:
                    {
                        state = TaskState.CanGet;
                    }
                    break;
                case TaskState.CanGet:
                    {
                        state = TaskState.Doing;
                    }
                    break;
                case TaskState.Doing:
                    {
                        if (info.oper != TaskOperator.None)
                        {
                            if (info.curNum < info.maxNum)
                            {
                                info.curNum++;
                            }
                            if (info.curNum == info.maxNum)
                            {
                                state = TaskState.CanComit;
                            }
                        }
                        else
                        {
                            state = TaskState.CanComit;
                        }
                    }
                    break;
                case TaskState.CanComit:
                    {
                        state = TaskState.Done;
                    }
                    break;
            }
            return state;
        }
    }
    public class BaseInfo
    {
        public int childID = 0;                           ///子id
        public int name;
        public TaskType type = TaskType.None;             ///类型
        public TaskOperator oper = TaskOperator.None;     ///任务操作类型
        public int maxNum = 0;                         ///目标个数
        public int curNum = 0;
        public int icon;
        public int desc;

        public Task.Reward reward;

        public string nameString
        {
            get
            {
                return Localization.Get(name);
            }
        }
        public string descString
        {
            get
            {
                return Localization.Get(desc);
            }
        }
        public string rewardString
        {
            get
            {
                return Localization.Get(reward.desc);
            }
        }
        public string texture
        {
            get
            {
                return GameData.IconData.Get(icon).texture;
            }
        }
    }
    public class Reward
    {
        public int desc;
        public List<Data.ItemCount> items;
    }
}
