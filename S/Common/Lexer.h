#pragma once
#include "uString.h"
#include "HashMap.h"
namespace Basic {

template<typename CH>
class Token {
  public:
    int mType;
    const CH* mStr;
  public:
    Token();
};
enum eCharState {
    eCharStateNone,
    eCharStateVar,
};
template<typename CH>
class Lexer {
  public:
    typedef Token<CH> MyToken;
    static const int ErrorTokenType = -1;
  public:
    Lexer(void);
    ~Lexer(void);
    bool parser(const CH* content);
    void bind(int type, const CH* str);
    void next(MyToken& token);
    inline bool isEnd();
    inline bool isTokenTypeValid() const;
  protected:
    int getTokenType(const CH* str) const;
    inline CH getNextChar();

    HashMap<std::basic_string<CH>, int> mTokenMap;
    Buffer mBuffer;
    std::basic_string<CH> mCurString;
    u32 mLine;
    u32 mCursor;
    eCharState mState;
};

template<typename CH>
Lexer<CH>::~Lexer(void) {
}

template<typename CH>
int Lexer<CH>::getTokenType(const CH* str) const {
    int type = -1;
    mTokenMap.Get(str, type);
    return type;
}

template<typename CH>
inline bool Lexer<CH>::isEnd() {
    return mCursor >= mBuffer.capacity();
}

template<typename CH>
void Lexer<CH>::next(MyToken& token) {
    mCurString.clear();
    while (!isEnd()) {
        CH c = getNextChar();

        switch (c) {
        case '\n': {
            mLine++;
        }
        case ' ':
        case '\t':
        case ',':
        case ':':
        case '&':
        case ';':
        case '#':
        case '{':
        case '}':
        case '(':
        case ')': {
            if (mState == eCharStateVar) {
                token.mStr = mCurString.c_str();
                token.mType = getTokenType(token.mStr);
                mState = eCharStateNone;
                //OutputDebugStringA ( "\n" );
                //OutputDebugStringA ( token.mStr );
                return;
            }
        }
        break;
        default: {
            mCurString.append(1, c);
            mState = eCharStateVar;
        }
        break;
        }
    }
}

template<typename CH>
CH Lexer<CH>::getNextChar() {
    assert(mCursor < mBuffer.capacity());
    mCursor++;
    return mBuffer.get<CH>(mCursor);
}
template<typename CH>
Lexer<CH>::Lexer(void) {
    mCursor = 0;
    mLine = 1;
    mState = eCharStateVar;
    mBuffer.setElementByteCount(sizeof(CH));
}

template<typename CH>
void Lexer<CH>::bind(int type, const CH* str) {
    assert(!mTokenMap.findkey(str));
    mTokenMap.Insert(str, type);
}

template<typename CH>
bool Lexer<CH>::parser(const CH* content) {
    mCursor = 0;
    assert(content);
    u32 len = dStrLen(content);
    mBuffer.reallocateByElementCount(len + 1);
    mBuffer.copyFrom((void*)content);
    return true;
}

template<typename CH>
Token<CH>::Token()
    : mType(Lexer<CH>::ErrorTokenType)
    , mStr(nullptr) {
}
typedef Token<char> CXCharToken;
typedef Token<wchar_t> CXWCharToken;

typedef Lexer<char> CXCharLexer;
typedef Lexer<wchar_t> CXWCharLexer;
}
