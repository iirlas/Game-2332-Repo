#include "stdafx.h"
#include <cassert>
#include "Utilities/PathUtilities.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/DxGameSprite.h"
#include "DxWrapper/DxAssetManager.h"

//=======================================================================
DxGameSprite::DxGameSprite ( )
:  myPosition( 0, 0, 0 ), myVelocity( 0, 0, 0 ), myAcceleration( 0, 0, 0 ), 
   myCenter( 0, 0 ), myScale( 1, 1 )
{
   myAnimation = NULL;
   myVisibility = true;
   myRotation = false;
}

//=======================================================================
DxGameSprite::~DxGameSprite( )
{
   destroy();
}

//=======================================================================
//make create that takes in width, height, and x+y positions
bool DxGameSprite::create( const tstring& animationName, float playSpeed, D3DCOLOR transcolor )
{
   //create animation here
   DxAnimation* animation = DxAssetManager::getInstance().getAnimation( animationName );
   if ( !animation )
   {
      return false;
   }

   myAnimation = new DxAnimation( *animation );
   myAnimation->speed( playSpeed );

   myCollisionArea.set( 0, 0, width(), height() );

   myAnimation->play();

   myVisibility = true;

   return true;
}

//=======================================================================
//make create that takes in width, height, and x+y positions
bool DxGameSprite::create( DxTexture* texture, D3DCOLOR transcolor )
{
   //create animation here
   myAnimation = new DxAnimation();
   if ( !myAnimation || !myAnimation->init( texture ) )
   {
      return false;
   }

   myVisibility = true;
   myCollisionArea.set( 0, 0, width(), height() );

   return true;
}



//=======================================================================
void DxGameSprite::destroy ( )
{
   if ( myAnimation )
   {
      myAnimation->shutdown();
      delete myAnimation;
      myAnimation = NULL;
   }
   myVisibility = false;
   scale( 1, 1 );
   rotation( 0 );
   center( 0, 0 );
   position( 0, 0 );
   velocity( 0, 0 );
   acceleration( 0, 0 );
   myCollisionArea.set( 0, 0, 0, 0 );
}

//=======================================================================
bool DxGameSprite::changeAnimation( const tstring& animationName, float playSpeed, D3DCOLOR color )
{
   DxAnimation* animation = DxAssetManager::getInstance().getAnimation( animationName );
   if ( animation )
   {
      myAnimation = new DxAnimation( *animation );
      myAnimation->speed( playSpeed );
      return true;
   }
   return false;
}

//=======================================================================
bool DxGameSprite::changeAnimation( DxAnimation& newAnimation )
{
   (*myAnimation) = newAnimation;
   return true;
}

//=======================================================================
DxAnimation& DxGameSprite::getAnimation( )
{
   return *myAnimation;
}

//===========================================================================
D3DXVECTOR3 DxGameSprite::position ( float x, float y )
{
   myPosition.x = x;
   myPosition.y = y;
   return myPosition;
}

//===========================================================================
D3DXVECTOR3 DxGameSprite::velocity ( float hSpeed, float vSpeed )
{
   myVelocity.x = hSpeed;
   myVelocity.y = vSpeed;
   return myVelocity;
}

//===========================================================================
D3DXVECTOR3 DxGameSprite::acceleration ( float hAccel, float vAccel )
{
   myAcceleration.x = hAccel;
   myAcceleration.y = vAccel;
   return myAcceleration;
}

//===========================================================================
D3DXVECTOR2 DxGameSprite::scale ( float scaleX, float scaleY )
{
   myScale.x = scaleX;
   myScale.y = scaleY;
   return myScale;
}

//===========================================================================
D3DXVECTOR2 DxGameSprite::center ( float x, float y )
{
   myCenter.x = x;
   myCenter.y = y;
   return myCenter;
}

//===========================================================================
int DxGameSprite::width () const
{
   if ( myAnimation )
      return (int)(myAnimation->width() * myScale.x);
   else
      return -1;
}

//===========================================================================
int DxGameSprite::height () const
{
   if ( myAnimation )
      return (int)(myAnimation->height() * myScale.y);
   else
      return -1;
}


//===========================================================================
void DxGameSprite::draw ( IDXSPRITE spriteObj, D3DCOLOR color )
{
   if ( myAnimation && visibility() )
   {
      myAnimation->drawFrame ( spriteObj, &myPosition, &myScale, 
                               myRotation, &myCenter,  color );
   }
}

//=======================================================================
void DxGameSprite::update()
{
   // Update Position
   myVelocity += myAcceleration;
   myPosition += myVelocity;

   // Update Animation
   if ( myAnimation )
   {
      myAnimation->update();
   }
}


//=======================================================================
Rect DxGameSprite::collisionArea ( int x, int y, int width, int height )
{
   myCollisionArea.set( x, y, x + width, y + height );
   return myCollisionArea;
}

//=======================================================================
bool DxGameSprite::collidesWith ( const DxGameSprite& other )
{
   Rect col = myCollisionArea;
   col.left  += (LONG)myPosition.x;
   col.right += (LONG)myPosition.x;
   col.top  += (LONG)myPosition.y;
   col.bottom  += (LONG)myPosition.y;

   return col.collidesWith( other.myCollisionArea );
}

//=======================================================================
bool DxGameSprite::contains ( float x, float y )
{
   Rect col = myCollisionArea;
   col.left  += (LONG)myPosition.x;
   col.right += (LONG)myPosition.x;
   col.top  += (LONG)myPosition.y;
   col.bottom  += (LONG)myPosition.y;

   return col.contains( (LONG)x, (LONG)y );
}

//=======================================================================
void DxGameSprite::resetCollisionArea ( )
{
   myCollisionArea.set( 0, 0, width(), height() );
}