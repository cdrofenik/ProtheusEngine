#pragma once

#include "core\math\ProPrecision.hpp"
#include "core\math\ProVector3.hpp"
#include "core\math\ProMatrix4.hpp"

#include "GL\glew.h"

#include <vector>
#include <unordered_map>


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

	void SetUniform1F(const GLchar* uniformName, const ProReal& value);
	void SetUniform3F(const GLchar* uniformName, const ProVector3r& value);
	void SetUniformMatrix4F(const GLchar* uniformName, ProMatrix4& value);

	GLuint GetUniformLocation(const GLchar *value);
	GLuint GetProgram();

private:
	GLuint m_program;
	std::vector<GLuint> m_shaderList;
	std::unordered_map<GLchar*, GLuint> m_uniformList;

	void PopulateUniforms();
	void AddShader(const char * shaderFilePath, GLuint shaderType);
	void ShaderSanityCheck(const GLuint& _id, const bool& _isProgram);
};

