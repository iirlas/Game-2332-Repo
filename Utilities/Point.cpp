#include "Utilities/Point.h"

//=======================================================================
Point::Point ()
{
    myPoint.x = myPoint.y = 0;
}

//=======================================================================
Point::Point ( const Point& other )
{
    myPoint = other.myPoint;
}

//=======================================================================
Point::Point ( const POINT& other )
{
    myPoint = other;
}

//=======================================================================
Point::Point ( LONG x, LONG y )
{
    set( x, y );
}

//=======================================================================
Point::~Point ()
{
}

//=======================================================================
Point::operator POINT& ()
{
    return myPoint;
}

//=======================================================================
LPPOINT Point::operator& ()
{
    return &myPoint;
}

//=======================================================================
Point& Point::operator= ( const Point& other )
{
    myPoint = other.myPoint;
    return *this;
}

//=======================================================================
Point& Point::operator= ( const POINT& other )
{
    myPoint = other;
    return *this;
}

//=======================================================================
void Point::set( LONG x, LONG y )
{
    myPoint.x = x;
    myPoint.y = y;
}

//=======================================================================
LONG Point::x ( LONG value )
{
    return (myPoint.x = value);
}

//=======================================================================
LONG Point::y ( LONG value )
{
    return (myPoint.y = value);
}
