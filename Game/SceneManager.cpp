
#include "StdAfx.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "Memory.h"
#include "ObjectType.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "String.h"
#include "Shape.h"
#include <fstream>
#include "TextManager.h"
#include "Globals.h"
#include "Bounce.h"
#include "Box.h"
#include "Food.h"
#include "Triangle.h"
#include "Thorn.h"
#include "Target.h"
#include "StateManager.h"
#include "ContactListener.h"
#include "CantactManager.h"
#include "Button.h"
#include "Splash.h"
#include "Scene.h"
#include "Game.h"
#include "MainMenu.h"
#include "Loading.h"
#include "JSON.h"
#include "LevelMenu.h"


#define RATIO 0.008f
#define pix2met(x) (RATIO*x)
#define met2pix(x) (x/RATIO)


SceneManager * SceneManager::ms_pInstance = NULL;

SceneManager::SceneManager(void)
{
	

	selectedObject = NULL;

	//Console::log("Use arrow keys to move.\n");

}

SceneManager::~SceneManager(void)
{
	Memory::Delete(sceneGame);
	Memory::Delete(sceneMenu);
	Memory::Delete(sceneLevelMenu);
	Memory::Delete(sceneLoading);
	Memory::Delete(sceneSplash);
	Memory::Delete(sceneSetting);
	ContactListener::DestroyInstance();
}





std::vector<Object*> SceneManager::ReadMapFromJSON(const char* file_name)
{

	std::vector<Object*> list;
	FILE* file = fopen(file_name, "r");
	if(file == NULL)
	{
		Console::log("Can not open to read file %s.\n", file_name);
		return list;
	}
	else
	{
		//Console::log("Load file %s successfully.\n", file_name);
	}
	fclose(file);

	std::string content = file_get_contents(file_name);
	Json::Value document = JSONparse(content);
	//Console::log("Read file %s successfully.\n", file_name);
	int size = document["objects"]["data"].size();

	Json::Value data  = document["objects"]["data"];


	std::vector<Object*> r_object;

	ResourceManager* rc = ResourceManager::GetInstance();

	for(int i = 0; i < size; i++)
	{

		Json::Value item = data[i];

		const char* object_name = item["name"].asCString();
		const char* object_type = item["type"].asCString();


		r_object.push_back(NULL);

		switch(ObjectType::GetType(object_type))
		{
			case ObjectType::BOUNCE :
			{
				r_object[i] = new Bounce();
				break;
			};
			case ObjectType::TRIANGLE :
			{
				r_object[i] = new Triangle();
				break;
			};
			case ObjectType::HANDLER :
			{
				r_object[i] = new Handler();
				break;
			};
			case ObjectType::FOOD :
			{
				r_object[i] = new Food();
				break;
			};
			case ObjectType::BUTTON :
			case ObjectType::LEVELGAME :
			case ObjectType::LABEL :
			{
				Button *b = new Button();
				int cl;
				float cr, cg, cb, ca;
				cr = item["color"][cl = 0].asDouble();
				cg = item["color"][cl = 1].asDouble();
				cb = item["color"][cl = 2].asDouble();
				ca = item["color"][cl = 3].asDouble();
				b->color = Vector4(cr, cg, cb, ca);
				b->pixel_Size = item["pxSize"].asDouble();
				strcpy(b->value, item["value"].asCString());
				r_object[i] = b;
				break;
			};
			case ObjectType::THORN :
			{
				r_object[i] = new Thorn();
				break;
			}
			case ObjectType::TARGET:
			{
				r_object[i] = new Target();
				break;
			}
			default:
			{
				r_object[i] = new Box();
			}
		}

		int textureCount = item["texture"].size();
		r_object[i]->textureCount = textureCount;
		r_object[i]->texture = new Texture*[textureCount];
		for(int index = 0;index<textureCount;index++)
			r_object[i]->texture[index] = ResourceManager::GetInstance()->GetTextureById(item["texture"][index].asInt());

		r_object[i]->Id = item["id"].asInt();
		r_object[i]->SetName( object_name);
		strcpy(r_object[i]->type, object_type);
		r_object[i]->moveable = item["moveable"].asBool();

		//Model View
		float px, py, rz, sx, sy, tx, ty;
		int k;
		px = item["position"][k = 0].asDouble();
		py = item["position"][k = 1].asDouble();
		rz = item["rotation"][k = 0].asDouble();
		sx = item["scale"][k = 0].asDouble();
		sy = item["scale"][k = 1].asDouble();
		tx = item["tile"][k = 0].asDouble();
		ty = item["tile"][k = 1].asDouble();

		float scaleValue = 1;
		r_object[i]->position = Vector2(px*(scaleValue+1)/2, py*(scaleValue+1)/2);
		r_object[i]->SetAngleDeg(rz);
		r_object[i]->scale = Vector2(sx*scaleValue, sy*scaleValue);
		r_object[i]->tiling = Vector2(tx, ty);
	}
	return r_object;
}




