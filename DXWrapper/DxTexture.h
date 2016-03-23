

#pragma once

#if !defined(_DXTEXTURE_H_)
#define _DXTEXTURE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities/NonCopyable.h"
#include "Utilities/TType.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/ImageInfo.h"
#include "DxWrapper/DxTypes.h"

namespace DxWrapper
{

class Texture : public ImageInfo
{
public:
   Texture ( void );
   Texture ( const Texture& other );
   ~Texture ( void );
   Texture& operator= ( const Texture& other );
   operator IDxTexture ( void );

   UINT width ( void ) { return myTextureInfo.Width; }
   UINT height ( void ) { return myTextureInfo.Height; }
   
   bool create ( IDxDevice device, const tstring& filename, D3DCOLOR transcolor = D3DCOLOR_XRGB( 255, 255, 255 ), RECT* crop = NULL );
   void destroy ( void );

   void draw ( IDxSprite spriteobj, D3DXVECTOR3* position, D3DCOLOR color = D3DCOLOR_XRGB( 255, 255, 255 ), RECT* crop = NULL );
   void draw ( IDxSprite spriteobj, D3DXVECTOR3* position, D3DXVECTOR2* scale, float rotation, D3DXVECTOR2* center, D3DCOLOR color = D3DCOLOR_XRGB( 0, 0, 0 ), RECT* crop = NULL );

private:  
   IDxTexture      myTexture;
   D3DXIMAGE_INFO myTextureInfo;
};

}

#endif //_DXTEXTURE_H_