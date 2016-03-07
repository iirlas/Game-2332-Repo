
#pragma once

#if !defined(_DXCOMMON_H_)
#define _DXCOMMON_H_

#define DIRECTINPUT_VERSION (0x0800)
#define INFRELEASE(INTERFACE) if(INTERFACE){INTERFACE->Release();INTERFACE = NULL;}

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <DxErr.h>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <tchar.h>


// libraries
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

#endif //_DXCOMMON_H_
