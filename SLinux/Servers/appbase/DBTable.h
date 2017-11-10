#pragma once
#include "DBExecuter.h"
class DBTable
{
public:
    string dbName;
    string name;
private:
    DBExecuter* executer_;
public:
    DBTable();
    ~DBTable();

    bool exist(const char* col);
    int refreshRecordCount();
    void fetchColumns();
    const std::vector<string>& columns()const;
private:

    std::vector<string> columns_;
};

