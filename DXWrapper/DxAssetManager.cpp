
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
bool DxAssetManager::init ( const tstring& configFilename, const TCHAR* rootPath,  bool createIfNotFound )
{
   DWORD gle;

   if ( !myAssetPath.empty() )
   {
      return false;
   }

   TCHAR working_directory[MAX_PATH] = { 0 };
   
   if ( !(gle = GetCurrentDirectory( MAX_PATH, working_directory )) )
   {
      return false;
   }

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
      assetDir = working_directory;
      if ( !PathUtilities::pathAppend( assetDir, "Assets" ) )
      {
         return false;
      }
   }

   if ( !PathUtilities::pathIsDirectory( assetDir ) )
   {
      if ( !createIfNotFound )
      {
         logln( "Unable to find specified Assets directory!" );
         return false;
      }
      CreateDirectory( assetDir.c_str(), NULL );

      tstring configFilepath(assetDir);
      FILE* configFile = NULL;
      fopen_s( &configFile, configFilepath.c_str(), "a" );

      if ( configFile )
      {
         fclose( configFile );
      }   
   }

   myAssetPath = assetDir;
   tstring configFilepath = myAssetPath;
   PathUtilities::pathAppend( configFilepath, configFilename );
   return parse( configFilepath );
}

//=======================================================================
bool DxAssetManager::parseConfig ( const tstring& filename )
{
   tifstream script( getConfigAssetPath( filename ).c_str(), std::ios_base::in );
   DxTexture* currentTexture = NULL;
   

   if ( !script.is_open() || script.bad() )
   {
      logln( _T("Unable to load Asset Animation File:\"%s\""), filename.c_str() );
      return false;
   }

   ConfigParser parser;
   tstring line;
   while ( parser.getNextLine( script, line ) )
   {
      tstringstream ss(line);
      tstring token;
      ss >> token;
      if ( token == "@file" && ss >> token )
      {
         addTextureAsset( token );
         currentTexture = getTexture( token );
      }
      else if ( myAnimationCount < ourMaxCachedItemsCount )
      {
         int type = 0;
         ss >> type;
         if ( type == 3 ) // creates a texture
         {
            Point pos, size;
            
            ss >> pos.x >> pos.y >> size.x >> size.y;
            if ( ss.fail() )
            {
               return false;
            }

            if ( !myTextures[myTextureCount].create( DxWrapper::device(), size.x, size.y, D3DUSAGE_RENDERTARGET ) )
            {
               return false;
            }
            myTextures[myTextureCount].name( token );
            
            Rect srcRect( pos, size.x, size.y );
            currentTexture->stretchRect( DxWrapper::device(), &srcRect, myTextures[myTextureCount], NULL );            

            myTextureCount++;
            continue;
         }
         if ( type == 4 )// creates a surface;
         {
            mySurfaces[mySurfaceCount];
            continue;
         }

         myAnimations[myAnimationCount].animation( (DxAnimation::ANIMATION)type );

         while ( true )
         {
            DxAnimationFrame frame;
            Point pos;            
            int width = -1, height = -1;
             frame.texture = currentTexture;

            ss >> pos.x >> pos.y >> width >> height;

            if ( ss.fail() )
            {
               break;
            }

            assert( width != -1 && height != -1 );

            frame.rect.set( pos, width, height );

            myAnimations[myAnimationCount].name( token );
            myAnimations[myAnimationCount].addFrame( frame );
         }
         myAnimationCount++;
      }
   }
   script.close();
   return true;
}


//=======================================================================
void DxAssetManager::shutdown ()
{
   myAssetPath.clear();
}

//=======================================================================
//tstring DxAssetManager::getAssetPath ( const tstring& imageName )
//{
//   return myAssetPath + "\\" + imageName;
//}

//=======================================================================
tstring DxAssetManager::getConfigAssetPath ( const tstring& configFilename )
{
   tstring configFilePath( myAssetPath );
   PathUtilities::pathAppend( configFilePath, configFilename );
   return configFilePath;
}

//=======================================================================
DxTexture* DxAssetManager::getTexture ( const tstring& name )
{
   for ( unsigned int index = 0; index < myTextureCount; index++ )
   {
      if ( myTextures[index].name() == name )
      {
         return &myTextures[index];
      }
   }
   logln( _T("Unable to find Texture:\"%s\""), name.c_str() );
   return NULL;
}


//=======================================================================
DxAnimation* DxAssetManager::getAnimation ( const tstring& name )
{
   for ( unsigned int index = 0; index < myAnimationCount; index++ )
   {
      if ( myAnimations[index].name() == name )
      {
         return &myAnimations[index];
      }
   }
   logln( _T("Unable to find Animation:\"%s\""), name.c_str() );
   assert(false);
   return NULL;
}

////=======================================================================
//tstring DxAssetManager::getSoundAsset ( const tstring& soundName )
//{
//   return myAssetPath + _T("\\") + soundName;
//}

//=======================================================================
DxAssetManager::DxAssetManager ()
:myConfigFileCount(0), mySurfaceCount(0), myTextureCount(0), myAnimationCount(0)
{
}

//=======================================================================
DxAssetManager::~DxAssetManager ()
{
}

//=======================================================================
bool DxAssetManager::parse ( const tstring& assetConfig )
{
   tifstream configFile( assetConfig.c_str(), std::ios_base::in  );
   DWORD gle = GetLastError();      // not likely to work in this instance... tbd
   
   if ( !configFile.is_open() || configFile.bad() )
   {
      logln( _T("Unable to load Asset Configuration File:\"%s\""), assetConfig.c_str() );
      return false;
   }
   ConfigParser parser;
   tstring line;
   while ( parser.getNextLine( configFile, line ) )
   {
      if ( myConfigFileCount >= ourMaxCachedItemsCount )
      {
         break;
      }

      tstringstream ss( line );
      ss >> myConfigFiles[myConfigFileCount];
      myConfigFileCount++;
   }

   configFile.close();
   return true;
}

//=======================================================================
bool DxAssetManager::addTextureAsset ( const tstring& name, POINT* srcSize )
{
   if ( myTextureCount < ourMaxCachedItemsCount )
   {
      tstring imageFilePath( myAssetPath );
      PathUtilities::pathAppend( imageFilePath, name );
      myTextures[myTextureCount].create( DxWrapper::device(), imageFilePath, 0, srcSize );
      myTextures[myTextureCount].name( Util::trimPath( imageFilePath ) );
      myTextureCount++;
      return true;
   }

   return false;
}

