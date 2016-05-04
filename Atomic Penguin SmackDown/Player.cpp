#include "stdafx.h"
#include <cassert>
#include "Utilities/ConfigParser.h"
#include "DxWrapper/DxKeyboard.h"
#include "DxWrapper/DxAssetManager.h"
#include "DxWrapper/DxWrapper.h"
#include "Atomic Penguin SmackDown/Player.h"

//=======================================================================
bool Player::init ( tstring playerConfigFile, int tileWidth, int tiltHeight )
{
   ConfigParser parser;
   tifstream file( DxAssetManager::getInstance().getConfigAssetPath( playerConfigFile ).c_str() );
   tstring line;
   unsigned int penguinIndex = 0;

   if ( !file.is_open() || file.bad() )
   {
      return false;
   }

   while ( parser.getNextLine( file, line ) )
   {
      tstringstream ss(line);
      int type = -1;

      ss >> type;
      if ( ss.fail() )
      {
         ss.clear();
         tstring token;
         ss >> token;
         if ( token == "@NUMBER" && myPenguinCount == 0  )
         {
            ss >> myPenguinCount;
            myPenguins = new Penguin[myPenguinCount];
         }
         else if ( token == "@PLAYER" )
         {
            ss >> myTurnIndex;
         }
         else if ( token == "@MAXMOVE" )
         {
            ss >> myMaxMoves;
         }
         else
         {
            return false;
         }
      }
      else 
      {
         if ( myPenguinCount == 0 || penguinIndex >= myPenguinCount )
         {
            return false;
         }

         float c, r;
         ss >> c >> r;

         if ( ss.fail() )
         {
            return false;
         }

         myPenguins[penguinIndex].create( (Penguin::Type)type, c * tileWidth, r * tiltHeight, myTurnIndex );
         myPenguins[penguinIndex].setScale( (float)tileWidth  / (float)myPenguins[penguinIndex].getWidth(), 
            (float)tiltHeight / (float)myPenguins[penguinIndex].getHeight() );
         myPenguins[penguinIndex].resizeCollisionArea();
         penguinIndex++;
      }
   }

   myCursor.create( "CURSOR", 10 );
   myCursor.setScale( (float)tileWidth  / (float)myCursor.getWidth(), 
      (float)tiltHeight / (float)myCursor.getHeight() );
   myPrevMoveTexture = DxAssetManager::getInstance().getTexture( "GRADIENT" );
   return (myPrevMoveTexture != NULL);
}

//=======================================================================
void Player::update ( TiledBackground& tiledBackground )
{
   getSelectedPenguin();

   // penguin movement
   if ( mySelectedPenguin )
   {
      Tile* tile =   tiledBackground.tileAt( (float)mySelectedPenguin->getXPosition(), (float)mySelectedPenguin->getYPosition(),
                                             (float)mySelectedPenguin->getWidth(), (float)mySelectedPenguin->getHeight() );

      if ( DxKeyboard::keyPressed( VK_RETURN ) )// set penguin position 
      {
         myMoveCount += myMovements.size();
         myMovements.clear();
         if ( mySelectedPenguin->type() == Penguin::PAWN && tile->type() == Tile::SLIME )
         {
            mySackCount++;
            mySelectedPenguin->destroy();
            if ( mySackCount == 2 )
            {   
               mySelectedPenguin->create( Penguin::HULK, mySelectedPenguin->getXPosition(), mySelectedPenguin->getYPosition(), myTurnIndex );
            }
         }
         mySelectedPenguin = NULL;
      }
      else if ( DxKeyboard::keyPressed( VK_BACK ) && !myMovements.empty() )// move penguin to prev position
      {
         mySelectedPenguin->setPosition(myMovements.back().position);
         mySelectedPenguin->direction( myMovements.back().direction );
         myMovements.pop_back();
      }
   }
   myCursor.update();
}

//=======================================================================
void Player::draw ( IDXSPRITE spriteInterface )
{
   for ( unsigned int index = 0; mySelectedPenguin && index < myMovements.size(); index++ )
   {
      myPrevMoveTexture->drawScale( spriteInterface, myMovements[index].position.x, myMovements[index].position.y, 
                                    (float)mySelectedPenguin->getWidth(), (float)mySelectedPenguin->getHeight() );
   }

   if ( mySelectedPenguin )
   {
      myCursor.setPosition( mySelectedPenguin->getPosition() );
      myCursor.draw( spriteInterface );
   }

   for ( unsigned int index = 0; index < myPenguinCount; index++ )
   {
      myPenguins[index].draw( spriteInterface );
   }

}


//=======================================================================
void Player::shutdown ()
{
   if ( myPenguins )
   {
      delete[] myPenguins;
      myPenguins = NULL;
   }
}

//=======================================================================
bool Player::penguinCollision ( int column, int row )
{
   for ( unsigned int index = 0; index < myPenguinCount; index++ )
   {
      float x = (float)(column * myPenguins[index].getWidth());
      float y = (float)(row * myPenguins[index].getHeight());
      if ( x == myPenguins[index].getXPosition() && y == myPenguins[index].getYPosition() )
      {
         return true;
      }
   }
   return false;
}

//=======================================================================
bool Player::canMove ()
{
   return myMovements.size() < mySelectedPenguin->moveCount() &&
          (myMoveCount + myMovements.size()) < myMaxMoves;
}

//=======================================================================
void Player::moveSelectedPenguinTo ( int horz, int vert )
{
   if ( selectedPenguin() )
   {
      float nextX = mySelectedPenguin->getXPosition() + horz * mySelectedPenguin->getWidth();
      float nextY = mySelectedPenguin->getYPosition() + vert * mySelectedPenguin->getHeight();
      Movement movement = { mySelectedPenguin->direction(), D3DXVECTOR3( mySelectedPenguin->getXPosition(), mySelectedPenguin->getYPosition(), 0 ) };
      myMovements.push_back( movement );
      mySelectedPenguin->setXPosition(nextX);
      mySelectedPenguin->setYPosition(nextY);
   }
}

//=======================================================================
void Player::getSelectedPenguin ()
{
   // penguin selection
   for ( unsigned int index = 0; index < myPenguinCount; index++ )
   {
      myPenguins[index].update();

      if ( DxWrapper::mouse().mouseButton(0) )
      {
         int mouse_x = DxWrapper::mouse().mouseX(), mouse_y = DxWrapper::mouse().mouseY();
         if ( myMovements.empty() && myPenguins[index].getCollisionArea().contains( mouse_x, mouse_y ) )
         {
            mySelectedPenguin = &myPenguins[index];
         }
      }

      if ( &myPenguins[index] != mySelectedPenguin )
      {
         myPenguins[index].getAnimation().stop();
         myPenguins[index].getAnimation().reset();
      }
      else if ( !myPenguins[index].getAnimation().isPlaying() )
      {
         myPenguins[index].getAnimation().play();
      }
   }
}