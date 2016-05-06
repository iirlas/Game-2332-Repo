#pragma once

#if !defined(_PLAYER_H_)
#define _PLAYER_H_

#include <vector>
#include "Utilities/TTypes.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/DxGameSprite.h"
#include "DxWrapper/DxKeyboard.h"
#include "Atomic Penguin SmackDown/CollisionManager.h"
#include "Atomic Penguin SmackDown/TiledBackground.h"
#include "Atomic Penguin SmackDown/Penguin.h"

struct Movement
{
   Penguin::Direction direction;
   D3DXVECTOR3 position;
};

class Player
{
public:
   Player () 
   { 
      mySelectedPenguin = NULL; myPrevMoveTexture = NULL; 
      myTurnIndex = 0; mySackCount = 0; myMaxMoves = 0; myMoveCount = 0;
      myStartDirection = Penguin::Direction::NONE;
      isAttacking = false;
   }
   ~Player () { shutdown(); }

   bool init ( tstring playerConfigFile, int tileWidth, int tiltHeight );
   void update ( TiledBackground& tiledBackground );
   void draw ( IDXSPRITE spriteInterface );
   void shutdown ();

   inline Penguin* at ( unsigned int index )
   {
      if ( index < myPenguins.size() )
      {
         return myPenguins[index];
      }
      return NULL;
   }

   void resolveCollisions ( TiledBackground& tiledBackground );
   bool penguinCollision ( int column, int row );
   bool canMoveSelected ();
   bool penguinIsAlive ();
   bool canMove ();
   void moveSelectedPenguinTo ( int horz, int vert );
   void clearMoves();
   bool attackPenguin( float x, float y, int damage );

   unsigned int maxMoves () { return myMaxMoves; }
   unsigned int moveCount () { return myMoveCount; }
   unsigned int penguinCount () { return myPenguins.size(); }
   unsigned int turnIndex () { return myTurnIndex; }
   Penguin* selectedPenguin () { return mySelectedPenguin; }
   bool attacking () { return isAttacking; } 
   void toggleAttacking () { isAttacking = !isAttacking; }
   void deselectPenguin () { mySelectedPenguin = NULL; }

private:
   void getSelectedPenguin ();

private:
   bool                     isAttacking;
   unsigned int             myMoveCount;
   unsigned int             myMaxMoves;
   unsigned int             mySackCount;
   unsigned int             myTurnIndex;
   std::vector<Penguin*>    myPenguins;
   std::map<Penguin*,bool>  myPenguinMoveFlag;
   Penguin*                 mySelectedPenguin;
   Penguin::Direction       myStartDirection;
   CollisionManager         myCollisionManager;
   DxTexture*               myPrevMoveTexture;
   DxGameSprite             myCursor;
   std::vector<Movement>    myMovements;

};

#endif //_PLAYER_H_