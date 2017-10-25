// NewTrainingFramework.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"

#include "../Game/Globals.h"

#include "../Game/ResourceManager.h"
#include "../Game/SceneManager.h"
#include "../Game/KeyManager.h"
#include "../Game/TextManager.h"
#include "../Game/StateManager.h"
#include <conio.h>


extern int  GameInit();
extern void GameDraw();
extern void GameUpdate(float);
extern void OnKeyEvent(unsigned char, bool);
extern void GameCleanUp();
extern void OnTouchEvent(int type, int x, int y, int id);

static const int TOUCH_ACTION_UP = 0;
static const int TOUCH_ACTION_DOWN = 1;
static const int TOUCH_ACTION_MOVE = 2;


int Init(ESContext *esContext)
{
    //glViewport(0, 0, esContext->width, esContext->height);
    return GameInit();

}



void Draw(ESContext *esContext)
{
    SceneManager::GetInstance()->Draw();
}

void Update(ESContext *esContext, float deltaTime)
{
    SceneManager::GetInstance()->Update(deltaTime);
}

void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{
    OnKeyEvent(key, bIsPressed);
}

void CleanUp()
{
    GameCleanUp();
}



void TouchActionDown(ESContext *esContext, int x, int y)
{
    OnTouchEvent(TOUCH_ACTION_DOWN, x, y, 0);
}

void TouchActionUp(ESContext *esContext, int x, int y)
{
    OnTouchEvent(TOUCH_ACTION_UP, x, y, 0);
}

void TouchActionMove(ESContext *esContext, int x, int y)
{
    OnTouchEvent(TOUCH_ACTION_MOVE, x, y, 0);
}


int _tmain(int argc, const char * argv[])
{
    int a = 1;

    ESContext esContext;

    esInitContext(&esContext);

    esCreateWindow(&esContext, "3D Trainning", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

    if (Init(&esContext) != 0)
        return 0;

    esRegisterDrawFunc(&esContext, Draw);
    esRegisterUpdateFunc(&esContext, Update);
    esRegisterKeyFunc(&esContext, Key);
    esRegisterMouseDownFunc(&esContext, TouchActionDown);
    esRegisterMouseUpFunc(&esContext, TouchActionUp);
    esRegisterMouseMoveFunc(&esContext, TouchActionMove);

    SceneManager::GetInstance()->esContext = &esContext;


    esMainLoop(&esContext);



    //releasing OpenGL resources
    CleanUp();



    //identifying memory leaks
    MemoryDump();
    //Console::log("Press any key...\n");
    _getch();

    return 0;

}


