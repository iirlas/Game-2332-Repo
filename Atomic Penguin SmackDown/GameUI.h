#pragma once

#if !defined(_GAMEUI_H_)
#define _GAMEUI_H_

#include <vector>
#include "Utilities/NonCopyable.h"
#include "Utilities/TTypes.h"
#include "Utilities/Rect.h"
#include "Utilities/Point.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxTexture.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/DxGameSprite.h"
#include "DxWrapper/DxText.h"
#include "Utilities/Timer.h"
#include "DxWrapper/DxAssetManager.h"
#include "Atomic Penguin SmackDown/Player.h"



class GameUI
{
public:
	GameUI ( void );
	~GameUI ( void );

public:
   bool init( IDXFONT font, int xPos, int yPos, Player& player, D3DCOLOR color );
   bool update( bool isPlayerTurn );
   bool destroy();

   bool draw( IDXSPRITE spriteObj );
   
   void updateMovesCounter( int movesCounter );
   
   

 
private:
   Player*           myPlayer;
   DxText            myPlayerOne;
   DxText            myPlayerTwo;
   DxText            myMovesCounter;

   std::vector<DxGameSprite*> myPenguins;
   std::vector<Penguin::Type> myPenguinTypes;
   std::vector<DxGameSprite*> myHealthBars;
   DxGameSprite               myPlayerHeader;
   DxGameSprite               myRoundCounter;
   DxGameSprite               myPlayCounter;

   D3DCOLOR          myTextColor;

   int               movesCounter;


   //DxGameSprite    myUIHeader;
   //
   //DxGameSprite     myClockFace;
   //DxText           myTimerText;
   //DxText           myScoreText;

   //DxGameSprite     myKittyFace;
   //DxText           myLivesText;

   //D3DCOLOR         myTextColor;
   //
   //Timer            myTimer;

   //int              myTotalTime;
   //int              myScoreAmount;
   //int              myLivesAmount;


};

#endif 