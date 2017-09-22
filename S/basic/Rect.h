#pragma once
#include "Point2.h"
class Rect {
  public:
    Rect ( void );
    ~Rect ( void );
    Rect ( long x, long y, long w, long h );
    bool operator== ( const Rect& rhs ) const;
    bool operator!= ( const Rect& rhs ) const;
    Rect& operator= ( const Rect& rhs );
    long mX;
    long mY;
    long mW;
    long mH;

    Point2 center() const;
    bool contain ( const Point2& pt ) const;
    bool contain ( long x, long y ) const;
    long right() const;
    long bottom() const;
    long area() const;
    bool isOverlaps ( const Rect& rc ) const;
    void offset ( long x, long y );
    void correct();
    void clamp ( const Rect& rc );
    void scaleX ( double scale, long xRef );
    void scaleY ( double scale, long yRef );
    void scale ( double scale, long xref, long yref );
};


inline Rect::~Rect ( void ) {
}

inline bool Rect::isOverlaps ( const Rect& rc ) const {
    long x0 = dMax ( mX, rc.mX );
    long y0 = dMax ( mY, rc.mY );
    long x1 = dMin ( right(), rc.right() );
    long y1 = dMin ( bottom(), rc.bottom() );

    return x0 < x1 && y0 < y1;
}

inline long Rect::right() const {
    return mX + mW;
}

inline long Rect::bottom() const {
    return mY + mH;
}

inline long Rect::area() const {
    return mW * mH;
}

inline Rect::Rect() {
    mX = 0;
    mY = 0;
    mW = 1;
    mH = 1;
}
inline Rect::Rect ( long x, long y, long w, long h ) {
    mX = x;
    mY = y;
    mW = w;
    mH = h;
}

inline bool Rect::contain ( long x, long y ) const {
    return x >= mX && x <= right() && y >= mY && y <= bottom();
}

inline bool Rect::contain ( const Point2& pt ) const {
    return contain ( pt.mX, pt.mY );
}

inline bool Rect::operator== ( const Rect& rhs ) const {
    return mX == rhs.mX && mY == rhs.mY && mW == rhs.mW && mH == rhs.mH;
}

inline bool Rect::operator!= ( const Rect& rhs ) const {
    if ( mX != rhs.mX )
        return true;
    if ( mY != rhs.mY )
        return true;
    if ( mW != rhs.mW )
        return true;
    if ( mH != rhs.mH )
        return true;
    return false;
}

inline Point2 Rect::center() const {
    Point2 pt;
    pt.mX = mX + mW / 2;
    pt.mY = mY + mH / 2;
    return pt;
}

inline void Rect::offset ( long x, long y ) {
    mX += x;
    mY += y;
}

inline Rect& Rect::operator= ( const Rect& rhs ) {
    mX = rhs.mX;
    mY = rhs.mY;
    mW = rhs.mW;
    mH = rhs.mH;
    return *this;
}

inline void Rect::correct() {
    if ( mW < 0 ) {
        mX += mW;
        mW = -mW;
    }
    if ( mH < 0 ) {
        mY += mH;
        mH = -mH;
    }
}

inline void Rect::clamp ( const Rect& rc ) {
    Rect tmp ( rc );
    tmp.correct();
    this->correct();
    long r = right(), b = bottom();
    mX = dClamp ( mX, rc.mX, rc.right() );
    mY = dClamp ( mY, rc.mY, rc.bottom() );
    r = dClamp ( r, rc.mX, rc.right() );
    b = dClamp ( b, rc.mY, rc.bottom() );
    mW = r - mX;
    mH = b - mY;
}


inline void Rect::scaleY ( double scale, long yRef ) {
    mY = dScale ( mY, yRef, scale );
    mH *= scale;
}

inline void Rect::scaleX ( double scale, long xRef ) {
    mX = dScale ( mX, xRef, scale );
    mW *= scale;
}

inline void Rect::scale ( double scale, long xref, long yref ) {
    scaleX ( scale, xref );
    scaleY ( scale, yref );
}
