#pragma once
#include "GameEntity.h"
#include "TableDefine/GameUserDefine.h"
#include "Role.h"
class GameUser: public GameEntity {
  public:
    GameUser();
    ~GameUser();
    virtual void createDefine() override;
    virtual bool initialize() override;

    inline GameUserDefine* getDefine() const;

    void onEnterGate();

    Role* getRole();

    void activeRole();

  private:
    Role role_;
};


inline GameUserDefine* GameUser::getDefine() const {
    return (GameUserDefine*)this->dbInterface_;
}


