#include "StdAfx.h"
#include "MvpMatrix.h"

MvpMatrix::MvpMatrix(void)
{
	M = Matrix();
	M.SetIdentity();

	R = Matrix();
	R.SetZero();
	T = Matrix();
	T.SetZero();
	S = Matrix();
	S.SetIdentity();

	this->SetRotate(0, 0, 0);
	this->SetScale(1, 1, 1);
	this->SetTranslate(0, 0, 0);


}

MvpMatrix::MvpMatrix(Matrix m)
{
	this->M = m;
}

MvpMatrix::~MvpMatrix(void)
{
}


void MvpMatrix::SetRotate(float thx, float thy, float thz)
{
	//Rotate Matrix
	Matrix Rx = Matrix(); Rx.SetRotationX(thx);
	Matrix Ry = Matrix(); Ry.SetRotationY(thy);
	Matrix Rz = Matrix(); Rz.SetRotationZ(thz);

	this->R = Rz*Rx*Ry;
}

void MvpMatrix::SetTranslate(float dx, float dy, float dz)
{
	this->T.SetTranslation(dx, dy, dz);
}

void MvpMatrix::SetScale(float dx, float dy, float dz)
{
	this->S.SetScale(dx, dy, dz);
}

Matrix MvpMatrix::GetSRTMatrix()
{
	return this->S * this->R * this->T;
}

MvpMatrix &MvpMatrix::Rotate(float thx, float thy, float thz)
{
	MvpMatrix r1 = MvpMatrix();
	r1.SetRotate(thx, thy, thz);
	this->R = this->R * r1.R;

	this->M = this->M * this->R;
	return *this;
}

Vector3 MvpMatrix::GetRotation()
{
	Vector4 v4 =  Vector4(0, 0, 0, 1) * this->R;
	return Vector3(v4.x, v4.y, v4.z);
}

MvpMatrix &MvpMatrix::Translate(float dx, float dy, float dz)
{

	MvpMatrix t1 = MvpMatrix();
	t1.SetTranslate(dx, dy, dz);
	this->T = this->T * t1.T;

	this->M = this->M * this->T;
	return *this;
}

MvpMatrix &MvpMatrix::Scale(float dx, float dy, float dz)
{

	MvpMatrix s1 = MvpMatrix();
	s1.SetScale(dx, dy, dz);
	this->S = this->S * s1.S;

	this->M = this->M *  this->S;
	return *this;
}

MvpMatrix &MvpMatrix::Scale(float dd)
{
	return this->Scale(dd, dd, dd);
}



MvpMatrix &MvpMatrix::Reset()
{
	M.SetIdentity();
	SetRotate(0, 0, 0);
	SetTranslate(0, 0, 0);
	SetScale(0, 0, 0);
	return *this;
}

Matrix MvpMatrix::GetProjectMatrix()
{
	return Matrix().SetPerspective(1.0, 2.0, 0.1, 500);
}

Matrix MvpMatrix::CreateMatrix(Vector4 row1, Vector4 row2, Vector4 row3, Vector4 row4)
{
	Matrix mat = Matrix();
	mat.m[0][0] = row1[0];
	mat.m[0][1] = row1[1];
	mat.m[0][2] = row1[2];
	mat.m[0][3] = row1[3];
	mat.m[1][0] = row2[0];
	mat.m[1][1] = row2[1];
	mat.m[1][2] = row2[2];
	mat.m[1][3] = row2[3];
	mat.m[2][0] = row3[0];
	mat.m[2][1] = row3[1];
	mat.m[2][2] = row3[2];
	mat.m[2][3] = row3[3];
	mat.m[3][0] = row4[0];
	mat.m[3][1] = row4[1];
	mat.m[3][2] = row4[2];
	mat.m[3][3] = row4[3];
	return mat;
}

/**
* camera_pos: vị trí của camera
* target_pos: vị trí của mục tiêu mà camera muốn ngắm đến
* up: góc quay quanh trục của camera
*/
/*
Matrix MvpMatrix::lookAt(Vector3 camera_pos, Vector3 target_pos, Vector3 up)
{

	Vector3 cameraDirection = (camera_pos - target_pos).Normalize();
	Vector3 cameraRight =  up.Cross(cameraDirection).Normalize();
	Vector3 cameraUp = cameraDirection.Cross(cameraRight);

	Matrix m = MvpMatrix::CreateMatrix
	(
		Vector4(cameraRight.x, cameraUp.x, cameraDirection.x, 0), 
		Vector4(cameraRight.y, cameraUp.y, cameraDirection.y, 0),
		Vector4(cameraRight.z, cameraUp.z, cameraDirection.z, 0),
		Vector4(0, 0, 0, 1)
	);

	Matrix t = MvpMatrix::CreateMatrix
	(
		Vector4(1, 0, 0,  0), 
		Vector4(0, 1, 0,  0),
		Vector4(0, 0, 1,  0),
		Vector4(-camera_pos.x, -camera_pos.y, -camera_pos.z, 1)
	);
	return m*t;

}
*/