#ifndef TaskSystem_h__
#define TaskSystem_h__
#include "SystemBase.h"
class TaskSystem : public SystemBase
{
public:
    TaskSystem();
    ~TaskSystem();

    virtual void initialize(Role* role) override;
};
#endif // TaskSystem_h__

