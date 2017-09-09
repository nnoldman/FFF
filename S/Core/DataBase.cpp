#include "stdafx.h"
#include "DataBase.h"
#include "DBTable.h"
#include "MySqlExecuter.h"
#include "DBDefine.h"
DataBase::DataBase()
{
    mExecuter = new MySQLExecuter();
}


DataBase::~DataBase()
{
    delete mExecuter;
    dSafeDeleteMap2(mTables);
}


bool DataBase::initialize(const DBConfig& config)
{
    if (!mExecuter->initialize(config))
        return false;

    mExecuter->use(config.dbName.c_str());

    reGetTables();

    checkDefineToCreateTables.invoke(mExecuter);

    //Data::MySQL::Connector::registerConnector();

    //generateConnectString();

    //try
    //{
    //	_pSession = new Session(MySQL::Connector::KEY, _dbConnString);
    //}
    //catch (ConnectionFailedException& ex)
    //{
    //	std::cout << ex.displayText() << std::endl;
    //	std::cout << "Trying to connect without DB and create one ..." << std::endl;
    //	if (!createDB)
    //		return false;
    //}


    return true;
}

void DataBase::finish()
{
}

void DataBase::create_table_if_not_exist(const char* name)
{
}

bool DataBase::create_column_if_not_exist(const char* table, const char* key)
{
    auto res = mTables.find(table);
    if (res != mTables.end())
    {
        DBTable* sqltable = res->second;
        if (!sqltable->exist(key))
        {
            return sqltable->insertCol(key);
        }
    }
    return false;
}


bool DataBase::createTable(const char* name, const char* cmd)
{
    stringstream cmdstring;
    mExecuter->queryBegin(cmd);
    reGetTables();
    return hasTable(name);
}

bool DataBase::hasTable(const char* name)
{
    return mTables.find(name) != mTables.end();
}

bool DataBase::queryKey(string table, string key, const char* value)
{
    stringstream ss;
    ss << "SELECT COUNT(*) FROM " << table << " WHERE " << key << " = " << value;
    mExecuter->queryBegin(ss.str().c_str());
    return mExecuter->queryEnd();
}

bool DataBase::queryRecord(const char* cmd, std::vector<string>& result)
{
    mExecuter->queryBegin(cmd);
    return mExecuter->queryEnd(result);
}

bool DataBase::queryRecord(string table, string key, const char* value, std::vector<string>& result)
{
    stringstream ss;
    ss << "SELECT COUNT(*) FROM " << table << " WHERE " << key << " = " << value;
    mExecuter->queryBegin(ss.str().c_str());
    return mExecuter->queryEnd(result);
}

bool DataBase::queryRecord(string table, string key, const char* value, OUT DBDefine* result)
{
    stringstream ss;
    ss << "SELECT COUNT(*) FROM " << table << " WHERE " << key << " = " << value;
    mExecuter->queryBegin(ss.str().c_str());
    std::vector<string> records;
    auto ret = mExecuter->queryEnd(records);
    if (ret)
    {
        result->stream().set(records);
        result->deserialize();
    }
    return ret;
}

bool DataBase::pull(Value keyvalue, OUT DBDefine* def)
{
    return pull(def->key(), keyvalue, def);
}

bool DataBase::pull(const char* key, Value keyvalue, OUT DBDefine* def)
{
    stringstream ss;
    if (keyvalue.type()==Basic::ValueType::String)
        ss << "SELECT * FROM " << def->table() << " WHERE " << key << " = '" << keyvalue.toString() << "'";
    else
        ss << "SELECT * FROM " << def->table() << " WHERE " << key << " = " << keyvalue.toString();
    mExecuter->queryBegin(ss.str().c_str());
    std::vector<string> records;
    auto ret = mExecuter->queryEnd(records);
    if (ret)
    {
        def->set(records);
        def->deserialize();
    }
    return ret;
}

bool DataBase::commit(Value keyvalue, OUT DBDefine* def)
{
    return false;
}

bool DataBase::commit(OUT DBDefine* def)
{
    stringstream ssupdate;
    def->serializeForUpdate(ssupdate);
    stringstream cmd;
    cmd << "UPDATE " << def->table() << " SET " << ssupdate.str() << "WHERE id="<<def->id<<";";
    mExecuter->queryBegin(cmd.str().c_str());
    return mExecuter->queryEnd();
}

