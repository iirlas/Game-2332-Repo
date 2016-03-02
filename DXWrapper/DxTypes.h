//-----------------------------------------------------------------------
//Provides more usable version of DirectX interface and device
//variables
//-----------------------------------------------------------------------

#if !defined( _DXTYPES_H_ )
#define _DXTYPES_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

typedef LPDIRECT3D9				   dxInterface;
typedef LPDIRECT3DDEVICE9		   dxDevice;
typedef D3DPRESENT_PARAMETERS	   dxPresentParams;
typedef LPDIRECT3DSURFACE9		   dxSurface;
typedef LPDIRECTINPUT8			   dxInput;
typedef LPDIRECTINPUTDEVICE8	   dxInputDevice;
typedef LPDIRECT3DTEXTURE9		   dxTexture;
typedef LPD3DXSPRITE			      dxSprite;
typedef D3DXIMAGE_INFO           dxImageInfo;
typedef D3DSURFACE_DESC          dxSurfaceDesc;
typedef D3DBACKBUFFER_TYPE       dxBackBufferType;
typedef D3DCOLOR                 dxColor;
typedef D3DXVECTOR2              dxVector2;
typedef D3DXVECTOR3              dxVector3;

#endif //_DXTYPES_H_