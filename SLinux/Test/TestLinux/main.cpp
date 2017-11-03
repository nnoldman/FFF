#include <cstdio>
#include "Installer.h"
#include <unistd.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
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
void initCrashDump()
{
    signal(SIGSEGV, &crash_dump);
    signal(SIGFPE, &crash_dump);
    signal(SIGINT, &crash_dump);
    signal(SIGILL, &crash_dump);
    signal(SIGABRT, &crash_dump);
}
class TestA
{
public:
    void printMe()
    {
        printf("printMe");
    }
};
int main(int narg, char* args[])
{
    initCrashDump();
    TestA* p = nullptr;
    p->printMe();

    Installer::run();
    return 0;
}