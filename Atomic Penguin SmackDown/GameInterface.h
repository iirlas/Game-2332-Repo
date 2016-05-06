#pragma once

#if !defined(_GAMEINTERFACE_H_)
#define _GAMEINTERFACE_H_

#include "DxWrapper/DxWrapper.h"

class Game;

class GameInterface
{
public:
   enum State { NONE, INIT, RUN, RESET, SHUTDOWN };

   GameInterface () { myState = INIT; }
   virtual ~GameInterface () {}

   virtual bool init ( Game* window ) = 0;
   virtual void run ( Game* window ) = 0;
   virtual void reset ( Game* window ) = 0;
   virtual void shutdown ( Game* window ) = 0;

   State state () { return myState; }
   State state ( State state ) { return (myState = state); }

protected:
   State myState; // to enum
};


#endif //_GAMEINTERFACE_H_