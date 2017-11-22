#include "appbase.h"
#include "App.h"

#include "services/LoggerService.h"
#include "services/DBService.h"
#include "services/WorldService.h"
#include "services/OptionService.h"
#include "services/NetService.h"
#include "services/TimeService.h"

#ifdef WIN32
    #pragma comment(lib,"User32.lib")
#endif

App* App::Instance = nullptr;

App::App(int narg, char* argv[])
    : Application(narg, argv)
    , commandLine_(narg, argv)
    , quiting_(false)
    , isCenter_(false)
    , serverID_(0) {
    this->setWorkDirectory(argv[0]);
    Instance = this;
}

App::~App() {
    Instance = nullptr;
    std::cout << "~App" << std::endl;
}
void App::addInnerServices() {
    addController<LoggerService>();
    addController<OptionService>();
    addController<NetService>();
    addController<DBService>();
    addController<WorldService>();
    addController<TimeService>();
}

bool App::initialize() {
    LOG_INFO_A("%s",string("=====================Start Application====================="));

    if (!initializeCommandLine()) {
        LOG_INFO_A("InitializeCommandLine Failed !");
        return false;
    }

    addInnerServices();
    addExternServices();

    for (auto it : this->serivces_) {
        if (it->start()) {
            LOG_INFO_A("Service Start %s Successfully!", string(it->name()));
        } else {
            LOG_INFO_A("Service Start %s Failed!", string(it->name()));
            return false;
        }
    }
    return true;
}
int App::main(const std::vector<std::string>& args) {
    if (!initialize())
        return EXIT_CONFIG;
#ifdef WIN32
    int bIsCtrl = 0;
    while (!bIsCtrl)
#else
    while (!quiting_)
#endif
    {
        mainLoop();
        Platform::sleep(5);
#ifdef WIN32
        bIsCtrl = (::GetAsyncKeyState(VK_RETURN) & 0x8000);
#endif
    }
    this->onQuit();
    return EXIT_OK;
}
void App::initialize(Application& app) {
    Util::Application::initialize(app);
}

void App::uninitialize() {
    return Poco::Util::Application::uninitialize();
}

void App::reinitialize(Application& app) {
    return Poco::Util::Application::reinitialize(app);
}

bool App::initializeCommandLine() {
    if (commandLine_.arg_count()) {
        auto commandline = this->getCommandLine();
        commandline.get("serverID", serverID_);
        string serverID;
        commandline.get("serverID", serverID);
        ServerID::set(serverID.c_str());
        return serverID_ >= 0;
    }
    return false;
}
void App::mainLoop() {
    for (auto it : this->serivces_) {
        if(it->dynamic())
            it->tick();
    }
}



bool App::connectCenter() {
    return true;
}

void App::setWorkDirectory(char* appName) {
    Poco::Path dir(appName);
    printf("Current working directory : %s\n", Poco::Path::current().c_str());
    Basic::Platform::setWorkDirectory(dir.makeParent().toString().c_str());
    printf("Current working directory : %s\n", Poco::Path::current().c_str());
}

void App::onQuit() {
    archive();
}

void App::addExternServices() {
}

void App::archive() {
}

void App::quit() {
    quiting_ = true;
}

bool App::isQuiting() const {
    return quiting_;
}

Basic::CommandLine& App::getCommandLine() {
    return commandLine_;
}


