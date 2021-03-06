#pragma once

#if !defined( _TILEDBACKGROUND_H_ )
#define _TILEDBACKGROUND_H_


#include "DxWrapper\DxWrapper.h"
#include "DxWrapper/DxCommon.h"
#include "Utilities\Logger.h"
#include "WinWrapper/Application.h"
#include "DxWrapper\DxSurface.h"
#include "DxWrapper\DxTexture.h"
#include "DxWrapper/DxAnimationInfo.h"
#include "DxWrapper/DxAssetManager.h"
#include "DxWrapper/DxAnimation.h"
#include "DxWrapper/DxGameSprite.h"
#include "Utilities/Point.h"
#include "Atomic Penguin SmackDown/Penguin.h"
#include "Atomic Penguin SmackDown/Tile.h"


//===================================================================================================
// This things purpose...
//    Opens a spriteSheet (by name?)
//    Loads a description of tile distribution (by name?)
//    Generates a tiled background, as a texture 
//    Provides access to the tiled background for use by gameRun
//    OR draws the background...
class TiledBackground
{
public:
   TiledBackground();
  ~TiledBackground();

   bool init ( IDXDEVICE dev, const tstring& bgConfigFilename );
   bool update ();
   void shutdown ();

   bool draw ( IDXSURFACE dstSurface, const RECT* dstRect = NULL );
   bool draw ( IDXSPRITE spriteobj, const RECT* dstRect = NULL );

   bool drawMySpriteMap( IDXSPRITE spriteObj );

   RECT getMyBgSrcRect();
   int numColumns () const { return myNumTilesHoriz; }
   int numRows () const { return myNumTilesVert; }

   int tileWidth () const { return myTileWidth; }
   int tileHeight () const { return myTileHeight; }

   inline Tile* tileAt ( int column, int row )
   {
      if ( column < 0 || column >= myNumTilesHoriz || 
           row < 0    || row >= myNumTilesVert )
           return NULL;
      unsigned int index = column + row * myNumTilesHoriz;
      if ( index < mySpriteMap.size() )
         return &mySpriteMap[index];
      return NULL;
   }

   inline Tile* tileAt ( float x, float y, float width, float height )
   {
      return tileAt( (int)(x/width), (int)(y/height) );
   }

   inline Tile* tileAt ( Penguin& penguin )
   {
      return tileAt( (float)penguin.x(),(float)penguin.y(), (float)penguin.width(), (float)penguin.height() );
   }

   std::vector<Tile> mySpriteMap;
   
private:
   void scrollScreen( IDXSURFACE backBuf );
   bool buildBackground ( const tstring& configFilename );

private:
   IDXDEVICE      myDevice;            //todo  need means to get this from framework...
   DxTexture      mySpriteSheet;
   DxTexture      myTiledBgTexture, myTestTexture;
   tstring        myFilePath;
   tstring        myImageFilePath;
   DxGameSprite   mySprite;

   int         myTileWidth, myTileHeight;    // Actual size rqrd in the tiled bg, NOT image width/height
   int         myNumTilesHoriz, myNumTilesVert;

   RECT        myBgSrcRect;
   int         myBgWidth, myBgHeight;

   struct TileDescr 
   {
      tstring     label;
      int         idNum;
      int         xPos, yPos, pixWidth, pixHeight;
   };

   

   



private:

};


#endif //_TILEDBACKGROUND_H_