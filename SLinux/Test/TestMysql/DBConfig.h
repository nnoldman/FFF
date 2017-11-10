struct DBConfig
{
    string dbName;
    string user;
    string password;
    string host;
    int port;
    bool autoCreateAccount;
    DBConfig()
        : host("localhost")
        , port(3306)
        , autoCreateAccount(true)
    {
    }
};


