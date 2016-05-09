#pragma once

#if !defined(_DXGAMESPRITE_H_)
#define _DXGAMESPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities/NonCopyable.h"
#include "Utilities/TTypes.h"
#include "Utilities/Rect.h"
#include "Utilities/Point.h"
#include "DxWrapper/DxTexture.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/DxAnimation.h"

class DxGameSprite
{
public:
	DxGameSprite ( void );
	~DxGameSprite ( void );

public:

	void update ();

	bool create ( const tstring& animationName, float playSpeed = 0, D3DCOLOR transcolor = 0 );
	bool create ( DxTexture* texture, D3DCOLOR transcolor = 0 );
	void destroy ( void );

   bool changeAnimation ( const tstring& animationName, float playSpeed = 0, D3DCOLOR excludeColor = 0 );
   bool changeAnimation ( DxAnimation& newAnimation );
   DxAnimation& getAnimation ();

   //position
   inline D3DXVECTOR3 position () const { return myPosition; }
   inline D3DXVECTOR3 position ( const D3DXVECTOR3& position ) { return (myPosition = position); }
   D3DXVECTOR3 position ( float x, float y );

	inline float x () const { return myPosition.x; }
   inline float x ( float x ) { return (myPosition.x = x); }

	inline float y () const { return myPosition.y; }
	inline float y ( float y ) { return (myPosition.y = y); }

   inline D3DXVECTOR3 velocity () const { return myVelocity; }
   inline D3DXVECTOR3 velocity ( const D3DXVECTOR3& velocity ) { return (myVelocity = velocity); }
   D3DXVECTOR3 velocity ( float hSpeed, float vSpeed );
   
   inline float hSpeed () const { return myVelocity.x; }
   float hSpeed ( float speed ) { return (myVelocity.x = speed); }

   inline float vSpeed () const { return myVelocity.y; }
   float vSpeed ( float speed ) { return (myVelocity.y = speed); }

   inline D3DXVECTOR3 acceleration () const { return myAcceleration; }
   inline D3DXVECTOR3 acceleration ( const D3DXVECTOR3& acceleration ) { return (myAcceleration = acceleration); }
   D3DXVECTOR3 acceleration ( float hAccel, float vAccel );

   inline float hAccel () const { return myAcceleration.x; }
   float hAccel ( float acceleration ) { return (myAcceleration.x = acceleration); }

   inline float vAccel () const { return myAcceleration.y; }
   float vAccel ( float acceleration ) { return (myAcceleration.y = acceleration); }


   //drawing
   inline float rotation () const { return myRotation; }
   float rotation ( float rotation ) { return (myRotation = rotation); }

   inline D3DXVECTOR2 scale () { return myScale; }
   inline D3DXVECTOR2 scale ( D3DXVECTOR2 scale ) { return (myScale = scale); }
	D3DXVECTOR2 scale ( float scaleX, float scaleY );

   inline D3DXVECTOR2 center () const { return myCenter; }
   inline D3DXVECTOR2 center ( D3DXVECTOR2 center ) { return (myCenter = center); }
   D3DXVECTOR2 center ( float x, float y );

   inline int width () const; 
   inline int height () const;

   void draw( IDXSPRITE spriteobj, D3DCOLOR color = D3DCOLOR_XRGB( 255, 255, 255) );

   inline bool visibility () const { return myVisibility; }
   inline bool visibility ( bool visibility ) { return (myVisibility = visibility); }
   
   bool isValid ()  { return !!myAnimation; }

   //collision
	inline Rect collisionArea () const { return myCollisionArea; }
   inline Rect collisionArea ( const Rect& collisionArea ) { return (myCollisionArea = collisionArea); }
   Rect collisionArea ( int x, int y, int width, int height );
   void resetCollisionArea ();

   bool collidesWith ( const DxGameSprite& other ); 
   bool contains ( float x, float y );


private:
	D3DXVECTOR3  myPosition;
	D3DXVECTOR3  myVelocity;
	D3DXVECTOR3  myAcceleration;

	float        myRotation;
	D3DXVECTOR2  myScale;
	D3DXVECTOR2  myCenter;

	bool         myVisibility;

	Rect		    myCollisionArea;

	DxAnimation* myAnimation;


};

#endif //_DXGAMESPRITE_H_