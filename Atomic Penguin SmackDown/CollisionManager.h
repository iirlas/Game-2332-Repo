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
   CollisionManager();
   ~CollisionManager();
   void init();
   void update();
   void shutdown();
   
   bool worldCollisions( DxGameSprite sprite, TiledBackground&  LevelRef, unsigned int* index = NULL );
   bool spriteCollsions( DxGameSprite sprite1, DxGameSprite sprite2 );

private:
   bool loadAnimation();

private:
   bool myFirstTimeFlag;
   DxAnimation myGrassAnim;
   DxAnimation myBoomBrickAnim;
   int myDoorIndex;


};

#endif 
