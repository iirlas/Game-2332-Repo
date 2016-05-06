// Atomic Penguin SmackDown.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <cassert>
#include "Utilities/ConfigParser.h"
#include "DxWrapper/DxAssetManager.h"
#include "Atomic Penguin SmackDown/GameMenu.h"
#include "Atomic Penguin SmackDown/GameRun.h"
#include "Atomic Penguin SmackDown/GameBlueVictory.h"
#include "Atomic Penguin SmackDown/GameGreenVictory.h"
#include "Atomic Penguin SmackDown/GameStalemate.h"
#include "Atomic Penguin SmackDown/Atomic Penguin SmackDown.h"

LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(Msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch(wParam)
		{
		case ID_OK:
			EndDialog(hWndDlg, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}

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
LRESULT Game::onCommand ( WPARAM wParam, LPARAM lParam  )
{
   switch ( LOWORD(wParam) )
   {

   case IDM_ABOUT:
      DialogBox(instance(), MAKEINTRESOURCE(IDD_DIALOG_GUIDE), window(), reinterpret_cast<DLGPROC>(DlgProc));
      break;
   case IDM_EXIT:
      quit();
      break;
   default:
      return DefWindowProc( window(), WM_COMMAND, wParam, lParam );
   }
   return 0;
}

//=======================================================================
bool Game::gameInit ()
{
   bool result = true;
   myGameTitle.append("Atomic Penguin Warfare");
   winSetTitle ( myGameTitle );
   bind( (Application::MsgProc)(&Game::onCommand), WM_COMMAND );

   bgColor = D3DCOLOR_XRGB( 0, 0, 100 );
   result &= DxAssetManager::getInstance().init();
   result &= DxAssetManager::getInstance().load("animations.txt");

   myGameInterfaces.push_back( new GameMenu() );         // 0
   myGameInterfaces.push_back( new GameRun() );          // 1
   myGameInterfaces.push_back( new GameBlueVictory() );  // 2
   myGameInterfaces.push_back( new GameGreenVictory() ); // 3
   myGameInterfaces.push_back( new GameStalemate() );    // 4


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
   case GameInterface::RESET:
      myCurrentGameInterface->reset( this );
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

