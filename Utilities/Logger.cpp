#include "Logger.h"
#include "TType.h"
#include <tchar.h>

//=======================================================================
void log ( LPCTSTR format, ... )
{
    TCHAR cstrMessage[UCHAR_MAX] = {0};

    va_list listArgs;
    va_start( listArgs, format );
    TSPRINTF_S( cstrMessage, UCHAR_MAX, format, listArgs );
    va_end( listArgs );
 
    OutputDebugString( cstrMessage );
}