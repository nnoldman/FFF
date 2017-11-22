#include "../appbase.h"
#include "OptionService.h"
#include "../default/PathConfiguration.h"
#include "../../basic/ServerID.h"

OptionService::OptionService() {
    this->dynamic_ = false;
}


OptionService::~OptionService() {
}

bool OptionService::start() {
    auto path = PathConfiguration::appConfigurationFile(Basic::ServerID::get());
    if (!loader_.open(path.c_str()))
        return false;
    ParseResult ok = root_.Parse<0>(loader_.getBuffer());
    if (!ok) {
        LOG_INFO_A("Json Parse Error:(%s) %s (Position:%u)", path.c_str(), rapidjson::GetParseError_En(ok.Code()), ok.Offset());
        return false;
    }
    return true;
}

const char * OptionService::name() {
    return "OptionService";
}
