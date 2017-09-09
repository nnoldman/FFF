using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public enum GameGroup
{
    None,
    Wei,
    Shu,
    Wu,
    Count,
}

/// <summary>
/// 角色数据
/// </summary>
public class StatRole : DataDriverObject<StatRole>
{
    public UInt64 id = 0;
    public DString name = new DString();
    public DInt lv = new DInt(1);
    public DInt heroLvLimit = new DInt();
    public DInt energy = new DInt();
    public DInt energyLimit = new DInt();
    public UInt64 exp = 0;
    public UInt64 totleExp = 0;
    public int title = 0;               ///称号
    public int icon = 0;                ///头像
    public int iconEdage = 0;           ///图像框
    public DInt gold = new DInt(0);               ///元宝
    public DInt silver = new DInt(0);             ///银两
    public DInt jewel = new DInt(0);              ///宝石

    public DInt group = new DInt((int)GameGroup.Shu);

    public void RandomGenerate()
    {
    }

    public string titleString
    {
        get
        {
            return GameData.TitleData.Get(title).titleString;
        }
    }
}


/// <summary>
/// 技能数据
/// </summary>
public class StatSkill
{
    public int id = 0;
    public int lv = 0;
    public int general = 0;       ///所属武将
}

/// <summary>
/// 武将数据
/// </summary>
public class StatGeneral
{
    public int id;
    public int lv = 1;
    public int power = 0;         ///战力

    public GameData.PropertyOfGeneral baseinfo
    {
        get
        {
            if (gamedata.baseinfos.Count > lv - 1)
                return gamedata.baseinfos[lv - 1];
            return null;
        }
    }

    public GameData.GeneralData gamedata
    {
        get
        {
            return GameData.GeneralData.Get(id);
        }
    }

}
/// <summary>
/// 俘虏数据
/// </summary>
public class StatCapture : StatGeneral
{
    public int intimacy = 0;                ///亲密度
    public uint presentLeftTime = 0;        ///赠送礼物剩余时间,秒
    ///
    public int heartCount
    {
        get
        {
            return intimacy / GameData.GeneralData.INTIMACY_SEG;
        }
    }
}
public enum SoliderType
{
    Sword,          ///刀盾
    Lance,          ///枪兵
    Archer,         ///弓兵
    Vehicle,        ///骑兵
    Female,         ///女兵
    Count,
}

/// <summary>
/// VIP数据
/// </summary>
public class StatVip
{
    public uint charge = 0;
    public int vip = 1;

    public bool maxLevel
    {
        get
        {
            GameData.VipData d = GameData.VipData.Get(vip + 1);
            return d == null;
        }
    }
    public uint upNeed
    {
        get
        {
            return GameData.VipData.Get(vip + 1).allCharge - charge;
        }
    }
    public string sprite
    {
        get
        {
            return "V" + vip.ToString();
        }
    }
    public string nextSprite
    {
        get
        {
            return "V" + (vip + 1).ToString();
        }
    }
}

public enum CommonState
{
    Unreach,
    CanFetch,
    Fetched,
    Count,
}
public class StatSignOfDay
{
    public int day = 1;
    public CommonState state = CommonState.Unreach;

    public GameData.SignData data
    {
        get
        {
            return GameData.SignData.Get(day);
        }
    }
}
/// <summary>
/// 签到数据
/// </summary>
public class StatSign:DataDriverObject<StatSign>
{
    public StatSignOfDay today = new StatSignOfDay();
    public List<StatSignOfDay> signStats = new List<StatSignOfDay>();
    public StatSign()
    {
        today.day = DateTime.Now.Day;
        int daycount=DateTime.DaysInMonth(DateTime.Now.Year,DateTime.Now.Month);
        for (int i = 0; i < daycount; ++i)
        {
            var st = new StatSignOfDay();
            st.day = i + 1;
            signStats.Add(st);
        }
    }
}
public enum TaskState
{
    None,           ///不可接取
    CanGet,         ///可接取
    Doing,          ///正在做
    CanComit,       ///可交付
    Done,           ///已交付
}
/// <summary>
/// 任务数据
/// </summary>
public class StatTask
{
    public int taskid = 0;
    public int childID = 0;
    public int curOperator = 0;
    public TaskState state = TaskState.None;
}
/// <summary>
/// 每次出战时，发送给服务器；上线时服务器发送来
/// </summary>
public class StatWarSetting
{
    public static int GeneralCount = 3;
    public int adviser; ///选择的军师
    public int[] generals = new int[GeneralCount];//选择的武将
}

public class StatDungeon
{
    public int id;              ///副本id
    public int enterTimes;      ///已进入次数
    public int leftTimes;       ///剩余次数
    public bool occupy;         ///是否攻占
    public int star;
}

public class StatDugeonChapter
{
    public static int REWARD_COUNT = 3;
    public static int MAX_STARTS = 30;
    public CommonState[] rewardState = new CommonState[REWARD_COUNT];
}
public class StatDugeonChapterMap
{
    public Dictionary<int, StatDugeonChapter> chapterRewards = new Dictionary<int, StatDugeonChapter>();
}
public class WarResultGeneral
{
    public int generalID = 0;
    public int expGeneral = 1;
    public int expSolider = 1;
    public int deadSolider = 0;
}
public class StatWarResult
{
    public int roleExp;
    public int silver;
    public int medal;                           ///勋章
    public WarResultGeneral[] generals;         ///武将奖励
    public Data.ItemCount[] drops;                   ///掉落
    public StatCapture[] captures;              ///战俘
}

public class StatChat
{
    public string name;
    public DString content = new DString();
}