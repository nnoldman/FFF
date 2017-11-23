#include "../appbase.h"
#include "DumpService.h"
DumpService::DumpService() {
}


DumpService::~DumpService() {
}
bool DumpService::start() {
    return true;
}

const char* DumpService::name() {
    return "DumpService";
}
