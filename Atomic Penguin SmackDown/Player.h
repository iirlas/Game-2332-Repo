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
   Player () { myPenguinCount = 0; myPenguins = NULL; mySelectedPenguin = NULL; myPrevMoveTexture = NULL; myTurnIndex = 0; mySackCount = 0; }
   ~Player () { shutdown(); }

   bool init ( tstring playerConfigFile, int tileWidth, int tiltHeight );
   void update ( TiledBackground& tiledBackground );
   void draw ( IDXSPRITE spriteInterface );
   void shutdown ();

   void resolveCollisions ( TiledBackground& tiledBackground );

   const Penguin* selectedPenguin () { return mySelectedPenguin; }

private:
   unsigned int             mySackCount;
   unsigned int             myTurnIndex;
   unsigned int             myPenguinCount;
   Penguin*                 myPenguins;
   Penguin*                 mySelectedPenguin;
   CollisionManager         myCollisionManager;
   DxTexture*               myPrevMoveTexture;
   DxGameSprite             myCursor;
   std::vector<Movement>    myMovements;

};

#endif //_PLAYER_H_