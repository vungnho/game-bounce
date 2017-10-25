#include "StdAfx.h"
#include "Sprite.h"
#include "Model.h"

Sprite::Sprite():m_Width(0), m_Height(0){}
Sprite::Sprite(Texture** t, int c,Shader* s)
{
	this->texture = t;
	this->textureCount = c;
	this->shader = s;
	this->mass = 1.0;

}


//float Sprite::GetWidth(){return m_Width;}
//float Sprite::GetHeight(){return m_Height;}
Sprite::~Sprite()
{
	delete model;
}
