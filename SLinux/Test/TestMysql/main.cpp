// TestMysql.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MySqlExecuter.h"


int main()
{
    {
        DBConfig config;
        config.host = "43.248.102.164";
        config.user = "root";
        config.password = "ni2handan";
        config.port = 3306;
        config.dbName = "ff";
        //
        MySQLExecuter executer;
        assert(executer.initialize(config));
        auto columns = executer.queryBegin("select * from game_items1");
        vector<vector<string>> records;
        if (!executer.queryEnd(records))
        {
        }
    }
    return 0;
}

