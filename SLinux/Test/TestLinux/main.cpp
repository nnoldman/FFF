#include <cstdio>
#include "Installer.h"
#include <unistd.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#ifdef __GNUC__
    #include <execinfo.h>
#endif
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
    snprintf(cmd, sizeof(cmd), "date > ./crash.log", buf, 1000);
    printf(cmd);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "gdb %s %d -ex=bt >> ./crash.log", buf, getpid());
    printf(cmd);
    system(cmd);
    exit(-1);
}

const int MAX_STACK_FRAMES = 32;

void OnCrashHandler(int signum)
{
    FILE* f = fopen("log/crash.txt", "at");
    if (nullptr == f)
    {
        exit(1);
        return;
    }
    try
    {
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
        for (i = 0; i < size; ++i)
        {
#if 0
            std::string symbol(strings[i]);
            std::string::size_type pos1 = symbol.find_first_of("[");
            std::string::size_type pos2 = symbol.find_last_of("]");
            std::string address = symbo.substr(pos1 + 1, pos2 - pos1 - 1);
            char cmd[128] = { 0, };
            sprintf(cmd, "addr2line -e gameserver %p", address.c_str());
            system(cmd);
#endif
            char szLine[512] = { 0, };
            sprintf(szLine, "%d %s\n", i, strings[i]);
            fwrite(szLine, 1, strlen(szLine), f);
            // fprintf(stderr, "%d %s\n",i, strings[i]);
        }
        free(strings);
#endif // __linux
    }
    catch (...)
    {
        //
    }
    fflush(f);
    fclose(f);
    f = nullptr;
    exit(1);
}
typedef void(*dump_handler)(int);
void initCrashDump(dump_handler handler)
{
    signal(SIGSEGV, handler);
    signal(SIGFPE, handler);
    signal(SIGINT, handler);
    signal(SIGILL, handler);
    signal(SIGABRT, handler);
}
class TestA
{
public:
    void printMe()
    {
        printf("printMe");
    }
};
void TestXX()
{
    int* p = nullptr;
    //initCrashDump(crash_dump);
    *p = 5;
}
int main(int narg, char* args[])
{
    //initCrashDump(crash_dump);
    initCrashDump(OnCrashHandler);
    TestXX();
    //initCrashDump(crash_dump);
    //initCrashDump(crash_dump);
    //Installer::run();
    return 0;
}