#include "stdafx.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxKeyboard.h"
using namespace std;

DxKeyboard::DxKeyboard()
{
	myKeyboard = NULL;
	myInput = NULL;
}
DxKeyboard::~DxKeyboard()
{

}


bool DxKeyboard::keyboardInit(HWND hwnd)
{
   
	myHwnd = hwnd;
    //initialize DirectInput object
    DirectInput8Create(
        GetModuleHandle(NULL), 
        DIRECTINPUT_VERSION, 
        IID_IDirectInput8,
        (void**)&myInput,
        NULL);

    //initialize the keyboard
    myInput->CreateDevice(GUID_SysKeyboard, &myKeyboard, NULL); 
    myKeyboard->SetDataFormat(&c_dfDIKeyboard); //how the data format is set.
    myKeyboard->SetCooperativeLevel(myHwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND); // how mucj of the keyboard directInput will give your program by way of priority.
    myKeyboard->Acquire();// acquire the device

    return true;
}

void DxKeyboard::keyboardUpdate()
{
    //update keyboard
    myKeyboard->Poll();
    if (!SUCCEEDED(myKeyboard->GetDeviceState(256,(LPVOID)&myKeys)))
    {
        //keyboard device lost, try to re-acquire
        myKeyboard->Acquire(); //acquire the device
    }
}

bool DxKeyboard::keyPressed(int key) 
{
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}


bool DxKeyboard::keyDown(int key)
{
	short state = GetAsyncKeyState(key);

	if(state & 0x0001)
	{
		return (GetAsyncKeyState(key) & 0x8000) != 0;
	}
	
	return false;
}

//bool DxKeyboard::keyUp(int key)
//{
//   short state = GetAsyncKeyState(key);
//
//   if(state & 0x0101)
//
//   {
//      return !(GetAsyncKeyState(key) & ~0x8000) != 0;
//   }
//
//   return false;
//}

void DxKeyboard::shutdown()
{
        myKeyboard->Unacquire();
        myKeyboard->Release();
        myKeyboard = NULL;
}


//------------Testing getting individual keys------------------
char DxKeyboard::getKeys(int key)
{
   return myKeys[key];
}