#pragma once

#include "core\math\Precision.hpp"
#include "core\math\Vector3.hpp"
#include "core\math\Matrix4.hpp"

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

	void SetUniform1F(const GLchar* uniformName, const math::Real& value);
	void SetUniform3F(const GLchar* uniformName, const math::Vector3r& value);
	void SetUniformMatrix4F(const GLchar* uniformName, math::Matrix4& value);

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

