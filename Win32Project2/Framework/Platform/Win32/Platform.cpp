#include "Platform.h"

#include <string>

void DebugLog(int level, const char * pszFormat, ...)
{
	const int BUFFERSIZE = 1024*100;
    char* szBuf = new char[BUFFERSIZE];
    char* label = NULL;
    
    switch( level )
    {
        case 1:
            label = "[Info] ";
            break;
        case 2:
            label = "[Warning] ";
            break;
        case 3:
            label = "[Error] ";
            break;
    }
    
    if ( label )
		OutputDebugStringA( label );

    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(szBuf, BUFFERSIZE, pszFormat, ap);
	szBuf[BUFFERSIZE-1] = 0;
    va_end(ap);
	OutputDebugStringA( szBuf );
	OutputDebugStringA( "\n" );

	delete[] szBuf;
}