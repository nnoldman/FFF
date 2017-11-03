#include "RewardSystem.h"



RewardSystem::RewardSystem()
{
}


RewardSystem::~RewardSystem()
{
}

void RewardSystem::initialize(Role* role)
{
    SystemBase::initialize(role);
}

void RewardSystem::onNet(Cmd::CLIENTID id, ProtocoBuffer* pb)
{
}
