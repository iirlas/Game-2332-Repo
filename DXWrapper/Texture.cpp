#include "stdafx.h"
#include <cassert>
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/Texture.h"

using namespace DxWrapper;

//=======================================================================
Texture::Texture ( void )
:myTexture(NULL)
{
   ZeroMemory( &myTextureInfo, sizeof(myTextureInfo) );
}

//=======================================================================
Texture::Texture ( const Texture& other )
:ImageInfo(other), myTexture(NULL)
{
   ZeroMemory( &myTextureInfo, sizeof(myTextureInfo) );
   *this = other;
}

//=======================================================================
Texture::~Texture ( void )
{
   destroy();
}

//=======================================================================
Texture& Texture::operator= ( const Texture& other )
{
   ImageInfo::operator=( other );
   if ( myTexture )
   {
      destroy();
   }
   if ( other.myTexture )
   {
      other.myTexture->AddRef();
      myTexture = other.myTexture;
      myTextureInfo = other.myTextureInfo;
   }
   return *this;
}

//=======================================================================
Texture::operator IDxTexture ( void )
{
   return myTexture;
}

//=======================================================================
bool Texture::create ( IDxDevice device, const tstring& filename, D3DCOLOR transcolor, RECT* crop )
{
   HRESULT result;
   assert( getInfoFromFile( filename ) );

   result = D3DXCreateTextureFromFileEx( device,                                                  //Direct3D device object
						                       filename.c_str(),                                        //bitmap filename
                                         (crop ? (crop->right - crop->left) : fileInfo().Width),  //bitmap image width
						                       (crop ? (crop->bottom - crop->top) : fileInfo().Height), //bitmap image height
						                       1,                                                       //mip-map levels (1 for no chain)
						                       D3DPOOL_DEFAULT,                                         //the type of surface (standard)
						                       D3DFMT_UNKNOWN,                                          //surface format (default)
						                       D3DPOOL_DEFAULT,                                         //memory class for the texture
						                       D3DX_DEFAULT,                                            //image filter
						                       D3DX_DEFAULT,                                            //mip filter
						                       transcolor,                                              //color key for transparency
                                         &myTextureInfo,                                          //bitmap file myFileInfo (from loaded file)
						                       NULL,                                                    //color palette
						                       &myTexture );                                            //destination texture
   return SUCCEEDED( result );
}

//=======================================================================
void Texture::destroy ( void )
{
   removeFileInfo();
   INFRELEASE( myTexture );
   ZeroMemory( &myTextureInfo, sizeof(myTextureInfo) );
}

//=======================================================================
void Texture::draw ( IDxSprite spriteobj, D3DXVECTOR3* position, D3DCOLOR color, RECT* crop )
{
	HRESULT result = spriteobj->Draw( myTexture, crop, NULL, position, color);
	assert( SUCCEEDED( result ) );
}

//=======================================================================
void Texture::draw ( IDxSprite spriteobj, D3DXVECTOR3* position, D3DXVECTOR2* scale, float rotation, D3DXVECTOR2* center, D3DCOLOR color, RECT* crop )
{
	D3DXMATRIX matrix, lastMatrix;
	HRESULT result;	
	
	D3DXVECTOR3 center3d( (center ? center->x : 0), (center ? center->y : 0), 0.0f ); 
	D3DXMatrixTransformation2D( &matrix, center, 0, scale, center, rotation, NULL );
   
   result = spriteobj->GetTransform( &lastMatrix );
   assert( SUCCEEDED( result ) );

	result = spriteobj->SetTransform( &matrix );
   assert( SUCCEEDED( result ) );

   result = spriteobj->Draw( myTexture, crop, &center3d, position, color );
	assert( SUCCEEDED( result ) );

   result = spriteobj->SetTransform( &lastMatrix );
   assert( SUCCEEDED( result ) );
}
