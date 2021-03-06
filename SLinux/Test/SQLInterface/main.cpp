// SQLInterface.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Test_Json.h"
#include "Voice.h"
#include "OptionService.h"
struct  NetOption {
    string ip;
    string name;
    int port;
    int threadCount;
    void fromText(Value* serializer) {
        Serializer::JsonReader::read(serializer, "ip", this->ip);
        Serializer::JsonReader::read(serializer, "name", this->name);
        Serializer::JsonReader::read(serializer, "port", this->port);
        Serializer::JsonReader::read(serializer, "threadCount", this->threadCount);
    }
};
struct DBOption {
    string dbName;
    string user;
    string password;
    string host;
    int port;
    bool autoCreateAccount;
    void fromText(Value* serializer) {
        Serializer::JsonReader::read(serializer, "dbName", this->dbName);
        Serializer::JsonReader::read(serializer, "user", this->user);
        Serializer::JsonReader::read(serializer, "password", this->password);
        Serializer::JsonReader::read(serializer, "host", this->host);
        Serializer::JsonReader::read(serializer, "port", this->port);
        Serializer::JsonReader::read(serializer, "autoCreateAccount", this->autoCreateAccount);
    }
};
int main() {
    //Voice voice;
    Test_Json test_json;

    DBOption option;
    NetOption netOption;
    OptionService service;
    service.start();
    service.getOption("0", "db", option);
    service.getOption("0", "net", netOption);
    return 0;
}

