#include "stdafx.h"
#include "App.h"

App* App::Instance = nullptr;

Config App::Config;

DataBase App::DataBase;

NetWork App::Net;

World App::World;

Gate App::Gate;

App::App(int narg, const char** args)
    :commandLine_(narg, args)
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

    if (!Config.initialize("..\\..\\config.xml"))
        return false;

    if (!Net.initialize(getNetConfig()))
        return false;

    if (!onInitializeNet())
        return false;

    if (!initializeDataBase())
        return false;

    if (!isCenter_ && !connectCenter())
        return false;

    if (!World.initialize())
        return false;

    return this->onInitializeEnd();
}

void App::run()
{
    while (!quiting_)
    {
        Net.prosess();
        Platform::sleep(5);
    }
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

int App::Main(App* app)
{
    if (!app->initialize())
        return 1;
    app->run();
    app->onQuit();
    return 0;
}


