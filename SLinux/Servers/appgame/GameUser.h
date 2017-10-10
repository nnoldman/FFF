#pragma once
#include "DBObject.h"
#include "GameUserDefine.h"
#include "Role.h"
class GameUser:public DBObject
{
    //DeclareObjectPool(GameUser);
public:
    GameUser();
    ~GameUser();

    // Í¨¹ý BaseObject ¼Ì³Ð
    virtual void createDefine() override;

    virtual bool initialize() override;

    inline GameUserDefine* getDefine() const;

    void onEnterGate();

    Role* getRole();

    void activeRole();

private:
    Role role_;
};


inline GameUserDefine* GameUser::getDefine() const
{
    return (GameUserDefine*)this->dbInterface_;
}


