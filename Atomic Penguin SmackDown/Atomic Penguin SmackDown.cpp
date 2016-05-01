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
   DxAssetManager::getInstance().init();
   DxAssetManager::getInstance().load("animations.txt");

   myBgRect = Rect( 0, 0, startTransWidth(), startTransHeight() );

   result &= myLevelBgnds.init( device(), _T("16x16.config") );
   
   result &= myGameUI.init( fontInterface(), 0, 0, D3DCOLOR_XRGB(255, 255, 255) );

   result &= Penguin::initPenguinMovement( "Penguin.config" );

   myPlayers.push_back( Player() );

   for ( unsigned int index = 0; index < myPlayers.size(); index++ )
   {
      result &= myPlayers[index].init( "Player1.config", myLevelBgnds.tileWidth(), myLevelBgnds.tileHeight() );
   }
   return result;
}

//=======================================================================
void Game::gameRun ()
{
   // pre-render
   TiledBackground&  levelRef = myLevelBgnds;
   // clear the backbuffer
   device()->ColorFill( backBuffer(), NULL, bgColor );
   myLevelBgnds.update();
   for ( unsigned int index = 0; index < myPlayers.size(); index ++ )
   {
      myPlayers[index].update( levelRef );
   }
   myGameUI.update();

   //myPlayer.resolveCollisions( levelRef );


   // start rendering
   if ( SUCCEEDED(device()->BeginScene()) )
   {
      if ( SUCCEEDED(spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
         // sprite rendering...       
         myLevelBgnds.drawMySpriteMap( spriteInterface() );
         for ( unsigned int index = 0; index < myPlayers.size(); index ++ )
         {
            myPlayers[index].draw( spriteInterface() );
         }
         myGameUI.draw( spriteInterface() );
         
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
   for ( unsigned int index = 0; index < myPlayers.size(); index++ )
   {
      myPlayers[index].shutdown();
   }
   myGameUI.destroy();
   myLevelBgnds.shutdown();
   DxAssetManager::getInstance().shutdown();
}