#if !defined(_POINT_H_)
#define _POINT_H_
#include <windows.h>
class Point
{
public:
    Point ( );
    Point ( const Point& other ); 
    Point ( const POINT& other );  
    Point ( LONG x, LONG y );
    ~Point ( );

    operator POINT& ( );
    LPPOINT operator& ( );
    Point& operator() ( LONG x, LONG y );
    Point& operator= ( const Point& other );
    Point& operator= ( const POINT& other );

    inline LONG x ( ) const 
    {
        return myPoint.x;
    }

    inline LONG y ( ) const
    {
        return myPoint.y;
    }
    
    LONG x ( LONG value );
    LONG y ( LONG value );

private:
    POINT myPoint;
};

#endif //_POINT_H_