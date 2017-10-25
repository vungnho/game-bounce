#pragma once
#include <Utilities/MyMath.h>

class MvpMatrix
{
public:
	MvpMatrix(void);
	MvpMatrix(Matrix m);
	~MvpMatrix(void);

	void SetRotate(float thx, float thy, float thz);
	void SetTranslate(float dx, float dy, float dz);
	void SetScale(float dx, float dy = 1, float dz = 1);
	Vector3 GetRotation();
	Vector3 GetTranslation();
	Vector3 GetScale();
	Matrix GetSRTMatrix();

	MvpMatrix &Rotate(float thx, float thy, float thz);
	MvpMatrix &Translate(float dx, float dy, float dz);
	MvpMatrix &Scale(float dx, float dy, float dz);
	MvpMatrix &Scale(float d);
	MvpMatrix &Reset();
	//Matrix toMatrix();
	static Matrix lookAt(Vector3 camera_pos, Vector3 target_pos, Vector3 up);
	static Matrix GetProjectMatrix();
	static Matrix CreateMatrix(Vector4 row1, Vector4 row2, Vector4 row3, Vector4 row4);


private:
	Matrix R;
	Matrix T;
	Matrix S;
	Matrix M;

};
