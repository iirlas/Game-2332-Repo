
#include "stdafx.h"
#include "DxWrapper/DxAssetManager.h"
#include "Atomic Penguin SmackDown/Atomic Penguin SmackDown.h"
#include "Atomic Penguin SmackDown/GameStalemate.h"


bool GameStalemate::init (Game* window)
{
   bool result = true;
   staleEnd.create("STALEMATE");
   state( State::RUN );
   return result;

}

void GameStalemate::run (Game* window)
{
   if ( DxKeyboard::keyPressed( VK_RETURN ) )
   {
      window->loadLevel( 0 );
   }

   if ( SUCCEEDED (window->device()->BeginScene()) )
   {
      if ( SUCCEEDED(window->spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
         staleEnd.draw( window->spriteInterface() );
         window->spriteInterface()->End();
      }

      window->device()->EndScene();
      window->device()->Present( NULL, NULL, NULL, NULL );
   }

}

void GameStalemate::shutdown (Game* window)
{
   staleEnd.destroy();
}