#pragma once
#include "Environment.h"
#include "Object.h"
#include "MvpMatrix.h"
#include "Camera.h"
#include "Bounce.h"
#include "Handler.h"
#include "Score.h"
#include "Button.h"
#include <Utilities/MyMath.h> // if you use STL, please include this line AFTER all other include
#define CDTIME_KEY_PRESS 0.01f
class Scene
{


#pragma region [Feild]
public:
	Vector2 lastMousePos;
	Vector2 lastMouseDown;
	float tourchTime;
	Camera* camera;
	float coolDownTime;

#pragma endregion

#pragma region [Method]
public:
	Scene(void);
	virtual ~Scene(void);

	
	//Mouse Events
	virtual void OnTourchDown(int x, int y){};
	virtual void OnTourchUp(int x,int y){};
	virtual void OnTourchMove(int x, int y){};

	//Key Events
	virtual void OnKeyDown(unsigned char keyChar){};
	virtual void OnKeyUp(unsigned char keyChar){};


	virtual void Draw(){};
	virtual void Update(float delta_time){};

	virtual void OnSizeChange(){};

#pragma endregion

};
