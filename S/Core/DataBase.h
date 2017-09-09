#pragma once
#include "ConfigInfo.h"
#include "DBExecuter.h"
#include "DBTable.h"
#include "DBStream.h"

class DBDefine;

class COREAPI DataBase
{
public:
    DataBase();
    ~DataBase();

    Delegate1<bool, DBExecuter*> checkDefineToCreateTables;

    bool initialize(const DBConfig& config);

    void finish();

    void create_table_if_not_exist(const char* name);

    bool create_column_if_not_exist(const char* table, const char* key);

    bool createTable(const char* name, const char* cmd);

    bool hasTable(const char* name);

    bool queryKey(string table, string key, const char* value);

    bool queryRecord(string table, string key, const char* value, OUT DBDefine* result);
    bool queryRecord(string table, string key, const char* value, std::vector<string>& result);
    bool queryRecord(const char* cmd, std::vector<string>& result);

    bool pull(Value keyvalue, OUT DBDefine* def);
    bool pull(const char* key, Value keyvalue, OUT DBDefine* def);
    bool commit(OUT DBDefine* def);
    bool commit(Value keyvalue, OUT DBDefine* def);
    bool insert(OUT DBDefine* def);
    /*
     *	insert and record ,then execute query
     */
    bool insertAndQuery(Value keyvalue, OUT DBDefine* def);
    bool insertAndQuery(const char* key, Value keyvalue, OUT DBDefine* def);

    bool insertDefaultByGUID(const char* table, const char* guid);

    DBExecuter& executer();

    DBTable* getTable(const char* name);
    template<typename T>
    bool insertKeyValue(const char* table, T value, T value1)
    {
        stringstream str;
        str << "INSERT INTO " << table << " VALUES (?,?) ";
        try
        {
            *_pSession << str.str(), use(value), use(value1), now;
            return true;
        }
        catch (ConnectionException& ce)
        {
            std::cout << ce.displayText() << std::endl;
        }
        catch (StatementException& se)
        {
            std::cout << se.displayText() << std::endl;
        }
        return false;
    }
public:

    bool createDB();

private:

    void generateConnectString();
    void reGetTables();
    bool connectNoDB();
    //static void dbInfo(Poco::Data::Session& session);
    void bareboneMySQLTest(const char* host, const char* user, const char* pwd, const char* db, int port, const char* tableCreateString);

private:

    DBExecuter* mExecuter;

    //Poco::SharedPtr<Poco::Data::Session> _pSession;

    map<string, DBTable*> mTables;
};




inline DBExecuter& DataBase::executer()
{
    return *mExecuter;
}