#include "StdAfx.h"
#include "Game.h"
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
#include "Button.h"
#include "Target.h"
#include "StateManager.h"
#include "ContactListener.h"
#include "CantactManager.h"

#include "Splash.h"
#include "Scene.h"
#include "JSON.h"
#include "MainMenu.h"
#include "LevelMenu.h"

#define RATIO 0.008f
#define pix2met(x) (RATIO*x)
#define met2pix(x) (x/RATIO)

Game::Game()
{
	this->bounce = NULL;
	this->touchPoint = NULL;
	this->touchMove = NULL;
	this->b2dWorld = NULL;
	this->score = NULL;
	this->level = 1;

	/* ENABLE OR DISABLE TOURCH TO MOVE*/
	this->useTouch = 0;
}

Game::~Game(void)
{
	Memory::Delete(objects);
	Memory::Delete(handlers);
	Memory::Delete(this->b2dWorld);
	Memory::Delete(this->score);
}


//Mouse Events
void Game::OnTourchDown(int x, int y)
{
    for (auto &handler : handlers)
	{
		if(handler->IsInside(Vector2(x, y)))
		{
			if(String::IsEquals(handler->name,"Arrow Left"))
			{
				SceneManager::GetInstance()->OnKeyDown(KeyManager::S_CHAR_LEFT);
                handler->swapTexture();
			}
			else if(String::IsEquals(handler->name,"Arrow Right"))
			{
				SceneManager::GetInstance()->OnKeyDown(KeyManager::S_CHAR_RIGHT);
                handler->swapTexture();
			}
			else if(String::IsEquals(handler->name,"Arrow Up"))
			{
				SceneManager::GetInstance()->OnKeyDown(KeyManager::S_CHAR_UP);
                handler->swapTexture();
			}
		}
	}
	/*  DISABLE FOR DEBUG */

	if(touchPoint!=NULL && touchMove!=NULL && this->useTouch)
	{
		touchPoint->position = Vector2(x,y);
		touchPoint->setTexture(2);
		touchMove->position = Vector2(x,y);
		touchMove->setTexture(2);
	}


};
void Game::OnTourchUp(int x,int y)
{
    for (auto &handler : handlers)
	{
		if(handler->IsInside(Vector2(x, y)))
		{
			if(String::IsEquals(handler->name,"Arrow Left"))
			{
				SceneManager::GetInstance()->OnKeyUp(KeyManager::S_CHAR_LEFT);
                handler->swapTexture();
			}
			else if(String::IsEquals(handler->name,"Arrow Right"))
			{
				SceneManager::GetInstance()->OnKeyUp(KeyManager::S_CHAR_RIGHT);
                handler->swapTexture();
			}
			else if(String::IsEquals(handler->name,"Arrow Up"))
			{
				SceneManager::GetInstance()->OnKeyUp(KeyManager::S_CHAR_UP);
                handler->swapTexture();
			}
			else if(String::IsEquals(handler->name, "Reload"))
			{
				SceneManager::GetInstance()->ChangeScene(SceneManager::GetInstance()->sceneLoading);
			}
			else if(String::IsEquals(handler->name, "Pause"))
			{
				SceneManager::GetInstance()->OnKeyUp(KeyManager::S_CHAR_P);
			}
			else if(String::IsEquals(handler->name, "Replay"))
			{
				SceneManager::GetInstance()->ChangeScene(SceneManager::GetInstance()->sceneLoading);
			}
			else if(String::IsEquals(handler->name, "Next Level"))
			{
				this->level++;
				score->logScore();
				SceneManager::GetInstance()->ChangeScene(SceneManager::GetInstance()->sceneLoading);
			}
			break;
		}

	}

	if(touchPoint!=NULL && touchMove!=NULL  && this->useTouch)
	{
		touchPoint->position = Vector2();
		touchPoint->setTexture(1);
		touchMove->position = Vector2();
		touchMove->setTexture(1);
	}
	
};
void Game::OnTourchMove(int x, int y)
{
	if(touchPoint!=NULL && touchMove!=NULL  && this->useTouch)
	{
		//touchPoint->position = touchMove->position;
		touchMove->position = Vector2(x,y);
		touchMove->setTexture(2);

	}
};

