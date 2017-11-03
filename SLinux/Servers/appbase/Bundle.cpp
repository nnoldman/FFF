#include "stdafx.h"
#include "Bundle.h"
#include "Connection.h"

BundleReceiver::BundleReceiver(Connection* ss, char* data, u16 len)
    : mSocket(&ss->getSocket())
    , mBuffer(data)
    , mLength(len)
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

void BundleSender::setConnection(Connection* con)
{
    connection_ = con;
}

void BundleSender::send(ProtocoBuffer* pkg, int len)
{
}

void BundleSender::sendFlatbuffer(u32 opcode, u32 length, char* data)
{
}

void BundleSender::sendProtoBuffer(u32 opcode, google::protobuf::MessageLite* message)
{

}

void BundleSender::sendProtoBuffer(u32 opcode, google::protobuf::MessageLite * message, Connection * ss)
{
    connection_ = ss;
    locker.lock();
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
    catch (google::protobuf::exception exc)
    {
        printf(exc.what());
    }
    mBuffer.forwardPosition(len);
    try
    {
        if (connection_ && connection_->valid())
        {
            int ret = connection_->getSocket().sendBytes(mBuffer.getBuffer(), mBuffer.getPosition());
        }
    }
    catch (std::exception exc)
    {
        if (connection_ && connection_->valid())
            this->onException.invoke(connection_);
        //LOG_TRACE_A(exc.what());
    }
    locker.unlock();
}

