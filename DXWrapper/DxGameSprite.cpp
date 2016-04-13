#include "stdafx.h"
#include <cassert>
#include "Utilities/PathUtilities.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/DxGameSprite.h"
#include "DxWrapper/DxAssetManager.h"

//=======================================================================
DxGameSprite::DxGameSprite ( )
:myRotation(0), isCollidable(true), myVisible(true), isDestroyable(true), myCenter( 0, 0 ), 
myVelocity( 0, 0, 0 ), myLastVelocity( 0, 0, 0 ), myAccel( 0, 0, 0 ), 
myLastAccel( 0, 0, 0 ),myScale( 1, 1 ), myPosition( 0, 0, 0 ), myLastPosition ( 0, 0, 0 )
{

}

//=======================================================================
DxGameSprite::~DxGameSprite( )
{
	destroy();
}

//=======================================================================
void DxGameSprite::shutdown()
{

}

//=======================================================================
//make create that takes in width, height, and x+y positions
bool DxGameSprite::create( const tstring& animationName, D3DCOLOR transcolor )
{
	//create animation here
   myAnimation = DxAssetManager::getInstance().getAnimationCopy( animationName, 0, transcolor );

	myCollisionArea.top  = (long)myPosition.y;
	myCollisionArea.bottom = (long)myCollisionArea.top + getHeight();
	myCollisionArea.left = (long)myPosition.x;
	myCollisionArea.right = (long)myCollisionArea.left + getWidth();

 	return true;
}

//=======================================================================
//make create that takes in width, height, and x+y positions
bool DxGameSprite::create( DxTexture* texture, D3DCOLOR transcolor )
{
	//create animation here

   if ( !myAnimation.init( texture, 0 ) )
   {
      return false;
   }

	myCollisionArea.top  = (long)myPosition.y;
	myCollisionArea.bottom = (long)myCollisionArea.top + getHeight();
	myCollisionArea.left = (long)myPosition.x;
	myCollisionArea.right = (long)myCollisionArea.left + getWidth();

 	return true;
}

//=======================================================================
void DxGameSprite::destroy ( )
{
   myAnimation.shutdown();
   myCollisionArea.set( 0, 0, 0, 0 );
}


//=======================================================================
bool DxGameSprite::changeAnimation( DxAnimation& newAnimation )
{
   myAnimation = newAnimation;
   return true;
}

//=======================================================================
void DxGameSprite::transform ( float x, float y, D3DXVECTOR2 center, float rotation, D3DXVECTOR2 scale, D3DCOLOR color )
{
	this->setXPosition( x );
	this->setYPosition( y );
	myCenter = center;
	myRotation = rotation;
	myScale = scale;
	myColor = color;
}

//=======================================================================
void DxGameSprite::setPosition ( float x, float y )
{
   setXPosition( x );
   setYPosition( y );
}
//=======================================================================
void DxGameSprite::setXPosition ( float value )
{
	//set XPOS
	myPosition.x = value;

	//update collision Area to new XPOS
   myCollisionArea.x( (long)myPosition.x );

}

//=======================================================================
void DxGameSprite::setYPosition ( float value )
{
	//set YPOS
	myPosition.y = value;

	//update Collision Area to new YPOS
   myCollisionArea.y( (long)myPosition.y );
}

//===========================================================================
void DxGameSprite::setScale ( float scaleX, float scaleY )
{
   myScale.x = scaleX;
   myScale.y = scaleY;
}
//===========================================================================
void DxGameSprite::draw (IDXSPRITE spriteObj, D3DCOLOR color)
{
	if ( isVisible() )
	{
      myAnimation.drawFrame ( spriteObj, &myPosition, &myScale, 
						      myRotation, &myCenter,  color );
	}
}

//=======================================================================

void DxGameSprite::setXVel (float xV)
{
	myVelocity.x = xV;
}

//=======================================================================

void DxGameSprite::setYVel (float yV)
{
	myVelocity.y = yV;
}

//=======================================================================

void DxGameSprite::evaluateCenter ()
{
   myCenter = D3DXVECTOR2( ( myPosition.x + ( getWidth() / 2 ) ), myPosition.y + ( ( getHeight() / 2 ) ) );
}



//=======================================================================

void DxGameSprite::setLastXVel ( float xV )
{
	myLastVelocity.x = xV;
}

//=======================================================================

void DxGameSprite::setLastYVel ( float yV )
{
	myLastVelocity.y = yV;
}

//=======================================================================

void DxGameSprite::update()
{
	myLastPosition = myPosition;

	// Velocity Updates

	// Position Updates
	myVelocity     += myAccel;
	myPosition     += myVelocity;

	// update collision area
   myCollisionArea.x( (long)myPosition.x );
   myCollisionArea.y( (long)myPosition.y );

   myAnimation.update();

}

//=======================================================================
bool DxGameSprite::collidesWith ( const DxGameSprite& other )
{
   return myCollisionArea.collidesWith( other.myCollisionArea );
}

//=======================================================================
bool DxGameSprite::radialCollidesWith ( const DxGameSprite& other  )
{
   D3DXVECTOR2 centerOne, centerTwo;
   double radiusOne, radiusTwo;


   //Get the radius for the first sprite using the longest dimension
   //    because wouldn't want to have it collide with you and do nothing
   //    just because the sprite is skinny or fat or short or tall
   if( getWidth() > getHeight() )
      radiusOne = getWidth() / 2;
   else
      radiusOne = getHeight() / 2;

   centerOne.x = getXPosition() + (float)radiusOne;
   centerOne.y = getYPosition() + (float)radiusOne;

   if( other.getWidth() > other.getHeight() )
      radiusTwo = other.getWidth() / 2.0;
   else
      radiusTwo = other.getHeight() / 2.0;

   centerTwo.x = other.getXPosition() + (float)radiusTwo;
   centerTwo.y = other.getYPosition() + (float)radiusTwo;

   double deltaX = centerOne.x - centerTwo.x;
   double deltaY = centerTwo.y - centerOne.y;
   double distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));


   return (distance < radiusOne + radiusTwo);

   //other.getHeight() - centerTwo.y;
   //other.getWidth() - centerTwo.x;

   ////Gives center but need radius
   //evaluateCenter();
   //centerOne = getCenter();

   //Gives center but need radius
   //other.evaluateCenter();
   //centerTwo = other.getCenter();


   //Calculate distance


}

//=======================================================================

void DxGameSprite::toggleVisible ()
{
   myVisible = !myVisible;
}

//=======================================================================
void DxGameSprite::setCollisionArea (RECT collisionArea)
{
	myCollisionArea = collisionArea;
}