//Key Events
void Game::OnKeyDown(unsigned char keyChar)
{

}
void Game::OnKeyUp(unsigned char keyChar)
{
	if(keyChar == KeyManager::S_CHAR_P)
	{
		if(!SceneManager::GetInstance()->sceneMenu)
		{
			SceneManager::GetInstance()->sceneMenu = new MainMenu();
			SceneManager::GetInstance()->sceneLevelMenu= new LevelMenu();
		}
		SceneManager::GetInstance()->ChangeScene(SceneManager::GetInstance()->sceneMenu);
	}
	//KeyManager::GetInstance()->UnAllKeyPress();
};

void Game::DrawText(int x, int y, Vector4 color)
{
	GLfloat textHeight = 50.0f;
    GLfloat s = 50.0f + x;
    GLfloat t = Globals::screenHeight - textHeight + y;
	TextManager::GetInstance()->RenderString("Level", color, s, t, 64);
	TextManager::GetInstance()->RenderNumber( this->level, color,s + 80, t,64);
	TextManager::GetInstance()->RenderString("Score", color, s + 150, t,64);
	TextManager::GetInstance()->RenderString(score->getStringScore(), color,s + 250, t,64);
	TextManager::GetInstance()->RenderString("HScore", color, s + 350, t,64);
	TextManager::GetInstance()->RenderString(score->getStringHightScore(), color,s + 460, t,64);
	Vector2 pos = score->position - camera->GetPosition();
	TextManager::GetInstance()->RenderString(score->getStringScorePlus(), color, pos.x+x, pos.y+y+50,64);
	return;
}
void Game::Draw()
{
    for (auto &object : objects)
	{
		object->Draw();
	}
	
    for (auto &handler : handlers)
	{
        handler->Draw();
	}

	/* DRAW TEXT IN SCREEN */
	//this->DrawText(-1, -1, Vector4(0.7, 0.7, 0.7, 0.8));
	this->DrawText(1, 1, Vector4(0.7f, 0.7f, 0.7f, 0.8f));
	this->DrawText(0, 0, Vector4(1, 1, 1, 0.8f));
	if(game_over)
	{
		
		float scaleX = (float)Globals::screenWidth/ Globals::screenWidthRatio;
		float scaleY = (float)Globals::screenHeight/ Globals::screenHeightRatio;
		float scale = scaleX>scaleY ? scaleY : scaleX;
		scaleX = scaleX > scale ? (scaleX + 1)/2 : scaleX;
		scaleY = scaleY > scale ? (scaleY + 1)/2 : scaleY;

        unsigned int pixelSize = (unsigned int) (200 * scale);
		if(this->complete)
		{
			TextManager::GetInstance()->RenderString("Level Complete!",Vector4(0.9f, 0.7f, 0.1f, 0.8f),80*scaleX,380*scaleY, pixelSize);
			TextManager::GetInstance()->RenderString(score->getStringScore(),Vector4(0.8f, 0.1f, 0.1f, 0.8f),350*scaleX,280*scaleY, pixelSize);
		}
		else
		{
			TextManager::GetInstance()->RenderString("Game Over!",Vector4(0.8f, 0.8f, 0.3f, 0.8f),170*scaleX,390*scaleY, pixelSize);
			TextManager::GetInstance()->RenderString(score->getStringScore(),Vector4(0.8f, 0.1f, 0.1f, 0.8f),380*scaleX,280*scaleY, pixelSize);
		}
	}



};
void Game::Update(float dt)
{
	if(KeyManager::GetInstance()->IsKeyPressed(KeyManager::S_KEY_R))
	{
		SceneManager::GetInstance()->currentScene = SceneManager::GetInstance()->sceneLoading;
	}
    for (auto &handler : handlers)
	{
        handler->Update(dt);
	}


	if(coolDownTime>0)
	{
		coolDownTime-=dt;
	}
	else
	if(!this->game_over && bounce)
	{
		//KeyManager::GetInstance()->SetKeyPress(keyChar);
		b2Body* body = (b2Body*)this->bounce->GetUserData();
		b2Vec2 v = body->GetLinearVelocity();
		b2Vec2 vChange = v;
		if(KeyManager::GetInstance()->IsKeyUpPressed())
		{

			//Bounce Jump
			if(this->bounce->numContact > 0)
			{
				b2Body* body =  (b2Body*)bounce->GetUserData();
				vChange.y = 5;
			}
			
		}
		if(KeyManager::GetInstance()->IsKeyRightPressed() && !KeyManager::GetInstance()->IsKeyLeftPressed())
		{
			vChange.x = 2;
		}
		if(KeyManager::GetInstance()->IsKeyLeftPressed() && !KeyManager::GetInstance()->IsKeyRightPressed())
		{
			vChange.x = -2;
		}
		if(touchPoint!=NULL && touchMove!=NULL)
		{
			Vector2 deltaTouch = touchMove->position - touchPoint->position;
			Vector2 adt = Vector2(fabs(deltaTouch.x),fabs(deltaTouch.y));
			float k = 30;
			if(adt.x>k || deltaTouch.y>k)
			{
				if(adt.x*adt.y == 0)
				{
					adt.x = (!adt.x) ? 1 : adt.x;
					adt.y = (!adt.y) ? 1 : adt.y;
				}
				if(adt.x>k && adt.y/adt.x<6)
				{
					vChange.x = 2*deltaTouch.x/adt.x;
				}
				if(deltaTouch.y>k && this->bounce->numContact > 0 && adt.x/adt.y<6)
				{
					vChange.y = 5;
				}

			}
		}	
		
		body->SetLinearVelocity(vChange);
		this->coolDownTime = CDTIME_KEY_PRESS;
	}

	if(this->b2dWorld)
	{
		b2dWorld->Step(dt, 8, 3);
	}

	while(recycleBin.size())
	{
		this->RemoveObject(recycleBin.back());
		recycleBin.pop_back();
	}


	b2Body* body = b2dWorld->GetBodyList();

	while(body != NULL)
	{
			//Get object in b2dBody
			Object* obj  = (Object*)body->GetUserData();
			//Update Position
			obj->position = Vector2(met2pix(body->GetPosition().x), met2pix(body->GetPosition().y));
			obj->SetAngle(body->GetAngle());
			obj->Update(dt);
			body = body->GetNext();

			//Remove very low object
			if(obj->position.y < -5000)
			{
				//Console::log("Object %s has been removed.\n", obj->name);
				if(obj->GetType()==ObjectType::BOUNCE)
				{
					bounce = NULL;
					EndGame(false);
				}
				this->RemoveObject(obj);
			}

			
	}



	if(this->bounce)
	{
		float lim_left = Globals::screenWidth*0.2f;
		float lim_right = Globals::screenWidth*0.8f;
		float lim_top = Globals::screenHeight*0.8f;
		float lim_bottom = Globals::screenHeight*0.2f;

		Vector2 d = this->bounce->position - this->camera->GetPosition();

		if(d.x > lim_right)
		{
			this->camera->position.x = this->bounce->position.x - lim_right;
			this->camera->target.x = this->bounce->position.x - lim_right;
		}
		else if(d.x < lim_left)
		{
			this->camera->position.x = this->bounce->position.x - lim_left;
			this->camera->target.x = this->bounce->position.x - lim_left;
		}
		if(d.y > lim_top)
		{
			this->camera->position.y = this->bounce->position.y - lim_top;
			this->camera->target.y = this->bounce->position.y - lim_top;
		}
		else if(d.y < lim_bottom)
		{
			this->camera->position.y = this->bounce->position.y - lim_bottom;
			this->camera->target.y = this->bounce->position.y - lim_bottom;
		}

		//Reduce velocity of bounce by the time.
		if(bounce->numContact > 0)
		{
			ReduceLovecity();
		}

		score->update(dt);

	}

};





