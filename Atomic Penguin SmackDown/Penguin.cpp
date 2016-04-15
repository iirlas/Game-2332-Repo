#include "stdafx.h"
#include "Atomic Penguin SmackDown/Penguin.h"

float Penguin::ourAnimationSpeed = 10.0f;

//=======================================================================
bool Penguin::create ( PENGUIN type, float x ,float y )
{
   bool result = false;
   switch ( type )
   {
   case PENGUIN::PAWN_P1:
      myFrontAnim = "P1-PAWN-FRONT"; myBackAnim =  "P1-PAWN-BACK"; 
      myLeftAnim =  "P1-PAWN-LEFT"; myRightAnim = "P1-PAWN-RIGHT";
      break;
   case PENGUIN::BAZOOKA_P1:
      myFrontAnim = "P2-BAZOOKA-FRONT"; myBackAnim =  "P2-BAZOOKA-BACK"; 
      myLeftAnim =  "P2-BAZOOKA-LEFT"; myRightAnim = "P2-BAZOOKA-RIGHT";
      break;
   case PENGUIN::SLIDER_P1:
      myFrontAnim = "P1-SLIDER-FRONT"; myBackAnim =  "P1-SLIDER-BACK"; 
      myLeftAnim =  "P1-SLIDER-LEFT"; myRightAnim = "P1-SLIDER-RIGHT";
      break;
   case PENGUIN::GENERAL_P1:
      myFrontAnim = "P1-GENERAL-FRONT"; myBackAnim =  "P1-GENERAL-BACK";
      myLeftAnim =  "P1-GENERAL-LEFT"; myRightAnim = "P1-GENERAL-RIGHT";
      break;
   case PENGUIN::HULK_P1:
      myFrontAnim = "P1-HULK-FRONT"; myBackAnim =  "P1-HULK-BACK";
      myLeftAnim =  "P1-HULK-LEFT"; myRightAnim = "P1-HULK-RIGHT";
      break;



   case PENGUIN::PAWN_P2:
      myFrontAnim = "P2-PAWN-FRONT"; myBackAnim =  "P2-PAWN-BACK"; 
      myLeftAnim =  "P2-PAWN-LEFT"; myRightAnim = "P2-PAWN-RIGHT";
      break;
   case PENGUIN::BAZOOKA_P2:
      myFrontAnim = "P2-BAZOOKA-FRONT"; myBackAnim =  "P2-BAZOOKA-BACK"; 
      myLeftAnim =  "P2-BAZOOKA-LEFT"; myRightAnim = "P2-BAZOOKA-RIGHT";
      break;
   case PENGUIN::SLIDER_P2:
      myFrontAnim = "P2-SLIDER-FRONT"; myBackAnim =  "P2-SLIDER-BACK"; 
      myLeftAnim =  "P2-SLIDER-LEFT"; myRightAnim = "P2-SLIDER-RIGHT";
      break;
   case PENGUIN::GENERAL_P2:
      myFrontAnim = "P2-GENERAL-FRONT"; myBackAnim =  "P2-GENERAL-BACK";
      myLeftAnim =  "P2-GENERAL-LEFT"; myRightAnim = "P2-GENERAL-RIGHT";
      break;
   case PENGUIN::HULK_P2:
      myFrontAnim = "P2-HULK-FRONT"; myBackAnim =  "P2-HULK-BACK";
      myLeftAnim =  "P2-HULK-LEFT"; myRightAnim = "P2-HULK-RIGHT";
      break;
   default:
      return false;
   }      
   result = DxGameSprite::create( myFrontAnim, ourAnimationSpeed );
   setPosition( x, y );
   return result;
}