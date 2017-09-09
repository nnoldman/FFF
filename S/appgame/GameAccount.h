#pragma once
#include "BaseObject.h"
class GameAccount: BaseObject {
  public:
    GameAccount();
    ~GameAccount();

    virtual bool initialize() override;

    virtual void createDefine() override;

};

