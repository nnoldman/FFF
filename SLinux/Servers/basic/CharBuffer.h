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
        inline bool operator==(const char* str) {
            return strcmp(c_str(), str) == 0;
        }
        inline bool operator!=(const char* str) {
            return strcmp(c_str(), str) != 0;
        }
        inline void addString(const char* str) {
            assert(str);
            assert(elementWidth() == 1);
            size_t len = strlen(str);
            size_t cnt = len + 1;
            if (cnt > capacity())
                reallocate(cnt);
            zero();
            setElementCount(cnt);
            dMemoryCopy(getBuffer(), (void*)str, len);
        }
        inline void setString(const char* str) {
            this->clear();
            addString(str);
        }
        inline CharBuffer& operator=(const char* str) {
            this->clear();
            addString(str);
            return *this;
        }
    };
}

#endif // CharBuffer_h__
