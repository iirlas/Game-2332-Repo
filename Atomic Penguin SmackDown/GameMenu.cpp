#include "stdafx.h"

#include "DxWrapper/DxKeyboard.h"
#include "Atomic Penguin SmackDown/Atomic Penguin SmackDown.h"
#include "Atomic Penguin SmackDown/GameMenu.h"

//=======================================================================
GameMenu::GameMenu ()
{
   state( State::INIT );
   myIndex = 0;
}

//=======================================================================
GameMenu::~GameMenu ()
{
}

//=======================================================================
bool GameMenu::init ( Game* window )
{
   bool result = true;

   result &= mySplash.create( "SPLASH" );
   result &= myStartText.create( window->fontInterface(), "Start", 380, 0, 100, 100 );
   result &= myQuitText.create( window->fontInterface(), "Quit", 380, 600, 100, 100 );


   state( State::RUN );

   return result;
}

//=======================================================================
void GameMenu::run ( Game* window )
{


   if ( DxKeyboard::keyPressed( VK_UP) && myIndex > 0 )
   {
      myIndex--;
   }

   if ( DxKeyboard::keyPressed( VK_DOWN ) && myIndex < 1 )
   {
      myIndex++;
   }

   if ( DxKeyboard::keyPressed( VK_RETURN )  )
   {
      switch ( myIndex )
      {
      case 0:
         window->loadNextLevel();
         break;
      case 1:
         window->quit();
         break;
      }
   }

   myStartText.setColor( ( myIndex == 0 ? D3DCOLOR_XRGB(255,0,0) : D3DCOLOR_XRGB(255,255,255) ) );
   myQuitText.setColor( ( myIndex == 1 ? D3DCOLOR_XRGB(255,0,0) : D3DCOLOR_XRGB(255,255,255) ) );


   // start rendering
   if ( SUCCEEDED(window->device()->BeginScene()) )
   {
      if ( SUCCEEDED(window->spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
         mySplash.draw( window->spriteInterface() );
         myStartText.draw( window->spriteInterface() );
         myQuitText.draw( window->spriteInterface() );

         // stop rendering
         window->spriteInterface()->End();
      }

      // End rendering:
      window->device()->EndScene();
      window->device()->Present( NULL, NULL, NULL, NULL );
   }
}

//=======================================================================
void GameMenu::shutdown ( Game* window )
{
   myStartText.destroy();
   myQuitText.destroy();
   mySplash.destroy();
}

