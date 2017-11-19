#ifndef WorldService_h__
#define WorldService_h__

class GameEntity;
class Connection;
#include "Poco/Net/StreamSocket.h"
#include "IService.h"

class COREAPI WorldService:public IService<WorldService> {
  public:
    WorldService();
    virtual ~WorldService();

    Basic::Delegate1<void, GameEntity*> onAccountEnterWorld;
    Basic::Delegate1<void, GameEntity*> onAccountLeaveWorld;

    bool start();

    GameEntity* getAccount(int accountID);

    GameEntity* getAccount(Connection* connection);

    const map<Connection*, GameEntity*>& getAcccounts() const;
    void process();
  public:
    void reclaimAccount(Connection* connection);
    void onEnterWorld(Connection* connection, GameEntity* account);

    virtual void onDisconnect(Connection* connection);

    void onNetException(Connection* connection);
  private:
    map<Connection*, GameEntity*> accounts_;
    vector<Connection*> quitedAccounts_;
    bool dirty_;

    // Í¨¹ý IController ¼Ì³Ð
    virtual const char * name() override;
};

#endif // WorldService_h__
