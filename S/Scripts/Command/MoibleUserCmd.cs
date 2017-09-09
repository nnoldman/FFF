using System.Collections;
using System.Collections.Generic;
using System.Text;
using System;
using System.IO;

public enum SERVER_MESSAGE
{
    SERVER_MESSAGE_NONE = 0,
    SERVER_MESSAGE_USERDATA = 1,  //玩家用户数据
    SERVER_MESSAGE_OBJS = 2,  //包裹数据
    SERVER_MESSAGE_CHAT = 3,  //聊天数据
    SERVER_MESSAGE_DAYSIGN = 4,  //每日签到次数
    SERVER_MESSAGE_ADDMAILLIST = 5, //邮件列表 t_MailAddListProto      
    SERVER_MESSAGE_MAILCONTENT = 6, //邮件内容 t_MailContentProto
    SERVER_MESSAGE_ALLSOLDIERS = 7, //全部小兵 t_SoldierCmdProto
    SERVER_MESSAGE_ALLGENERALS = 8, //全部武将 t_GeneralCmdProto
    SERVER_MESSAGE_FIGHTSETTING = 9, //出站军师武将     t_FightSettingProto
    SERVER_MESSAGE_SELECTUSERINFO = 10,//选择角色信息 t_stUserInfoUserCmdProto   
    SERVER_MESSAGE_RANDNAME = 11,//随机名字 t_stRandNameCmdProto
    SERVER_MESSAGE_MAX,
};

public class stMobileUnityUserCmd : stNullUserCmd
{
    public const byte SEND_UNITY_USERCMD = 1;
    public const byte CLIENT_UNITY_USERCMD = 2;


    public stMobileUnityUserCmd()
    {
        byCmd = MOBILEUNITY_USERCMD;
    }
    public override void serialize(MemoryStream stream)
    {
        base.serialize(stream);
    }
    public override void unserialize(MemoryStream stream)
    {
        base.unserialize(stream);
    }
}

public class stSendUnityUserCmd : stMobileUnityUserCmd
{
    public stSendUnityUserCmd()
    {
        byParam = SEND_UNITY_USERCMD;

        messageid = 0;
        size = 0;
    }
    public override void serialize(MemoryStream stream)
    {
        base.serialize(stream);

        byte[] bmessageid = BitConverter.GetBytes(messageid);
        stream.Write(bmessageid, 0, bmessageid.Length);

        byte[] bsize = BitConverter.GetBytes(size);
        stream.Write(bsize, 0, bsize.Length);

        if (data != null)
            stream.Write(data, 0, (int)size);
    }

    public override void unserialize(MemoryStream stream)
    {
        base.unserialize(stream);

        byte[] bmessageid = new byte[4];
        stream.Read(bmessageid, 0, 4);
        messageid = BitConverter.ToUInt32(bmessageid, 0);

        byte[] bsize = new byte[4];
        stream.Read(bsize, 0, 4);
        size = BitConverter.ToUInt32(bsize, 0);
        try
        {
            data = new byte[size];
            stream.Read(data, 0, (int)size);
        }
        catch (Exception ex)
        {
            ALog.logError(ex.Message);
        }
    }
    public uint messageid;//消息编号
    public uint size;
    public byte[] data;
}

public enum CLIENT_MESSAGE
{
    CLIENT_MESSAGE_NONE = 0,
    CLIENT_MESSAGE_SIGN = 1,//签到  
    CLIENT_MESSAGE_GETMAILLIST = 2,//请求邮件列表
    CLIENT_MESSAGE_OPENMAIL = 3,//打开邮件 t_MailOpenCmdProto       
    CLIENT_MESSAGE_GETMAILITEM = 4,//取得邮件附件 t_MailOpenCmdProto
    CLIENT_MESSAGE_DELMAIL = 5,//删除邮件 t_MailOpenCmdProto
    CLIENT_MESSAGE_CLEARMAIL = 6,//清空邮件
    CLIENT_MESSAGE_FIGHTSETTING = 7, //选择出站军师武将 t_FightSettingProto
    CLINET_MESSAGE_GENERALSELECTSOLDIERS = 8, //选择武将带小兵   t_GeneralSelectSoldierProto
    CLIENT_MESSAGE_CHAT = 9,  //聊天,t_stMobileChannelChatUserCmdProto
    CLIENT_MESSAGE_GETRANDNAME = 10, //得到名字,t_stGetRandNameCmdProto
    CLIENT_MESSAGE_MAX,
};

