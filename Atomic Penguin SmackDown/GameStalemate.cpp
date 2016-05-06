
#include "stdafx.h"
#include "DxWrapper/DxAssetManager.h"
#include "Atomic Penguin SmackDown/Atomic Penguin SmackDown.h"
#include "Atomic Penguin SmackDown/GameStalemate.h"


bool GameStalemate::init (Game* window)
{
   bool result = true;
   staleEnd.create("STALEMATE");

   return result;

}

void GameStalemate::run (Game* window)
{
   
   if ( SUCCEEDED (window->device()->BeginScene()) )
   {
      if ( SUCCEEDED(window->spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
            staleEnd.draw( window->spriteInterface() );
      }

      window->spriteInterface()->End();
   }

}

void GameStalemate::shutdown (Game* window)
{
     staleEnd.destroy();
}