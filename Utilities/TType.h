#if !defined(_TTYPE_H_)
#define _TTYPE_H_
#include <windows.h>
#include <string>
#include <fstream>

#if defined(UNICODE)// Is UNICODE
#define TSPRINTF_S swprintf_s
typedef std::wstring tstring;
typedef std::wfstream tfstream;
#else // NOT UNICODE
#define TSPRINTF_S sprintf_s
typedef std::string tstring;
typedef std::fstream tfstream;
#endif // UNICODE

#endif //_TTYPE_H_