using System;

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