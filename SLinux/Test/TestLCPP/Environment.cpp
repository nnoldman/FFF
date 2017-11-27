#include "Environment.h"
#include <iostream>
#ifdef _WIN32
    #include "windows.h"
    #include <objbase.h>
    #pragma comment(lib,"ole32.lib")
#elif __GNUC__
    #include <sys/types.h> /* For useconds_t. */
    #include <sys/stat.h>
    #include <unistd.h>
    #include <time.h>
    #include <signal.h>
    #include <string.h>
    #include <execinfo.h>
    #include <fcntl.h>
    #include <map>
    #include <pthread.h>
    #include <unistd.h>
#endif

std::string Environment::appFileFullName_;

char Environment::spliter;

std::map<int, string> Environment::signalMap_;
void Environment::start() {
#if _WIN32
    spliter = '\\';
#elif __GNUC__
    spliter = '/';
#endif
    refreshName();
    installCrashReporter();
}

std::string Environment::appStoreDirectory() {
    auto pos = appFileFullName_.find_last_of(spliter);
    return appFileFullName_.substr(0, pos);
}

void Environment::installCrashReporter() {
    setCrashDumperHandler();
}

void Environment::sleep(int millSeconds) {
#if _WIN32
    ::Sleep(millSeconds);
#elif __GNUC__
    ::sleep(millSeconds);
#endif
}

int Environment::setCurrentWorkDirectory(const char* dir) {
    int ret = 0;
#ifdef WIN32
    ret = SetCurrentDirectoryA(dir);
#elif __GNUC__
    ret = chdir(dir);
#endif
    refreshName();
    return ret;
}

std::string Environment::getAppName() {
    auto pos = appFileFullName_.find_last_of(spliter);
    return appFileFullName_.substr(pos + 1);
}

const std::string& Environment::getAppFileFullName() {
    return appFileFullName_;
}

void Environment::refreshName() {
    char link[256];
    char path[256];
    sprintf(link, "/proc/%d/exe", getpid());
    auto i = readlink(link, path, sizeof(path));
    path[i] = '\0';
    appFileFullName_ = path;
}


std::string& Environment::getSignalName(int sig) {
    return signalMap_[sig];
}

void Environment::saveBackTrace(int sig) {
    Environment env;
    //打开文件
    time_t tSetTime;
    time(&tSetTime);
    tm* ptm = localtime(&tSetTime);
    char fname[256] = { 0 };
    sprintf(fname, "%s.%d-%d-%d_%d_%d_%d", env.getAppFileFullName().c_str(),
            ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,
            ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    FILE* f = fopen(fname, "a");
    if (f == NULL) {
        exit(1);
    }
    int fd = fileno(f);
    //锁定文件
    flock fl;
    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    fl.l_pid = getpid();
    fcntl(fd, F_SETLKW, &fl);
    //输出程序的绝对路径
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    auto count = readlink("/proc/self/exe", buffer, sizeof(buffer));
    if (count > 0) {
        buffer[count] = '\n';
        buffer[count + 1] = 0;
        fwrite(buffer, 1, count + 1, f);
    }
    //输出信息的时间
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "Dump Time: %d-%d-%d %d:%d:%d\n",
            ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,
            ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    fwrite(buffer, 1, strlen(buffer), f);
    //线程和信号
    sprintf(buffer, "Curr thread: %d, Catch signal:%s\n",
            pthread_self(), getSignalName(sig).c_str());
    fwrite(buffer, 1, strlen(buffer), f);
    //堆栈
    void* DumpArray[256];
    int    nSize = backtrace(DumpArray, 256);
    sprintf(buffer, "backtrace rank = %d\n", nSize);
    fwrite(buffer, 1, strlen(buffer), f);
    if (nSize > 0) {
        char** symbols = backtrace_symbols(DumpArray, nSize);
        if (symbols != NULL) {
            for (int i = 0; i < nSize; i++) {
                fwrite(symbols[i], 1, strlen(symbols[i]), f);
                fwrite("\n", 1, 1, f);
            }
            const char* line = "==============================================";
            fwrite(line, 1, strlen(line), f);
            for (int i = 0; i < nSize; ++i) {
                std::string symbol(symbols[i]);
                std::string::size_type pos1 = symbol.find_first_of("[");
                std::string::size_type pos2 = symbol.find_last_of("]");
                std::string address = symbol.substr(pos1 + 1, pos2 - pos1 - 1);
                char cmd[128] = { 0, };
                char   buf[1024] = { 0, };
                FILE   *stream;
                sprintf(cmd, "addr2line -e %s %s -f -C", env.getAppFileFullName().c_str(), address.c_str());
                stream = popen(cmd, "r"); //将“ls －l”命令的输出 通过管道读取（“r”参数）到FILE* stream
                fread(buf, sizeof(char), sizeof(buf), stream); //将刚刚FILE* stream的数据流读取到buf中
                string content = buf;
                string funcname;
                string fileAndLine = content;
                auto pos = content.find_first_of('\n');
                if (pos != string::npos) {
                    funcname = content.substr(0, pos);
                    fileAndLine = content.substr(pos + 1, content.length() - pos - 2);
                    fileAndLine += " ";
                    fileAndLine += funcname;
                    fileAndLine.insert(0, "\n");
                }
                fwrite(fileAndLine.c_str(), 1, fileAndLine.length(), f);
                pclose(stream);
            }
            free(symbols);
        }
    }
    //文件解锁后关闭, 最后终止进程
    fl.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &fl);
    fclose(f);
    exit(1);
}

#define SET_SIG(sig) signalMap_[sig] = #sig;

void Environment::setCrashDumperHandler() {
    signalMap_.clear();
    SET_SIG(SIGILL)//非法指令
    SET_SIG(SIGBUS)//总线错误
    SET_SIG(SIGFPE)//浮点异常
    SET_SIG(SIGABRT)//来自abort函数的终止信号
    SET_SIG(SIGSEGV)//无效的存储器引用(段错误)
    SET_SIG(SIGPIPE)//向一个没有读用户的管道做写操作
    SET_SIG(SIGTERM)//软件终止信号
    SET_SIG(SIGSTKFLT)//协处理器上的栈故障
    SET_SIG(SIGXFSZ)//文件大小超出限制
    SET_SIG(SIGTRAP)//跟踪陷阱

    for (auto it : signalMap_) {
        signal(it.first, saveBackTrace);
    }
}


std::string Environment::currentWorkDirectory() {
    char path[256] = { 0 };
    getcwd(path, 256);
    return path;
}
