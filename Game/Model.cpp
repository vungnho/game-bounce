
#include "StdAfx.h"
#include "Model.h"
#include "JSON.h"


Model::Model(void)
{
}

Model::Model(const char* fileName)
{
	this->Load(fileName);
}

Model::Model(int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH)
{

	this-> numVertex = 4;
	this-> numIndice = 6;
	this->vertexes = new Vertex[4];
	//Vector2 delta = Vector2(origin.x-(float)spriteW/2, origin.y-(float)spriteH/2);
	this->vertexes[0].Position = Vector2(-(float)spriteW/2, -(float)spriteH/2);
	this->vertexes[1].Position = Vector2((float)spriteW/2, -(float)spriteH/2);
	this->vertexes[2].Position = Vector2(-(float)spriteW/2, (float)spriteH/2);
	this->vertexes[3].Position = Vector2((float)spriteW/2, (float)spriteH/2);
	this->vertexes[0].UV = Vector2((float)spriteX/textureW, (float)spriteY/textureH);
	this->vertexes[1].UV = Vector2((float)(spriteX+spriteW)/textureW, (float)spriteY/textureH);
	this->vertexes[2].UV = Vector2((float)spriteX/textureW, (float)(spriteY+spriteH)/textureH);
	this->vertexes[3].UV = Vector2((float)(spriteX+spriteW)/textureW, (float)(spriteY+spriteH)/textureH);
	
	this->indices = new int[6];

	this->indices[0] = 0;
	this->indices[1] = 1;
	this->indices[2] = 2;
	this->indices[3] = 3;
	this->indices[4] = 1;
	this->indices[5] = 2;
}







Model::~Model(void)
{
	delete[] vertexes;
	delete[] indices;
}

void Model::Load(const char *fileName)
{
	

	int num_vertex = 0;
	int num_indice = 0;
	//char lineHeader[512];
	FILE * file;
	file = fopen (fileName, "r");
	if(file == NULL)
	{
		Console::log("Can not load file %s.\n", fileName);
		return;
	}


	std::string content = file_get_contents(fileName);
	//Console::log("Parse file \"%s\"...\n", fileName);
	Json::Value root = JSONparse(content);

	Json::Value o_vertices = root["vertices"];
	Json::Value o_indices = root["indices"];

	num_vertex = o_vertices["size"].asInt();

	this->vertexes = new Vertex[num_vertex];

	Json::Value data = o_vertices["data"];

	int l_a = 0;
	int l_b = 1;
	for(int i = 0; i < num_vertex; i++)
	{
		vertexes[i].Position = Vector2(data[i]["pos"][l_a].asDouble(), data[i]["pos"][l_b].asDouble());
		vertexes[i].UV       = Vector2(data[i]["uv"][l_a].asDouble(), data[i]["uv"][l_b].asDouble());
		//printf("pos: %d\n", pos);
	}

	num_indice = o_indices["size"].asInt();
	indices = new int[num_indice];
	data = o_indices["data"];
	for(int i = 0; i < num_indice; i+=3)
	{
		indices[i] = (int) data[(i+1)/3][l_a].asDouble();
		indices[i + 1] = (int) data[(i+1)/3][l_a+1].asDouble();
		indices[i + 2] = (int) data[(i+1)/3][l_a+2].asDouble();

	}

	this->numVertex = num_vertex;
	this->numIndice = num_indice;
}


int Model::GetVertexSize()
{
	return this->numVertex * sizeof(Vertex);
}

int Model::GetIndiceSize()
{
	return this->numIndice * sizeof(int);
}

void* Model::GetVertexPointer()
{
	return this->vertexes;
}
void* Model::GetIndicePointer()
{
	return this->indices;
}