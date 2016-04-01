#pragma once

#if !defined(_GAME_H_)
#define _GAME_H_

#include "Utilities/Logger.h"
#include "DxWrapper/DxTexture.h"
#include "DxWrapper/DxWrapper.h"
#include "Resource.h"
#include <Windows.h>
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
private:
   DxTexture* myHulkPenguin;
   D3DCOLOR bgColor;
};

#endif //_GAME_H_