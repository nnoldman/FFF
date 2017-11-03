#pragma once
#include "DBObject.h"
#include "TableDefine/GameRoleDefine.h"
#include "Cmd.pb.h"
#include "Command.pb.h"
#include "ServerDefine.h"

class LevelSystem;
class ItemSystem;
class TaskSystem;
class SystemBase;
class Role: public DBObject
{

public:
    Role();
    ~Role();

    virtual bool initialize() override;
    virtual void createDefine()override;

    GameRoleDefine* getDefine() const;

    bool valid() const;

    virtual void syncToClient() override;
    void onNet(Cmd::CLIENTID id, ProtocoBuffer* pb);
public:
    SystemBase* systems_[ServerDefine::SystemType_Count];
};

inline bool Role::valid() const
{
    return getDefine()->id > 0;
}

