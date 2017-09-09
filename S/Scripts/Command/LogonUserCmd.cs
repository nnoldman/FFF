using System.Collections;
using System.Collections.Generic;
using System.Text;
using System;
using System.IO;   


public class stLogonUserCmd :  stNullUserCmd
{
	public const byte  USER_VERIFY_VER_PARA                 = 1;
	public const byte  USER_REQUEST_LOGIN_PARA              = 2;
	public const byte  SERVER_RETURN_LOGIN_FAILED           = 3;
	public const byte  SERVER_RETURN_LOGIN_OK         		= 4;
	public const byte  PASSWD_LOGON_USERCMD_PARA         	= 5;

	public const byte  GM_REQUEST_LOGIN_PARA         		= 11;
	public stLogonUserCmd()
	{
		byCmd = LOGON_USERCMD;
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
public    class stUserVerifyVerCmd :  stLogonUserCmd
{
	public stUserVerifyVerCmd()
	{
		byParam = USER_VERIFY_VER_PARA;
		reserve=0;
		version=0;
	}
	public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);
		byte[] breserve =BitConverter.GetBytes(reserve);
		stream.Write(breserve,0,breserve.Length);
		
		byte[] bversion =BitConverter.GetBytes(version);
		stream.Write(bversion,0,bversion.Length);
		
		
	}
	
	public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);
		byte[] breserve=new byte[4];
		stream.Read(breserve,0,4);
		reserve = BitConverter.ToUInt32(breserve,0);
		
		byte[] bversion=new byte[4];
		stream.Read(bversion,0,4);
		version = BitConverter.ToUInt32(bversion,0);
	}
	public uint reserve;
	public uint version;
}
public    class stServerReturnLoginFailedCmd :  stLogonUserCmd
{
	public stServerReturnLoginFailedCmd()
	{
		byParam = SERVER_RETURN_LOGIN_FAILED;
		sdReturnCode=0;

	}
	public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);
		stream.WriteByte(sdReturnCode);
		
		
	}
	
	public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);
		sdReturnCode=Convert.ToByte(stream.ReadByte());
	}
	public byte sdReturnCode;

}


public    class stServerReturnLoginSuccessCmd :  stLogonUserCmd
{
	public stServerReturnLoginSuccessCmd()
	{
		byParam = SERVER_RETURN_LOGIN_OK;
		dwUserID=0;
		loginTempID=0;
		port=0;
	}
	public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);
		byte[] bdwUserID =BitConverter.GetBytes(dwUserID);
		stream.Write(bdwUserID,0,bdwUserID.Length);
		
		byte[] bloginTempID =BitConverter.GetBytes(loginTempID);
		stream.Write(bloginTempID,0,bloginTempID.Length);
		
		
		stream.Write(domain,0,domain.Length);
		
		byte[] bport =BitConverter.GetBytes(port);
		stream.Write(bport,0,bport.Length);
		
		
	}
	
	public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);
		byte[] bdwUserID=new byte[8];
		stream.Read(bdwUserID,0,8);
		dwUserID = BitConverter.ToUInt64(bdwUserID,0);
		
		byte[] bloginTempID=new byte[4];
		stream.Read(bloginTempID,0,4);
		loginTempID = BitConverter.ToUInt32(bloginTempID,0);
		
		
		stream.Read(domain,0,domain.Length);
		
		byte[] bport=new byte[2];
		stream.Read(bport,0,2);
		port = BitConverter.ToUInt16(bport,0);
	}
	public UInt64 dwUserID;
	public uint loginTempID;
	public byte[] domain =new byte[MAX_NAMESIZE+1];
	public ushort port;
}
public    class stPasswdLogonUserCmd :  stLogonUserCmd
{
	public stPasswdLogonUserCmd()
	{
		byParam = PASSWD_LOGON_USERCMD_PARA;
		loginTempID=0;
		dwUserID=0;
	}
	public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);

		
		byte[] bloginTempID =BitConverter.GetBytes(loginTempID);
		stream.Write(bloginTempID,0,bloginTempID.Length);

		byte[] bdwUserID =BitConverter.GetBytes(dwUserID);
		stream.Write(bdwUserID,0,bdwUserID.Length);

		stream.Write(pstrName,0,pstrName.Length);
		stream.Write(pstrPassword,0,pstrPassword.Length);
	}
	
	public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);

	
		
		byte[] bloginTempID=new byte[4];
		stream.Read(bloginTempID,0,4);
		loginTempID = BitConverter.ToUInt32(bloginTempID,0);

		byte[] bdwUserID=new byte[8];
		stream.Read(bdwUserID,0,8);
		dwUserID = BitConverter.ToUInt64(bdwUserID,0);

		stream.Read(pstrName,0,pstrName.Length);
		stream.Read(pstrPassword,0,pstrPassword.Length);
	}

	public uint loginTempID; // sid长度
	public UInt64 dwUserID;
	public byte[] pstrName =new byte[MAX_ACCNAMESIZE];
	public byte[] pstrPassword =new byte[MAX_PASSWORD];
}

public    class stGMRequestLoginCmd :  stLogonUserCmd
{
	public stGMRequestLoginCmd()
	{
		byParam = GM_REQUEST_LOGIN_PARA;
		wdSize=0;
	}
    public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);
		byte[] bwdSize =BitConverter.GetBytes(wdSize);
		stream.Write(bwdSize,0,bwdSize.Length);
		
		stream.Write(sid,0,wdSize);
		
	}
	
	public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);
		byte[] bwdSize=new byte[2];
		stream.Read(bwdSize,0,2);
		wdSize = BitConverter.ToUInt16(bwdSize,0);
		
		//		stream.Read(sid,0,wdSize);
	}
	//	public uint getSize()  
	//	{
	//		return sizeof(*this ) + wdSize;
	//	}
	
	// 只需验证SID
	public ushort wdSize; // sid长度
	public byte[] sid;
	//char sid[0]; 
}

