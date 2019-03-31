#include "StdAfx.h"
#include "Splash.h"
#include "TextManager.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "LevelMenu.h"
#include "Memory.h"
#include "Box.h"
#include "String.h"
#include "Globals.h"
#include <iostream>
#ifdef ANDROID
#endif



Splash::Splash():isTouched(false)
{
	const char* s = String::concat(BOUNCE_DATA_LOCATION, "Data/Splash.json");
	this->objects= SceneManager::ReadMapFromJSON(s);
	delete[] s;
    for (auto &object : objects)
	{
        object->Bind();
	}

	//Console::log("Text Width: %d \n", TextManager::GetInstance()->GetStringWidth("Giappi", 50));
}

Splash::~Splash(void)
{
}

//Mouse Events
void Splash::OnTourchDown(int x, int y)
{


};
void Splash::OnTourchUp(int x,int y)
{
	isTouched = true;
	
};
void Splash::OnTourchMove(int x, int y)
{
};

//Key Events
void Splash::OnKeyDown(unsigned char keyChar)
{
}
void Splash::OnKeyUp(unsigned char keyChar)
{
};


void Splash::Draw()
{
    for (auto &object : objects)
	{
        object->Draw();
	}
	//TextManager::GetInstance()->RenderString("Bounce",Vector4(0.6, 0.6, 0.6, 0.9),130,300,380);
	//TextManager::GetInstance()->RenderString("Tourch any where...",Vector4(0.5,0.5,0.5,0.8),320,150,48);
};
void Splash::Update(float delta_time)
{
	if(isTouched)
	{
		if(!SceneManager::GetInstance()->sceneLevelMenu)
		{
			SceneManager::GetInstance()->sceneLevelMenu = new LevelMenu();
		}
		if(!SceneManager::GetInstance()->sceneMenu)
		{
			SceneManager::GetInstance()->sceneMenu = new MainMenu();
		}
		SceneManager::GetInstance()->ChangeScene(SceneManager::GetInstance()->sceneMenu);
	}
};