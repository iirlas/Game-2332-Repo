#pragma once

#if !defined(_GAMEUI_H_)
#define _GAMEUI_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities/NonCopyable.h"
#include "Utilities/TTypes.h"
#include "Utilities/Rect.h"
#include "Utilities/Point.h"
#include "DxWrapper/DxTexture.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/DxGameSprite.h"
#include "DxWrapper/DxText.h"
#include "Utilities/Timer.h"
#include "DxWrapper/DxAssetManager.h"



class GameUI
{
public:
	GameUI ( void );
	~GameUI ( void );

public:
   bool init( IDXFONT font, int xPos, int yPos, D3DCOLOR color );
   bool update();
   bool destroy();

   bool draw( IDXSPRITE spriteObj );
   
   void updateMovesCounter( int movesCounter );
   
   

 
private:
   DxText            myPlayerOne;
   DxText            myPlayerTwo;
   DxText            myMovesCounter;


   DxGameSprite      p1Header;
   DxGameSprite      p1General;
   DxGameSprite      p1GeneralHealth;
   DxGameSprite      p1Bazooka;
   DxGameSprite      p1BazookaHealth;
   DxGameSprite      p1Slider; 
   DxGameSprite      p1SliderHealth;
   DxGameSprite      p1Pawn1;
   DxGameSprite      p1Pawn1Health;
   DxGameSprite      p1Pawn2;
   DxGameSprite      p1Pawn2Health;
   DxGameSprite      p1Hulk;
   DxGameSprite      p1HulkHealth;


   DxGameSprite      p2Header;
   DxGameSprite      p2General;
   DxGameSprite      p2GeneralHealth;
   DxGameSprite      p2Bazooka;
   DxGameSprite      p2BazookaHealth;
   DxGameSprite      p2Slider; 
   DxGameSprite      p2SliderHealth;
   DxGameSprite      p2Pawn1;
   DxGameSprite      p2Pawn1Health;
   DxGameSprite      p2Pawn2;
   DxGameSprite      p2Pawn2Health;
   DxGameSprite      p2Hulk;
   DxGameSprite      p2HulkHealth;

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