//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: GameDefine.proto
namespace GameDefine
{
    [global::ProtoBuf.ProtoContract(Name=@"Capcity")]
    public enum Capcity
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"BagLimit", Value=180)]
      BagLimit = 180,
            
      [global::ProtoBuf.ProtoEnum(Name=@"Bag", Value=120)]
      Bag = 120,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ChildGroup", Value=5)]
      ChildGroup = 5,
            
      [global::ProtoBuf.ProtoEnum(Name=@"Equip", Value=30)]
      Equip = 30,
            
      [global::ProtoBuf.ProtoEnum(Name=@"Store", Value=50)]
      Store = 50,
            
      [global::ProtoBuf.ProtoEnum(Name=@"Mail", Value=100)]
      Mail = 100,
            
      [global::ProtoBuf.ProtoEnum(Name=@"Function", Value=160)]
      Function = 160,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ProertyCount", Value=100)]
      ProertyCount = 100
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"ItemDeleteReason")]
    public enum ItemDeleteReason
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"Invalid", Value=0)]
      Invalid = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"Client", Value=1)]
      Client = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"Move", Value=2)]
      Move = 2,
            
      [global::ProtoBuf.ProtoEnum(Name=@"Combine", Value=3)]
      Combine = 3
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"ItemRefreshReason")]
    public enum ItemRefreshReason
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"ItemRefreshReason_None", Value=0)]
      ItemRefreshReason_None = 0
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"ItemLocation")]
    public enum ItemLocation
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"ItemLocation_None", Value=0)]
      ItemLocation_None = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ItemLocation_Bag", Value=1)]
      ItemLocation_Bag = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ItemLocation_Equip", Value=2)]
      ItemLocation_Equip = 2
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"ItemSellSource")]
    public enum ItemSellSource
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"ItemSellSource_Invalid", Value=0)]
      ItemSellSource_Invalid = 0
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"ObjectCellType")]
    public enum ObjectCellType
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"ObjectCellType_None", Value=0)]
      ObjectCellType_None = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ObjectCellType_Bag", Value=1)]
      ObjectCellType_Bag = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ObjectCellType_Equip", Value=2)]
      ObjectCellType_Equip = 2,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ObjectCellType_Store", Value=3)]
      ObjectCellType_Store = 3
    }
  
}