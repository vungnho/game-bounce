#include "StdAfx.h"
#include "Texture.h"
#include <Utilities/TGA.h>

Texture::Texture()
{
	this->wrapMode = GL_REPEAT;
	this->minFilterMode = GL_LINEAR_MIPMAP_LINEAR;
	this->magFilterMode = GL_LINEAR;

	//1. Genarate texture
	glGenTextures(1, &textureId);
	//glGenTextures(1, &(this ->textureId));

	//2. Buffer texture
	this->UpdateFilter();

}

Texture::Texture(const char *fileName)
{
	this->wrapMode = GL_REPEAT;
	this->minFilterMode = GL_LINEAR_MIPMAP_LINEAR;
	this->magFilterMode = GL_LINEAR;

	//1. Genarate texture
	glGenTextures(1, &textureId);
	//2. Buffer texture
	this->Bind();
	this->Load(fileName);
	this->UpdateFilter();
	this->UnBind();
}

void Texture::Load(const char* arg_fileName)
{
	//Load Image Texture
	int iWidth, iHeight, iBpp;
	char * imageData = LoadTGA(  arg_fileName,  &iWidth, &iHeight, &iBpp);
	if(imageData == NULL)
	{
		Console::log("Loading %s failed.\n", arg_fileName);
		return;
	}

	int ColorDepth = iBpp < 32 ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0,ColorDepth , iWidth, iHeight, 0, ColorDepth, GL_UNSIGNED_BYTE, imageData );
	delete[] imageData;


}

Texture::~Texture(void)
{
}


void Texture::UpdateFilter()
{
	/* 2D */
	//set the filters for minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->magFilterMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->minFilterMode);
	// generate the mipmap chain
	if(this->minFilterMode == GL_LINEAR_MIPMAP_LINEAR)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapMode);




}
void Texture::Bind()
{
	// bind the texture to the currently active texture id
	glBindTexture(GL_TEXTURE_2D, this->textureId);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureId);
}


void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::LoadCube(char** s)
{
}