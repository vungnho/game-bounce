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
    for (auto &mn : menu)
	{
        mn->Bind();
	}
	ResetMenu();

}

void MainMenu::ResetMenu()
{
    int menuSize = this->menu.size();
	for(int i = 0; i < menuSize; i++)
	{
		this->menu[i]->position.x = (GLfloat) Globals::screenWidth/2;
		this->menu[i]->position.y = (GLfloat) Globals::screenHeight/ (menuSize + 1) * (menuSize -i);
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
    for (auto &mn : menu)
	{
		if(mn->IsInside(Vector2(x, y)))
		{
            SceneManager *sceneManager = SceneManager::GetInstance();
			if(String::IsEquals(mn->name, "Play"))
			{
				if(sceneManager->sceneLevelMenu)
				{
                    sceneManager->ChangeScene(sceneManager->sceneLevelMenu);
				}
			}
			else if(String::IsEquals(mn->name, "Options"))
			{
                if (sceneManager->sceneSetting)
                {
                    sceneManager->ChangeScene(sceneManager->sceneSetting);
                }
			}
			else if(String::IsEquals(mn->name, "Continue"))
			{
				if(sceneManager->sceneGame->bounce)
				{
                    sceneManager->ChangeScene(sceneManager->sceneGame);
				}
			}
			else if(String::IsEquals(mn->name, "Exit"))
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
    for (auto &mn : menu)
	{
        mn->Draw();
	}
};
void MainMenu::Update(float delta_time)
{
};

