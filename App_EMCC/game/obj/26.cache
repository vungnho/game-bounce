#include "StdAfx.h"
#include "Handler.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Shape.h"

Handler::Handler(void)
{
	this->model = ResourceManager::GetInstance()->GetModelById(7);
	this->shader = ResourceManager::GetInstance()->GetShaderById(0);
	this->shapeType = Shape::POLYGON;

}

Handler::~Handler(void)
{
}


Matrix Handler::GetMVPMatrix()
{
	return 	this->GetSRTMatrix()*
		SceneManager::GetInstance()->GetCamera()->GetProjectMatrix();
}

void Handler::hightlight(bool yes)
{

}