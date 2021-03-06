
#include "stdafx.h"
#include "DxWrapper/DxAssetManager.h"
#include "Atomic Penguin SmackDown/Atomic Penguin SmackDown.h"
#include "Atomic Penguin SmackDown/GameGreenVictory.h"


bool GameGreenVictory::init (Game* window)
{
   bool result = true;
   greenVictory.create("GREENVICTORY");
   state( State::RUN );

   return result;
}

void GameGreenVictory::run (Game* window)
{
   if ( DxKeyboard::keyPressed( VK_RETURN ) )
   {
      window->loadInterface( "Menu", GameInterface::RUN );
   }

   if ( SUCCEEDED (window->device()->BeginScene()) )
   {
      if ( SUCCEEDED(window->spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
         greenVictory.draw( window->spriteInterface() );
         window->spriteInterface()->End();
      }

      window->device()->EndScene();
      window->device()->Present( NULL, NULL, NULL, NULL );
   }

}

void GameGreenVictory::shutdown (Game* window)
{
   greenVictory.destroy();
}