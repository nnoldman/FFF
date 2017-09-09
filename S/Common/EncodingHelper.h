#ifndef uEncodingHelper_h__
#define uEncodingHelper_h__
#include <xlocale>
#include "Buffer.h"
#include <stdlib.h>
#include "base.h"
#include "ObjectPool.h"
namespace Basic {

enum Encoding {
    Encoding_ANSI,
    Encoding_UTF8,
    Encoding_Unicode,
    Encoding_Count,
#ifdef UNICODE
    Encoding_Default = Encoding_Unicode,
#else
    Encoding_Default = Encoding_ANSI,
#endif
};
typedef bool ( *EncodixngConverter ) ( Buffer&,  const Char*, size_t );
class _LocatSetter {
  public:
    _LocatSetter() {
        ///此处有内存泄露？
        std::locale::global(std::locale(""));
    }
};
class uStringBuffer {
    static ObjectPool<Buffer>& getBufferPool() {
        static _LocatSetter setter;
        static ObjectPool<Buffer> bufferpool(4);
        return bufferpool;
    }
  public:
    static const int BufferSize = 1024 * 128;

    uStringBuffer()
        : _buffer(0) {
        _buffer = getBufferPool().acquireObject();
        if(_buffer->size() == 0)
            _buffer->reAllocate(BufferSize);
    }
    ~uStringBuffer() {
        _buffer->clear();
        getBufferPool().releaseObject(_buffer);
    }
    Buffer& buffer() {
        return *_buffer;
    }
  private:
    Basic::Buffer* _buffer;
};

class EncodingHelper {
  public:

    typedef bool ( *EncodingConverter ) ( Buffer&,  const Char*, size_t);

    //static bool convertAnsiToUnicode ( uBuffer& buffer, const  Char* data, size_t len );
    //static bool convertUtf8ToUnicode ( uBuffer& buffer, const  Char* data, size_t len );

    //static bool convertAnsiToUtf8 ( uBuffer& buffer, const  Char* data, size_t len );
    //static bool convertUnicodeToUtf8 ( uBuffer& buffer, const  Char* data, size_t len );

    //static bool convertUnicodeToAnsi ( uBuffer& buffer, const  Char* data, size_t len );
    //static bool convertUtf8ToAnsi ( uBuffer& buffer, const  Char* data, size_t len );



    static EncodingConverter getConverter ( Encoding src, Encoding dst ) {
        static const EncodingConverter helpers[Encoding_Count][Encoding_Count] = {
            {nullptr, convertAnsiToUtf8, convertAnsiToUnicode},
            {convertUtf8ToAnsi, nullptr, convertUtf8ToUnicode},
            {convertUnicodeToAnsi, convertUnicodeToUtf8, nullptr},
        };
        return helpers[src][dst];
    }
    static bool convertAnsiToUnicode (Buffer& buffer, const Char* data, size_t len ) {
        size_t sz = 0;
        buffer.zero();
        //errno_t error = mbstowcs_s ( &sz, ( wchar_t* ) buffer.getPointer(), len, data, len + 1 );
        errno_t error = mbstowcs_s ( &sz, ( wchar_t* ) buffer.getBuffer(), buffer.capacity() / sizeof ( wchar_t ), data, len );
        /** @brief tail is '\0' **/
        assert ( sz > 0 );
        len = ( sz - 1 ) * sizeof ( wchar_t );
        buffer.setSize ( len);
        return error == 0;
    }
    static inline size_t countOfUtf8Char ( char& c ) {
        size_t byteCnt = 1;
        static const size_t MaxByte = 6;
        static const unsigned char otcCnt[MaxByte - 1] = {0XFC, 0XF8, 0XF0, 0XE0, 0XC0};
        for ( size_t i = 0; i < MaxByte - 1; ++i ) {
            if ( ( otcCnt[i] & c ) == otcCnt[i] ) {
                byteCnt = MaxByte - i;
                break;
            }
        }
        return byteCnt;
    }

