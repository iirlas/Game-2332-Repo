#pragma once

#if !defined(_TILE_H_)
#define _TILE_H_

#include "DxWrapper/DxGameSprite.h"


typedef enum
{
   GROUND,
   GROUNDBORDERED,		
   GROUNDBOTTOM,			
   GROUNDTOP,				
   GROUNDLEFT,				
   GROUNDRIGHT,			
   GROUNDCORNERTL,		
   GROUNDCORNERTR,		
   GROUNDCORNERBL,		
   GROUNDCORNERBR,		
   GROUNDINLETTOP,		
   GROUNDINLETBOTTOM,	
   GROUNDINLETLEFT, 	
   GROUNDINLETRIGHT,
   
   ICE,
   ICEBORDERED,	
   ICEBOTTOM,		
   ICETOP,			
   ICELEFT,	   
   ICERIGHT,		
   ICECORNERTL,	
   ICECORNERTR,	
   ICECORNERBL,	
   ICECORNERBR,	
   ICEINLETTOP,	
   ICEINLETBOTTOM,
   ICEINLETLEFT,	
   ICEINLETRIGHT,

   SLIME,
   SLIMEBORDERED,		
   SLIMEBOTTOM,		
   SLIMETOP,		   
   SLIMELEFT,		   
   SLIMERIGHT,		   
   SLIMECORNERTL,		
   SLIMECORNERTR,		
   SLIMECORNERBL,		
   SLIMECORNERBR,		
   SLIMEINLETTOP,		
   SLIMEINLETBOTTOM,	
   SLIMEINLETLEFT,		
   SLIMEINLETRIGHT,	

   SNOW,
   WATER,

   ROCK,
   ROCKGROUND2,	
   ROCKGROUND3,	
   ROCKSNOW1,		
   ROCKSNOW2,		
   ROCKSNOW3		

} TileType;

class Tile : public DxGameSprite
{
public:
   TileType type () const { return myType; }
   TileType type ( TileType type ) { return (myType = type); }
private:
   TileType myType;
};

#endif //_TILE_H_