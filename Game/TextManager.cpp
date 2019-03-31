#include "stdafx.h"
#include "TextManager.h"
#include "Globals.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include "String.h"

TextManager * TextManager::ms_pInstance = NULL;


#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


TextManager::TextManager()
{
}
TextManager::~TextManager()
{
	glDeleteBuffers(1, &(m_vboId));
}
void TextManager::Init()
{
	if(FT_Init_FreeType(&m_ft))
	{
		Console::log("Could not init freetype library\n");
		return;
	}
    //const char* s = String::concat(BOUNCE_DATA_LOCATION, "Fonts/Snacker.ttf");
    const char* s = String::concat(BOUNCE_DATA_LOCATION, "Fonts/angrybirds-regular.ttf");
	if(FT_New_Face(m_ft, s, 0, & m_face))
	//if(FT_New_Face(m_ft, "../Resources/Fonts/Snacker.ttf", 0, &m_face))
	{
		Console::log("Could not load font Snacker.ttf\n");
		return;
	}
	else
	{
		Console::log("Load font Snacker.ttf ok!\n");
	}

	delete[] s;

	FT_Select_Charmap(
          m_face,               /* target face object */
		  FT_ENCODING_UNICODE ); /* encoding           */

	FT_Set_Pixel_Sizes(m_face, 0, 48);
	m_glyphSlot = m_face->glyph;
	this->m_shader = ResourceManager::GetInstance()->m_vShaders[1];
	//Console::log("Line 27 - TextManager.cpp. Id shader: %d\n", m_shader-> Id);

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenBuffers(1, &m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
}
	
void TextManager::RenderString(const char *text, Vector4 color, float x, float y,
    unsigned int pixel_Size)
{
	FT_Set_Pixel_Sizes(m_face, 0, pixel_Size);
	// use glProgram, bind texture & pass color uniform here
	glUseProgram(this->m_shader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Enable Vertex if able
	if(this->m_shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(this->m_shader->positionAttribute);
		glVertexAttribPointer(this->m_shader->positionAttribute, 4, GL_FLOAT, GL_FALSE, 16, VERTEX_POS);
	}
	
	if(this->m_shader->uftLoc[0]!=-1){
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(this->m_shader->uftLoc[0],0);
	}


	//Set uniform color
	this->m_shader->SetUniform("u_color", color);

	//Console::log("Line 49 - TextManager.cpp. ");

	float sx = 1.0f / Globals::screenWidth;
	float sy = 1.0f / Globals::screenHeight;
	x = -1.0f + 2.0f * x/Globals::screenWidth;
	y = -1.0f + 2.0f * y/Globals::screenHeight;
	for(const char *p = text; *p; p++)
	{
		if(FT_Load_Char(m_face, *p, FT_LOAD_RENDER))
		{
			continue;
		}
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			m_glyphSlot->bitmap.width,
			m_glyphSlot->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			m_glyphSlot->bitmap.buffer
			);
		float x2 = x + m_glyphSlot->bitmap_left * sx;
		float y2 = -y - m_glyphSlot->bitmap_top * sy;
		float w = m_glyphSlot->bitmap.width * sx;
		float h = m_glyphSlot->bitmap.rows * sy;
		GLfloat box[4][4] = {
			{x2, -y2 , 0, 0},
			{x2 + w, -y2 , 1, 0},
			{x2, -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		x += (m_glyphSlot->advance.x >> 6) * sx;
		y += (m_glyphSlot->advance.y >> 6) * sy;
	}

	//Console::log("TextManager::RenderString(): x = %d, y = %d. \n");
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void TextManager::RenderNumber(const int number, Vector4 color, float x, float y,
    unsigned int pixel_Size)
{
	char *text = new char[25];
	sprintf ( text, "%d", number );
	FT_Set_Pixel_Sizes(m_face, 0, pixel_Size);
	// use glProgram, bind texture & pass color uniform here
	glUseProgram(this->m_shader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Enable Vertex if able
	if(this->m_shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(this->m_shader->positionAttribute);
		glVertexAttribPointer(this->m_shader->positionAttribute, 4, GL_FLOAT, GL_FALSE, 16, VERTEX_POS);
	}
	
	if(this->m_shader->uftLoc[0]!=-1){
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(this->m_shader->uftLoc[0],0);
	}


	//Set uniform color
	this->m_shader->SetUniform("u_color", color);

	//Console::log("Line 49 - TextManager.cpp. ");

	float sx = 1.0f / Globals::screenWidth;
	float sy = 1.0f / Globals::screenHeight;
	x = -1.0f + 2.0f * x/Globals::screenWidth;
	y = -1.0f + 2.0f * y/Globals::screenHeight;
	for(const char *p = text; *p; p++)
	{
		if(FT_Load_Char(m_face, *p, FT_LOAD_RENDER))
		{
			continue;
		}
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			m_glyphSlot->bitmap.width,
			m_glyphSlot->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			m_glyphSlot->bitmap.buffer
			);
		float x2 = x + m_glyphSlot->bitmap_left * sx;
		float y2 = -y - m_glyphSlot->bitmap_top * sy;
		float w = m_glyphSlot->bitmap.width * sx;
		float h = m_glyphSlot->bitmap.rows * sy;
		GLfloat box[4][4] = {
			{x2, -y2 , 0, 0},
			{x2 + w, -y2 , 1, 0},
			{x2, -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		x += (m_glyphSlot->advance.x >> 6) * sx;
		y += (m_glyphSlot->advance.y >> 6) * sy;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	delete[] text;
	text = NULL;
}


int TextManager::GetStringWidth(char *text, int size)
{
	FT_Set_Pixel_Sizes(m_face, 0, size);

	int last_x = 0, last_w = 0;
	for(const char *p = text; *p; p++)
	{
		if(FT_Load_Char(m_face, *p, FT_LOAD_RENDER))
		{
			continue;
		}
		//last_x += m_glyphSlot->bitmap_left;
		last_w = m_glyphSlot->bitmap.width;
		last_x += m_glyphSlot->advance.x >> 6;
	}
	return last_x;
}
unsigned int TextManager::GetStringHeight(char *text, unsigned int size)
{
	FT_Set_Pixel_Sizes(m_face, 0, size);

    unsigned int width = 0, height = 0;

	float sx = 1.0f / Globals::screenWidth;
	float sy = 1.0f / Globals::screenHeight;
	for(const char *p = text; *p; p++)
	{
		if(FT_Load_Char(m_face, *p, FT_LOAD_RENDER))
		{
			continue;
		}
		width += m_glyphSlot->bitmap.width;
		height = max(m_glyphSlot->bitmap.rows, height);
	}
	return height;
}