#pragma once
class DBObject;
class COREAPI Gate {
  public:
    Gate();
    ~Gate();
    void onEnter(DBObject* account);
};

