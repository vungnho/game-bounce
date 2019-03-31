#pragma once

class Globals
{
public:

    static int screenWidth;
    static int screenHeight;
    static int screenWidthRatio;
    static int screenHeightRatio;

};

#ifdef WIN32
#if _DEBUG
//#define BOUNCE_DATA_LOCATION  "../../Resources/"
#define BOUNCE_DATA_LOCATION  "E:/WorkSpace/GIT/vungnho/game-bounce/Resources/"
#else
#define BOUNCE_DATA_LOCATION  "Resources/"
#endif
#else
	#define BOUNCE_DATA_LOCATION  "/sdcard/bounce/resources/"
#endif //OS_ANDROID