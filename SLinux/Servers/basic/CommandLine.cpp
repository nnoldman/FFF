#include "base.h"
#include "CommandLine.h"
namespace Basic
{
	CommandLine::CommandLine(int narg, char* argv[])
	{
		for (int i = 1; i < narg; ++i)
		{
			std::string element = argv[i];
			size_t pos = element.find("=");
			if (pos != std::string::npos)
			{
				std::string key = element.substr(0, pos);
				std::string value = element.substr(pos + 1);
				this->args_.insert(make_pair(key, value));
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
