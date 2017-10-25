#include "StdAfx.h"
#include "MapEditor.h"
#include "Memory.h"
#include "SceneManager.h"
#include "Bounce.h"
#include "Box.h"
#include "Food.h"
#include "Triangle.h"
#include "Thorn.h"
#include "Button.h"
#include "Target.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "Memory.h"
#include "ObjectType.h"
#include "Bounce.h"
#include "Box.h"
#include "Food.h"
#include "Triangle.h"
#include "Thorn.h"
#include "Target.h"
#include <fstream>
#include <iostream>
#include <json/json.h>

MapEditor::MapEditor():Scene()
{
	this->selectedObject = NULL;
	
	std::cout << "Nhap ten file: ";
	std::string input;
	std::getline(std::cin, input);
	strcpy(this->fileName ,input.c_str());
	this->LoadMap(this->fileName);
}

MapEditor::~MapEditor(void)
{
	while(objects.size())
	{
		delete objects.back();
		objects.pop_back();
	}
}

//Mouse Events
void MapEditor::OnTourchDown(int x, int y)
{

	lastMousePos.x = lastMouseDown.x = x;
	lastMousePos.y = lastMouseDown.y = y;
	tourchTime = 0;

	/*MAP EDITOR*/

	Vector2 real_point = Vector2(x + this->camera->position.x, y + this->camera->position.y);
	//Console::log("Mouse is at [%.0f, %.0f ].\n", real_point.x, real_point.y);

	for(int i = 0; i < objects.size(); i++)
	{
		Object* o = objects[i];
		bool is_inside = o->IsInside(real_point);
		if(is_inside)
		{
			this->selectedObject = objects[i];
			Console::log("%s selected.\n", this->selectedObject->name);
		}

	}



};
void MapEditor::OnTourchUp(int x,int y)
{

	int dx = x - lastMouseDown.x;
	int dy = y - lastMouseDown.y;


	//Reset
	this->tourchTime = 0;

	this->selectedObject = 0;
	
};
void MapEditor::OnTourchMove(int x, int y)
{

	int dx = x - lastMousePos.x;
	int dy = y - lastMousePos.y;


	if(this->selectedObject != NULL)
	{
		selectedObject->position.x += dx;
		selectedObject->position.y += dy;
	}


	lastMousePos.x = x;
	lastMousePos.y = y;

};

//Key Events
void MapEditor::OnKeyDown(unsigned char keyChar)
{
//CTRL + S: save
	//if(KeyManager::GetInstance()->IsKeyPressed(KeyManager::S_KEY_CTRL))
	{
		if(KeyManager::GetInstance()->IsKeyPressed(KeyManager::S_KEY_F))
		{
			SaveScence();
			return;
		}
	}
	//Console::log("%c pressed.\n", keyChar);
	//CTRL + C: copy to clipple
	//if(KeyManager::GetInstance()->IsKeyPressed(KeyManager::S_KEY_CTRL))
	{
		if(keyChar == KeyManager::S_CHAR_C)
		{
			clipple = selectedObject;
			//Console::log("Copying %s...", clipple->name);
			return;
		}

	}
	//CTRL + V: paste to clipple
	//if(KeyManager::GetInstance()->IsKeyPressed(KeyManager::S_KEY_CTRL))
	{
		if(keyChar == KeyManager::S_CHAR_V)
		{
			Object* o = CopyObject(clipple);
			o->Bind();
			o->position = Vector2(camera->position.x, camera->position.y)  + this->lastMousePos;
			//Adding a object
			this->objects.push_back(o);
			return;
		}
	}


}
void MapEditor::OnKeyUp(unsigned char keyChar)
{
	if(keyChar == KeyManager::S_CHAR_Q)
	{
		delete this;
		SceneManager::GetInstance()->currentScene = SceneManager::GetInstance()->sceneMenu;
	}
};


