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
   myInterfaces["Menu"] = new GameMenu();
   myInterfaces["Run"] = new GameRun();
   myInterfaces["BlueVictory"] = new GameBlueVictory();
   myInterfaces["GreenVictory"] = new GameGreenVictory();
   myInterfaces["Stalemate"] = new GameStalemate();

   myCurrentInterfaceName = "Menu";
}

//=======================================================================
Game::~Game ()
{
}

//=======================================================================
// load a game interface with a given state
void Game::loadInterface ( const tstring& name, GameInterface::State state )
{
   if ( myInterfaces.find( name ) != myInterfaces.end() )
   {
      myCurrentInterfaceName = name;
      myInterfaces[myCurrentInterfaceName]->state( state );
   }
}

//=======================================================================
// load a game interface with a current state
void Game::loadInterface ( const tstring& name )
{
   if ( myInterfaces.find( name ) != myInterfaces.end() )
   {
      myCurrentInterfaceName = name;
   }
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

   return result;
}

//=======================================================================
void Game::gameRun ()
{
   GameInterface* currentInterface = NULL;
   if ( myInterfaces.find(myCurrentInterfaceName) != myInterfaces.end() )
   {
      currentInterface = myInterfaces[myCurrentInterfaceName];
   }

   switch ( currentInterface->state() )
   {
   case GameInterface::NONE:
      assert(false);
      break;
   case GameInterface::INIT:
      if ( !currentInterface->init( this ) )
      {
         quit();
      }
      break;
   case GameInterface::RUN:
      // clear the backbuffer
      device()->ColorFill( backBuffer(), NULL, bgColor );
      currentInterface->run( this );
      break;
   case GameInterface::RESET:
      currentInterface->reset( this );
      break;
   case GameInterface::SHUTDOWN:
      currentInterface->shutdown( this );
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
   InterfaceMap::iterator item = myInterfaces.begin();
   for ( ; item != myInterfaces.end(); item++ )
   {
      item->second->shutdown( this );
      delete item->second;
      item->second = NULL;
   }
   DxAssetManager::getInstance().shutdown();
}

