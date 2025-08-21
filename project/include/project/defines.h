#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
	#ifdef PROJECT_EXPORTS
		#define PROJECT_API __declspec(dllexport)
	#else
		#define PROJECT_API __declspec(dllimport)
	#endif
#else
	#define PROJECT_API
#endif