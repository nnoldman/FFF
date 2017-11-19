#include "../appbase.h"
#include "DumpService.h"
#ifdef __GNUC__
    #include <unistd.h>
    //#include <bits\signum.h>
    #include <execinfo.h>
    #include <signal.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../basic/Platform.h"
DumpService::DumpService() {
}


DumpService::~DumpService() {
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

bool DumpService::start() {
    _initCrashDump(OnCrashHandler);
    return true;
}

const char* DumpService::name() {
    return "DumpService";
}
