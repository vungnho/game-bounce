#include "StdAfx.h"
#include "MainMenu.h"
#include "TextManager.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "LevelMenu.h"
#include "Memory.h"
#include "String.h"
#include "Game.h"
#include "MapEditor.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "Memory.h"
#include "Globals.h"
#include "ObjectType.h"
MainMenu::MainMenu(): Scene()
{
	const char* s = String::concat(BOUNCE_DATA_LOCATION, "Data/Menu.json");
	this->menu = SceneManager::ReadMapFromJSON(s);
	delete[] s;
	for(int i = 0; i < this->menu.size(); i++)
	{
		this->menu[i]->Bind();
	}
	ResetMenu();

}

void MainMenu::ResetMenu()
{
	for(int i = 0; i < this->menu.size(); i++)
	{
		this->menu[i]->position.x = Globals::screenWidth/2;
		this->menu[i]->position.y = Globals::screenHeight/ (menu.size() + 1) * (this->menu.size()-i);
	}
}

void MainMenu::OnSizeChange()
{
	ResetMenu();
}

MainMenu::~MainMenu(void)
{
	while(menu.size() > 0)
	{
		delete menu.back();
		menu.pop_back();
	}
}


//Mouse Events
void MainMenu::OnTourchDown(int x, int y)
{
};
void MainMenu::OnTourchUp(int x,int y)
{

	for(int i = 0; i < menu.size(); i++)
	{
		if(menu[i]->IsInside(Vector2(x, y)))
		{
			if(String::IsEquals(menu[i]->name, "Play"))
			{
				if(SceneManager::GetInstance()->sceneLevelMenu)
				{
					SceneManager::GetInstance()->ChangeScene(SceneManager::GetInstance()->sceneLevelMenu);
				}
			}
			else if(String::IsEquals(menu[i]->name, "Options"))
			{
                if (SceneManager::GetInstance()->sceneSetting)
                {
                    SceneManager::GetInstance()->ChangeScene(SceneManager::GetInstance()->sceneSetting);
                }
			}
			else if(String::IsEquals(menu[i]->name, "Continue"))
			{
				if(SceneManager::GetInstance()->sceneGame->bounce)
				{
					SceneManager::GetInstance()->ChangeScene(SceneManager::GetInstance()->sceneGame);
				}
			}
			else if(String::IsEquals(menu[i]->name, "Exit"))
			{
				exit(0);
			}
		}
	}

};
void MainMenu::OnTourchMove(int x, int y)
{
};

//Key Events
void MainMenu::OnKeyDown(unsigned char keyChar)
{

}
void MainMenu::OnKeyUp(unsigned char keyChar)
{

	if(keyChar == 'E')
	{
		SceneManager::GetInstance()->currentScene = new MapEditor();
		return;
	}
};


void MainMenu::Draw()
{
	//LOGI(">>>> Screen: %d, %d \n", Globals::screenWidth, Globals::screenHeight);
	for(int i = 0; i < this->menu.size(); i++)
	{
		this->menu[i]->Draw();
	}
};
void MainMenu::Update(float delta_time)
{
};

