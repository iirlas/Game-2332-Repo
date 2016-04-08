#include "stdafx.h"

#include "Utilities/TTypes.h"
#include "Utilities/PathUtilities.h"
#include "Utilities/ConfigParser.h"
#include "Atomic Penguin SmackDown/TileDescParser.h"

//===================================================================================================>
//
TileDescParser::TileDescParser()
{
   myLevelTileDescrs = NULL;
}

//===================================================================================================>
//
TileDescParser::~TileDescParser()
{
   shutdown();
}

//===================================================================================================>
//
bool TileDescParser::init ( IDXDEVICE device, const tstring& configFilename )
{
   bool b = parseLevelConfig( device, configFilename );
   return b;
}


//===================================================================================================>
//

bool TileDescParser::parseLevelConfig ( IDXDEVICE device, const tstring& configFilename )
{
   TCHAR state = _T('\0');
   const TCHAR* whitespace = _T(" \t\n\r\b\v" );
   const TCHAR  sectionChar = _T('@');


   struct SourceTileDescr 
   {
      tstring     label;
      int         idNum;
      int         xPos, yPos, pixWidth, pixHeight;
      DxTexture   texture;
   };
   std::map<int, SourceTileDescr>  srcTileDescrMap;



   myFilePath = DxAssetManager::getInstance().getConfigAssetPath( configFilename );
   tifstream      configFile( myFilePath.c_str() );
   DWORD gle = GetLastError();

   if ( !configFile.is_open() || configFile.bad() )
   {
      // Print GLE, Print log message, fail.
      assert( false );
      return false;
   }

   ConfigParser   parser;
   tstring        line, verb, arg;

   //--------- Parse @FILE <filename>
   if ( !parser.getNextLine( configFile, line ) ) 
      return false;
   if ( !parser.parsePairString( line, verb, arg ) )
      return false;

   myImageFilePath = DxAssetManager::getInstance().getConfigAssetPath( arg );
   tstring imageName( myImageFilePath );
   PathUtilities::pathStripPath( imageName );
   DxTexture* bigImage = DxAssetManager::getInstance().getTexture( imageName );

   
   //-------- Parse @TILES: n instances of "label idNum"
   //if ( !parser.getNextLine( configFile, line ) ) 
   //   return false;  //todo
   if ( !parser.getNextLine( configFile, line ) ) 
      return false;  //todo
   if ( line.find( "@TILES" ) == tstring::npos )
      return false;  //todo

   while ( parser.getNextLine( configFile, line ) && (line[0] != sectionChar) )
   {
      // line is in form "label idNum x y w h"  the {x y w h} part is TO BE REMOVED
      tstringstream ss( line );
      int      idNum, x, y, w, h;
      tstring  label;

      ss >> label >> idNum >> x >> y >> w >> h;
      if ( ss.fail() )
         return false;

      SourceTileDescr srcDescr;

      srcDescr.idNum     = idNum;
      srcDescr.label     = label;
      srcDescr.xPos      = x; 
      srcDescr.yPos      = y; 
      srcDescr.pixWidth  = w; 
      srcDescr.pixHeight = h; 

      Rect  srcRect( x, y, x+w, y+h );
      bool result = srcDescr.texture.create( device, w, h, D3DUSAGE_RENDERTARGET );
      bigImage->stretchRect( DxWrapper::device(), &srcRect, srcDescr.texture, NULL );

      srcDescr.texture.name( label );
      assert( result );

      srcTileDescrMap[idNum] = srcDescr;
   }


   // Exits above loop when it finds "@" (sectionChar) if all is well
   // so we should be on @DIMENSIONS mapWidth mapHeight tileWidth tileHeight
   myNumTilesHoriz = myNumTilesVert = myTileWidth = myTileHeight = 0;
   if ( line.find( _T("@DIMENSIONS") == 0 ) )
   {
      tstringstream ss( line );

      ss >> verb >> myNumTilesHoriz >> myNumTilesVert >> myTileWidth >> myTileHeight;
      if ( ss.fail() )
         return false;
   }
   else
   {
      return false; //todo - something wrong
   }


   // Finally, next section should be @LEVELMAP, so - if we're doing the work here... time to setup the surfaces

   //result = mySpriteSheet.create( myDevice, myImageFilePath, 0 );
   //assert( result );

   // compute bg size
   int numTiles   = myNumTilesHoriz * myNumTilesVert;
   myLevelTileDescrs = new BgTileDescr[ numTiles ];

   if ( !parser.getNextLine( configFile, line ) ) 
      return false;  //todo
   if ( line != _T("@LEVELMAP") )
      return false;  //todo

   // for each row....
   for ( int row = 0; row < myNumTilesVert; row++ )
   {
      if ( !parser.getNextLine( configFile, line ) ) 
         assert( false );

      tstringstream ss( line );

      for ( int col = 0; col < myNumTilesHoriz; col++ )
      {
         int idNum;

         ss >> idNum;
         if ( ss.fail() )
            assert( false );

         DxTexture& texture = srcTileDescrMap[idNum].texture;
         tstring&   label   = srcTileDescrMap[idNum].label;
         BgTileDescr& descr = getDescr(row,col);

         descr.label    = label;
         descr.texture  = texture;
               
      }
   }


   return true;
}


//===================================================================================================>
//
tstring TileDescParser::getTileType (int row, int col) 
{

   return getDescr(row,col).label;
}
//===================================================================================================>
//
DxTexture& TileDescParser::getTileTexture (int row, int col) 
{

   return getDescr(row,col).texture;
}

//===================================================================================================>
//
TileDescParser::BgTileDescr& TileDescParser::getDescr ( int row, int col )
{
   //TODO: DO VALIDATION ON ROW COL HERE
   int li = (row * myNumTilesHoriz) + col;
   return myLevelTileDescrs[li];
}

//===================================================================================================>
//
void TileDescParser::shutdown ( )
{
   delete [] myLevelTileDescrs;
   myLevelTileDescrs = NULL;
}
