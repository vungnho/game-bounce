#pragma once
#include "Environment.h"
#include "Object.h"
#include "MvpMatrix.h"
#include "Camera.h"
#include "Bounce.h"
#include "Handler.h"
#include "Score.h"
#include "Button.h"
#include "Scene.h"
#include "Game.h"
#include "Loading.h"
#include "Splash.h"
#include "LevelMenu.h"
#include "MainMenu.h"
#include "Setting.h"
//#include <Utilities/utilities.h> // if you use STL, please include this line AFTER all other include


class SceneManager
{
public:


	MvpMatrix view;
	MvpMatrix project;



	Scene* currentScene;
	Game* sceneGame;
	MainMenu* sceneMenu;
	LevelMenu* sceneLevelMenu;
	Loading* sceneLoading;
	Splash* sceneSplash;
	Setting* sceneSetting;


	std::vector<Object*> *selectedMap;
	std::vector<Object*> menu;

	Object* selectedObject;


	Vector2 lastMousePos;
	Vector2 lastMouseDown;
	float tourchTime;
	int level;

	
	void Init();
	static std::vector<Object*> ReadMapFromJSON(const char* file_name);

	void Draw();
	void OnTourchDown(int x, int y);
	void OnTourchUp(int x,int y);
	void OnTourchMove(int x, int y);
	void OnKeyDown(unsigned char keyChar);
	void OnKeyUp(unsigned char keyChar);
	void Update(float delta_time);
	void ContactProcess(Object* o1, Object* o2);
	void SaveScence();

	void ChangeScene(Scene* scene);

	Camera* GetCamera();
	void OnResize();



private:

	void EditMap(char* filename);
	Object* CopyObject(Object* o);

private:
	Object* clipple;

	SceneManager(void);
	~SceneManager(void);

public:
	/*implicit methods exist for the copy constructor and operator= and we want to forbid calling them.*/
	SceneManager(const SceneManager &){};
	SceneManager& operator =(const SceneManager &){};
	static void CreateInstance()
    {
        if ( ms_pInstance == NULL )
		   ms_pInstance = new SceneManager();
    }
	static SceneManager * GetInstance() 
    {
		return ms_pInstance;
    }
	static void DestroyInstance() 
    {
	   if ( ms_pInstance )
	   {
		  delete ms_pInstance;
		  ms_pInstance = NULL;
	   }
    }

protected:
	static SceneManager * ms_pInstance;
};
