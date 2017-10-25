#pragma once
#include "object.h"
#include "ResourceManager.h"
#include "Shape.h"

class Box :
	public Object
{
public:
	Box(void);
	~Box(void);
	Box* clone() const
	{
		Box* box = new Box(*this);
		box->model = ResourceManager::GetInstance()->GetModelById(7);
		box->shader = ResourceManager::GetInstance()->GetShaderById(0);
		box->shapeType = Shape::POLYGON;
		return box;

	}
};
