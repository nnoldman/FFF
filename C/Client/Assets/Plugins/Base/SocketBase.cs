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

public enum NetEventID {
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

public class Connection {
    public string host;
    public int port;
    public object userToken;

    public Action onConnectSucessed;
    public Action<SocketError> onConnectFailed;
}

public class SocketBase {
    public delegate void MessageHanlder( byte[] data);

    public System.Action<int> errorHandler;
    public MessageHanlder messageHandler;

    private const uint COMPRESS = 0x40000000;
    private Boolean UseComPress = true;
    private const uint HeaderLength = 4;
    private uint mTargetLength = HeaderLength;

    private uint mHeader = 0;

    private int _counterSend;

    private Boolean _isMainSocket;

    public static Socket ClientSocket = null;
    byte[] mHeaderData = new byte[HeaderLength];


    public const int kBufferSize = 2 << 16;

    public uint _mGameTime;
    private Queue<byte[]> mDataQueue = new Queue<byte[]>();
    private object mQueueLock = new object();
    private List<byte[]> mCommandList = new List<byte[]>();

    private List<NetEventID> mNetEvents = new List<NetEventID>();

    public bool TryConnecting = false;
    public bool Interrupted = false;

    private bool mCanReceive = false;
    private bool mConnecting = false;
    private Thread mThreadReader;
    private int mSleepTimeMS = 15;

    private byte[] sendBuffer_ = new byte[kBufferSize];

    public bool connected {
        get {
            return ClientSocket != null;
        }
    }

    public uint lastServerTime {
        get {
            return _mGameTime;
        }
        set {
            _mGameTime = value;
        }
    }

    public SocketBase() {
    }

    void RecreateNetReader() {
        DestroyNetReader();
        mThreadReader = new Thread(ClientReceive);
        mThreadReader.Start();
    }

    void DestroyNetReader() {
        if (mThreadReader != null) {
            mThreadReader.Abort();
            mThreadReader = null;
        }
    }

    void OnDestroy() {
        Closed(NetEventID.ActiveDisconnect);
    }

    public void connect(Connection connection) {
        Closed(NetEventID.CloseForInitialize);
        IPAddress[] address = Dns.GetHostAddresses(connection.host);
        if (address[0].AddressFamily == AddressFamily.InterNetworkV6) {
            Debug.Log("InterNetworkV6 " + address[0]);
            ClientSocket = new Socket(AddressFamily.InterNetworkV6, SocketType.Stream, ProtocolType.Tcp);
        } else {
            Debug.Log("InterNetwork " + address[0]);
            ClientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }

        IPAddress ipa = address[0];
        IPEndPoint iep = new IPEndPoint(ipa, connection.port);

        try {
            ClientSocket.ReceiveTimeout = 2000;
            ClientSocket.SendTimeout = 2000;
            ClientSocket.ReceiveBufferSize = kBufferSize;

            RecreateNetReader();
            SocketAsyncEventArgs args = new SocketAsyncEventArgs();
            args.Completed += Args_Completed;
            args.RemoteEndPoint = iep;
            args.UserToken = connection;
            ClientSocket.ConnectAsync(args);
            mNetEvents.Add(NetEventID.BeginConnect);
        } catch (SocketException ex) {
            Debug.Log(ex.Message);
            ProcessError(ex.SocketErrorCode, false);
        }
    }

    private void Args_Completed(object sender, SocketAsyncEventArgs e) {
        e.Completed -= Args_Completed;

        SocketError error = e.SocketError;
        Connection connection = (Connection)e.UserToken;
        try {
            switch (error) {
            case SocketError.Success: {
                if (ClientSocket.Connected) {
                    if (connection.onConnectSucessed!=null)
                        connection.onConnectSucessed();
                }
            }
            break;
            default: {
                if (connection.onConnectFailed != null)
                    connection.onConnectFailed(error);
            }
            ProcessError(error, false);
            break;
            }
        } catch (SocketException ex) {
            Debug.Log(ex.Message);
            ProcessError(ex.SocketErrorCode, false);
        }
    }

    SocketError GetAsysnErrorCode(IAsyncResult ar) {
        SocketError error = SocketError.SocketError;
        System.Reflection.PropertyInfo propinfo = ar.GetType().GetProperty("ErrorCode");
        if(propinfo != null)
            error = (SocketError)propinfo.GetValue(ar, null);
        return error;
    }

