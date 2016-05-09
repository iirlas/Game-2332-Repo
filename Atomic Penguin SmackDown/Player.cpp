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
         if ( token == "@NUMBER" )
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
         penguin->scale( (float)tileWidth  / (float)penguin->width(), (float)tiltHeight / (float)penguin->height() );
         penguin->resetCollisionArea();
         myPenguinMoveFlag[penguin] = true;
         myPenguins.push_back( penguin );
      }
   }
   myCursor.create( "CURSOR", 10 );
   myCursor.scale( (float)tileWidth  / (float)myCursor.width(), (float)tiltHeight / (float)myCursor.height() );
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
               mySelectedPenguin->create( Penguin::HULK, mySelectedPenguin->x(), mySelectedPenguin->y(), myTurnIndex, myStartDirection );
            }
         }
         myPenguinMoveFlag[mySelectedPenguin] = false;
      }
      else if ( DxKeyboard::keyPressed( VK_BACK ) && !myMovements.empty() )// move penguin to prev position
      {
         mySelectedPenguin->position(myMovements.back().position);
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
                                    (float)mySelectedPenguin->width(), (float)mySelectedPenguin->height() );
   }

   if ( mySelectedPenguin )
   {
      myCursor.position( mySelectedPenguin->position() );
      myCursor.draw( spriteInterface );
   }

   for ( unsigned int index = 0; index < penguinCount(); index++ )
   {
      if ( myPenguins[index]->isAlive() )
      {
         myPenguins[index]->draw( spriteInterface );
      }
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
      float x = (float)(column * myPenguins[index]->width());
      float y = (float)(row * myPenguins[index]->height());
      if ( myPenguins[index]->isAlive() && x == myPenguins[index]->x() && y == myPenguins[index]->y() )
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
bool Player::penguinIsAlive()
{
   bool aPenguinIsAlive = false;
   for ( unsigned int index = 0; index < myPenguins.size(); index++ )
   {
      aPenguinIsAlive |= myPenguins[index]->isAlive();
   }
   return aPenguinIsAlive;
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
int Player::movesLeft ()
{
   return myMaxMoves - (myMoveCount + myMovements.size());
}

//=======================================================================
void Player::moveSelectedPenguinTo ( int horz, int vert )
{
   if ( selectedPenguin() )
   {
      float nextX = mySelectedPenguin->x() + horz * mySelectedPenguin->width();
      float nextY = mySelectedPenguin->y() + vert * mySelectedPenguin->height();
      Movement movement = { mySelectedPenguin->direction(), D3DXVECTOR3( mySelectedPenguin->x(), mySelectedPenguin->y(), 0 ) };
      myMovements.push_back( movement );
      mySelectedPenguin->x(nextX);
      mySelectedPenguin->y(nextY);
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
bool Player::attackPenguin( float x, float y, int damage )
{
   for ( unsigned int index = 0; index < penguinCount(); index++ )
   {
      if ( myPenguins[index]->isAlive() && myPenguins[index]->x() == x && myPenguins[index]->y() == y )
      {
         if ( myPenguins[index]->health() - damage <= 0 )
         {
            myPenguins[index]->kill();
         }
         else
         {
            myPenguins[index]->health( myPenguins[index]->health() - damage );
         }
         return true;
      }
   }
   return false;
}

//=======================================================================
void Player::getSelectedPenguin ()
{
   // penguin selection

   for ( unsigned int index = 0; index < penguinCount(); index++ )
   {
      if ( !myPenguins[index]->isAlive() || !myPenguinMoveFlag[myPenguins[index]] )
      {
         continue;
      }

      if ( DxWrapper::mouse().mouseButton(0) )
      {
         float mouse_x = (float)DxWrapper::mouse().mouseX(), mouse_y = (float)DxWrapper::mouse().mouseY();
         if ( myMovements.empty() && myPenguins[index]->contains( mouse_x, mouse_y ) )
         {
            if ( mySelectedPenguin )
            {
               mySelectedPenguin->getAnimation().setFrame( 0 );
            }
            mySelectedPenguin = myPenguins[index];
         }
      }
   
      if ( mySelectedPenguin )
      {
         mySelectedPenguin->update();
      }
   }
}