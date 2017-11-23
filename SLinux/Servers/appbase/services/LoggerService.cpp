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
    //ָ����־·�����ļ���
    fileChannel->setProperty("path", file.path().c_str());
    fileChannel->setProperty("archive", "timestamp");   //��־�ļ���ʱ���
    Poco::AutoPtr<Poco::PatternFormatter> patternFormatter(new Poco::PatternFormatter());
    patternFormatter->setProperty("pattern", "%L%Y/%m/%d %H:%M:%S %s(%l): %t");    //ÿ����־ʱ��
    auto channel = new Poco::FormattingChannel(patternFormatter, fileChannel);//��ʼ����Channel
    App::Instance->logger().setChannel(channel);//�ѡ�Application �� Channel ����Ϊ����ָ�������
    return true;
}

const char * LoggerService::name() {
    return "LoggerService";
}
