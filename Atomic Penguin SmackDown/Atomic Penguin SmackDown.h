#pragma once

#if !defined(_GAME_H_)
#define _GAME_H_

#include "Utilities/Logger.h"
#include "DxWrapper/DxTexture.h"
#include "DxWrapper/DxWrapper.h"
#include "Resource.h"
#include <Windows.h>
#include "Atomic Penguin SmackDown/TiledBackground.h"
#include "Atomic Penguin SmackDown/Player.h"

class Game : public DxWrapper
{
public:
   Game ();
   ~Game ();
//WINDOW
protected:
   LPCTSTR resourceMenu (){return MAKEINTRESOURCE(IDC_ATOMICPENGUINSMACKDOWN); }//MAKEINTRESOURCE() creates a string ID from a resourcce ID
   bool gameInit ();
   void gameRun ();
   void gameExit ();

   int startTransWidth ()  { return 960; }
   int startTransHeight()  { return 960; }

private:
   D3DCOLOR        bgColor;
   Player          myPlayer;
   tstring         myGameTitle;
   TiledBackground myLevelBgnds;
   RECT            myBgRect;
};

#endif //_GAME_H_