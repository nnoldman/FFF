#ifndef App_h__
#define App_h__
#include "Poco/Util/Application.h"
#include "db/DBTableDefine.h"
#include "services/IService.h"
class COREAPI App : public Poco::Util::Application {
  public:
    static App* Instance;
  public:
    App(int narg, char* argv[]);
    virtual ~App();
  public:
    virtual bool initialize() final;
    void quit();
    bool isQuiting() const;
    CommandLine& getCommandLine();
    virtual const vector<const DBTableDefine*>& getTableDefines() const = 0;
  protected:
    template<typename T>
    void addController() {
        auto ctrler = T::createInstance();
        serivces_.push_back(ctrler);
    }
  protected:
    virtual void archive() = 0;
    virtual void onQuit();
    virtual void addExternServices();
    virtual int main(const std::vector<std::string>& args) override;
    virtual void initialize(Application& app) override;
    virtual void uninitialize() override;
    virtual void reinitialize(Application& app) override;
    virtual bool loadGameConfig();
    virtual void mainLoop();
  private:
    virtual bool initializeCommandLine();
    virtual void addInnerServices();
    bool connectCenter();
    void setWorkDirectory(char* appName);
  private:
    vector<ServiceBase*> serivces_;
    CommandLine commandLine_;
    bool quiting_;
    bool isCenter_;
    int serverID_;
};
#endif // App_h__
