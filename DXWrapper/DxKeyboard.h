#pragma once

#if !defined(_DXKEYBOARD_H_)
#define _DXKEYBOARD_H_

#include "stdafx.h"
#include <windows.h>
#include "DxWrapper/DxCommon.h"

class DxKeyboard
{
public:
   enum KeyState
   {      
      UP,
      DOWN
   };

   static bool keyPressed(int key);

	static bool keyDown(int key);
   static bool keyUp(int key);

private:
   DxKeyboard();
	~DxKeyboard();
   static KeyState ourKeyState[256];
};

#endif

