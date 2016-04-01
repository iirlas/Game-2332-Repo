// Atomic Penguin SmackDown.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DxWrapper/DxAssetManager.h"
#include "Atomic Penguin SmackDown.h"

//=======================================================================
int APIENTRY _tWinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                         LPTSTR    lpCmdLine, int       nCmdShow)
{
   Game penguinGame;
   return penguinGame.winMain( hInstance, hPrevInstance, lpCmdLine, nCmdShow );
}

//=======================================================================
Game::Game ()
:myHulkPenguin(NULL)
{
}

//=======================================================================
Game::~Game ()
{
}

//=======================================================================
bool Game::gameInit ()
{
   if ( !DxAssetManager::getInstance().init( "config.txt" ) ||
        !DxAssetManager::getInstance().parseConfig( "images.txt" ) )
   {
      return false;
   }
   
   myHulkPenguin = DxAssetManager::getInstance().getTexture( "HULK" );
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
   if ( SUCCEEDED(device()->BeginScene()) && SUCCEEDED(spriteInterface()->Begin(D3DXSPRITE_ALPHABLEND) ) )
   {
      //render
      myHulkPenguin->draw( spriteInterface(), NULL, &D3DXVECTOR2(5.2f,5.2f), 0, NULL );
      // stop rendering
      spriteInterface()->End();
      device()->EndScene();

      //switch screen to the next backbuffer
      device()->Present( NULL, NULL, NULL, NULL );
   }
}

//=======================================================================
void Game::gameExit ()
{
}