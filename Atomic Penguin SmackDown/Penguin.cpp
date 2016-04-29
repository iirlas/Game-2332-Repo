#include "stdafx.h"
#include "Utilities/TTypes.h"
#include "Utilities/ConfigParser.h"
#include "DxWrapper/DxAssetManager.h"
#include "Atomic Penguin SmackDown/Penguin.h"
std::map<unsigned int, unsigned int> Penguin::ourPenguinMaxMoves;
float Penguin::ourAnimationSpeed = 10.0f;


//=======================================================================
bool Penguin::initPenguinMovement ( const tstring& filename )
{
   tifstream file( DxAssetManager::getInstance(). getConfigAssetPath(filename).c_str() );
   if ( !file.is_open() || file.bad() )
   {
      return false;
   }
   ConfigParser parser;
   tstring line;
   while ( parser.getNextLine( file, line ) )
   {
      tstringstream ss( line );
      int penguinType = 0, speed = -1;
      ss >> penguinType >> speed;
      if ( ss.fail() )
      {
         return false;
      }

      ourPenguinMaxMoves[penguinType] = speed;
   }
   return true;
}

//=======================================================================
bool Penguin::create ( Penguin::Type type, float x ,float y, int playerTurnIndex )
{
   bool result = false;
   myDirection = SOUTH;

   switch ( type )
   {
   case PAWN:
      myFrontAnim = "PAWN-FRONT"; myBackAnim = "PAWN-BACK"; 
      myLeftAnim =  "PAWN-LEFT"; myRightAnim = "PAWN-RIGHT";
      break;
   case BAZOOKA:
      myFrontAnim = "BAZOOKA-FRONT"; myBackAnim = "BAZOOKA-BACK"; 
      myLeftAnim =  "BAZOOKA-LEFT"; myRightAnim = "BAZOOKA-RIGHT";
      break;
   case SLIDER:
      myFrontAnim = "SLIDER-FRONT"; myBackAnim = "SLIDER-BACK"; 
      myLeftAnim =  "SLIDER-LEFT"; myRightAnim = "SLIDER-RIGHT";
      break;
   case GENERAL:
      myFrontAnim = "GENERAL-FRONT"; myBackAnim = "GENERAL-BACK";
      myLeftAnim =  "GENERAL-LEFT"; myRightAnim = "GENERAL-RIGHT";
      break;
   case HULK:
      myFrontAnim = "HULK-FRONT"; myBackAnim = "HULK-BACK";
      myLeftAnim =  "HULK-LEFT"; myRightAnim = "HULK-RIGHT";
      break;
   default:
      return false;
   }
   myFrontAnim = "P" + Util::intToString(playerTurnIndex) + "-" + myFrontAnim; 
   myBackAnim  = "P" + Util::intToString(playerTurnIndex) + "-" + myBackAnim;
   myLeftAnim  = "P" + Util::intToString(playerTurnIndex) + "-" + myLeftAnim; 
   myRightAnim = "P" + Util::intToString(playerTurnIndex) + "-" + myRightAnim;
   myType = type;
   myMaxMoves = ourPenguinMaxMoves[type];
   
   result = DxGameSprite::create( myFrontAnim, ourAnimationSpeed );
   setPosition( x, y );
   return result;
}


//=======================================================================
Penguin::Direction Penguin::direction ( Penguin::Direction direction )
{
   switch ( direction )
   {
   case Direction::NORTH:
      changeAnimation( myBackAnim, ourAnimationSpeed );
      break;
   case Direction::SOUTH:
      changeAnimation( myFrontAnim, ourAnimationSpeed );
      break;
   case Direction::EAST:
      changeAnimation( myRightAnim, ourAnimationSpeed );
      break;
   case Direction::WEST:
      changeAnimation( myLeftAnim, ourAnimationSpeed );
      break;
   }
   return (myDirection = direction);
}

//=======================================================================
bool Penguin::canMoveTo ( Tile::Type type )
{
   switch ( myType )
   {
   case PAWN:
   case HULK:
      return !!(type & (Tile::SLIME | Tile::PASSABLE));
   case BAZOOKA:
   case SLIDER:
   case GENERAL:
      return !!(type & (Tile::PASSABLE));
   }
   return false;
}

//=======================================================================
bool Penguin::canMoveFrom ( Tile::Type type )
{
   switch ( myType )
   {
   case HULK:
      return !!(type & (Tile::SLIME | Tile::PASSABLE));
   case PAWN:
   case BAZOOKA:
   case SLIDER:
   case GENERAL:
      return !!(type & (Tile::PASSABLE));
   }
   return false;
}