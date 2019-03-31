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
    for (auto &levelM : levelMenu)
	{
        levelM->scaleSelf();
        levelM->Bind();
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
    for (auto &levelM : levelMenu)
	{
		if(levelM->IsInside(Vector2(x, y)))
		{
			if(levelM->GetType()==ObjectType::LEVELGAME)
			{
				int val = atoi(((Button*) levelM)->value);
				//Console::log("Selected level %d \n",val);

				SceneManager::GetInstance()->sceneGame->level = val;
				SceneManager::GetInstance()->ChangeScene(SceneManager::GetInstance()->sceneLoading);
				//SceneManager::GetInstance()->sceneGame->Initialaze();
				//SceneManager::GetInstance()->currentScene = SceneManager::GetInstance()->sceneGame;
			}
			else if(levelM->GetType()==ObjectType::HANDLER)
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
    for (auto &levelM : levelMenu)
	{
        levelM->Draw();
	}
};
void LevelMenu::Update(float delta_time)
{
};

