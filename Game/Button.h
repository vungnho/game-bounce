#pragma once
#include "object.h"
#include "Handler.h"

class Button :
	public Handler
{
public:
	Button(void);
	~Button(void);

	void Draw();
	float GetWidth();
	float GetHeight();
	float pixel_Size;
	Vector4 color;
	char value[256];

	void SetName(const char* name);
	void scaleSelf();

};
