#pragma once
#include "Poco\Net\StreamSocket.h"
#include "ProtocoBuffer.h"
#include "google\protobuf\message_lite.h"

static const u32 kSizeLength = sizeof(u32);
static const u32 kOpCodeLength = sizeof(u32);
static const u32 kHeaderLength = kSizeLength + kOpCodeLength;

class Connection;

class COREAPI BundleReceiver {
  public:

    BundleReceiver(Connection* ss, char* data, u16 len);

    ~BundleReceiver();

    bool valid() const;

    ProtocoBuffer* get() const;

  private:

    Poco::Net::StreamSocket* mSocket;

    char* mBuffer;

    u32 mLength;
};

class COREAPI BundleSender {
  private:
    BundleSender();
  public:
    static BundleSender& GetInstance() {
        static BundleSender sender;
        return sender;
    }
    void setConnection(Poco::Net::StreamSocket& ss);
    void send(ProtocoBuffer* pkg, int len);
    void sendFlatbuffer(u32 opcode, u32 length, char* data);
    void sendProtoBuffer(u32 opcode, google::protobuf::MessageLite* message);
  private:
    Poco::Net::StreamSocket* mSocket;
    Basic::Buffer mBuffer;
    u32 mLength;
};
#define SendPKG(streamSocket,pkg) {BundleSender sender(streamSocket);sender.send(&pkg,sizeof(pkg));}
#define SendFlatbuffer(streamSocket,opcode,length,data) {BundleSender sender(streamSocket);sender.sendFlatbuffer(opcode,length,(char*)data);}
#define SendProtoBuffer(connection,opcode,data) \
{\
	BundleSender::GetInstance().setConnection(connection);\
	BundleSender::GetInstance().sendProtoBuffer(opcode, &data);\
}

