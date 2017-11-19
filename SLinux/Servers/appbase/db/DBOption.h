#ifndef DBOption_h__
#define DBOption_h__
#include "../json/JsonReader.h"

struct DBOption {
    string dbName;
    string user;
    string password;
    string host;
    int port;
    bool autoCreateAccount;
    DBOption();
    void fromText(Value* serializer) {
        Serializer::JsonReader::read(serializer, "dbName", this->dbName);
        Serializer::JsonReader::read(serializer, "user", this->user);
        Serializer::JsonReader::read(serializer, "password", this->password);
        Serializer::JsonReader::read(serializer, "host", this->host);
        Serializer::JsonReader::read(serializer, "port", this->port);
        Serializer::JsonReader::read(serializer, "autoCreateAccount", this->autoCreateAccount);
    }
};
#endif // DBOption_h__
