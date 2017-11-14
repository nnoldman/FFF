#include "stdafx.h"
#include "MySqlExecuter.h"
#include "QueryNode.h"



MySQLExecuter::MySQLExecuter()
    :mysql_(nullptr) {
}


MySQLExecuter::~MySQLExecuter() {
}

bool MySQLExecuter::initialize(const DBConfig& config) {
    DBExecuter::initialize(config);

    mysql_ = mysql_init(0);
    assert(mysql_ != 0);
    MYSQL* tmp = mysql_real_connect(mysql_, config_.host.c_str(), config_.user.c_str(), config_.password.c_str(),
                                    config_.dbName.c_str(), config_.port, 0, 0);
    if (tmp == nullptr) {
        std::cout << "MySQLExecuter::initialize=>>" << mysql_error(mysql_) << std::endl;
        return false;
    }
    MYSQL_STMT* hstmt = mysql_stmt_init(mysql_);
    assert(hstmt != 0);
    return true;
}
unsigned long MySQLExecuter::count(const char* name) {
    QueryNode query(this->mysql_);
    throw new exception();
    return 0;
}

void MySQLExecuter::use() const {
    stringstream cmd;
    cmd << "use " << this->config_.dbName << ";";
    QueryNode query(this->mysql_);
    query.query(cmd.str().c_str());
}

void MySQLExecuter::close()  {
    if(this->mysql_)
        mysql_close(this->mysql_);
    this->mysql_ = nullptr;
}

bool MySQLExecuter::query(const char* cmd) {
    QueryNode query(this->mysql_);
    if (query.start(cmd)) {
        return true;
    }
    return false;
}

bool MySQLExecuter::query(const char* cmd, OUT vector<string>& result) {
    QueryNode query(this->mysql_);
    if (query.start(cmd)) {
        return query.fetch(result);
    }
    return false;
}

bool MySQLExecuter::query(const char* cmd, OUT vector<vector<string>>& result) {
    QueryNode query(this->mysql_);
    if (query.start(cmd)) {
        return query.fetch(result);
    }
    return false;
}

bool MySQLExecuter::query(const char* cmd, OUT DBDefine* ret) {
    QueryNode query(this->mysql_);
    vector<string> columns;
    if (query.start(cmd)) {
        if (query.fetch(columns)) {
            ret->deserialize(columns);
            return true;
        }
    }
    return false;
}


bool MySQLExecuter::query(const char* cmd, OUT vector<DBDefine *>& ret, DBDefineCreator creator) {
    vector<vector<string>> records;
    QueryNode query(this->mysql_);
    if (query.start(cmd)) {
        if (query.fetch(records)) {
            for (auto columns : records) {
                auto def = creator(this);
                def->deserialize(columns);
                ret.push_back(def);
            }
            return true;
        }
    }
    return false;
}

