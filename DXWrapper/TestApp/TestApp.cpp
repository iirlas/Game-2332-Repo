// TestApp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DxWrapper/DxAssetManager.h"
#include "TestApp.h"


//=======================================================================
int APIENTRY _tWinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                        LPTSTR    lpCmdLine, int       nCmdShow)
{
   Game app;
   return app.winMain ( hInstance, hPrevInstance, lpCmdLine, nCmdShow );
}

//=======================================================================
Game::Game ()
{
}

//=======================================================================
Game::~Game ()
{
}

//=======================================================================
bool Game::gameInit ()
{
   if ( !DxAssetManager::getInstance().init( "config.txt" ) )
   {
      return false;
   }
   bgColor = D3DCOLOR_XRGB( 0, 0, 100 );
   return true;
}

//=======================================================================
void Game::gameRun ()
{
   // pre-render

   // clear the backbuffer
   device()->ColorFill( backBuffer(), NULL, bgColor );

   // start rendering
   if ( SUCCEEDED(device()->BeginScene()) )
   {
      //render

      // stop rendering
      device()->EndScene();

      //switch screen to the next backbuffer
      device()->Present( NULL, NULL, NULL, NULL );
   }
}

//=======================================================================
void Game::gameExit ()
{
}