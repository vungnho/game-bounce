#pragma once
#include "Scene.h"
#include <vector>

class Splash : public Scene
{
public:
	Splash(void);
	~Splash(void);

	std::vector<Object*> objects;

	//Mouse Events
	virtual void OnTourchDown(int x, int y);
	virtual void OnTourchUp(int x,int y);
	virtual void OnTourchMove(int x, int y);

	//Key Events
	virtual void OnKeyDown(unsigned char keyChar);
	virtual void OnKeyUp(unsigned char keyChar);


	virtual void Draw();
	virtual void Update(float delta_time);
private:
	bool isTouched;


};
