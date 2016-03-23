#pragma once

#if !defined(_DXANIMATIONINFO_H_)
#define _DXANIMATIONINFO_H_
#include "Utilities\TTypes.h"
#include "DxWrapper\DxTexture.h"

struct DxAnimationInfo
{
   DxAnimationInfo ()
   :texture(NULL), name(), information()
   {
   }
   DxTexture* texture;
   tstring name;
   tstring information;
};

#endif //_DXANIMATIONINFO_H_