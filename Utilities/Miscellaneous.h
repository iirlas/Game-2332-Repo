#pragma once

#if !defined(_MISCELLANEOUS_H_)
#define _MISCELLANEOUS_H_
#include <tchar.h>
#include "Utilities/TType.h"

//=======================================================================
tstring reverse ( const tstring& str );

//=======================================================================
tstring trimFront ( const tstring& str, const tstring& toTrim = _T(" \t\n\v\f\r") );

//=======================================================================
tstring trimBack ( const tstring& str, const tstring& toTrim = _T(" \t\n\v\f\r") );

//=======================================================================
tstring trimPath ( const tstring& str, const tstring& toTrim = _T("\\/") );

#endif //_MISCELLANEOUS_H_