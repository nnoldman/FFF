#include "stdafx.h"
#include "GameControllers.h"
#include "MessageController.h"



GameControllers::GameControllers()
{
}

GameControllers::~GameControllers()
{
    dSafeDeleteVector(this->controllers_);
}

void GameControllers::start()
{
    add<MessageController>();
}

void GameControllers::update()
{
    for (auto it : this->controllers_)
    {
        it->update();
    }
}
