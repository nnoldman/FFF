#ifndef BaseObject_h__
#define BaseObject_h__
#include "net/Connection.h"
#include "db/DBDefine.h"
#include "IObject.h"
class COREAPI GameEntity :IObject {
  public:
    GameEntity();
    virtual ~GameEntity();
    virtual bool initialize();
    virtual void setGlobalID(int globalID) final;
    virtual void createDefine() = 0;
    inline DBDefine* getDBInterface() const;
    inline void setConnection(Connection* connect);
    virtual void syncToClient();
    inline int globalID()const;
    inline Connection* getNetInterface();
  protected:
    DBDefine* dbInterface_;
    Connection* netInterface_;
  private:
    int globalID_;
};
inline int GameEntity::globalID() const {
    return globalID_;
}
inline DBDefine* GameEntity::getDBInterface() const {
    return dbInterface_;
}
inline void GameEntity::setConnection(Connection* connect) {
    netInterface_ = connect;
}

inline Connection* GameEntity::getNetInterface() {
    return netInterface_;
}

#endif // BaseObject_h__

