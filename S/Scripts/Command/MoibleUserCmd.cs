using System.Collections;
using System.Collections.Generic;
using System.Text;
using System;
using System.IO;

public enum SERVER_MESSAGE
{
    SERVER_MESSAGE_NONE = 0,
    SERVER_MESSAGE_USERDATA = 1,  //����û�����
    SERVER_MESSAGE_OBJS = 2,  //��������
    SERVER_MESSAGE_CHAT = 3,  //��������
    SERVER_MESSAGE_DAYSIGN = 4,  //ÿ��ǩ������
    SERVER_MESSAGE_ADDMAILLIST = 5, //�ʼ��б� t_MailAddListProto      
    SERVER_MESSAGE_MAILCONTENT = 6, //�ʼ����� t_MailContentProto
    SERVER_MESSAGE_ALLSOLDIERS = 7, //ȫ��С�� t_SoldierCmdProto
    SERVER_MESSAGE_ALLGENERALS = 8, //ȫ���佫 t_GeneralCmdProto
    SERVER_MESSAGE_FIGHTSETTING = 9, //��վ��ʦ�佫     t_FightSettingProto
    SERVER_MESSAGE_SELECTUSERINFO = 10,//ѡ���ɫ��Ϣ t_stUserInfoUserCmdProto   
    SERVER_MESSAGE_RANDNAME = 11,//������� t_stRandNameCmdProto
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
    public uint messageid;//��Ϣ���
    public uint size;
    public byte[] data;
}

public enum CLIENT_MESSAGE
{
    CLIENT_MESSAGE_NONE = 0,
    CLIENT_MESSAGE_SIGN = 1,//ǩ��  
    CLIENT_MESSAGE_GETMAILLIST = 2,//�����ʼ��б�
    CLIENT_MESSAGE_OPENMAIL = 3,//���ʼ� t_MailOpenCmdProto       
    CLIENT_MESSAGE_GETMAILITEM = 4,//ȡ���ʼ����� t_MailOpenCmdProto
    CLIENT_MESSAGE_DELMAIL = 5,//ɾ���ʼ� t_MailOpenCmdProto
    CLIENT_MESSAGE_CLEARMAIL = 6,//����ʼ�
    CLIENT_MESSAGE_FIGHTSETTING = 7, //ѡ���վ��ʦ�佫 t_FightSettingProto
    CLINET_MESSAGE_GENERALSELECTSOLDIERS = 8, //ѡ���佫��С��   t_GeneralSelectSoldierProto
    CLIENT_MESSAGE_CHAT = 9,  //����,t_stMobileChannelChatUserCmdProto
    CLIENT_MESSAGE_GETRANDNAME = 10, //�õ�����,t_stGetRandNameCmdProto
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
    public uint messageid;//��Ϣ���
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
    CHAT_TYPE_PRIVATE = 1,                 /// ˽��Ƶ��
    CHAT_TYPE_NINE,                                 /// ����Ƶ��
    CHAT_TYPE_TEAM,                 /// ����Ƶ��
    CHAT_TYPE_FAMILY,               /// ����Ƶ��
    CHAT_TYPE_GROUP,                                        /// ��ӪƵ��
    CHAT_TYPE_WORLD,                                /// ����Ƶ��


    CHAT_TYPE_ALL_ZONE = 10,                            /// ȫ������
    CHAT_TYPE_SYSTEM = 11,               /// ϵͳƵ��
    CHAT_TYPE_NPC = 12,                            /// npc˵��

    CHAT_TYPE_GM = 13,                   /// GM��Ƶ��
    CHAT_TYPE_ERROR_GM = 14,                            /// ���͵�GM���ߵľ�����Ϣ


    CHAT_TYPE_LOUDSPEAKERONE = 20,      // С����1
    CHAT_TYPE_LOUDSPEAKERTWO = 21,      // С����2
    CHAT_TYPE_LOUDSPEAKERTHREE = 22,      // С����3
    CHAT_TYPE_LOUDSPEAKERFOUR = 23,      // С����4
    CHAT_TYPE_LOUDSPEAKERFIVE = 24,      // С����5
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
    public uint index { get; set; }//λ��


    [ProtoBuf.ProtoMember(2)]
    public uint type { get; set; }//ʿ������


    [ProtoBuf.ProtoMember(3)]
    public uint level { get; set; }//�ȼ�

    [ProtoBuf.ProtoMember(4)]
    public uint star { get; set; }//����

    [ProtoBuf.ProtoMember(5)]
    public uint deathstate { get; set; }//0������1����


    [ProtoBuf.ProtoMember(6)]
    public string name { get; set; }//����

    [ProtoBuf.ProtoMember(7)]
    public UInt64 exp { get; set; }//��ǰ����

    [ProtoBuf.ProtoMember(8)]
    public uint general { get; set; }//�����佫

}

//ʿ���б�
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
    public uint level { get; set; }//�ȼ�

    [ProtoBuf.ProtoMember(3)]
    public uint star { get; set; }//����

    [ProtoBuf.ProtoMember(4)]
    public uint deathstate { get; set; }//0������1����



    [ProtoBuf.ProtoMember(5)]
    public UInt64 exp { get; set; }//��ǰ����


}

//�佫�б�
[ProtoBuf.ProtoContract]
public class t_GeneralCmdProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public t_PetGeneralStructProto[] generals { get; set; }

}

//ѡ���佫�;�ʦ
[ProtoBuf.ProtoContract]
public class t_FightSettingProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint adviser { get; set; }//ѡ��ľ�ʦ

    [ProtoBuf.ProtoMember(2)]
    public uint[] generals { get; set; }//ѡ����佫�б�

}

//ѡ���佫��С����ÿ��ѡ��֮��ȫ�����͹���
[ProtoBuf.ProtoContract]
public class t_GeneralSelectSoldierProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint general { get; set; }//�佫

    [ProtoBuf.ProtoMember(2)]
    public uint[] soldiers { get; set; }//����С��

}

//������ַ���
[ProtoBuf.ProtoContract]
public class t_stRandNameCmdProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public string name { get; set; }
}

//��ȡ�������
[ProtoBuf.ProtoContract]
public class t_stGetRandNameCmdProto : ICommand
{
    [ProtoBuf.ProtoMember(1)]
    public uint sex { get; set; }
}


