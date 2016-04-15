#include "stdafx.h"

#include "Utilities/ConfigParser.h"
#include "DxWrapper/DxAssetManager.h"
#include "DxWrapper/DxWrapper.h"
#include "Atomic Penguin SmackDown/Player.h"

//=======================================================================
bool Player::init ( tstring playerConfigFile, int tileWidth, int tiltHeight )
{
   ConfigParser parser;
   tifstream file( DxAssetManager::getInstance().getConfigAssetPath( playerConfigFile ).c_str() );
   tstring line;
   int penguinIndex = 0;
   
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
         penguinIndex++;
      }
   }
   return true;
}

//=======================================================================
void Player::update ()
{
   for ( int index = 0; index < myPenguinCount; index++ )
   {
      myPenguins[index].update( );
   }
}

//=======================================================================
void Player::draw ()
{
   for ( int index = 0; index < myPenguinCount; index++ )
   {
      myPenguins[index].draw( DxWrapper::spriteInterface() );
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