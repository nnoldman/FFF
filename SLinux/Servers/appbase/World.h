#ifndef World_h__
#define World_h__
class DBObject;
class Connection;
#include "Poco/Net/StreamSocket.h"

class COREAPI World
{
public:
    World();
    virtual ~World();

    Delegate1<void, DBObject*> onAccountEnterWorld;
    Delegate1<void, DBObject*> onAccountLeaveWorld;

    bool initialize();

    DBObject* get(int accountID);

    DBObject* get(Connection* connection);

public:
    void reclaimAccount(Connection* connection);
    void onEnterWorld(Connection* connection, DBObject* account);

    virtual void onDisconnect(Connection* connection);

	void onNetException(Poco::Net::StreamSocket& ss);
private:
    map<string, DBObject*> accounts_;
};

#endif // World_h__
