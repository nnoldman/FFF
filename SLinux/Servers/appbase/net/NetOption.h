#ifndef NetOption_h__
#define NetOption_h__

#include "../json/JsonReader.h"
struct COREAPI NetOption {
    string ip;
    string name;
    u32 port;
    u32 threadCount;
    NetOption();
    void fromText(Value* serializer) {
        Serializer::JsonReader::read(serializer, "ip", this->ip);
        Serializer::JsonReader::read(serializer, "name", this->name);
        Serializer::JsonReader::read(serializer, "port", this->port);
        Serializer::JsonReader::read(serializer, "threadCount", this->threadCount);
    }
};
#endif // NetOption_h__
