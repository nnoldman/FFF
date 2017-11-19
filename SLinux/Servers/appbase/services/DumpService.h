#ifndef DumpService_h__
#define DumpService_h__


#include "IService.h"
class DumpService :IService<DumpService> {
  public:
    DumpService();
    ~DumpService();

    virtual bool start() override;


    virtual const char* name() override;

};

#endif // DumpService_h__