Object* Game::GetObjectByName(char* name)
{
    for (auto &object : objects)
	{
		if(String::IsEquals(name, object->name))
		{
			return object;
		}
	}
	return NULL;
}
Object* Game::GetHandlerByName(char* name)
{
    for (auto &handler : handlers)
	{
		if(String::IsEquals(name, handler->name))
		{
			return handler;
		}
	}
	return NULL;
}

void Game::ReduceLovecity()
{
	b2Body* body = (b2Body*)GetObjectByName("Bounce")->GetUserData();
	if(body)
	{
		b2Vec2 v = body->GetLinearVelocity();
		body->SetLinearVelocity(b2Vec2(v.x*0.98f, v.y));
	}
}



//Scale must have object in body userdata
void Game::ScaleBody(b2Body* body, float ratio)
{

	Object* obj = (Object*) body->GetUserData();
	b2Fixture* b2f = body->GetFixtureList();
	while(b2f)
	{

		if(b2f->GetType() == b2Shape::e_circle)
		{
			//Scale circle
			b2f->GetShape()->m_radius *= ratio;
		}
		else
		{

			  b2PolygonShape *poly = (b2PolygonShape*)b2f->GetShape();

			  int count = poly->GetVertexCount();

			  b2Vec2 v[9999];

			  for( int i = 0; i < poly->GetVertexCount(); i++ )
			  {
				  b2Vec2 tr = poly->GetVertex(i);
				  v[i] = b2Vec2(tr.x * obj->scale.x, tr.y * obj->scale.y);
			  }
			  poly->Set(v, poly->GetVertexCount());

		}




		b2f = b2f->GetNext();
	}



}


