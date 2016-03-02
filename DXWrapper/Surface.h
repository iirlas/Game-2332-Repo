//-------------------------------------------------------------------------
// Author: Issac Irlas
//-------------------------------------------------------------------------

#if !defined(_SURFACE_H_)
#define _SURFACE_H_
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "DxTypes.h"
#include "ImageInfo.h"
class Surface : public ImageInfo
{
public:
   Surface ( );
   ~Surface ( );
   operator dxSurface ( );
   operator bool ( );
   dxSurface* operator& ( );

   UINT width ( ) { return mySurfaceDescription.Width; }
   UINT height ( ) { return mySurfaceDescription.Height; }

   bool create ( dxDevice device, unsigned width, unsigned height );
   bool createFromFile ( dxDevice device, LPCTSTR filepath, RECT* rCrop = NULL );
   void destroy ( void );
   HRESULT setToBackBuffer ( dxDevice device, UINT iSwapChain, UINT iBackBuffer, dxBackBufferType type );
   void draw ( dxDevice device, LPRECT sRect, dxSurface target, LPRECT tRect, D3DTEXTUREFILTERTYPE filter = D3DTEXF_NONE );

   // Set surface's color
   bool setColor( dxDevice device, D3DCOLOR color );


private:
   dxSurface     mySurface;
   dxSurfaceDesc mySurfaceDescription;
};

#endif //_SURFACE_H_