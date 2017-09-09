using System.Collections;
using System.Collections.Generic;
using System.Text;
using System;
using System.IO;   

public class   stNullUserCmd
{


	public const uint MAX_PASSWORD 		=16;

	

	public const uint MAX_NAMESIZE    	=64;
	
  
	public const uint MAX_DOMAINSIZE  	=64;

	public const uint MAX_ACCNAMESIZE 	=48;



	// constant values.
	public const byte  NULL_USERCMD                 = 0;
	public const byte  TIME_USERCMD                 = 1;
	public const byte  LOGON_USERCMD                = 2;
	public const byte  DATA_USERCMD					= 4;
	public const byte  MAPSCREEN_USERCMD			= 7;

	public const byte  SELECT_USERCMD               = 19;

	public const byte  SCRIPT_USERCMD           	= 30;
    public const byte  MOBILEUNITY_USERCMD          = 53;

	public stNullUserCmd()
	{
		byCmd=NULL_USERCMD;
		byParam=NULL_USERCMD;
		dwTimestamp=0;
	}
	
    void writeHeader(MemoryStream stream)
    {
        stream.WriteByte(byCmd);
        stream.WriteByte(byParam);
        byte[] bpara = BitConverter.GetBytes(dwTimestamp);
        stream.Write(bpara, 0, bpara.Length);
        //Debug.Log("byCmd=" + byCmd + " byParam" + byParam + " dwTimestamp" + dwTimestamp + " length" + bpara.Length + " bpara" + bpara.ToString());
    }
    protected virtual stNullUserCmd write(MemoryStream stream)
    {
        return this;
    }
	public virtual void serialize(MemoryStream stream)  
	{
        writeHeader(stream);
        write(stream);
    }

    public virtual void unserialize(MemoryStream stream) 
	{
		byCmd=Convert.ToByte(stream.ReadByte());
		byParam=Convert.ToByte(stream.ReadByte());
		byte[] bpara=new byte[4];
		stream.Read(bpara,0,4);
		dwTimestamp = BitConverter.ToUInt32(bpara,0);
	}
	
	public  byte    byCmd;
	
	public  byte    byParam;
	
	
	
	
	public uint   dwTimestamp;
}