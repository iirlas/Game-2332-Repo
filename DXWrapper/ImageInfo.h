#pragma once

#if !defined(_IMAGEINFO_H_)
#define _IMAGEINFO_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities\NonCopyable.h"
#include "Utilities\TType.h"
#include "DxTypes.h"

namespace DxWrapper
{

class ImageInfo
{
public:
   ImageInfo ( void );
   ImageInfo ( const ImageInfo& other );
   virtual ~ImageInfo ( void ) { };
   ImageInfo& operator= ( const ImageInfo& other );

   const D3DXIMAGE_INFO& fileInfo ( void )  { return myFileInfo; }
   const tstring& filename ( void ) { return myFilename; }
   
protected:
	bool getInfoFromFile ( const tstring& filename );
   void removeFileInfo ( void );

private:
   tstring		       myFilename;
	D3DXIMAGE_INFO	    myFileInfo;
};

}

#endif //_IMAGEINFO_H_