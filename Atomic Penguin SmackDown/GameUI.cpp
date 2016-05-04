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
//**************************************PLAYER NAMES*************************************************
   p1Header.create("P1HEADER");
   p1Header.setPosition(0.0f, 0.0f);
   
   p2Header.create("P2HEADER");
   p2Header.setPosition(759.0f, 0.0f);


//-----------------------------------PLAYER1(GREEN)--------------------------------------------------
   //GENERAL Health: 80
   p1General.setScale(0.5f, 0.5f);
   p1General.create("P1-GENERAL-FRONT", 2.0f);
   p1General.setPosition((float)(xPos+10),(float)(yPos + 90));

   
   
   p1GeneralHealth.create("HEALTH", 1.0f);
   p1GeneralHealth.getAnimation().setFrame(2);
   p1GeneralHealth.setPosition (10.0f, 140.0f);
   

   //BAZOOKA Health: 60
   p1Bazooka.setScale(0.5f, 0.5f);
   p1Bazooka.create("P1-BAZOOKA-FRONT", 2.0f);
   p1Bazooka.setPosition((float)(xPos+10),(float)(yPos + 183));

   p1BazookaHealth.create("HEALTH");
   p1BazookaHealth.getAnimation().setFrame(4);
   p1BazookaHealth.setPosition( 10.0f, 233.0f);



   //SLIDER health: 40
   p1Slider.setScale(0.5f, 0.5f);
   p1Slider.create("P1-SLIDER-LEFT", 2.0f);
   p1Slider.setPosition((float)(xPos+10),(float)(yPos + 276));

   p1SliderHealth.create("HEALTH", 1.0f);
   p1SliderHealth.getAnimation().setFrame(6);
   p1SliderHealth.setPosition (10.0f, 326.0f);


   //PAWN ONE health: 30
   p1Pawn1.setScale(0.5f, 0.5f);
   p1Pawn1.create("P1-PAWN-FRONT", 2.0f);
   p1Pawn1.setPosition((float)(xPos+10),(float)(yPos + 369));


   p1Pawn1Health.create("HEALTH", 1.0f);
   p1Pawn1Health.getAnimation().setFrame(7);
   p1Pawn1Health.setPosition (10.0f, 419.0f);

   

   //PAWN TWO health: 30
   p1Pawn2.setScale(0.5f, 0.5f);
   p1Pawn2.create("P1-PAWN-FRONT", 2.0f);
   p1Pawn2.setPosition((float)(xPos+10),(float)(yPos + 462));

   p1Pawn2Health.create("HEALTH", 1.0f);
   p1Pawn2Health.getAnimation().setFrame(7);
   p1Pawn2Health.setPosition (10.0f, 502.0f);


   //HULK health: 50
   p1Hulk.setScale(0.5f, 0.5f);
   p1Hulk.create("P1-HULK-FRONT", 2.0f);
   p1Hulk.setPosition((float)(xPos+10),(float)(yPos + 555));

   p1HulkHealth.create("HEALTH", 1.0f);
   p1HulkHealth.getAnimation().setFrame(5);
   p1HulkHealth.setPosition (10.0f, 595.0f);





//-------------------------------------------PLAYER2(BLUE)-----------------------------------------------------------
   //GENERAL health: 80
   p2General.setScale(0.5f, 0.5f);
   p2General.create("P2-GENERAL-FRONT", 2.0f);
   p2General.setPosition((float)(xPos+830),(float)(yPos + 90));


   p2GeneralHealth.create("HEALTH", 1.0f);
   p2GeneralHealth.getAnimation().setFrame(2);
   p2GeneralHealth.setPosition (770.0f, 140.0f);


   
   //BAZOOKA health: 60
   p2Bazooka.setScale(0.5f, 0.5f);
   p2Bazooka.create("P2-BAZOOKA-FRONT", 2.0f);
   p2Bazooka.setPosition((float)(xPos+830),(float)(yPos + 183));

   p2BazookaHealth.create("HEALTH");
   p2BazookaHealth.getAnimation().setFrame(4);
   p2BazookaHealth.setPosition( 770.0f, 233.0f);



   //SLIDER health: 40
   p2Slider.setScale(0.5f, 0.5f);
   p2Slider.create("P2-SLIDER-RIGHT", 2.0f);
   p2Slider.setPosition((float)(xPos+830),(float)(yPos + 276));

   p2SliderHealth.create("HEALTH", 1.0f);
   p2SliderHealth.getAnimation().setFrame(6);
   p2SliderHealth.setPosition (770.0f, 326.0f);




   //PAWN ONE health: 30
   p2Pawn1.setScale(0.5f, 0.5f);
   p2Pawn1.create("P2-PAWN-FRONT", 2.0f);
   p2Pawn1.setPosition((float)(xPos+830),(float)(yPos + 369));

   p2Pawn1Health.create("HEALTH", 1.0f);
   p2Pawn1Health.getAnimation().setFrame(7);
   p2Pawn1Health.setPosition (770.0f, 419.0f);



   //PAWN TWO health: 30
   p2Pawn2.setScale(0.5f, 0.5f);
   p2Pawn2.create("P2-PAWN-FRONT", 2.0f);
   p2Pawn2.setPosition((float)(xPos+830),(float)(yPos + 462));

   p2Pawn2Health.create("HEALTH", 1.0f);
   p2Pawn2Health.getAnimation().setFrame(7);
   p2Pawn2Health.setPosition (770.0f, 502.0f);



   //HULK health: 50
   p2Hulk.setScale(0.5f, 0.5f);
   p2Hulk.create("P2-HULK-FRONT", 2.0f);
   p2Hulk.setPosition((float)(xPos+830),(float)(yPos + 555));


   p2HulkHealth.create("HEALTH", 1.0f);
   p2HulkHealth.getAnimation().setFrame(5);
   p2HulkHealth.setPosition (770.0f, 595.0f);


   return true;
}
//=======================================================================
bool GameUI::update(  )
{
   
   //p1GeneralHealth.update();
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
   
   
   
   p1Header.draw( spriteObj );
   p2Header.draw( spriteObj );
   p1General.draw( spriteObj );
   p1GeneralHealth.draw( spriteObj );
   p1Bazooka.draw( spriteObj );
   p1BazookaHealth.draw( spriteObj );
   p1Slider.draw( spriteObj );
   p1SliderHealth.draw( spriteObj );
   p1Pawn1.draw( spriteObj );
   p1Pawn1Health.draw( spriteObj );
   p1Pawn2.draw( spriteObj );
   p1Pawn2Health.draw( spriteObj );
   p1Hulk.draw( spriteObj );
   p1HulkHealth.draw( spriteObj );
   p2General.draw( spriteObj );
   p2GeneralHealth.draw( spriteObj );
   p2Bazooka.draw( spriteObj );
   p2BazookaHealth.draw( spriteObj );
   p2Slider.draw( spriteObj );
   p2SliderHealth.draw( spriteObj );
   p2Pawn1.draw( spriteObj );
   p2Pawn1Health.draw( spriteObj );
   p2Pawn2.draw( spriteObj );
   p2Pawn2Health.draw( spriteObj );
   p2Hulk.draw( spriteObj );
   p2HulkHealth.draw( spriteObj );


   return true;
}

void GameUI::updateMovesCounter( int movesCounter )
{
}






