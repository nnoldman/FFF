#pragma once
#include "DBExecuter.h"
class DBTable {
  public:
    string dbName;
    string name;
  private:
    int mRecordCount;
    DBExecuter* mExecuter;
  public:
    DBTable();
    ~DBTable();

    bool insert(const char* cmd);

    bool exist(const char* col);

    bool insertCol(const char* col);

    int refreshRecordCount();

  private:

    std::vector<string> mcolumns;
};

