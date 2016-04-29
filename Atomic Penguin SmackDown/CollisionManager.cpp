#include "stdafx.h"
#include "Atomic Penguin SmackDown/CollisionManager.h"


CollisionManager::CollisionManager()
{
   myFirstTimeFlag = true;
}
//========================================================================================
//
CollisionManager::~CollisionManager(){}
//========================================================================================
//
void CollisionManager::init()
{ 
  loadAnimation();

}
//========================================================================================
//
bool CollisionManager::loadAnimation()
{
   if( myFirstTimeFlag )
   {
      myFirstTimeFlag = false;
      myGrassAnim = DxAssetManager::getInstance().getAnimationCopy( "GRASS", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myBoomBrickAnim = DxAssetManager::getInstance().getAnimationCopy( "BRICK-DESTROY", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
   }

   return true;
}
//========================================================================================
//
void CollisionManager::update(){}
//========================================================================================
//
void CollisionManager::shutdown(){}
//========================================================================================
//
bool CollisionManager::worldCollisions( DxGameSprite sprite, TiledBackground&  LevelRef, unsigned int* index )
{
   Rect collision = sprite.getCollisionArea();
   int indexTopLeft = ( (int)collision.left / 32 ) + 
                      ( (int)collision.top / 32 ) *  LevelRef.numColumns();

   int indexBottomLeft = ( (int)collision.left / 32 ) + 
                         ( (int)collision.bottom / 32 ) *
                         LevelRef.numColumns();

   int indexTopRight = ( (int)collision.right / 32 ) + 
                       ( (int)collision.top / 32 ) * LevelRef.numColumns();

   int indexBottomRight = ( (int)collision.right / 32 ) +
                          ( (int)collision.bottom / 32 ) * 
                          LevelRef.numColumns();

   if( ( sprite.collidesWith( LevelRef.mySpriteMap[indexTopLeft] )&&  
         LevelRef.mySpriteMap[indexTopLeft].collidable() ) )
   {
      if ( index )
      {
         *index = indexTopLeft;
      }
      return true;
   }
   else if ( ( sprite.collidesWith( LevelRef.mySpriteMap[indexBottomLeft] ) &&  
              LevelRef.mySpriteMap[indexBottomLeft].collidable() ) )
   {
      if ( index )
      {
         *index = indexBottomLeft;
      }
      return true;
   }
   else if( ( sprite.collidesWith( LevelRef.mySpriteMap[indexTopRight] ) &&  
            LevelRef.mySpriteMap[indexTopRight].collidable() ) )
   {
      if ( index )
      {
         *index = indexTopRight;
      }
      return true;
   }
   else if( ( sprite.collidesWith( LevelRef.mySpriteMap[indexBottomRight] ) &&  
             LevelRef.mySpriteMap[indexBottomRight].collidable() ) )
   {
      if ( index )
      {
         *index = indexBottomRight;
      }
      return true;
   }

   return false;
}

//========================================================================================
//
bool CollisionManager::spriteCollsions( DxGameSprite sprite1, DxGameSprite sprite2 )
{
   if( ( sprite1.collidesWith( sprite2 ) && sprite2.collidable() ) )
   {
      return true;
   }

   return false;
}