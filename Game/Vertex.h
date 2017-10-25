#pragma once
#include <Utilities/MyMath.h>

struct Vertex
{
	Vector2 Position;
	Vector2 UV;
};

#define VERTEX_POS	0
#define VERTEX_UV	8 // size of Vector3