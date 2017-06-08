#include "Shader.h"

#include "..\utils\ResourceLoader.h"

using namespace math;

namespace graphics {

	Shader::Shader()
	{
	}

	Shader::~Shader()
	{
		cleanUp();
	}

	void Shader::bind()
	{
		glUseProgram(m_program);
	}

	void Shader::cleanUp()
	{
		glUseProgram(0);
		for (size_t i = 0; i < m_shaderList.size(); i++)
		{
			glDetachShader(this->m_program, m_shaderList[i]);
			glDeleteShader(m_shaderList[i]);
		}

		glDeleteProgram(this->m_program);
	}

	void Shader::compile()
	{
		printf("[Shader] Creating program.\n");
		this->m_program = glCreateProgram();

		for (size_t i = 0; i < m_shaderList.size(); i++)
			glAttachShader(this->m_program, m_shaderList[i]);

		glLinkProgram(this->m_program);
		glValidateProgram(this->m_program);
		shaderSanityCheck(this->m_program, true);

		populateUniforms();
		printf("[Shader] Program compiled and prepared for usage.\n");
	}

	void Shader::addVertexShader(const char * shaderFilePath)
	{
		addShader(shaderFilePath, GL_VERTEX_SHADER);
	}

	void Shader::addGeometryShader(const char * shaderFilePath)
	{
		addShader(shaderFilePath, GL_GEOMETRY_SHADER);
	}

	void Shader::addFragmentShader(const char * shaderFilePath)
	{
		addShader(shaderFilePath, GL_FRAGMENT_SHADER);
	}

	void Shader::populateUniforms()
	{
		GLuint uniformID = glGetUniformLocation(this->m_program, (GLchar*)"model");
		m_uniformList.insert_or_assign((GLchar*)"model", uniformID);

		//TODO: Try to implement this properly in the future
	}

	void Shader::addShader(const char * shaderFilePath, GLuint shaderType)
	{
		GLuint shaderId = glCreateShader(shaderType);

		std::string shaderCode = ResourceLoader::GetStringFromFile(shaderFilePath);

		char const * sourcePointer = shaderCode.c_str();
		glShaderSource(shaderId, 1, &sourcePointer, NULL);
		glCompileShader(shaderId);

		shaderSanityCheck(shaderId, false);

		m_shaderList.push_back(shaderId);
	}

	void Shader::shaderSanityCheck(const GLuint& id, const bool& isProgram)
	{
		GLint success = GL_FALSE;
		GLchar infoLog[512];

		if (isProgram) {
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(id, 512, NULL, infoLog);
				printf("[Shader] %s\n", infoLog);
			}
		}
		else {
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(id, 512, NULL, infoLog);
				printf("[Shader] %s\n", infoLog);
			}
		}
	}

	GLuint Shader::getProgram() { return m_program; }

	GLuint Shader::getUniformLocation(const GLchar *value_)
	{
		return glGetUniformLocation(this->m_program, value_);
	}

	void Shader::setUniform1F(const GLchar* uniformName, const Real& value)
	{
		GLuint uniformID = getUniformLocation(uniformName);
		glUniform1f(uniformID, value);
	}

	void Shader::setUniform1I(const GLchar * uniformName, const int & value)
	{
		GLuint uniformID = getUniformLocation(uniformName);
		glUniform1i(uniformID, value);
	}

	void Shader::setUniform3F(const GLchar* uniformName, const Vector3r& value)
	{
		GLuint uniformID = getUniformLocation(uniformName);
		glUniform3fv(uniformID, 1, &value.data[0]);
	}

	void Shader::setUniformMatrix4F(const GLchar* uniformName, Matrix4 &value)
	{
		GLuint uniformID = getUniformLocation(uniformName);
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, value.m);
	}
}