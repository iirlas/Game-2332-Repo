#include "Utilities/Point.h"
#include "Utilities/Rect.h"

//=======================================================================
Rect::Rect ( )
{
   left = 
      top = 
      right = 
      bottom = 0;
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
Rect::~Rect ()
{
}

//=======================================================================
LONG Rect::area () const
{
   return (width() * height());
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
   return !!IntersectRect( &intersect, this, &other );
}

//=======================================================================
bool Rect::contains ( const POINT& point ) const
{
   return !!PtInRect( this, point );
}

//=======================================================================
bool Rect::contains ( LONG x, LONG y ) const
{
   Point point( x, y );
   return contains( point );
}

//=======================================================================
void Rect::normalize ( )
{
   if ( left > right )
   {
      left ^= right;
      right^= left;
      left ^= right;
   }
   if ( top > bottom )
   {
      top   ^= bottom;
      bottom^= top;
      top   ^= bottom;
   }
}

//=======================================================================
void Rect::set ( LONG left, LONG top, LONG right, LONG bottom )
{
   this->left = left;
   this->top = top;
   this->right = right;
   this->bottom = bottom;
   normalize( );
}

//=======================================================================
void Rect::set ( POINT topLeft, LONG width, LONG height )
{
   left = topLeft.x;
   top = topLeft.y;
   right = topLeft.x + width;
   bottom = topLeft.y + height;
   normalize( );
}

//=======================================================================
LONG Rect::x ( LONG value, bool relative )
{
   right += (relative)? (value):(value - left);
   left = (relative)? (left + value):(value);
   normalize( );
   return left;
}

//=======================================================================
LONG Rect::y ( LONG value, bool relative )
{
   bottom += (relative)? (value):(value - top);
   top = (relative)? (top + value):(value);
   normalize( );
   return top;
}

//=======================================================================
LONG Rect::width ( LONG value )
{
   right = left + value;
   normalize( );
   return (right - left);
}

//=======================================================================
LONG Rect::height ( LONG value )
{    
   bottom = top + value;
   normalize( );
   return (bottom - top);
}
