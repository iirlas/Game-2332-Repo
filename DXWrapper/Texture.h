#if !defined(_TEXTURE_H_)
#define _TEXTURE_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "ImageInfo.h"
#include "DxTypes.h"
#include "Utilities/NonCopyable.h"
#include "Utilities/TType.h"
class Texture : public ImageInfo
{
public:
   Texture ( );
   ~Texture ( );
   operator dxTexture ( );

   UINT width ( void ) { return myTextureInfo.Width; }
   UINT height ( void ) { return myTextureInfo.Height; }
   
   bool create ( dxDevice device, const tstring& filename, dxColor transcolor = D3DCOLOR_XRGB( 255, 255, 255 ), RECT* crop = NULL );
   void destroy ( void );

   void draw ( dxSprite spriteobj, dxVector3* position, dxColor color = D3DCOLOR_XRGB( 255, 255, 255 ), RECT* crop = NULL );
   void drawEx ( dxSprite spriteobj, dxVector3* position, dxVector2* scale, float rotation, dxVector2* center, dxColor color = D3DCOLOR_XRGB( 0, 0, 0 ), RECT* crop = NULL );

private:  
   dxTexture   myTexture;
   dxImageInfo myTextureInfo;
};

#endif //_TEXTURE_H_