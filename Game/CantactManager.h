#pragma once
#include "SceneManager.h"
class CantactManager
{
public:
	CantactManager(void);
	~CantactManager(void);

	static std::vector<Vector2> CheckContacting(Object* o1, Object* o2);
};
