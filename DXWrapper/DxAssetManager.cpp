
#include "stdafx.h"
#include <stdio.h>
#include <assert.h>
#include "Utilities/Point.h"
#include "Utilities/Logger.h"
#include "Utilities/ConfigParser.h"
#include "Utilities/PathUtilities.h"
#include "Utilities/TStringRoutines.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/DxWrapper.h"
#include "DxWrapper/DxAssetManager.h"

//=======================================================================
//=======================================================================
template<typename AssetType>
struct DxAssetManager::Asset
{
   tstring name;
   AssetType asset;
};

//=======================================================================
//=======================================================================
struct DxAssetManager::RawAsset
{
   DxTexture* texture;
   tstring info;
};

//=======================================================================
//static
DxAssetManager& DxAssetManager::getInstance ()
{
   static DxAssetManager instance;
   return instance;
}

//=======================================================================
bool DxAssetManager::init ( const TCHAR* rootPath,  bool createRootAssetDir )
{
   DWORD gle;
   tstring assetDir;
   
   if ( rootPath )
   {
      if ( !PathUtilities::pathCanonicalize( assetDir, rootPath ) )
      {
         return false;
      }
   }
   else
   {
      TCHAR working_directory[MAX_PATH] = { 0 };
      if ( !(gle = GetCurrentDirectory( MAX_PATH, working_directory )) )
      {
         return false;
      }
      assetDir = working_directory;
      if ( !PathUtilities::pathAppend( assetDir, "Assets" ) )
      {
         return false;
      }
   }
   
   // "c:/.../Assets/Assets" should become "c:/.../Assets"


   if ( !PathUtilities::pathIsDirectory( assetDir ) )
   {
      if ( createRootAssetDir )
      {
         if ( !CreateDirectory( assetDir.c_str(), NULL ) )
         {
            return false;
         }
      }
      else
      {
         logln( "Unable to find specified Assets directory!" );
         return false;
      }
      return false;
   }

   myAssetPath = assetDir;
   if ( PathUtilities::pathIsDirectory( myAssetPath ) )
   {
      return true;
   }
   return false;
}

//=======================================================================
bool DxAssetManager::load ( const tstring& configFilename, bool build )
{
   tstring configFilepath = myAssetPath;
   
   // configfilename, absolute path vs relative path? 
   // check configfile is exists.
   PathUtilities::pathAppend( configFilepath, configFilename );
   if ( !PathUtilities::pathFileExists( configFilepath ) )  // relative path check
   {
      if ( PathUtilities::pathFileExists( configFilename ) )// absolute path check
      {
         configFilepath = configFilename;
      }
      else
      {
         logln( "Unable to find config file: [%s]!", configFilename.c_str() );
         return false;
      }
   }

   return parseConfig( configFilepath, build );
}


//=======================================================================
void DxAssetManager::shutdown ()
{
   unsigned int index = 0;
   for ( index = 0; index < myTextures.size(); index++ )
   {
      myTextures[index].asset.destroy();
   }
   for ( index = 0; index < mySurfaces.size(); index++ )
   {
      mySurfaces[index].asset.destroy();
   }
   for ( index = 0; index < myAnimations.size(); index++ )
   {
      myAnimations[index].asset.shutdown();
   }
} 

//=======================================================================
tstring DxAssetManager::getAssetPath ( const tstring& name )
{
   tstring filePath( myAssetPath );
   PathUtilities::pathAppend( filePath, name );
   return filePath;
}

//=======================================================================
tstring DxAssetManager::getConfigAssetPath ( const tstring& configFilename )
{
   return getAssetPath( configFilename ); //todo
}

//=======================================================================
tstring DxAssetManager::getSoundAssetPath ( const tstring& soundFilename )
{
   return getAssetPath( soundFilename ); //todo
}

//=======================================================================
DxTexture* DxAssetManager::getTexture ( const tstring& name )
{
   for ( unsigned int index = 0; index < myTextures.size(); index++ )
   {
      if ( myTextures[index].name == name )
      {
         return &myTextures[index].asset;
      }
   }
   RawAsset* asset = getAssetRaw( name );
   if ( asset && buildTexturetAsset( asset->info, asset->texture ) )
   {
      return getTexture( name );
   }
   else
   {
      logln( _T("Unable to find Texture:[%s]"), name.c_str() );
      assert(false);
   }
   return NULL;
}

//=======================================================================
DxSurface* DxAssetManager::getSurface ( const tstring& name )
{
   for ( unsigned int index = 0; index < mySurfaces.size(); index++ )
   {
      if ( mySurfaces[index].name == name )
      {
         return &mySurfaces[index].asset;
      }
   }
   RawAsset* asset = getAssetRaw( name );
   if ( asset && buildTexturetAsset( asset->info, asset->texture ) )
   {
      return getSurface( name );
   }
   else
   {
      logln( _T("Unable to find Surface:[%s]"), name.c_str() );
      assert(false);
   }
   return NULL;
}


//=======================================================================
DxAnimation* DxAssetManager::getAnimation ( const tstring& name )
{
   for ( unsigned int index = 0; index < myAnimations.size(); index++ )
   {
      if ( myAnimations[index].name == name )
      {
         return &myAnimations[index].asset;
      }
   }
   RawAsset* asset = getAssetRaw( name );
   if ( asset && buildTexturetAsset( asset->info, asset->texture ) )
   {
      return getAnimation( name );
   }
   else
   {
      logln( _T("Unable to find Animation:[%s]"), name.c_str() );
      assert(false);
   }
   return NULL;
}

