#ifndef PaySystem_h__
#define PaySystem_h__
#include "SystemBase.h"

class PaySystem: SystemBase
{
public:
    PaySystem();
    ~PaySystem();

    virtual void initialize(Role* role) override;

};

#endif // PaySystem_h__
