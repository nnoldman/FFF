#include "appbase.h"
#include "IObject.h"
IObject::IObject()
    :bit_flag_(0X10000000) {
}
IObject::~IObject() {
    assert(bit_flag_ == 0X10000000);
    bit_flag_ = 0X00000001;
}
