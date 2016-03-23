#pragma once

#if !defined(_ANIMATION_H_)
#define _ANIMATION_H_

#include <vector>
#include <map>
#include "Utilities/Rect.h"
#include "Utilities/TType.h"
#include "Utilities/Timer.h"
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/Texture.h"

//
// The animation can be described in two ways: In line with a string for a animation script file.
// In the first version of init use animation descrition string to format for each frame use the following
//    "RECT(xoffset yoffset width height) RECT(xoffset yoffset width height)"
//
// In the second version of init use the following from a file:
//    ## Animation example ##
//    # file: 'example.animation' 
//
//    # Define constants
//    # Note: Only WIDTH and HEIGHT are valid constants.
//    @WIDTH 20
//    @HEIGHT 20
//    
//    # Load image files
//    LOAD(../../Game Art/image1.png) 
//    LOAD(../../Game Art/image2.png) 
//    
//    # Selects the image to use.
//    USE[image1.png]
//    
//    # Inserts a frame with constants.
//    POINT(64 0) 
//    POINT(128 0) 
//    POINT(192 0)
//    
//    # Selects another image. 
//    USE[image2.png]
//    
//    # Inserts a frame without constants.
//    RECT(0 0 100 100)

namespace DxWrapper
{

class Animation
{
public:
   Animation ( );
   ~Animation ( );

   bool init ( IDxDevice device, const tstring& textureFilename, const tstring& animDescrStr, float speed );
   bool init ( IDxDevice device, const tstring& scriptFilename, float speed );
   void update ( );
   void shutdown ( );

   void drawFrame ( IDxSprite spriteobj, D3DXVECTOR3* position, D3DXVECTOR2* scale, float rotation, D3DXVECTOR2* center, D3DCOLOR color );

private:
   bool parse ( IDxDevice device, const tstring& animDescrStr );

private:
   float                                 mySpeed;
   int                                   myCurrentFrame;
   Timer                                 myTimer;
   std::map<tstring,Texture>             myTextures;
   std::vector<std::pair<Rect,Texture*>> myFrames;
};

}

#endif //_ANIMATION_H_