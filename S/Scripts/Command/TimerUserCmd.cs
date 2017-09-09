using System.Collections;
using System.Collections.Generic;
using System.Text;
using System;
using System.IO;   


public class stTimerUserCmd :  stNullUserCmd
{
	public const byte  GAMETIME_TIMER_USERCMD_PARA              	   = 1;
	public const byte  REQUESTUSERGAMETIME_TIMER_USERCMD_PARA          = 2;
	public const byte  USERGAMETIME_TIMER_USERCMD_PARA           	   = 3;

	public stTimerUserCmd()
	{
		byCmd = TIME_USERCMD;
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

public    class stGameTimeTimerUserCmd :  stTimerUserCmd
{
	public stGameTimeTimerUserCmd()
	{
		byParam = GAMETIME_TIMER_USERCMD_PARA;
		qwGameTime=0;
		curServerTime=0;
	}
    public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);
		byte[] bqwGameTime =BitConverter.GetBytes(qwGameTime);
		stream.Write(bqwGameTime,0,bqwGameTime.Length);
		
		byte[] bcurServerTime =BitConverter.GetBytes(curServerTime);
		stream.Write(bcurServerTime,0,bcurServerTime.Length);
		
		
	}

    public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);
		byte[] bqwGameTime=new byte[4];
		stream.Read(bqwGameTime,0,4);
		qwGameTime = BitConverter.ToUInt32(bqwGameTime,0);
		
		byte[] bcurServerTime=new byte[4];
		stream.Read(bcurServerTime,0,4);
		curServerTime = BitConverter.ToUInt32(bcurServerTime,0);
	}
	public uint qwGameTime;
	public uint curServerTime;
}
public    class stRequestUserGameTimeTimerUserCmd :  stTimerUserCmd
{
	public stRequestUserGameTimeTimerUserCmd()
	{
		byParam = REQUESTUSERGAMETIME_TIMER_USERCMD_PARA;

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

public    class stUserGameTimeTimerUserCmd :  stTimerUserCmd
{
	public stUserGameTimeTimerUserCmd()
	{
		byParam = USERGAMETIME_TIMER_USERCMD_PARA;
		dwUserTempID=0;
		qwGameTime=0;
	}
    public override void serialize(MemoryStream stream) 
	{
		base.serialize(stream);
		byte[] bdwUserTempID =BitConverter.GetBytes(dwUserTempID);
		stream.Write(bdwUserTempID,0,bdwUserTempID.Length);
		
		byte[] bqwGameTime =BitConverter.GetBytes(qwGameTime);
		stream.Write(bqwGameTime,0,bqwGameTime.Length);
		
		
	}

    public override void unserialize(MemoryStream stream) 
	{
		base.unserialize(stream);
		byte[] bdwUserTempID=new byte[4];
		stream.Read(bdwUserTempID,0,4);
		dwUserTempID = BitConverter.ToUInt32(bdwUserTempID,0);
		
		byte[] bqwGameTime=new byte[4];
		stream.Read(bqwGameTime,0,4);
		qwGameTime = BitConverter.ToUInt32(bqwGameTime,0);
	}
	public uint dwUserTempID;
	public uint qwGameTime;
}

