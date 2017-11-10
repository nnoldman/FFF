#ifndef QueryNode_h__
#define QueryNode_h__
#include "DBDefine.h"

class QueryNode
{
public:
    typedef DBDefine* (*Creator)();
public:
    QueryNode(MYSQL* sql);
    ~QueryNode();
    bool query(const char* cmd, DBDefine* ret);
    bool query(const char* cmd, vector<DBDefine*>* ret);
    bool query(const char* cmd);
    ::size_t count();
protected:
    bool query() const;
    bool query(vector<string>& ret);
    bool query(vector<vector<string>>& ret);
    bool start(const char* cmd);
private:
    ::size_t getColumns();
private:
    MYSQL* mysql_;
    MYSQL_RES* resource_;
    const char* cmd_;
};
#endif // QueryNode_h__
