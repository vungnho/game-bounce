#pragma once

class Globals
{
public:

	static int screenWidth;
	static int screenHeight;

};

#ifdef WIN32
	#define BOUNCE_DATA_LOCATION  "../resources/"
#else
	#define BOUNCE_DATA_LOCATION  "/sdcard/bounce/resources/"
#endif //OS_ANDROID