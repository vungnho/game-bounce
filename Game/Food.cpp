#include "StdAfx.h"
#include "Food.h"
#include "ResourceManager.h"
#include "Shape.h"
Food::Food(void)
{
	this->model = ResourceManager::GetInstance()->GetModelById(8);

	this->shader = ResourceManager::GetInstance()->GetShaderById(0);
	this->shapeType = Shape::POLYGON;
}

Food::~Food(void)
{
}
