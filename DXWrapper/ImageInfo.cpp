#include "stdafx.h"
#include <cassert>
#include <windows.h>
#include "ImageInfo.h"

//=======================================================================
ImageInfo::ImageInfo ( )
{
   ZeroMemory( &myFileInfo, sizeof(myFileInfo) );
}

//=======================================================================
bool ImageInfo::getInfoFromFile ( const tstring& filename )
{
   myFilename = filename;

	//get image info from file
	HRESULT result = D3DXGetImageInfoFromFile( myFilename.c_str(), &myFileInfo);
   return SUCCEEDED( result );
}

//=======================================================================
void ImageInfo::removeFileInfo ( )
{
   myFilename = _T("");
   ZeroMemory( &myFileInfo, sizeof(myFileInfo) );
}