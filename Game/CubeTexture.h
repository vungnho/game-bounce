#pragma once
#include <Utilities/utilities.h>
#include "Texture.h"
class CubeTexture: Texture
{

public:
	CubeTexture(void);
	~CubeTexture(void);

	//Method
	void LoadCube(char** file_LTRBFB);
	void SetFilter();
	void Bind();
	void UnBind();
};
