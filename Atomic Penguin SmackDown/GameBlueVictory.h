#pragma once

#if !defined(_GAMEBLUEVICTORY_H_)
#define _GAMEBLUEVICTORY_

#include "DxWrapper/DxGameSprite.h"

class GameBlueVictory
{
public:
   bool init ( Game* window);
   void run ( Game* window );
   //void stop( Game* window);
   void shutdown( Game* window);

private:
   DxGameSprite  blueVictory;







};
#endif