#ifndef uString_h__
#define uString_h__

#include "base.h"
#include "EncodingHelper.h"
#include "Reference.h"
#include <stdarg.h>
namespace Basic
{

class uString
{
public:
    typedef size_t size_type;
    typedef char* iterator;

    static const size_t npos = -1;
    uString(void);
    ~uString(void);
    uString(Encoding encoding, size_t cap = 0);
    /** @brief with default encoding **/
    uString(const char* str);
    uString(const wchar_t* str);
    //uString ( const uString& str, bool sharedata  );
    uString(const uString& str);

    Encoding encoding() const;
    void setEncoding(Encoding en);
    size_t length() const;
    size_t sizeOfByte() const;
    size_t capacity() const;
    bool empty() const;

    operator const char* ();

    uString utf8() const;
    uString ansi() const;

    /** @brief ucs2 **/
    uString unicode() const;
    uString utf16() const;
    uString ucs2() const;

    /** @brief must not unicode **/
    const char* c_str() const;
    /** @brief must unicode **/
    const wchar_t* c_strw() const;

    const char* data() const;
    const char* tail() const;

    void format(const char* fmt, ...);
    bool find_pos(const char* str);
    //-------------------------------------------------------------------------
    // utf8 and ansi find string is may be error by byte mode,so covert dst and
    // src all to unicode,then find it,but also it is lower effective.
    //-------------------------------------------------------------------------
    size_t find(const char* str) const;
    size_t find(const char c) const;
    size_t find(const wchar_t* str) const;
    size_t find(const wchar_t c) const;
    size_t find_last_of(char c, size_t start = npos) const;
    size_t find_last_of(wchar_t c, size_t start = npos) const;
    size_t find_last_of(const char* str, size_t start = npos) const;
    size_t find_last_of(const wchar_t* str, size_t start = npos) const;
    void clear();

    bool end_with(const char* str);
    bool end_withw(const wchar_t* str);

    uString& trim_leftw();
    uString& trim_rightw();
    uString& trim();
    uString& trimw();
public:
    /** @brief with default encoding **/
    uString& operator= (const char* str);
    uString& operator= (const wchar_t* str);
    uString& operator+= (char c);
    uString& operator+= (wchar_t c);
    uString& operator+= (const char* str);
    uString& operator+= (const wchar_t* str);

    uString operator+ (char c);
    uString operator+ (const char* str);
    uString operator+ (wchar_t c);
    uString operator+ (const wchar_t* str);

    uString operadd(const char* str);
    uString operadd(const wchar_t* str);

    uString& append(size_t cnt, char c);
    uString& append(const char* str);

    uString& append(size_t cnt, wchar_t c);
    uString& append(const wchar_t* str);

    bool operator== (const char* str);
    bool operator!= (const char* str);


    char at(size_t i) const
    {
        assert(i < mLengthOfByte);
        return mRef.pointer()[i];
    }
    wchar_t& atw(size_t i) const
    {
        assert(mEncoding == Encoding_Unicode && i < mLengthOfByte);
        return mRef.pointerw()[i];
    }
    char& operator[](size_t i)
    {
        assert(i < mLengthOfByte);
        return mRef.pointer()[i];
    }

    uString tolower() const;
public:
    iterator begin();
    iterator end();
    uString& insert(size_t where, size_t cnt, char c);
    uString& insert(size_t where, const char* str);
    uString substr(size_t start, size_t cnt = npos) const;
    uString& replace(const char* src, const char* dst);
public:
    template<typename StringArr>
    void split(const char delimiter, typename StringArr& arr)
    {
        uString ele;
        for (size_t i = 0; i < length(); ++i)
        {
            char c = at(i);
            if (c == delimiter)
            {
                arr.push_back(ele);
                ele.clear();
            }
            else
            {
                ele.append(1, c);
            }
        }
        if (!ele.empty())
            arr.push_back(ele);
    }
private:

