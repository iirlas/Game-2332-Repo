//-------------------------------------------------------------------------
// Author: Issac Irlas
//-------------------------------------------------------------------------

#pragma once
#if !defined( _DXWRAPPER_H_ )
#define _DXWRAPPER_H_
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#include <d3d9.h>
#include <d3dx9.h>
#include "WinWrapper/Application.h"
#include "Utilities/TType.h"

class DxWrapper : public Application
{
public:
   //=======================================================================
   // Default Constructor
   DxWrapper ( );

   //=======================================================================
   // Default Overridable Deconstructor
   virtual ~DxWrapper ( );

protected:
   //=======================================================================
   // The initializer for any pre-game functionality.
   // Note: Must override to add functionality.
   virtual bool gameInit ( ) = 0;

   //=======================================================================
   // The updater for running and drawing frames for the game.
   // Note: Must override to add functionality.
   virtual void gameRun ( ) = 0;

   //=======================================================================
   // The cleanup function for the game.
   // Note: Must override to add functionality.
   virtual void gameExit ( ) = 0;

   //=======================================================================
   // The Interface used to create and control the dxDevice.
   LPDIRECT3D9 dxInterface ( )
   {
      return myD3D;
   }

   //=======================================================================
   // The interface used to create other directX objects.
   LPDIRECT3DDEVICE9 dxDevice ( )
   {
      return myD3DDevice;
   }

   //=======================================================================
   // The current backBuffer of window.
   LPDIRECT3DSURFACE9 backBuffer ( )
   {
      return myBackBuffer;
   }

   //=======================================================================
   //
   LPD3DXSPRITE spriteInterface ( )
   {
      return mySpriteobj;
   }

   //=======================================================================
   // Overrided to serive as the directX initializer and calls gameInit
   // after initialization.
   bool postInit ( );

   //=======================================================================
   // Overrided to wrap directX frame by frame updates and calls gameRun.
   void update ( );

   //=======================================================================
   // Overrided to call gameExit cleaning up after directX.
   void preDestroy ( );

   //=======================================================================
   // The presentation parameters of directX that determines the 
   // fullscreen/windowed state of the window.
   virtual bool fullscreen ( )
   {
      return FALSE;
   }

   //=======================================================================
   // The presentation parameters of directX that determines the type of
   // swap effect that directX will use.
   virtual D3DSWAPEFFECT swapEffect ( )
   {
      return D3DSWAPEFFECT_DISCARD;
   }

   //=======================================================================
   // The presentation parameters of directX that determines 
   // format of the back buffer.
   virtual D3DFORMAT format ( )
   {
      return D3DFMT_X8R8G8B8;
   }

   //=======================================================================
   // The presentation parameters of directX that determines the number of
   // back buffers.
   virtual UINT backBufferCount ( )      
   {
      return 1;
   }

   //=======================================================================
   // The presentation parameters of directX that determines the update 
   // interval of directX when rendering.
   virtual UINT presentationInterval ( ) 
   { 
      return D3DPRESENT_INTERVAL_DEFAULT; 
   }

private:
   LPDIRECT3D9           myD3D; 
   LPDIRECT3DDEVICE9     myD3DDevice;
   D3DPRESENT_PARAMETERS myD3Dpp;
   LPD3DXSPRITE          mySpriteobj;
   LPDIRECT3DSURFACE9    myBackBuffer;
};

#endif //_DXWRAPPER_H_
