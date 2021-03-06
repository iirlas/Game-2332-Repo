// DxWrapper.cpp : The Application Class.
//

#include "stdafx.h"
#include <assert.h>
#include "Utilities/PathUtilities.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxAssetManager.h"
#include "DxWrapper/DxWrapper.h"

IDXDEVICE    DxWrapper::ourDevice = NULL;
IDXINTERFACE DxWrapper::ourInterface = NULL;
IDXSPRITE    DxWrapper::ourSpriteInterface = NULL;
IDXFONT      DxWrapper::ourFontInterface = NULL;
DxMouse      DxWrapper::ourMouse;

//=======================================================================
DxWrapper::DxWrapper ()
:myBackBuffer(NULL)
{
}

//=======================================================================
DxWrapper::~DxWrapper ()
{
}

//=======================================================================
//protected
bool DxWrapper::preWindow ()
{
   return PathUtilities::init();
}

//=======================================================================
//protected
bool DxWrapper::postInit ()
{
   HRESULT result;   
   ourInterface = Direct3DCreate9(D3D_SDK_VERSION);

   if ( dxInterface() == NULL )
   {
      Logger::message( _T("Error when initailizing DirectX.") );
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
                                         &ourDevice );

   if ( FAILED(result) || ourDevice == NULL )
   {
      Logger::message( _T("Could not create DirectX device.") );
      return false;
   }

   result = D3DXCreateSprite( device(), &ourSpriteInterface );
   if ( FAILED(result) || ourSpriteInterface == NULL )
   {
      Logger::message( _T("Unable to create sprite Interface!") );
      return false;
   }

   result = D3DXCreateFont( device(), 42, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &ourFontInterface );
   if( FAILED( result ) )
   {
      Logger::message( _T("Unable to create font!") );
      return false;
   };

   result = device()->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &myBackBuffer );
   if ( FAILED(result) || myBackBuffer == NULL )
   {
      Logger::message( _T("Could not retrieve back buffer.") );
      return false;
   }


   if ( !ourMouse.mouseInit( window(), device() ) )
   {
      Logger::message( _T("Could not retrieve mouse.") );
      return false;
   }

   return gameInit();
}

//=======================================================================
//protected
void DxWrapper::update ()
{
   assert( !!ourDevice && "Trying to use an invalid DirectX device!" );
   mouse().mouseUpdate();
   gameRun();  
}

//=======================================================================
//protected
void DxWrapper::preDestroy ()
{
   gameExit();
   DxAssetManager::getInstance().shutdown();
   mouse().mouseShutdown();

   if( fontInterface() )
   {
      ourFontInterface->Release();
      ourFontInterface = NULL;
   }
   if ( spriteInterface() )
   {
      ourSpriteInterface->Release();
      ourSpriteInterface = NULL;
   }
   if ( device() )
   {
      ourDevice->Release();
      ourDevice = NULL;
   }
   if ( dxInterface() )
   {
      ourInterface->Release();
      ourInterface = NULL;
   }
   PathUtilities::shutdown();
}