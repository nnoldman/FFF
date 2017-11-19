#include "../appbase.h"
#include "DBService.h"
#include "OptionService.h"
#include "../db/DBTable.h"
#include "../db/MySqlExecuter.h"
#include "../db/DBDefine.h"
#include "../db/DBTableDefine.h"
#include "../App.h"
DBService::DBService() {
    executer_ = new MySQLExecuter();
}

DBService::~DBService() {
    delete executer_;
    dSafeDeleteMap2(tables_);
}

bool DBService::start(const DBOption& config) {
    if (!executer_->initialize(config))
        return false;
    executer_->use();
    fetchTables();
    checkDefineToCreateTables.invoke(executer_);
    return true;
}

bool DBService::start() {
    if (!OptionService::get()->getOption(ServerID::get().c_str(), "db", this->option_))
        return false;
    if (!start(this->option_)) {
        return false;
    } else {
        auto ret = App::Instance->getTableDefines();
        for (auto def : ret) {
            if (!hasTable(def->tableName())) {
                createTable(def);
            } else {
                checkForAlterTableColumns(def);
            }
        }
    }
    return true;
}

void DBService::close() {
    if (this->executer_) {
        this->executer_->close();
        this->executer_ = nullptr;
    }
}
bool DBService::createTable(const char* name, const char* cmd) {
    if (executer_->query(cmd)) {
        fetchTables();
    }
    return hasTable(name);
}

bool DBService::createTable(const DBTableDefine* def) {
    stringstream cmd;
    if (def->generateCreateTableString(cmd)) {
        if (!this->createTable(def->tableName(), cmd.str().c_str())) {
            //LOG_DEBUG_A("Create Table %s Failed!", def->tableName());
            return false;
        }
    }
    return true;
}

const char* DBService::name() {
    return "DBService";
}

const DBOption & DBService::option() const {
    return this->option_;
}

void DBService::make_alter_columns(const vector<string>& source, const vector<string>& dest, OUT vector<string>& remove_columns, OUT vector<tuple<string, string>>& add_columns) {
    remove_columns.clear();
    add_columns.clear();
    auto finder = [](const vector<string>& arr, size_t start, string text) {
        size_t ret = -1;
        for (size_t i = start; i < arr.size(); ++i) {
            if (arr[i] == text) {
                ret = i;
                break;
            }
        }
        return ret;
    };
    for (size_t i = 0, start = 0; i < dest.size(); ++i) {
        auto cur = dest[i];
        auto index = finder(source, start, cur);
        if (index == -1) {
            add_columns.push_back(tuple<string, string>(i == 0 ? "" : dest[i - 1], dest[i]));
        } else if (index > start) {
            start = index;
            ++start;
        }
    }
    for (size_t i = 0, start = 0; i < source.size(); ++i) {
        auto cur = source[i];
        auto index = finder(dest, start, cur);
        if (index == -1) {
            remove_columns.push_back(cur);
        } else if (index > start) {
            start = index;
            ++start;
        }
    }
}

void DBService::make_alter_cmds(const vector<string>& remove_columns, const vector<tuple<string, string>>& add_columns, const DBTableDefine* def, OUT vector<string>& cmds) {
    {
        size_t pindex = 0;
        while (pindex < remove_columns.size()) {
            auto column = remove_columns[pindex];
            stringstream cmd;
            def->generateDropCloumnString(cmd, column);
            cmds.push_back(cmd.str());
            ++pindex;
        }
    }
    {
        size_t pindex = 0;
        while (pindex < add_columns.size()) {
            auto column = add_columns[pindex];
            stringstream cmd;
            def->generateAddCloumnString(cmd, std::get<0>(column), std::get<1>(column));
            cmds.push_back(cmd.str());
            ++pindex;
        }
    }
}

bool DBService::hasTable(const char* name) {
    return tables_.find(name) != tables_.end();
}

void DBService::checkDefines(const vector<const DBTableDefine*>& tableDefines) {
    for (auto def : tableDefines) {
        if (!this->hasTable(def->tableName())) {
            this->createTable(def);
        } else {
            this->checkForAlterTableColumns(def);
        }
    }
}

void DBService::checkForAlterTableColumns(const DBTableDefine* def) {
    assert(def);
    DBTable* table = getTable(def->tableName());
    assert(table);
    vector<string> remove_columns;
    vector<tuple<string, string>> add_columns;
    vector<string> currentColumns;
    for (auto it : def->columns())
        currentColumns.push_back(it.name);
    this->make_alter_columns(table->columns(), currentColumns, remove_columns, add_columns);
    vector<string> cmds;
    this->make_alter_cmds(remove_columns, add_columns, def, cmds);
    for (auto it : cmds) {
        executer_->query(it.c_str());
    }
}

bool DBService::queryKey(string table, string key, const char* value) {
    stringstream ss;
    ss << "SELECT COUNT(*) FROM " << table << " WHERE " << key << " = " << value << ";";;
    return executer_->query(ss.str().c_str());
}

DBTable* DBService::getTable(const char* name) {
    auto p = tables_.find(name);
    if (p == tables_.end())
        return nullptr;
    return p->second;
}

void DBService::fetchTables() {
    dSafeDeleteMap2(tables_);
    vector<vector<string>> tableNames;
    if (!executer_->query("show tables;",tableNames)) {
        return;
    }
    for (auto record : tableNames) {
        DBTable* table = new DBTable(this->executer_);
        table->name = record[0];
        table->dbName = executer_->config().dbName;
        table->fetchColumns();
        tables_.insert(make_pair(table->name, table));
    }
}


