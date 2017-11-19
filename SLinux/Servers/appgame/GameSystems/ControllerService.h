#ifndef ControllerService_h__
#define ControllerService_h__

#include "GameControllerBase.h"
class ControllerService:public IService<ControllerService> {
  public:
    ControllerService();
    ~ControllerService();
    virtual const char * name() override;
  public:
    virtual bool start() override;
    virtual void tick() override;
    template<typename T>
    void add();
  private:
    vector<GameControllerBase*> controllers_;
};

template<typename T>
void ControllerService::add() {
    T::instance_ = new T();
    this->controllers_.push_back(T::instance_);
}

#endif // ControllerService_h__
