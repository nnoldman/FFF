#ifndef PathConfiguration_h__
#define PathConfiguration_h__

#include <string>
#include <sstream>
class PathConfiguration
{
public:
	static const std::string appConfigurationFile(std::string serverID)
	{
		return "../env/config.xml";
	}
	static const std::string appLoggerFile(std::string serverID)
	{
		std::stringstream ret;
		ret << "../log/" << serverID << "/log.txt";
		return ret.str();
	}
};
#endif // PathConfiguration_h__

