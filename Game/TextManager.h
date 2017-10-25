#pragma once
#include "Shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H

class TextManager
{
public:
	
	Shader* m_shader;

	FT_Library m_ft;
	FT_Face m_face;
	FT_GlyphSlot m_glyphSlot;

	GLuint m_textureId, m_vboId;

	void Init();
	void RenderString(const char *text, Vector4 color, float x, float y, float pixel_Size=48);
	void RenderNumber(const int number, Vector4 color, float x, float y, float pixel_Size=48);
	int GetStringWidth(char* text, int size);
	int GetStringHeight(char* text, int size);
	

#pragma region "Singleton"
private:
	TextManager();
	~TextManager();

public:
	static void CreateInstance()
	{
		if ( ms_pInstance == NULL )
			ms_pInstance = new TextManager();
	}

	static TextManager * GetInstance() 
	{
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
	static TextManager * ms_pInstance;

#pragma endregion
};