#include "stdafx.h"
#include <cassert>
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
      tstring     skin;
      int         idNum;
      int         type;
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
      int  idNum, type;
      tstring skin;

      ss >> skin >> idNum >> type;
      if ( ss.fail() )
         return false;

      SourceTileDescr srcDescr;
      
      srcDescr.skin    = skin;
      srcDescr.idNum    = idNum;
      srcDescr.type     = type;

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

         tstring& skin = srcTileDescrMap[idNum].skin;
         int&     type = srcTileDescrMap[idNum].type;

         BgTileDescr& descr = getDescr(row,col);
         descr.skin = skin;
         descr.type = type;
         descr.idNum = idNum;
      }
   }


   return true;
}

//===================================================================================================>
//
tstring TileDescParser::getTileSkin (int row, int col) 
{

   return getDescr(row,col).skin;
}


//===================================================================================================>
//
int TileDescParser::getTileType (int row, int col) 
{

   return getDescr(row,col).type;
}


//===================================================================================================>
//
int TileDescParser::getTileID (int row, int col) 
{

   return getDescr(row,col).idNum;
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
