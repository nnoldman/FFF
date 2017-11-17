#include "stdafx.h"
#include "App.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/FileChannel.h"
#include "PathConfiguration.h"
#include "Poco/File.h"
#include "Timers.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#ifdef __GNUC__
    #include <execinfo.h>
#endif

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
    , isCenter_(false) {
    this->setWorkDirectory(argv[0]);
    Instance = this;
}

App::~App() {
    Instance = nullptr;
    std::cout << "~App" << std::endl;
}

bool App::initialize() {
    if (commandLine_.arg_count()) {
        if (!parseCommandLine()) {
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
    if (!onInitializeNet()) {
        LOG_INFO_A("Initialize Net Failed!");
        return false;
    } else {
        LOG_INFO_A("Initialize Net Sucessfully!");
    }
    if (!initializeDataBase()) {
        LOG_INFO_A("Initialize DataBase Failed!");
        return false;
    } else {
        LOG_INFO_A("Initialize DataBase Sucessfully!");
    }
    if (!isCenter_ && !connectCenter())
        return false;
    if (!loadGameConfig()) {
        LOG_INFO_A("LoadGameConfig Failed!");
        return false;
    } else {
        LOG_INFO_A("LoadGameConfig Sucessfully!");
    }
    if (!World.initialize())
        return false;
    else
        LOG_INFO_A("Initialize World Sucessfully!");
    return this->onInitializeEnd();
}
int App::main(const std::vector<std::string>& args) {
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
void App::initialize(Application& app) {
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

void App::uninitialize() {
    return Poco::Util::Application::uninitialize();
}

void App::reinitialize(Application& app) {
    return Poco::Util::Application::reinitialize(app);
}

bool App::loadGameConfig() {
    return true;
}

void crash_dump(int signo) {
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

const int MAX_STACK_FRAMES = 64;

void OnCrashHandler(int signum) {
    Basic::Platform::createDirectory("log");
    FILE* f = fopen("crash_app.txt", "at");
    if (nullptr == f) {
        exit(1);
        return;
    }
    try {
        char szLine[512] = { 0, };
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        int nLen1 = sprintf(szLine
                            , "#########################################################\n[%04d-%02d-%02d %02d:%02d:%02d][crash signal number:%d]\n"
                            , now->tm_year + 1900
                            , now->tm_mon + 1
                            , now->tm_mday
                            , now->tm_hour
                            , now->tm_min
                            , now->tm_sec
                            , signum);
        fwrite(szLine, 1, strlen(szLine), f);
#ifdef __linux
        void* array[MAX_STACK_FRAMES];
        size_t size = 0;
        char** strings = nullptr;
        size_t i, j;
        signal(signum, SIG_DFL);
        size = backtrace(array, MAX_STACK_FRAMES);
        strings = (char**)backtrace_symbols(array, size);
        //fprintf(stderr, "oncrash;\n");
        for (i = 0; i < size; ++i) {
#if 1
            std::string symbol(strings[i]);
            std::string::size_type pos1 = symbol.find_first_of("[");
            std::string::size_type pos2 = symbol.find_last_of("]");
            std::string address = symbol.substr(pos1 + 1, pos2 - pos1 - 1);
            char cmd[128] = { 0, };
            sprintf(cmd, "addr2line -e appgame.out %p", address.c_str());
            system(cmd);
#endif
            char szLine[512] = { 0, };
            sprintf(szLine, "%d %s\n", i, strings[i]);
            fwrite(szLine, 1, strlen(szLine), f);
            // fprintf(stderr, "%d %s\n",i, strings[i]);
        }
        free(strings);
#endif // __linux
    } catch (...) {
        //
    }
    fflush(f);
    fclose(f);
    f = nullptr;
    exit(1);
}
typedef void(*dump_handler)(int);
void _initCrashDump(dump_handler handler) {
    signal(SIGSEGV, handler);
    signal(SIGFPE, handler);
    signal(SIGINT, handler);
    signal(SIGILL, handler);
    signal(SIGABRT, handler);
}

void App::initCrashDump() {
    //_initCrashDump(OnCrashHandler);
}

void App::mainLoop() {
    Net.prosess();
    World.process();
    Timers::getInstance()->tick();
}

bool App::initializeDataBase() {
    if (!DataBase.initialize(getDataBaseConfig())) {
        return false;
    } else {
        auto ret = this->getTableDefines();
        for (auto def : ret) {
            if (!this->DataBase.hasTable(def->tableName())) {
                this->DataBase.createTable(def);
            } else {
                this->DataBase.checkForAlterTableColumns(def);
            }
        }
    }
    return true;
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

bool App::initializeLogger() {
    AutoPtr<FileChannel> fileChannel(new FileChannel());
    Poco::File file(PathConfiguration::appLoggerFile(ServerID::get()));
    Poco::Path path(file.path().c_str());
    Poco::File dir(path.parent());
    if (!dir.exists()) {
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


