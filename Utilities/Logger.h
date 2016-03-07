#pragma once
#if !defined(_LOGGER_H_)
#include <windows.h>
#include "Utilities/TType.h"


//=======================================================================
// Logs a formated message to the debug console.
// Usage: log ( _T( formatedMessage ), arg1, arg2, etc. );
void log ( LPCTSTR format, ... );

#endif //_LOGGER_H_