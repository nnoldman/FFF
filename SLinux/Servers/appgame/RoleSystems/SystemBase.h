#ifndef SystemBase_h__
#define SystemBase_h__
#include "TableDefine/GameRoleDefine.h"
#include "../Role.h"
#include "Cmd.pb.h"
#include "Command.pb.h"
#include "Timer.h"


class SystemBase
{
public:
    SystemBase();
    virtual ~SystemBase();
public:
    virtual void initialize(Role* role);
    virtual void onNet(Cmd::CLIENTID id, ProtocoBuffer* pb);
    virtual void archieve();
    void send(Cmd::SERVERID id, google::protobuf::MessageLite* message);
protected:
    virtual void onTimer(Basic::Timer* timer);
    virtual void onTimerEnd(Basic::Timer* timer);
protected:
    Role* role_;
};

#endif // SystemBase_h__
