using System.Collections;
using System.Collections.Generic;
using System.Text;
using System;
using System.IO;   


[ProtoBuf.ProtoContract]
public class SelectUserInfo : ICommand
{
	[ProtoBuf.ProtoContract]
	public class t_MapUserSculptProto : ICommand
	{
		[ProtoBuf.ProtoMember(1)]
		public uint dwHorseID { get; set; }
	
		[ProtoBuf.ProtoMember(2)]
		public uint dwHeadID { get; set; }

		[ProtoBuf.ProtoMember(3)]
		public uint dwBodyID { get; set; }

		[ProtoBuf.ProtoMember(4)]
		public uint dwlegsID { get; set; }

		[ProtoBuf.ProtoMember(5)]
		public uint dwhandsID { get; set; }

		[ProtoBuf.ProtoMember(6)]
		public uint dwfeetsID { get; set; }

		[ProtoBuf.ProtoMember(7)]
		public uint dwWeaponID { get; set; }
	
		
	}

	[ProtoBuf.ProtoMember(1)]
	public uint id { get; set; }

	[ProtoBuf.ProtoMember(2)]
	public string name { get; set; }

	[ProtoBuf.ProtoMember(3)]
	public uint type { get; set; }

	[ProtoBuf.ProtoMember(4)]
	public uint level { get; set; }

	[ProtoBuf.ProtoMember(5)]
	public uint mapid { get; set; }

	[ProtoBuf.ProtoMember(6)]
	public string mapName { get; set; }

	[ProtoBuf.ProtoMember(7)]
	public uint country { get; set; }

	[ProtoBuf.ProtoMember(8)]
	public uint group { get; set; }

	[ProtoBuf.ProtoMember(9)]
	public uint face { get; set; }

	[ProtoBuf.ProtoMember(10)]
	public uint hair { get; set; }

	[ProtoBuf.ProtoMember(11)]
	public string countryName { get; set; }

	[ProtoBuf.ProtoMember(12)]
	public uint bitmask { get; set; }

	[ProtoBuf.ProtoMember(13)]
	public uint forbidTime { get; set; }

	[ProtoBuf.ProtoMember(14)]
	public uint zone_state { get; set; }

	[ProtoBuf.ProtoMember(15)]
	public uint target_zone { get; set; }

	[ProtoBuf.ProtoMember(16)]
	public uint acceptPK { get; set; }

	[ProtoBuf.ProtoMember(17)]
	public t_MapUserSculptProto sculpt { get; set; }

	[ProtoBuf.ProtoMember(18)]
	public uint flatZoneID { get; set; }

	[ProtoBuf.ProtoMember(19)]
	public uint gameZoneID { get; set; }

	[ProtoBuf.ProtoMember(20)]
	public uint activestar { get; set; }


}

[ProtoBuf.ProtoContract]
public class t_stUserInfoUserCmdProto : ICommand
{
	[ProtoBuf.ProtoMember(1)]
	public uint version { get; set; }

	
	[ProtoBuf.ProtoMember(2)]
	public SelectUserInfo[] userset { get; set; }

}

[ProtoBuf.ProtoContract]
public class t_stCreateSelectUserCmdProto : ICommand
{
	[ProtoBuf.ProtoMember(1)]
	public uint version { get; set; }
	
	[ProtoBuf.ProtoMember(2)]
	public string strUserName { get; set; }

	[ProtoBuf.ProtoMember(3)]
	public uint jobType { get; set; }

	[ProtoBuf.ProtoMember(4)]
	public uint charType { get; set; }

	[ProtoBuf.ProtoMember(5)]
	public uint country { get; set; }

	[ProtoBuf.ProtoMember(6)]
	public uint suitType { get; set; }

	[ProtoBuf.ProtoMember(7)]
	public string strPromoterName { get; set; }
}

public class stSelectUserCmd :  stNullUserCmd
{
	public const uint		MAX_CHARINFO = 4;

	public const byte  USERINFO_SELECT_USERCMD_PARA              	   = 1;
	public const byte  CREATE_SELECT_USERCMD_PARA				       = 2;
	public const byte  LOGIN_SELECT_USERCMD_PARA		           	   = 3;
	public const byte  DELETE_SELECT_USERCMD_PARA 					   = 4;
	public const byte  CHECKNAME_SELECT_USERCMD_PARA 				   = 5;
	public const byte  RETURN_DELETE_SELECT_USERCMD_PARA 			   = 6;
	public const byte  RQ_GET_NAME_BY_RAND_PARA 					   = 19;
	public const byte  RT_NAME_BY_RAND_PARA 						   = 20;

