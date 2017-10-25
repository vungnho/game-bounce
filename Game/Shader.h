#pragma once
#include <Utilities/esUtil.h>
#include <Utilities/MyMath.h>
class Shader 
{
public:
	Shader();
	Shader(const char* vs_file, const char* fs_file);
	GLuint program, vertexShader, fragmentShader;
	

	int Id;
	char* fileVS;
	char* fileFS;

	GLuint positionAttribute;
	GLuint textureAttribute;
	GLuint uftColor;
	GLuint uftLoc[99];
	GLuint uniformMatrixLocation;
	GLuint ufWorld;
	GLuint ufTileLoc;

	GLuint ufEyePos;

	int depthTest;
	int culling;

	int Init(const char * fileVertexShader, const char * fileFragmentShader);
	GLuint GetUniform(const char* name);
	void SetUniform(const char* name, float value);
	void SetUniform(const char* name, Vector2 value);
	void SetUniform(const char* name, Vector3 value);
	void SetUniform(const char* name, Vector4 value);
	void SetUniform(const char* name, Matrix value);
	~Shader();
};