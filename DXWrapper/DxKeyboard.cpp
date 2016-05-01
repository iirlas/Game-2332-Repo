#include "stdafx.h"
#include "Utilities/Logger.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxKeyboard.h"
using namespace std;

DxKeyboard::KeyState DxKeyboard::ourKeyboardState[256] = {};

//=======================================================================
bool DxKeyboard::keyPressed(int key) 
{
   short state = GetAsyncKeyState(key);
   if ( (state & 0x0001) && (state & 0x8000) )
   {
      if ( ourKeyboardState[key] != DOWN )
      {
         ourKeyboardState[key] = DOWN;
         return true;
      }
   }
   else if ( ourKeyboardState[key] == DOWN && !(state & 0x8000) )
   {
      ourKeyboardState[key] = UP;
   }
   return false;
}


//=======================================================================
bool DxKeyboard::keyDown(int key)
{
   return ( (GetAsyncKeyState(key) & 0x8000) != 0 );
}

//=======================================================================
//bool DxKeyboard::keyUp(int key)
//{
//   short state = GetAsyncKeyState(key);
//
//   if(state & 0x0001)
//   {
//      return (GetAsyncKeyState(key) & 0x8000) != 0;
//   }
//
//   return false;
//}