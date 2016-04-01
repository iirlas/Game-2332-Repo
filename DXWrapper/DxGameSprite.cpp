#include "stdafx.h"
#include <cassert>
#include "Utilities/PathUtilities.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/DxGameSprite.h"

//=======================================================================
DxGameSprite::DxGameSprite ( )
:myRotation(0)
{

}

//=======================================================================
DxGameSprite::~DxGameSprite( )
{
	destroy();
}


//=======================================================================
void DxGameSprite::init()
{

}


//=======================================================================
void DxGameSprite::shutdown()
{

}


//=======================================================================
bool DxGameSprite::create ( IDXDEVICE device, const tstring& filename, D3DCOLOR transcolor, POINT* srcSize )
{
	bool result = myTexture.create( device, filename, transcolor, srcSize );
   myColor =  D3DCOLOR_XRGB( 255, 255, 255 );

	//create animation here

   tstring name(filename);
   PathUtilities::pathStripPath( name );
   DxAnimationFrame frame;
   frame.texture = &myTexture;
   frame.rect.set( 0, 0, (srcSize ? srcSize->x : myTexture.width()), ( srcSize ? srcSize->y : myTexture.height()) );
   myAnimation.addFrame( frame );



	myWidth = myTexture.width();
	myHeight = myTexture.height();
	myVisible = true;
	myVelocity.x = myVelocity.y = myVelocity.z = 0;
	myLastVelocity.x = myLastVelocity.y = myLastVelocity.z = 0;
	myAccel.x = myAccel.y = myAccel.z = 0;
	myPosition.x = myPosition.y = myPosition.z = 0;
	myLastPosition.x = myLastPosition.y = myLastPosition.z = 0;

	myCenter.x = myCenter.y = 0;
	myScale.x = myScale.y = 1;
	myRotation = 0;

	myCollisionArea.top  = (long)myPosition.y;
	myCollisionArea.bottom = (long)myCollisionArea.top + myHeight;
	myCollisionArea.left = (long)myPosition.x;
	myCollisionArea.right = (long)myCollisionArea.left + myWidth;

	return result;
}

//=======================================================================
//make create that takes in width, height, and x+y positions
bool DxGameSprite::create( IDXDEVICE device,
						         const tstring& animationName )
{
   myColor =  D3DCOLOR_XRGB( 255, 255, 255 );

	//create animation here
	bool b = myAnimation.init( device, animationName, 10, myColor );

   int  width = 80;
   int  height= 108;
   //TODO: myTexture.create( device,  myAnimation.width(), myAnimation.height() );
	// b = myTexture.create( device,  width, height );
   
	myWidth = width;
	myHeight = height;

	myVisible = true;

	myVelocity.x = myVelocity.y = myVelocity.z = 0;
	myLastVelocity.x = myLastVelocity.y = myLastVelocity.z = 0;

	myAccel.x = myAccel.y = myAccel.z = 0;

	myPosition.x = myPosition.y = myPosition.z = 0;
	myLastPosition.x = myLastPosition.y = myLastPosition.z = 0;

	myCenter.x = myCenter.y = 0;
	myScale.x = myScale.y = 1;
	myRotation = 0;

	myCollisionArea.top  = (long)myPosition.y;
	myCollisionArea.bottom = (long)myCollisionArea.top + myHeight;
	myCollisionArea.left = (long)myPosition.x;
	myCollisionArea.right = (long)myCollisionArea.left + myWidth;

 	return true;
}


//=======================================================================
void DxGameSprite::destroy ( )
{
	myTexture.destroy();
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
	myCollisionArea.left =(long)myPosition.x;
	myCollisionArea.right =(long)myCollisionArea.left + myWidth;

}

//=======================================================================
void DxGameSprite::setYPosition ( float value )
{
	//set YPOS
	myPosition.y = value;

	//update Collision Area to new YPOS
	myCollisionArea.top  = (long)myPosition.y;
	myCollisionArea.bottom =(long) myCollisionArea.top + myHeight;
}

//=======================================================================
void DxGameSprite::draw ( IDXSPRITE spriteobj )
{
	//draw the sprite
	if(myVisible)
		myTexture.draw( spriteobj, &myPosition/*, &myScale, myRotation, &myCenter*/, myColor );
}

//=======================================================================

void DxGameSprite::draw(IDXSPRITE spriteobj, D3DCOLOR color)
{
	if(myVisible)
		myTexture.draw( spriteobj, &myPosition/*, &myScale, myRotation, &myCenter*/, color );

}

//===========================================================================
void DxGameSprite::drawAnim(IDXSPRITE spriteObj)
{
	if(myVisible)
		myAnimation.drawFrame ( spriteObj, &myPosition, &myScale, 
								  myRotation, &myCenter,  myColor );
}

//=======================================================================

void DxGameSprite::setXVel(float xV)
{
	myVelocity.x = xV;
}

//=======================================================================

void DxGameSprite::setYVel(float yV)
{
	myVelocity.y = yV;
}

//=======================================================================

void DxGameSprite::setLastXVel(float xV)
{
	myLastVelocity.x = xV;
}

//=======================================================================

void DxGameSprite::setLastYVel(float yV)
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
	myCollisionArea.top  = (long)myPosition.y;
	myCollisionArea.bottom = (long)myCollisionArea.top + myHeight;
	myCollisionArea.left = (long)myPosition.x;
	myCollisionArea.right = (long)myCollisionArea.left + myWidth;

   myAnimation.update();

}




void DxGameSprite::textureUpdate()
{
	myLastPosition = myPosition;

	// Velocity Updates
	myVelocity     += myAccel;
	// Position Updates
	myPosition     += myVelocity;

	// update collision area
	myCollisionArea.top  = (long)myPosition.y;
	myCollisionArea.bottom = (long)myCollisionArea.top + myHeight;
	myCollisionArea.left = (long)myPosition.x;
	myCollisionArea.right = (long)myCollisionArea.left + myWidth;

   //myTexture.update();

}

//=======================================================================

void DxGameSprite::toggleVisible()
{
	if(myVisible)
		myVisible = false;
	else
		myVisible = true;

}

//=======================================================================

void DxGameSprite::setCollisionArea(RECT collisionArea)
{
	myCollisionArea = collisionArea;
}