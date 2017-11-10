#ifndef MailSystem_h__
#define MailSystem_h__
#include "SystemBase.h"
#include "TableDefine/MailDefine.h"

class MailSystem: public SystemBase
{
public:
    MailSystem();
    ~MailSystem();

    virtual void initialize(Role* role) override;
    virtual void onNet(Cmd::CLIENTID id, ProtocoBuffer* pb) override;
    virtual void archieve() override;
protected:
    virtual void onTimer(Basic::Timer* timer) override;
    virtual void onTimerEnd(Basic::Timer* timer) override;
    void pullFromDB();
private:
    std::list<MailDefine*> mails_;
};

#endif // MailSystem_h__
