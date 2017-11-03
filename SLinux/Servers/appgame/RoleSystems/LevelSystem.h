#pragma once
#include "SystemBase.h"
class LevelSystem :
    public SystemBase
{
public:
    LevelSystem();
    virtual ~LevelSystem();
    virtual void initialize(Role* role) override;
protected:
    void onTimer(Basic::Timer* timer);
    void onTimeLineEnd(Basic::Timer* timer);
    void syncTimeLine();
    void calcTimeLine();
private:
    Role* role_;
    Basic::Timer* timeLineTimer_;
    int currentTrun_;
    int currentTrunLeftTime_;
    int currentTrunTotalTime_;
};

