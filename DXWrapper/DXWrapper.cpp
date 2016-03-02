// DXWrapper.cpp : The Application Class.
//

#include "stdafx.h"
#include "DXWrapper.h"
#include <assert.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

//=======================================================================
DXWrapper::DXWrapper ( )
:myD3D(NULL), myD3DDevice(NULL), myBackBuffer()
{
}

//=======================================================================
DXWrapper::~DXWrapper ( )
{
}

//=======================================================================
//protected
bool DXWrapper::postInit ( )
{
   HRESULT result;
   myD3D = Direct3DCreate9(D3D_SDK_VERSION);
   if ( myD3D == NULL )
   {
      log( _T("Error when initailizing DirectX.") );
      return false;
   }
   ZeroMemory(&myD3Dpp, sizeof(myD3Dpp));
   myD3Dpp.Windowed = !fullscreen();
   myD3Dpp.SwapEffect = swapEffect();
   myD3Dpp.BackBufferFormat = format();
   myD3Dpp.BackBufferCount = backBufferCount();
   myD3Dpp.BackBufferWidth = viewport().width();
   myD3Dpp.BackBufferHeight = viewport().height();
   myD3Dpp.hDeviceWindow = window();
   myD3Dpp.PresentationInterval = presentationInterval();

   result = dxInterface()->CreateDevice( D3DADAPTER_DEFAULT, 
                                         D3DDEVTYPE_HAL, 
                                         window(),
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                         &myD3Dpp, 
                                         &myD3DDevice );

   if ( FAILED(result) || myD3DDevice == NULL )
   {
      log( _T("Could not create DirectX device.") );
      return false;
   }

   result = D3DXCreateSprite( dxDevice(), &mySpriteobj );

   if ( FAILED(result) || mySpriteobj == NULL )
   {
      log( _T("Unable to create sprite!") );
      return false;
   }

   result = dxDevice()->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &myBackBuffer );

   if ( FAILED(result) || myBackBuffer == NULL )
   {
      log( _T("Could not retrieve back buffer.") );
      return false;
   }

   return gameInit();
}

//=======================================================================
//protected
void DXWrapper::update ( )
{
   assert( !!myD3DDevice && "Trying to use an invalid DirectX device!" );
   gameRun( );  
}

//=======================================================================
//protected
void DXWrapper::preDestroy ( )
{
   gameExit( );
   if ( spriteInterface() )
   {
      mySpriteobj->Release();
      mySpriteobj = NULL;
   }
   if ( dxDevice() )
   {
      myD3DDevice->Release();
      myD3DDevice = NULL;
   }
   if ( dxInterface() )
   {
      myD3D->Release();
      myD3D = NULL;
   }
}