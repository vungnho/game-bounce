#pragma once

class Globals
{
public:

	static int screenWidth;
	static int screenHeight;

};

#ifdef WIN32
#if _DEBUG
	#define BOUNCE_DATA_LOCATION  "../../Resources/"
#else
#define BOUNCE_DATA_LOCATION  "Resources/"
#endif
#else
	#define BOUNCE_DATA_LOCATION  "/sdcard/bounce/resources/"
#endif //OS_ANDROID