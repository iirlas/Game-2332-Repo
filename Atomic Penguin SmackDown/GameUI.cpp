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
bool GameUI::init( IDXFONT font, int xPos, int yPos, Player& player, D3DCOLOR color )
{
   myPlayer = &player;
   myTextColor = color;

   if ( !myPlayerHeader.create( "P" + Util::intToString( myPlayer->turnIndex() ) + "HEADER" ) ) 
   {
      return false;
   }
   myPlayerHeader.setPosition(xPos + 0.0f, yPos + 0.0f);

   float x = xPos + 10.0f, y = yPos + 90.0f;
   for ( unsigned int index = 0; index < myPlayer->penguinCount(); index++ )
   {
      Penguin* penguin = myPlayer->at(index);
      DxGameSprite* penguinSprite = new DxGameSprite();
      DxGameSprite* penguinHealthBar = new DxGameSprite();

      penguinSprite->create( "P" + Util::intToString( myPlayer->turnIndex() ) + 
                             "-" + penguin->typeToString() + "-FRONT", 2.0f );
      penguinSprite->setPosition( x, y );
      penguinSprite->setScale(0.5f, 0.5f);

      penguinHealthBar->create( "HEALTH" );
      penguinHealthBar->setPosition( x, y + 50.0f );

      y += 93.0f;

      myPenguins.push_back( penguinSprite );
      myHealthBars.push_back ( penguinHealthBar );
      myPenguinTypes.push_back( penguin->type() );
   }
   return true;
}
//=======================================================================
bool GameUI::update( bool isPlayerTurn )
{
   myPlayerHeader.getAnimation().setFrame( (isPlayerTurn ? 1 : 0) );

   for ( unsigned int index = 0; index < myPlayer->penguinCount(); index++ )
   {
      Penguin* penguin = myPlayer->at( index );
      if ( myPenguinTypes[index] != myPlayer->at(index)->type() )
      {
         myPenguins[index]->changeAnimation( "P" + Util::intToString( myPlayer->turnIndex() ) + 
                                             "-" + penguin->typeToString() + "-FRONT" );
      }
      myPenguins[index]->update();
   }
   for ( unsigned int index = 0; index < myHealthBars.size(); index++ )
   {
      Penguin* penguin = myPlayer->at( index );
      myHealthBars[index]->getAnimation().setFrame( 10 - (penguin->health()/10) );
   }
   
   return true;
}

//=======================================================================
bool GameUI::destroy()
{
   for ( unsigned int index = 0; index < myPenguins.size(); index++ )
   {
      myPenguins[index]->destroy();
      delete myPenguins[index];
      myPenguins[index] = NULL;
   }
   for ( unsigned int index = 0; index < myHealthBars.size(); index++ )
   {
      myHealthBars[index]->destroy();
      delete myHealthBars[index];
      myHealthBars[index] = NULL;
   }
   return true;
}

//=======================================================================
bool GameUI::draw( IDXSPRITE spriteObj )
{
   myPlayerHeader.draw( spriteObj );
   
   for ( unsigned int index = 0; index < myPenguins.size(); index++ )
   {
      D3DCOLOR color = ( myPlayer->at( index )->isAlive() ? D3DCOLOR_XRGB( 255, 255, 255 ) : D3DCOLOR_XRGB( 0, 0, 0 ) );
      myPenguins[index]->draw( spriteObj, color );
   }
   for ( unsigned int index = 0; index < myHealthBars.size(); index++ )
   {
      myHealthBars[index]->draw( spriteObj );

   }
   return true;
}

void GameUI::updateMovesCounter( int movesCounter )
{
}






