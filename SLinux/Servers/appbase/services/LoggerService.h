#ifndef LoggerService_h__
#define LoggerService_h__

#include "IService.h"

class LoggerService:public IService<LoggerService> {
  public:
    LoggerService();
    ~LoggerService();

    virtual bool start() override;
    virtual const char * name() override;

};

#endif // LoggerService_h__
