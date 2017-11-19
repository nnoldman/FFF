#ifndef DBService_h__
#define DBService_h__

#include "IService.h"
#include "../db/DBExecuter.h"
#include "../db/DBTable.h"
#include "../db/DBStream.h"
#include "../db/DBDefine.h"
#include "../db/DBOption.h"

class DBTableDefine;

class DBService:public IService<DBService> {
  public:

    DBService();
    ~DBService();

    Basic::Delegate1<bool, DBExecuter*> checkDefineToCreateTables;

    virtual bool start() override;
    bool start(const DBOption& config);
    virtual void close() ;
    void checkDefines(const vector<const DBTableDefine*>& tableDefines);
    bool hasTable(const char* name);
    bool queryKey(string table, string key, const char* value);
    DBExecuter& executer();
    DBTable* getTable(const char* name);
    template<typename T>
    T* createDefine();

    virtual const char* name() override;

    const DBOption& option() const;

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
    DBOption option_;
};

inline DBExecuter& DBService::executer() {
    return *executer_;
}

template<typename T>
T* DBService::createDefine() {
    auto ret= (T*)DBDefineInterface<T>::Create(this->executer_);
    return ret;
}
#endif // DBService_h__
