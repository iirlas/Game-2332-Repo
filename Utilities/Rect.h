#if !defined(_RECT_H_)
#define _RECT_H_
#include <windows.h>

class Rect
{
public:
   Rect ();
   Rect ( const Rect& other ); 
   Rect ( const RECT& other );  
   Rect ( LONG left, LONG top, LONG right, LONG bottom );
   Rect ( POINT topleft, LONG width, LONG height );
   ~Rect ();

   operator RECT& ();
   LPRECT operator& ();

   Rect& operator= ( const Rect& other );
   Rect& operator= ( const RECT& other );

   LONG area () const;
   bool collidesWith ( const RECT& other ) const;
   bool collidesWith ( const RECT& other, Rect& intersect ) const;
   bool contains ( const POINT& point ) const;
   bool contains ( LONG x, LONG y ) const;
   void normalize ();

   inline LONG x () const 
   {
      return myRect.left;
   }

   inline LONG y () const
   {
      return myRect.top;
   }

   inline LONG width () const
   {
      return (myRect.right - myRect.left);
   }    

   inline LONG height () const
   {
      return (myRect.bottom - myRect.top);
   }

   inline LONG left () const
   {
      return myRect.left;
   }

   inline LONG top () const
   {
      return myRect.top;
   }

   inline LONG right () const
   {
      return myRect.right;
   }

   inline LONG bottom () const
   {
      return myRect.bottom;
   }

   void set ( LONG left, LONG top, LONG right, LONG bottom );
   void set ( POINT topleft, LONG width, LONG height );
   LONG x ( LONG value, bool relative = false );
   LONG y ( LONG value, bool relative = false );
   LONG width ( LONG value );
   LONG height ( LONG value );
   LONG left ( LONG value );
   LONG top ( LONG value );
   LONG right ( LONG value );
   LONG bottom ( LONG value );

private:
   RECT myRect;
};
#endif //_RECT_H_