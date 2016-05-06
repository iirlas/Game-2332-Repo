
#include "stdafx.h"
#include "DxWrapper/DxAssetManager.h"
#include "Atomic Penguin SmackDown/Atomic Penguin SmackDown.h"
#include "Atomic Penguin SmackDown/GameBlueVictory.h"


bool GameBlueVictory::init (Game* window)
{
   bool result = true;
   blueVictory.create("BLUEVICTORY");
   state( State::RUN );

   return result;

}

void GameBlueVictory::run (Game* window)
{
   if ( DxKeyboard::keyPressed( VK_RETURN ) )
   {
      window->loadLevel( 0 );
   }

   if ( SUCCEEDED (window->device()->BeginScene()) )
   {
      if ( SUCCEEDED(window->spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
         blueVictory.draw( window->spriteInterface() );
         window->spriteInterface()->End();
      }

      window->device()->EndScene();
      window->device()->Present( NULL, NULL, NULL, NULL );
   }
}

void GameBlueVictory::shutdown (Game* window)
{
   blueVictory.destroy();
}