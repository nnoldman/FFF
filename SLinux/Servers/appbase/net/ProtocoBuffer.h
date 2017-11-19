#ifndef ProtocoBuffer_h__
#define ProtocoBuffer_h__
#include "../../basic/base.h"
struct ProtocoBuffer {
    u32 length;
    u32 opcode;
    char data[0];
    ProtocoBuffer();

    template<typename T>
    auto_ptr<T> parse(bool errorIfEmpty = true);
};

template<typename T>
std::auto_ptr<T> ProtocoBuffer::parse(bool errorIfEmpty /*= true*/) {
    if (data == nullptr)
        return auto_ptr<T>(nullptr);
    T* ret = new T();
    if (ret->ParsePartialFromArray(data, length)) {
        return auto_ptr<T>(ret);
    } else {
        if (errorIfEmpty) {
            assert(false);
            std::cerr << "ProtocolBuffer Parse Error" << std::endl;
            delete ret;
        }
    }
    return auto_ptr<T>(nullptr);
}

#endif // ProtocoBuffer_h__
