#pragma once
//#include <vector>
#include "Texture.h"
#include "Model.h"
#include "Shader.h"
//#include "CubeTexture.h"
class ResourceManager
{

protected:
	ResourceManager(void);
	~ResourceManager(void);
	/*implicit methods exist for the copy constructor and operator= and we want to forbid calling them.*/
	ResourceManager(const ResourceManager &){};
	ResourceManager& operator =(const ResourceManager &){};
public:
	Texture** m_vTextures;
	Model** m_vModels;
	Shader** m_vShaders;

	int m_numTextures;
	int m_numModels;
	int m_numShaders;

public:
	void Init();
	void LoadResource();
	int IndexOfModel(int id);
	int IndexOfTexture(int id);
	int IndexOfShader(int id);

	void __toString();

	Model* GetModelById(int id);
	Texture* GetTextureById(int id);
	Shader* GetShaderById(int id);
	static void CreateInstance()
    {
        ms_pInstance = new ResourceManager();
    }

public:
	static ResourceManager * GetInstance() 
    {
        if (!ms_pInstance) CreateInstance();
		return ms_pInstance;
    }
	static void DestroyInstance() 
    {
	   if ( ms_pInstance )
	   {
		  delete ms_pInstance;
		  ms_pInstance = NULL;
	   }
    }

protected:
	static ResourceManager * ms_pInstance;

};
