#if !defined(_TESTAPP_H_)
#define _TESTAPP_H_

#include "Utilities\Logger.h"
#include "DxWrapper\DxWrapper.h"
#include "Resource.h"
#include <Windows.h>
class Game : public DxWrapper
{
public:
   Game ();
   ~Game ();
//WINDOW
protected:
   LPCTSTR resourceMenu (){return MAKEINTRESOURCE(IDR_MENU1);}//MAKEINTRESOURCE() creates a string ID from a resourcce ID
   bool gameInit ();
   void gameRun ();
   void gameExit ();
private:
   D3DCOLOR bgColor;
};

#endif //_TESTAPP_H_