#ifndef ConfigInfo_h__
#define ConfigInfo_h__
struct COREAPI NetConfig {
    string ip;
    string name;
    u32 port;
    u32 threadCount;
    NetConfig();
};

struct COREAPI DBConfig {
    string dbName;
    string user;
    string password;
    string host;
    int port;
    bool autoCreateAccount;
    DBConfig()
        : host("localhost")
        , port(3306)
        , autoCreateAccount(true) {

    }
};

struct COREAPI ScriptConfig {
    bool open;
};

struct COREAPI AppConfiguratin {
    NetConfig net;
    DBConfig db;
    ScriptConfig script;
};

struct COREAPI CenterConfig {
    DBConfig db;
    ScriptConfig script;
    Map<int, NetConfig*> centers;
    ~CenterConfig() {
        centers.destroySecond();
    }
};

#endif // ConfigInfo_h__