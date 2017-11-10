#ifndef GameNetAgent_h__
#define GameNetAgent_h__

class Account;
class GameNetAgent
{
public:
    GameNetAgent();
    ~GameNetAgent();

    bool initialize();
protected:
    void onDisconnect(Connection* connection);
    void onMessage(ProtocoBuffer* pb, Connection* connection);
protected:

    bool on_rqCreateAccount(const string& user, const string& password, Connection* con);
    bool on_rqLoginAccount(string user, string psw, Connection* con);
    void onLoginSucess(Account* account);
};

#endif // GameNetAgent_h__
