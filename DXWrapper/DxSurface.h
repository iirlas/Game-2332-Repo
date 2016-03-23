//-------------------------------------------------------------------------
// Author: Issac Irlas
//-------------------------------------------------------------------------
#pragma once

#if !defined(_DXSURFACE_H_)
#define _DXSURFACE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/ImageInfo.h"


//===================================================================================================

namespace DxWrapper
{

class Surface : public ImageInfo
{
public:
   Surface ( void );
   Surface ( const Surface& other );
   ~Surface ( void );
   Surface& operator= ( const Surface& other );
   operator IDxSurface ( void );
   operator bool ( void );
   IDxSurface* operator& ( void );

   UINT width ( void ) { return mySurfaceDescription.Width; }
   UINT height ( void ) { return mySurfaceDescription.Height; }

   bool create ( IDxDevice device, unsigned width, unsigned height );
   bool createFromFile ( IDxDevice device, LPCTSTR filepath, RECT* rCrop = NULL );
   void destroy ( void );
   HRESULT setToBackBuffer ( IDxDevice device, UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE type );
   void draw ( IDxDevice device, LPRECT sRect, IDxSurface target, LPRECT tRect, D3DTEXTUREFILTERTYPE filter = D3DTEXF_NONE );

   // Set surface's color
   bool setColor( IDxDevice device, D3DCOLOR color );

private:
   IDxSurface     mySurface;
   D3DSURFACE_DESC mySurfaceDescription;
};

}

#endif //_DXSURFACE_H_