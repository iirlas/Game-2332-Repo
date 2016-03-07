#include "Utilities/TType.h"
#include "Utilities/Miscellaneous.h"

//=======================================================================
tstring reverse ( const tstring& str )
{
   tstring rStr(str);
   for ( unsigned index = 0, endIndex = 0; index < str.length(); index++, endIndex = (str.length() - index - 1) )
   {
      if ( index != endIndex )
      {
         rStr[index] ^= rStr[endIndex];
         rStr[endIndex] ^= rStr[index];
         rStr[index] ^= rStr[endIndex];
      }
   }
   return rStr;
}

//=======================================================================
tstring trimFront ( const tstring& str, const tstring& toTrim )
{
   int index = str.find_first_not_of( toTrim );
   if ( index == tstring::npos || index == (str.length() - 1) )
   {
      return _T("");
   }
   return str.substr( index );
}

//=======================================================================
tstring trimBack ( const tstring& str, const tstring& toTrim )
{
   tstring rStr = reverse( str );
   int index = str.find_last_of( toTrim );
   if ( index == tstring::npos || index == 0 )
   {
      return _T("");
   }
   return str.substr( 0, index );
}

//=======================================================================
tstring trimPath ( const tstring& str, const tstring& toTrim )
{
   int index = str.find_last_of( toTrim );
   if ( index == tstring::npos || index == 0 )
   {
      return _T("");
   }
   return str.substr( index + 1 );
}
