#ifndef TimeService_h__
#define TimeService_h__

#include "IService.h"
class TimeService :IService<TimeService> {
  public:
    TimeService();
    ~TimeService();
    virtual void tick() override;

    // Í¨¹ý IController ¼Ì³Ð
    virtual bool start() override;
    virtual const char * name() override;
};

#endif // TimeService_h__
