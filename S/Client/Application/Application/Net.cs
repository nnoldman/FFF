using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

public class LoginParam
{
    public string user;
    public string psw;
    public string host;
    public int port;
    public int serverID;
}

public class Net
{
    enum ConnectionID
    {
        Login,
        Game,
    }
    public string errorString;

    LoginParam mLoginParam;

    NetInterface mNetInterface;
    public Net()
    {
        mNetInterface = new NetInterface(true);
        mNetInterface.onNetConnected += OnConnected;
        mNetInterface.onMessage = Dispatch;
    }
    void OnConnected(bool connected, SocketError errorcode, int connectionID)
    {
        if (connected)
        {
            if (connectionID == (int)ConnectionID.Login)
            {
                Debug.Log("Connected login server successfully!");

                ClientToLogin_RqGameServerInfo pkg = new ClientToLogin_RqGameServerInfo();
                pkg.serverID = 5;
                Send(pkg);
            }
            else if (connectionID == (int)ConnectionID.Game)
            {
                Debug.Log("Connected game server successfully!");
                rqLoginGame pkg = new rqLoginGame();
                pkg.user = mLoginParam.user;
                pkg.psw = mLoginParam.psw;
                Send(pkg);
            }
        }
        else
        {
            switch(errorcode)
            {
                case SocketError.ConnectionRefused:
                    {
                        Debug.LogError("远程主机正在主动拒绝连接");
                    }
                    break;
            }
        }
    }
    public void ConnectLoginServer(LoginParam param)
    {
        mLoginParam = param;
        mNetInterface.Connect(param.host, param.port, (int)ConnectionID.Login);
    }

    void ConnectGameServer(LoginParam param)
    {
        mNetInterface.Connect(param.host, param.port, (int)ConnectionID.Game);
    }

    public void Send(PKG pkg)
    {
        if (mNetInterface != null)
            mNetInterface.Send(pkg.GetBytes());
    }

    public void Dispatch(byte[] msg)
    {
        PKG pkg = GetPKG<PKG>(msg);

        switch (pkg.opcode)
        {
            case OPCODE.ID.ClientLogin:
                {
                    switch ((OPCODE.ClientLoginType)pkg.childid)
                    {
                        case OPCODE.ClientLoginType.RtGameServerInfo:
                            {
                                ClientToLogin_RtGameServerInfo cmd = GetPKG<ClientToLogin_RtGameServerInfo>(msg);

                                LoginParam param = new LoginParam();
                                param.user = mLoginParam.user;
                                param.psw = mLoginParam.psw;
                                param.host = cmd.host;
                                param.port = cmd.port;

                                ConnectGameServer(param);
                            }
                            break;
                    }
                }
                break;
            case OPCODE.ID.CenterClient:
                {
                    switch ((OPCODE.CenterClientType)pkg.childid)
                    {
                        case OPCODE.CenterClientType.RtAccount:
                            {
                            }
                            break;
                        case OPCODE.CenterClientType.RtLogin:
                            {
                                rtLoginGame cmd = GetPKG<rtLoginGame>(msg);

                                if (cmd.errorCode == LoginErrorCode.Sucessed)
                                {
                                    Debug.Log("Server=>Connected game server successfully!");
                                }
                            }
                            break;
                    }
                }
                break;
        }
    }
    public T GetPKG<T>(byte[] msg) where T : PKG
    {
        return (T)PKG.BytesToStruct(msg, msg.Length, typeof(T));
    }
    public static T Parse<T>(byte[] msg) where T : PKG
    {
        MemoryStream stream = new MemoryStream(msg);
        T protoBuffer = ProtoBuf.Serializer.Deserialize<T>(stream);
        return protoBuffer;
    }

    public void Update()
    {
        if (mNetInterface != null)
            mNetInterface.UpdateMessageQueue();
    }
}