public class stClientUnityUserCmd : stMobileUnityUserCmd
{
    public stClientUnityUserCmd()
    {
        byParam = CLIENT_UNITY_USERCMD;

        messageid = 0;
        size = 0;
    }
    public override void serialize(MemoryStream stream)
    {
        base.serialize(stream);

        byte[] bmessageid = BitConverter.GetBytes(messageid);
        stream.Write(bmessageid, 0, bmessageid.Length);

        byte[] bsize = BitConverter.GetBytes(size);
        stream.Write(bsize, 0, bsize.Length);
        if (data != null)
            stream.Write(data, 0, (int)size);
    }

    public void unserialize(MemoryStream stream)
    {
        base.unserialize(stream);

        byte[] bmessageid = new byte[4];
        stream.Read(bmessageid, 0, 4);
        messageid = BitConverter.ToUInt32(bmessageid, 0);
        byte[] bsize = new byte[4];
        stream.Read(bsize, 0, 4);
        size = BitConverter.ToUInt32(bsize, 0);

        try
        {
            data = new byte[size];
            stream.Read(data, 0, (int)size);
        }
        catch (Exception ex)
        {
            ALog.logError(ex.Message);
        }
    }
    public uint messageid;//消息编号
    public uint size;
    public byte[] data;
}





[ProtoBuf.ProtoContract]
public class MainAttrib : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint id { get; set; }

    [ProtoBuf.ProtoMember(2)]
    public string name { get; set; }

    [ProtoBuf.ProtoMember(3)]
    public int lv { get; set; }

    [ProtoBuf.ProtoMember(4)]
    public int heroLvLimit { get; set; }

    [ProtoBuf.ProtoMember(5)]
    public uint energy { get; set; }

    [ProtoBuf.ProtoMember(6)]
    public uint energyLimit { get; set; }

    [ProtoBuf.ProtoMember(7)]
    public UInt64 exp { get; set; }

    [ProtoBuf.ProtoMember(8)]
    public UInt64 totleExp { get; set; }

    [ProtoBuf.ProtoMember(9)]
    public int title { get; set; }

    [ProtoBuf.ProtoMember(10)]
    public int iconEdage { get; set; }

    [ProtoBuf.ProtoMember(11)]
    public uint gold { get; set; }


}

[ProtoBuf.ProtoContract]
public class stObjectLocationProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint dwLocation { get; set; }

    [ProtoBuf.ProtoMember(2)]
    public uint x { get; set; }
}

