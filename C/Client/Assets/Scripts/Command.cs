//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: Command.proto
// Note: requires additional types generated from: GameDefine.proto
namespace Cmd
{
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"ReqAccountOperation")]
  public partial class ReqAccountOperation : global::ProtoBuf.IExtensible
  {
    public ReqAccountOperation() {}
    
    private Cmd.AccountAction _action;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"action", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public Cmd.AccountAction action
    {
      get { return _action; }
      set { _action = value; }
    }
    private string _user;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"user", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string user
    {
      get { return _user; }
      set { _user = value; }
    }
    private string _password;
    [global::ProtoBuf.ProtoMember(3, IsRequired = true, Name=@"password", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string password
    {
      get { return _password; }
      set { _password = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"RetAccountOperation")]
  public partial class RetAccountOperation : global::ProtoBuf.IExtensible
  {
    public RetAccountOperation() {}
    
    private Cmd.AccountErrorCode _error;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"error", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public Cmd.AccountErrorCode error
    {
      get { return _error; }
      set { _error = value; }
    }
    private int _accountid;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"accountid", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int accountid
    {
      get { return _accountid; }
      set { _accountid = value; }
    }
    private int _time;
    [global::ProtoBuf.ProtoMember(3, IsRequired = true, Name=@"time", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int time
    {
      get { return _time; }
      set { _time = value; }
    }
    private string _token;
    [global::ProtoBuf.ProtoMember(4, IsRequired = true, Name=@"token", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string token
    {
      get { return _token; }
      set { _token = value; }
    }
    private readonly global::System.Collections.Generic.List<int> _late_serverids = new global::System.Collections.Generic.List<int>();
    [global::ProtoBuf.ProtoMember(5, Name=@"late_serverids", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public global::System.Collections.Generic.List<int> late_serverids
    {
      get { return _late_serverids; }
    }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"ReqLoginGameServer")]
  public partial class ReqLoginGameServer : global::ProtoBuf.IExtensible
  {
    public ReqLoginGameServer() {}
    
    private int _accountid;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"accountid", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int accountid
    {
      get { return _accountid; }
      set { _accountid = value; }
    }
    private int _time;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"time", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int time
    {
      get { return _time; }
      set { _time = value; }
    }
    private string _token;
    [global::ProtoBuf.ProtoMember(3, IsRequired = true, Name=@"token", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string token
    {
      get { return _token; }
      set { _token = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"GameRole")]
  public partial class GameRole : global::ProtoBuf.IExtensible
  {
    public GameRole() {}
    
    private int _id;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"id", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int id
    {
      get { return _id; }
      set { _id = value; }
    }
    private int _level = default(int);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"level", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int level
    {
      get { return _level; }
      set { _level = value; }
    }
    private string _name = "";
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"name", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue("")]
    public string name
    {
      get { return _name; }
      set { _name = value; }
    }
    private int _sex = default(int);
    [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name=@"sex", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int sex
    {
      get { return _sex; }
      set { _sex = value; }
    }
    private int _job = default(int);
    [global::ProtoBuf.ProtoMember(5, IsRequired = false, Name=@"job", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int job
    {
      get { return _job; }
      set { _job = value; }
    }
    private int _vip = default(int);
    [global::ProtoBuf.ProtoMember(6, IsRequired = false, Name=@"vip", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int vip
    {
      get { return _vip; }
      set { _vip = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"RetLoginGameServer")]
  public partial class RetLoginGameServer : global::ProtoBuf.IExtensible
  {
    public RetLoginGameServer() {}
    
    private Cmd.LoginGameError _error;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"error", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public Cmd.LoginGameError error
    {
      get { return _error; }
      set { _error = value; }
    }
    private Cmd.GameRole _role;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"role", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public Cmd.GameRole role
    {
      get { return _role; }
      set { _role = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"ReqCreateRole")]
  public partial class ReqCreateRole : global::ProtoBuf.IExtensible
  {
    public ReqCreateRole() {}
    
    private int _sex = default(int);
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"sex", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int sex
    {
      get { return _sex; }
      set { _sex = value; }
    }
    private int _job = default(int);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"job", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int job
    {
      get { return _job; }
      set { _job = value; }
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
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"RetCreateRole")]
  public partial class RetCreateRole : global::ProtoBuf.IExtensible
  {
    public RetCreateRole() {}
    
    private Cmd.CreateRoleError _error = Cmd.CreateRoleError.CreateRoleSucess;
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"error", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(Cmd.CreateRoleError.CreateRoleSucess)]
    public Cmd.CreateRoleError error
    {
      get { return _error; }
      set { _error = value; }
    }
    private Cmd.GameRole _role = null;
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"role", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public Cmd.GameRole role
    {
      get { return _role; }
      set { _role = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"RTMainUser")]
  public partial class RTMainUser : global::ProtoBuf.IExtensible
  {
    public RTMainUser() {}
    
    private int _charID = default(int);
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"charID", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int charID
    {
      get { return _charID; }
      set { _charID = value; }
    }
    private int _job = default(int);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"job", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int job
    {
      get { return _job; }
      set { _job = value; }
    }
    private int _sex = default(int);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"sex", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int sex
    {
      get { return _sex; }
      set { _sex = value; }
    }
    private string _name = "";
    [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name=@"name", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue("")]
    public string name
    {
      get { return _name; }
      set { _name = value; }
    }
    private int _vip = default(int);
    [global::ProtoBuf.ProtoMember(5, IsRequired = false, Name=@"vip", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int vip
    {
      get { return _vip; }
      set { _vip = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"RetTimeLine")]
  public partial class RetTimeLine : global::ProtoBuf.IExtensible
  {
    public RetTimeLine() {}
    
    private int _trun = default(int);
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"trun", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int trun
    {
      get { return _trun; }
      set { _trun = value; }
    }
    private int _leftSeconds = default(int);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"leftSeconds", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int leftSeconds
    {
      get { return _leftSeconds; }
      set { _leftSeconds = value; }
    }
    private int _totalSeconds = default(int);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"totalSeconds", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int totalSeconds
    {
      get { return _totalSeconds; }
      set { _totalSeconds = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"ItemObject")]
  public partial class ItemObject : global::ProtoBuf.IExtensible
  {
    public ItemObject() {}
    
    private int _dbID = default(int);
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"dbID", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int dbID
    {
      get { return _dbID; }
      set { _dbID = value; }
    }
    private int _itemid = default(int);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"itemid", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int itemid
    {
      get { return _itemid; }
      set { _itemid = value; }
    }
    private int _count = default(int);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"count", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int count
    {
      get { return _count; }
      set { _count = value; }
    }
    private GameDefine.ObjectCellType _cell = GameDefine.ObjectCellType.ObjectCellType_None;
    [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name=@"cell", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(GameDefine.ObjectCellType.ObjectCellType_None)]
    public GameDefine.ObjectCellType cell
    {
      get { return _cell; }
      set { _cell = value; }
    }
    private int _position = default(int);
    [global::ProtoBuf.ProtoMember(5, IsRequired = false, Name=@"position", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int position
    {
      get { return _position; }
      set { _position = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"RetObjectAdd")]
  public partial class RetObjectAdd : global::ProtoBuf.IExtensible
  {
    public RetObjectAdd() {}
    
    private readonly global::System.Collections.Generic.List<Cmd.ItemObject> _objects = new global::System.Collections.Generic.List<Cmd.ItemObject>();
    [global::ProtoBuf.ProtoMember(1, Name=@"objects", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<Cmd.ItemObject> objects
    {
      get { return _objects; }
    }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"RetObjectSync")]
  public partial class RetObjectSync : global::ProtoBuf.IExtensible
  {
    public RetObjectSync() {}
    
    private readonly global::System.Collections.Generic.List<Cmd.ItemObject> _objects = new global::System.Collections.Generic.List<Cmd.ItemObject>();
    [global::ProtoBuf.ProtoMember(1, Name=@"objects", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<Cmd.ItemObject> objects
    {
      get { return _objects; }
    }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"RetObjectDelete")]
  public partial class RetObjectDelete : global::ProtoBuf.IExtensible
  {
    public RetObjectDelete() {}
    
    private readonly global::System.Collections.Generic.List<int> _objects = new global::System.Collections.Generic.List<int>();
    [global::ProtoBuf.ProtoMember(1, Name=@"objects", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public global::System.Collections.Generic.List<int> objects
    {
      get { return _objects; }
    }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"RetObjectMove")]
  public partial class RetObjectMove : global::ProtoBuf.IExtensible
  {
    public RetObjectMove() {}
    
    private int _dbID = default(int);
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"dbID", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int dbID
    {
      get { return _dbID; }
      set { _dbID = value; }
    }
    private GameDefine.ObjectCellType _cell = GameDefine.ObjectCellType.ObjectCellType_None;
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"cell", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(GameDefine.ObjectCellType.ObjectCellType_None)]
    public GameDefine.ObjectCellType cell
    {
      get { return _cell; }
      set { _cell = value; }
    }
    private int _position = default(int);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"position", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int position
    {
      get { return _position; }
      set { _position = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"ReqUseObject")]
  public partial class ReqUseObject : global::ProtoBuf.IExtensible
  {
    public ReqUseObject() {}
    
    private int _dbID = default(int);
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"dbID", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int dbID
    {
      get { return _dbID; }
      set { _dbID = value; }
    }
    private int _count = default(int);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"count", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int count
    {
      get { return _count; }
      set { _count = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"RetMessage")]
  public partial class RetMessage : global::ProtoBuf.IExtensible
  {
    public RetMessage() {}
    
    private Cmd.MessageChannel _channel = Cmd.MessageChannel.MessageChannel_System_None;
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"channel", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(Cmd.MessageChannel.MessageChannel_System_None)]
    public Cmd.MessageChannel channel
    {
      get { return _channel; }
      set { _channel = value; }
    }
    private string _sender = "";
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"sender", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue("")]
    public string sender
    {
      get { return _sender; }
      set { _sender = value; }
    }
    private string _content = "";
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"content", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue("")]
    public string content
    {
      get { return _content; }
      set { _content = value; }
    }
    private int _localTime = default(int);
    [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name=@"localTime", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int localTime
    {
      get { return _localTime; }
      set { _localTime = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"ReqChat")]
  public partial class ReqChat : global::ProtoBuf.IExtensible
  {
    public ReqChat() {}
    
    private Cmd.MessageChannel _channel = Cmd.MessageChannel.MessageChannel_System_None;
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"channel", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(Cmd.MessageChannel.MessageChannel_System_None)]
    public Cmd.MessageChannel channel
    {
      get { return _channel; }
      set { _channel = value; }
    }
    private int _roleID = default(int);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"roleID", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int roleID
    {
      get { return _roleID; }
      set { _roleID = value; }
    }
    private string _from = "";
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"from", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue("")]
    public string from
    {
      get { return _from; }
      set { _from = value; }
    }
    private string _to = "";
    [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name=@"to", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue("")]
    public string to
    {
      get { return _to; }
      set { _to = value; }
    }
    private string _content = "";
    [global::ProtoBuf.ProtoMember(5, IsRequired = false, Name=@"content", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue("")]
    public string content
    {
      get { return _content; }
      set { _content = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
    [global::ProtoBuf.ProtoContract(Name=@"AccountAction")]
    public enum AccountAction
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"AccountAction_None", Value=0)]
      AccountAction_None = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"AccountAction_Create", Value=1)]
      AccountAction_Create = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"AccountAction_Rename", Value=2)]
      AccountAction_Rename = 2,
            
      [global::ProtoBuf.ProtoEnum(Name=@"AccountAction_Delete", Value=3)]
      AccountAction_Delete = 3,
            
      [global::ProtoBuf.ProtoEnum(Name=@"AccountAction_Login", Value=4)]
      AccountAction_Login = 4
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"AccountErrorCode")]
    public enum AccountErrorCode
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"AccountErrorCode_None", Value=0)]
      AccountErrorCode_None = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"AccountErrorCode_CreateSucessed", Value=1)]
      AccountErrorCode_CreateSucessed = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"AccountErrorCode_NameRepeated", Value=2)]
      AccountErrorCode_NameRepeated = 2,
            
      [global::ProtoBuf.ProtoEnum(Name=@"AccountErrorCode_UserCantFind", Value=3)]
      AccountErrorCode_UserCantFind = 3,
            
      [global::ProtoBuf.ProtoEnum(Name=@"AccountErrorCode_PasswordError", Value=4)]
      AccountErrorCode_PasswordError = 4,
            
      [global::ProtoBuf.ProtoEnum(Name=@"AccountErrorCode_LoginSucessed", Value=5)]
      AccountErrorCode_LoginSucessed = 5
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"LoginGameError")]
    public enum LoginGameError
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"LoginGameSucess", Value=100)]
      LoginGameSucess = 100,
            
      [global::ProtoBuf.ProtoEnum(Name=@"LoginGameOverdue", Value=300)]
      LoginGameOverdue = 300,
            
      [global::ProtoBuf.ProtoEnum(Name=@"LoginGameInvalid", Value=400)]
      LoginGameInvalid = 400
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"CreateRoleError")]
    public enum CreateRoleError
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"CreateRoleSucess", Value=0)]
      CreateRoleSucess = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"CreateRoleNameRepeated", Value=1)]
      CreateRoleNameRepeated = 1
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"MessageSender")]
    public enum MessageSender
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageSender_System", Value=0)]
      MessageSender_System = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageSender_User", Value=1)]
      MessageSender_User = 1
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"MessageChannel")]
    public enum MessageChannel
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageChannel_System_None", Value=0)]
      MessageChannel_System_None = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageChannel_System_Error", Value=1)]
      MessageChannel_System_Error = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageChannel_System_Sucess", Value=2)]
      MessageChannel_System_Sucess = 2,
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageChannel_System_TV", Value=3)]
      MessageChannel_System_TV = 3,
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageChannel_System_MessageBox", Value=4)]
      MessageChannel_System_MessageBox = 4,
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageChannel_System_Count", Value=5)]
      MessageChannel_System_Count = 5,
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageChannel_User_None", Value=10)]
      MessageChannel_User_None = 10,
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageChannel_User_Normal", Value=11)]
      MessageChannel_User_Normal = 11,
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageChannel_User_World", Value=12)]
      MessageChannel_User_World = 12,
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageChannel_User_Louder", Value=13)]
      MessageChannel_User_Louder = 13,
            
      [global::ProtoBuf.ProtoEnum(Name=@"MessageChannel_User_Count", Value=14)]
      MessageChannel_User_Count = 14
    }
  
}