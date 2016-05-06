
#include "stdafx.h"
#include "DxWrapper/DxAssetManager.h"
#include "Atomic Penguin SmackDown/Atomic Penguin SmackDown.h"
#include "Atomic Penguin SmackDown/GameGreenVictory.h"


bool GameGreenVictory::init (Game* window)
{
  
   greenVictory.create("GREENVICTORY");
    bool result = true;

    return result;
}

void GameGreenVictory::run (Game* window)
{
   
   if ( SUCCEEDED (window->device()->BeginScene()) )
   {
      if ( SUCCEEDED(window->spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
            greenVictory.draw( window->spriteInterface() );
      }

      window->spriteInterface()->End();
   }

}

void GameGreenVictory::shutdown (Game* window)
{
     greenVictory.destroy();
}