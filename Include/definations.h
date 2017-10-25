#pragma once 

#define PI 3.141592654

#define LIMIT_FPS 60
#define MAX_TARGET_TRACE_ELEMENT 1000000

#define UP_KEY 38
#define DOWN_KEY 40
#define LEFT_KEY 37
#define RIGHT_KEY 39

#define TERRAIN_PEAK_VALUE 20.0f;

namespace fog
{
	const float k_fStart = 100000.0f;
	const float k_fLength = 400.0f;
#define FOG_COLOR 0.80f, 0.50f, 0.50f
}

const float ATTENUATION_CONSTANT_A = 0.1f;
const float ATTENUATION_CONSTANT_C = 1.0f;

const float DOF_FADE = 20.0f;
const float DOF_CLARITY = 20.0f;

#define LINE_LENGTH 256
#define GET_LINE() if ( fgets (line , LINE_LENGTH , pFile) == NULL ) return false

#ifdef WIN32
#define RM_PATH "../Resources/RM.txt"
#define SM_PATH "../Resources/SM.txt"
#define EM_PATH "../Resources/EM.txt"
#define DATA_PATH "../Resources/"

#else
#define RM_PATH "/sdcard/tungph/3DEngine/RM.txt"
#define SM_PATH "/sdcard/tungph/3DEngine/SM.txt"
#define EM_PATH "/sdcard/tungph/3DEngine/EM.txt"
#define DATA_PATH "/sdcard/tungph/3DEngine/"

#endif //WIN32
