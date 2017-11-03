#include "stdafx.h"
#include "App.h"
#include "App.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/FileChannel.h"
#include "PathConfiguration.h"
#include "Poco/File.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#ifdef WIN32
    #pragma comment(lib,"User32.lib")
#endif

App* App::Instance = nullptr;

EnvironmentConfig App::Config;

DataBase App::DataBase;

NetWork App::Net;

World App::World;

Gate App::Gate;

App::App(int narg, char* argv[])
    : Application(narg, argv)
    , commandLine_(narg, argv)
    , quiting_(false)
    , isCenter_(false)
{
    this->setWorkDirectory(argv[0]);
    Instance = this;
}

App::~App()
{
    Instance = nullptr;
    std::cout << "~App" << std::endl;
}

bool App::initialize()
{
    if (commandLine_.arg_count())
    {
        if (!parseCommandLine())
        {
            throw new std::logic_error("parseCommandLine Error");
            return false;
        }
    }

    if (!initializeLogger())
        return false;
    else
        LOG_INFO_A("Initialize Logger Sucessfully!");

    if (!Config.initialize(PathConfiguration::appConfigurationFile(ServerID::get()).c_str()))
        return false;

    if (!Net.initialize(getNetConfig()))
        return false;

    if (!onInitializeNet())
    {
        LOG_INFO_A("Initialize Net Failed!");
        return false;
    }
    else
    {
        LOG_INFO_A("Initialize Net Sucessfully!");
    }

    if (!initializeDataBase())
    {
        LOG_INFO_A("Initialize DataBase Failed!");
        return false;
    }
    else
    {
        LOG_INFO_A("Initialize DataBase Sucessfully!");
    }

    if (!isCenter_ && !connectCenter())
        return false;

    if (!loadGameConfig())
    {
        LOG_INFO_A("LoadGameConfig Failed!");
        return false;
    }
    else
    {
        LOG_INFO_A("LoadGameConfig Sucessfully!");
    }

    if (!World.initialize())
        return false;
    else
        LOG_INFO_A("Initialize World Sucessfully!");

    return this->onInitializeEnd();
}
int App::main(const std::vector<std::string>& args)
{
    if (!initialize())
        return EXIT_CONFIG;
    int bIsCtrl = 0;
#ifdef WIN32
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
void App::initialize(Application& app)
{
//   try
//   {
    //	//Util::Application::loadConfiguration("../env/center.json", PRIO_APPLICATION);
    //}
//   catch (Poco::FileNotFoundException exc)
//   {
    //	LOG_ERROR_A(exc.what());
//   }
    //Util::Application::initialize(*this);
    Util::Application::initialize(app);
}

void App::uninitialize()
{
    return Poco::Util::Application::uninitialize();
}

void App::reinitialize(Application& app)
{
    return Poco::Util::Application::reinitialize(app);
}

bool App::loadGameConfig()
{
    return true;
}

void crash_dump(int signo)
{
    char buf[1024];
    char cmd[1024];
    FILE *fh;

    printf("crashdetected: crash_dump(%d)", signo);

    snprintf(buf, sizeof(buf), "/proc/%d/cmdline", getpid());
    if (!(fh = fopen(buf, "r")))
        exit(0);
    if (!fgets(buf, sizeof(buf), fh))
        exit(0);
    fclose(fh);
    if (buf[strlen(buf) - 1] == '/n')
        buf[strlen(buf) - 1] = '/0';
    snprintf(cmd, sizeof(cmd), "date > ./crash.log", buf, getpid());
    printf(cmd);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "gdb %s %d -ex=bt >> ./crash.log", buf, getpid());
    printf(cmd);
    system(cmd);

    exit(-1);
}
void App::initCrashDump()
{
    signal(SIGSEGV, &crash_dump);
    signal(SIGFPE, &crash_dump);
    signal(SIGINT, &crash_dump);
    signal(SIGILL, &crash_dump);
    signal(SIGABRT, &crash_dump);
}

void App::mainLoop()
{
    Net.prosess();
}

bool App::initializeDataBase()
{
    if (!DataBase.initialize(getDataBaseConfig()))
    {
        return false;
    }
    else
    {
        auto ret = this->getTableDefines();
        for (auto def : ret)
        {
            if (!this->DataBase.hasTable(def->tableName()))
            {
                this->DataBase.createTable(def);
            }
            else
            {
                this->DataBase.checkForAlterTableColumns(def);
            }
        }
    }
    return true;
}

bool App::connectCenter()
{
    return true;
}

void App::setWorkDirectory(char* appName)
{
    Poco::Path dir(appName);
    printf("Current working directory : %s\n", Poco::Path::current().c_str());
    Basic::Platform::setWorkDirectory(dir.makeParent().toString().c_str());
    printf("Current working directory : %s\n", Poco::Path::current().c_str());
}

void App::onQuit()
{
    archive();
}



void App::archive()
{
}

void App::quit()
{
    quiting_ = true;
}

bool App::isQuiting() const
{
    return quiting_;
}

Basic::CommandLine& App::getCommandLine()
{
    return commandLine_;
}

bool App::initializeLogger()
{
    AutoPtr<FileChannel> fileChannel(new FileChannel());

    Poco::File file(PathConfiguration::appLoggerFile(ServerID::get()));
    Poco::Path path(file.path().c_str());
    Poco::File dir(path.parent());
    if (!dir.exists())
    {
        Basic::Platform::createDirectory(dir.path().c_str());
    }

    //指定日志路径及文件名
    fileChannel->setProperty("path", file.path().c_str());
    fileChannel->setProperty("archive", "timestamp");   //日志文件加时间戳
    Poco::AutoPtr<Poco::PatternFormatter> patternFormatter(new Poco::PatternFormatter());
    patternFormatter->setProperty("pattern", "%L%Y/%m/%d %H:%M:%S %s(%l): %t");    //每条日志时间
    auto channel = new Poco::FormattingChannel(patternFormatter, fileChannel);//初始化　Channel
    logger().setChannel(channel);//把　Application 的 Channel 设置为我们指定的输出
    return true;
}


