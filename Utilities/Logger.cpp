#include <tchar.h>
#include "Utilities\TTypes.h"
#include "Utilities/Logger.h"



//=======================================================================
void Logger::message ( LPCTSTR format, ... )
{
    TCHAR cstrMessage[UCHAR_MAX] = {0};

    va_list listArgs;
    va_start( listArgs, format );
    VTSPRINTF_S( cstrMessage, UCHAR_MAX, format, listArgs );
    va_end( listArgs );
 
    OutputDebugString( cstrMessage );
}