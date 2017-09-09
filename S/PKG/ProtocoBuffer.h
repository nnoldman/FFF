#ifndef PKG_h__
#define PKG_h__

#include "Default.h"

#pragma pack(push)
#pragma pack(1)

#define zeroArray(arr) memset(arr,0,sizeof(arr))
#define zeroThis(p) memset(p,0,sizeof(*p))


#pragma warning(disable:4200)

struct ProtocoBuffer
{
    u32 length;
    u32 opcode;
    char data[0];
    ProtocoBuffer()
    {
    }

    template<typename T>
    auto_ptr<T> parse(bool errorIfEmpty = true)
    {
        if (data == nullptr)
            return auto_ptr<T>(nullptr);
        T* ret = new T();
        if (ret->ParsePartialFromArray(data, length))
        {
            return auto_ptr<T>(ret);
        }
        else
        {
            if (errorIfEmpty)
            {
                assert(false);
                std::cerr << "ProtocolBuffer Parse Error" << std::endl;
            }
        }
        return auto_ptr<T>(nullptr);
    }
};

#pragma pack(pop)
#endif // PKG_h__
