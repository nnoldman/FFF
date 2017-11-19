#include "../appbase.h"
#include "IService.h"
ServiceBase::ServiceBase()
    :dynamic_(true) {
}

ServiceBase::~ServiceBase() {
}

bool ServiceBase::start() {
    return true;
}

void ServiceBase::tick() {
}

void ServiceBase::close() {
}

bool ServiceBase::dynamic() const {
    return this->dynamic_;
}

