#ifndef DBExecuter_h__
#define DBExecuter_h__

#include "DBExecuter.h"
#include "mysql.h"

class MySQLExecuter:public DBExecuter {
  public:

    MySQLExecuter();

    ~MySQLExecuter();

    bool initialize(const DBConfig& config);

    void queryBegin(const char* cmd) const;

    /*
    	Only return first record or nothing.
    */
    bool queryEnd(stringVector& result);

    /*
    	return all eligible records.
    */
    bool queryEnd(stringVectorVector& result);

    bool queryEnd();

    virtual unsigned long count() override;


    virtual void use(const char* dataBaseName) const override;

  private:

    DBConfig mConfig;

    MYSQL* mConnection;
};




#endif // DBExecuter_h__