void Game::AddObjectToWorld(Object *o)
{

		Object* obj = o;
		b2BodyDef defObj;
		defObj.position.Set(pix2met(obj->position.x), pix2met(obj->position.y));
		defObj.type = obj->moveable ? b2_dynamicBody : b2_staticBody;
		b2Body* body = b2dWorld->CreateBody(&defObj);

		body->SetUserData(obj);
		obj->SetUserData(body);

		body->SetLinearVelocity( b2Vec2(obj->velocity.x, obj->velocity.y));
		if(obj->shapeType == Shape::CIRCLE)
		{
			b2CircleShape circle;
			circle.m_radius = pix2met((obj->GetWidth()*obj->scale.x)/2);
			//Console::log("SM class. Line 380: %f\n", circle.m_radius);
			GLfloat density = 500;
			body->CreateFixture(&circle, density);
			
		}
		else
		{
			//Định nghĩa hình dạng cho mặt đất.
			b2PolygonShape polygon;

			int numvertex = obj->model->numVertex;
			Vertex* obj_vertexs = obj->model->vertexes;
			b2Vec2 vertexs[9999];

			for(int j = numvertex - 1; j >= 0; j--)
			{
				vertexs[j].Set(pix2met(obj_vertexs[j].Position.x*obj->scale.x), pix2met(obj_vertexs[j].Position.y*obj->scale.y));
			}

			polygon.Set(vertexs, numvertex);

			//Tạo ra hình dạng cho groundBody như đã định nghĩa.
			b2Fixture* fix = body->CreateFixture(&polygon, 10);
			//Độ ma sát [0 -> 1]
			fix->SetFriction(0.5);
			//Độ nảy của vật  [0 -> 1]
			fix->SetRestitution(0.1f);
		}
		//tính lại khối lượng
		body->ResetMassData();
		//Đặt góc quay cho vật
		body->SetTransform(body->GetPosition(), obj->GetAngle());

		//this->objects.push_back(obj);

}

void Game::InitBox2D()
{


	b2Vec2 l_gravity = b2Vec2(0.0f, -9.8f);
	Memory::Delete(b2dWorld);
	b2dWorld = new b2World(l_gravity);

    for (auto &object : objects)
	{
		if(object->GetType() != ObjectType::BACKGROUND)
			AddObjectToWorld(object);
	}

	b2dWorld->SetContactListener((ContactListener::GetInstance()));

}




void renameObject(Object* object, const char* new_name)
{
	object->SetName(new_name);
}

void Game::RemoveObject(Object* o)
{
	//Console::log("%s has been destroyed.\n", o->name);
	b2Body* body = (b2Body*)o->GetUserData();
	//remove from graphics
	objects.erase(std::remove(objects.begin(), objects.end(), o), objects.end());
	delete o;

	body->SetUserData(NULL);
	//remove from world
	b2dWorld->DestroyBody(body);
	//body->GetWorld()->DestroyBody( body );
	body = NULL;

}

