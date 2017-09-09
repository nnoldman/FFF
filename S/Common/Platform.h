#ifndef Platform_h__
#define Platform_h__

namespace Basic
{
class Platform
{
public:
    static void sleep(u32 time);

    static bool isPath(const char* str);

    static std::string generateGUIDString();

    static std::string generateGUIDSimpleString();
};
}
#endif // Platform_h__
