

#pragma once

#if !defined(_DXTEXTURE_H_)
#define _DXTEXTURE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities\NonCopyable.h"
#include "Utilities\TTypes.h"
#include "DxWrapper\DxCommon.h"
#include "DxWrapper\DxImage.h"
#include "DxWrapper\DxTypes.h"

//===================================================================================================
class DxTexture : public DxImage
{
public:
   DxTexture ( void );
   DxTexture ( const DxTexture& other );
   ~DxTexture ( void );
   DxTexture& operator= ( const DxTexture& other );
   operator IDXTEXTURE ( void );

   UINT width ( void ) { return myTextureInfo.Width; }
   UINT height ( void ) { return myTextureInfo.Height; }
   
   bool create ( IDXDEVICE device, int width, int height );
   bool create ( IDXDEVICE device, LPCVOID pData, UINT dataSize, D3DCOLOR transcolor );
   bool create ( IDXDEVICE device, const tstring& filename, D3DCOLOR transcolor, POINT* srcSize = NULL );
   void destroy ( void );

   void stretchRectToTexture ( IDXDEVICE device, const RECT* srcRect, DxTexture destTexture, const RECT* destRect );
   void stretchRectToSurface ( IDXDEVICE device, const RECT* srcRect, IDXSURFACE desSurface, const RECT* desRect );

   void draw ( IDXSPRITE spriteobj, D3DXVECTOR3* position, D3DCOLOR color = D3DCOLOR_XRGB( 255, 255, 255 ), RECT* crop = NULL );
   void draw ( IDXSPRITE spriteobj, D3DXVECTOR3* position, D3DXVECTOR2* scale, float rotation, D3DXVECTOR2* center, D3DCOLOR color = D3DCOLOR_XRGB( 0, 0, 0 ), RECT* crop = NULL );

private:  
   IDXTEXTURE      myTexture;
   D3DXIMAGE_INFO myTextureInfo;
};

#endif //_DXTEXTURE_H_