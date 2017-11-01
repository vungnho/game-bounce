#pragma once

#include <stdio.h>

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
    template<typename... Args>
    static void log(const char* formatStr, Args... args)
	{
        printf(formatStr, args...);
	}
};