	public stSelectUserCmd()
	{
		byCmd = SELECT_USERCMD;
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


public    class stUserInfoUserCmd :  stSelectUserCmd
{
	public stUserInfoUserCmd()
	{
		byParam = USERINFO_SELECT_USERCMD_PARA;
		
		
		size=0;
	}
	public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);
		
		byte[] bsize =BitConverter.GetBytes(size);
		stream.Write(bsize,0,bsize.Length);
		
		stream.Write(data,0,(int)size);
	}

    public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);

		
		byte[] bsize=new byte[4];
		stream.Read(bsize,0,4);
		size = BitConverter.ToUInt32(bsize,0);

		data= new byte[size];
		stream.Read(data,0,(int)size);
	}

	public uint size;
	public byte[] data;
}



public    class stCreateSelectUserCmd :  stSelectUserCmd
{
	public stCreateSelectUserCmd()
	{
		byParam = CREATE_SELECT_USERCMD_PARA;
		
		
	
		
	}
    public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);
		
		byte[] bsize =BitConverter.GetBytes(size);
		stream.Write(bsize,0,bsize.Length);
		
		stream.Write(data,0,(int)size);
	}

    public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);
		
		
		byte[] bsize=new byte[4];
		stream.Read(bsize,0,4);
		size = BitConverter.ToUInt32(bsize,0);
		
		data= new byte[size];
		stream.Read(data,0,(int)size);
	}
	public uint size;
	public byte[] data;
}
public    class stLoginSelectUserCmd :  stSelectUserCmd
{
	public stLoginSelectUserCmd()
	{
		byParam = LOGIN_SELECT_USERCMD_PARA;
		
		
		charNo=0;
	}
    public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);

		
		byte[] bcharNo =BitConverter.GetBytes(charNo);
		stream.Write(bcharNo,0,bcharNo.Length);
		
		
	}

    public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);

		
		byte[] bcharNo=new byte[4];
		stream.Read(bcharNo,0,4);
		charNo = BitConverter.ToUInt32(bcharNo,0);
	}

	public uint charNo;
}

public    class stDeleteSelectUserCmd :  stSelectUserCmd
{
	public stDeleteSelectUserCmd()
	{
		byParam = DELETE_SELECT_USERCMD_PARA;
		charNo=0;
	}
    public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);
			
		byte[] bcharNo =BitConverter.GetBytes(charNo);
		stream.Write(bcharNo,0,bcharNo.Length);
	}
    public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);

		byte[] bcharNo=new byte[4];
		stream.Read(bcharNo,0,4);
		charNo = BitConverter.ToUInt32(bcharNo,0);
	}
	public uint charNo;
}

public    class stCheckNameSelectUserCmd :  stSelectUserCmd
{
	public stCheckNameSelectUserCmd()
	{
		byParam = CHECKNAME_SELECT_USERCMD_PARA;
		err_code=0;
	}
    public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);
		stream.Write(name,0,name.Length);
		stream.WriteByte(err_code);
	}
    public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);
		stream.Read(name,0,name.Length);
		err_code=Convert.ToByte(stream.ReadByte());
	}
	public byte[] name=new byte[MAX_NAMESIZE+1];
	public byte err_code;
}

public    class stReturnDeleteSelectUserCmd :  stSelectUserCmd
{
	public stReturnDeleteSelectUserCmd()
	{
		byParam = RETURN_DELETE_SELECT_USERCMD_PARA;
		err_code=0;
	}
    public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);
		stream.Write(name,0,name.Length);
		stream.WriteByte(err_code);
	}
    public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);
		stream.Read(name,0,name.Length);
		err_code=Convert.ToByte(stream.ReadByte());
	}
	public byte[] name=new byte[MAX_NAMESIZE+1];
	public byte err_code;
}

public    class rqGetNameByRandUserCmd :  stSelectUserCmd
{
	public rqGetNameByRandUserCmd()
	{
		byParam = RQ_GET_NAME_BY_RAND_PARA;
		sex=0;
	}
    public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);

		stream.WriteByte(sex);
	}
    public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);
	
		sex=Convert.ToByte(stream.ReadByte());
	}

	public byte sex;
}
