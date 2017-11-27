#pragma once
class ControllerBase {
  public:
    ControllerBase();
    virtual ~ControllerBase();
  public:
    virtual bool initialize() {
        return true;
    }
};

template<typename T>
class ControllerInterface :public ControllerBase {
  protected:
    ControllerInterface() {
    }
  public:
    static T*& get() {
        static T* obj = nullptr;
        return obj;
    }
    static T* createInstance() {
        get() = new T();
        return get();
    }
};

class NetController :public ControllerInterface<NetController> {
  public:
    virtual bool initialize() override;
};
class Test_templete {
  public:
    Test_templete();
    ~Test_templete();
};

