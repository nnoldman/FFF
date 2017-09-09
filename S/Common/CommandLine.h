#pragma once
#include "uString.h"
#include "Array.h"
#include "Map.h"
namespace Basic
{
class CommandLine
{
public:
    CommandLine(int narg, const char** args);
    ~CommandLine();

    template<typename T>
    void get(const char* key, T& v)
    {
        if (args_.findkey(key))
            StringHelper::setValue(args_[key].c_str(), &v);
    }
    size_t arg_count();
private:
    Map<std::string, std::string> args_;
};
}
