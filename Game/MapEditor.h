#pragma once
#include "scene.h"
#include <vector>

class MapEditor :
	public Scene
{
public:


	std::vector<Object*> objects;
	Object* selectedObject;
    int selectedId;
	char fileName[255];
	Object* clipple;

	MapEditor(void);
	~MapEditor(void);

	//Mouse Events
	virtual void OnTourchDown(int x, int y);
	virtual void OnTourchUp(int x,int y);
	virtual void OnTourchMove(int x, int y);

	//Key Events
	virtual void OnKeyDown(unsigned char keyChar);
	virtual void OnKeyUp(unsigned char keyChar);


	virtual void Draw();
	virtual void Update(float delta_time);

	void LoadMap(const char* file_name);
	Object* CopyObject(Object *o);
	void SaveScence();

};
