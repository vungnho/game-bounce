
#include "Shader.h"
#include "Console.h"
#include <Utilities/esShader.h>

Shader::Shader()
{

}
Shader::Shader(const char *vs_file, const char *fs_file)
{
	this->Init(vs_file, fs_file);
}

GLuint Shader::GetUniform(const char* name)
{
	return glGetUniformLocation(program, name);
}

void Shader::SetUniform(const char* name, float value)
{
	GLuint id = this->GetUniform(name);
	if(id != -1)
	{
		glUniform1f(id, value);
	}
}
void Shader::SetUniform(const char* name, Vector2 value)
{
	GLuint id = this->GetUniform(name);
	if(id != -1)
	{
		glUniform2f(id, value.x, value.y);
	}
}
void Shader::SetUniform(const char* name, Vector3 value)
{
	GLuint id = this->GetUniform(name);
	if(id != -1)
	{
		glUniform3f(id, value.x, value.y, value.z);
	}
}


void Shader::SetUniform(const char* name, Vector4 value)
{
	GLuint id = this->GetUniform(name);
	if(id != -1)
	{
		glUniform4f(id, value.x, value.y, value.z, value.w);
	}
}

void Shader::SetUniform(const char *name, Matrix value)
{

	GLuint id = this->GetUniform(name);
	if(id != -1)
	{
		glUniformMatrix4fv(id, 1, GL_FALSE, &(value.m[0][0]));
	}

}

int Shader::Init(const char * fileVertexShader, const char * fileFragmentShader)
{


	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
	{
		Console::log("Fail on loading file %s.\n", fileVertexShader);
		return -1;
	}

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		Console::log("Fail on loading file %s.\n", fileFragmentShader);
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);
    //program = esLoadProgram(fileVertexShader, fileFragmentShader);

	//finding location of uniforms / attributes
	positionAttribute	= glGetAttribLocation(program, "a_pos");
	textureAttribute	= glGetAttribLocation(program, "a_uv");
	uftColor	= glGetUniformLocation(program, "u_color");
	uftLoc[0]		= glGetUniformLocation(program, "u_texture");
	uniformMatrixLocation	= glGetUniformLocation(program, "u_mvp");
	
	uftLoc[1] = glGetUniformLocation(program, "u_texture1");
	uftLoc[2] = glGetUniformLocation(program, "u_texture2");
	uftLoc[3] = glGetUniformLocation(program, "u_texture3");
	uftLoc[4] = glGetUniformLocation(program, "u_texture4");
	uftLoc[5] = glGetUniformLocation(program, "u_texture5");
	uftLoc[6] = glGetUniformLocation(program, "u_texture6");

	ufTileLoc	= glGetUniformLocation(program, "u_tile");
	ufEyePos	= glGetUniformLocation(program, "u_EyePos");
	ufWorld		= glGetUniformLocation(program, "u_world");

	return 0;
}

Shader::~Shader()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}