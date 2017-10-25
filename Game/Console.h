#pragma once

/*

#include <Utilities/utilities.h>
#include <fstream>
#include <stdarg.h>
#ifdef WIN32
#define LOGI(...) ;
#define LOGE(...) ;
#else
#include <android/log.h>]
#define LOG_TAG					"Bounce: "
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#endif
*/

class Console
{
public:
	static void log(const char* formatStr, ...)
	{
        /*
		va_list params;
			char buf[2048];
		va_start ( params, formatStr );
		vsprintf ( buf, formatStr, params );

		char text[9999];
		printf ("%s", buf );
		sprintf (text, "%s", buf );


		//write to file
		 std::ofstream outfile;
#ifdef WIN32
		 outfile.open("log.txt", std::ios_base::app);
#else
		 outfile.open("/sdcard/log.txt", std::ios_base::app);
#endif
		 outfile << text ; 

		//OutputDebugString(buf);    
		va_end ( params );
        */
	}
};
