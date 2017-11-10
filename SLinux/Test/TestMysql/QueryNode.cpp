#include "stdafx.h"
#include "QueryNode.h"

QueryNode::QueryNode(MYSQL* sql)
    : mysql_(nullptr)
{
    mysql_store_result(mysql_);
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

MYSQL_ROW QueryNode::nextRow()
{
    return mysql_fetch_row(this->resource_);
}

::size_t QueryNode::getColumns()
{
    return mysql_num_fields(resource_);
}

