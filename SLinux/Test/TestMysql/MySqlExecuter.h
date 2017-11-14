#ifndef MySqlExecuter_h__
#define MySqlExecuter_h__

#include "DBExecuter.h"

class MySQLExecuter: public DBExecuter {
  public:
    MySQLExecuter();
    ~MySQLExecuter();

    virtual bool initialize(const DBConfig& config) override;
    virtual unsigned long count(const char* tablaname) override;
    void use() const;
    virtual void close() override;

    virtual bool query(const char* cmd) override;
    virtual bool query(const char* cmd, OUT vector<string>& result) override;
    virtual bool query(const char* cmd, OUT vector<vector<string>>& result) override;
    virtual bool query(const char* cmd, OUT DBDefine* ret) override;
    virtual bool query(const char* cmd, OUT vector<DBDefine *>& ret, DBDefineCreator creator) override;
  private:
    MYSQL* mysql_;
};
#endif // MySqlExecuter_h__
