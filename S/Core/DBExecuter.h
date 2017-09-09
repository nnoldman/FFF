#ifndef SQLExecuter_h__
#define SQLExecuter_h__

#include "ConfigInfo.h"


class DBExecuter {
  public:

    virtual bool initialize(const DBConfig& config) = 0;

    virtual void queryBegin(const char* cmd) const = 0;

    virtual bool queryEnd(stringVector& result) = 0;

    virtual bool queryEnd(stringVectorVector& result) = 0;

    virtual bool queryEnd() = 0;

    virtual unsigned long count() = 0;

    virtual void use(const char* dataBaseName) const = 0;
};
#endif // SQLExecuter_h__
