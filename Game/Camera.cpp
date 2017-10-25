
#include "Camera.h"
#include "MvpMatrix.h"
#include <math.h>
#include "Globals.h"
#include <Utilities/esUtil.h>

Camera::Camera(void):  moveSpeed(200.0), rotateSpeed(2.0), velMovingY(1), velMovingX(1), velRotatingV(0), velRotatingH(0)
{
	this->up = Vector3(0, 1, 0);
	this->position = Vector3(0, 0, 1);
	this->target = Vector3(0, 0, 0);
	this->fovY = 1.0f;
	this->aspect = 2.0;
	this->nearPlane = 0.1;
	this->farPlane = 500;

	if(0)
	{
		this->SetPerspective();
	}
	else
	{
		this->SetOrtho(0, Globals::screenWidth, 0, Globals::screenHeight, -1.0, 1.0);
		glDepthMask(GL_FALSE);
	}

}

Camera::~Camera(void)
{
}

void Camera::LookAt(Vector3 target)
{
	this->target = target;
}

Matrix Camera::GetViewMatrix()
{
	Vector3 direction = (this->position - this->target).Normalize();
	Vector3 cameraRight =  this->up.Cross(direction).Normalize();
	Vector3 cameraUp = direction.Cross(cameraRight);
	return MvpMatrix::CreateMatrix
	(
		Vector4(cameraRight.x, cameraUp.x, direction.x, 0), 
		Vector4(cameraRight.y, cameraUp.y, direction.y, 0),
		Vector4(cameraRight.z, cameraUp.z, direction.z, 0),
		Vector4(-position.Dot(cameraRight), -position.Dot(cameraUp), -position.Dot(direction), 1)
	);
}

Matrix Camera::GetProjectMatrix()
{
	//return Matrix().SetPerspective(this->fovY, this->aspect, this->nearPlane, this->farPlane);

	return this->projectView;
}

void Camera::SetPerspective()
{
	this->projectView = Matrix().SetPerspective(this->fovY, this->aspect, this->nearPlane, this->farPlane);
}
void Camera::SetOrtho(GLfloat leftPlane, GLfloat rightPlane, GLfloat bottomPlane, GLfloat topPlane, GLfloat nearPlane, GLfloat farPlane)
{
	 float deltaX = rightPlane - leftPlane;
	 float deltaY = topPlane - bottomPlane;
	 float deltaZ = farPlane - nearPlane;

	 this->projectView = MvpMatrix::CreateMatrix(
		 Vector4(2.0 / deltaX,	0,				0,				0),
		 Vector4(0,				2.0 / deltaY,	0,				0),
		 Vector4(0,				0,				-2.0 / deltaZ,	0),
		 Vector4(-(leftPlane + rightPlane) / deltaX, -(bottomPlane + topPlane) / deltaY, -(nearPlane + farPlane) / deltaZ, 1.0)
		 );
}


void Camera::RotateHorizontal(float a)
{
	Vector3 direction = (this->position - this->target).Normalize();
	Vector3 cameraRight =  this->up.Cross(direction).Normalize();
	Vector3 cameraUp = direction.Cross(cameraRight);

	Matrix worldCamera = MvpMatrix::CreateMatrix
	(
		Vector4(cameraRight.x,	cameraRight.y,	cameraRight.z,	0.0), 
		Vector4(cameraUp.x,		cameraUp.y,		cameraUp.z,		0.0),
		Vector4(direction.x,	direction.y,	direction.z,	0.0),
		Vector4(position.x,		position.y,		position.z,		1.0)
	);
	Vector4
		localTarget = Vector4(0, 0, -(position - target).Length(), 1),
		localNewTarget = localTarget * MvpMatrix().Rotate(a, 0, 0).GetSRTMatrix(),
		newTarget = localNewTarget * worldCamera;

	//Treat 90 degree on rotate
	Vector3 new_direction = (this->position - Vector3(newTarget.x, newTarget.y, newTarget.z)).Normalize();
	Vector3 new_cameraRight =  this->up.Cross(new_direction).Normalize();
	Vector3 new_cameraUp = new_direction.Cross(new_cameraRight);
	if(new_cameraUp.y < 0.2)
	{
		return;
	}
	this->target = Vector3(newTarget.x, newTarget.y, newTarget.z);
}

void Camera::RotateVertical(float a)
{
	Vector4
		localTarget = Vector4(target-position, 1),
		localNewTarget = localTarget * MvpMatrix().Rotate(0, a, 0).GetSRTMatrix(),
		newTarget = localNewTarget + Vector4(position, 1);
	this->target = Vector3(newTarget.x, newTarget.y, newTarget.z);

	
}


void Camera::MoveInY(float dt)
{
	//Vector3 normalZ = (this->position - this->target).Normalize();
	//Vector3 normalX =  this->up.Cross(normalZ).Normalize();
	//Vector3 normalY =  normalZ.Cross(normalX).Normalize();
	//Vector3 delta_move =  normalY * velMovingY * dt * moveSpeed;
	Vector3 delta_move =  Vector3(0,1,0)* dt * moveSpeed;
	this->position += delta_move;
	this->target += delta_move;

	//Console::log("Camera: [%f, %f].\n", position.x, position.y);
}


void Camera::MoveInX(float dt)
{
	//Vector3 normalZ = (this->position - this->target).Normalize();
	//Vector3 normalX =  this->up.Cross(normalZ).Normalize();
	//Vector3 delta_move =  normalX * velMovingX * dt * moveSpeed;
	Vector3 delta_move =  Vector3(1,0,0)* dt * moveSpeed;
	this->position += delta_move;
	this->target += delta_move;

}


void Camera::Update(float dt)
{
	this->SetOrtho(0, Globals::screenWidth, 0, Globals::screenHeight, -1.0, 1.0);
}


Vector2 Camera::GetPosition()
{
	return Vector2( this->position.x, this->position.y);
}
void Camera::SetPosition(Vector2 v)
{
	this->position.x = v.x;
	this->position.y = v.y;
}