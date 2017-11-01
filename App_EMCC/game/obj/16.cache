#include "StdAfx.h"
#include "Object.h"
#include "Memory.h"
#include "SceneManager.h"
#include "ObjectType.h"
#include  <cstdlib>
#include "Geometry.h"
#include "Shape.h"
#include "String.h"
#include "myDefines.h"
#include "ResourceManager.h"
#include "Console.h"
#include "Globals.h"

Object::Object():tiling(Vector2(1,1))
{
	shapeType = Shape::POLYGON;
	this->moveable = false;
	this->SetUserData(NULL);
	this->vboId = -1;
	this->iboId = -1;
}
void Object::SetShapeType(const char * shape_Type)
{
	if(String::IsEquals(shape_Type, "circle"))
	{
		shapeType = Shape::CIRCLE;
		return;
	}
	if(String::IsEquals(shape_Type, "rect"))
	{
		shapeType = Shape::RECT;
		return;
	}
	if(String::IsEquals(shape_Type, "triagle"))
	{
		shapeType = Shape::TRIANGLE;
		return;
	}
	if(String::IsEquals(shape_Type, "polygon"))
	{
		shapeType = Shape::POLYGON;
		return;
	}
}

char* Object::GetShapeType()
{
	if(shapeType == Shape::CIRCLE)
	{
		return "circle";
	}
	if(shapeType = Shape::RECT)
	{
		
		return "rect";
	}
	if(shapeType = Shape::TRIANGLE)
	{
		
		return "triagle";
	}
	if(shapeType = Shape::POLYGON)
	{
		
		return "polygon";
	}
}




Object::Object(Model* m, Texture** t, Shader* s):tiling(Vector2(1,1))
{
	this->model = m;
	this->texture = t;
	this->shader = s;
	this->mass = 1.0;
	this->velocity = Vector2(0, 0);
	this->userData = NULL;
	this->moveable = true;
	this->numContact = 0;
	this->SetUserData(NULL);
	this->vboId = -1;
	this->iboId = -1;
}
void Object::scaleSelf()
{
	float scaleX = (float)Globals::screenWidth/800;
	float scaleY = (float)Globals::screenHeight/600;
	float scale = scaleX>scaleY ? scaleY : scaleX;
	scaleX = scaleX > scale ? (scaleX + 1)/2 : scaleX;
	scaleY = scaleY > scale ? (scaleY + 1)/2 : scaleY;

	this->position = Vector2(position.x*scaleX, position.y*scaleY);
	this->scale *= scale;
}

Object::~Object(void)
{
	Memory::Delete(this->texture);
	glDeleteBuffers(1, &(vboId));

	glDeleteBuffers(1, &(iboId));

}
void Object::swapTexture()
{
	if(textureCount < 2) return;
	Texture *t0 = texture[0];
	for(GLuint i=0; i<textureCount-1; i++)texture[i]=texture[i+1];
	texture[textureCount-1]=t0;
}
void Object::setTexture(GLuint id)
{
	if(textureCount<3 || id>textureCount-1 || id<1) return;
	texture[0] = texture[id];
}
void Object::Buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboId);
}

