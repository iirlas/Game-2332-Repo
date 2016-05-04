#pragma once

#if !defined(_PENGUIN_H_)
#define _PENGUIN_H_

#include <map>
#include "DxWrapper/DxGameSprite.h"
#include "Atomic Penguin SmackDown/Tile.h"


class Penguin : public DxGameSprite
{
public:

   struct Info
   {
      unsigned int maxMoves;
      unsigned int maxHealth;
   };

   typedef enum 
   {
      PAWN     = 1, 
      BAZOOKA  = 2, 
      SLIDER   = 3, 
      GENERAL  = 4, 
      HULK     = 5,
   } Type;

   typedef enum 
   {
      NONE,
      NORTH,
      SOUTH,
      EAST,
      WEST
   } Direction;

   inline static Direction makeDirection ( int xDir, int yDir )
   {
      return ( xDir > 0 ? EAST : 
               ( xDir < 0 ? WEST :
                  ( yDir > 0 ? SOUTH :
                     ( yDir < 0 ? NORTH : NONE ))));
   }
   
   inline static Direction makeDirection ( const tstring& str )
   {
      Direction direction = Direction::NONE;
      direction = ( str == "NORTH" ? Direction::NORTH : direction );
      direction = ( str == "SOUTH" ? Direction::SOUTH : direction );
      direction = ( str == "EAST" ? Direction::EAST : direction );
      direction = ( str == "WEST" ? Direction::WEST : direction );

      return direction;
   }
   
   static bool initPenguinMovement ( const tstring& filename );

   Penguin () {myHealth = 0; myDirection = Direction::NONE;}
   ~Penguin () {}
   bool create ( Type type, float x ,float y, int playerTurnIndex, Penguin::Direction direction  );
   inline unsigned int moveCount () { return ourPenguinInfo[myType].maxMoves; }

   Direction direction () { return myDirection; }
   Direction direction ( Direction direction );

   unsigned int health () { return myHealth; }
   unsigned int health ( unsigned int health ) { return (myHealth = health); }

   bool isAlive() { return myHealth > 0 && isValid(); }

   Type type () { return myType; }
   inline tstring typeToString ()
   {
      switch ( myType )
      {
      case PAWN:
         return "PAWN";
      case BAZOOKA:
         return "BAZOOKA";
      case SLIDER:
         return "SLIDER";
      case GENERAL:
         return "GENERAL";
      case HULK:
         return "HULK";
      }
      return "ERROR";
   }

   bool canMoveTo ( Tile::Type type );
   bool canMoveFrom ( Tile::Type type );

private:

   static std::map<Type, Info> ourPenguinInfo;
   static float ourAnimationSpeed;

   int          myHealth;
   tstring      myFrontAnim;
   tstring      myBackAnim;
   tstring      myLeftAnim;
   tstring      myRightAnim;
   Direction    myDirection;
   Type         myType;
};


#endif //_PENGUIN_H_