[ProtoBuf.ProtoContract]
public class t_ObjectProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint qwThisID { get; set; }

    [ProtoBuf.ProtoMember(2)]
    public uint dwObjectID { get; set; }

    [ProtoBuf.ProtoMember(3)]
    public string strName { get; set; }

    [ProtoBuf.ProtoMember(4)]
    public uint dwNum { get; set; }

    [ProtoBuf.ProtoMember(5)]
    public stObjectLocationProto pos { get; set; }

    [ProtoBuf.ProtoMember(6)]
    public uint lv { get; set; }

    public GameData.ObjectBase itemDefine
    {
        get
        {
            return GameData.ObjectBase.Get((int)dwObjectID);
        }
    }
    public GameData.EquipData equipData
    {
        get
        {
            return GameData.EquipData.Get((int)dwObjectID);
        }
    }
    public GameData.EquipData equipDataNext
    {
        get
        {
            if (!equipData.IsMax((int)lv))
                return GameData.EquipData.Get(equipData.next);
            return null;
        }
    }
    public GameData.Property prop
    {
        get
        {
            if (equipData)
                return equipData.lvPropertys[(int)lv - 1];
            return null;
        }
    }
    public GameData.Property nextEquipProp
    {
        get
        {
            if (equipDataNext)
                return equipDataNext.lvPropertys[(int)lv - 1];
            return null;
        }
    }
    public GameData.Property nextLvProp
    {
        get
        {
            if (equipData && lv + 1 < equipData.lvPropertys.Count)
                return equipData.lvPropertys[(int)lv];
            return null;
        }
    }
}
public enum ItemAction
{
    Add,
    Update,
    Delete,
    Count,
}
[ProtoBuf.ProtoContract]
public class t_AddObjectInfoProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint byActionType { get; set; }

    [ProtoBuf.ProtoMember(2)]
    public t_ObjectProto obj { get; set; }
}

[ProtoBuf.ProtoContract]
public class t_stAddObjectListUnityUserCmdProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint version { get; set; }

    [ProtoBuf.ProtoMember(2)]
    public t_AddObjectInfoProto[] userset { get; set; }
}

public enum enumChatType
{
    CHAT_TYPE_PRIVATE = 1,                 /// 私聊频道
    CHAT_TYPE_NINE,                                 /// 轻聊频道
    CHAT_TYPE_TEAM,                 /// 队伍频道
    CHAT_TYPE_FAMILY,               /// 军团频道
    CHAT_TYPE_GROUP,                                        /// 阵营频道
    CHAT_TYPE_WORLD,                                /// 世界频道


    CHAT_TYPE_ALL_ZONE = 10,                            /// 全区聊天
    CHAT_TYPE_SYSTEM = 11,               /// 系统频道
    CHAT_TYPE_NPC = 12,                            /// npc说话

    CHAT_TYPE_GM = 13,                   /// GM聊频道
    CHAT_TYPE_ERROR_GM = 14,                            /// 发送到GM工具的警告信息


    CHAT_TYPE_LOUDSPEAKERONE = 20,      // 小喇叭1
    CHAT_TYPE_LOUDSPEAKERTWO = 21,      // 小喇叭2
    CHAT_TYPE_LOUDSPEAKERTHREE = 22,      // 小喇叭3
    CHAT_TYPE_LOUDSPEAKERFOUR = 23,      // 小喇叭4
    CHAT_TYPE_LOUDSPEAKERFIVE = 24,      // 小喇叭5
};
[ProtoBuf.ProtoContract]
public class t_stMobileChannelChatUserCmdProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint version { get; set; }

    [ProtoBuf.ProtoMember(2)]
    public uint dwType { get; set; }


    [ProtoBuf.ProtoMember(3)]
    public uint dwSysInfoType { get; set; }


    [ProtoBuf.ProtoMember(4)]
    public uint dwCharType { get; set; }


    [ProtoBuf.ProtoMember(5)]
    public uint dwCountry { get; set; }


    [ProtoBuf.ProtoMember(6)]
    public uint dwVip { get; set; }

    [ProtoBuf.ProtoMember(7)]
    public uint dwFromUserTempID { get; set; }

    [ProtoBuf.ProtoMember(8)]
    public uint dwChatTime { get; set; }

    [ProtoBuf.ProtoMember(9)]
    public string pstrName { get; set; }

    [ProtoBuf.ProtoMember(10)]
    public string pstrChat { get; set; }

}

[ProtoBuf.ProtoContract]
public class t_DaySignRwdRecProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint id { get; set; }

    [ProtoBuf.ProtoMember(2)]
    public uint state { get; set; }
}

[ProtoBuf.ProtoContract]
public class t_DaySignCmdProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public t_DaySignRwdRecProto[] signs { get; set; }

}

[ProtoBuf.ProtoContract]
public class t_MailOpenCmdProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint mailid { get; set; }


}