    void ProcessError(SocketError error, bool acitve) {
        switch (error) {
        case SocketError.TimedOut:
        case SocketError.ConnectionRefused:
            mNetEvents.Add(NetEventID.OnTimeOut);
            break;
        case SocketError.NotConnected:
        case SocketError.ConnectionReset:
        case SocketError.ConnectionAborted:
            mNetEvents.Add(NetEventID.OnDisconnect);
            break;
        case SocketError.NetworkUnreachable:
            mNetEvents.Add(NetEventID.NetworkUnreachable);
            break;
        default: {
            Debug.Log("ProcessError " + error.ToString());
            throw new SocketException((int)error);
        }
        }
    }

    void ClientReceive() {
        while (true) {
            if (ClientSocket != null) {
                bool connecting  = ClientSocket.Connected;
                if (connecting) {
                    if (ClientSocket.Available > 0)
                        read();
                    else
                        Thread.Sleep(mSleepTimeMS);
                } else if(mConnecting) {
                    Closed(NetEventID.OnDisconnect);
                }
                mConnecting = connecting;
            } else {
                Thread.Sleep(mSleepTimeMS);
            }
        }
    }

    void read() {
        if (ClientSocket.Available < mTargetLength)
            return;
        try {
            if (mHeader == 0) {
                int ret = ClientSocket.Receive(mHeaderData, (int)HeaderLength, 0);//将数据从连接的   Socket   接收到接收缓冲区的特定位置。
                //Debug.Log("read ret:" + ret.ToString());
                if (ret == 0) {
                    //socket连接已断开,调用处理方法,服务器断开连接
                    Debug.Log("read 0");
                    Closed(NetEventID.OnDisconnect);
                    return;
                }
                mHeader = BitConverter.ToUInt32(mHeaderData, 0);
                //Debug.Log("read _packHead:" + _packHead.ToString());
                mTargetLength = (mHeader & 0x0000FFFF);
            } else {
                byte[] bytesArray = new byte[mTargetLength];
                int ret = ClientSocket.Receive(bytesArray, 0, (int)mTargetLength, SocketFlags.None);
#if UNITY_EDITOR
                Debug.Assert(ret == mTargetLength);
#endif
                lock (mQueueLock) {
                    mDataQueue.Enqueue(bytesArray);
                }
                mTargetLength = HeaderLength;
                mHeader = 0;
            }
        } catch (SocketException exc) {
            Debug.Log(exc.Message);
            ProcessError(exc.SocketErrorCode, false);
        }
    }

    public void Closed(NetEventID netevent) {
        DestroyNetReader();

        mCommandList.Clear();
        mDataQueue.Clear();

        if (ClientSocket != null && ClientSocket.Connected) {
            try {
                ClientSocket.Shutdown(SocketShutdown.Both);
            } catch (SocketException ex) {
                Debug.Log(ex.Message);
                //ProcessError(ex.SocketErrorCode,manual);
            }
            ClientSocket.Close();
            Debug.Log("Main socket Closed ");
        }

        mConnecting = false;
        ClientSocket = null;
        mNetEvents.Add(netevent);
        mTargetLength = HeaderLength;
        mHeader = 0;
    }


    public void send(MemoryStream data) {
        if (!ClientSocket.Connected)//判断Socket是否已连接
            return;


        byte[] head = new byte[4];
        head = BitConverter.GetBytes(data.Length);

        Array.Copy(head, 0, sendBuffer_, 0, 4);
        Array.Copy(data.GetBuffer(), 0, sendBuffer_, 4, data.Length);

        try {
            ClientSocket.Send(sendBuffer_, 0, (int)data.Length + 4, SocketFlags.None);
        } catch (SocketException exc) {
            ProcessError(exc.SocketErrorCode, false);
        }
    }



    public void UpdateMessageQueue() {
        if(mNetEvents.Count > 0) {
            for (int i = 0; i < mNetEvents.Count; ++i) {
                if (errorHandler != null)
                    errorHandler((int)mNetEvents[i]);
            }
            mNetEvents.Clear();
            return;
        }

        if (ClientSocket == null || Interrupted)
            return;

        lock (mQueueLock) {
            while (mDataQueue.Count > 0)
                mCommandList.Add(mDataQueue.Dequeue());
        }

        if (mCommandList.Count > 0) {
            int i = 0;

            for (; i < mCommandList.Count; i++) {
                byte[] data = mCommandList[i];
                if(data.Length > 0 && messageHandler != null)
                    messageHandler(data);

                if (Interrupted) {
                    mCommandList.RemoveRange(0, i + 1);
                    break;
                }
            }
        }

        if (!Interrupted)
            mCommandList.Clear();
    }

}

