#pragma once

#include "Vertex.h"
class Model
{
public:
	Model(void);
	Model(const char* fileName);
	Model(int spriteX, int spriteY, int spriteH, int spriteW, int textureW, int textureH);

	~Model(void);

	int id;

	Vertex* vertexes;
	int* indices;

	int numVertex;
	int numIndice;


	void Load(const char* fileName);
	int GetVertexSize();
	int GetIndiceSize();
	void* GetVertexPointer();
	void* GetIndicePointer();


};

