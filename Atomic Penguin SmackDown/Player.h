#pragma once

#if !defined(_PLAYER_H_)
#define _PLAYER_H_

#include <vector>
#include "Utilities/TTypes.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/DxGameSprite.h"
#include "DxWrapper/DxKeyboard.h"
#include "Atomic Penguin SmackDown/Penguin.h"

class Player
{
public:
   Player () { myPenguinCount = 0; myPenguins = NULL; mySelectedPenguin = NULL;}
   ~Player () {}

   bool init ( tstring playerConfigFile, int tileWidth, int tiltHeight );
   void update ();
   void draw ( IDXSPRITE spriteInterface );
   void shutdown ();

private:
   int                      myPenguinCount;
   Penguin*                 myPenguins;
   Penguin*                 mySelectedPenguin;
   DxGameSprite             myCursor;
   std::vector<D3DXVECTOR3> myMovements;

};

#endif //_PLAYER_H_