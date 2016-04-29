#pragma once

#if !defined(_PENGUIN_H_)
#define _PENGUIN_H_

#include <map>
#include "DxWrapper/DxGameSprite.h"
#include "Atomic Penguin SmackDown/Tile.h"


class Penguin : public DxGameSprite
{
public:

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
   
   static bool initPenguinMovement ( const tstring& filename );

   Penguin () {myMaxMoves = 0;}
   ~Penguin () {}
   bool create ( Type type, float x ,float y, int playerTurnIndex );
   inline unsigned int moveCount () { return myMaxMoves; }

   Direction direction () { return myDirection; }
   Direction direction ( Direction direction );

   Type type () { return myType; }

   bool canMoveTo ( Tile::Type type );
   bool canMoveFrom ( Tile::Type type );

private:

   static std::map<unsigned int, unsigned int> ourPenguinMaxMoves;
   static float ourAnimationSpeed;

   unsigned int myMaxMoves;
   tstring      myFrontAnim;
   tstring      myBackAnim;
   tstring      myLeftAnim;
   tstring      myRightAnim;
   Direction    myDirection;
   Type         myType;
};


#endif //_PENGUIN_H_