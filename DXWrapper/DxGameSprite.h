#pragma once

#if !defined(_DXGAMESPRITE_H_)
#define _DXGAMESPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities/NonCopyable.h"
#include "Utilities/TTypes.h"
#include "DxWrapper/DxTexture.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/DxAnimation.h"

class DxGameSprite
{
public:
	DxGameSprite ( void );
	~DxGameSprite ( void );

public:

	void update();

	void shutdown();

	bool create ( const tstring& animationName, float speed = 0, D3DCOLOR transcolor = 0 );
	bool create( DxTexture* texture, D3DCOLOR transcolor = 0 );
	void destroy ( void );
   
   //Different types of changeAnimations:
   //pass in animation
   //pass in animation name
   //...
   //pass in group of animations ????

   //MUST have working animation copy constructor/assignment operator
   bool changeAnimation( const tstring& animationName, float speed, D3DCOLOR excludeColor = 0 );
   bool changeAnimation( DxAnimation& newAnimation );
   DxAnimation& getAnimation( );

	void transform ( float x, float y, D3DXVECTOR2 center, float rotation, D3DXVECTOR2 scale, D3DCOLOR excludeColor );
	inline float getXPosition ( ) const { return myPosition.x; }
	inline float getYPosition ( ) const { return myPosition.y; }
	void setPosition ( float x, float y );
	void setXPosition ( float value );
	void setYPosition ( float value );
   void setScale( float scaleX, float scaleY );

   int getWidth() const {return (int)(myAnimation.width() * myScale.x);}
	int getHeight() const {return (int)(myAnimation.height() * myScale.y);}

	float getXVel(){return  myVelocity.x;}
	float getYVel(){return  myVelocity.y;}
	void setXVel(float xV);
	void setYVel(float yV);

   void evaluateCenter();
   D3DXVECTOR2 center ( D3DXVECTOR2 center ) { return (myCenter = center); }
   D3DXVECTOR2 center () const { return myCenter; }


	float getLastXVel(){return  myLastVelocity.x;}
	float getLastYVel(){return  myLastVelocity.y;}

	void setLastXVel(float xV);
	void setLastYVel(float yV);

	RECT getCollisionArea(){return myCollisionArea;}
	void setCollisionArea(RECT collisionArea);

   void draw( IDXSPRITE spriteobj, D3DCOLOR color = D3DCOLOR_XRGB( 255, 255, 255) );
   
   bool collidable ( bool flag ) { return (isCollidable = flag); }
   bool collidable () const { return isCollidable; } 
   bool collidesWith ( const DxGameSprite& other );
   bool setDestroyable ( bool flag ){ return (isDestroyable = flag); }
   bool getDestroyable() const { return isDestroyable; }
   bool radialCollidesWith ( const DxGameSprite& otherSprite  );
   void toggleVisible();
   bool isVisible(){return myVisible;}
   
   
private:

	D3DXVECTOR3    myPosition;
	D3DXVECTOR3    myLastPosition;
	D3DXVECTOR3    myVelocity;
	D3DXVECTOR3    myLastVelocity;
	D3DXVECTOR3    myAccel;
    D3DXVECTOR3    myLastAccel;

	float          myRotation;
	D3DXVECTOR2    myScale;
	D3DXVECTOR2    myCenter;
	D3DCOLOR       myColor;    //WHAT COLOR IS THIS???

	bool           myVisible;
   bool           isCollidable;
   bool           isDestroyable;

	Rect		   myCollisionArea;

	//////////////////////////
	DxAnimation    myAnimation;
	//DxAnimation    myAnimations[10];       //TODO: fix this const size.


};

#endif //_DXGAMESPRITE_H_