#pragma once
#include "scene.h"
#include <Box2D/Box2D.h>
#include <vector>

class Game :
	public Scene
{
public:


	std::vector<Object*> handlerArrow;
	std::vector<Object*> handlerTop;


	Bounce* bounce;
	Handler* touchPoint;
	Handler* touchMove;
	bool complete;
	bool game_over;
	b2World* b2dWorld;
	Score* score;

	int level;



	std::vector<Object*> objects;
	std::vector<Object*> recycleBin;
	std::vector<Object*> handlers;



	Game(void);
	virtual ~Game(void);

	//Mouse Events
	virtual void OnTourchDown(int x, int y);
	virtual void OnTourchUp(int x,int y);
	virtual void OnTourchMove(int x, int y);

	//Key Events
	virtual void OnKeyDown(unsigned char keyChar);
	virtual void OnKeyUp(unsigned char keyChar);


	virtual void Draw();
	virtual void Update(float delta_time);





	void AddObjectToWorld(Object* o);
	void CountObject();
	void ContactProcess(Object* o1, Object* o2);
	void DrawText(int x, int y, Vector4 color);
	void IsTouchDirectionChange();
	void EndGame(bool win);
	Object* GetObjectByName(char* name);
	Object* GetHandlerByName(char* name);
	void InitBox2D();
	void LoadLevel(int level);
	void RemoveObject(Object* o);
	void ReduceLovecity();
	void Initialaze();
	void Initcontrol();
	void ScaleBody(b2Body* body, float ratio);

private:
	bool useTouch;


};
