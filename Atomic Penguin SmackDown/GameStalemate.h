#pragma once

#if !defined(_GAMESTALEMATE_H_)
#define _GAMESTALEMATE_

#include "DxWrapper/DxGameSprite.h"
#include "Atomic Penguin SmackDown/GameInterface.h"

class GameStalemate : public GameInterface
{
public:
   bool init ( Game* window);
   void run ( Game* window );
   void reset ( Game* window ) {}
   void shutdown( Game* window);

private:
   DxGameSprite  staleEnd;
};
#endif