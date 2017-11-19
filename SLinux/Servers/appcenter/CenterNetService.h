#ifndef CenterNetService_h__
#define CenterNetService_h__


class Account;
class CenterNetService:public IService<CenterNetService> {
  public:

    CenterNetService();
    ~CenterNetService();
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

    // Í¨¹ý IController ¼Ì³Ð
    virtual bool start() override;
    virtual const char * name() override;
};

#endif // CenterNetService_h__
