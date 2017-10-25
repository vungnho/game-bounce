#pragma once
#include "object.h"

class Food :
	public Object
{
public:
	Food(void);
	~Food(void);
	Food* clone() const { return new Food(*this); }
};
