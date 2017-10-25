#pragma once
#include "object.h"

class Triangle :
	public Object
{
public:
	Triangle(void);
	~Triangle(void);
	Triangle* clone() const { return new Triangle(*this); }
};
