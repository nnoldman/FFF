#ifndef CharBuffer_h__
#define CharBuffer_h__
#include "Buffer.h"

namespace Basic {
template<int N>
class CharBuffer : public Buffer {
  public:
    CharBuffer()
        : Buffer(N) {
    }
    CharBuffer& operator=(const char* str) {
        __super::operator =(str);
        return *this;
    }
    inline bool operator==(const char* str) {
        return strcmp(c_str(), str) == 0;
    }
    inline bool operator!=(const char* str) {
        return strcmp(c_str(), str) != 0;
    }
};
}

#endif // CharBuffer_h__
