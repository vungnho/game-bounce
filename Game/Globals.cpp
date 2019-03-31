#include "Globals.h"

#ifdef WIN32
    int Globals::screenWidth = 800;
    int Globals::screenHeight = 480;
    int Globals::screenWidthRatio = 800;
    int Globals::screenHeightRatio = 600;
#else
	int Globals::screenWidth = 800;
	int Globals::screenHeight = 480;
    int Globals::screenWidthRatio = 800;
    int Globals::screenHeightRatio = 600;
#endif //OS_ANDROID