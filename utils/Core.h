#ifdef CS_PLATFORM_WINDOWS
	#ifdef CS_BUILD_DLL
		#define CS_UTIL __declspec(dllexport)
	#else
		#define CS_UTIL __declspec(dllimport)
	#endif
#else
	#define CS_UTIL
#endif

#define CS_OK 0
typedef unsigned long int cs_int;