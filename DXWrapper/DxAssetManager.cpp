
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
      return false;
   }

   myAssetPath = assetDir;
   tstring configFilepath = myAssetPath;
   PathUtilities::pathAppend( configFilepath, configFilename );
   return parseConfig( configFilepath );
}

//=======================================================================
bool DxAssetManager::parseConfig ( const tstring& filename )
{
   tifstream script( getConfigAssetPath( filename ).c_str(), std::ios_base::in );
   DxTexture* currentTexture = NULL;
   

   if ( !script.is_open() || script.bad() )
   {
      logln( _T("Unable to load Asset Configuration File:\"%s\""), filename.c_str() );
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
         int a = 0, r = 0, g = 0, b = 0;
         ss >> a >> r >> g >> b;
         token = Util::trimBoth( token );
         addTextureAsset( token, NULL, D3DCOLOR_ARGB( a, r, g, b ) );
         currentTexture = getTexture( token );

      }
      else
      {
         tstring name = token;
         int type;
         
         ss >> type;
         if ( ss.fail() )
         {
            return false;
         }

         if ( type == 3 && myTextureCount < ourMaxCachedItemsCount )
         {
            int x, y, width, height;

            ss >> x >> y >> width >> height;
            if ( ss.fail() )
            {
               return false;
            }

            Rect srcRect( x, y, x + width, y + height );
            tstring imageFilePath( myAssetPath );

            PathUtilities::pathAppend( imageFilePath, name );
            myTextures[myTextureCount].create( DxFramework::device(), width, height, D3DUSAGE_RENDERTARGET );
            myTextures[myTextureCount].name( name );

            currentTexture->stretchRect( DxFramework::device(), &srcRect, myTextures[myTextureCount], NULL );
            myTextureCount++;
         }
         else if ( type == 4 && mySurfaceCount < ourMaxCachedItemsCount )
         {

         }
         else if ( myAnimationCount < ourMaxCachedItemsCount )
         {
            myAnimations[myAnimationCount].init( currentTexture, line, 0 );
            myAnimationCount++;
         }
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
//tstring DxAssetManager::getAssetFilePath ( const tstring& imageName )
//{
//   while (  )
//   {
//
//   }
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

//=======================================================================
DxAnimation DxAssetManager::getAnimationCopy ( const tstring& name, float speed, D3DCOLOR excludeColor )
{
   DxAnimation animation;
   for ( unsigned int index = 0; index < myAnimationCount; index++ )
   {
      if ( myAnimations[index].name() == name )
      {
         animation = myAnimations[index];
         break;
      }
   }
   animation.speed( speed );
   animation.excludeColor( excludeColor );
   return animation;
}

////=======================================================================
//tstring DxAssetManager::getSoundAsset ( const tstring& soundName )
//{
//   return myAssetPath + _T("\\") + soundName;
//}

//=======================================================================
DxAssetManager::DxAssetManager ()
:mySurfaceCount(0), myTextureCount(0), myAnimationCount(0)
{
}

//=======================================================================
DxAssetManager::~DxAssetManager ()
{
}

//=======================================================================
//bool DxAssetManager::parse ( const tstring& assetConfig )
//{
//   tifstream configFile( assetConfig.c_str(), std::ios_base::in  );
//   DWORD gle = GetLastError();      // not likely to work in this instance... tbd
//   
//   if ( !configFile.is_open() || configFile.bad() )
//   {
//      logln( _T("Unable to load Asset Configuration File:\"%s\""), assetConfig.c_str() );
//      return false;
//   }
//   ConfigParser parser;
//   tstring line;
//   while ( parser.getNextLine( configFile, line ) )
//   {
//      if ( myConfigFileCount >= ourMaxCachedItemsCount )
//      {
//         break;
//      }
//
//      //tstringstream ss( line );
//      //ss >> myConfigFiles[myConfigFileCount];
//      //myConfigFileCount++;
//   }
//
//   configFile.close();
//   return true;
//}

//=======================================================================
bool DxAssetManager::addTextureAsset ( const tstring& name, POINT* srcSize, D3DCOLOR excludeColor )
{
   if ( myTextureCount < ourMaxCachedItemsCount )
   {
      tstring imageFilePath( myAssetPath );
      PathUtilities::pathAppend( imageFilePath, name );
      myTextures[myTextureCount].create( DxFramework::device(), imageFilePath, excludeColor, srcSize );
      myTextures[myTextureCount].name( Util::trimPath( imageFilePath ) );
      myTextureCount++;
      return true;
   }

   return false;
}

