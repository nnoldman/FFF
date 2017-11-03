#include "Installer.h"
#include <sys/stat.h>

int createDirectory(const char *pszDir)
{
    auto status = mkdir(pszDir, ALLPERMS);
    perror("createDirectory");
    return status;
}

Function(Test_Path)
{
    //assert(createDirectory("../log") == 0);
}
