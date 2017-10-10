#include "base.h"
#include "Platform.h"

#ifdef _WIN32
#include "windows.h"
#include <objbase.h>
#pragma comment(lib,"ole32.lib")
#elif __GNUC__
#include <sys/types.h> /* For useconds_t. */
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace Basic
{
    void Platform::sleep(u32 time)
    {
#ifdef _WIN32
        Sleep(time);
#elif __GNUC__
#endif
    }

	int Platform::createDirectory(const char *pszDir)
	{
#ifdef __GNUC__
		auto status = mkdir(pszDir, ALLPERMS);
		perror(pszDir);
		return status;
#endif
	}


	int Platform::setWorkDirectory(const char* path)
	{
#ifdef WIN32
		return SetCurrentDirectory(path);
#elif __GNUC__
		return chdir(path);
#endif
	}

}
