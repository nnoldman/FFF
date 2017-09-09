#include "stdafx.h"
#include "DBTable.h"
#include "App.h"

DBTable::DBTable()
    :mRecordCount(0)
    , mExecuter(&App::DataBase.executer()) {
}


DBTable::~DBTable() {
}


bool DBTable::insert(const char* cmd) {
    int n = mRecordCount;
    mExecuter->queryBegin(cmd);
    refreshRecordCount();
    return n < mRecordCount;
}

//void SQLTable::freshColumns()
//{
//	/*stringstream str;
//	str << "SELECT COLUMN_NAME FROM " << dbName << ".COLUMNS WHERE TABLE_NAME = '" << name << "'";
//	try
//	{
//		*_pSession << str.str(), into(mcolumns), now;
//	}
//	catch (ConnectionException& ce)
//	{
//		std::cout << ce.displayText() << std::endl;
//	}
//	catch (StatementException& se)
//	{
//		std::cout << se.displayText() << std::endl;
//	}*/
//}

bool DBTable::exist(const char* col) {
    return std::find(mcolumns.begin(), mcolumns.end(), col) != mcolumns.end();
}

bool DBTable::insertCol(const char* col) {
    //alter table table1 add transactor varchar(10) not Null;
    /*stringstream str;
    str << "alter table " << name << "add " << col << " transactor varchar(10) not Null;";
    try
    {
    	*_pSession << str.str(), now;
    }
    catch (ConnectionException& ce)
    {
    	std::cout << ce.displayText() << std::endl;
    }
    catch (StatementException& se)
    {
    	std::cout << se.displayText() << std::endl;
    }
    freshColumns();*/
    return exist(col);
}

int DBTable::refreshRecordCount() {
    stringstream sm;
    sm << "SELECT COUNT(*) FROM " << name << ";";

    mExecuter->queryBegin(sm.str().c_str());
    mRecordCount = mExecuter->count();
    return mRecordCount;
}
