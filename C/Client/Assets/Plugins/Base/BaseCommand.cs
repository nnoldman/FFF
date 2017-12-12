using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System;
using System.IO;
namespace Frame {
    public class Packet {
        public static readonly int HeaderLength = 12;

        public int size;
        public int id;//ÏûÏ¢±àºÅ
        public byte[] data;

        Packet() {
            size = 0;
            id = 0;
        }
        public static Packet From(byte[] data) {
            return null;
        }
        public static Packet ToPacket(int id) {
            return ToPacket(id, null);
        }
        public static Packet ToPacket(int id, byte[] data) {
            Packet ret = new Packet();
            ret.id = id;
            ret.size = HeaderLength;
            if (data != null) {
                ret.size += data.Length;
                ret.data = new byte[data.Length];
                Array.Copy(ret.data, data, data.Length);
            }
            return ret;
        }
        private void WriteHeader(Frame.Buffer buffer) {
            buffer.Write(id);
            buffer.Write(size);
        }

        protected Frame.Packet Write(Frame.Buffer buffer) {
            buffer.Write(data);
            return this;
        }
        public void Serialize(Frame.Buffer buffer) {
            WriteHeader(buffer);
            Write(buffer);
        }

        public virtual void Deserialize(Frame.Buffer buffer) {
            buffer.Read(ref size);
            buffer.Read(ref id);
            buffer.Read(ref data, (int)size - 8);
        }
    }
}
