#ifndef QueryNode_h__
#define QueryNode_h__
#include "DBDefine.h"

class QueryNode {
  public:
    typedef DBDefine* (*Creator)();
  public:
    QueryNode(MYSQL* sql);
    ~QueryNode();

    bool start(const char* cmd);
    bool fetch() const;
    bool fetch(vector<string>& ret);
    bool fetch(vector<vector<string>>& ret);

    bool query(const char* cmd);

    operator bool();

    MYSQL_ROW nextRow();

  private:
    ::size_t getColumns();
    bool store();
  private:
    MYSQL* mysql_;
    MYSQL_RES* resource_;
    const char* cmd_;
};
#endif // QueryNode_h__
