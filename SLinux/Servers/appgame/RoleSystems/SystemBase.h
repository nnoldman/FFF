#ifndef SystemBase_h__
#define SystemBase_h__
#include "TableDefine/GameRoleDefine.h"
#include "Cmd.pb.h"
#include "Command.pb.h"
#include "../Role.h"



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
    Role* role_;
};

#endif // SystemBase_h__
