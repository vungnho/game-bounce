#pragma once
#include "Object.h"

class Bounce :
	public Object
{
public:
	Bounce(void);
	~Bounce(void);
	Bounce* clone() const { return new Bounce(*this); }

	//void Update(float delta_time);
	//void Backward(float dx);
	//void Forward(float dx);
	//void Jump();
	void Happy();
	void Sad();
	void Die();
};
