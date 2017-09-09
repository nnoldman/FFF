#ifndef App_h__
#define App_h__

#include "Config.h"
#include "NetWork.h"
#include "DataBase.h"
#include "World.h"
#include "Gate.h"
#include "DBTableDefine.h"

class COREAPI App
{
public:
    static Config Config;
    static DataBase DataBase;
    static NetWork	Net;
    static World World;
    static Gate Gate;
    static App* Instance;
public:
    App(int narg, const char** args);
    virtual ~App();
public:
    virtual bool initialize() final;
    void quit();
    bool isQuiting() const;
    CommandLine& getCommandLine();
protected:
    virtual void archive() = 0;
    virtual void onQuit();
    virtual	const NetConfig& getNetConfig() = 0;
    virtual	const DBConfig& getDataBaseConfig() = 0;
    virtual	bool parseCommandLine() = 0;
    virtual	bool onInitializeEnd() = 0;
    virtual	bool onInitializeNet() = 0;
    virtual const vector<const DBTableDefine*>& getTableDefines() const= 0;
private:
    void run();
    virtual bool initializeDataBase()final;
    bool connectCenter();
private:
    CommandLine commandLine_;
    bool quiting_;
    bool isCenter_;
public:
    static int Main(App* app);
};
#endif // App_h__
