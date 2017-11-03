using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;
using System;
using System.IO;
using System.Threading;
using System.Net;
using System.Net.Sockets;

public enum NetEventID
{
    Success = 0,
    BeginConnect = 1,
    CloseForInitialize = 2,
    CloseForLoginGame = 3,
    OnTimeOut = 4,
    OnDisconnect = 5,
    ActiveDisconnect = 6,
    CloseByExitGame = 7,
    NetworkUnreachable = 8,
    Exception = 9,
}

public class Connection
{
    public string host;
    public int port;
    public object userToken;
    public Action onConnectSucessed;
    public Action<SocketError> onConnectFailed;
}

public class SocketBase
{
    public delegate void MessageHanlder( byte[] data);
    public System.Action<int> errorHandler;
    public MessageHanlder messageHandler;
    private const uint HeaderLength = 4;
    private const int kBufferSize = 2 << 16;

    public bool Interrupted = false;

    private uint gameTime_;
    private Socket socket_ = null;
    private bool tryConnecting_ = false;
    private uint targetLength_ = HeaderLength;
    private byte[] header_ = new byte[HeaderLength];
    private uint headerData_ = 0;
    private List<NetEventID> events_ = new List<NetEventID>();
    private Queue<byte[]> commands_ = new Queue<byte[]>();
    private List<byte[]> messages_ = new List<byte[]>();
    private object queueLocker_ = new object();
    private bool connected_ = false;
    private byte[] sendBuffer_ = new byte[kBufferSize];
    private int sleepTimeMS_ = 15;
    private Thread readThread_;

    public bool connected
    {
        get
        {
            return socket_ != null;
        }
    }

    public SocketBase()
    {
    }

    void RecreateNetReader()
    {
        DestroyNetReader();
        readThread_ = new Thread(ClientReceive);
        readThread_.Start();
    }

    void DestroyNetReader()
    {
        if (readThread_ != null)
        {
            readThread_.Abort();
            readThread_ = null;
        }
    }

    void OnDestroy()
    {
        Closed(NetEventID.ActiveDisconnect);
    }

    public void connect(Connection connection)
    {
        Closed(NetEventID.CloseForInitialize);
        IPAddress[] address = Dns.GetHostAddresses(connection.host);
        if (address[0].AddressFamily == AddressFamily.InterNetworkV6)
        {
            Debug.Log("InterNetworkV6 " + address[0]);
            socket_ = new Socket(AddressFamily.InterNetworkV6, SocketType.Stream, ProtocolType.Tcp);
        }
        else
        {
            Debug.Log("InterNetwork " + address[0]);
            socket_ = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }

        IPAddress ipa = address[0];
        IPEndPoint iep = new IPEndPoint(ipa, connection.port);

        try
        {
            socket_.ReceiveTimeout = 2000;
            socket_.SendTimeout = 2000;
            socket_.ReceiveBufferSize = kBufferSize;

            RecreateNetReader();
            SocketAsyncEventArgs args = new SocketAsyncEventArgs();
            args.Completed += Args_Completed;
            args.RemoteEndPoint = iep;
            args.UserToken = connection;
            socket_.ConnectAsync(args);
            events_.Add(NetEventID.BeginConnect);
        }
        catch (SocketException ex)
        {
            Debug.Log(ex.Message);
            ProcessError(ex.SocketErrorCode, false);
        }
    }

    private void Args_Completed(object sender, SocketAsyncEventArgs e)
    {
        e.Completed -= Args_Completed;

        SocketError error = e.SocketError;
        Connection connection = (Connection)e.UserToken;
        try
        {
            switch (error)
            {
                case SocketError.Success:
                {
                    if (socket_.Connected)
                    {
                        if (connection.onConnectSucessed != null)
                            connection.onConnectSucessed();
                    }
                }
                break;
                default:
                {
                    if (connection.onConnectFailed != null)
                        connection.onConnectFailed(error);
                    ProcessError(error, false);
                }
                break;
            }
        }
        catch (SocketException ex)
        {
            Debug.Log(ex.Message);
            ProcessError(ex.SocketErrorCode, false);
        }
    }

    SocketError GetAsysnErrorCode(IAsyncResult ar)
    {
        SocketError error = SocketError.SocketError;
        System.Reflection.PropertyInfo propinfo = ar.GetType().GetProperty("ErrorCode");
        if(propinfo != null)
            error = (SocketError)propinfo.GetValue(ar, null);
        return error;
    }

