#include "StdAfx.h"
#include "Box.h"
#include "ResourceManager.h"
#include "Shape.h"

Box::Box(void): Object(NULL, NULL, NULL)
{
	this->model = ResourceManager::GetInstance()->GetModelById(7);

	this->shader = ResourceManager::GetInstance()->GetShaderById(0);
	this->shapeType = Shape::POLYGON;
/*
		this->textureCount = 1;
	this->texture = new Texture*[this->textureCount];
	this->texture[0] = ResourceManager::GetInstance()->GetTextureById(1);
	*/
}

Box::~Box(void)
{

}
