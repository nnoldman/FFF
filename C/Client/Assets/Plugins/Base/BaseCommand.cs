using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System;
using System.IO;

public class ProtocoBuffer {
    private static byte[] s4ByteBuffer = new byte[4];
    private byte[] sPara = new byte[4];

    public uint id;//ÏûÏ¢±àºÅ
    public uint size;
    public byte[] data;

    public ProtocoBuffer() {
        id = 0;
        size = 0;
    }

    void writeHeader(MemoryStream stream) {
        s4ByteBuffer = BitConverter.GetBytes(size);
        stream.Write(s4ByteBuffer, 0, s4ByteBuffer.Length);
    }
    protected virtual ProtocoBuffer write(MemoryStream stream) {
        s4ByteBuffer = BitConverter.GetBytes(id);
        stream.Write(s4ByteBuffer, 0, s4ByteBuffer.Length);
        if (data != null)
            stream.Write(data, 0, (int)size);
        return this;
    }
    public virtual void serialize(MemoryStream stream) {
        writeHeader(stream);
        write(stream);
    }

    public virtual void deserialize(MemoryStream stream) {
        stream.Read(s4ByteBuffer, 0, 4);
        size = BitConverter.ToUInt32(s4ByteBuffer, 0);
        stream.Read(s4ByteBuffer, 0, 4);
        id = BitConverter.ToUInt32(s4ByteBuffer, 0);
        try {
            data = new byte[size];
            stream.Read(data, 0, (int)size);
        } catch (Exception ex) {
            Debug.LogError(ex.Message);
        }
    }
}
