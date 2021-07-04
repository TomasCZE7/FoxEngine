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

#ifdef FOX_ENABLE_ASSERTS
    #define FOX_ASSERT(x, ...) { if(!(x)) { FOX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define FOX_CORE_ASSERT(x, ...) { if(!(x)) { FOX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define FOX_ASSERT(x, ...)
    #define FOX_CORE_ASSERT(x, ...)
#endif