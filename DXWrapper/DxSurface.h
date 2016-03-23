//-------------------------------------------------------------------------
// Author: Issac Irlas
//-------------------------------------------------------------------------
#pragma once

#if !defined(_DXSURFACE_H_)
#define _DXSURFACE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "DxWrapper\DxCommon.h"
#include "DxWrapper\DxTypes.h"
#include "DxWrapper\DxImage.h"


//===================================================================================================
class DxSurface : public DxImage
{
public:
   DxSurface ( void );
   DxSurface ( const DxSurface& other );
   ~DxSurface ( void );
   DxSurface& operator= ( const DxSurface& other );
   operator IDXSURFACE ( void );
   operator bool ( void );
   IDXSURFACE* operator& ( void );

   UINT width ( void ) { return mySurfaceDescription.Width; }
   UINT height ( void ) { return mySurfaceDescription.Height; }

   bool create ( IDXDEVICE device, unsigned width, unsigned height );
   bool createFromFile ( IDXDEVICE device, LPCTSTR filepath, RECT* rCrop = NULL );
   void destroy ( void );
   HRESULT setToBackBuffer ( IDXDEVICE device, UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE type );
   void draw ( IDXDEVICE device, LPRECT sRect, IDXSURFACE target, LPRECT tRect, D3DTEXTUREFILTERTYPE filter = D3DTEXF_NONE );

   // Set surface's color
   bool setColor( IDXDEVICE device, D3DCOLOR color );

private:
   IDXSURFACE     mySurface;
   D3DSURFACE_DESC mySurfaceDescription;
};

#endif //_DXSURFACE_H_