void SceneManager::Init()
{
	this->sceneSplash = new Splash();
	this->sceneGame = new Game();
	this->sceneMenu = new MainMenu();
	this->sceneLevelMenu = NULL;
	this->sceneLoading = new Loading();
	this->sceneSetting = NULL;

	this->ChangeScene(this->sceneSplash);
	//this->currentScene = new Scene();

}




void SceneManager::Draw()
{

	/* BEFRORE DRAW*/
	//glEnable(GL_DEPTH_TEST);
	// Enable blending alpha

	 glEnable(GL_BLEND);
	 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* WHILE DRAW */


	 this->currentScene->Draw();




	/* END DRAW */
#ifdef WIN32
     
	//eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
#endif

}


void SceneManager::OnTourchDown(int x, int y)
{
	this->currentScene->OnTourchDown(x, y);
	lastMousePos.x = lastMouseDown.x = x;
	lastMousePos.y = lastMouseDown.y = y;
	tourchTime = 0;

	//Console::log("SceneManager::OnTourchDown(%d, %d); \n", x, y);
	
}

void SceneManager::OnTourchMove(int x, int y)
{

	this->currentScene->OnTourchMove(x, y);

	int dx = x - lastMousePos.x;
	int dy = y - lastMousePos.y;

	if(StateManager::GetInstance()->GetCurrentState() == STATE_MAP_EDITOR)
	{
		if(this->selectedObject != NULL)
		{
			selectedObject->position.x += dx;
			selectedObject->position.y += dy;
			void * object = selectedObject->GetUserData();
			if(object)
			{
				b2Body* body = (b2Body*)object;
				body->SetTransform(b2Vec2(pix2met(selectedObject->position.x), pix2met(selectedObject->position.y)), selectedObject->GetAngle());
			}
		}
	}


	lastMousePos.x = x;
	lastMousePos.y = y;
}

void SceneManager::OnTourchUp(int x, int y)
{
	this->currentScene->OnTourchUp(x, y);
	int dx = x - lastMouseDown.x;
	int dy = y - lastMouseDown.y;

	//Reset
	this->tourchTime = 0;
	this->selectedObject = 0;
}

void SceneManager::OnKeyDown(unsigned char keyChar)
{
	KeyManager::GetInstance()->SetKeyPress(keyChar);
	this->currentScene->OnKeyDown(keyChar);
	//Console::log("Key down: %c \n", keyChar);
}

void SceneManager::OnKeyUp(unsigned char keyChar)
{
	KeyManager::GetInstance()->UnKeyPress(keyChar);
	this->currentScene->OnKeyUp(keyChar);
}




void SceneManager::Update(float dt)
{	
	this->tourchTime += dt;

	if(KeyManager::GetInstance()->IsKeyPressed(KeyManager::S_KEY_ESC))
		exit(0);
	if(KeyManager::GetInstance()->IsKeyPressed(KeyManager::S_KEY_S))
		this->currentScene->camera->MoveInY(-dt);
	if(KeyManager::GetInstance()->IsKeyPressed(KeyManager::S_KEY_W))
		this->currentScene->camera->MoveInY(dt);
	if(KeyManager::GetInstance()->IsKeyPressed(KeyManager::S_KEY_A))
		this->currentScene->camera->MoveInX(-dt);
	if(KeyManager::GetInstance()->IsKeyPressed(KeyManager::S_KEY_D))
		this->currentScene->camera->MoveInX(dt);

	if(this->currentScene)
	{
		this->currentScene->camera->Update(dt);
		this->currentScene->Update(dt);
	}

}






void SceneManager::ContactProcess(Object* o1, Object* o2)
{
	Game* game = (Game*) this->currentScene;
	if(game)
	{
		game->ContactProcess(o1, o2);
	}
}




Camera* SceneManager::GetCamera()
{
	return this->currentScene->camera;
}



void SceneManager::OnResize()
{
	this->currentScene->OnSizeChange();
}

void SceneManager::ChangeScene(Scene* scene)
{
	this->currentScene = scene;
	this->currentScene->OnSizeChange();
}