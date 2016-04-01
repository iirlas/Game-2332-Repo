#include "stdafx.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxMouse.h"

DxMouse::DxMouse()
{
	myMouse = NULL;
	myInput = NULL;
}

DxMouse::~DxMouse()
{

}


bool DxMouse::mouseInit(HWND hwnd, LPDIRECT3DDEVICE9 d3ddev)
{
	myHwnd = hwnd;
    //initialize DirectInput object
    DirectInput8Create(
        GetModuleHandle(NULL), 
        DIRECTINPUT_VERSION, 
        IID_IDirectInput8,
        (void**)&myInput,
        NULL);

    //initialize the mouse
    myInput->CreateDevice(GUID_SysMouse, &myMouse, NULL);
    myMouse->SetDataFormat(&c_dfDIMouse);
    myMouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    myMouse->Acquire();
    d3ddev->ShowCursor(false);

    return true;
}

void DxMouse::mouseUpdate()
{
    //update mouse
    myMouse->Poll();
    if (!SUCCEEDED(myMouse->GetDeviceState(sizeof(DIMOUSESTATE),&myMouseState)))
    {
        //mouse device lose, try to re-acquire
        myMouse->Acquire();
    }
}

void DxMouse::mouseShutdown()
{
    if (myMouse) 
    {
        myMouse->Unacquire();
        myMouse->Release();
        myMouse = NULL;
    }
}


int DxMouse::mouseX()
{
    return myMouseState.lX;
}

int DxMouse::mouseY()
{
    return myMouseState.lY;
}

int DxMouse::mouseButton(int button)
{
    return myMouseState.rgbButtons[button] & 0x80;
}