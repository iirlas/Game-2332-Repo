#pragma once

#if !defined(_GAME_H_)
#define _GAME_H_

#include "Utilities/Logger.h"
#include "DxWrapper/DxTexture.h"
#include "DxWrapper/DxWrapper.h"
#include "DxWrapper/DxText.h"
#include "Resource.h"
#include <Windows.h>
#include "Atomic Penguin SmackDown/CollisionManager.h"
#include "Atomic Penguin SmackDown/TiledBackground.h"
#include "Atomic Penguin SmackDown/Player.h"
#include "Atomic Penguin SmackDown/GameUI.h"
class Game : public DxWrapper
{
public:
   Game ();
   ~Game ();
//WINDOW
protected:
   LPCTSTR resourceMenu (){return MAKEINTRESOURCE(IDC_ATOMICPENGUINSMACKDOWN); }//MAKEINTRESOURCE() creates a string ID from a resourcce ID
   bool initPlayers ( const tstring& configFilename );
   void resolveCollisions ();
   bool gameInit ();
   void gameRun ();
   void gameExit ();
   int resourceIconID () { return IDI_ATOMICPENGUINSMACKDOWN; }
   int resourceIconSmallID () { return IDI_SMALL; }
   int startTransWidth ()  { return 880; }
   int startTransHeight()  { return 640; }

private:
   int                  myPlayerIndex;
   D3DCOLOR             bgColor;
   std::vector<Player*> myPlayers;
   tstring              myGameTitle;
   TiledBackground      myLevelBgnds;
   RECT                 myBgRect;
   CollisionManager     myCollisionManager;

   GameUI              myGameUI;

};

#endif //_GAME_H_