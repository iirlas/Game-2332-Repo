
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
//static
DxAssetManager& DxAssetManager::getInstance ()
{
   static DxAssetManager instance;
   return instance;
}

//=======================================================================
DxAssetManager::DxAssetManager ()
{
}

//=======================================================================
DxAssetManager::~DxAssetManager ()
{
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
         Logger::message( "Unable to find specified Assets directory!" );
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
bool DxAssetManager::load ( const tstring& configFilename )
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
         Logger::message( "Unable to find config file: [%s]!", configFilename.c_str() );
         return false;
      }
   }

   return parseConfig( configFilepath );
}

//=======================================================================
void DxAssetManager::shutdown ()
{
   myAssetPath.clear();
   
   for ( std::map<tstring, DxTexture>::iterator item = myTextures.begin(); 
         item != myTextures.end(); item++ )
   {
      item->second.destroy();
   }
   myTextures.clear();

   for ( std::map<tstring, DxSurface>::iterator item = mySurfaces.begin(); 
         item != mySurfaces.end(); item++ )
   {
      item->second.destroy();
   }
   mySurfaces.clear();

   for ( std::map<tstring, DxAnimation>::iterator item = myAnimations.begin(); 
         item != myAnimations.end(); item++ )
   {
      item->second.shutdown();
   }
   myAnimations.clear();
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
   std::map<tstring, DxTexture>::iterator item = myTextures.find( name );
   if ( item != myTextures.end() )
   {
      return &item->second;
   }
   Logger::message( _T("Unable to find Texture:\"%s\""), name.c_str() );
   return NULL;
}


//=======================================================================
DxAnimation* DxAssetManager::getAnimation ( const tstring& name )
{
   std::map<tstring, DxAnimation>::iterator item = myAnimations.find( name );
   if ( item != myAnimations.end() )
   {
      return &item->second;
   }
   Logger::message( _T("Unable to find Animation:\"%s\""), name.c_str() );
   assert(false);
   return NULL;
}

//=======================================================================
DxAnimation DxAssetManager::getAnimationCopy ( const tstring& name, float speed, D3DCOLOR excludeColor )
{
   DxAnimation animation;
   std::map<tstring, DxAnimation>::iterator item = myAnimations.find( name );
   if ( item != myAnimations.end() )
   {
      animation = item->second;
   }
   animation.speed( speed );
   animation.excludeColor( excludeColor );
   return animation;
}

//=======================================================================
bool DxAssetManager::parseConfig ( const tstring& filename )
{
   tifstream script( getConfigAssetPath( filename ).c_str(), std::ios_base::in );
   DxTexture* currentTexture = NULL;
   

   if ( !script.is_open() || script.bad() )
   {
      Logger::message( _T("Unable to load Asset Configuration File:\"%s\""), filename.c_str() );
      return false;
   }

   ConfigParser parser;
   tstring line;
   while ( parser.getNextLine( script, line ) )
   {
      tstringstream ss(line);
      tstring token;
      ss >> token;
      if ( token == "@Image")
      {
         int a = 0, r = 0, g = 0, b = 0;
         tstring name, filename;
         ss >> name >> filename >> a >> r >> g >> b;
         loadTextureFile( name, filename, D3DCOLOR_ARGB(a,r,g,b) );
         currentTexture = getTexture( name );
      }
      else
      {
         tstring name = token;
         int type, x, y, width, height;;
         
         ss >> type >> x >> y >> width >> height;
         if ( ss.fail() )
         {
            return false;
         }

         Rect srcRect( x, y, x + width, y + height );

         switch ( type )
         {
         case 3:
            loadTexture( name, currentTexture, srcRect );
            break;
         case 4:
            loadSurface( name, currentTexture, srcRect );
            break;
         default:
            loadAnimation( name, currentTexture, line );
            break;

         }
      }
   }
   script.close();
   return true;
}

//=======================================================================
bool DxAssetManager::loadTextureFile ( tstring name, tstring filename, D3DCOLOR excludeColor )
{
   DxTexture texture;
   if ( texture.create( DxWrapper::device(), getAssetPath(filename), excludeColor ) )
   {
      myTextures[name] = texture;
      return true;
   }
   return false;
}

//=======================================================================
bool DxAssetManager::loadTexture ( tstring name, DxTexture* fileTexture, Rect& srcRect )
{
   DxTexture texture;
   if ( texture.create( DxWrapper::device(), srcRect.width(), srcRect.height(), D3DUSAGE_RENDERTARGET ) )
   {
      fileTexture->stretchRect( DxWrapper::device(), &srcRect, texture, NULL );
      myTextures[name] = texture;
      return true;
   }
   return false;
}

//=======================================================================
bool DxAssetManager::loadSurface ( tstring name, DxTexture* fileTexture, Rect& srcRect )
{
   DxSurface surface;
   if ( surface.createFromFile( DxWrapper::device(), fileTexture->filename(), &srcRect ) )
   {
      mySurfaces[name] = surface;
      return true;
   }
   return false;
}

//=======================================================================
bool DxAssetManager::loadAnimation ( tstring name, DxTexture* fileTexture, tstring animationDescr )
{
   DxAnimation animation;
   if ( !animation.init( fileTexture, animationDescr, 0 ) )
   {
      return false;
   }
   myAnimations[name] = animation;
   return true;
}