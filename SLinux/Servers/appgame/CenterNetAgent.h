#pragma once
class Account;
class CenterNetAgent
{
public:
    CenterNetAgent();
    ~CenterNetAgent();

    bool initialize();
protected:
    void onDisconnect(Connection* connection);
    void onMessage(ProtocoBuffer* pb, Connection* connection);
protected:

    bool on_rqCreateAccount(const string& user, const string& password, Connection* con);
    bool on_rqLoginAccount(string user, string psw, Connection* con);
    void onLoginSucess(Account* account);
};

