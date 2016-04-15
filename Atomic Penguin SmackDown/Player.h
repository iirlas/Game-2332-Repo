#pragma once

#if !defined(_PLAYER_H_)
#define _PLAYER_H_

#include "Utilities/TTypes.h"
#include "Atomic Penguin SmackDown/Penguin.h"

class Player
{
public:
   Player () { myPenguinCount = 0; myPenguins = NULL; }
   ~Player () {}

   bool init ( tstring playerConfigFile, int tileWidth, int tiltHeight );
   void update ();
   void draw ();
   void shutdown ();

private:
   int myPenguinCount;
   Penguin* myPenguins;
};

#endif //_PLAYER_H_