    bool convertTo(Buffer& buffer, Encoding src, Encoding dst, const char* str, size_t len)
    {
        EncodingHelper::EncodingConverter convert = EncodingHelper::getConverter(src, dst);
        if (convert)
        {
            return convert(buffer, (const char*)str, len);
        }
        return false;
    }
    bool convertTo(Buffer& buffer, Encoding src, Encoding dst, const wchar_t* str, size_t len)
    {
        EncodingHelper::EncodingConverter convert = EncodingHelper::getConverter(src, dst);
        if (convert)
        {
            return convert(buffer, (const char*)str, len * 2);
        }
        return false;
    }
    void constructByType(const char* str, size_t len, Encoding src, Encoding dst)
    {
        assert(str);
        uStringBuffer stringbuffer;
        if (convertTo(stringbuffer.buffer(), src, dst, str, len))
        {
            mLengthOfByte = stringbuffer.buffer().size();
            mRef.reallocate(mLengthOfByte);
            stringbuffer.buffer().copyTo(mRef.pointer());
        }
        else
        {
            mLengthOfByte = len;
            dMemoryCopy(stringbuffer.buffer().getBuffer(), (void*)str, mLengthOfByte);
            mRef.reallocate(mLengthOfByte);
            dMemoryCopy(mRef.pointer(), (void*)str, mLengthOfByte);
        }
    }
    void constructByType(const wchar_t* str, Encoding dst)
    {
        assert(str);
        size_t len = wcslen(str);
        uStringBuffer stringbuffer;
        if (convertTo(stringbuffer.buffer(), Encoding_Unicode, dst, str, len))
        {
            mLengthOfByte = stringbuffer.buffer().size();
            mRef.reallocate(mLengthOfByte);
            stringbuffer.buffer().copyTo(mRef.pointer());
        }
        else
        {
            mLengthOfByte = len * 2;
            dMemoryCopy(stringbuffer.buffer().getBuffer(), (void*)str, mLengthOfByte);
            mRef.reallocate(mLengthOfByte);
            dMemoryCopy(mRef.pointer(), stringbuffer.buffer().getBuffer(), mLengthOfByte);
        }
    }
private:
    Reference mRef;
    Encoding mEncoding;
    size_t mLengthOfByte;
};
inline size_t uString::capacity() const
{
    return mRef.capcity();
}
inline bool uString::operator== (const char* str)
{
    return dStrEqual(c_str(), str);
}
inline bool uString::operator!= (const char* str)
{
    return !dStrEqual(c_str(), str);
}
inline size_t hash_value(const uString& str)
{
    return (std::_Hash_bytes((const unsigned char*)str.data(), str.sizeOfByte()));
}
inline bool operator < (const uString& lhs, const uString& rhs)
{
    size_t len0 = lhs.length();
    size_t len1 = rhs.length();
    if (len0 == len1)
        return memcmp(lhs.data(), rhs.data(), len0) < 0;
    else
        return len0 < len1;
}

inline uString::uString(const uString& str)
    : mEncoding(str.mEncoding)
{
    mRef.copyData(str.mRef);
    mLengthOfByte = str.sizeOfByte();
}

inline uString::uString(void)
    : mEncoding(Encoding_Default)
    , mLengthOfByte(0)
{
}
inline uString& uString::trimw()
{
    return trim_leftw().trim_rightw();
}
inline uString& uString::trim()
{
    if (mEncoding == Encoding_Unicode)
        return trimw();
    uString str = unicode().trimw();
    str.setEncoding(mEncoding);
    *this = str;
    return *this;
}
inline bool uString::empty() const
{
    return mLengthOfByte == 0;
}
inline uString::operator const char* ()
{
    return c_str();
}
inline const char* uString::c_str() const
{
    assert(mEncoding != Encoding_Unicode);
    return mRef.pointer();
}
inline const char* uString::data() const
{
    return mRef.pointer();
}
inline uString uString::operadd(const char* str)
{
    assert(str);
    size_t len = strlen(str);
    uString thiscopy(*this/*, false*/);

    uString tmp(mEncoding);
    tmp.constructByType(str, len, Encoding_Default, mEncoding);
    size_t dstlen = mLengthOfByte + tmp.sizeOfByte();

    if (this->capacity() >= dstlen)
    {
        dMemoryCopy((void*)(thiscopy.tail()), (void*)tmp.data(), tmp.sizeOfByte());
        return thiscopy;
    }
    else
    {
        thiscopy.mRef.reallocate(dstlen);
        assert(thiscopy.mRef.capcity() >= dstlen);
        dMemoryCopy((void*)(thiscopy.data()), (void*) this->data(), this->sizeOfByte());
        dMemoryCopy((void*)(thiscopy.data() + this->sizeOfByte()), (void*)tmp.data(), tmp.sizeOfByte());
        thiscopy.mLengthOfByte = dstlen;
    }
    return thiscopy;
}
inline uString uString::operator+ (const char* str)
{
    return operadd(str);
}
inline uString uString::operator+ (char c)
{
    char str[2] = { 0 };
    str[0] = c;
    return operadd(str);
}
inline uString uString::operator+ (wchar_t c)
{
    wchar_t str[2] = { 0 };
    str[0] = c;
    return operadd(str);
}
inline uString uString::operator+ (const wchar_t* str)
{
    return operadd(str);
}

inline uString uString::operadd(const wchar_t* str)
{
    assert(str);
    size_t len = wcslen(str);
    uString thiscopy(*this/*, false*/);

    uString tmp(mEncoding);
    tmp.constructByType(str, mEncoding);
    size_t dstlen = mLengthOfByte + tmp.sizeOfByte();

    if (this->capacity() >= dstlen)
    {
        dMemoryCopy((void*)(thiscopy.tail()), (void*)tmp.data(), tmp.sizeOfByte());
        return thiscopy;
    }
    else
    {
        thiscopy.mRef.reallocate(dstlen);
        assert(thiscopy.mRef.capcity() >= dstlen);
        dMemoryCopy((void*)(thiscopy.data()), (void*) this->data(), this->sizeOfByte());
        dMemoryCopy((void*)(thiscopy.data() + this->sizeOfByte()), (void*)tmp.data(), tmp.sizeOfByte());
        thiscopy.mLengthOfByte = dstlen;
    }
    return thiscopy;
}
inline uString& uString::operator+= (char c)
{
    return append(1, c);
}
inline uString& uString::operator+= (wchar_t c)
{
    return append(1, c);
}
inline uString& uString::operator+= (const wchar_t* str)
{
    return append(str);
}
inline uString& uString::operator+= (const char* str)
{
    return append(str);
}
inline const wchar_t* uString::c_strw() const
{
    assert(mEncoding == Encoding_Unicode);
    return mRef.pointerw();
}

inline uString::~uString(void)
{
}

inline Encoding uString::encoding() const
{
    return mEncoding;
}
inline uString::uString(const char* str)
    : mEncoding(Encoding_Default)
{
    constructByType(str, strlen(str), Encoding_Default, Encoding_Default);
}
inline uString::uString(Encoding encoding, size_t cap/* = 0*/)
    : mEncoding(encoding)
    , mLengthOfByte(0)
{
    if (cap > 0)
        mRef.reallocate(cap);
}

inline uString::uString(const wchar_t* str)
    : mEncoding(Encoding_Default)
{
    constructByType(str, mEncoding);
}

inline uString& uString::operator= (const char* str)
{
    constructByType(str, strlen(str), mEncoding, mEncoding);
    return *this;
}
inline uString& uString::operator= (const wchar_t* str)
{
    constructByType(str, mEncoding);
}

inline uString uString::unicode() const
{
    if (mEncoding == Encoding_Unicode)
    {
        return uString(*this);
    }
    if (!mRef.pointer())
        return uString(Encoding_Unicode);
    uString ucs2(Encoding_Unicode);
    ucs2.constructByType(mRef.pointer(), mLengthOfByte, mEncoding, Encoding_Unicode);
    return ucs2;
}
inline uString uString::substr(size_t start, size_t cnt /*= npos*/) const
{
    if (cnt == 0)
        return uString();
    assert(cnt > 0);
    assert(start <= length());
    if (cnt == npos)
        cnt = length() - start;
    assert(start + cnt <= length());
    size_t starti = mEncoding == Encoding_Unicode ? start * 2 : start;
    size_t len = mEncoding == Encoding_Unicode ? cnt * 2 : cnt;
    uString str(mEncoding, len);
    dMemoryCopy((void*)str.data(), (void*)(data() + starti), len);
    str.mLengthOfByte = len;
    return str;
}
inline std::wstring replaceT(const std::wstring& str, const std::wstring& src, const std::wstring& dest)
{
    std::wstring  ret;

    std::wstring::size_type pos_begin = 0;
    std::wstring::size_type pos = str.find(src);
    while (pos != std::wstring::npos)
    {
        ret.append(str.data() + pos_begin, pos - pos_begin);
        ret += dest;
        pos_begin = pos + 1;
        pos = str.find(src, pos_begin);
    }
    if (pos_begin < str.length())
    {
        ret.append(str.begin() + pos_begin, str.end());
    }
    return ret;
}
inline uString& uString::replace(const char* src, const char* dst)
{
    uString ssrc = src;
    uString sdst = dst;
    std::wstring thiscopy = unicode().c_strw();
    std::wstring ret = replaceT(this->unicode().c_strw(), ssrc.unicode().c_strw(), sdst.unicode().c_strw());
    constructByType(ret.c_str(), mEncoding);
    return *this;
}
inline uString& uString::insert(size_t where, const char* str)
{
    std::wstring thiscopy;
    if (mLengthOfByte > 0)
        thiscopy = unicode().c_strw();
    uString sdst = str;
    thiscopy.insert(where, sdst.unicode().c_strw());
    constructByType(thiscopy.c_str(), mEncoding);
    return *this;
}
inline uString& uString::insert(size_t where, size_t cnt, char c)
{
    std::string thiscopy = ansi().c_str();
    thiscopy.insert(where, cnt, c);
    constructByType(thiscopy.c_str(), thiscopy.length(), Encoding_Default, mEncoding);
    return *this;
}

inline void uString::setEncoding(Encoding en)
{
    if (mEncoding == en)
        return;
    if (mEncoding == Encoding_Unicode)
    {
        constructByType(mRef.pointerw(), en);
    }
    else
    {
        constructByType(mRef.pointer(), strlen(mRef.pointer()), mEncoding, en);
    }
    mEncoding = en;
}

inline void uString::format(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    uStringBuffer stringbuffer;
    Buffer& buffer = stringbuffer.buffer();
    vsnprintf_s(buffer.getBuffer(), buffer.length(), _TRUNCATE, fmt, ap);
    va_end(ap);
    size_t len = strlen(buffer.getBuffer());
    buffer.setSize(len);
    constructByType(buffer.getBuffer(), len, Encoding_Default, mEncoding);
}
inline size_t uString::find(const char* str) const
{
    uString src = unicode().c_strw();
    uString dst = str;
    return src.find(dst.unicode().c_strw());
}


inline size_t uString::find(const char c) const
{
    char str[2] = { 0 };
    str[0] = c;
    return find(str);
}
inline size_t uString::find_last_of(const wchar_t* str, size_t start /*= npos */) const
{
    std::wstring src = unicode().c_strw();
    return src.find_last_of(str, start);
}
inline size_t uString::find_last_of(const char* str, size_t start /*= npos */) const
{
    std::wstring src = unicode().c_strw();
    uString dst = str;
    return src.find_last_of(dst.unicode().c_strw(), start);
}
inline size_t uString::find_last_of(char c, size_t start /*= npos*/) const
{
    char str[2] = { 0 };
    str[0] = c;
    std::wstring src = unicode().c_strw();
    uString dst = str;
    return src.find_last_of(dst.unicode().c_strw(), start);
}
inline size_t uString::find_last_of(wchar_t c, size_t start /*= npos*/) const
{
    wchar_t str[2] = { 0 };
    str[0] = c;
    std::wstring src = unicode().c_strw();
    return src.find_last_of(str, start);
}
inline size_t uString::find(const wchar_t c) const
{
    wchar_t str[2] = { 0 };
    str[0] = c;
    return find(str);
}

inline size_t uString::find(const wchar_t* str) const
{
    std::wstring src = unicode().c_strw();
    return src.find(str);
}

inline uString uString::ansi() const
{
    if (mEncoding == Encoding_ANSI)
    {
        return uString(*this);
    }
    uString ansi(Encoding_ANSI);
    if (mEncoding == Encoding_Unicode)
    {
        ansi.constructByType(mRef.pointerw(), Encoding_ANSI);
    }
    else
    {
        ansi.constructByType(mRef.pointer(), strlen(mRef.pointer()), mEncoding, Encoding_ANSI);
    }
    return ansi;
}

inline uString uString::utf8() const
{
    if (mRef.pointer() == nullptr || mEncoding == Encoding_UTF8)
    {
        return uString(*this);
    }
    uString utf8(Encoding_UTF8);
    if (mEncoding == Encoding_Unicode)
    {
        utf8.constructByType(mRef.pointerw(), Encoding_UTF8);
    }
    else
    {
        utf8.constructByType(mRef.pointer(), strlen(mRef.pointer()), mEncoding, Encoding_UTF8);
    }
    return utf8;
}

inline void uString::clear()
{
    mLengthOfByte = 0;
    mRef.setzero();
}

inline size_t uString::length() const
{
    if (mEncoding == Encoding_Unicode)
        return mLengthOfByte / 2;
    return mLengthOfByte;
}
inline size_t uString::sizeOfByte() const
{
    return mLengthOfByte;
}

inline const char* uString::tail() const
{
    return data() + mLengthOfByte;
}

inline uString& uString::append(const char* str)
{
    assert(str);
    size_t len = strlen(str);

    uString tmp(mEncoding);
    tmp.constructByType(str, len, Encoding_Default, mEncoding);
    size_t dstlen = mLengthOfByte + tmp.sizeOfByte();

    if (this->capacity() >= dstlen + 1)
    {
        dMemoryCopy((void*)(tail()), (void*)tmp.data(), tmp.sizeOfByte());
        mLengthOfByte = dstlen;
        return *this;
    }
    else
    {
        uString thiscopy(*this/*, false*/);
        mRef.reallocate(dstlen);
        assert(mRef.capcity() >= dstlen);
        if (thiscopy.data())
            dMemoryCopy((void*)(data()), (void*)thiscopy.data(), mLengthOfByte);
        dMemoryCopy((void*)(tail()), (void*)tmp.data(), tmp.sizeOfByte());
        mLengthOfByte = dstlen;
    }
    return *this;
}
inline uString&  uString::append(size_t cnt, char c)
{
    if (cnt == 0 || c == '\0')
    {
        return *this;
    }
    uStringBuffer stringbuffer;
    Buffer& buffer = stringbuffer.buffer();
    buffer.setSize(cnt + 1);
    assert(cnt < buffer.capacity());
    memset(buffer.getBuffer(), c, cnt);
    buffer.set(cnt, '\0');
    append(buffer.getBuffer());
    return *this;
}

inline uString& uString::append(const wchar_t* str)
{
    assert(str);
    size_t len = wcslen(str);

    uString tmp(mEncoding);
    tmp.constructByType(str, mEncoding);
    size_t dstlen = mLengthOfByte + tmp.sizeOfByte();

    if (this->capacity() >= dstlen)
    {
        dMemoryCopy((void*)(tail()), (void*)tmp.data(), tmp.sizeOfByte());
        mLengthOfByte = dstlen;
        return *this;
    }
    else
    {
        uString thiscopy(*this/*, false*/);
        mRef.reallocate(dstlen);
        assert(mRef.capcity() >= dstlen);
        if (thiscopy.data())
            dMemoryCopy((void*)(data()), (void*)thiscopy.data(), mLengthOfByte);
        dMemoryCopy((void*)(tail()), (void*)tmp.data(), tmp.sizeOfByte());
    }
    return *this;
}

inline uString&  uString::append(size_t cnt, wchar_t c)
{
    if (cnt == 0 || c == L'\0')
    {
        return *this;
    }
    uStringBuffer stringbuffer;
    Buffer& buffer = stringbuffer.buffer();
    buffer.setSize((u32)(cnt * 2));
    assert(cnt < buffer.capacity());
    memset(buffer.getBuffer(), c, cnt * sizeof(wchar_t));
    buffer.set((u32)cnt, L'\0');
    append(buffer.getWChar());
    return *this;
}

inline uString& uString::trim_leftw()
{
    assert(mEncoding == Encoding_Unicode);
    wchar_t* _start = (wchar_t*)c_strw();
    for (; *_start != L'\0'; ++_start)
    {
        wchar_t& c = *_start;
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
            break;
    }
    constructByType(_start, mEncoding);
    return *this;
}

inline uString& uString::trim_rightw()
{
    int _end = 0;
    if (length() > 0)
    {
        _end = length() - 1;
        for (; _end >= 0; --_end)
        {
            wchar_t& c = atw(_end);
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
                break;
        }
    }

    if (0 <= _end)
    {
        constructByType(substr(0, _end + 1).c_strw(), mEncoding);
    }
    return *this;
}

inline bool uString::end_with(const char* str)
{
    if (str == nullptr)
        return false;
    if (length() == 0)
        return false;
    if (mEncoding != Encoding_Unicode)
    {
        return length() - 1 == find_last_of(str);
    }
    else
    {
        return ansi().end_with(str);
    }
}

inline bool uString::end_withw(const wchar_t* str)
{
    if (str == nullptr)
        return false;
    if (length() == 0)
        return false;
    if (mEncoding == Encoding_Unicode)
    {
        return length() - 1 == find_last_of(str);
    }
    else
    {
        return unicode().end_withw(str);
    }
}
}

#endif // uString_h__