void Game::ContactProcess(Object* o1, Object* o2)
{
	if(this->game_over && (o1 == bounce || o2 == bounce))return;
	if((bounce == o1 && o2->GetType() == ObjectType::FOOD) || (bounce == o2 && o1->GetType() == ObjectType::FOOD))
	{
		score->addNumScore();
		score->position = (o1->position + o2->position)/2;
		//Console::log("Bounce have just ate food (%d).\n", score->getNumScore());
		if(o1->GetType() == ObjectType::FOOD)
		{
			recycleBin.push_back(o1);
		}
	}

	if((bounce == o1 && o2->GetType() == ObjectType::CLOUD) || (bounce == o2 && o1->GetType() == ObjectType::CLOUD))
	{
		score->addNumScore(100);
		score->position = (o1->position + o2->position)/2;
		//Console::log("Bounce have just ate cloud (%d).\n", score->getNumScore());
		if(o1->GetType() == ObjectType::CLOUD)
		{
			recycleBin.push_back(o1);
		}
	}

	if((bounce == o1 && o2->GetType() == ObjectType::THORN) || (bounce == o2 && o1->GetType() == ObjectType::THORN))
	{
		score->addNumScore(-score->getNumScore());
		score->position = (o1->position + o2->position)/2;
		score->setDefault();
		EndGame(false);
		//Console::log("Bounce have just die.\n");
	}
	if((bounce == o1 && o2->GetType() == ObjectType::TARGET) || (bounce == o2 && o1->GetType() == ObjectType::TARGET))
	{
		EndGame(true);
		//Console::log("Level complete.\n");

		//Load Endgame Handle;
		while(handlers.size())
		{
			delete handlers.back();
			handlers.pop_back();
		}
		const char * s = String::concat(BOUNCE_DATA_LOCATION, "Data/EndGame.json");
		this->handlers = SceneManager::ReadMapFromJSON(s);
		delete[] s;
		//Rebind Handle
        for (auto &handler : handlers)
		{
            handler->scaleSelf();
            handler->Bind();
		}

		score->saveScore();
	}
}


void Game::EndGame(bool win)
{
	this->complete = win;
	this->game_over = true;
	touchMove->setTexture(1);
	touchPoint->setTexture(1);
	touchMove = NULL;
	touchPoint = NULL;
}

void Game::LoadLevel(int level)
{

	Memory::Delete(objects);
	Memory::Delete(handlers);

	const char * s = String::concat(BOUNCE_DATA_LOCATION, "Data/Handler.json");
	this->handlers = SceneManager::ReadMapFromJSON(s);
	delete[] s;

    for (auto &handler : handlers)
	{
        handler->Bind();
	}


	/* Align top top item*/
	Initcontrol();
	int margin = 10;
    //for (auto &handlerT : handlerTop)
    int handlerTopSize = this->handlerTop.size();
    for (int i = 0; i < handlerTopSize; i++)
	{
        handlerTop[i]->position.x = Globals::screenWidth - (handlerTop[i]->GetWidth() + 20)*(i+1);
        handlerTop[i]->position.y = Globals::screenHeight - handlerTop[i]->GetHeight()/2 - margin;
	}


	char* L = new char[256]; //{"Level0.json", "Level1.json"};
	sprintf ( L, "Data/Level%d.json", level-1 );
	s = String::concat(BOUNCE_DATA_LOCATION, L);
	this->objects  = SceneManager::ReadMapFromJSON(s);
	delete[] L;
	delete[] s;
	if(this->objects.size()==0)
	{
		this->level = 1;
		this->objects  = SceneManager::ReadMapFromJSON(String::concat(BOUNCE_DATA_LOCATION, "Data/Level0.json"));
	}
	//binding
    for (auto &object : objects)
	{
        object->Bind();
	}

	bounce = (Bounce*)GetObjectByName("Bounce");
	touchPoint = (Handler*)GetHandlerByName("Touch Point");
	touchMove = (Handler*)GetHandlerByName("Touch Move");
	touchPoint->position = Vector2(0, 0);
	touchMove->position = Vector2(0, 0);
	InitBox2D();
}



void Game::Initialaze()
{

	this->game_over = false;

	Memory::Delete(this->score);
	this->score = new Score();
	this->LoadLevel( this->level);


}

void Game::Initcontrol()
{
	this->handlerTop.clear();
	Object* os[] = {this->GetHandlerByName("Pause"), this->GetHandlerByName("Reload"), NULL};
	int i = 0;
	while(os[i])
	{
		this->handlerTop.push_back(os[i]);
		i++;
	}
}