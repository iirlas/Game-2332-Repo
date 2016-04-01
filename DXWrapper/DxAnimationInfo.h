#pragma once

#if !defined(_DXANIMATIONFRAME_H_)
#define _DXANIMATIONFRAME_H_
#include "Utilities/TTypes.h"
#include "Utilities/Rect.h"
#include "DxWrapper/DxTexture.h"

struct DxAnimationFrame
{
   DxAnimationFrame ()
      :texture(NULL), rect()
   {
   }
   DxTexture* texture;
   Rect       rect;
};

#endif //_DXANIMATIONFRAME_H_