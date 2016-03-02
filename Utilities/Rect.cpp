#include "Rect.h"

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
Rect::Rect ( LONG x, LONG y, LONG width, LONG height )
{
    (*this)( x, y, width, height );
}

//=======================================================================
Rect::Rect ( POINT topLeft, LONG width, LONG height )
{
    (*this)( topLeft.x, topLeft.y, width, height);
}


//=======================================================================
Rect::Rect ( POINT topLeft, POINT bottomRight )
{
    (*this)( topLeft, bottomRight );
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
Rect& Rect::operator() ( LONG x, LONG y, LONG width, LONG height )
{
    myRect.left = x;
    myRect.top = y;
    myRect.right = x + width;
    myRect.bottom = y + height;
    normalize( );
    return *this;
}


//=======================================================================
Rect& Rect::operator() ( POINT topLeft, POINT bottomRight )
{
    myRect.left = topLeft.x;
    myRect.top = topLeft.y;
    myRect.right = bottomRight.x;
    myRect.bottom = bottomRight.y;
    normalize( );
    return *this;
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

    intersect( 0, 0, 0, 0 );
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

