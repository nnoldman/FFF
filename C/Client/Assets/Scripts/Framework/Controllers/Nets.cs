using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using UnityEngine;

public class Nets : GameController<Nets> {
    public override IEnumerator Initialize() {
        InitSocket();
        yield return null;
    }

    public override void ForceClose() {
        if(mSocketBase != null)
            mSocketBase.Closed(NetEventID.ActiveDisconnect);
        mSocketBase = null;
    }

    public override void OnMapReady() {
        //this.ResumeMessageLoop();
    }

    public override void Update() {
        if (mSocketBase != null)
            mSocketBase.UpdateMessageQueue();
    }

    SocketBase mSocketBase;

    public string ServerIp = "169.254.1.200";
    public int ServerPort = 15299;
    public float ConnectTimeout = 10.0f;
    public UInt64 _dwUserID;
    public uint _loginTempID;
    public ushort _port;
    public float HeartBeatTime = 20f + 20f;
    float mServerTimeMark = 0;
    private static Frame.Buffer sSerializeBuffer = new Frame.Buffer(2 << 15);

    private Connection mCurrentConnectArgs;

    public bool Interrupting {
        get {
            if (mSocketBase != null) return mSocketBase.Interrupted;
            return false;
        }
    }
    public SocketBase MainSocket {
        get {
            return mSocketBase;
        }
    }

    public void OnTimeSet() {
        //Debug.LogWarning(string.Format("OnTimeSet:{0}", Time.time));
        mServerTimeMark = Time.realtimeSinceStartup;
    }

    //public uint serverTime
    //{
    //    get
    //    {
    //        if (mSocketBase != null)
    //        {
    //            return (uint)(mSocketBase.lastServerTime + Time.realtimeSinceStartup - mServerTimeMark);
    //        }
    //        return 0;
    //    }
    //}


    void InitSocket() {
        if (mSocketBase == null) {
            if (Application.isPlaying) {
                mSocketBase = new SocketBase();
                mSocketBase.messageHandler += DispatchMessage;
                mSocketBase.errorHandler += OnNetEvent;
            }
        }
    }

    void OnNetEvent(int id) {
    }

    public void InterruptMessageLoop() {
        if (mSocketBase != null)
            mSocketBase.Interrupted = true;
    }
    public void ResumeMessageLoop() {
        if (mSocketBase != null)
            mSocketBase.Interrupted = false;
    }

    public void connect(Connection connection) {
        mCurrentConnectArgs = new Connection();
        if (mSocketBase != null) {
            mSocketBase.connect(connection);
        }
    }

    public void Disconnect() {
        if (mSocketBase != null)
            mSocketBase.Closed(NetEventID.ActiveDisconnect);
    }

    public static void SendBuffer(int msgid, byte[] data) {
        if (!isConnected)
            return;
        Frame.Packet packet = Frame.Packet.ToPacket(msgid, data);
        SendCommand(packet);
    }

    static void SendCommand<T>(T cmd) where T : Frame.Packet {
        sSerializeBuffer.SetPosition(0);
        sSerializeBuffer.SetLength(0);
        cmd.Serialize(sSerializeBuffer);
        Instance.mSocketBase.Send(sSerializeBuffer);
    }

    public static void SendCommand(int msgid) {
        if (!isConnected)
            return;

        if (!isConnected)
            return;
        Frame.Packet packet = Frame.Packet.ToPacket(msgid, null);
        SendCommand(packet);
    }


    public static void Send(Cmd.CLIENTID msgid) {
        if (!isConnected)
            return;
        SendCommand(Frame.Packet.ToPacket((int)msgid));
        //LogClass.Instance.LogSend(sendcmd);
    }
    public static bool isConnected {
        get {
            if (Instance == null)
                return false;
            if (Instance.mSocketBase == null)
                return false;
            if (!Instance.mSocketBase.connected)
                return false;
            return true;
        }
    }

    public static void send(Frame.Packet cmd) {
        if (!isConnected)
            return;
        sSerializeBuffer.SetPosition(0);
        cmd.Serialize(sSerializeBuffer);
        Instance.mSocketBase.Send(sSerializeBuffer);
    }

    public static void Send<T>(Cmd.CLIENTID msgid, T protodata) where T : ProtoBuf.IExtensible {
        if (!isConnected)
            return;
        MemoryStream stream = new MemoryStream();
        ProtoBuf.Serializer.Serialize<T>(stream, protodata);
        Frame.Packet packet = Frame.Packet.ToPacket((int)msgid, stream.ToArray());
        SendCommand(packet);
    }
    public static T Parse<T>(byte[] msg) where T : ICommand {
        MemoryStream stream = new MemoryStream(msg);
        T protoBuffer = ProtoBuf.Serializer.Deserialize<T>(stream);
        return protoBuffer;
    }
    public static object Parse(byte[] msg, Type tp) {
        MemoryStream stream = new MemoryStream(msg);
        object protoBuffer = ProtoBuf.Serializer.NonGeneric.Deserialize(tp, stream);
        return protoBuffer;
    }

    public static T parseCommand<T>(byte[] msg) where T : Frame.Packet {
        Type tp = typeof(T);
        T cmd = (T)tp.GetConstructor(Type.EmptyTypes).Invoke(null);
        cmd.Deserialize(new Frame.Buffer(msg));
        return cmd;
    }

    public void onCommand(ref byte[] msg, uint msgId) {
    }

    public void DispatchMessage(byte[] data) {
        var protobuffer = Frame.Packet.From(data);
        protobuffer.Deserialize(new Frame.Buffer(data));
        Commands.Instance.Trigger((Cmd.SERVERID)protobuffer.id, new MemoryStream(protobuffer.data));
    }

    public override IEnumerator onGameStageClose() {
        throw new NotImplementedException();
    }
}
