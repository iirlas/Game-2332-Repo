#pragma once

#if !defined(_GAMERUN_H_)
#define _GAMERUN_H_

#include <vector>
#include "Utilities/ConfigParser.h"
#include "DxWrapper/DxCommon.h"
#include "Atomic Penguin SmackDown/GameUI.h"
#include "Atomic Penguin SmackDown/Player.h"
#include "Atomic Penguin SmackDown/GameInterface.h"

class GameRun : public GameInterface
{
public:
   GameRun ();
   ~GameRun ();

   bool init ( Game* window );
   void run ( Game* window );
   void reset ( Game* window ) ;
   void shutdown ( Game* window );

protected:
   bool initPlayers ( const tstring& configFilename, Game* window);
   void resolveCollisions ();

private:
   bool                 hasPlayerAttacked;
   int                  myRoundCount;
   int                  myRoundCountSinceAttack;
   int                  myPlayerIndex;
   std::vector<Player*> myPlayers;
   std::vector<GameUI*> myGUIs;
   TiledBackground      myLevelBgnds;
   CollisionManager     myCollisionManager;
   DxText               myRoundText;
   DxText               myMoveText;
};

#endif //_GAMERUN_H_