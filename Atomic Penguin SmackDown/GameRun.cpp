#include "stdafx.h"

#include "Atomic Penguin SmackDown/Atomic Penguin SmackDown.h"
#include "Atomic Penguin SmackDown/GameRun.h"

//=======================================================================
GameRun::GameRun ()
//:myHulkPenguin(NULL)
{
   myPlayerIndex = 0;
   myRoundCount = 0;
   myRoundCountSinceAttack = 0;
   hasPlayerAttacked = false;
   state( State::INIT );
}

//=======================================================================
GameRun::~GameRun ()
{
}

//=======================================================================
bool GameRun::initPlayers ( const tstring& configFilename, Game* window )
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
      tstringstream ss(line);
      tstring filename;
      int guiX = 0, guiY = 0;
      ss >> filename >> guiX >> guiY;
      if ( ss.fail() )
      {
         return false;
      }
      myPlayers.push_back( new Player() );
      if (  !myPlayers.back()->init( filename, myLevelBgnds.tileWidth(), myLevelBgnds.tileHeight() ) )
      {
         return false;
      }
      myGUIs.push_back( new GameUI() );
      if ( !myGUIs.back()->init( window->fontInterface(), guiX, guiY, *myPlayers.back(), D3DCOLOR_XRGB(255, 255, 255) ) )
      {
         return false;
      }
   }

   playerConfigFile.close();
   state( State::RUN );
   return true;
}

//=======================================================================
void GameRun::resolveCollisions ( )
{
   Player* currentPlayer = myPlayers[myPlayerIndex];
   Penguin* currentPenguin = currentPlayer->selectedPenguin();
   int horz = DxKeyboard::keyPressed( VK_RIGHT ) - DxKeyboard::keyPressed( VK_LEFT );
   int vert = DxKeyboard::keyPressed( VK_DOWN ) - DxKeyboard::keyPressed( VK_UP );

   if ( currentPenguin && XOR( horz, vert ) )
   {
      int column = (int)(currentPenguin->getXPosition() / currentPenguin->getWidth()) + horz;
      int row = (int)(currentPenguin->getYPosition() / currentPenguin->getHeight()) + vert;
      if ( column < myLevelBgnds.numColumns() && column >= 0 && row < myLevelBgnds.numRows() && row >= 0 )
      {
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
         if ( currentPlayer->canMoveSelected() && canMoveFrom && canMoveTo && isFreeFromCollision )
         {
            currentPlayer->moveSelectedPenguinTo( horz, vert );
            currentPenguin->direction( Penguin::makeDirection( horz, vert ) );
         }
      }
   }
}

//=======================================================================
bool GameRun::init ( Game* window )
{
   bool result = true;

   result &= myLevelBgnds.init( window->device(), _T("16x16.config") );

   result &= Penguin::initPenguinMovement( "Penguin.config" );

   result &= initPlayers("Player.config", window);

   result &= myMoveText.create( window->fontInterface(), "0", 350, 0, 100, 100 );

   result &= myRoundText.create( window->fontInterface(), "0", 350, 600, 100, 100 );

   return result;
}

//=======================================================================
void GameRun::run ( Game* window )
{
   // pre-render
   TiledBackground&  levelRef = myLevelBgnds;
   // clear the backbuffer

   myLevelBgnds.update();

   for ( unsigned int index = 0; index < myPlayers.size(); index++ )
   {
      if ( index == myPlayerIndex )
      {
         myPlayers[index]->update( levelRef );
      }
      myGUIs[index]->update( (myPlayers[index]->turnIndex()-1) == myPlayerIndex );

      if ( myPlayers[index]->attacking() )
      {
         float x = 0, y = 0;
         myPlayers[index]->selectedPenguin()->getFacingPosition( &x, &y );
         for ( unsigned int j = 0; j < myPlayers.size(); j++ )
         {
            if ( j != index )
            {
               if ( myPlayers[j]->attackPenguin( x, y, myPlayers[index]->selectedPenguin()->attackPower() ) )
               {
                  hasPlayerAttacked = true;
                  myRoundCountSinceAttack = 0;
               }
            }
         }
         myPlayers[index]->toggleAttacking();
         myPlayers[index]->deselectPenguin();      
         if ( !myPlayers[index]->canMove() )
         {
            myRoundCount++;
            if ( !hasPlayerAttacked )
            {
               myRoundCountSinceAttack++;
            }
            hasPlayerAttacked = false;
            myRoundText.setText( myRoundCount );
            myPlayerIndex = (myPlayerIndex + 1) % myPlayers.size();
            myPlayers[myPlayerIndex]->clearMoves();
         }
         // check for game over
      }
      if ( !myPlayers[index]->penguinIsAlive() )
      {
         state( State::RESET );
         window->loadLevel( (index == 0 ? 3 : 2) );
         return;
      }
   }
   resolveCollisions();
   
   if ( myRoundCountSinceAttack >= 10 )
   {
      state( State::RESET );
      window->loadLevel( 4 );
   }


   //myPlayer.resolveCollisions( levelRef );


   // start rendering
   if ( SUCCEEDED(window->device()->BeginScene()) )
   {
      if ( SUCCEEDED(window->spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
         // sprite rendering...       
         myLevelBgnds.drawMySpriteMap( window->spriteInterface() );
         for ( unsigned int index = 0; index < myPlayers.size(); index ++ )
         {
            myPlayers[index]->draw( window->spriteInterface() );
            myGUIs[index]->draw( window->spriteInterface() );
         }
         
         myMoveText.draw( window->spriteInterface() );
         myRoundText.draw( window->spriteInterface() );
         
         // stop rendering
         window->spriteInterface()->End();
      }

      // End rendering:
      window->device()->EndScene();
      window->device()->Present( NULL, NULL, NULL, NULL );
   }
}

//=======================================================================
void GameRun::reset ( Game* window )
{ 
   myRoundCount = 0; 
   myRoundCountSinceAttack = 0; 
   hasPlayerAttacked = false;
   shutdown(window);
   init(window);
}

//=======================================================================
void GameRun::shutdown ( Game* window )
{
   myMoveText.destroy();
   myRoundText.destroy();
   for ( unsigned int index = 0; index < myPlayers.size(); index++ )
   {
      myPlayers[index]->shutdown();
      delete myPlayers[index];
      myPlayers[index] = NULL;
   }
   for ( unsigned int index = 0; index < myGUIs.size(); index++ )
   {
      myGUIs[index]->destroy();
      delete myGUIs[index];
      myGUIs[index] = NULL;
   }
   myPlayers.clear();
   myGUIs.clear();
   myLevelBgnds.shutdown();
}

