#ifndef DBTable_h__
#define DBTable_h__

#include "DBExecuter.h"
class DBTable {
  public:
    string dbName;
    string name;
  private:
    DBExecuter* executer_;
  public:
    DBTable(DBExecuter* executer);
    ~DBTable();
    bool exist(const char* col);
    void fetchColumns();
    const std::vector<string>& columns()const;
  private:

    std::vector<string> columns_;
};

#endif // DBTable_h__
