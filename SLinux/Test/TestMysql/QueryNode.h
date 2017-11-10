#ifndef QueryNode_h__
#define QueryNode_h__

class QueryNode
{
public:
    QueryNode(MYSQL* sql);
    ~QueryNode();
    bool query() const;
    bool query(vector<string>& ret);
    bool query(vector<vector<string>>& ret);
    MYSQL_ROW  nextRow();
private:
    ::size_t getColumns();
private:
    MYSQL* mysql_;
    MYSQL_RES* resource_;
};
#endif // QueryNode_h__
