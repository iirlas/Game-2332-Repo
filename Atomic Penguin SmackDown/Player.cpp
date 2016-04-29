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
         if ( myPenguinCount != 0 )
         {
            return false;
         }
         ss.clear();

         tstring token;
         ss >> token;
         if ( token == "@NUMBER" )
         {
            ss >> myPenguinCount;
         }
         myPenguins = new Penguin[myPenguinCount];
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

         myPenguins[penguinIndex].create( (PENGUIN)type, c * tileWidth, r * tiltHeight );
         myPenguins[penguinIndex].setScale( (float)tileWidth  / (float)myPenguins[penguinIndex].getWidth(), 
            (float)tiltHeight / (float)myPenguins[penguinIndex].getHeight() );
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

   // penguin movement
   if ( mySelectedPenguin )
   {
      int horz = DxKeyboard::keyPressed( VK_RIGHT ) - DxKeyboard::keyPressed( VK_LEFT );
      int vert = DxKeyboard::keyPressed( VK_DOWN ) - DxKeyboard::keyPressed( VK_UP );

      if ( XOR(horz, vert) && myMovements.size() < mySelectedPenguin->moveCount() )
      {  
         float nextX = mySelectedPenguin->getXPosition() + horz * mySelectedPenguin->getWidth();
         float nextY = mySelectedPenguin->getYPosition() + vert * mySelectedPenguin->getHeight();


         Tile* tile = tiledBackground.tileAt( (float)nextX, (float)nextY, (float)mySelectedPenguin->getWidth(), (float)mySelectedPenguin->getHeight() );
         if ( tile && tile->type() != Tile::BLOCKED )
         {
            Movement movement = { mySelectedPenguin->direction(), D3DXVECTOR3( mySelectedPenguin->getXPosition(), mySelectedPenguin->getYPosition(), 0 ) };
            myMovements.push_back( movement );
            mySelectedPenguin->setXPosition(nextX);
            mySelectedPenguin->setYPosition(nextY);
         }

         mySelectedPenguin->direction( Penguin::makeDirection( horz, vert ) );

      }
      else if ( DxKeyboard::keyPressed( VK_RETURN ) )
      {
         myMovements.clear();
         mySelectedPenguin = NULL;
      }
      else if ( DxKeyboard::keyPressed( VK_BACK ) && !myMovements.empty() )
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
//void Player::collisionAt ( TiledBackground& tiledBackground,  )
//{
//   for ( unsigned int index = 0; index < myPenguinCount; index++ )
//   {
//      unsigned int tileIndex = 0;
//      if ( myCollisionManager.worldCollisions( myPenguins[index], tiledBackground, &tileIndex ) )
//      {
//         switch ( tiledBackground.mySpriteMap[tileIndex].type() )
//         {
//         case Tile::BLOCKED:
//            break;
//         case Tile::PASSABLE:
//            break;
//         case Tile::SLIME:
//            break;
//         }
//      }
//   }
//   //int index = ( (int)collision.left / mySelectedPenguin->getWidth() ) + 
//   //            ( (int)collision.top / mySelectedPenguin->getHeight() ) *  tiledBackground.numColumns();
//   //return mySelectedPenguin->collidesWith( tiledBackground.mySpriteMap[indexTopRight] ) &&  
//   //       tiledBackground.mySpriteMap[indexTopRight].collidable()
//}