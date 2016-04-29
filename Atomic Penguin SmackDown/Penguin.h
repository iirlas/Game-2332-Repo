#pragma once

#if !defined(_PENGUIN_H_)
#define _PENGUIN_H_

#include "DxWrapper/DxGameSprite.h"


typedef enum 
{
   PAWN_P1,
   BAZOOKA_P1,
   SLIDER_P1,
   GENERAL_P1,
   HULK_P1,

   PAWN_P2 = 0x100,
   BAZOOKA_P2,
   SLIDER_P2,
   GENERAL_P2,
   HULK_P2

} PENGUIN;

class Penguin : public DxGameSprite
{
public:
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
   
   static bool initPenguinMovement ();

   Penguin () {myMaxMoves = 0;}
   ~Penguin () {}
   bool create ( PENGUIN type, float x ,float y );
   inline unsigned int moveCount () { return myMaxMoves; }

   Direction direction () { return myDirection; }
   Direction direction ( Direction direction );

private:
   static unsigned int ourPenguinMaxMoves[5];
   static float ourAnimationSpeed;

   unsigned int myMaxMoves;
   tstring      myFrontAnim;
   tstring      myBackAnim;
   tstring      myLeftAnim;
   tstring      myRightAnim;
   Direction    myDirection;
};


#endif //_PENGUIN_H_