#include "StdAfx.h"
#include "Bounce.h"
#include "Shape.h"
#include "ResourceManager.h"

Bounce::Bounce():Object(NULL, NULL, NULL)
{
	this->model = ResourceManager::GetInstance()->GetModelById(8);
	this->shader = ResourceManager::GetInstance()->GetShaderById(0);
	this->shapeType = Shape::CIRCLE;
}

Bounce::~Bounce()
{
}


/*
void Bounce::Update(float dt)
{
	Object::Update(dt);
}

void Bounce::Jump()
{
	b2Body* body =  static_cast<b2Body*>(this->GetUserData());
	body->ApplyLinearImpulse( b2Vec2(0, 15), body->GetPosition(), true);
}

void Bounce::Forward(float dx)
{
	b2Body* body =  static_cast<b2Body*>(this->GetUserData());
}

*/