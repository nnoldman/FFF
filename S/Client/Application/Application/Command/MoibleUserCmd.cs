using System;

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