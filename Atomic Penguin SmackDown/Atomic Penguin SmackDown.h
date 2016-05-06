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
#include "Atomic Penguin SmackDown/GameInterface.h"


class Game : public DxWrapper
{
public:
   Game ();
   ~Game ();
   
   void loadLevel ( unsigned int index );
   void loadNextLevel ();
   void loadPrevLevel ();

//WINDOW
protected:
   LRESULT onCommand ( WPARAM wParam, LPARAM lParam );
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
   unsigned int                myGameIndex;
   std::vector<GameInterface*> myGameInterfaces;
   GameInterface*              myCurrentGameInterface;
   tstring                     myGameTitle;
   D3DCOLOR                    bgColor;

};

#endif //_GAME_H_