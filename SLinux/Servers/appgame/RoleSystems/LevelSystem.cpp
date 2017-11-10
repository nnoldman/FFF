#include "../stdafx.h"
#include "LevelSystem.h"
#include "Config/TimeTable.h"
#include "GameSystems/MessageController.h"

LevelSystem::LevelSystem()
    : role_(nullptr)
    , currentTrun_(0)
    , currentTrunLeftTime_(0)
    , currentTrunTotalTime_(0)
{
}


LevelSystem::~LevelSystem()
{
    if (!this->timeLineTimer_.expired())
        this->timeLineTimer_.lock()->cancel();
}

void LevelSystem::initialize(Role* role)
{
    this->role_ = role;
    SystemBase::initialize(role);
    calcTimeLine();
    syncTimeLine();
    MessageController::getInstance()->onUserEnterWorld(this->role_);
}

void LevelSystem::onTimer(Basic::Timer* timer)
{
}

void LevelSystem::onTimeLineEnd(Basic::Timer* timer)
{
    calcTimeLine();
    syncTimeLine();
}

void LevelSystem::syncTimeLine()
{
    Cmd::RetTimeLine ret;
    ret.set_trun(this->currentTrun_);
    ret.set_leftseconds(this->timeLineTimer_.lock()->leftSeconds());
    ret.set_totalseconds(this->currentTrunTotalTime_);
    send(Cmd::SERVERID::RTTimeLine, &ret);
}

void LevelSystem::calcTimeLine()
{
    auto roledefine = this->role_->getDefine();
    auto delta = Basic::Time_::nowMinusLocalTime(roledefine->base.borntime.c_str());
    auto allrecords = TimeTable::getInstance()->all();
    int64_t eclipseTime = 0;
    for (auto i = 0; i < allrecords.size() - 1; ++i)
    {
        auto record = allrecords[i];
        auto next = allrecords[i + 1];
        currentTrunTotalTime_ = (next->start - record->start) / record->realtime / 1000000;
        eclipseTime += currentTrunTotalTime_;
        if (eclipseTime > delta)
        {
            currentTrun_ = i;
            currentTrunLeftTime_ = eclipseTime - delta;
            if (this->timeLineTimer_.lock())
                this->timeLineTimer_.lock()->cancel();
            this->timeLineTimer_ = Timers::getInstance()->repeat(
                                       5000, &LevelSystem::onTimer, this, currentTrunLeftTime_ * 1000, &::LevelSystem::onTimeLineEnd );
            break;
        }
    }
}
