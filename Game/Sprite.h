#pragma once
#include "Object.h"

class Sprite:public Object
{
public:
	Sprite();
	Sprite(Texture** t, int c,Shader* s);

	float m_X, m_Y, m_Width, m_Height, m_TH, m_TW;
	//float GetWidth();
	//float GetHeight();

	~Sprite();
	void Init(int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH);



	

};