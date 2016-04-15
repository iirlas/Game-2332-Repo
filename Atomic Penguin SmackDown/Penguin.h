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
   Penguin () {}
   ~Penguin () {}
   bool create ( PENGUIN type, float x ,float y );

private:
   static float ourAnimationSpeed;
   tstring  myFrontAnim;
   tstring  myBackAnim;
   tstring  myLeftAnim;  
   tstring  myRightAnim;
};


#endif //_PENGUIN_H_