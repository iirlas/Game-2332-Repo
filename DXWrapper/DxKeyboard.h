#pragma once

#if !defined(_DXKEYBOARD_H_)
#define _DXKEYBOARD_H_

#include "stdafx.h"
#include <windows.h>
#include "DxWrapper/DxCommon.h"

class DxKeyboard
{
public:
	DxKeyboard();
	~DxKeyboard();
	
	bool keyboardInit(HWND hwnd);
	void keyboardUpdate();
   void shutdown();
   char getKeys(int key);
	static bool keyPressed(int key);
	static bool keyDown(int key);
   static bool keyUp(int key);



private:
	LPDIRECTINPUTDEVICE8 myKeyboard;
	LPDIRECTINPUT8		   myInput;
	char				      myKeys[256];
	HWND				      myHwnd;

};

#endif

