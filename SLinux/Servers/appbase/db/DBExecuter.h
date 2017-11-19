#ifndef DBExecuter_h__
#define DBExecuter_h__

#include "DBOption.h"
class DBDefine;
class DBTableDefine;
class DBExecuter {
  public:
    virtual ~DBExecuter() {}
    typedef DBDefine* (*DBDefineCreator)(DBExecuter*);

    virtual bool initialize(const DBOption& config);
    virtual bool query(const char* cmd) = 0;
    virtual bool query(const char* cmd, OUT vector<string>& result) = 0;
    virtual bool query(const char* cmd, OUT vector<vector<string>>& result) = 0;
    virtual bool query(const char* cmd, OUT DBDefine* ret) = 0;
    virtual bool query(const char* cmd, OUT vector<DBDefine*>& ret, DBDefineCreator creator) = 0;

    virtual unsigned long count(const char* tablaname) = 0;

    virtual void use() const = 0;
    virtual void close() = 0;

    bool pull(const char* key, Basic::AnyValue keyvalue, OUT DBDefine* def);
    /*
    �����Խ�ɫIDΪ����1��DBIDΪ����2�ı�������ȡ�������ݣ����ɵ������ڴ���Ҫʹ���߹���
    ����߱�
    */
    bool pullByKey1(const DBTableDefine& def, Basic::AnyValue keyvalue, DBDefineCreator creator, OUT std::vector<DBDefine*>& ret);
    /*
    ��ȡһ������
    */
    bool pullByKey1(OUT DBDefine* def);
    /*
    ��ȡһ������
    */
    bool pullByKey1Key2(DBDefine* def,Basic::AnyValue keyvalue);
    //delete
    bool commit(DBDefine* def);
    //delete then insert
    bool commitByKey1(DBDefine* def);
    //delete then insert
    bool commitByKey1Key2(DBDefine* def, Basic::AnyValue key2Value);
    bool deleteByKey1(DBDefine* def);
    bool deleteByKey1Key2(DBDefine* def, Basic::AnyValue key2Value);

    //bool insertAndQuery(Basic::AnyValue keyvalue, OUT DBDefine* def);
    //bool insertAndQuery(const char* key, Basic::AnyValue keyvalue, OUT DBDefine* def);

    const DBOption& config() const;
  private:
    bool insert(OUT DBDefine* def);
    string makeValue(const Basic::AnyValue& keyvalue);
  protected:
    DBOption config_;
};
#endif // DBExecuter_h__
