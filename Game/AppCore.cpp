#include <stdlib.h>

#include "../Game/ResourceManager.h"
#include "../Game/SceneManager.h"
#include "../Game/KeyManager.h"
#include "../Game/TextManager.h"
#include "../Game/StateManager.h"
#include "../Game/Globals.h"
#include "definations.h"
#include "../Game/Console.h"

#ifdef OS_ANDROID
	#include "jni_base.h"
#endif //OS_ANDROID


//convert to bottom left
int Invert(int y, int height)
{
	Console::log("Screen Height: %d, y = %d \n", height, y);
	return (height - y);
}

int WIDTH = 500, HEIGHT = 500;

int GameInit()
{
    
	Console::log("----------------------\n\n");
	glClearColor ( 0, 0, 1, 0.5 ); //RGBA
    glViewport(0, 0, WIDTH, HEIGHT);

	KeyManager::CreateInstance();
	KeyManager::GetInstance()->Init();

	ResourceManager::CreateInstance();
	ResourceManager::GetInstance()->Init();

	TextManager::CreateInstance();
	TextManager::GetInstance()->Init();

	SceneManager::CreateInstance();
	SceneManager::GetInstance()->Init();


	StateManager::CreateInstance();
	StateManager::GetInstance()->Init();
    
    return 0;
}

void GameDraw()
{
	SceneManager::GetInstance()->Draw();
}

void GameUpdate(float deltaTime)
{
	SceneManager::GetInstance()->Update(deltaTime);
}

void OnKeyEvent( unsigned char key, bool bIsPressed)
{
	if(bIsPressed)
	{
		SceneManager::GetInstance()->OnKeyDown(key);
	}
	else
	{
		SceneManager::GetInstance()->OnKeyUp(key);
	}
}

void GameCleanUp()
{
    
	StateManager::DestroyInstance();
	SceneManager::DestroyInstance();
	TextManager::DestroyInstance();
	ResourceManager::DestroyInstance();
	KeyManager::DestroyInstance();
    
}

void GameResize(int w, int h)
{
    
    Globals::screenWidth = w;
    Globals::screenHeight = h;
	SceneManager::GetInstance()->OnResize();
    
}

void OnTouchEvent(int type, int x, int y, int id)
{
    static const int TOUCH_ACTION_UP = 0;
	static const int TOUCH_ACTION_DOWN = 1;
    static const int TOUCH_ACTION_MOVE = 2;

	y = Invert(y, Globals::screenHeight);

	if(type == TOUCH_ACTION_DOWN)
	{
		SceneManager::GetInstance()->OnTourchDown(x, y);
	}

	if(type == TOUCH_ACTION_MOVE)
	{
		SceneManager::GetInstance()->OnTourchMove(x, y);
	}

	if(type == TOUCH_ACTION_UP)
	{
		SceneManager::GetInstance()->OnTourchUp(x, y);
	}


}