void Object::Bind()
{
	//buffer object
	glGenBuffers(1, &(vboId));
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, model->GetVertexSize(), model->GetVertexPointer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	//int indicesData[] = {0, 1, 2};
	//buffer object
	glGenBuffers(1, &(iboId));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->GetIndiceSize(), model->GetIndicePointer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::UnBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::SetName(const char* name)
{
	strcpy(this->name, name);
}

void Object::Draw()
{

	glUseProgram(this->shader->program);
	this -> Buffer();
	
	// Enable Vertex if able
	if(this->shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(this->shader->positionAttribute);
		glVertexAttribPointer(this->shader->positionAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VERTEX_POS);
	}
	// Enable Texture if able
	if(this->shader->textureAttribute != -1)
	{
		glEnableVertexAttribArray(this->shader->textureAttribute);
		glVertexAttribPointer(this->shader->textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*) 0 + VERTEX_UV);
		
	}

	//Set mvp matrix
	this->shader->SetUniform("u_mvp", this->GetMVPMatrix());

	//Set matrix world
	this->shader->SetUniform("u_world", this->srt.GetSRTMatrix());

	//Set camera position
	this->shader->SetUniform("u_EyePos", SceneManager::GetInstance()->GetCamera()->position);
	/*
	//Set Fog Value
	this->shader->SetUniform("u_fogStart", SceneManager::GetInstance()->fog.fogStart);
	this->shader->SetUniform("u_fogRange", SceneManager::GetInstance()->fog.fogRange);
	this->shader->SetUniform("u_fogColor", SceneManager::GetInstance()->fog.fogColor);
	*/
	//set tiling value
	this->shader->SetUniform("u_tile", this->tiling);

	//binding texture
	for(int j = 0; j < textureCount; j++)
	{
		if(this->shader->uftLoc[j] != -1)
		{
			//Activation Texture
			glActiveTexture(GL_TEXTURE0 + j);

			this ->texture[j] ->Bind();
			//glUniform1i(this->shader->uftLoc[j], j);
		}
	}


	//glDrawArrays( GL_TRIANGLES, 0, 3);


	glDrawElements(GL_TRIANGLES, this-> model->numIndice , GL_UNSIGNED_INT, (const void*)0);

	//glDrawArrays(GL_TRIANGLES, 0, this-> model->numVertex);
	//unbinding texture
	glBindTexture(GL_TEXTURE_2D, 0);
	this-> UnBuffer();

}

void Object::Update(float delta_time)
{

	if(this->numContact)
	{
	}
}



Vector2 Object::TransformByView(Vector2 point)
{
	Vector4 a4(point.x, point.y, 0, 1);
	Vector4 b4 = a4 * this->GetSRTMatrix();
	return Vector2(b4.x, b4.y);
}


bool Object::IsInside(Vector2 point)
{
	int inside = 0;
	for(int i = 0; i < model->numIndice;)
	{
		
			inside |= Geometry::PointInTriangle(point,
				TransformByView(model->vertexes[model->indices[i++]].Position),
				TransformByView(model->vertexes[model->indices[i++]].Position),
				TransformByView(model->vertexes[model->indices[i++]].Position));
		

	}
	return inside;
}


Matrix Object::GetSRTMatrix()
{
	//return srt.GetSRTMatrix();
	return Matrix().SetScale(this->scale.x, this->scale.y, 1) * Matrix().SetRotationZ(this->angle) * Matrix().SetTranslation(this->position.x, this->position.y, 0);
}


Matrix Object::GetMVPMatrix()
{
	return 	this->mvp = this->GetSRTMatrix()*
		SceneManager::GetInstance()->GetCamera()->GetViewMatrix()*
		SceneManager::GetInstance()->GetCamera()->GetProjectMatrix();
}

float Object::GetWidth()
{
	int min = this->model->vertexes[0].Position.x;// * this->scale.x;
	int max = min;
	for(int i = 1; i < this->model->numVertex; i++)
	{
		int x = this->model->vertexes[i].Position.x;// * this->scale.x;
		min = x < min ? x : min;
		max = x > max ? x : max;
	}
	return (max - min);
}

float Object::GetHeight()
{
	int min = this->model->vertexes[0].Position.y;// * this->scale.y;
	int max = min;
	for(int i = 1; i < this->model->numVertex; i++)
	{
		int x = this->model->vertexes[i].Position.y;// * this->scale.y;
		min = x < min ? x : min;
		max = x > max ? x : max;
	}
	return (max - min);
}

void Object::SetUserData(void *data)
{
	this->userData = data;
}

void* Object::GetUserData()
{
	return this->userData;
}


void Object::SetAngle(float rad)
{
	rad = fmod(rad,2*PI);
	angle = rad;
	srt.SetRotate(0, 0, rad);
}

void Object::SetAngleDeg(float deg)
{
	SetAngle(DEG_2_RAG(deg));
}
float Object::GetAngleDeg()
{
	return RAG_2_DEG(angle);
}
float Object::GetAngle()
{
	return angle;
}


void Object::ContactWith(Object* o2)
{
	//Console::log("%s contact with %s.\n", this->name, o2->name);
	SceneManager::GetInstance()->ContactProcess(this, o2);
}

int Object::GetType()
{
	return ObjectType::GetType(this->type);
}
