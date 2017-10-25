#pragma once
#include <Utilities/MyMath.h>
#include "MvpMatrix.h"
class Camera
{
public:
	Camera(void);
	~Camera(void);

	float nearPlane;
	float farPlane;
	float aspect;
	float fovY;
	float moveSpeed;
	float rotateSpeed;
	//van toc hien tai cua camera
	float velMovingY;
	float velMovingX;
	float velRotatingV;
	float velRotatingH;


	MvpMatrix matrix;
	Vector3 position;
	Vector3 up;
	Vector3 target;

	void LookAt(Vector3 target);
	void RotateVertical(float d);
	void RotateHorizontal(float d);
	void MoveInY(float dy);
	void MoveInX(float dx);

	void Update(float delta_time);

	Matrix GetProjectMatrix();
	Matrix GetViewMatrix();
	void SetOrtho(GLfloat leftPlane, GLfloat rightPlane, GLfloat bottomPlane, GLfloat topPlane, GLfloat nearPlane, GLfloat farPlane);
	void SetPerspective();

	Vector2 GetPosition();
	void SetPosition(Vector2 v);

private:
	Matrix projectView;



};
