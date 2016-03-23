#pragma once

#if !defined(_DXGAMESPRITE_H_)
#define _DXGAMESPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities\NonCopyable.h"
#include "Utilities\TTypes.h"
#include "DxWrapper\DxTexture.h"
#include "DxWrapper\DxTypes.h"

class DxGameSprite
{
public:
	DxGameSprite ( void );
	~DxGameSprite ( void );

public:
	bool create ( IDXDEVICE device, const tstring& filename, D3DCOLOR transcolor, POINT* srcSize = NULL );
	void destroy ( void );

	void transform ( float x, float y, D3DXVECTOR2 center, float rotation, D3DXVECTOR2 scale, D3DCOLOR color );
	inline float getXPosition () const { return myPosition.x; }
	inline float getYPosition () const { return myPosition.y; }
	void setXPosition ( float value );
	void setYPosition ( float value );

	float getWidth(){return myWidth * myScale.x;}
	float getHeight(){return myHeight * myScale.y;}

	float getXVel(){return  myVelocity.x;}
	float getYVel(){return  myVelocity.y;}
	void setXVel(float xV);
	void setYVel(float yV);

	float getLastXVel(){return  myLastVelocity.x;}
	float getLastYVel(){return  myLastVelocity.y;}

	void setLastXVel(float xV);
	void setLastYVel(float yV);

	void draw ( IDXSPRITE spriteobj );
   void draw( IDXSPRITE spriteobj, D3DCOLOR color);

	void update();

	void toggleVisible();
	bool isVisible(){return myVisible;}

private:
	float          myRotation;
	D3DXVECTOR3    myPosition;
	D3DXVECTOR2    myScale;
	D3DXVECTOR2    myCenter;
	D3DCOLOR       myColor;
	DxTexture      myTexture;

	D3DXVECTOR3    myLastPosition;
	bool           myVisible;
	int            myWidth;
	int            myHeight;

	D3DXVECTOR3    myVelocity;
	D3DXVECTOR3    myLastVelocity;
	D3DXVECTOR3    myAccel;


};

#endif //_DXGAMESPRITE_H_