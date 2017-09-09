#include "base.h"
#include "CommandLine.h"
namespace Basic
{

CommandLine::CommandLine(int narg, const char** args)
{
    for (int i = 1; i < narg; ++i)
    {
        std::string element = args[i];
        size_t pos = element.find("=");
        if (pos != uString::npos)
        {
            std::string key = element.substr(0, pos);
            std::string value = element.substr(pos + 1);
            args_.Insert(key, value);
        }
    }
}

CommandLine::~CommandLine()
{
}

size_t CommandLine::arg_count()
{
    return args_.size();
}
}
