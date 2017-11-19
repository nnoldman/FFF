#ifndef TimeService_h__
#define TimeService_h__

#include "IService.h"
class TimeService :IService<TimeService> {
  public:
    TimeService();
    ~TimeService();
    virtual void tick() override;

    // ͨ�� IController �̳�
    virtual bool start() override;
    virtual const char * name() override;
};

#endif // TimeService_h__
