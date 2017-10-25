#include "StdAfx.h"
#include "Button.h"
#include "Object.h"
#include "Memory.h"
#include "SceneManager.h"
#include "ObjectType.h"
#include  <cstdlib>
#include "Geometry.h"
#include "Shape.h"
#include "String.h"
#include "Globals.h"
#include "myDefines.h"
#include "TextManager.h"
#include "ResourceManager.h"

Button::Button(void): Handler()
{
	this->model = ResourceManager::GetInstance()->GetModelById(11);
	this->shader = ResourceManager::GetInstance()->GetShaderById(0);
	this->shapeType = Shape::POLYGON;
	this->pixel_Size = 48;
	this->color = Vector4(1,0,0,1);
}

Button::~Button(void)
{
}

void Button::Draw()
{

	//Loi o Handle::Draw()
	Handler::Draw();
	Vector4 t = Vector4(this->position.x, this->position.y, 0, 1) * this->GetMVPMatrix();
	int x = position.x;
	int y = position.y;
	TextManager::GetInstance()->RenderString(
		this->name,
		color,
		x - (TextManager::GetInstance()->GetStringWidth(this->name, this->pixel_Size))/4,
		y - GetHeight()/6,
		pixel_Size);

}

float Button::GetHeight()
{
	return Object::GetHeight();
}
float Button::GetWidth()
{
	return Object::GetWidth();
}


void Button::SetName(const char *name)
{
	Object::SetName(name);
}
void Button::scaleSelf()
{
	float scaleX = (float)Globals::screenWidth/800;
	float scaleY = (float)Globals::screenHeight/600;
	float scale = scaleX>scaleY ? scaleY : scaleX;
	scaleX = scaleX > scale ? (scaleX + 1)/2 : scaleX;
	scaleY = scaleY > scale ? (scaleY + 1)/2 : scaleY;

	this->position = Vector2(position.x*scaleX, position.y*scaleY);
	this->scale *= scale;
	this->pixel_Size *= scale;
}