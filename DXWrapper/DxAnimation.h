#pragma once

#if !defined(_DXANIMATION_H_)
#define _DXANIMATION_H_
#define ANIMATION_MAX_LENGTH 256
#include <vector>
#include <map>
#include "Utilities/Rect.h"
#include "Utilities\TTypes.h"
#include "Utilities/Timer.h"
#include "DxWrapper\DxAnimationInfo.h"
#include "DxWrapper\DxCommon.h"
#include "DxWrapper\DxTexture.h"

//
// The animation can be described in two ways: In line with a string for a animation script file.
// In the first version of init use animation descrition string to format for each frame use the following
//    "RECT(xoffset yoffset width height) RECT(xoffset yoffset width height)"
//
// In the second version of init use the following from a file:
//# Base read file. This file will call any sprite sheets needed, 
//# load them, and allow us to create animations from specified
//# frames
//
//
//
//
//# all items following this are in this file.
//@spritesheet.png
//
//# Type		- The type of animatio, this can be the following:
//#			0 - Looping
//#			1 - Rocking
//#			2 - Single loop
//
//
//# ALL LINES MUST BE IN THE FOLLOWING FORMAT:
//# symbol			type	x y width height	{more x y width height's}
//#
//CANDYCORN-LOOP		0		916 646 32 36		948 646 32 36		980 646 32 36		1012 646 32 36
//SMILEYFACE-ROCK		1		1076 580 32 30		1110 576 28 34		1144 574 24 36
//ROCKCROC-ROCK		1		884  538 32 36   	918 538 32 36       948 538 32 36
//
//
//# allows multiple files.
//# @otherfile.ext
//

class DxAnimation
{
public:
   typedef enum 
   {
      LOOP,
      ROCKER,
      SINGLE
   } ANIMATION;

   DxAnimation ( );
   ~DxAnimation ( );

   bool init ( IDXDEVICE device, const tstring& animationName, float speed, D3DCOLOR excludeColor = D3DCOLOR_ARGB( 0, 0, 0, 0 ) );
   void update ( );
   void shutdown ( );

   ANIMATION animation ( ANIMATION type );
   ANIMATION animation ( ) { return myAnimation; }

   float speed ( float value );
   float speed ( ) { return mySpeed; }

   void drawFrame ( IDXSPRITE spriteobj, D3DXVECTOR3* position, D3DXVECTOR2* scale, float rotation, D3DXVECTOR2* center, D3DCOLOR color );
   unsigned int getFrameCount(){ return myFrameCount; }
private:
   bool parse ( DxAnimationInfo animInfo );

private:
   float        mySpeed;
   int          myCurrentFrame;
   D3DXCOLOR    myExcludeColor;
   ANIMATION    myAnimation;
   Timer        myTimer;
   DxTexture*   myTexture;
   unsigned int myFrameCount;
   Rect         myFrames[UCHAR_MAX];

};

#endif //_DXANIMATION_H_