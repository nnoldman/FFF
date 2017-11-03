#ifndef GameControllers_h__
#define GameControllers_h__
#include "GameSystems/GameControllerBase.h"
class GameControllers
{
public:
    GameControllers();
    ~GameControllers();
public:
    void start();
    void update();
    template<typename T>
    void add();
private:
    vector<GameControllerBase*> controllers_;
};

template<typename T>
void GameControllers::add()
{
    T::instance_ = new T();
    this->controllers_.push_back(T::instance_);
}

#endif // GameControllers_h__
