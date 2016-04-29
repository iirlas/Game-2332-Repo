// Atomic Penguin SmackDown.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DxWrapper/DxAssetManager.h"
#include "Atomic Penguin SmackDown.h"

//=======================================================================
int APIENTRY _tWinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                         LPTSTR    lpCmdLine, int       nCmdShow)
{
   Application::enableCRTHeapDebugging( false );
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
   bool result = true;
   myGameTitle.append("Atomic Penguin Smackdown");
   winSetTitle ( myGameTitle );
   

   bgColor = D3DCOLOR_XRGB( 0, 0, 100 );
   DxAssetManager::getInstance().init("animations.txt");

   myBgRect = Rect( 0, 0, startTransWidth(), startTransHeight() );

   result &= myLevelBgnds.init( device(), _T("16x16.config") );
   myCollisionManager.init();

   return myPlayer.init( "Player1.config", myLevelBgnds.tileWidth(), myLevelBgnds.tileHeight() );
}

//=======================================================================
void Game::gameRun ()
{
   // pre-render
   TiledBackground&  levelRef = myLevelBgnds;
   // clear the backbuffer
   device()->ColorFill( backBuffer(), NULL, bgColor );
   myLevelBgnds.update();
   myPlayer.update( levelRef );

   //myPlayer.resolveCollisions( levelRef );


   // start rendering
   if ( SUCCEEDED(device()->BeginScene()) )
   {
      if ( SUCCEEDED(spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
         // sprite rendering...       
         myLevelBgnds.drawMySpriteMap( spriteInterface() );
         myPlayer.draw( spriteInterface() );
         
         // stop rendering
         spriteInterface()->End();
      }

      // End rendering:
      device()->EndScene();
      device()->Present( NULL, NULL, NULL, NULL );
   }
}

//=======================================================================
void Game::gameExit ()
{
   myCollisionManager.shutdown();
}