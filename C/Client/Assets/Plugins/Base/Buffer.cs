using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Frame {
    public class Buffer {

        public Buffer() {
            stream_ = new MemoryStream();
        }

        public Buffer(int capacity) {
            stream_ = new MemoryStream(capacity);
        }

        public Buffer(byte[] value) {
            stream_ = new MemoryStream(value);
        }

        public long Length {
            get {
                return this.stream_.Length;
            }
        }

        public MemoryStream GetStream() {
            return this.stream_;
        }

        public byte[] GetBuffer() {
            return this.stream_.GetBuffer();
        }

        public void SetLength(long value) {
            stream_.SetLength(value);
        }

        public void SetPosition(long value) {
            this.stream_.Position = value;
        }

        public Buffer Write(int value) {
            var data = BitConverter.GetBytes(value);
            stream_.Write(data, 0, data.Length);
            return this;
        }
        public Buffer Write(byte[] value) {
            if(value != null)
                stream_.Write(value, 0, value.Length);
            return this;
        }
        public Buffer Write(char value) {
            var data = BitConverter.GetBytes(value);
            stream_.Write(data, 0, data.Length);
            return this;
        }

        public Buffer Write(byte value) {
            stream_.WriteByte(value);
            return this;
        }

        public Buffer Write(sbyte value) {
            var data = BitConverter.GetBytes(value);
            stream_.Write(data, 0, data.Length);
            return this;
        }

        public Buffer Write(uint value) {
            var data = BitConverter.GetBytes(value);
            stream_.Write(data, 0, data.Length);
            return this;
        }

        public Buffer Write(short value) {
            var data = BitConverter.GetBytes(value);
            stream_.Write(data, 0, data.Length);
            return this;
        }

        public Buffer Write(ushort value) {
            var data = BitConverter.GetBytes(value);
            stream_.Write(data, 0, data.Length);
            return this;
        }

        public Buffer Write(string value, Encoding encoding) {
            var data = encoding.GetBytes(value.ToCharArray());
            stream_.Write(data, 0, data.Length);
            return this;
        }

        public Buffer Read(ref int value) {
            stream_.Read(s4ByteBuffer, 0, 4);
            value = BitConverter.ToInt32(s4ByteBuffer, 0);
            return this;
        }
        public Buffer Read(ref uint value) {
            stream_.Read(s4ByteBuffer, 0, 4);
            value = BitConverter.ToUInt32(s4ByteBuffer, 0);
            return this;
        }

        public Buffer Read(ref byte[] value, int length) {
            value = new byte[length];
            stream_.Read(value, 0, length);
            return this;
        }

        private MemoryStream stream_;
        private static byte[] s4ByteBuffer = new byte[4];
    }
}

