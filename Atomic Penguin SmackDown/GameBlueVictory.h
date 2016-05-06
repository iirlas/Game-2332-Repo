#pragma once

#if !defined(_GAMEBLUEVICTORY_H_)
#define _GAMEBLUEVICTORY_

#include "DxWrapper/DxGameSprite.h"
#include "Atomic Penguin SmackDown/GameInterface.h"

class GameBlueVictory : public GameInterface
{
public:
   bool init ( Game* window);
   void run ( Game* window );
   void reset ( Game* window ) {}
   void shutdown( Game* window);

private:
   DxGameSprite  blueVictory;

};
#endif