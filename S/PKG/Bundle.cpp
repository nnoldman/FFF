#include "stdafx.h"
#include "Bundle.h"
#include "Core\Connection.h"

BundleReceiver::BundleReceiver(Connection* ss, char* data, u16 len)
    : mSocket(&ss->getSocket())
    , mLength(len)
    , mBuffer(data)
{

}

BundleReceiver::~BundleReceiver()
{
}

bool BundleReceiver::valid() const
{
    u16 dataLength = *((u16*)mBuffer);
    return dataLength + kHeaderLength == mLength;
}

ProtocoBuffer* BundleReceiver::get() const
{
    return (ProtocoBuffer*)(mBuffer);
}

BundleSender::BundleSender()
    : mBuffer(Default::ReceiveBufferSize)
{
}

void BundleSender::setConnection(Poco::Net::StreamSocket& ss)
{
    mSocket = &ss;
}

void BundleSender::send(ProtocoBuffer* pkg, int len)
{
}

void BundleSender::sendFlatbuffer(u32 opcode, u32 length, char* data)
{
}

void BundleSender::sendProtoBuffer(u32 opcode, google::protobuf::MessageLite* message)
{
    mBuffer.clear();
    u32 len = message->ByteSize();
    u32 allsize = kHeaderLength + len;
    mBuffer.write(allsize);
    mBuffer.write(len);
    mBuffer.write(opcode);
    try
    {
        message->SerializeToArray((void*)(mBuffer.currentPointer()), len);
    }
    catch(google::protobuf::exception exc)
    {
        printf(exc.what());
    }
    mBuffer.forwardPosition(len);
    int ret = mSocket->sendBytes(mBuffer.getBuffer(), mBuffer.getPosition());
}

