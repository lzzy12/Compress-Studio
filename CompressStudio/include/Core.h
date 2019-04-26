namespace cs {
	#ifdef CS_PLATFORM_WINDOWS
		#ifdef CS_SHARED_LINK
			#ifdef CS_BUILD_DLL
				#define CS_UTIL __declspec(dllexport)
				#define EX_SCOPE
			#else
				#define CS_UTIL __declspec(dllimport)
				#define EX_SCOPE extern
			#endif
		#else
			#define CS_UTIL
		#endif
	#else 
		#define CS_UTIL
	#endif
	#define CS_OK true
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
}