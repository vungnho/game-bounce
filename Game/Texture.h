#pragma once
#include <SDL2/SDL_opengles2.h>
#include <string.h>

class Texture
{
public:
	//Constructor
	Texture();
	Texture(const char* fileName);
	~Texture(void);

	int Id;

	//Feild
	GLuint textureId;
	int wrapMode;
	int minFilterMode;
	int magFilterMode;
	

	//Method
	virtual void Load(const char* TGA_FileName);
	virtual void UpdateFilter();
	virtual void Bind();
	virtual void UnBind();
	virtual void LoadCube(char** files);

	static GLint GetWrapMode(const char* mode)
	{
		if(strcmp(mode, "repeat") == 0)
			return GL_REPEAT;
		if(strcmp(mode, "clam") == 0)
			return GL_CLAMP_TO_EDGE;
		return GL_REPEAT;

	}

	static GLint GetFilterMode(const char* mode)
	{
		if(strcmp(mode, "linear_linear") == 0)
			return GL_LINEAR;
		return GL_LINEAR;
	}

};
