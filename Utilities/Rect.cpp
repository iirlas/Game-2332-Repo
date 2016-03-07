#include "Utilities/Rect.h"

//=======================================================================
Rect::Rect ( )
{
    myRect.left = 
        myRect.top = 
        myRect.right = 
        myRect.bottom = 0;
}

//=======================================================================
Rect::Rect ( const Rect& other )
    :myRect(other.myRect)
{
    normalize( );
}

//=======================================================================
Rect::Rect ( const RECT& other )
    :myRect(other)
{
    normalize( );
}

//=======================================================================
Rect::Rect ( LONG left, LONG top, LONG right, LONG bottom )
{
   set( left, top, right, bottom );
}

//=======================================================================
Rect::Rect ( POINT topLeft, LONG width, LONG height )
{
   set( topLeft, width, height );
}

//=======================================================================
Rect::~Rect ( )
{
}

//=======================================================================
Rect::operator RECT& ( )
{
    return myRect;
}

//=======================================================================
LPRECT Rect::operator& ( )
{
    return &myRect;
}

//=======================================================================
Rect& Rect::operator= ( const Rect &other )
{
    myRect = other.myRect;
    return *this;
}

//=======================================================================
Rect& Rect::operator= ( const RECT &other )
{
    myRect = other;
    return *this;
}

//=======================================================================
LONG Rect::area ( ) const
{
    return (width( ) * height( ));
}

//=======================================================================
bool Rect::collidesWith ( const RECT& other ) const
{
    Rect intersect;
    return collidesWith( other, intersect );
}

//=======================================================================
bool Rect::collidesWith ( const RECT& other, Rect& intersect ) const
{
    intersect.myRect.left =    max( myRect.left, other.left );
    intersect.myRect.top =     max( myRect.top, other.top );
    intersect.myRect.right =   min( myRect.right, other.right );
    intersect.myRect.bottom =  min( myRect.bottom, other.bottom );

    if ( intersect.myRect.left < intersect.myRect.right &&
         intersect.myRect.top < intersect.myRect.bottom )
    {
        intersect.normalize( );
        return true;
    }

    intersect;
    return false;
}

//=======================================================================
bool Rect::contains ( const POINT& point ) const
{
    return contains( point.x, point.y );
}

//=======================================================================
bool Rect::contains ( LONG x, LONG y ) const
{
    return ( x >= myRect.left && x < myRect.right && 
             y >= myRect.top && y < myRect.bottom );
}

//=======================================================================
void Rect::normalize ( )
{
    if ( myRect.left > myRect.right )
    {
        myRect.left ^= myRect.right;
        myRect.right^= myRect.left;
        myRect.left ^= myRect.right;
    }
    if ( myRect.top > myRect.bottom )
    {
        myRect.top   ^= myRect.bottom;
        myRect.bottom^= myRect.top;
        myRect.top   ^= myRect.bottom;
    }
}

//=======================================================================
void Rect::set ( LONG left, LONG top, LONG right, LONG bottom )
{
   myRect.left = left;
   myRect.top = top;
   myRect.right = right;
   myRect.bottom = bottom;
   normalize( );
}

//=======================================================================
void Rect::set ( POINT topLeft, LONG width, LONG height )
{
   myRect.left = topLeft.x;
   myRect.top = topLeft.y;
   myRect.right = topLeft.x + width;
   myRect.bottom = topLeft.y + height;
   normalize( );
}

//=======================================================================
LONG Rect::x ( LONG value, bool relative )
{
    myRect.right += (relative)? (value):(value - myRect.left);
    myRect.left = (relative)? (myRect.left + value):(value);
    normalize( );
    return myRect.left;
}

//=======================================================================
LONG Rect::y ( LONG value, bool relative )
{
    myRect.bottom += (relative)? (value):(value - myRect.top);
    myRect.top = (relative)? (myRect.top + value):(value);
    normalize( );
    return myRect.top;
}

//=======================================================================
LONG Rect::width ( LONG value )
{
    myRect.right = myRect.left + value;
    normalize( );
    return (myRect.right - myRect.left);
}

//=======================================================================
LONG Rect::height ( LONG value )
{    
    myRect.bottom = myRect.top + value;
    normalize( );
    return (myRect.bottom - myRect.top);
}

//=======================================================================
LONG Rect::left ( LONG value )
{
    myRect.left = value;
    normalize( );
    return myRect.left;
}

//=======================================================================
LONG Rect::top ( LONG value )
{
    myRect.top = value;
    normalize( );
    return myRect.top;
}

//=======================================================================
LONG Rect::right ( LONG value )
{
    myRect.right = value;
    normalize( );
    return myRect.right;
}

//=======================================================================
LONG Rect::bottom ( LONG value )
{
    myRect.bottom = value;
    normalize( );    
    return myRect.bottom;
}

