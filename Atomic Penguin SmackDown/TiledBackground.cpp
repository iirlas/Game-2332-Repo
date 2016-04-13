

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

         mySpriteMap[index].setScale( .5, .5 );

         if(  fileInfo.getTileType( row, col ) == _T("GROUND") )
         {
            mySpriteMap[index].create( "GROUND" );
            mySpriteMap[index].collidable(false);
         }
          else if(  fileInfo.getTileType( row, col ) == _T("GROUND-BORDERED") )
         {
            mySpriteMap[index].create( "GROUND-BORDERED" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("GROUND-BOTTOM") )
         {
            mySpriteMap[index].create( "GROUND-BOTTOM" );
            mySpriteMap[index].collidable(false);
         }
          else if(  fileInfo.getTileType( row, col ) == _T("GROUND-TOP") )
         {
            mySpriteMap[index].create( "GROUND-TOP" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("GROUND-LEFT") )
         {
            mySpriteMap[index].create( "GROUND-LEFT" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("GROUND-RIGHT") )
         {
            mySpriteMap[index].create( "GROUND-RIGHT" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("GROUND-CORNERTL") )
         {
            mySpriteMap[index].create( "GROUND-CORNERTL" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("GROUND-CORNERTR") )
         {
            mySpriteMap[index].create( "GROUND-CORNERTR" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("GROUND-CORNERBL") )
         {
            mySpriteMap[index].create( "GROUND-CORNERBL" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("GROUND-CORNERBR") )
         {
            mySpriteMap[index].create( "GROUND-CORNERBR" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("GROUND-INLETTOP") )
         {
            mySpriteMap[index].create( "GROUND-INLETTOP" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("GROUND-INLETBOTTOM") )
         {
            mySpriteMap[index].create( "GROUND-INLETBOTTOM" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("GROUND-INLETLEFT") )
         {
            mySpriteMap[index].create( "GROUND-INLETLEFT" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("GROUND-INLETRIGHT") )
         {
            mySpriteMap[index].create( "GROUND-INLETRIGHT" );
            mySpriteMap[index].collidable(false);
         }




         else if(  fileInfo.getTileType( row, col ) == _T("ICE") )
         {
            mySpriteMap[index].create( "ICE" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-BORDERED") )
         {
            mySpriteMap[index].create( "ICE-BORDERED" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-BOTTOM") )
         {
            mySpriteMap[index].create( "ICE-BOTTOM" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-TOP") )
         {
            mySpriteMap[index].create( "ICE-TOP" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-LEFT") )
         {
            mySpriteMap[index].create( "ICE-LEFT" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-RIGHT") )
         {
            mySpriteMap[index].create( "ICE-RIGHT" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-CORNERTL") )
         {
            mySpriteMap[index].create( "ICE-CORNERTL" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-CORNERTR") )
         {
            mySpriteMap[index].create( "ICE-CORNERTR" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-CORNERBL") )
         {
            mySpriteMap[index].create( "ICE-CORNERBL" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-CORNERBR") )
         {
            mySpriteMap[index].create( "ICE-CORNERBR" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-INLETTOP") )
         {
            mySpriteMap[index].create( "ICE-INLETTOP" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-INLETBOTTOM") )
         {
            mySpriteMap[index].create( "ICE-INLETBOTTOM" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-INLETLEFT") )
         {
            mySpriteMap[index].create( "ICE-INLETLEFT" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("ICE-INLETRIGHT") )
         {
            mySpriteMap[index].create( "ICE-INLETRIGHT" );
            mySpriteMap[index].collidable(false);
         }



         else if(  fileInfo.getTileType( row, col ) == _T("SLIME") )
         {
            mySpriteMap[index].create( "SLIME" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIMEBORDERED") )
         {
            mySpriteMap[index].create( "SLIMEBORDERED" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIMEBOTTOM") )
         {
            mySpriteMap[index].create( "SLIMEBOTTOM" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIMETOP") )
         {
            mySpriteMap[index].create( "SLIMETOP" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIMELEFT") )
         {
            mySpriteMap[index].create( "SLIMELEFT" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIME-RIGHT") )
         {
            mySpriteMap[index].create( "SLIME-RIGHT" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIME-CORNERTL") )
         {
            mySpriteMap[index].create( "SLIME-CORNERTL" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIME-CORNERTR") )
         {
            mySpriteMap[index].create( "SLIME-CORNERTR" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIME-CORNERBL") )
         {
            mySpriteMap[index].create( "SLIME-CORNERBL" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIME-CORNERBR") )
         {
            mySpriteMap[index].create( "SLIME-CORNERBR" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIME-INLETTOP") )
         {
            mySpriteMap[index].create( "SLIME-INLETTOP" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIME-INLETBOTTOM") )
         {
            mySpriteMap[index].create( "SLIME-INLETBOTTOM" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIME-INLETLEFT") )
         {
            mySpriteMap[index].create( "SLIME-INLETLEFT" );
            mySpriteMap[index].collidable(false);
         }
         else if(  fileInfo.getTileType( row, col ) == _T("SLIME-INLETRIGHT") )
         {
            mySpriteMap[index].create( "SLIME-INLETRIGHT" );
            mySpriteMap[index].collidable(false);
         }
         
         
         else if(  fileInfo.getTileType( row, col ) == _T("SNOW") )
         {
            mySpriteMap[index].create( "SNOW" );
            mySpriteMap[index].collidable(false);
         }
         


         else if ( fileInfo.getTileType( row, col ) == _T("ROCK") )
         {
            mySpriteMap[index].create( "ROCK" );
            mySpriteMap[index].setDestroyable ( false );
         }
         else if ( fileInfo.getTileType( row, col ) == _T("ROCK-GROUND2") )
         {
            mySpriteMap[index].create( "ROCK-GROUND2" );
            mySpriteMap[index].setDestroyable ( false );
         }
         else if ( fileInfo.getTileType( row, col ) == _T("ROCK-GROUND3") )
         {
            mySpriteMap[index].create( "ROCK-GROUND3" );
            mySpriteMap[index].setDestroyable ( false );
         }
         else if ( fileInfo.getTileType( row, col ) == _T("ROCK-SNOW1") )
         {
            mySpriteMap[index].create( "ROCK-SNOW1" );
            mySpriteMap[index].setDestroyable ( false );
         }
         else if ( fileInfo.getTileType( row, col ) == _T("ROCK-SNOW2") )
         {
            mySpriteMap[index].create( "ROCK-SNOW2" );
            mySpriteMap[index].setDestroyable ( false );
         }
         else if ( fileInfo.getTileType( row, col ) == _T("ROCK-SNOW3") )
         {
            mySpriteMap[index].create( "ROCK-SNOW3" );
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

   if( label == "GROUND-BORDERED")
   {
      return GROUNDBORDERED;
   }
   if( label == "GROUND-BOTTOM")
   {
      return GROUNDBOTTOM;
   }
   if( label == "GROUND-TOP")
   {
      return GROUNDTOP;
   }
   if( label == "GROUND-LEFT")
   {
      return GROUNDLEFT;
   }
   if( label == "GROUND-RIGHT")
   {
      return GROUNDRIGHT;
   }
   if( label == "GROUND-CORNETL")
   {
      return GROUNDCORNERTL;
   }
   if( label == "GROUND-CORNERTR")
   {
      return GROUNDCORNERTR;
   }
   if( label == "GROUND-CORNERBL")
   {
      return GROUNDCORNERBL;
   if( label == "GROUND-CORNERBR")
   {
      return GROUNDCORNERBR;
   }
   }
      if( label == "GROUND-INLETTOP")
   {
      return GROUNDINLETTOP;
   }
      if( label == "GROUND-INLETBOTTOM")
   {
      return GROUNDINLETBOTTOM;
   }
      if( label == "GROUND-INLETLEFT")
   {
      return GROUNDINLETLEFT;
   }
      if( label == "GROUND-INLETRIGHT")
   {
      return GROUNDINLETRIGHT;
   }


   if( label == "ICE" )
   {
      return ICE;
   }
   if( label == "ICE-BORDERED" )
   {
      return ICEBORDERED;
   }
   if( label == "ICE-BOTTOM" )
   {
      return ICEBOTTOM;
   }
   if( label == "ICE-TOP" )
   {
      return ICETOP;
   }
   if( label == "ICE-LEFT" )
   {
      return ICELEFT;
   }
   if( label == "ICE-RIGHT" )
   {
      return ICERIGHT;
   }
   if( label == "ICE-CORNERTL" )
   {
      return ICECORNERTL;
   }
   if( label == "ICE-CORNERTR" )
   {
      return ICECORNERTR;
   }
   if( label == "ICE-CORNERBL" )
   {
      return ICECORNERBL;
   }
   if( label == "ICE-CORNERBR" )
   {
      return ICECORNERBR;
   }
   if( label == "ICE-INLETTOP" )
   {
      return ICEINLETTOP;
   }
   if( label == "ICE-INLETBOTTOM" )
   {
      return ICEINLETBOTTOM;
   }
   if( label == "ICE-INLETLEFT" )
   {
      return ICEINLETLEFT;
   }
   if( label == "ICE-INLETRIGHT" )
   {
      return ICEINLETRIGHT;
   }



    if( label == "SLIME" )
   {
      return SLIME;
   }
    if( label == "SLIMEBORDERED" )
   {
      return SLIMEBORDERED;
   }
    if( label == "SLIMEBOTTOM" )
   {
      return SLIMEBOTTOM;
   }
    if( label == "SLIMETOP" )
   {
      return SLIMETOP;
   }
    if( label == "SLIMELEFT" )
   {
      return SLIMELEFT;
   }
    if( label == "SLIME-RIGHT" )
   {
      return SLIMERIGHT;
   }
    if( label == "SLIME-CORNERTL" )
   {
      return SLIMECORNERTL;
   }
    if( label == "SLIME-CORNERTR" )
   {
      return SLIMECORNERTR;
   }
    if( label == "SLIME-CORNERBL" )
   {
      return SLIMECORNERBL;
   }
    if( label == "SLIME-CORNERBR" )
   {
      return SLIMECORNERBR;
   }
    if( label == "SLIME-INLETTOP" )
   {
      return SLIMEINLETTOP;
   }
    if( label == "SLIME-INLETBOTTOM" )
   {
      return SLIMEINLETBOTTOM;
   }
    if( label == "SLIME-INLETLEFT" )
   {
      return SLIMEINLETLEFT;
   }
    if( label == "SLIME-INLETRIGHT" )
   {
      return SLIMEINLETRIGHT;
   }




    if( label == "SNOW" )
   {
      return SNOW;
   }


   if( label == "ROCK" )
   {
      return ROCK;
   }
   if( label == "ROCK-GROUND2" )
   {
      return ROCKGROUND2;
   }
   if( label == "ROCK-GROUND3" )
   {
      return ROCKGROUND3;
   }
   if( label == "ROCK-SNOW1" )
   {
      return ROCKSNOW1;
   }
   if( label == "ROCK-SNOW2" )
   {
      return ROCKSNOW2;
   }
   if( label == "ROCK-SNOW3" )
   {
      return ROCKSNOW3;
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
     case GROUNDBORDERED:
         case GROUNDBOTTOM:
            case GROUNDTOP:
               case GROUNDLEFT:
                  case GROUNDRIGHT:
                     case GROUNDCORNERTL:
                        case GROUNDCORNERTR:
                           case GROUNDCORNERBL:
                              case GROUNDCORNERBR:
                                 case GROUNDINLETTOP:
                                    case GROUNDINLETBOTTOM:
                                       case GROUNDINLETLEFT:
                                          case GROUNDINLETRIGHT:
   case ICE:
      case ICEBORDERED:
         case ICEBOTTOM:
            case ICETOP:
               case ICELEFT:
                  case ICERIGHT:
                     case ICECORNERTL:
                        case ICECORNERTR:
                           case ICECORNERBL:
                              case ICECORNERBR:
                                 case ICEINLETTOP:
                                    case ICEINLETBOTTOM:
                                       case ICEINLETLEFT:
                                          case ICEINLETRIGHT:

   
   case SLIME:
      case SLIMEBORDERED:
         case SLIMEBOTTOM:
            case SLIMETOP:
               case SLIMELEFT:
                  case SLIMERIGHT:
                     case SLIMECORNERTL:
                        case SLIMECORNERTR:
                           case SLIMECORNERBL:
                              case SLIMECORNERBR:
                                 case SLIMEINLETTOP:
                                    case SLIMEINLETBOTTOM:
                                       case SLIMEINLETLEFT:
                                          case SLIMEINLETRIGHT:

   case SNOW:
      return false;     
      break;
      //List colidable tile names here
   case ROCK:
      case ROCKGROUND2:
         case ROCKGROUND3:
            case ROCKSNOW1:
               case ROCKSNOW2:
                  case ROCKSNOW3:
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