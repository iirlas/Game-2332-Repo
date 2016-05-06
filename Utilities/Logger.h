#pragma once
#if !defined(_LOGGER_H_)
#include <windows.h>
#include "Utilities\TTypes.h"
#include "Utilities\NonCopyable.h"

class Logger : private NonCopyable
{
public:
   //=======================================================================
   // Logs a formated message to the debug console.
   // Usage: Logger::message ( _T( formatedMessage ), arg1, arg2, etc. );
   static void message ( LPCTSTR format, ... );
};

#endif //_LOGGER_H_