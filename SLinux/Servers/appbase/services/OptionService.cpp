#include "../appbase.h"
#include "OptionService.h"
#include "../default/PathConfiguration.h"
#include "../../basic/ServerID.h"

OptionService::OptionService() {
}


OptionService::~OptionService() {
}

bool OptionService::start() {
    auto path = PathConfiguration::appConfigurationFile(Basic::ServerID::get());
    if (!loader_.open(path.c_str()))
        return false;
    root_.Parse<0>(loader_.getBuffer());
    return true;
}

const char * OptionService::name() {
    return "OptionService";
}