void MapEditor::Draw()
{
	for(int i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->Draw();
	}
};
void MapEditor::Update(float delta_time)
{
	if(KeyManager::GetInstance()->IsKeyPressed(KeyManager::S_KEY_R))
	{
		this->LoadMap(this->fileName);
		KeyManager::GetInstance()->UnKeyPress(KeyManager::S_KEY_R);
	}
};

void MapEditor::LoadMap(const char *file_name)
{

	while(objects.size())
	{
		delete objects.back();
		objects.pop_back();
	}

	this->objects  = SceneManager::ReadMapFromJSON(file_name);

	//binding
	for(int i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->Bind();
	}
}


Object* MapEditor::CopyObject(Object *o)
{


	Object* object;

	switch(ObjectType::GetType(o->type))
	{
		case ObjectType::BOUNCE :
		{
			object = new Bounce();
			break;
		};
		case ObjectType::TRIANGLE :
		{
			object = new Triangle();
			break;
		};
		case ObjectType::HANDLER :
		{
			object = new Handler();
			break;
		};
		case ObjectType::FOOD :
		{
			object = new Food();
			break;
		};
		case ObjectType::THORN :
		{
			object = new Thorn();
			break;
		};
		default:
		{
			object = new Box();
		}
	}



	object->textureCount = o->textureCount;
	object->texture = new Texture*[o->textureCount];

	for(int j = 0; j < o->textureCount; j++)
	{
		object->texture[j] = o->texture[j];
	}

	object->Id = objects.size()+9999+1;

	object->SetName( o->name);
	strcpy(object->type, o->type);
	object->moveable = o->moveable;

	object->position = o->position;
	object->SetAngle(o->GetAngle());
	object->scale = o->scale;
	object->tiling = o->tiling;

	//Console::log("%s coppied.\n", object->name);

	return object;
}




void MapEditor::SaveScence()
{

	std::ofstream out(this->fileName);
	Json::Value document;

	document["objects"] = Json::Value();

	//document["objects"]["size"] = objects.size();


	for(int i = 0; i < this->objects.size(); i++)
	{
		Json::Value t_obj;
		t_obj["id"] = i;//objects[i]->Id;
		t_obj["moveable"] =  this->objects[i]->moveable;
		t_obj["name"] = this->objects[i]->name;
		int k = 0;
		t_obj["position"][k = 0] = int(this->objects[i]->position.x + 0.5);
		t_obj["position"][k = 1] = int(this->objects[i]->position.y + 0.5);
		t_obj["rotation"][k = 0] = int(this->objects[i]->GetAngleDeg() + 0.5);
		t_obj["scale"][k = 0] = this->objects[i]->scale.x;
		t_obj["scale"][k = 1] = this->objects[i]->scale.y;
		t_obj["tile"][k = 0] = this->objects[i]->tiling.x;
		t_obj["tile"][k = 1] = this->objects[i]->tiling.y;
		//t_obj["textures"] = objects[i]->textureCount;
		for(int j = 0; j < this->objects[i]->textureCount; j++)
		{
			t_obj["texture"][j] = this->objects[i]->texture[j]->Id;
		}
		t_obj["type"] = this->objects[i]->type;

		if( this->objects[i]->GetType() == ObjectType::BUTTON || 
			this->objects[i]->GetType() == ObjectType::LEVELGAME ||
			this->objects[i]->GetType() == ObjectType::LABEL)
		{
			t_obj["pxSize"] = ((Button*) this->objects[i])->pixel_Size;
			t_obj["value"] = ((Button*) this->objects[i])->value;
			t_obj["color"][k = 0] = ((Button*) this->objects[i])->color.x;
			t_obj["color"][k = 1] = ((Button*) this->objects[i])->color.y;
			t_obj["color"][k = 2] = ((Button*) this->objects[i])->color.z;
			t_obj["color"][k = 3] = ((Button*) this->objects[i])->color.w;
		}

		document["objects"]["data"][i] = t_obj;
	}

	Json::StyledWriter writer;
	out << writer.write(document);

    out.close();
    Console::log("Saved Scence.\n");
}


