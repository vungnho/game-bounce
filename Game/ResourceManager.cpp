#include "StdAfx.h"

#include "ResourceManager.h"
#include "Memory.h"
#include "JSON.h"
#include "String.h"
#include "Globals.h"

ResourceManager * ResourceManager::ms_pInstance = NULL;

ResourceManager::ResourceManager(void)
{
}

ResourceManager::~ResourceManager()
{
	Memory::Delete(this->m_vModels, this->m_numModels);
	Memory::Delete(this->m_vTextures, this->m_numTextures);
	Memory::Delete(this->m_vShaders, this->m_numShaders);
}

void ResourceManager::Init()
{
	LoadResource();
}

void ResourceManager::LoadResource()
{
	const char* file_name = String::concat(BOUNCE_DATA_LOCATION, "Data/RM.json");
	FILE* file = fopen(file_name, "r");
	if(file == NULL)
	{
		Console::log("Can not open to read file %s.\n", file_name);
		return;
	}
	else
	{
		Console::log("Load file %s successfully.\n", file_name);
	}
	fclose(file);
	
	std::string content = file_get_contents(file_name);
	Json::Value document = JSONparse(content);




	/* Load Models */

	int num_model = m_numModels = document["models"]["data"].size();

	Json::Value data  = document["models"]["data"];


	this->m_vModels = new Model*[m_numModels];
	for(int i = 0; i < m_numModels; i++)
	{
		if( String::IsEquals(data[i]["type"].asCString(), "sprite"))
		{
			int j = 0;

			this->m_vModels[i] = new Model(
				data[i]["data"][j+0].asInt(),
				data[i]["data"][j+1].asInt(),
				data[i]["data"][j+2].asInt(),
				data[i]["data"][j+3].asInt(),
				data[i]["data"][j+4].asInt(),
				data[i]["data"][j+5].asInt());

		}
		else
		{
			const char* s = String::concat( BOUNCE_DATA_LOCATION, data[i]["file"].asCString());
			this->m_vModels[i] = new Model(s);
			delete[] s;
		}

		this->m_vModels[i] ->id = data[i]["id"].asInt();
	}

	/* Load Textures */

	m_numTextures = document["textures"]["data"].size();
	data  = document["textures"]["data"];
	
	this->m_vTextures = new Texture*[m_numTextures];
	for(int i = 0; i < m_numTextures; i++)
	{
		const char* s = String::concat( BOUNCE_DATA_LOCATION,  data[i]["file"].asCString());
		//Initilaze
		this->m_vTextures[i] = new Texture(s);
		delete[] s;

		//Set Properties
		this->m_vTextures[i]->Id = data[i]["id"].asInt();
		this->m_vTextures[i]->wrapMode = Texture::GetWrapMode(data[i]["wrap"].asCString());
		this->m_vTextures[i]->minFilterMode = Texture::GetFilterMode(data[i]["min"].asCString());
		this->m_vTextures[i]->magFilterMode = Texture::GetFilterMode(data[i]["mag"].asCString());

	}

	/* Load Shaders */

	m_numShaders = document["shaders"]["data"].size();
	data  = document["shaders"]["data"];

	this->m_vShaders = new Shader*[m_numShaders];
	for(int i = 0; i < m_numShaders; i++)
	{

		const char* fs = String::concat(BOUNCE_DATA_LOCATION, data[i]["fs"].asCString());
		const char* vs = String::concat(BOUNCE_DATA_LOCATION, data[i]["vs"].asCString());
		m_vShaders[i] = new Shader(vs, fs);
		delete[] fs;
		delete[] vs;
		m_vShaders[i]->Id = data[i]["id"].asInt();
		m_vShaders[i]->depthTest = data[i]["depth_test"].asInt();
		m_vShaders[i]->culling = data[i]["culling"].asInt();
		
	}
	

	delete[] file_name;
	return;

}


Model* ResourceManager::GetModelById(int id)
{
	for(int i = 0; i < m_numModels; i++)
	{
		if(this->m_vModels[i]->id == id)
			return this->m_vModels[i];
	}
	return 0;
}



Texture* ResourceManager::GetTextureById(int id)
{
	for(int i = 0; i < m_numTextures; i++)
	{
		if(this->m_vTextures[i]->Id == id)
			return this->m_vTextures[i];
	}
	return 0;
}



Shader* ResourceManager::GetShaderById(int id)
{
	for(int i = 0; i < this->m_numShaders; i++)
	{
		if(this->m_vShaders[i]->Id == id)
			return this->m_vShaders[i];
	}
	return 0;
}