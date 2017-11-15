#ifndef DBDefine_h__
#define DBDefine_h__

#include "DBStream.h"
#include "Basic/Variable.h"
#include "Basic/ServerID.h"
#include "DBTableDefine.h"
#include "Basic/CharBuffer.h"
#include "DBExecuter.h"
class DBDefine {
  public:
    int id;
    DBExecuter* execter;
  public:
    virtual ~DBDefine() {}
    virtual const char* table() = 0;

    virtual const char* key() = 0;
    virtual const char* key2();

    virtual void deserialize(std::vector<string>& columns) final;
    virtual void serialize(stringstream& columns) final;

    virtual void serializeMe() = 0;
    virtual void deserializeMe() = 0;

    void set(vector<string>& values);
    //use key()
    bool pullByKey1();
    bool pullByKey1Key2(Basic::AnyValue key2value);
    //use key()
    bool commitByKey1();
    bool commitByKey1Key2(Basic::AnyValue key2value);
    bool insertByKey1();
    bool insertByKey1Key2(Basic::AnyValue key2value);
    bool insertAndQuery(Basic::AnyValue keyvalue);
    bool insertAndQuery(const char* key, Basic::AnyValue keyvalue);
    bool exist(const char* key, Basic::AnyValue value);
  public:
    inline DBStream& stream() {
        return stream_;
    }
  private:
    bool getValues(stringstream& ss);
  private:
    DBStream stream_;
};

template<typename T>
class DBDefineInterface: public DBDefine {
  public:
    static DBDefine* Create(DBExecuter* executer) {
        auto ret = (DBDefine*)(new T());
        ret->execter = executer;
        return ret;
    }
    virtual const char* table() override {
        return T::GetDefine().tableName();
    }
    virtual const char* key() override {
        return T::GetDefine().key();
    }
    virtual const char* key2() override {
        return T::GetDefine().key2();
    }
};
#endif // DBDefine_h__