    void ProcessError(SocketError error, bool acitve)
    {
        switch (error)
        {
            case SocketError.TimedOut:
            case SocketError.ConnectionRefused:
                events_.Add(NetEventID.OnTimeOut);
                break;
            case SocketError.NotConnected:
            case SocketError.ConnectionReset:
            case SocketError.ConnectionAborted:
                events_.Add(NetEventID.OnDisconnect);
                break;
            case SocketError.NetworkUnreachable:
                events_.Add(NetEventID.NetworkUnreachable);
                break;
            default:
            {
                Debug.LogError("ProcessError " + error.ToString());
            }
            break;
        }
    }

    void ClientReceive()
    {
        while (true)
        {
            if (socket_ != null)
            {
                bool connecting  = socket_.Connected;
                if (connecting)
                {
                    if (socket_.Available > 0)
                        Read();
                    else
                        Thread.Sleep(sleepTimeMS_);
                }
                else if(connected_)
                {
                    Closed(NetEventID.OnDisconnect);
                }
                connected_ = connecting;
            }
            else
            {
                Thread.Sleep(sleepTimeMS_);
            }
        }
    }

    void Read()
    {
        if (socket_.Available < targetLength_)
            return;
        try
        {
            if (headerData_ == 0)
            {
                int ret = socket_.Receive(header_, (int)HeaderLength, 0);//将数据从连接的   Socket   接收到接收缓冲区的特定位置。
                //Debug.Log("read ret:" + ret.ToString());
                if (ret == 0)
                {
                    //socket连接已断开,调用处理方法,服务器断开连接
                    Debug.Log("read 0");
                    Closed(NetEventID.OnDisconnect);
                    return;
                }
                headerData_ = BitConverter.ToUInt32(header_, 0);
                //Debug.Log("read _packHead:" + _packHead.ToString());
                targetLength_ = (headerData_ & 0x0000FFFF);
            }
            else
            {
                byte[] bytesArray = new byte[targetLength_];
                int ret = socket_.Receive(bytesArray, 0, (int)targetLength_, SocketFlags.None);
#if UNITY_EDITOR
                Debug.Assert(ret == targetLength_);
#endif
                lock (queueLocker_)
                {
                    commands_.Enqueue(bytesArray);
                }
                targetLength_ = HeaderLength;
                headerData_ = 0;
            }
        }
        catch (SocketException exc)
        {
            Debug.Log(exc.Message);
            ProcessError(exc.SocketErrorCode, false);
        }
    }

    public void Closed(NetEventID netevent)
    {
        DestroyNetReader();

        messages_.Clear();
        commands_.Clear();

        if (socket_ != null && socket_.Connected)
        {
            try
            {
                socket_.Shutdown(SocketShutdown.Both);
            }
            catch (SocketException ex)
            {
                Debug.Log(ex.Message);
                //ProcessError(ex.SocketErrorCode,manual);
            }
            socket_.Close();
            Debug.Log("Main socket Closed ");
        }

        connected_ = false;
        socket_ = null;
        events_.Add(netevent);
        targetLength_ = HeaderLength;
        headerData_ = 0;
    }


    public void Send(MemoryStream data)
    {
        if (!socket_.Connected)//判断Socket是否已连接
            return;


        byte[] head = new byte[4];
        head = BitConverter.GetBytes(data.Length);

        Array.Copy(head, 0, sendBuffer_, 0, 4);
        Array.Copy(data.GetBuffer(), 0, sendBuffer_, 4, data.Length);

        try
        {
            socket_.Send(sendBuffer_, 0, (int)data.Length + 4, SocketFlags.None);
        }
        catch (SocketException exc)
        {
            ProcessError(exc.SocketErrorCode, false);
        }
    }



    public void UpdateMessageQueue()
    {
        if(events_.Count > 0)
        {
            for (int i = 0; i < events_.Count; ++i)
            {
                if (errorHandler != null)
                    errorHandler((int)events_[i]);
            }
            events_.Clear();
            return;
        }

        if (socket_ == null || Interrupted)
            return;

        lock (queueLocker_)
        {
            while (commands_.Count > 0)
                messages_.Add(commands_.Dequeue());
        }

        if (messages_.Count > 0)
        {
            int i = 0;

            for (; i < messages_.Count; i++)
            {
                byte[] data = messages_[i];
                if(data.Length > 0 && messageHandler != null)
                    messageHandler(data);

                if (Interrupted)
                {
                    messages_.RemoveRange(0, i + 1);
                    break;
                }
            }
        }

        if (!Interrupted)
            messages_.Clear();
    }

}

