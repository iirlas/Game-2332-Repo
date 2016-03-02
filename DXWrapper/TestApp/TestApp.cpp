// TestApp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TestApp.h"


//=======================================================================
int APIENTRY _tWinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                        LPTSTR    lpCmdLine, int       nCmdShow)
{
   Game app;
   return app.winMain ( hInstance, hPrevInstance, lpCmdLine, nCmdShow );
}

//=======================================================================
Game::Game ( )
{
}

//=======================================================================
Game::~Game ( )
{
}

//=======================================================================
bool Game::gameInit ( )
{
   bgColor = D3DCOLOR_XRGB( 0, 0, 100 );
   return true;
}

//=======================================================================
void Game::gameRun ( )
{
   // pre-render

   // clear the backbuffer
   dxDevice()->ColorFill( backBuffer( ), NULL, bgColor );

   // start rendering
   if ( dxDevice()->BeginScene() )
   {
      //render

      // stop rendering
      dxDevice( )->EndScene();

      //switch screen to the next backbuffer
      dxDevice( )->Present( NULL, NULL, NULL, NULL );
   }
}

//=======================================================================
void Game::gameExit ( )
{
}