#pragma once

#include "GL\glew.h"

#include <vector>

class ProShader
{
public:
	ProShader();
	~ProShader();

	void Bind();
	void CleanUp();
	void Compile();
	void AddVertexShader(const char * shaderFilePath);
	void AddGeometryShader(const char * shaderFilePath);
	void AddFragmentShader(const char * shaderFilePath);

	GLuint getProgramID() { return m_program; }
private:
	GLuint m_program;
	std::vector<GLuint> m_shaderList;

	void AddShader(const char * shaderFilePath, GLuint shaderType);
	void ShaderSanityCheck(const GLuint& _id, const bool& _isProgram);
};

