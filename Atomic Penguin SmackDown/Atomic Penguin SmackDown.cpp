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
//:myHulkPenguin(NULL)
{
}

//=======================================================================
Game::~Game ()
{
}

//=======================================================================
bool Game::gameInit ()
{
   myGameTitle.append("Atomic Penguin Smackdown");
   winSetTitle ( myGameTitle );
   bool result = true;

   //DxAssetManager::getInstance().init("animation.txt");

   myBgRect = Rect( 0, 0, winScreenWidth(), winScreenHeight() );

   bgColor = D3DCOLOR_XRGB( 0, 0, 100 );

   //result &= myLevelBgnds.init( device(), _T("16x16.config") );
   //if ( !DxAssetManager::getInstance().init() ||
   //     !DxAssetManager::getInstance().parseConfig( "animations.txt" ) )
   //{
   //   return false;
   //}
   
   //myHulkPenguin = DxAssetManager::getInstance().getTexture( "HULK" );
   //bgColor = D3DCOLOR_XRGB( 0, 0, 100 );
   return true;
}

//=======================================================================
void Game::gameRun ()
{
   // pre-render

   // clear the backbuffer
   device()->ColorFill( backBuffer(), NULL, bgColor );
   //myLevelBgnds.update();
   // start rendering
   if ( SUCCEEDED(device()->BeginScene()) && SUCCEEDED(spriteInterface()->Begin(D3DXSPRITE_ALPHABLEND) ) )
   {
      //render
      //myHulkPenguin->draw( spriteInterface(), NULL, &D3DXVECTOR2(5.2f,5.2f), 0, NULL );
      // stop rendering
      //spriteInterface()->End();
      device()->EndScene();

      //switch screen to the next backbuffer
      device()->Present( NULL, NULL, NULL, NULL );
   }
}

//=======================================================================
void Game::gameExit ()
{
}