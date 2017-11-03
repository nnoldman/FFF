#ifndef RewardSystem_h__
#define RewardSystem_h__
#include "RoleSystems/SystemBase.h"
/*
½±ÀøÏµÍ³
*/
class RewardSystem: SystemBase
{
public:
    RewardSystem();
    ~RewardSystem();

    virtual void initialize(Role* role) override;


    virtual void onNet(Cmd::CLIENTID id, ProtocoBuffer* pb) override;

};

#endif // RewardSystem_h__
