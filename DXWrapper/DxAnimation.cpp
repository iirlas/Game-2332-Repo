#include "stdafx.h"
#include <cassert>
#include <map>
#include <fstream>
#include "Utilities/TTypes.h"
#include "Utilities/Rect.h"
#include "Utilities/Point.h"
#include "Utilities/TStringRoutines.h"
#include "DxWrapper/DxAssetManager.h"
#include "DxWrapper/DxTexture.h"
#include "DxWrapper/DxAnimation.h"
//=======================================================================
DxAnimation::DxAnimation ()
:myName(), myCurrentFrame(0), myFrameCount(0)
{  
}

//=======================================================================
DxAnimation::~DxAnimation ( )
{
}

//=======================================================================
//bool DxAnimation::init ( IDXDEVICE device, const tstring& textureFilename, const tstring& animDescrStr, float speed ) 
//{
//   bool result = false;
//   mySpeed = speed;
//   //if ( !myFrames.empty() )
//   //{
//   //   myFrames.clear();
//   //}
//
//   //tstring toParse = trimFront( _T("(") + textureFilename + _T(")[") + trimPath(textureFilename) + _T("]") + animDescrStr );
//   //result = parse( device, toParse );
//   //if ( result && animDescrStr.empty() )
//   //{
//   //   DxTexture& texture = myTextures.begin()->second;
//   //   myFrames.push_back( std::pair<Rect,DxTexture*>( Rect( Point(), texture.width(), texture.height() ), &texture ) );
//   //}
//   return result;
//}

//=======================================================================
bool DxAnimation::init ( DxTexture* texture, const tstring& animationDesc, float speed, D3DCOLOR excludeColor )
{
   Point pos;
   int width = -1, height = -1;
   tstringstream ss( animationDesc );
   int type = -1;  

   ss >> myName >> type;
   if ( ss.fail() )
   {
      return false;
   }

   myAnimation =  (ANIMATION)type;

   while ( true )
   {
      DxAnimationFrame frame;
      ss >> pos.x >> pos.y >> width >> height;
      if ( ss.fail() )
      {
         break;
      }
      frame.rect.set( pos, width, height );
      frame.texture = texture;
      myFrames[myFrameCount] = frame;
      myFrameCount++;
   }
   mySpeed = speed;
   myExcludeColor = excludeColor;
   return true;
}

//=======================================================================
bool DxAnimation::init ( DxTexture* texture, float speed, D3DCOLOR excludeColor )
{
   Point pos;
   DxAnimationFrame frame;
   frame.rect.set( 0, 0, texture->width(), texture->height() );
   frame.texture = texture;
   myFrames[myFrameCount] = frame;
   myFrameCount++; 
   mySpeed = speed;
   myExcludeColor = excludeColor;
   return true;
}

//=======================================================================
void DxAnimation::update ()
{
   if ( !myTimer.isRunning() )
   {
      myTimer.start();
   }
   if ( myTimer.elapsedTime() < 1000/mySpeed )
      return;
   myCurrentFrame = (myCurrentFrame + 1) % myFrameCount;
   myTimer.restart();
}

//=======================================================================
void DxAnimation::shutdown ()
{
   for ( unsigned int index = 0; index < ourMaxAnimationFrames; index++ )
   {
      myFrames[index].texture = NULL;
   }
}

//=======================================================================
void DxAnimation::reset() //added for resetting animation so it doesn't start mid frame
{
   myCurrentFrame = 0;
   myTimer.restart();
}


//=======================================================================
DxAnimation::ANIMATION DxAnimation::animation ( ANIMATION type )
{
   myAnimation = type;
   return myAnimation;
}


//=======================================================================
float DxAnimation::speed ( float value )
{
   mySpeed = value;
   return mySpeed;
}

//=======================================================================
void DxAnimation::drawFrame ( IDXSPRITE spriteobj, D3DXVECTOR3* position, 
                              D3DXVECTOR2* scale, float rotation, 
                              D3DXVECTOR2* center, D3DCOLOR color )
 {
   myFrames[myCurrentFrame].texture->draw ( spriteobj, position, scale, 
                                            rotation, center, color, 
                                            &myFrames[myCurrentFrame].rect );
}

//=======================================================================
//private
//
//bool DxAnimation::parse ( DxAnimationInfo animInfo )
//{
//   tstring parseStr( animInfo.information );
//   TCHAR state = _T('\0');
//   tstringstream ss( parseStr );
//   int animationType = -1;
//
//   ss >> myName >> animationType;
//   animation( (ANIMATION)animationType );
//
//   while ( true )
//   {
//      int x = -1, y = -1, width = -1, height = -1;
//      Rect rect;
//
//      ss >> x >> y >> width >> height;
//      if ( ss.fail() )
//      {
//         break;
//      }
//
//      assert( width != -1 && height != -1 );
//      rect.set( Point( x, y ), width, height );
//
//      if ( myFrameCount >= ANIMATION_MAX_LENGTH )
//      {
//         return false;
//      }
//
//      myFrames[myFrameCount] = rect;
//      myFrameCount++;
//   }
//   return true;
//}

//=======================================================================
//private
//tstring getNextToken ( const tstring& str, const tstring& pattern, char& state )
//{
//   size_t index = str.find_first_of( pattern );
//   size_t endIndex;
//   if ( index == tstring::npos || index == (str.length() - 1) )
//   {
//      assert( false );
//      return false;
//   }
//
//   endIndex = str.find_first_of( pattern, index + 1 );
//   if ( endIndex == tstring::npos )
//      endIndex = str.length();
//
//   state = str[index];
//   return str.substr( index + 1, (endIndex - index) - 1 );
//}