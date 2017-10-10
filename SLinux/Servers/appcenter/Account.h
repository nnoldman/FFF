#pragma once
#include "Connection.h"
#include "DBDefine.h"
#include "DBObject.h"
#include "GlobalAccountDefine.h"
class Account : public DBObject
{
public:
    Account();
    ~Account();

    virtual bool initialize() override;

    void onEnterGate();

    void onRoleRqEnterWorld(int globalID);

    void enterWorld();

    virtual void createDefine() override;

    inline	GlobalAccountDefine* getDefine() const;
};
inline GlobalAccountDefine * Account::getDefine() const
{
    return (GlobalAccountDefine*)this->dbInterface_;
}