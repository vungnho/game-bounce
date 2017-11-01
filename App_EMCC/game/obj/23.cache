#include "StdAfx.h"
#include "LevelMenu.h"
#include "TextManager.h"
#include "SceneManager.h"
#include "LevelMenu.h"
#include "Memory.h"
#include "String.h"
#include "Game.h"
#include "MapEditor.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "Memory.h"
#include "ObjectType.h"
#include "Globals.h"

LevelMenu::LevelMenu(): Scene()
{


	//SceneManager::GetInstance()->sceneGame->level = 2;
	//SceneManager::GetInstance()->sceneGame->Initialaze();
	//SceneManager::GetInstance()->currentScene = SceneManager::GetInstance()->sceneGame;


	const char* s = String::concat(BOUNCE_DATA_LOCATION, "Data/LevelMenu.json");
	this->levelMenu = SceneManager::ReadMapFromJSON(s);
	delete[] s;
	for(int i = 0; i < this->levelMenu.size(); i++)
	{
		this->levelMenu[i]->scaleSelf();
		this->levelMenu[i]->Bind();
	}


}

LevelMenu::~LevelMenu(void)
{
	while(levelMenu.size() > 0)
	{
		delete levelMenu.back();
		levelMenu.pop_back();
	}
}


//Mouse Events
void LevelMenu::OnTourchDown(int x, int y)
{
};
void LevelMenu::OnTourchUp(int x,int y)
{

	for(int i = 0; i < levelMenu.size(); i++)
	{
		if(levelMenu[i]->IsInside(Vector2(x, y)))
		{
			if(levelMenu[i]->GetType()==ObjectType::LEVELGAME)
			{
				int val = atoi(((Button*) this->levelMenu[i])->value);
				//Console::log("Selected level %d \n",val);

				SceneManager::GetInstance()->sceneGame->level = val;
				SceneManager::GetInstance()->ChangeScene(SceneManager::GetInstance()->sceneLoading);
				//SceneManager::GetInstance()->sceneGame->Initialaze();
				//SceneManager::GetInstance()->currentScene = SceneManager::GetInstance()->sceneGame;
			}
			else if(levelMenu[i]->GetType()==ObjectType::HANDLER)
			{
				SceneManager::GetInstance()->ChangeScene(SceneManager::GetInstance()->sceneMenu);
			}
		}
	}

};
void LevelMenu::OnTourchMove(int x, int y)
{
};

//Key Events
void LevelMenu::OnKeyDown(unsigned char keyChar)
{

}
void LevelMenu::OnKeyUp(unsigned char keyChar)
{

	if(keyChar == KeyManager::S_CHAR_E)
	{
		SceneManager::GetInstance()->ChangeScene(new MapEditor());
		return;
	}
};


void LevelMenu::Draw()
{
	for(int i = 0; i < this->levelMenu.size(); i++)
	{
		this->levelMenu[i]->Draw();
	}
};
void LevelMenu::Update(float delta_time)
{
};

