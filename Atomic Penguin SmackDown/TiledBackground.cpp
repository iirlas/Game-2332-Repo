

#include "stdafx.h"
#include <cassert>
#include "Utilities/Point.h"
#include "Utilities/Rect.h"
#include "Utilities/ConfigParser.h"
#include "Atomic Penguin SmackDown/TiledBackground.h"
#include "Atomic Penguin SmackDown/TileDescParser.h"



//===================================================================================================>
//
//===================================================================================================>
//
TiledBackground::TiledBackground()
{
   myNumTilesVert = 
      myNumTilesHoriz = 0;
   myDevice = NULL;
}

//===================================================================================================>
//
TiledBackground::~TiledBackground()
{
   shutdown();
}

//===================================================================================================>
//
bool TiledBackground::init ( IDXDEVICE device, const tstring& configFilename )
{
   myDevice = device;
   device->AddRef();

   DxAssetManager& assetManager = DxAssetManager::getInstance();

   bool b = buildBackground( configFilename );


   //TODO:    FIX FOR WIN 8 and 10
      // The RENDER_TARGET mechanism is not working.
      // The test below proves it, it uses NO render target, and draws perfectly.
      // however, if changed to .create( dev, fn, rect, RENDER_TARGET ) version, it creates a render target
      //    AND DOES NOT WORK IN WIN8
 



   //RECT junk = { 0,0, 800,576 };
   //HRESULT result = myTestTexture.create( myDevice, 
   //                                        DxAssetManager::getInstance().getConfigAssetPath(_T("SCOTTS_TEST.png")), 
   //                                        D3DCOLOR_XRGB( 243,242,241), NULL );



   return b;
}


