#pragma once

#if !defined(_GAMEMENU_H_)
#define _GAMEMENU_H_

#include <vector>
#include "Utilities/ConfigParser.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxText.h"
#include "Atomic Penguin SmackDown/GameUI.h"
#include "Atomic Penguin SmackDown/Player.h"
#include "Atomic Penguin SmackDown/GameInterface.h"

class GameMenu : public GameInterface
{
public:
   GameMenu ();
   ~GameMenu ();

   bool init ( Game* window );
   void run ( Game* window );
   void reset ( Game* window ) { myIndex = 0; }
   void shutdown ( Game* window );

protected:
   bool initPlayers ( const tstring& configFilename, Game* window);
   void resolveCollisions ();

private:
   int          myIndex;
   DxGameSprite mySplash;
   DxText       myStartText;
   DxText       myQuitText;
};

#endif //_GAMEMENU_H_