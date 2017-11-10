#ifndef SQLExecuter_h__
#define SQLExecuter_h__
#include "EnvironmentConfig.h"

class DBExecuter
{
public:

    virtual bool initialize(const DBConfig& config) = 0;

    virtual bool queryBegin(const char* cmd) const = 0;

    virtual bool queryEnd(vector<string>& result) = 0;

    virtual bool queryEnd(vector<vector<string>>& result) = 0;

    virtual bool queryEnd() = 0;

    virtual unsigned long count() = 0;

    virtual void use(const char* dataBaseName) const = 0;
};
#endif // SQLExecuter_h__
