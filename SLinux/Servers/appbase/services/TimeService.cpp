#include "../appbase.h"
#include "TimeService.h"
#include "Timers.h"

TimeService::TimeService() {
}


TimeService::~TimeService() {
}

void TimeService::tick() {
    Timers::getInstance()->tick();
}

bool TimeService::start() {
    return false;
}

const char * TimeService::name() {
    return "TimeService";
}
