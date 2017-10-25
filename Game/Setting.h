#pragma once
#include "scene.h"

class Setting :
	public Scene
{
public:
	Setting(void);
	~Setting(void);

	//Mouse Events
	virtual void OnTourchDown(int x, int y);
	virtual void OnTourchUp(int x,int y);
	virtual void OnTourchMove(int x, int y);

	//Key Events
	virtual void OnKeyDown(unsigned char keyChar);
	virtual void OnKeyUp(unsigned char keyChar);


	virtual void Draw();
	virtual void Update(float delta_time);

};
