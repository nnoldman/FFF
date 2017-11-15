#include "stdafx.h"
#include "QueryNode.h"

QueryNode::QueryNode(MYSQL* sql) : mysql_(sql) {

}

QueryNode::~QueryNode() {
    if (resource_)
        mysql_free_result(resource_);
    resource_ = nullptr;
}

bool QueryNode::fetch(vector<string>& ret) {
    if (!store())
        return false;
    auto row = this->nextRow();
    if (row) {
        auto columns = mysql_num_fields(resource_);
        for (auto i = 0U; i < columns; ++i) {
            ret.push_back(row[i]);
        }
    }
    return true;
}

bool QueryNode::fetch(vector<vector<string>>& ret) {
    if (!store())
        return false;
    auto columns = getColumns();
    auto row = nextRow();
    while (row) {
        vector<string> record;
        for (auto j = 0U; j < columns; ++j)
            record.push_back(row[j]);
        ret.push_back(record);
        row = nextRow();
    }
    return ret.size() > 0;
}

bool QueryNode::fetch() const {
    return true;
}

bool QueryNode::query(const char* cmd) {
    if (!this->start(cmd))
        return false;
    return true;
}

bool QueryNode::start(const char* cmd) {
    auto state = mysql_real_query(this->mysql_,cmd,strlen(cmd));
    std::cout << "Query:" << cmd << std::endl;
    if (state == 0)
        return true;
    std::cout << "QueryError:" << mysql_error(this->mysql_) << std::endl;
    return false;
}

MYSQL_ROW QueryNode::nextRow() {
    return mysql_fetch_row(this->resource_);
}

QueryNode::operator bool() {
    return this->resource_ != nullptr;
}

::size_t QueryNode::getColumns() {
    return mysql_num_fields(resource_);
}

bool QueryNode::store() {
    if (mysql_)
        this->resource_ = mysql_store_result(mysql_);
    return this->resource_ != nullptr;
}

