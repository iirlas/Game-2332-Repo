#include "stdafx.h"
#include <cassert>
#include <map>
#include <fstream>
#include "Utilities/TType.h"
#include "Utilities/Rect.h"
#include "Utilities/Point.h"
#include "Utilities/Miscellaneous.h"
#include "DxWrapper/Animation.h"

using namespace DxWrapper;

//=======================================================================
Animation::Animation ( )
:myCurrentFrame(0)
{
}

//=======================================================================
Animation::~Animation ( )
{
}

//=======================================================================
bool Animation::init ( IDxDevice device, const tstring& textureFilename, const tstring& animDescrStr, float speed ) 
{
   bool result = false;
   mySpeed = speed;
   if ( !myFrames.empty() )
   {
      myFrames.clear();
   }

   tstring toParse = trimFront( _T("(") + textureFilename + _T(")[") + trimPath(textureFilename) + _T("]") + animDescrStr );
   result = parse( device, toParse );
   if ( result && animDescrStr.empty() )
   {
      Texture& texture = myTextures.begin()->second;
      myFrames.push_back( std::pair<Rect,Texture*>( Rect( Point(), texture.width(), texture.height() ), &texture ) );
   }
   return result;
}

//=======================================================================
bool Animation::init ( IDxDevice device, const tstring& scriptFilename, float speed ) 
{
   tfstream script( scriptFilename.c_str(), std::ios_base::in );
   tstring line, fileParsingData;
   bool result = false;

   if ( !script.is_open() || script.bad() )
   {
      return false;
   }

   mySpeed = speed;
   if ( !myFrames.empty() )
   {
      myFrames.clear();
   }

   while ( std::getline( script, line ) )
   {
      line = trimFront( line );

      if ( !line.empty() && line[0] != '#' )
      {
         fileParsingData += line;
      }
   }

   result = parse( device, fileParsingData );
   script.close();
   return result;
}

//=======================================================================
void Animation::update ( )
{
   if ( !myTimer.isRunning() )
   {
      myTimer.start();
   }
   if ( myTimer.elapsedTime() < 1000/mySpeed )
      return;
   myCurrentFrame = (myCurrentFrame + 1) % myFrames.size();
   myTimer.restart();
}

//=======================================================================
void Animation::shutdown ( )
{
   myTextures.clear();
}

//=======================================================================
void Animation::drawFrame ( IDxSprite spriteobj, D3DXVECTOR3* position, 
                              D3DXVECTOR2* scale, float rotation, 
                              D3DXVECTOR2* center, D3DCOLOR color )
{
   myFrames[myCurrentFrame].second->draw( spriteobj, position, scale, 
                                          rotation, center, color, 
                                          &myFrames[myCurrentFrame].first );
}

//=======================================================================
//private
bool Animation::parse ( IDxDevice device, const tstring& originalStr )
{
   tstring parseStr( originalStr );
   tstring currentTextureName;
   int cWidth = -1, cHeight = -1;
   TCHAR state = _T('\0');

   while ( !parseStr.empty() )
   {
      tstring oneStatementStr;

      size_t index = parseStr.find_first_of( _T("@([") );
      size_t endIndex;
      if ( index == tstring::npos || index == (parseStr.length() - 1) )
      {
         assert( false );
         return false;
      }

      endIndex = parseStr.find_first_of( _T("@(["), index + 1 );
      if ( endIndex == tstring::npos )
         endIndex = parseStr.length();

      state = parseStr[index];

      oneStatementStr = parseStr.substr( index + 1, (endIndex - index) - 1 );
      parseStr = parseStr.substr( endIndex );
      tstringstream ss( oneStatementStr );
      if ( state == _T('@') )
      {
         tstring name;
         ss >> name;
         if ( name == _T("WIDTH") )
         {
            ss >> cWidth;
         }
         else if ( name == _T("HEIGHT") )
         {
            ss >> cHeight;
         }
         else
         {
            assert(false);
         }
      }
      else if ( state == _T('[') )
      {
         ss >> currentTextureName;
         currentTextureName = trimBack( currentTextureName, _T("]") );
      }
      else if ( state == _T('(') )
      {
         int x = -1, y = -1, width = -1, height = -1;
         Rect rect;
         ss >> x >> y;
         
         if ( ss.fail() )
         {
            Texture texture;
            tstring filepath = trimBack( oneStatementStr, _T(")") );
            if ( texture.create( device, filepath ) )
            {
               myTextures.insert( std::pair<tstring,Texture>( trimPath( filepath ),texture ) );
               continue;
            }
            return false;
         }

         ss >> width >> height;
         if ( ss.fail() )
         {
            width = cWidth;
            height = cHeight;   
         }

         assert( width != -1 && height != -1 );
         rect.set( Point( x, y ), width, height );
         myFrames.push_back( std::pair<Rect,Texture*>(rect,&myTextures[currentTextureName]) );
      }

   }
   return true;
}

