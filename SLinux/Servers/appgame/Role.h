#pragma once
#include "DBObject.h"
#include "GameRoleDefine.h"

class Role:public DBObject
{
public:
    Role();
    ~Role();

    virtual bool initialize() override;
    virtual void createDefine()override;

    GameRoleDefine* getDefine() const;

    bool valid() const;

    virtual void syncToClient() override;

};

inline bool Role::valid() const
{
    return getDefine()->id > 0;
}

