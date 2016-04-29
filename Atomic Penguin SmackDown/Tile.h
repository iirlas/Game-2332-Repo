#pragma once

#if !defined(_TILE_H_)
#define _TILE_H_

#include "DxWrapper/DxGameSprite.h"




class Tile : public DxGameSprite
{
public:

   typedef enum
   {
      PASSABLE = 0x1, // 0001
      BLOCKED  = 0x2, // 0010
      SLIME    = 0x4, // 0100
   } Type;

   Type type () const { return myType; }
   Type type ( Type type ) { return (myType = type); }
private:
   Type myType;
};

#endif //_TILE_H_