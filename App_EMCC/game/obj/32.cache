
#include "StdAfx.h"
#include "CubeTexture.h"
#include <Utilities/TGA.h>

CubeTexture::CubeTexture()
{
	//1. Genarate texture
	glGenTextures(1, &(this ->textureId));
	//2. Buffer texture
	this->Bind();
	//Set filter
	this->SetFilter();

}

void CubeTexture::LoadCube(char** file_LTRBFB)
{
	for(int i=0; i<6; i++)
	{
		//Load Image Texture
		int iWidth, iHeight, iBpp;
		char * imageData = LoadTGA(file_LTRBFB[i],  &iWidth, &iHeight, &iBpp);

		glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData );
		delete[] imageData;
	}



}

CubeTexture::~CubeTexture(void)
{
}


void CubeTexture::SetFilter()
{
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
void CubeTexture::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureId);
	//esLogMessage("3D Cube Binded.\n");
}

void CubeTexture::UnBind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}