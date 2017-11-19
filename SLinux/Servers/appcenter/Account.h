#pragma once
#include "GameEntity.h"
#include "GlobalAccountDefine.h"
class Account : public GameEntity {
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
inline GlobalAccountDefine * Account::getDefine() const {
    return (GlobalAccountDefine*)this->dbInterface_;
}