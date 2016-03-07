//-----------------------------------------------------------------------
//Provides more usable version of DirectX interface and device
//variables
//-----------------------------------------------------------------------
#pragma once

#if !defined( _DXTYPES_H_ )
#define _DXTYPES_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

typedef LPDIRECT3D9				   IDxInterface;
typedef LPDIRECT3DDEVICE9		   IDxDevice;
typedef LPDIRECT3DSURFACE9		   IDxSurface;
typedef LPDIRECTINPUT8			   IDxInput;
typedef LPDIRECTINPUTDEVICE8	   IDxInputDevice;
typedef LPDIRECT3DTEXTURE9		   IDxTexture;
typedef LPD3DXSPRITE			      IDxSprite;

#endif //_DXTYPES_H_