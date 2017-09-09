#include "stdafx.h"
#include "MySqlExecuter.h"


MySQLExecuter::MySQLExecuter() {
}


MySQLExecuter::~MySQLExecuter() {
}

bool MySQLExecuter::initialize(const DBConfig& config) {
    mConfig = config;

    mConnection = mysql_init(0);
    assert(mConnection != 0);

    MYSQL* tmp = mysql_real_connect(mConnection, mConfig.host.c_str(), mConfig.user.c_str(), mConfig.password.c_str(),
                                    mConfig.dbName.c_str(), mConfig.port, 0, 0);
    assert(tmp == mConnection);

    MYSQL_STMT* hstmt = mysql_stmt_init(mConnection);
    assert(hstmt != 0);

    return true;
}


void MySQLExecuter::queryBegin(const char* cmd) const {
    assert(cmd);
    int res = mysql_real_query(mConnection, cmd, static_cast<unsigned long>(strlen(cmd)));
    printf("QUERY=>%s\n", cmd);
}



bool MySQLExecuter::queryEnd() {
    return  mysql_affected_rows(mConnection) > 0;
}


bool MySQLExecuter::queryEnd(stringVector& result) {
    MYSQL_RES* records = mysql_store_result(mConnection);
    if (records) {
        auto columns = mysql_num_fields(records);
        assert(records->row_count <= 1);
        MYSQL_ROW row = mysql_fetch_row(records);
        if (row) {
            for (int j = columns - 1; j >=0; --j) {
                result.push_back(row[j]);
            }
        }
        return result.size() > 0;
    } else {
        return false;
    }

    return result.size() > 0;
}


bool MySQLExecuter::queryEnd(stringVectorVector& result) {
    MYSQL_RES* records = mysql_store_result(mConnection);

    if (records) {
        auto columns = mysql_num_fields(records);
        for (auto i = 0; i < records->row_count; ++i) {
            MYSQL_ROW row = mysql_fetch_row(records);
            if (row) {
                stringVector record;
                for (auto j = 0; j < columns; ++j) {
                    record.push_back(row[j]);
                }
                result.push_back(record);
            }
        }
        return result.size() > 0;
    }

    return result.size() > 0;
}

unsigned long MySQLExecuter::count() {
    MYSQL_RES* ress = mysql_store_result(mConnection);
    if (ress == nullptr)
        return 0;
    MYSQL_ROW row = mysql_fetch_row(ress);
    if (ress)
        return ::atoi(row[0]);
    return 0;
}

void MySQLExecuter::use(const char* dataBaseName) const {
    stringstream cmd;
    cmd << "use database " << dataBaseName << ";";
    queryBegin(cmd.str().c_str());
}

