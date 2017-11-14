#pragma once
#include "DBExecuter.h"
#include "DBTable.h"
#include "DBStream.h"

class DBDefine;
class DBTableDefine;

class DataBase {
  public:

    DataBase();
    ~DataBase();

    Delegate1<bool, DBExecuter*> checkDefineToCreateTables;

    bool initialize(const DBConfig& config);
    void finish();
    void checkDefines(const vector<const DBTableDefine*>& tableDefines);
    bool hasTable(const char* name);
    bool queryKey(string table, string key, const char* value);
    DBExecuter& executer();
    DBTable* getTable(const char* name);
    template<typename T>
    T* createDefine();
  public:
    void make_alter_columns(
        const vector<string>& source
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
    void fetchTables();
    bool createTable(const DBTableDefine* def);
    void checkForAlterTableColumns(const DBTableDefine* def);
  private:
    DBExecuter* executer_;
    map<string, DBTable*> tables_;
};

inline DBExecuter& DataBase::executer() {
    return *executer_;
}

template<typename T>
T* DataBase::createDefine() {
    auto ret= (T*)DBDefineInterface<T>::Create(this->executer_);
    return ret;
}