//===================================================================================================>
//
bool TiledBackground::buildBackground ( const tstring& configFilename )
{
   TileDescParser fileInfo;
   bool result = true;

   if ( !fileInfo.init( myDevice, configFilename ) )
   {
      assert(false);
      return false;
   }

   myNumTilesVert = fileInfo.numTileRows();
   myNumTilesHoriz = fileInfo.numTileCols();

   mySpriteMap.resize( myNumTilesVert * myNumTilesHoriz );
      
   //int bgWidth  = fileInfo.getTilePixWidth() * myNumTilesHoriz;
   //int bgHeight = fileInfo.getTilePixHeight() * myNumTilesVert;



   //SAS: NOTE: Windows 8 is not working, windows 10, either.
   //     But works fine one Win7.
   //     It's got to do with this create.
   //     The texture created here DOES NOT WORK regardless whether it is done from tiles or a simple file load.
   //     BUT it DOES work on Win8 if we create a straight texture 
   //
   //     Sunday - More information.
   //     I've installed VS2008, SP1, DirectX Jun2010, SVN, Winmerge;
   //     All on a clean Windows 10 Professional installation, running in a VMWare virtual machine,
   //     *** THE BACKGROUND DRAWS PERFECTLY ***
   //     I think that if you're having problems on your own machines... you should look a bit closer at your installation,
   //     particularly, reinstall the DirectX_2010, check DxDiag and your video drivers, and get rid of the TONS of bloatware.
   //     But... it's now verifiably WORKING on a machine that isn't totally overrun with bloat, so it's on YOU to isolate 
   //     the problem.
   //     

   //result = myTiledBgTexture.create( myDevice, bgWidth, bgHeight, D3DUSAGE_RENDERTARGET );
   //RECT junk = { 0,0, 800, 576 };
   //result = myTiledBgTexture.create( myDevice, 
   //                                  DxAssetManager::getInstance().getConfigAssetPath(_T("SCOTTS_TEST.png")), 
   //                                  junk, 
   //                                  D3DUSAGE_RENDERTARGET );


   //assert(result); //todo


   int index = 0;

   int tilePixWidth  = fileInfo.getTilePixWidth();
   int tilePixHeight = fileInfo.getTilePixHeight();

   for (int row = 0; row < fileInfo.numTileRows(); row++)
   {
      for (int col = 0; col < fileInfo.numTileCols(); col++)
      {
         //RECT dstRect = { xPos, yPos, tilePixWidth+xPos, tilePixHeight+yPos };

         //DxTexture& srcTileTexture = fileInfo.getTileTexture(row,col);

         //srcTileTexture.stretchRect( myDevice, NULL, myTiledBgTexture, &dstRect );

         int xPos = col*tilePixWidth;
         int yPos = row*tilePixHeight; 

         mySpriteMap[index].setScale( .25, .25 );

         if(  fileInfo.getTileType( row, col ) == _T("GROUND") )
         {
            mySpriteMap[index].create( "GROUND" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE") )
         {
            mySpriteMap[index].create( "ICE" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SNOW") )
         {
            mySpriteMap[index].create( "SNOW" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIME") )
         {
            mySpriteMap[index].create( "SLIME" );
            mySpriteMap[index].collidable(false);
         }
         else if ( fileInfo.getTileType( row, col ) == _T("ROCK") )
         {
            mySpriteMap[index].create( "ROCK" );
            //Point pos( (LONG)xPos, (LONG)yPos );
            //mySpriteMap[index].setCollisionArea(Rect( pos, tilePixWidth, tilePixHeight ) );
            mySpriteMap[index].setDestroyable ( false );
         }
         else
         {
            mySpriteMap[index].create( "WATER" );
            mySpriteMap[index].setDestroyable(false);
         }
         
         mySpriteMap[index].setPosition( float(xPos), float(yPos) );

         index++;
      }
   }


   return true;
}
//===================================================================================================>
//
TiledBackground::TileType TiledBackground::getTileEnumType( const tstring& label )
{
   if( label == "GROUND")
   {
      return GROUND;
   }

   if( label == "ICE" )
   {
      return ICE;
   }
    if( label == "SLIME" )
   {
      return SLIME;
   }
    if( label == "SNOW" )
   {
      return SNOW;
   }
   if( label == "ROCK" )
   {
      return ROCK;
   }

   assert(false);
   return TileType(-1);
}


//===================================================================================================>
//
bool TiledBackground::tileIsCollidable( TiledBackground::TileType tileEnumType )
{
   switch( tileEnumType )
   {
      //List non collidable tile names here
   case GROUND:
   case ICE:
   case SNOW:
   case SLIME:
      return false;     
      break;
      //List colidable tile names here
   case ROCK:
   case WATER:
      return true;
   default:
      return true;
      break;
   }
   return true;
}



//===================================================================================================>
//
bool TiledBackground::update ( )
{
   return true;
}



//===================================================================================================>
//
void TiledBackground::shutdown ( )
{
   if ( myDevice )
   {
      myDevice->Release();    // Utilities::ifRelease( myDevice );
      myDevice = NULL;
   }
}


//===================================================================================================>
//
bool TiledBackground::draw( IDXSURFACE dstSurface, const RECT* dstRect )
{

   //todo sas - not quite right, just yet.  This should NOT stretch to the dstSurface's full size
   //           so... if dstRect isn't given... fool it into drawing in same aspect as srcSurface
   
   RECT srcRect = { 0, 0, myTiledBgTexture.width(), myTiledBgTexture.height() };

   if (dstRect == NULL) 
      dstRect = &srcRect;

   RECT dRect = *dstRect;

   //todo: this isn't right.  limit to min's.
   dRect.bottom = min( dRect.bottom, srcRect.bottom );
   dRect.right  = min( dRect.right, srcRect.right);


   HRESULT hr = -1;  //myDevice->StretchRect( myTiledBgSurface, NULL, dstSurface, &dRect, D3DTEXF_NONE );


   return SUCCEEDED( hr );  //TODO
}
//===================================================================================================>
//
bool TiledBackground::draw ( IDXSPRITE spriteobj, const RECT* dstRect )
{

   //todo sas - not quite right, just yet.  This should NOT stretch to the dstSurface's full size
   //           so... if dstRect isn't given... fool it into drawing in same aspect as srcSurface
   
   RECT srcRect = { 0, 0, myTiledBgTexture.width(), myTiledBgTexture.height() };

   if (dstRect == NULL) 
      dstRect = &srcRect;

   RECT dRect = *dstRect;

   //todo: this isn't right.  limit to min's.
   dRect.bottom = min( dRect.bottom, srcRect.bottom );
   dRect.right  = min( dRect.right, srcRect.right);


   //HRESULT hr = myDevice->StretchRect( myTiledBgSurface, NULL, dstSurface, &dRect, D3DTEXF_NONE );
   //HRESULT hr = spriteobj->Draw( myTiledBgTexture, NULL, NULL );
   
   
   
   //TODO: Need to change locations
   D3DXVECTOR3 vPos( 0, 0, 0 );
   HRESULT hr = myTiledBgTexture.draw( spriteobj, &vPos, D3DCOLOR_XRGB(255,255,255), &dRect );
   
   //drawMySpriteMap( spriteobj );

   return SUCCEEDED( hr );  //TODO
}

bool TiledBackground::drawMySpriteMap( IDXSPRITE spriteobj )
{
   for( size_t i = 0; i < mySpriteMap.size(); i++ )
   {
      mySpriteMap[i].draw( spriteobj );
   }

   return true;
}