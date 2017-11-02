#pragma once 

#define PI 3.141592654

#ifdef WIN32
	#define RM_PATH "RM.json"
	#define SM_PATH "SM.json"

#else
	#define RM_PATH "/sdcard/@Nhom2/Bounce/RM.json"
	#define SM_PATH "/sdcard/@Nhom2/Bounce/SM.json"

#endif //WIN32
