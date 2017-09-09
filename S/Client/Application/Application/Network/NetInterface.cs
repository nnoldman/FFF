using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;
using System;
using System.IO;
using System.Threading;
using System.Net;
using System.Net.Sockets;

public class NetInterface
{
    public delegate void NetAction(bool connected, SocketError errorcode, int connectionID);

    public NetAction onNetConnected;

    public Action<byte[]> onMessage;

    static uint HeaderLength = 4;

    Queue<byte[]> mDataQueue;

    List<byte[]> mCommands;

    object mLocker;

    bool mConnecting = false;

    bool mAnsy = true;

    Socket mSocket;

    Thread mAcceptThread;

    public bool connected
    {
        get
        {
            return mSocket != null && mSocket.Connected;
        }
    }
    public bool connecting
    {
        get
        {
            return mConnecting;
        }
    }

    public NetInterface(bool ansy)
    {
        mDataQueue = new Queue<byte[]>();
        mCommands = new List<byte[]>();
        mLocker = new object();
        mAnsy = ansy;
    }
    ~NetInterface()
    {
        Clean(true);
    }
    void Clean(bool manual = false)
    {
        if (mSocket != null)
        {
            if(mSocket.Connected)
                mSocket.Shutdown(SocketShutdown.Both);
            mSocket.Close();
            mSocket = null;
        }
        mCommands.Clear();
        mDataQueue.Clear();
        mAcceptThread = null;
    }
    class ConnectArg : SocketAsyncEventArgs
    {
        public Action<SocketAsyncEventArgs> callBack;
        protected override void OnCompleted(System.Net.Sockets.SocketAsyncEventArgs e)
        {
            if (callBack != null)
                callBack(e);
        }
    }
    void OnConnect(SocketAsyncEventArgs arg)
    {
        int connectionID = (int)arg.UserToken;

        if (arg.SocketError == SocketError.Success && mSocket.Connected)
        {
            mConnecting = false;
            onNetConnected.Invoke(true, SocketError.Success, connectionID);
            BeginAccept();
        }
        else
        {
            onNetConnected.Invoke(false, arg.SocketError, connectionID);
        }
    }
    public void Connect(string host, int port, int connectionID)
    {
        Clean();

        mSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        IPAddress ipa = IPAddress.Parse(host);
        IPEndPoint iep = new IPEndPoint(ipa, port);

        if (mAnsy)
        {
            ConnectArg arg = new ConnectArg();
            arg.AcceptSocket = mSocket;
            arg.callBack = OnConnect;
            arg.RemoteEndPoint = iep;
            arg.UserToken = connectionID;
            bool res = mSocket.ConnectAsync(arg);
            mConnecting = true;
        }
        else
        {
            try
            {
                mSocket.Connect(iep);//连接到服务器
            }
            catch (SocketException exc)
            {
                onNetConnected.Invoke(false, (SocketError)exc.ErrorCode, connectionID);
            }
            onNetConnected.Invoke(true, SocketError.Success, connectionID);
            BeginAccept();
        }
    }

    void BeginAccept()
    {
        mAcceptThread = new Thread(ReceiveFunc);
        mAcceptThread.Start();
    }


    void ProcessError(SocketError error, bool manual)
    {
        //switch (error)
        //{
        //    case SocketError.TimedOut:
        //        {
        //            Net.errorString = "连接服务器超时！";
        //        }
        //        break;
        //    case SocketError.NotConnected:
        //        {
        //            Net.errorString = "服务器断开连接！";
        //        }
        //        break;
        //}
        //if (!manual)
        //{
        //    Net.isClosed = true;
        //    Net.manualClosed = false;
        //}
    }

    void ReceiveFunc()
    {
        while (true)
        {
            if (mSocket != null)
            {
                if (mSocket.Connected)
                {
                    if (mSocket.Available <= 0)
                        Thread.Sleep(1);
                    else
                        Read();
                }
                else
                {
                    Clean();
                    break;
                }
            }
            else
            {
                break;
            }
            Thread.Sleep(1);
        }
    }
    void OnEmptyHeader()
    {
        Debug.Log("Length is 0?");
        Clean();
    }
    void Read()
    {
        if (mSocket.Available < 0)
            return;
        try
        {
            byte[] header = new byte[HeaderLength];
            int ret = mSocket.Receive(header, header.Length, 0);
            if (ret == 0)
            {
                OnEmptyHeader();
                return;
            }
            uint len = BitConverter.ToUInt32(header, 0);
            if (len > HeaderLength)
            {
                uint dataLength = len - HeaderLength;
                if (dataLength > 0)
                {
                    byte[] data = new byte[dataLength];
                    mSocket.Receive(data, (int)dataLength, 0);
                    lock (mLocker)
                    {
                        mDataQueue.Enqueue(data);
                    }
                }
            }
        }
        catch (Exception ex)
        {
            Debug.Log(ex.Message);
        }
    }


    public void Send(byte[] bytes)
    {
        if (!connected)
            return;

        byte[] head = new byte[4];
        head = BitConverter.GetBytes(bytes.Length + 4);

        byte[] topData = new byte[bytes.Length + 4];
        Array.Copy(head, 0, topData, 0, 4);
        Array.Copy(bytes, 0, topData, 4, bytes.Length);
        Debug.Log(string.Format("Send=>Type:{0},Param:{1},Length:{2}", bytes[0], bytes[1], topData.Length));

        try
        {
            SocketAsyncEventArgs arg = new SocketAsyncEventArgs();
            arg.SetBuffer(topData, 0, topData.Length);
            if (!mSocket.SendAsync(arg))
            {
                ProcessError(arg.SocketError, false);
                arg.Dispose();
            }
            else
            {
                arg.Dispose();
            }
        }
        catch (SocketException exc)
        {
            ProcessError(exc.SocketErrorCode, false);
        }

    }

    public void UpdateMessageQueue()
    {
        if (mSocket == null)
            return;
        mCommands.Clear();
        lock (mLocker)
        {
            while (mDataQueue.Count > 0)
                mCommands.Add(mDataQueue.Dequeue());
        }
        if (mCommands.Count > 0)
        {
            for (int i = 0; i < mCommands.Count; i++)
            {
                byte[] data = mCommands[i];
                if (onMessage != null)
                    onMessage(data);
            }
        }
        mCommands.Clear();
    }

}