bool DataBase::insert(OUT DBDefine* def)
{
    stringstream ss;
    stringstream ssvalue;
    def->serialize();
    def->getValues(ssvalue);
    ss << "INSERT INTO " << def->table()<<" VALUES (" << ssvalue.str().c_str() << ");";
    mExecuter->queryBegin(ss.str().c_str());
    return mExecuter->queryEnd();
}

bool DataBase::insertAndQuery(Value keyvalue, OUT DBDefine* def)
{
    bool ret = insert(def);
    if (ret)
    {
        ret = pull(keyvalue, def);
    }
    return ret;
}

bool DataBase::insertAndQuery(const char* key, Value keyvalue, OUT DBDefine* def)
{
    bool ret = insert(def);
    if (ret)
    {
        ret = pull(key, keyvalue, def);
    }
    return ret;
}

bool DataBase::insertDefaultByGUID(const char* table, const char* guid)
{
    assert(table);
    assert(guid);
    assert(strlen(table));
    assert(strlen(guid));

    stringstream sm;
    sm << "INSERT INTO " << table << "(guid) VALUES (" << guid << ");";
    mExecuter->queryBegin(sm.str().c_str());
    return mExecuter->queryEnd();
}



DBTable* DataBase::getTable(const char* name)
{
    auto p = mTables.find(name);
    if (p == mTables.end())
        return nullptr;
    return p->second;
}

bool DataBase::createDB()
{
    /*if (!connectNoDB)
    	return false;

    try
    {
    	_pSession = new Session(MySQL::Connector::KEY, _dbConnString);
    }
    catch (ConnectionFailedException& ex)
    {
    	std::cout << ex.displayText() << std::endl;
    	return false;
    }*/
    return true;
}

void DataBase::generateConnectString()
{
    /*std::stringstream ss;
    ss << "host=" << mConfig.host
    	<< ";port=" << mConfig.port
    	<< ";user=" << mConfig.user
    	<< ";password=" << mConfig.password
    	<< ";db=" << mConfig.dbName
    	<< ";compress=true"
    	<< ";auto-reconnect=true"
    	<< ";secure-auth=true";*/
    //_dbConnString = ss.str();
}

void DataBase::reGetTables()
{
    dSafeDeleteMap2(mTables);

    stringstream sm;
    sm << "show tables;";
    mExecuter->queryBegin(sm.str().c_str());

    stringVectorVector tableNames;
    if (!mExecuter->queryEnd(tableNames))
    {
        //assert(0);
    }
    for (auto record : tableNames)
    {
        DBTable* table = new DBTable();
        table->name = record[0];
        table->refreshRecordCount();
        mTables.insert(make_pair(table->name, table));
    }
}

bool DataBase::connectNoDB()
{
    /*try
    {
    	Session session(MySQL::Connector::KEY, _dbConnString);
    	std::cout << "Connected to [" << "MySQL" << "] without database." << std::endl;
    	dbInfo(session);
    	session << "CREATE DATABASE IF NOT EXISTS "<< mConfig.dbName<< "; now";
    	std::cout << "Disconnecting ..." << std::endl;
    	session.close();
    	std::cout << "Disconnected." << std::endl;
    	return true;
    }
    catch (ConnectionFailedException& ex)
    {
    	std::cout << ex.displayText() << std::endl;
    	return false;
    }*/
    return true;
}

//void DataBase::dbInfo(Poco::Data::Session& session)
//{
//	std::cout << "Server Info: " << MySQL::Utility::serverInfo(session) << std::endl;
//	std::cout << "Server Version: " << MySQL::Utility::serverVersion(session) << std::endl;
//	std::cout << "Host Info: " << MySQL::Utility::hostInfo(session) << std::endl;
//}

