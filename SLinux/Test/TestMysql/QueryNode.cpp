#include "stdafx.h"
#include "QueryNode.h"

QueryNode::QueryNode(MYSQL* sql)
    : mysql_(nullptr)
{
}

QueryNode::~QueryNode()
{
    if (resource_)
        mysql_free_result(resource_);
    resource_ = nullptr;
}

bool QueryNode::query(vector<string>& ret)
{
    auto row = this->nextRow();
    if (row)
    {
        auto columns = mysql_num_fields(resource_);
        for (auto i = 0U; i < columns; ++i)
        {
            ret.push_back(row[i]);
        }
    }
    return true;
}

bool QueryNode::query(vector<vector<string>>& ret)
{
    if (resource_)
    {
        auto columns = getColumns();
        auto row = nextRow();
        while (row)
        {
            vector<string> record;
            for (auto j = 0U; j < columns; ++j)
                record.push_back(row[j]);
            ret.push_back(record);
            row = nextRow();
        }
        return ret.size() > 0;
    }
    return ret.size() > 0;
}

bool QueryNode::query() const
{
    return true;
}

bool QueryNode::query(const char* cmd, DBDefine* ret)
{
    if (!this->start(cmd))
        return false;
}

bool QueryNode::query(const char* cmd, vector<DBDefine*>* ret)
{
    if (!this->start(cmd))
        return false;
}

bool QueryNode::query(const char* cmd)
{
    return this->start(cmd);
}

bool QueryNode::start(const char* cmd)
{
    auto state = mysql_real_query(this->mysql_);
    if (state == 0)
        return true;
    std::cout << "Error:" << mysql_error(this->mysql_) << std::endl;
    return false;
}

MYSQL_ROW QueryNode::nextRow()
{
    return mysql_fetch_row(this->resource_);
}

QueryNode::operator bool()
{
    return this->resource_ != nullptr;
}

::size_t QueryNode::count()
{
    stringstream cmd;
    cmd << "select count(*) from " << tablaname << ";";
    if (!queryBegin(cmd.str().c_str()))
    {
        return 0;
    }
    MYSQL_RES* ress = mysql_store_result(mysql_);
    if (ress == nullptr)
        return 0;
    MYSQL_ROW row = mysql_fetch_row(ress);
    mysql_free_result(ress);
    ress = nullptr;
    return ::atoi(row[0]);
}

::size_t QueryNode::getColumns()
{
    return mysql_num_fields(resource_);
}