public class t_MailAddListProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint id { get; set; }

    [ProtoBuf.ProtoMember(2)]
    public uint state { get; set; }

    [ProtoBuf.ProtoMember(3)]
    public string fromname { get; set; }

    [ProtoBuf.ProtoMember(4)]
    public string title { get; set; }

    [ProtoBuf.ProtoMember(5)]
    public uint accessory { get; set; }

    [ProtoBuf.ProtoMember(6)]
    public uint createtime { get; set; }

    [ProtoBuf.ProtoMember(7)]
    public uint endtime { get; set; }

    [ProtoBuf.ProtoMember(8)]
    public uint type { get; set; }

    [ProtoBuf.ProtoMember(9)]
    public uint needmoney { get; set; }
}

public class t_MailContentProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint id { get; set; }

    [ProtoBuf.ProtoMember(2)]
    public string title { get; set; }

    [ProtoBuf.ProtoMember(3)]
    public uint accessory { get; set; }

    [ProtoBuf.ProtoMember(4)]
    public string text { get; set; }

    [ProtoBuf.ProtoMember(5)]
    public uint sendmoney { get; set; }

    [ProtoBuf.ProtoMember(5)]
    public uint recvmoney { get; set; }

    [ProtoBuf.ProtoMember(6)]
    public uint sendgold { get; set; }

    [ProtoBuf.ProtoMember(7)]
    public uint recvgold { get; set; }

    [ProtoBuf.ProtoMember(9)]
    public t_ObjectProto obj { get; set; }
}

[ProtoBuf.ProtoContract]
public class t_PetSoldierStructProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint index { get; set; }//位置


    [ProtoBuf.ProtoMember(2)]
    public uint type { get; set; }//士兵类型


    [ProtoBuf.ProtoMember(3)]
    public uint level { get; set; }//等级

    [ProtoBuf.ProtoMember(4)]
    public uint star { get; set; }//星数

    [ProtoBuf.ProtoMember(5)]
    public uint deathstate { get; set; }//0正常，1死亡


    [ProtoBuf.ProtoMember(6)]
    public string name { get; set; }//名字

    [ProtoBuf.ProtoMember(7)]
    public UInt64 exp { get; set; }//当前经验

    [ProtoBuf.ProtoMember(8)]
    public uint general { get; set; }//所属武将

}

//士兵列表
[ProtoBuf.ProtoContract]
public class t_SoldierCmdProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public t_PetSoldierStructProto[] soldiers { get; set; }

}

public class t_PetGeneralStructProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint id { get; set; }//id



    [ProtoBuf.ProtoMember(2)]
    public uint level { get; set; }//等级

    [ProtoBuf.ProtoMember(3)]
    public uint star { get; set; }//星数

    [ProtoBuf.ProtoMember(4)]
    public uint deathstate { get; set; }//0正常，1死亡



    [ProtoBuf.ProtoMember(5)]
    public UInt64 exp { get; set; }//当前经验


}

//武将列表
[ProtoBuf.ProtoContract]
public class t_GeneralCmdProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public t_PetGeneralStructProto[] generals { get; set; }

}

//选择武将和军师
[ProtoBuf.ProtoContract]
public class t_FightSettingProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint adviser { get; set; }//选择的军师

    [ProtoBuf.ProtoMember(2)]
    public uint[] generals { get; set; }//选择的武将列表

}

//选择武将带小兵，每次选择之后全部发送过来
[ProtoBuf.ProtoContract]
public class t_GeneralSelectSoldierProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint general { get; set; }//武将

    [ProtoBuf.ProtoMember(2)]
    public uint[] soldiers { get; set; }//带的小兵

}

//随机名字返回
[ProtoBuf.ProtoContract]
public class t_stRandNameCmdProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public string name { get; set; }
}

//获取随机名字
[ProtoBuf.ProtoContract]
public class t_stGetRandNameCmdProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint sex { get; set; }
}


