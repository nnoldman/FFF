#ifndef App_h__
#define App_h__

#include "NetWork.h"
#include "DataBase.h"
#include "World.h"
#include "Gate.h"
#include "DBTableDefine.h"
#include "EnvironmentConfig.h"
#include "Poco/Util/Application.h"
#include "ServerID.h"

class COREAPI App : public Poco::Util::Application
{
public:
    static EnvironmentConfig Config;
    static class DataBase DataBase;
    static NetWork	Net;
    static class World World;
    static class Gate Gate;
    static App* Instance;
public:
    App(int narg, char* argv[]);
    virtual ~App();
public:
    virtual bool initialize() final;
    void quit();
    bool isQuiting() const;
    CommandLine& getCommandLine();
    bool initializeLogger();
protected:
    virtual void archive() = 0;
    virtual void onQuit();
    virtual	const NetConfig& getNetConfig() = 0;
    virtual	const DBConfig& getDataBaseConfig() = 0;
    virtual	bool parseCommandLine() = 0;
    virtual	bool onInitializeEnd() = 0;
    virtual	bool onInitializeNet() = 0;
    virtual const vector<const DBTableDefine*>& getTableDefines() const = 0;

    virtual int main(const std::vector<std::string>& args) override;
    virtual void initialize(Application& app) override;
    virtual void uninitialize() override;
    virtual void reinitialize(Application& app) override;
    virtual bool loadGameConfig();
    void initCrashDump();
    virtual void mainLoop();
private:
    //void run();
    virtual bool initializeDataBase()final;
    bool connectCenter();
    void setWorkDirectory(char* appName);
private:
private:
    CommandLine commandLine_;
    bool quiting_;
    bool isCenter_;
public:
};
#endif // App_h__
