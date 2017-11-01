#pragma once

class Globals
{
public:

	static int screenWidth;
	static int screenHeight;

};

#ifdef WIN32
	#define BOUNCE_DATA_LOCATION  "G:\\__public__\\_downloads\\3D to 2D project 15032016\\Bounce Project (Renew)\\Resources\\"
#else
	#define BOUNCE_DATA_LOCATION  "/sdcard/bounce/resources/"
#endif //OS_ANDROID