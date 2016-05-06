// Atomic Penguin SmackDown.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <cassert>
#include "Utilities/ConfigParser.h"
#include "DxWrapper/DxAssetManager.h"
#include "Atomic Penguin SmackDown/GameMenu.h"
#include "Atomic Penguin SmackDown/GameRun.h"
#include "Atomic Penguin SmackDown/Atomic Penguin SmackDown.h"

//=======================================================================
int APIENTRY _tWinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                         LPTSTR    lpCmdLine, int       nCmdShow)
{
   Application::enableCRTHeapDebugging( false );
   //Application::breakOnCRTAlloc( 3061 );
   Game penguinGame;
   return penguinGame.winMain( hInstance, hPrevInstance, lpCmdLine, nCmdShow );
}

//=======================================================================
Game::Game ()
{
   myGameIndex = 0;
}

//=======================================================================
Game::~Game ()
{
}

//=======================================================================
void Game::loadLevel ( unsigned int index )
{
   myGameIndex = index;
   if ( myGameIndex >= 0 && myGameIndex < myGameInterfaces.size() )
   {
      myCurrentGameInterface = myGameInterfaces[myGameIndex];
   }
}

//=======================================================================
void Game::loadNextLevel ()
{
   loadLevel( myGameIndex + 1 );
}

//=======================================================================
void Game::loadPrevLevel ()
{
   loadLevel( myGameIndex - 1 );
}

//=======================================================================
bool Game::gameInit ()
{
   bool result = true;
   myGameTitle.append("Atomic Penguin Warfare");
   winSetTitle ( myGameTitle );
   

   bgColor = D3DCOLOR_XRGB( 0, 0, 100 );
   result &= DxAssetManager::getInstance().init();
   result &= DxAssetManager::getInstance().load("animations.txt");

   myGameInterfaces.push_back( new GameMenu() );
   myGameInterfaces.push_back( new GameRun() );

   myCurrentGameInterface = myGameInterfaces[myGameIndex];

   return result;
}

//=======================================================================
void Game::gameRun ()
{
   switch ( myCurrentGameInterface->state() )
   {
   case GameInterface::NONE:
      assert(false);
      break;
   case GameInterface::INIT:
      if ( !myCurrentGameInterface->init( this ) )
      {
         quit();
      }
      break;
   case GameInterface::RUN:
      // clear the backbuffer
      device()->ColorFill( backBuffer(), NULL, bgColor );
      myCurrentGameInterface->run( this );
      break;
   case GameInterface::SHUTDOWN:
      myCurrentGameInterface->shutdown( this );
      break;
   default:
      break;
   }

   //if the escape key is pressed, destroy
   if ( DxKeyboard::keyPressed( VK_ESCAPE ) )
   {
      quit();
   }

}

//=======================================================================
void Game::gameExit ()
{
   for ( unsigned int index = 0; index < myGameInterfaces.size(); index++ )
   {
      myGameInterfaces[index]->shutdown( this );
      delete myGameInterfaces[index];
      myGameInterfaces[index] = NULL;
   }
   DxAssetManager::getInstance().shutdown();
}

