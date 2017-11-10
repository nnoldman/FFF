#include "stdafx.h"
#include "MySqlExecuter.h"



MySQLExecuter::MySQLExecuter()
{
}


MySQLExecuter::~MySQLExecuter()
{
}

bool MySQLExecuter::initialize(const DBConfig& config)
{
    mConfig = config;
    mysql_ = mysql_init(0);
    assert(mysql_ != 0);
    MYSQL* tmp = mysql_real_connect(mysql_, mConfig.host.c_str(), mConfig.user.c_str(), mConfig.password.c_str(),
                                    mConfig.dbName.c_str(), mConfig.port, 0, 0);
    assert(tmp == mysql_);
    MYSQL_STMT* hstmt = mysql_stmt_init(mysql_);
    assert(hstmt != 0);
    return true;
}


bool MySQLExecuter::queryBegin(const char* cmd) const
{
    assert(cmd);
    int status = mysql_real_query(mysql_, cmd, static_cast<unsigned long>(strlen(cmd)));
    if (status != 0)
        printf("QUERY X=>%s\n", mysql_error(mysql_));
    else
        printf("QUERY V=>%s\n", cmd);
    return status == 0;
}

bool MySQLExecuter::queryEnd()
{
    return  mysql_affected_rows(mysql_) > 0;
}


bool MySQLExecuter::queryEnd(vector<string>& record)
{
    if (mysql_affected_rows(mysql_) == 0)
        return false;
    MYSQL_RES* records = nullptr;
    records = mysql_store_result(mysql_);
    if (records)
    {
        auto columns = mysql_num_fields(records);
        assert(records->row_count <= 1);
        MYSQL_ROW row = mysql_fetch_row(records);
        if (row)
        {
            for (int i = 0; i < columns; ++i)
                record.push_back(row[i]);
        }
        mysql_free_result(records);
        records = nullptr;
        return record.size() > 0;
    }
    else
    {
        return false;
    }
    return record.size() > 0;
}




bool MySQLExecuter::queryEnd(vector<vector<string>>& ret_records)
{
    if (mysql_affected_rows(mysql_) == 0)
        return false;
    MYSQL_RES* records = nullptr;
    records = mysql_store_result(mysql_);
    if (records)
    {
        auto columns = mysql_num_fields(records);
        MYSQL_ROW row = mysql_fetch_row(records);
        while (row)
        {
            vector<string> record;
            for (auto j = 0; j < columns; ++j)
                record.push_back(row[j]);
            ret_records.push_back(record);
            row = mysql_fetch_row(records);
        }
        mysql_free_result(records);
        records = nullptr;
        return ret_records.size() > 0;
    }
    return ret_records.size() > 0;
}

unsigned long MySQLExecuter::count()
{
    MYSQL_RES* ress = mysql_store_result(mysql_);
    if (ress == nullptr)
        return 0;
    MYSQL_ROW row = mysql_fetch_row(ress);
    mysql_free_result(ress);
    ress = nullptr;
    return ::atoi(row[0]);
}

void MySQLExecuter::use(const char* dataBaseName) const
{
    stringstream cmd;
    cmd << "use database " << dataBaseName << ";";
    queryBegin(cmd.str().c_str());
}

