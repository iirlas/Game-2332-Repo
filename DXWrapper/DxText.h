#pragma once

#if !defined(_DXTEXT_H_)
#define _DXTEXT_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities/NonCopyable.h"
#include "Utilities/TTypes.h"
#include "Utilities/Rect.h"
#include "Utilities/Point.h"
#include "DxWrapper/DxTexture.h"
#include "DxWrapper/DxTypes.h"

class DxText
{
public:
	DxText ( void );
	~DxText ( void );

public:

   bool create( IDXFONT fontObj, tstring inputString, int xPixPos, int yPixPos, int width, int height, D3DCOLOR color = D3DCOLOR_XRGB( 0, 0, 0 ) );   //whatever's needed for the DrawText method
   bool update();
   bool destroy();

   bool draw( IDXSPRITE spriteObj );

   void setText( tstring newString );
   void setText ( int number );
   void setText ( float number );

   void setColor ( D3DCOLOR color );

   void setPosition ( float x, float y );
   void setXPosition ( float value );
   void setYPosition ( float value );

   void setScale( float scaleX, float scaleY );

   void clear();


private:


private:
   IDXFONT        myFont;
   tstring        myString;
   D3DCOLOR       myColor;
   D3DXVECTOR3    myPosition;
   D3DXVECTOR3    myScale;
   int            myWidth;
   int            myHeight;
   Rect           myRect;

};

#endif //_DXGAMESPRITE_H_