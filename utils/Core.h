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
#define CS_FILE_OPEN_FAILED -1
#define CS_MINIZIP_API_ERROR -2

#define CS_DEFLATED   8
#define CS_DEFAULT_STRATEGY    0

#define CS_NO_COMPRESSION         0
#define CS_BEST_SPEED             1
#define CS_BEST_COMPRESSION       9
#define CS_DEFAULT_COMPRESSION  (-1)

#define cs_options minizip_opt
typedef unsigned long int cs_int;