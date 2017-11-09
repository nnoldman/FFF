#ifndef ChatSystem_h__
#define ChatSystem_h__

#include "SystemBase.h"
class ChatSystem :
    public SystemBase
{
public:
    ChatSystem();
    ~ChatSystem();

    virtual void initialize(Role* role) override;
    virtual void onNet(Cmd::CLIENTID id, ProtocoBuffer* pb) override;
protected:
    void onWorldMessage(Cmd::ReqChat* message);
    virtual void onTimer(Basic::Timer* timer) override;
    virtual void onTimerEnd(Basic::Timer* timer) override;

};

#endif // ChatSystem_h__
