#pragma once

#include <Windows.h>

void DebugLog( int level, const char* format, ... );

#ifdef _DEBUG
	#include <assert.h>

	#define LOG(format, ...)				DebugLog( 0, format, __VA_ARGS__ )
	#define LOGERROR(format,...)			DebugLog( 3, format, __VA_ARGS__ )
	#define LOGINFO(format,...)				DebugLog( 1, format, __VA_ARGS__ )
	#define LOGWARN(format,...)				DebugLog( 2, format, __VA_ARGS__ )

	#define ASSERT( condition, message )		assert( condition )

#else

	#define ISLOG(format, ...)					0
	#define ISLOGERROR(format,...)				0
	#define ISLOGINFO(format,...)				0
	#define ISLOGWARN(...)						0
	#define ISASSERT( condition, message )		0

#endif