#include "stdafx.h"
#include "DBTable.h"
#include "App.h"

DBTable::DBTable()
    : executer_(&App::DataBase.executer())
{
}


DBTable::~DBTable()
{
}

bool DBTable::exist(const char* col)
{
    return std::find(columns_.begin(), columns_.end(), col) != columns_.end();
}
int DBTable::refreshRecordCount()
{
    stringstream sm;
    sm << "SELECT COUNT(*) FROM " << name << ";";
    executer_->queryBegin(sm.str().c_str());
    return 0;
}

void DBTable::fetchColumns()
{
    //select COLUMN_NAME from information_schema.COLUMNS where table_name = 'game_role1' and table_schema = 'ff';
    stringstream sm;
    sm << "select COLUMN_NAME from information_schema.COLUMNS where table_name = '" <<
       name << "' and table_schema = '" << dbName << "';";
    executer_->queryBegin(sm.str().c_str());
    vector<vector<string>> ret_records;
    if (executer_->queryEnd(ret_records))
    {
        std::for_each(ret_records.begin(), ret_records.end(), [this](const vector<string>& it)
        {
            this->columns_.push_back(it[0]);
        });
    }
}

const std::vector<string>& DBTable::columns() const
{
    return columns_;
}
