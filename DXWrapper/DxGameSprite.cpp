#include "stdafx.h"
#include <cassert>
#include "DXWrapper/DxCommon.h"
#include "DXWrapper/DxTypes.h"
#include "DXWrapper/DxGameSprite.h"

//=======================================================================
DxGameSprite::DxGameSprite ()
:myRotation(0)
{

}

//=======================================================================
DxGameSprite::~DxGameSprite()
{
	destroy();
}

//=======================================================================
bool DxGameSprite::create ( IDXDEVICE device, const tstring& filename, D3DCOLOR transcolor, POINT* srcSize )
{
	bool result = myTexture.create( device, filename, transcolor, srcSize );

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


	return result;
}

//=======================================================================
void DxGameSprite::destroy ()
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
void DxGameSprite::setXPosition ( float value )
{
	myPosition.x = value;
}

//=======================================================================
void DxGameSprite::setYPosition ( float value )
{
	myPosition.y = value;
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
		// Velocity Updates
	myVelocity += myAccel;

	// Position Updates
	myLastPosition = myPosition;
	myPosition += myVelocity;

}

//=======================================================================

void DxGameSprite::toggleVisible()
{
	if(myVisible)
		myVisible = false;
	else
		myVisible = true;

}

