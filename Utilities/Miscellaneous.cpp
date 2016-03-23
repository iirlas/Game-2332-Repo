#include "Utilities\TTypes.h"
#include "Utilities/Miscellaneous.h"

//=======================================================================
tstring Util::reverse ( const tstring& str )
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
tstring Util::trimFront ( const tstring& str, const tstring& toTrim )
{
   int index = str.find_first_not_of( toTrim );
   if ( index == tstring::npos || index == (str.length() - 1) )
   {
      return str;
   }
   return str.substr( index );
}

//=======================================================================
tstring Util::trimBack ( const tstring& str, const tstring& toTrim )
{
   tstring rStr = reverse( str );
   int index = rStr.find_first_of( toTrim );
   if ( index == tstring::npos || index == 0 )
   {
      return str;
   }
   return reverse( rStr.substr( index ) );
}

//=======================================================================
tstring Util::trimPath ( const tstring& str, const tstring& toTrim )
{
   int index = str.find_last_of( toTrim );
   if ( index == tstring::npos || index == 0 )
   {
      return str;
   }
   return str.substr( index + 1 );
}
