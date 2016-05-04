// Atomic Penguin SmackDown.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Utilities/ConfigParser.h"
#include "DxWrapper/DxAssetManager.h"
#include "Atomic Penguin SmackDown.h"

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
//:myHulkPenguin(NULL)
{
   myPlayerIndex = 0;
}

//=======================================================================
Game::~Game ()
{
}

//=======================================================================
bool Game::initPlayers ( const tstring& configFilename )
{
   tifstream playerConfigFile( DxAssetManager::getInstance().getAssetPath( configFilename ).c_str() );
   if ( !playerConfigFile.is_open() || playerConfigFile.bad() )
   {
      return false;
   }

   ConfigParser parser;
   tstring line;
   while ( parser.getNextLine( playerConfigFile, line ) )
   {
      myPlayers.push_back( new Player() );
      if (  !myPlayers.back()->init( line, myLevelBgnds.tileWidth(), myLevelBgnds.tileHeight() ) )
      {
         return false;
      }
   }

   playerConfigFile.close();
   return true;
}

//=======================================================================
void Game::resolveCollisions ()
{
   Player* currentPlayer = myPlayers[myPlayerIndex];
   Penguin* currentPenguin = currentPlayer->selectedPenguin();
   int horz = DxKeyboard::keyPressed( VK_RIGHT ) - DxKeyboard::keyPressed( VK_LEFT );
   int vert = DxKeyboard::keyPressed( VK_DOWN ) - DxKeyboard::keyPressed( VK_UP );

   if ( currentPenguin && XOR( horz, vert ) )
   {
      int column = (int)(currentPenguin->getXPosition() / currentPenguin->getWidth()) + horz;
      int row = (int)(currentPenguin->getYPosition() / currentPenguin->getHeight()) + vert;
      bool isFreeFromCollision = true;
      for ( unsigned int index = 0; index < myPlayers.size(); index++ )
      {
         if ( myPlayers[index]->penguinCollision( column, row ) )
         {
            isFreeFromCollision = false;
            break;
         }
      }
      bool canMoveFrom = currentPenguin->canMoveFrom( myLevelBgnds.tileAt( *currentPenguin )->type() );
      bool canMoveTo = currentPenguin->canMoveTo( myLevelBgnds.tileAt( column, row )->type() );
      if ( currentPlayer->canMove() && canMoveFrom && canMoveTo && isFreeFromCollision )
      {
         currentPlayer->moveSelectedPenguinTo( horz, vert );
         currentPenguin->direction( Penguin::makeDirection( horz, vert ) );
      }
      
   }
}

//=======================================================================
bool Game::gameInit ()
{
   bool result = true;
   myGameTitle.append("Atomic Penguin Warfare");
   winSetTitle ( myGameTitle );
   

   bgColor = D3DCOLOR_XRGB( 0, 0, 100 );
   DxAssetManager::getInstance().init();
   DxAssetManager::getInstance().load("animations.txt");

   myBgRect = Rect( 0, 0, startTransWidth(), startTransHeight() );

   result &= myLevelBgnds.init( device(), _T("16x16.config") );
   
   result &= myGameUI.init( fontInterface(), 0, 0, D3DCOLOR_XRGB(255, 255, 255) );

   result &= Penguin::initPenguinMovement( "Penguin.config" );

   result &= initPlayers("Player.config");

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
   for ( unsigned int index = 0; index < myPlayers.size(); index++ )
   {
      if ( index == myPlayerIndex )
      {
         myPlayers[index]->update( levelRef );
      }
   }
   resolveCollisions();
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
            myPlayers[index]->draw( spriteInterface() );
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
      myPlayers[index]->shutdown();
      delete myPlayers[index];
      myPlayers[index] = NULL;
   }
   myPlayers.clear();
   myGameUI.destroy();
   myLevelBgnds.shutdown();
   DxAssetManager::getInstance().shutdown();
}

