#include "stdafx.h"
#include <cassert>
#include "Utilities/Rect.h"
#include "Utilities/Point.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/DxWrapper.h"
#include "DxWrapper/DxTexture.h"

//=======================================================================
DxTexture::DxTexture ( void )
:myTexture(NULL)
{
   ZeroMemory( &myTextureInfo, sizeof(myTextureInfo) );
}

//=======================================================================
DxTexture::DxTexture ( const DxTexture& other )
:DxImage(other), myTexture(NULL)
{
   ZeroMemory( &myTextureInfo, sizeof(myTextureInfo) );
   *this = other;
}

//=======================================================================
DxTexture::~DxTexture ( void )
{
   destroy();
}

//=======================================================================
DxTexture& DxTexture::operator= ( const DxTexture& other )
{
   DxImage::operator=( other );
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
DxTexture::operator IDXTEXTURE ( void )
{
   return myTexture;
}

//=======================================================================
bool DxTexture::create ( IDXDEVICE device, int width, int height, DWORD usage )
{
   HRESULT result;
   result = D3DXCreateTexture( device,             //Direct3D device object
                               width,              //image width
                               height,             //image height
                               1,                  //mip-map levels (1 for no chain)
                               usage,              //D3DUSAGE: )
                               D3DFMT_UNKNOWN,     //texture format (default)
                               D3DPOOL_DEFAULT,    //memory class for the texture
                               &myTexture          //destination texture
                               );                                           
   return SUCCEEDED( result );
}

//bool DxTexture::create( IDXDEVICE device, int width, int height, DWORD usage, 

//=======================================================================
bool DxTexture::create ( IDXDEVICE device, LPCVOID pData, UINT dataSize, D3DCOLOR transcolor )
{
   HRESULT result;
   assert( getInfoFromFileInMemory( pData, dataSize ) );

   result = D3DXCreateTextureFromFileInMemoryEx ( device,              //Direct3D device object
                                                  pData,               //Pointer to the file in memory
                                                  dataSize,            //the size of the file in memory height
                                                  fileInfo().Width,    //bitmap image width
                                                  fileInfo().Height,   //bitmap image height
                                                  1,                   //mip-map levels (1 for no chain)
                                                  D3DPOOL_DEFAULT,     //the type of surface (standard)
                                                  D3DFMT_UNKNOWN,      //surface format (default)
                                                  D3DPOOL_DEFAULT,     //memory class for the texture
                                                  D3DX_DEFAULT,        //image filter
                                                  D3DX_DEFAULT,        //mip filter
                                                  transcolor,          //color key for transparency
                                                  &myTextureInfo,      //bitmap file myFileInfo (from loaded file)
                                                  NULL,                //color palette
                                                  &myTexture );        //destination texture
   return SUCCEEDED( result );
}

//=======================================================================
bool DxTexture::create ( IDXDEVICE device, const tstring& filename, D3DCOLOR transcolor, POINT* srcSize )
{
   HRESULT result;
   assert( getInfoFromFile( filename ) );

   result = D3DXCreateTextureFromFileEx( device,                                         //Direct3D device object
						                       filename.c_str(),                               //bitmap filename
                                         (srcSize ? (srcSize->x) : fileInfo().Width),    //bitmap image width
                                         (srcSize ? (srcSize->y) : fileInfo().Height),   //bitmap image height
						                       1,                                              //mip-map levels (1 for no chain)
						                       D3DPOOL_DEFAULT,                                //the type of surface (standard)
						                       D3DFMT_UNKNOWN,                                 //surface format (default)
						                       D3DPOOL_DEFAULT,                                //memory class for the texture
						                       D3DX_DEFAULT,                                   //image filter
						                       D3DX_DEFAULT,                                   //mip filter
						                       transcolor,                                     //color key for transparency
                                         &myTextureInfo,                                 //bitmap file myFileInfo (from loaded file)
						                       NULL,                                           //color palette
						                       &myTexture );                                   //destination texture
   return SUCCEEDED( result );
}

//=======================================================================
void DxTexture::destroy ( void )
{
   removeFileInfo();
   IfRelease( &myTexture );
   ZeroMemory( &myTextureInfo, sizeof(myTextureInfo) );
}


//=======================================================================
void DxTexture::stretchRect ( IDXDEVICE device, RECT* srcRect, IDXTEXTURE desTexture, RECT* desRect )
{
   IDXSURFACE srcSurface = NULL, desSurface = NULL, prevTarget = NULL;
   HRESULT hr;   

   hr = myTexture->GetSurfaceLevel( 0, &srcSurface );
   assert( SUCCEEDED(hr) );

   hr = desTexture->GetSurfaceLevel( 0, &desSurface );
   assert( SUCCEEDED(hr) );

   hr = device->GetRenderTarget( 0, &prevTarget );
   assert( SUCCEEDED(hr) );

   hr = device->SetRenderTarget( 0, desSurface );
   assert( SUCCEEDED(hr) );

   if ( SUCCEEDED(device->BeginScene()) && SUCCEEDED(DxWrapper::spriteInterface()->Begin(D3DXSPRITE_ALPHABLEND)) )
   {
      D3DXVECTOR3 pos( (desRect ? (FLOAT)desRect->left : 0), (desRect ? (FLOAT)desRect->top : 0), 0 );
      draw( DxWrapper::spriteInterface(), &pos, D3DCOLOR_XRGB( 255, 255, 255 ), srcRect, NULL );

      DxWrapper::spriteInterface()->End();
      device->EndScene();

      hr = device->Present( NULL, desRect, NULL, NULL );
      assert( SUCCEEDED(hr) );
   }


   hr = device->SetRenderTarget( 0, prevTarget );
   assert( SUCCEEDED(hr) );

   IfRelease(&srcSurface);
   IfRelease(&desSurface);
   IfRelease(&prevTarget);
}


//=======================================================================
HRESULT DxTexture::draw ( IDXSPRITE spriteobj, D3DXVECTOR3* position, D3DCOLOR color, RECT* dstRect, D3DXVECTOR3* center )
{
	HRESULT result = spriteobj->Draw( myTexture, dstRect, NULL, position, color);
	assert( SUCCEEDED( result ) );
   return result;
}

//=======================================================================
HRESULT DxTexture::draw ( IDXSPRITE spriteobj, D3DXVECTOR3* position, D3DXVECTOR2* scale, 
						 float rotation, D3DXVECTOR2* center, D3DCOLOR color, RECT* dstRect )
{
	D3DXMATRIX matrix, lastMatrix;
	HRESULT result;
	D3DXVECTOR3 center3d( (center ? center->x : 0.0f), (center ? center->y : 0.0f), 0.0f ); 
   D3DXVECTOR2 position2d( (position ? position->x : 0.0f), (position ? position->y : 0.0f) );

   D3DXMatrixTransformation2D( &matrix, center, 0, scale, center, rotation, &position2d );
   
   result = spriteobj->GetTransform( &lastMatrix );
   assert( SUCCEEDED( result ) );

	result = spriteobj->SetTransform( &matrix );
   assert( SUCCEEDED( result ) );

   result = spriteobj->Draw( myTexture, dstRect, &center3d, position, color );
	assert( SUCCEEDED( result ) );

   result = spriteobj->SetTransform( &lastMatrix );
   assert( SUCCEEDED( result ) );

   return result;
}
