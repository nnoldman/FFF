#pragma once
#include "DBExecuter.h"
#include "DBTable.h"
#include "DBStream.h"
#include "AnyObject.h"

class DBDefine;
class DBTableDefine;

class COREAPI DataBase
{
public:
    typedef DBDefine* (*DBDefineCreator)();

    DataBase();
    ~DataBase();

    Delegate1<bool, DBExecuter*> checkDefineToCreateTables;

    bool initialize(const DBConfig& config);

    void finish();
    bool createTable(const DBTableDefine* def);
    bool hasTable(const char* name);
    void checkForAlterTableColumns(const DBTableDefine* def);

    bool queryKey(string table, string key, const char* value);

    bool queryRecord(string table, string key, const char* value, OUT DBDefine* result);
    bool queryRecord(string table, string key, const char* value, std::vector<string>& result);
    bool queryRecord(const char* cmd, std::vector<string>& result);

    bool pull(AnyObject keyvalue, OUT DBDefine* def);
    bool pull(const char* key, AnyObject keyvalue, OUT DBDefine* def);
    /*
    适用以角色ID为主键1、DBID为主键2的表，上线拉取数据，生成的数据内存需要使用者管理。
    如道具表
    */
    bool pullByPrimaryKey(const DBTableDefine& def, AnyObject keyvalue, DBDefineCreator creator, OUT std::list<DBDefine*>& ret);

    bool commitByKey1(DBDefine* def);
    bool commitByKey1Key2(DBDefine* def, AnyObject key2Value);
    bool deleteByKey1(DBDefine* def);
    bool deleteByKey1Key2(DBDefine* def, AnyObject key2Value);

    bool insert(OUT DBDefine* def);
    /*
     *	insert and record ,then execute query
     */
    bool insertAndQuery(AnyObject keyvalue, OUT DBDefine* def);
    bool insertAndQuery(const char* key, AnyObject keyvalue, OUT DBDefine* def);

    bool insertDefaultByGUID(const char* table, const char* guid);


    DBExecuter& executer();

    DBTable* getTable(const char* name);
public:
    bool createDB();
private:
    void make_alter_columns(const vector<string>& source
                            , const vector<string>& dest
                            , OUT vector<string>& remove_columns
                            , OUT vector<tuple<string, string>>& add_columns
                           );
    void make_alter_cmds(
        const vector<string>& remove_columns
        , const vector<tuple<string, string>>& add_columns
        , const DBTableDefine* def
        , OUT vector<string>& cmds
    );
    bool createTable(const char* name, const char* cmd);
    void generateConnectString();
    void fetchTables();
    bool connectNoDB();
    //static void dbInfo(Poco::Data::Session& session);
    void bareboneMySQLTest(const char* host, const char* user, const char* pwd, const char* db, int port, const char* tableCreateString);
private:
    DBExecuter* executer_;
    //Poco::SharedPtr<Poco::Data::Session> _pSession;
    map<string, DBTable*> tables_;
};




inline DBExecuter& DataBase::executer()
{
    return *executer_;
}
