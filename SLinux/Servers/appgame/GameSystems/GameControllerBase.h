#ifndef GameControllerBase_h__
#define GameControllerBase_h__
class GameControllerBase
{
public:
    GameControllerBase();
    virtual ~GameControllerBase();
public:
    virtual void start();
    virtual void update();
};

template<typename T>
class GameController: public GameControllerBase
{
public:
    static T* getInstance()
    {
        return instance_;
    }
private:
    static T* instance_;

    friend class GameControllers;
};

template<typename T>
declare_var_once T* GameController<T>::instance_ = nullptr;

#endif // GameControllerBase_h__
