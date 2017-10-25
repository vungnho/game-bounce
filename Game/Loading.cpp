#include "StdAfx.h"
#include "Loading.h"
#include "TextManager.h"
#include "SceneManager.h"
#include "Box.h"


Loading::Loading(): isLoaded(false), isDrowing(false)
{
		
}

Loading::~Loading()
{
}
void Loading::Update(float dt)
{
	
	if(isLoaded)
	{
		isLoaded = false;
		isDrowing = false;
		SceneManager::GetInstance()->ChangeScene(SceneManager::GetInstance()->sceneGame);
		return;
	}
	if(isDrowing)
	{
		SceneManager::GetInstance()->sceneGame->Initialaze();
		isLoaded = true;
	}
	isDrowing = true;
}


void Loading::Draw()
{
	TextManager::GetInstance()->RenderString("Loading...",Vector4(0.7, 0.7, 0.7, 0.8), 300, 300, 100);

}