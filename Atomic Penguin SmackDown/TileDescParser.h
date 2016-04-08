#pragma once

#if !defined( _TILEDESCPARSER_H_ )
#define _TILEDESCPARSER_H_


#include "WinWrapper/Application.h"
#include "DxWrapper/DxWrapper.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper\DxSurface.h"
#include "DxWrapper\DxTexture.h"
#include "DxWrapper/DxAnimationInfo.h"
#include "DxWrapper/DxAssetManager.h"
#include "DxWrapper/DxAnimation.h"
#include "Utilities/Logger.h"
#include "Utilities/Point.h"

class TileDescParser 
{
public:
   TileDescParser();
  ~TileDescParser();

   struct BgTileDescr 
   {
      tstring     label;
      DxTexture   texture;
      // Do we NEED anything else here... not right now... 
      // We *could* put pixWidth,pixHeight - which would allow the bg tiles to be *any* size
      // and we *could* put xPos,yPos - but I think the Level would really be more likely to
      // *calculate* these based on the tile's logical position (row,col) and height,width
   };

   bool init ( IDXDEVICE device, const tstring& bgConfigFilename );
   void shutdown ();

   tstring sourceFilename ( ) const { return myImageFilePath; }
   int numTileCols ( )        const { return myNumTilesHoriz; }
   int numTileRows ( )        const { return myNumTilesVert; }
   int getTilePixWidth  ( )   const { return myTileWidth; }
   int getTilePixHeight ( )   const { return myTileHeight; }
   tstring getTileType ( int row, int col );
   DxTexture& getTileTexture ( int row, int col );
   
private:
   bool parseLevelConfig ( IDXDEVICE device, const tstring& configFilename );
   BgTileDescr&  getDescr ( int row, int col );

private:
   tstring     myFilePath;
   tstring     myImageFilePath;

   int         myTileWidth, myTileHeight;       // Actual size rqrd in the tiled bg, NOT image width/height
   int         myNumTilesHoriz, myNumTilesVert;

   BgTileDescr*  myLevelTileDescrs;
   

};


#endif 
