#pragma once
#include "object.h"

class Thorn :
	public Object
{
public:
	Thorn(void);
	~Thorn(void);
	Thorn* clone() const { return new Thorn(*this); }
};
