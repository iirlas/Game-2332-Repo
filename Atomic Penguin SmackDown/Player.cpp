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
         if ( token == "@NUMBER" && penguinCount() == 0  )
         {
            //ss >> myPenguinCount;
            //myPenguins = new Penguin[myPenguinCount];
         }
         else if ( token == "@PLAYER" )
         {
            ss >> myTurnIndex;
         }
         else if ( token == "@MAXMOVE" )
         {
            ss >> myMaxMoves;
         }
         else if ( token == "@DIRECTION" )
         {
            tstring strDir;
            ss >> strDir;
            myStartDirection = Penguin::makeDirection( strDir );
         }
         else
         {
            return false;
         }
         if ( ss.fail() )
         {
            return false;
         }
      }
      else 
      {
         float c = 0, r = 0;
         ss >> c >> r;

         if ( ss.fail() )
         {
            return false;
         }
         Penguin* penguin = new Penguin();
         penguin->create( (Penguin::Type)type, c * tileWidth, r * tiltHeight, myTurnIndex, myStartDirection );
         penguin->setScale( (float)tileWidth  / (float)penguin->getWidth(),
                            (float)tiltHeight / (float)penguin->getHeight() );
         penguin->resizeCollisionArea();
         myPenguinMoveFlag[penguin] = true;
         myPenguins.push_back( penguin );
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
      Tile* tile =   tiledBackground.tileAt( *mySelectedPenguin );

      if ( DxKeyboard::keyPressed( VK_RETURN ) )// set penguin position 
      {
         myMoveCount += myMovements.size();
         myMovements.clear();
         toggleAttacking();

         if ( mySelectedPenguin->type() == Penguin::PAWN && tile->type() == Tile::SLIME )
         {
            mySackCount++;
            mySelectedPenguin->kill();
            if ( mySackCount == 2 )
            {   
               mySelectedPenguin->create( Penguin::HULK, mySelectedPenguin->getXPosition(), mySelectedPenguin->getYPosition(), myTurnIndex, myStartDirection );
            }
         }
         myPenguinMoveFlag[mySelectedPenguin] = false;
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

   for ( unsigned int index = 0; index < penguinCount(); index++ )
   {
      myPenguins[index]->draw( spriteInterface );
   }

}


//=======================================================================
void Player::shutdown ()
{
   for ( unsigned int index = 0; index < myPenguins.size(); index++ )
   {
      myPenguins[index]->destroy();
      delete myPenguins[index];
      myPenguins[index] = NULL;
   }
   myPenguins.clear();
}

//=======================================================================
bool Player::penguinCollision ( int column, int row )
{
   for ( unsigned int index = 0; index < penguinCount(); index++ )
   {
      float x = (float)(column * myPenguins[index]->getWidth());
      float y = (float)(row * myPenguins[index]->getHeight());
      if ( myPenguins[index]->isAlive() && x == myPenguins[index]->getXPosition() && y == myPenguins[index]->getYPosition() )
      {
         return true;
      }
   }
   return false;
}

//=======================================================================
bool Player::canMoveSelected ()
{
   return myMovements.size() < mySelectedPenguin->moveCount() &&
          (myMoveCount + myMovements.size()) < myMaxMoves && myPenguinMoveFlag[mySelectedPenguin];
}

//=======================================================================
bool Player::canMove()
{
   bool aPenguinCanMove = false;
   for ( unsigned int index = 0; index < myPenguins.size(); index++ )
   {
      aPenguinCanMove |= myPenguinMoveFlag[myPenguins[index]] && myPenguins[index]->isAlive();
   }
   return myMoveCount < myMaxMoves && aPenguinCanMove;
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
void Player::clearMoves() 
{ 
   myMoveCount = 0;
   std::map<Penguin*,bool>::iterator item = myPenguinMoveFlag.begin();
   for ( ; item != myPenguinMoveFlag.end(); item++ )
   {
      item->second = true;
   }
}

//=======================================================================
void Player::attackPenguin( float x, float y, int damage )
{
   for ( unsigned int index = 0; index < penguinCount(); index++ )
   {
      if ( myPenguins[index]->isAlive() && myPenguins[index]->getXPosition() == x && myPenguins[index]->getYPosition() == y )
      {
         myPenguins[index]->health( myPenguins[index]->health() - damage );
         if ( myPenguins[index]->health() <= 0 )
         {
            myPenguins[index]->destroy();
            myPenguins[index]->health(0);
         }
         break;
      }
   }
   
}

//=======================================================================
void Player::getSelectedPenguin ()
{
   // penguin selection
   for ( unsigned int index = 0; index < penguinCount(); index++ )
   {
      myPenguins[index]->update();

      if ( DxWrapper::mouse().mouseButton(0) )
      {
         int mouse_x = DxWrapper::mouse().mouseX(), mouse_y = DxWrapper::mouse().mouseY();
         if ( myPenguinMoveFlag[myPenguins[index]] && myMovements.empty() && myPenguins[index]->getCollisionArea().contains( mouse_x, mouse_y ) )
         {
            mySelectedPenguin = myPenguins[index];
         }
      }

      if ( myPenguins[index] != mySelectedPenguin )
      {
         myPenguins[index]->getAnimation().stop();
         myPenguins[index]->getAnimation().reset();
      }
      else if ( !myPenguins[index]->getAnimation().isPlaying() )
      {
         myPenguins[index]->getAnimation().play();
      }
   }
}