//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: Command.proto
namespace Cmd
{
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"Duration")]
  public partial class Duration : global::ProtoBuf.IExtensible
  {
    public Duration() {}
    
    private long _seconds = default(long);
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"seconds", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(long))]
    public long seconds
    {
      get { return _seconds; }
      set { _seconds = value; }
    }
    private int _nanos = default(int);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"nanos", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int nanos
    {
      get { return _nanos; }
      set { _nanos = value; }
    }
    private string _name = "";
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"name", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue("")]
    public string name
    {
      get { return _name; }
      set { _name = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"RTGameServer")]
  public partial class RTGameServer : global::ProtoBuf.IExtensible
  {
    public RTGameServer() {}
    
    private string _ip = "";
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"ip", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue("")]
    public string ip
    {
      get { return _ip; }
      set { _ip = value; }
    }
    private int _port = default(int);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"port", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int port
    {
      get { return _port; }
      set { _port = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}