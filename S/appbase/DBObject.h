#ifndef BaseObject_h__
#define BaseObject_h__
#include "Connection.h"
#include "DBDefine.h"

class COREAPI DBObject
{
public:
    DBObject();
    virtual ~DBObject();
    virtual bool initialize();
    virtual void setGlobalID(int globalID) final;
    virtual void createDefine() = 0;
    inline DBDefine* getDBInterface() const;
    inline void setConnection(Connection* connect);
    virtual void syncToClient();
    inline int globalID()const;
    inline Connection* getNetInterface();
    //bool pull(Value keyValue);
    //bool commit(Value keyValue);
protected:
    DBDefine* dbInterface_;
    Connection* netInterface_;
private:
    int globalID_;
};
inline int DBObject::globalID() const
{
    return globalID_;
}
inline DBDefine* DBObject::getDBInterface() const
{
    return dbInterface_;
}
inline void DBObject::setConnection(Connection* connect)
{
    netInterface_ = connect;
}

inline Connection* DBObject::getNetInterface()
{
    return netInterface_;
}

#endif // BaseObject_h__

