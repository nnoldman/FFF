using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public enum GameEventID
{
    HeroPosition = 1,
    KeyMoveStart = 2,
    Map_Info = 3,
    OnPathBegin = 4,
    OnPathEnd = 5,
    SDKInit = 6,
    OnGameExit = 7,
    AutoFindPath = 8,
    AutoFight = 9,
    HeroIdleStateChange = 10,
    //ID<=10内C和Lua公用

    OnGetRoleName,
    MainUserData,

    OnTopStateChange,

    GameBaseStart = 100,
    OnTVMessage,


    PropertyStart = 1000,
    PropertyEnd = PropertyStart + 2000,

    OnAddExp,//添加修为
    OnTrainTimeChange,//修炼剩余时间

    OnAddSpirit,//添加灵气

    Bag_CapcityChange,//包裹各自数量改变

    ItemDelete,
    ItemAdd,
    ItemMove,
    ItemRefresh,

    OnSchoolBaseChange,//门派

    OnSchoolDataChange,
    OnSchoolExchange,
    OnSchoolTaskChange,

    OnSchoolGapsAdd,

    Magic_OnUpdataSkill,
    Magic_OnDeleteSkill,

    OnCaveChange,//洞府

    OnCaveAdd,

    OnCurrentLog,

    OnMapListChange,
    OnTerrainChange,
    OnHeroPositionChange,

    OnChargeBegin,
    OnChargeReturn,
    OnChargeUserCancel,

    OnRemendChange,//引荐人信息

    Mail_Change,
    Mail_New,
    Mail_ContentChange,
    Mail_Delete,

    OnRefiningElixirInfo,//炼丹信息
    OnRefiningItemInfo,//炼器信息

    School_OnTrainChange,//练功房

    AutoMap_Records,//扫荡
    AutoMap_ResultChange,

    //寻龙
    Dragon_InfoChange,
    Dragon_Event,

    //灵山
    SoulMount_LeftTimesChange,

    //地图次数
    MapTimesChange,

    //功能开启
    OnFucntionOpenAll,
    OnFunctionOpenSingle,

    //道童
    OnPriest_WashPoolChange,
    OnPriest_Change,
    Count,
}


