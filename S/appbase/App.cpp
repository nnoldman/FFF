#include "stdafx.h"
#include "App.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/FileChannel.h"

App* App::Instance = nullptr;

EnvironmentConfig App::Config;

DataBase App::DataBase;

NetWork App::Net;

World App::World;

Gate App::Gate;

App::App(int narg, char* argv[])
    : commandLine_(narg, argv)
    , Application(narg, argv)
    , quiting_(false)
    , isCenter_(false)
{
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

    if (!Config.initialize("..\\..\\config.xml"))
        return false;

    if (!Net.initialize(getNetConfig()))
        return false;

    if (!onInitializeNet())
        return false;
    else
        LOG_INFO_A("Initialize Net Sucessfully!");

    if (!initializeDataBase())
        return false;
    else
        LOG_INFO_A("Initialize DataBase Sucessfully!");

    if (!isCenter_ && !connectCenter())
        return false;

    if (!loadGameConfig())
    {
        LOG_INFO_A("loadGameConfig Failed!");
        return false;
    }
    else
    {
        LOG_INFO_A("loadGameConfig Sucessfully!");
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

    while (!quiting_)
    {
        Net.prosess();
        Platform::sleep(5);
    }

    this->onQuit();
    return EXIT_OK;
}
void App::initialize(Application& app)
{
    Util::Application::loadConfiguration("../env/app.json", PRIO_APPLICATION);
    Util::Application::initialize(*this);
}

void App::uninitialize()
{
    return __super::uninitialize();
}

void App::reinitialize(Application& app)
{
    return __super::reinitialize(app);
}

bool App::loadGameConfig()
{
    return true;
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
                stringstream cmd;
                if (def->generateCreateTableString(cmd))
                {
                    if (!this->DataBase.createTable(def->tableName(), cmd.str().c_str()))
                    {
                        printf_s("Create Table %s Failed!", def->tableName());
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool App::connectCenter()
{
    return true;
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
    stringstream logFile;
    logFile << "../Log/" << ServerID::get() << "/";
    Basic::Platform::createDirectory(logFile.str().c_str());
    logFile << "log.txt";
    fileChannel->setProperty("path", logFile.str());     //指定日志路径及文件名
    fileChannel->setProperty("archive", "timestamp");   //日志文件加时间戳
    Poco::AutoPtr<Poco::PatternFormatter> patternFormatter(new Poco::PatternFormatter());
    patternFormatter->setProperty("pattern", "%Y/%m/%d %H:%M:%S %s(%l): %t");    //每条日志时间
    auto channel = new Poco::FormattingChannel(patternFormatter, fileChannel);//初始化　Channel
    logger().setChannel(channel);//把　Application 的 Channel 设置为我们指定的输出
    return true;
}


