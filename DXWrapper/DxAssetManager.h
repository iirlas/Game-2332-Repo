#pragma once

#if !defined(_DXASSETMANAGER_H_)
#define _DXASSETMANAGER_H_
#define ANIMATION_MAX_COUNT UCHAR_MAX
#define TEXTURE_MAX_COUNT UCHAR_MAX
#include <windows.h>
#include <vector>
#include "Utilities\NonCopyable.h"
#include "Utilities\TTypes.h"
#include "DxWrapper\DxCommon.h"
#include "DxWrapper\DxTypes.h"
#include "DxWrapper\DxTexture.h"
#include "DxWrapper\DxAnimationInfo.h"

class DxAssetManager : NonCopyable
{
public:
   
   static DxAssetManager& getInstance ();
   bool init ( const tstring& filedata ); 
   void shutdown ();
   
   tstring getAsset ( const tstring& name );   // asset name
   DxAnimationInfo getAnimationInfo ( const tstring& name );
   DxTexture* getTexture ( const tstring& name );
   //tstring getImageAsset(const tstring& imageName);   // image name
   //tstring getSoundAsset(const tstring& soundName);   // sound name
   tstring getConfiguration(const tstring& fileInfo); // configuration info from files.

private:

   DxAssetManager ();
   ~DxAssetManager ();
   bool parse ( const tstring& filedata );
   bool parseAnimation ( const tstring& filename );

   unsigned int    myTextureCount;
   unsigned int    myAnimationCount;
   tstring         myAssetPath;
   DxTexture       myTextures[TEXTURE_MAX_COUNT];
   DxAnimationInfo myAnimations[ANIMATION_MAX_COUNT];
};

#endif
