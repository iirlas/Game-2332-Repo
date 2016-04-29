#pragma once

#if !defined( _COLLISIONMANAGER_H_ )
#define _COLLISIONMANAGER_H_

#include "DxWrapper/DxWrapper.h"
#include "DxWrapper/DxGameSprite.h"
#include "DxWrapper/DxGameSprite.h"
#include "DxWrapper/DxImage.h"
#include "Atomic Penguin SmackDown/TiledBackground.h"

class CollisionManager
{
public:

   static bool worldCollisions( DxGameSprite sprite, TiledBackground&  LevelRef, unsigned int* index = NULL );
   static bool spriteCollsions( DxGameSprite sprite1, DxGameSprite sprite2 );

   CollisionManager() {};
   ~CollisionManager() {};
   
private:

private:
};

#endif 