    static  bool utf8ToUnicode ( wchar_t* pOut, char *pText, OUT size_t& wcount ) {
        static const unsigned short a = 0X1000;
        static const bool littleendian = ( ( * ( ( ( char* ) &a ) + 1 ) ) == 0X10 );

        char* src = pText;
        char* temp = ( char* ) pOut;
        size_t j = 0;
        size_t i = 0;

        size_t h = 0;
        size_t l = 0;
        while ( *src != '\0' ) {
            size_t charCnt = countOfUtf8Char ( *src );
            h = littleendian ? j + 1 : j;
            l = littleendian ? j : j + 1;
            j += 2;
            switch ( charCnt ) {
            case 1: {
                temp[l] = src[i];
                temp[h] = 0;
            }
            break;
            case 2: {
                temp[l] = src[i];
                temp[h] = src[i + 1];
            }
            break;
            case 3: {
                temp[l] = ( ( src[i + 1] & 0x03 ) << 6 ) + ( src[i + 2] & 0x3F );
                temp[h] = ( ( src[i] & 0x0F ) << 4 ) | ( ( src[i + 1] >> 2 ) & 0x0F );
            }
            break;
            default:
                return false;
                break;
            }
            src += charCnt;
        }
        //temp[j++] = 0;
        //temp[j++] = 0;
        wcount = j / 2;
        return true;
    }
    static  size_t countOfUnicodeChar ( const wchar_t& c ) {
        if ( c > 0X07FF ) {
            return 3;
        } else if ( c > 0X007F ) {
            return 2;
        }
        return 1;
    }
    static  bool unicodeToUtf8 ( char* pOut, wchar_t* pText, OUT size_t& cCnt ) {
        static const unsigned short a = 0X1000;
        static const bool littleendian = ( ( * ( ( ( char* ) &a ) + 1 ) ) == 0X10 );
        wchar_t* src = pText;
        size_t j = 0;
        size_t i = 0;

        static const size_t h = littleendian ? 1 : 0;
        static const size_t l = littleendian ? 0 : 1;

        while ( *src != '\0' ) {
            size_t charCnt = countOfUnicodeChar ( *src );
            const wchar_t& unic = *src;
            switch ( charCnt ) {
            case 1: {
                pOut[i++]  = ( unic & 0x7F );
            }
            break;
            case 2: {
                pOut[i++]  = ( ( unic >> 6 ) & 0x1F ) | 0xC0;
                pOut[i++]  = ( unic & 0x3F ) | 0x80;
            }
            break;
            case 3: {
                pOut[i++]  = ( ( unic >> 12 ) & 0x0F ) | 0xE0;
                pOut[i++]  = ( ( unic >>  6 ) & 0x3F ) | 0x80;
                pOut[i++]  = ( unic & 0x3F ) | 0x80;
            }
            break;
            //ucs4
            //case 4:
            //{
            //    pOut[i++]  = ( ( unic >> 18 ) & 0x07 ) | 0xF0;
            //    pOut[i++]  = ( ( unic >> 12 ) & 0x3F ) | 0x80;
            //    pOut[i++]  = ( ( unic >>  6 ) & 0x3F ) | 0x80;
            //    pOut[i++]  = ( unic & 0x3F ) | 0x80;
            //}
            //break;
            //case 5:
            //{
            //    pOut[i++]  = ( ( unic >> 24 ) & 0x03 ) | 0xF8;
            //    pOut[i++]  = ( ( unic >> 18 ) & 0x3F ) | 0x80;
            //    pOut[i++]  = ( ( unic >> 12 ) & 0x3F ) | 0x80;
            //    pOut[i++]  = ( ( unic >>  6 ) & 0x3F ) | 0x80;
            //    pOut[i++]  = ( unic & 0x3F ) | 0x80;
            //}
            //break;
            //case 6:
            //{
            //    pOut[i++]  = ( ( unic >> 30 ) & 0x01 ) | 0xFC;
            //    pOut[i++]  = ( ( unic >> 24 ) & 0x3F ) | 0x80;
            //    pOut[i++]  = ( ( unic >> 18 ) & 0x3F ) | 0x80;
            //    pOut[i++]  = ( ( unic >> 12 ) & 0x3F ) | 0x80;
            //    pOut[i++]  = ( ( unic >>  6 ) & 0x3F ) | 0x80;
            //    pOut[i++]  = ( unic & 0x3F ) | 0x80;
            //}
            //break;
            default:
                return false;
                break;
            }
            src ++;
        }
        //pOut[i++] = '\0';
        cCnt = i;
        return true;
    }
    static  bool convertUtf8ToUnicode ( Buffer& buffer, const  Char* data, size_t len ) {
        size_t sz = 0;
        buffer.zero();
        bool res = utf8ToUnicode ( ( wchar_t* ) buffer.getBuffer(), (  char* ) data, sz );
        assert ( res );
        buffer.setSize ( sz * sizeof ( wchar_t ) );
        return res;
    }

    static  bool convertAnsiToUtf8 ( Buffer& buffer, const  Char* data, size_t len ) {
        uStringBuffer stringbuffer;
        bool res = convertAnsiToUnicode ( stringbuffer.buffer(), data, len );
        if ( !res ) {
            assert ( 0 );
            return false;
        }
        res = convertUnicodeToUtf8 ( buffer, stringbuffer.buffer().getBuffer(), stringbuffer.buffer().size() );

        return res;
    }
    static  bool convertUnicodeToUtf8 ( Buffer& buffer, const  Char* data, size_t len ) {
        size_t sz = 0;
        bool res = unicodeToUtf8 ( buffer.getBuffer(), (  wchar_t* ) data, sz );
        assert ( res );
        buffer.setSize ( sz * sizeof ( char ) );
        return true;
    }

    static  bool convertUnicodeToAnsi ( Buffer& buffer, const  Char* data, size_t len ) {
        size_t sz = 0;
        buffer.zero();
        errno_t error = wcstombs_s ( &sz, ( Char * ) buffer.getBuffer(), buffer.length(), ( const wchar_t* ) data,  buffer.length() );
        /** @brief tail is '\0' **/
        buffer.setSize ( sz - 1  );
        return error == 0;
    }
    static  bool convertUtf8ToAnsi ( Buffer& buffer, const  Char* data, size_t len ) {
        uStringBuffer stringbuffer;
        bool res = convertUtf8ToUnicode ( stringbuffer.buffer(), data, len );
        if ( !res ) {
            assert ( 0 );
            return false;
        }
        res = convertUnicodeToAnsi ( buffer, stringbuffer.buffer().getBuffer(), stringbuffer.buffer().size() );

        return res;
    }
};

}



#endif // uEncodingHelper_h__
