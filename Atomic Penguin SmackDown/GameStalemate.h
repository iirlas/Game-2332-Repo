#pragma once

#if !defined(_GAMESTALEMATE_H_)
#define _GAMESTALEMATE_

#include "DxWrapper/DxGameSprite.h"

class GameStalemate
{
public:
   bool init ( Game* window);
   void run ( Game* window );
   //void stop( Game* window);
   void shutdown( Game* window);

private:
   DxGameSprite  staleEnd;







};
#endif