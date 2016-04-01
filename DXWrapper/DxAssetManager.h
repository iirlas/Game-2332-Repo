#pragma once

#if !defined(_DXASSETMANAGER_H_)
#define _DXASSETMANAGER_H_

#include <windows.h>
#include <vector>
#include "Utilities/TTypes.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/DxTypes.h"
#include "DxWrapper/DxSurface.h"
#include "DxWrapper/DxTexture.h"
#include "DxWrapper/DxAnimation.h"

class DxAssetManager : private NonCopyable
{
public:
   static const unsigned ourMaxCachedItemsCount = 256;

   static DxAssetManager& getInstance ();
   bool init ( const tstring& configFilename, const TCHAR* rootPath = NULL,  bool createIfNotFound = false );
   bool parseConfig ( const tstring& name );
   void shutdown ();
   
   //tstring getAssetPath ( const tstring& name );
   tstring getConfigAssetPath ( const tstring& name );
   DxTexture* getTexture ( const tstring& name );
   DxAnimation* getAnimation ( const tstring& name );

   //[SoundType] getSoundAsset(const tstring& soundFilename);

private:

   DxAssetManager ();
   ~DxAssetManager ();
   bool parse ( const tstring& configFile );
   bool addTextureAsset ( const tstring& name, POINT* srcSize = NULL );

   unsigned int    myConfigFileCount;
   unsigned int    myTextureCount;
   unsigned int    mySurfaceCount;
   unsigned int    myAnimationCount;
   tstring         myAssetPath;
   tstring         myConfigFiles[ourMaxCachedItemsCount];
   DxTexture       myTextures[ourMaxCachedItemsCount];
   DxSurface       mySurfaces[ourMaxCachedItemsCount];
   DxAnimation     myAnimations[ourMaxCachedItemsCount];
};

#endif
