#pragma once

#define BIT(x) 1 << x

#ifdef FOX_PLATFORM_WINDOWS
	#ifdef FOX_BUILD_DLL
		#define FOX_API __declspec(dllexport)
	#else
		#define FOX_API __declspec(dllimport)
	#endif
#else
	#error Windows support only. Dream big and one day... 
#endif