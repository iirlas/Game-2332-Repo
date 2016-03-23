#include "stdafx.h"
#include <assert.h>
#include "Utilities/Miscellaneous.h"
#include "Utilities/Logger.h"
#include "DXWrapper/DxTypes.h"
#include "DXWrapper/DXWrapper.h"
#include "DXWrapper/DxAssetManager.h"

//=======================================================================
//static
DxAssetManager& DxAssetManager::getInstance ()
{
   static DxAssetManager instance;
   return instance;
}

//=======================================================================
bool DxAssetManager::init ( const tstring& filedata )
{
   if ( !myAssetPath.empty() )
   {
      return false;
   }

   tstring directory( MAX_PATH, _T('\0') ), workingDirectory( MAX_PATH, _T('\0') ), root;


   GetCurrentDirectory( workingDirectory.size(), &workingDirectory[0] ); // get working directory   
   root = workingDirectory.substr( 0, workingDirectory.find( _T("\\") ) + 1 );
   do // find asset directory
   {
      GetCurrentDirectory( directory.size(), &directory[0] );
      
      if ( SetCurrentDirectory( _T(".\\Assets") ) )
      {
         break;
      }
      
      if ( !SetCurrentDirectory( _T("..") ) || directory.c_str() == root )
      {
         SetCurrentDirectory( workingDirectory.c_str() );// set back to process directory
         logln( "Unable to find Assets directory, creating Assets folder at working directory!" );
         tstring assetDir = tstring(workingDirectory.c_str()) + "\\Assets";
         CreateDirectory( assetDir.c_str(), NULL );
         CreateFile( (assetDir + _T("\\AssetConfig.txt")).c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, 1, FILE_ATTRIBUTE_NORMAL, NULL );
         return false;
      }

   } while ( true );

   SetCurrentDirectory( workingDirectory.c_str() );// set back to working directory
   
   myAssetPath = directory.c_str() + tstring("\\Assets");

   return parse( myAssetPath + "\\" + filedata );
}

//=======================================================================
void DxAssetManager::shutdown ()
{
   myAssetPath.clear();
   for ( int index = 0; index < ANIMATION_MAX_COUNT; index++ )
   {
      myAnimations[index].information.clear();
   }
}

//=======================================================================
tstring DxAssetManager::getAsset ( const tstring& imageName )
{
   return myAssetPath + _T("\\") + imageName;
}

//=======================================================================
DxAnimationInfo DxAssetManager::getAnimationInfo ( const tstring& name )
{
   for ( unsigned int index = 0; index < myAnimationCount; index++ )
   {
      if ( myAnimations[index].name == name )
      {
         return myAnimations[index];
      }
   }
   assert(false);
   return DxAnimationInfo();
}


//=======================================================================
DxTexture* DxAssetManager::getTexture ( const tstring& name )
{
   for ( unsigned int index = 0; index < myTextureCount; index++ )
   {
      if ( Util::trimPath(myTextures[index].filename()) == name )
      {
         return &myTextures[index];
      }
   }
   logln( _T("Unable to find Texture:\"%s\""), name.c_str() );
   assert(false);
   return NULL;
}


////=======================================================================
//tstring DxAssetManager::getSoundAsset ( const tstring& soundName )
//{
//   return myAssetPath + _T("\\") + soundName;
//}

//=======================================================================
tstring DxAssetManager::getConfiguration ( const tstring& fileInfo )
{

   return myAssetPath + _T("\\") + fileInfo;
}

//=======================================================================
DxAssetManager::DxAssetManager ()
:myTextureCount(0), myAnimationCount(0)
{
}

//=======================================================================
DxAssetManager::~DxAssetManager ()
{
}

//=======================================================================
bool DxAssetManager::parse ( const tstring& assetConfig )
{
   tfstream file( assetConfig.c_str() );
   tstring line;
   if ( !file.is_open() || file.bad() )
   {
      logln( _T("Unable to load Asset Configuration File:\"%s\""), assetConfig.c_str() );
      return false;
   }
   
   while ( std::getline( file, line ) )
   {
      tstring parsedLine = Util::trimFront( line );

      if ( !parsedLine.empty() && parsedLine[0] != _T('#') )
      {
         tstringstream ss( parsedLine );
         tstring name;
         ss >> name;
         name = Util::trimFront( name, _T("@") );
         if ( name == _T("animations.txt") )
         {
            parseAnimation( myAssetPath + _T("\\") + name );
         }
      }
   }

   file.close();
   return true;
}

//=======================================================================
bool DxAssetManager::parseAnimation ( const tstring& filename )
{
   tfstream script( filename.c_str(), std::ios_base::in );
   tstring line;
   DxTexture* currentTexture = NULL;

   if ( !script.is_open() || script.bad() )
   {
      logln( _T("Unable to load Asset Animation File:\"%s\""), filename.c_str() );
      return false;
   }
   
   while ( std::getline( script, line ) )
   {
      line = Util::trimFront( line );

      if ( !line.empty() && line[0] != _T('#') )
      {
         tstringstream ss(line);
         if ( line[0] == _T('@') && myTextureCount < TEXTURE_MAX_COUNT )
         {
            if ( !myTextures[myTextureCount] )
            {
               myTextures[myTextureCount].create( DxWrapper::device(), getAsset( Util::trimFront( line, _T("@") ) ), D3DCOLOR_ARGB( 255, 170, 181, 129 ));
               currentTexture = &myTextures[myTextureCount];
               myTextureCount++;
            }
         }
         else
         {
            if ( myAnimationCount < ANIMATION_MAX_COUNT )
            {
               ss >> myAnimations[myAnimationCount].name;
               myAnimations[myAnimationCount].information = line.substr( myAnimations[myAnimationCount].name.length() );
               myAnimations[myAnimationCount].texture = currentTexture;
               myAnimationCount++;
            }
         }
      }
   }

   script.close();
   return true;
}
