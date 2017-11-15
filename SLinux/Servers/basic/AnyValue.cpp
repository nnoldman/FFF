#include "base.h"
#include "AnyValue.h"
#include <sstream>
namespace Basic {

    ValueHolder::~ValueHolder() {
    }

    AnyValue::AnyValue() : holder_(nullptr) {
    }

    AnyValue::AnyValue(const AnyValue& other)
        : holder_(other.holder_ ? other.holder_->clone() : nullptr) {
    }

    AnyValue::AnyValue(const char* var)
        : holder_(new Holder<std::string>(var)) {
    }

    AnyValue& AnyValue::operator=(AnyValue& other) {
        if (this->holder_)
            delete this->holder_;
        if (other.holder_)
            this->holder_ = other.holder_->clone();
        return *this;
    }

    bool AnyValue::isString() const {
        return this->holder_ ? this->holder_->isString() : false;
    }

    bool AnyValue::isNumber() const {
        return this->holder_ ? this->holder_->isNumber() : false;
    }

    std::string AnyValue::toString() const {
        std::stringstream ret;
        if (this->holder_) {
            const auto& id = this->holder_->type();
            if (id == typeid(u8)) {
                ret << get<u8>();
            } else if (id == typeid(u16)) {
                ret << get<u16>();
            } else if (id == typeid(u32)) {
                ret << get<u32>();
            } else if (id == typeid(u64)) {
                ret << get<u64>();
            } else if (id == typeid(s8)) {
                ret << get<s8>();
            } else if (id == typeid(s16)) {
                ret << get<s16>();
            } else if (id == typeid(s32)) {
                ret << get<s32>();
            } else if (id == typeid(s64)) {
                ret << get<s64>();
            } else if (id == typeid(bool)) {
                ret << get<bool>();
            } else if (id == typeid(double)) {
                ret << get<double>();
            } else if (id == typeid(float)) {
                ret << get<float>();
            } else if (id == typeid(string)) {
                ret << get<string>();
            } else {
                assert(false && "Non Implement Type!"&&id.name());
            }
        }
        return ret.str();
    }

    AnyValue::~AnyValue() {
        delete holder_;
    }
}
