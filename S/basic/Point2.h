#pragma once
class Point2 {
  public:
    Point2 ( void );
    ~Point2 ( void );
    Point2 ( long x, long y );
    long mX;
    long mY;
};

inline Point2::Point2 ( void )
    : mX ( 0 )
    , mY ( 0 ) {
}
inline Point2::Point2 ( long x, long y )
    : mX ( x )
    , mY ( y ) {

}


inline Point2::~Point2 ( void ) {
}