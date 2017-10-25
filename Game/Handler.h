#pragma once
#include "object.h"

class Handler :
	public Object
{
public:
	Handler(void);
	~Handler(void);

	Texture* tt_focus;
	Texture* tt_blur;

	Matrix GetMVPMatrix();

	void hightlight(bool yes);
};
