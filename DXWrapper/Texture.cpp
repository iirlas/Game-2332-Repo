#include "stdafx.h"
#include <cassert>
#include "DxTypes.h"
#include "Texture.h"

//=======================================================================
Texture::Texture ( )
:myTexture(NULL)
{
   ZeroMemory( &myTextureInfo, sizeof(myTextureInfo) );
}

//=======================================================================
Texture::~Texture ( )
{
   destroy();
}

//=======================================================================
Texture::operator dxTexture ( )
{
   return myTexture;
}

//=======================================================================
bool Texture::create ( dxDevice device, const tstring& filename, D3DCOLOR transcolor, RECT* crop )
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
void Texture::destroy ( )
{
   removeFileInfo();
   assert( myTexture );
   myTexture->Release();
   myTexture = NULL;
}


//=======================================================================
void Texture::draw ( dxSprite spriteobj, dxVector3* position, dxColor color, RECT* crop )
{
	HRESULT result = spriteobj->Draw( myTexture, crop, NULL, position, color);
	assert( SUCCEEDED( result ) );
}

//=======================================================================
void Texture::drawEx ( dxSprite spriteobj, dxVector3* position, dxVector2* scale, float rotation, dxVector2* center, dxColor color, RECT* crop )
{
	D3DXMATRIX matrix, lastMatrix;
	HRESULT result;	
	
	dxVector3 center3d( (center ? center->x : 0), (center ? center->y : 0), 0.0f ); 
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
