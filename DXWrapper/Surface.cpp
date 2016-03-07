#include "stdafx.h"
#include <assert.h>
#include "Utilities/Rect.h"
#include "Utilities/Point.h"
#include "Utilities/Logger.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/Surface.h"

using namespace DxWrapper;

//=======================================================================
Surface::Surface ( void )
:mySurface( NULL )
{
   ZeroMemory( &mySurfaceDescription, sizeof(mySurfaceDescription) );
}

//=======================================================================
Surface::Surface ( const Surface& other )
:ImageInfo(other), mySurface(NULL)
{
   ZeroMemory( &mySurfaceDescription, sizeof(mySurfaceDescription) );
   *this = other;
}

//=======================================================================
Surface::~Surface ( void )
{
   destroy();
}

//=======================================================================
Surface& Surface::operator= ( const Surface& other )
{
   ImageInfo::operator=( other );
   if ( mySurface )
   {
      destroy();
   }
   if ( other.mySurface )
   {
      other.mySurface->AddRef();
      mySurface = other.mySurface;
      mySurfaceDescription = other.mySurfaceDescription;
   }
   return *this;
}

//=======================================================================
Surface::operator IDxSurface ( void )
{
   return mySurface;
}

//=======================================================================
IDxSurface* Surface::operator& ( void )
{
   return &mySurface;
}

//=======================================================================
Surface::operator bool ( void )
{
   return mySurface != NULL;
}

//=======================================================================
bool Surface::create ( IDxDevice device, unsigned width, unsigned height )
{
   HRESULT result = device->CreateOffscreenPlainSurface( width, height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &mySurface, NULL );
   if ( FAILED( result ) )
   {
      log( _T("Error: Could not create Surface!\n") );
      return false;
   }
   result = mySurface->GetDesc( &mySurfaceDescription );
   return SUCCEEDED(result);
}

//=======================================================================
bool Surface::createFromFile ( IDxDevice device, LPCTSTR filepath, RECT* rCrop )
{
   if ( !getInfoFromFile( filepath ) )
   {
      log( _T("Error: Could not load file!\n") );
      return false;
   }
   if ( !create( device, 
                 (rCrop ? ( rCrop->right - rCrop->left ): fileInfo().Width), 
                 (rCrop ? ( rCrop->bottom - rCrop->top ): fileInfo().Height) ) )
   {
      return false;
   }
   return SUCCEEDED( D3DXLoadSurfaceFromFile( mySurface, NULL, NULL, filepath, rCrop, D3DX_DEFAULT, 0, NULL ) );

}

//=======================================================================
void Surface::destroy ( void )
{
   removeFileInfo();
   INFRELEASE( mySurface );
   ZeroMemory( &mySurfaceDescription, sizeof(mySurfaceDescription) );
}

//=======================================================================
HRESULT Surface::setToBackBuffer ( IDxDevice device, UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE type )
{
   return device->GetBackBuffer( iSwapChain, iBackBuffer, type, &mySurface );
}

//=======================================================================
void Surface::draw ( IDxDevice device, LPRECT sRect, LPDIRECT3DSURFACE9 target, LPRECT tRect, D3DTEXTUREFILTERTYPE filter )
{
   D3DVIEWPORT9 viewport = {0};
   device->GetViewport( &viewport );

   Rect rCSource( (sRect ? sRect->left : 0), 
                  (sRect ? sRect->top : 0), 
                  (sRect ? (sRect->right - sRect->left) : width( )), 
                  (sRect ? (sRect->bottom - sRect->top) : height( )) );
   Rect rCTarget( (tRect ? tRect->left : viewport.X), 
                  (tRect ? tRect->top : viewport.Y), 
                  (tRect ? (tRect->right - tRect->left) : viewport.Width), 
                  (tRect ? (tRect->bottom - tRect->top) : viewport.Height) );

   rCTarget.right( min( (LONG)(viewport.X + viewport.Width), rCTarget.right( ) ) );
   rCTarget.bottom( min( (LONG)(viewport.Y + viewport.Height), rCTarget.bottom( ) ) );

   rCSource.right( min( rCTarget.width( ), rCSource.width( ) ) );
   rCSource.bottom( min( rCTarget.height( ), rCSource.height( ) ) );

   rCSource.left( rCTarget.left( ) < 0 ?  abs( rCSource.left( ) - rCTarget.left( ) ) : rCSource.left( ) );
   rCSource.top( rCTarget.top( ) < 0 ?  abs( rCSource.top( ) - rCTarget.top( ) ) : rCSource.top( ) );

   rCTarget.left( max( (LONG)viewport.X, rCTarget.left( ) ) );
   rCTarget.top( max( (LONG)viewport.Y, rCTarget.top( ) ) );

   device->StretchRect( mySurface, &rCSource, target, &rCTarget, filter );
}

//=======================================================================
bool Surface::setColor( IDxDevice device, D3DCOLOR color )
{
	HRESULT result = device->ColorFill( mySurface, NULL, color );

   return ( SUCCEEDED( result ) );
}