#include "stdafx.h"
#include <cassert>
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxTypes.h"
#include "Atomic Penguin SmackDown/GameUI.h"

//=======================================================================
GameUI::GameUI()
{

}

//=======================================================================
GameUI::~GameUI()
{
}

//=======================================================================
bool GameUI::init( IDXFONT font, int xPos, int yPos, D3DCOLOR color )
{
   myTextColor = color;

   myPlayerOne.create( font, "PLAYER ONE", 10, 15, 100, 100, myTextColor ); 
   myPlayerTwo.create( font, "PLAYER TWO", 770, 15, 100, 100, myTextColor );
   
   p1General.setScale(0.5f, 0.5f);
   p1General.create("P1-GENERAL-FRONT", 2);
   p1General.setPosition((xPos+10),(yPos + 60));

   p1Bazooka.setScale(0.5f, 0.5f);
   p1Bazooka.create("P1-BAZOOKA-FRONT", 2);
   p1Bazooka.setPosition((xPos+10),(yPos + 160));

   p1Slider.setScale(0.5f, 0.5f);
   p1Slider.create("P1-SLIDER-LEFT", 2);
   p1Slider.setPosition((xPos+10),(yPos + 260));

   p1Pawn1.setScale(0.5f, 0.5f);
   p1Pawn1.create("P1-PAWN-FRONT", 2);
   p1Pawn1.setPosition((xPos+10),(yPos + 360));

   p1Pawn2.setScale(0.5f, 0.5f);
   p1Pawn2.create("P1-PAWN-FRONT", 2);
   p1Pawn2.setPosition((xPos+10),(yPos + 460));

   p1Hulk.setScale(0.5f, 0.5f);
   p1Hulk.create("P1-HULK-FRONT", 2);
   p1Hulk.setPosition((xPos+10),(yPos + 560));


   p2General.setScale(0.5f, 0.5f);
   p2General.create("P2-GENERAL-FRONT", 2);
   p2General.setPosition((xPos+830),(yPos + 60));

   p2Bazooka.setScale(0.5f, 0.5f);
   p2Bazooka.create("P2-BAZOOKA-FRONT", 2);
   p2Bazooka.setPosition((xPos+830),(yPos + 160));

   p2Slider.setScale(0.5f, 0.5f);
   p2Slider.create("P2-SLIDER-RIGHT", 2);
   p2Slider.setPosition((xPos+830),(yPos + 260));

   p2Pawn1.setScale(0.5f, 0.5f);
   p2Pawn1.create("P2-PAWN-FRONT", 2);
   p2Pawn1.setPosition((xPos+830),(yPos + 360));

   p2Pawn2.setScale(0.5f, 0.5f);
   p2Pawn2.create("P2-PAWN-FRONT", 2);
   p2Pawn2.setPosition((xPos+830),(yPos + 460));

   p2Hulk.setScale(0.5f, 0.5f);
   p2Hulk.create("P2-HULK-FRONT", 2);
   p2Hulk.setPosition((xPos+830),(yPos + 560));


   return true;
}
//=======================================================================
bool GameUI::update(  )
{
   myPlayerOne.update();
   myPlayerTwo.update();
   p1General.update();
   p1Bazooka.update();
   p1Slider.update();
   p1Pawn1.update();
   p1Pawn2.update();
   p1Hulk.update();
   p2General.update();
   p2Bazooka.update();
   p2Slider.update();
   p2Pawn1.update();
   p2Pawn2.update();
   p2Hulk.update();
   
   return true;
}

//=======================================================================
bool GameUI::destroy()
{
   return true;
}

//=======================================================================
bool GameUI::draw( IDXSPRITE spriteObj )
{
   
   myPlayerOne.draw( spriteObj );
   myPlayerTwo.draw( spriteObj );
   p1General.draw( spriteObj );
   p1Bazooka.draw( spriteObj );
   p1Slider.draw( spriteObj );
   p1Pawn1.draw( spriteObj );
   p1Pawn2.draw( spriteObj );
   p1Hulk.draw( spriteObj );
   p2General.draw( spriteObj );
   p2Bazooka.draw( spriteObj );
   p2Slider.draw( spriteObj );
   p2Pawn1.draw( spriteObj );
   p2Pawn2.draw( spriteObj );
   p2Hulk.draw( spriteObj );


   return true;
}

void GameUI::updateMovesCounter( int movesCounter )
{
}