void DataBase::bareboneMySQLTest(const char* host, const char* user, const char* pwd, const char* db, int port, const char* tableCreateString)
{
    //bareboneMySQLTest(mConfig.host.c_str(), mConfig.user.c_str(), mConfig.password.c_str(), mConfig.dbName.c_str()
    //	, mConfig.port, "create table account;");

    /*int rc;
    MYSQL* hsession = mysql_init(0);
    assert(hsession != 0);

    MYSQL* tmp = mysql_real_connect(hsession, host, user, pwd, db, port, 0, 0);
    assert(tmp == hsession);

    MYSQL_STMT* hstmt = mysql_stmt_init(hsession);
    assert(hstmt != 0);

    std::string sql = "DROP TABLE Test";
    mysql_real_query(hsession, sql.c_str(), static_cast<unsigned long>(sql.length()));

    sql = tableCreateString;
    rc = mysql_stmt_prepare(hstmt, sql.c_str(), static_cast<unsigned long>(sql.length()));
    assert(rc == 0);

    rc = mysql_stmt_execute(hstmt);
    assert(rc == 0);

    sql = "INSERT INTO Test VALUES (?,?,?,?,?)";
    rc = mysql_stmt_prepare(hstmt, sql.c_str(), static_cast<unsigned long>(sql.length()));
    assert(rc == 0);

    std::string str[3] = { "111", "222", "333" };
    int fourth = 4;
    float fifth = 1.5;

    MYSQL_BIND bind_param[5] = { { 0 } };

    bind_param[0].buffer = const_cast<char*>(str[0].c_str());
    bind_param[0].buffer_length = static_cast<unsigned long>(str[0].length());
    bind_param[0].buffer_type = MYSQL_TYPE_STRING;

    bind_param[1].buffer = const_cast<char*>(str[1].c_str());
    bind_param[1].buffer_length = static_cast<unsigned long>(str[1].length());
    bind_param[1].buffer_type = MYSQL_TYPE_STRING;

    bind_param[2].buffer = const_cast<char*>(str[2].c_str());
    bind_param[2].buffer_length = static_cast<unsigned long>(str[2].length());
    bind_param[2].buffer_type = MYSQL_TYPE_STRING;

    bind_param[3].buffer = &fourth;
    bind_param[3].buffer_type = MYSQL_TYPE_LONG;

    bind_param[4].buffer = &fifth;
    bind_param[4].buffer_type = MYSQL_TYPE_FLOAT;

    rc = mysql_stmt_bind_param(hstmt, bind_param);
    assert(rc == 0);

    rc = mysql_stmt_execute(hstmt);
    assert(rc == 0);

    sql = "SELECT * FROM Test";
    rc = mysql_stmt_prepare(hstmt, sql.c_str(), static_cast<unsigned long>(sql.length()));
    assert(rc == 0);

    char chr[3][5] = { { 0 } };
    unsigned long lengths[5] = { 0 };
    fourth = 0;
    fifth = 0.0f;

    MYSQL_BIND bind_result[5] = { { 0 } };

    bind_result[0].buffer = chr[0];
    bind_result[0].buffer_length = sizeof(chr[0]);
    bind_result[0].buffer_type = MYSQL_TYPE_STRING;
    bind_result[0].length = &lengths[0];

    bind_result[1].buffer = chr[1];
    bind_result[1].buffer_length = sizeof(chr[1]);
    bind_result[1].buffer_type = MYSQL_TYPE_STRING;
    bind_result[1].length = &lengths[1];

    bind_result[2].buffer = chr[2];
    bind_result[2].buffer_length = sizeof(chr[2]);
    bind_result[2].buffer_type = MYSQL_TYPE_STRING;
    bind_result[2].length = &lengths[2];

    bind_result[3].buffer = &fourth;
    bind_result[3].buffer_type = MYSQL_TYPE_LONG;
    bind_result[3].length = &lengths[3];

    bind_result[4].buffer = &fifth;
    bind_result[4].buffer_type = MYSQL_TYPE_FLOAT;
    bind_result[4].length = &lengths[4];

    rc = mysql_stmt_bind_result(hstmt, bind_result);
    assert(rc == 0);

    rc = mysql_stmt_execute(hstmt);
    assert(rc == 0);
    rc = mysql_stmt_fetch(hstmt);
    assert(rc == 0);

    assert(0 == std::strncmp("111", chr[0], 3));
    assert(0 == std::strncmp("222", chr[1], 3));
    assert(0 == std::strncmp("333", chr[2], 3));
    assert(4 == fourth);
    assert(1.5 == fifth);

    rc = mysql_stmt_close(hstmt);
    assert(rc == 0);

    sql = "DROP TABLE Test";
    rc = mysql_real_query(hsession, sql.c_str(), static_cast<unsigned long>(sql.length()));
    assert(rc == 0);

    mysql_close(hsession);*/
}

