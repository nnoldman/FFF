#include "../appbase.h"
#include "LoggerService.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/FileChannel.h"
#include "PathConfiguration.h"
#include "Poco/File.h"
#include "../App.h"
LoggerService::LoggerService() {
}


LoggerService::~LoggerService() {
}

bool LoggerService::start() {
    AutoPtr<FileChannel> fileChannel(new FileChannel());
    Poco::File file(PathConfiguration::appLoggerFile(ServerID::get()));
    Poco::Path path(file.path().c_str());
    Poco::File dir(path.parent());
    if (!dir.exists()) {
        Basic::Environment::createDirectory(dir.path().c_str());
    }
    //指定日志路径及文件名
    fileChannel->setProperty("path", file.path().c_str());
    fileChannel->setProperty("archive", "timestamp");   //日志文件加时间戳
    Poco::AutoPtr<Poco::PatternFormatter> patternFormatter(new Poco::PatternFormatter());
    patternFormatter->setProperty("pattern", "%L%Y/%m/%d %H:%M:%S %s(%l): %t");    //每条日志时间
    auto channel = new Poco::FormattingChannel(patternFormatter, fileChannel);//初始化　Channel
    App::Instance->logger().setChannel(channel);//把　Application 的 Channel 设置为我们指定的输出
    return true;
}

const char * LoggerService::name() {
    return "LoggerService";
}
