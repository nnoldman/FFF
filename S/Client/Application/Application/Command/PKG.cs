using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
namespace OPCODE
{
    public enum ID : int
    {
        None,

        ClientLogin,

        CenterLogin,

        CenterClient,

        Create_Account,

        DBData,

        Protocolbuf,
    };

    enum LoginToCenterType : int
    {
        L2C_User,
    };
    enum ClientLoginType
    {
        RqGameServerInfo,
        RtGameServerInfo,
    };
    enum CenterLoginType
    {
        AppStart,
        AppInfo,
    };
    enum CenterClientType
    {
        RqLogin,
        RqAccount,

        RtLogin,
        RtAccount,

        ClientMessage,
        ServerMessage,
    };
}
public enum Default
{
    NameSize = 24,
    PasswordSize = 24,
    HostSize = 256,
    DataSize = 1024,
};

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public class PKG
{
    public OPCODE.ID opcode = OPCODE.ID.None;

    public int childid = 0;

    public static implicit operator bool(PKG cmd)
    {
        return cmd != null;
    }
    public byte[] GetBytes()
    {
        int rawsize = Marshal.SizeOf(this);
        IntPtr buffer = Marshal.AllocHGlobal(rawsize);
        Marshal.StructureToPtr(this, buffer, false);
        byte[] rawdatas = new byte[rawsize];
        Marshal.Copy(buffer, rawdatas, 0, rawsize);
        Marshal.FreeHGlobal(buffer);
        return rawdatas;
    }

    public static object BytesToStruct(byte[] buf, int len, Type type)
    {
        object rtn;
        IntPtr buffer = Marshal.AllocHGlobal(len);
        Marshal.Copy(buf, 0, buffer, len);
        rtn = Marshal.PtrToStructure(buffer, type);
        Marshal.FreeHGlobal(buffer);
        return rtn;
    }

};

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public class ClientToLoginPKG : PKG
{
    public ClientToLoginPKG()
    {
        opcode = OPCODE.ID.ClientLogin;
    }
};
[StructLayout(LayoutKind.Sequential, Pack = 1)]
public class PKG_CenterClient : PKG
{
    public PKG_CenterClient()
    {
        opcode = OPCODE.ID.CenterClient;
    }
};

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public class ClientToLogin_RqGameServerInfo : ClientToLoginPKG
{
    public int serverID;
    public ClientToLogin_RqGameServerInfo()
    {
        childid = (int)OPCODE.ClientLoginType.RqGameServerInfo;
        serverID = 0;
    }
};

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public class ClientToLogin_RtGameServerInfo : ClientToLoginPKG
{
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = (int)Default.HostSize)]
    public string host;
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = (int)Default.NameSize)]
    public string name;

    public int port;

    public ClientToLogin_RtGameServerInfo()
    {
        childid = (int)OPCODE.ClientLoginType.RtGameServerInfo;
        port = 0;
    }
};

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public class rqClientMessage : PKG_CenterClient
{
    public UInt32 count;

    public char[] data;

    public rqClientMessage()
    {
        count = 0;
        childid = (int)OPCODE.CenterClientType.ClientMessage;
    }
};
public enum LoginErrorCode
{
    LoginErrorCode_None,
    Sucessed,
    UserCantFind,
    PasswordError,
};
[StructLayout(LayoutKind.Sequential, Pack = 1)]
public class rqLoginGame : PKG_CenterClient
{
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = (int)Default.NameSize)]
    public string user;
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = (int)Default.NameSize)]
    public string psw;
    public rqLoginGame()
    {
        childid = (int)OPCODE.CenterClientType.RqLogin;
    }
};
[StructLayout(LayoutKind.Sequential, Pack = 1)]
public class rtLoginGame : PKG_CenterClient
{
    public LoginErrorCode errorCode;

    public rtLoginGame()
    {
        childid = (int)OPCODE.CenterClientType.RtLogin;
    }
};