//=======================================================================
DxAnimation DxAssetManager::getAnimationCopy ( const tstring& name, float speed, D3DCOLOR excludeColor )
{
   DxAnimation animation = *getAnimation( name );
   animation.speed( speed );
   animation.excludeColor( excludeColor );
   return animation;
}

//=======================================================================
//private
bool DxAssetManager::parseConfig ( const tstring& filename, bool build )
{
   tifstream script( getConfigAssetPath( filename ).c_str(), std::ios_base::in );
   DxTexture* currentTexture = NULL;
   bool result = true;

   if ( !script.is_open() || script.bad() )
   {
      logln( _T("Unable to load Asset Configuration File: [%s]"), filename.c_str() );
      return false;
   }

   ConfigParser parser;
   tstring line;
   while ( parser.getNextLine( script, line ) )
   {
      if ( line[0] == '@' )
      {
         buildFileAsset( line );
      }
      else if ( build )
      {
         buildTexturetAsset( line, myCurrentBuildingTexture );
      }
      else
      {
         RawAsset asset;
         asset.info = line;
         asset.texture = myCurrentBuildingTexture;
         myRawAssets.push_back( asset );
      }

   }
   script.close();
   return true;
}

//=======================================================================
DxAssetManager::RawAsset* DxAssetManager::getAssetRaw ( const tstring& name )
{
   for ( unsigned int index = 0; index < myRawAssets.size(); index++ )
   {
      tstringstream ss( myRawAssets[index].info );
      tstring token;
      ss >> token;
      if ( token[0] == '@' )
      {
         ss >> token;
      }
      if ( token == name )
      {
         return &myRawAssets[index];
      }
   }
   assert(false);
   return NULL;
}

//=======================================================================
bool DxAssetManager::buildFileAsset ( const tstring& rawAsset )
{
   tstringstream ss(rawAsset);
   tstring token;
   ss >> token;
   if ( token == "@Image" )
   {
      tstring name, filename;
      int a = 0, r = 0, g = 0, b = 0;
      ss >> name >> filename;
      if ( ss.fail() )
      {
         return false;
      }
      ss >> a >> r >> g >> b;
      addTextureFromFile( name, filename, D3DCOLOR_ARGB(a, r, g, b) );
      myCurrentBuildingTexture = getTexture( name );

   }
   return true;
}

//=======================================================================
bool DxAssetManager::buildTexturetAsset ( const tstring& rawAsset, DxTexture* texture )
{
   tstringstream ss(rawAsset);   
   tstring name;
   int type, x, y, width, height;
   
   ss >> name >> type >> x >> y >> width >> height;
   if ( ss.fail() )
   {
      return false;
   }
   if ( type == 3 )
   {
      addTexture( name, texture, x, y ,width, height );
   }
   else if ( type == 4  )
   {            
      addSurface( name, texture, x, y ,width, height );
   }
   else
   {
      addAnimation( name, texture, rawAsset );
   }
   return true;
}

//=======================================================================
bool DxAssetManager::addTextureFromFile ( const tstring& name, const tstring& filename, D3DCOLOR excludeColor )
{
   bool result = true;
   Asset<DxTexture> textureAsset;
   result &= textureAsset.asset.create( DxWrapper::device(), getAssetPath( filename ), excludeColor );
   textureAsset.name = name;
   myTextures.push_back( textureAsset );
   return result;
}

//=======================================================================
bool DxAssetManager::addTexture ( const tstring& name, DxTexture* texture, int x, int y, int width, int height )
{
   bool result = true;
   Rect srcRect( x, y, x + width, y + height );
   Asset<DxTexture> textureAsset;

   textureAsset.asset.create( DxWrapper::device(), width, height, D3DUSAGE_RENDERTARGET );
   textureAsset.name = name;
   texture->stretchRect( DxWrapper::device(), &srcRect, textureAsset.asset, NULL );
   myTextures.push_back( textureAsset );
   return result;
}

//=======================================================================
bool DxAssetManager::addSurface ( const tstring& name, DxTexture* texture, int x, int y, int width, int height )
{
   bool result = true;
   Rect srcRect( x, y, x + width, y + height );
   Asset<DxSurface> surfaceAsset;
   result &= surfaceAsset.asset.createFromFile( DxWrapper::device(), texture->filename(), &srcRect );
   surfaceAsset.name = name;
   mySurfaces.push_back( surfaceAsset );
   return result;
}

//=======================================================================
bool DxAssetManager::addAnimation ( const tstring& name, DxTexture* texture, const tstring& animationDescr  )
{
   bool result = true;
   Asset<DxAnimation> animationAsset;
   result &= animationAsset.asset.init( texture, animationDescr, 0 );
   animationAsset.name = name;
   myAnimations.push_back( animationAsset );
   return result;
}

//=======================================================================
DxAssetManager::DxAssetManager ()
{
   myTextures.reserve( ourMaxCachedItemsCount );
   mySurfaces.reserve( ourMaxCachedItemsCount );
   myAnimations.reserve( ourMaxCachedItemsCount );
}

//=======================================================================
DxAssetManager::~DxAssetManager ()
{
}