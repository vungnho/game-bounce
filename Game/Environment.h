#pragma once
#include <Utilities/MyMath.h>

class Fog
{
public:
	float fogStart;
	float fogRange;
	Vector4 fogColor;

	Fog(){};
	Fog(float start, float range, Vector4 color){};
};



class Light
{
public:
	static Vector3 ambientColor;
	static float ambientWeight;
	static float lightsCount;
};

