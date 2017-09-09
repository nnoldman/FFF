#include "base.h"
#include "Platform.h"

#ifdef _WIN32
#include "windows.h"
#endif

#ifdef WIN32
#include <objbase.h>
#pragma comment(lib,"ole32.lib")
#else
#include <uuid/uuid.h>
#pragma comment(lib,"uuid.so")
#endif

namespace Basic
{

void Platform::sleep(u32 time)
{
#ifdef _WIN32
    Sleep(time);
#endif
}

#include <sys\stat.h>

bool Platform::isPath(const char* str)
{
    struct stat info;
    stat(str, &info);
    return (((info.st_mode) & S_IFMT) == S_IFDIR);
}

GUID generateGuid()
{
    GUID guid;
#ifdef WIN32
    CoCreateGuid(&guid);
#else
    uuid_generate(reinterpret_cast<unsigned char*>(&guid));
#endif
    return guid;
}


std::string getGUIDString(const GUID& guid, const char* fmt)
{
    char buf[64] = { 0 };
#ifdef __GNUC__
    snprintf(
#else // MSVC
    _snprintf_s(
#endif
        buf,
        sizeof(buf),
        fmt,
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1],
        guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5],
        guid.Data4[6], guid.Data4[7]);
    return std::string(buf);
}

std::string Platform::generateGUIDString()
{
    GUID guid = generateGuid();
    return getGUIDString(guid, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}");
}

std::string Platform::generateGUIDSimpleString()
{
    GUID guid = generateGuid();
    return getGUIDString(guid, "%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X");
}
}
