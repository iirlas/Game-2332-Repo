#pragma once
#if !defined(_IMAGEINFO_H_)
#define _IMAGEINFO_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities\NonCopyable.h"
#include "Utilities\TType.h"
#include "DxTypes.h"

class ImageInfo : public NonCopyable
{
public:
   ImageInfo ( void );
   virtual ~ImageInfo ( void ) { };

   const dxImageInfo& fileInfo ( void )  { return myFileInfo; }
   const tstring& filename ( void ) { return myFilename; }
   
protected:
	bool getInfoFromFile ( const tstring& filename );
   void removeFileInfo ( );

private:
   tstring		       myFilename;
	D3DXIMAGE_INFO	    myFileInfo;
};

#endif //_IMAGEINFO_H_