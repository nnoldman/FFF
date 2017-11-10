#ifndef CenterNetAgent_h__
#define CenterNetAgent_h__

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
    bool on_rqLoginAccount(const string& user, const string& password, Connection* con);
    bool on_rqCreateAccount(const string& user, const string& password, Connection* con);
    bool on_rqDeleteAccount(const string& user, const string& password, Connection* con);
    bool on_rqRenameAccount(const string& user, const string& password, Connection* con);

    void onLoginSucess(Account* account, Connection* con);
protected:
    bool createAccount(string user, string psd, Connection* con);
private:
    map<Connection*, int> mClients;
};

#endif // CenterNetAgent_h__
