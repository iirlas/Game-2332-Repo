#if !defined(_TESTAPP_H_)
#define _TESTAPP_H_

#include "Utilities\Logger.h"
#include "DxWrapper\DxWrapper.h"
class Game : public DxWrapper
{
public:
   Game ();
   ~Game ();

protected:
   bool gameInit ( );
   void gameRun ( );
   void gameExit ();
private:
   D3DCOLOR bgColor;
};

#endif //_TESTAPP_H_