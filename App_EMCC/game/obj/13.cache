#include "StdAfx.h"
#include "Scene.h"
#include "Memory.h"

Scene::Scene():coolDownTime(CDTIME_KEY_PRESS)
{
	this->camera = new Camera();
}

Scene::~Scene(void)
{
	Memory::Delete(this->camera);
}
