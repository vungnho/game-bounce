#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "MvpMatrix.h"




class Object
{
public:
	Object(void);

	Object(Model* m, Texture** t, Shader* s);
	virtual ~Object(void);

    Object(const Object& o) { }
    //Object& operator=(const Object& o) {};
	virtual Object* clone() const { return new Object(*this); }


	Vector2 position;
	Vector2 scale;
	Texture** texture;
	int textureCount;
	Model* model;
	int modeldata[6];
	Shader* shader;
	char name[255];
	char type[255];
	int shapeType;
	bool moveable;

	bool hidden;


	void SetShapeType(const char * shapeType);
	char* GetShapeType();
	int GetType();
	Vector2 tiling;

	float mass;
	Vector2 velocity;

	GLuint matID;
	MvpMatrix srt;

	GLuint Id, vboId,iboId;

	virtual void SetName(const char* name);

	void swapTexture();
	void setTexture(GLuint id);
	void Buffer();
	void Bind();
	void UnBuffer();
	virtual void Draw();
	virtual void Update(float delta_time);
	Matrix GetSRTMatrix();
	virtual Matrix GetMVPMatrix();

	virtual bool IsInside(Vector2 point);

	virtual float GetWidth();
	virtual float GetHeight();
	void SetUserData(void* data);
	void* GetUserData();

	virtual void SetAngle(float radian);
	virtual float GetAngle();
	void SetAngleDeg(float deg);
	float GetAngleDeg();

	void startContact() { numContact++; }
	void endContact() { numContact--; }


	void ContactWith(Object* another);

	Vector2 TransformByView(Vector2 point);
	Vector2 TransformByWorld(Vector2 point);

	//being colision
	int numContact;

	virtual void scaleSelf();

private:
	Matrix mvp;
	void* userData;
	float angle;
protected:

	


};
