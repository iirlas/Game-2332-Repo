#include "stdafx.h"
#include <cassert>
#include <windows.h>
#include "DxWrapper/DxCommon.h"
#include "DxWrapper/ImageInfo.h"

using namespace DxWrapper;

//=======================================================================
ImageInfo::ImageInfo ( )
{
   ZeroMemory( &myFileInfo, sizeof(myFileInfo) );
}

//=======================================================================
ImageInfo::ImageInfo ( const ImageInfo& other )
:myFilename(other.myFilename), myFileInfo(other.myFileInfo)
{
}

//=======================================================================
ImageInfo& ImageInfo::operator= ( const ImageInfo& other )
{
   myFilename = other.myFilename;
   myFileInfo = other.myFileInfo;
   return *this;
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