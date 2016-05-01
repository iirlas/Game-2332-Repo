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
private:
   template<typename AssetType> struct Asset;
   struct RawAsset;

public:
   static const unsigned ourMaxCachedItemsCount = 256;

   static DxAssetManager& getInstance ();
   // if rootAssetPath is null will use "c:/.../working_dir/Assets".
   // if not null will append "Assets" to given path.
   // if createRootAssetDir is true and Rootpath is not found, creates only the root asset path.
   bool init ( const TCHAR* rootAssetPath = NULL,  bool createRootAssetDir = false );
   
   // load from current asset path, unless specifilced.
   bool load ( const tstring& configFilename, bool build = true );


   void shutdown ();
   
   tstring getAssetPath ( const tstring& name );
   tstring getConfigAssetPath ( const tstring& name );
   tstring getSoundAssetPath ( const tstring& name );
   DxTexture* getTexture ( const tstring& name );
   DxSurface* getSurface ( const tstring& name );
   DxAnimation* getAnimation ( const tstring& name );
   DxAnimation getAnimationCopy ( const tstring& name, float speed, D3DCOLOR excludeColor = D3DCOLOR_ARGB( 0, 0, 0, 0 ) );

private:
   bool parseConfig ( const tstring& name, bool build );
   RawAsset* getAssetRaw ( const tstring& name );

   bool buildFileAsset ( const tstring& rawAsset );
   bool buildTexturetAsset ( const tstring& rawAsset, DxTexture* texture );

   bool addTextureFromFile ( const tstring& name, const tstring& filename, D3DCOLOR excludeColor );
   bool addTexture ( const tstring& name, DxTexture* texture, int x, int y, int width, int height );
   bool addSurface ( const tstring& name, DxTexture* texture, int x, int y, int width, int height );
   bool addAnimation ( const tstring& name, DxTexture* texture, const tstring& animationDescr  );

   DxAssetManager ();
   ~DxAssetManager ();
   //bool parse ( const tstring& configFile );

   
   tstring                                myAssetPath;
   DxTexture*                             myCurrentBuildingTexture;
   std::vector<RawAsset>                  myRawAssets;
   std::vector<Asset<DxTexture>>          myTextures;
   std::vector<Asset<DxSurface>>          mySurfaces;
   std::vector<Asset<DxAnimation>>        myAnimations;
};

#endif
