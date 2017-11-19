#ifndef IService_h__
#define IService_h__


class ServiceBase {
  public:
    ServiceBase();
    virtual ~ServiceBase();
  public:
    virtual bool start() = 0;
    virtual const char* name() = 0;
    virtual void tick();
    virtual void close();
    bool dynamic() const;
  protected:
    bool dynamic_;
};

template<typename T>
class IService :public ServiceBase {
  public:
    static T*& get() {
        static T* obj = nullptr;
        return obj;
    }
    static T* createInstance() {
        assert(get() == nullptr);
        get() = new T();
        return get();
    }
};

#endif // IService_h__
