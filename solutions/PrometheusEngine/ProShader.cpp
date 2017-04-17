#include "ProShader.h"

#include "ProResourceLoader.h"

ProShader::ProShader()
{
}


ProShader::~ProShader()
{
	CleanUp();
}

void ProShader::Bind()
{
	glUseProgram(m_program);
}

void ProShader::CleanUp()
{
	glUseProgram(0);
	for (size_t i = 0; i < m_shaderList.size(); i++)
	{
		glDetachShader(this->m_program, m_shaderList[i]);
		glDeleteShader(m_shaderList[i]);
	}

	glDeleteProgram(this->m_program);
}

void ProShader::Compile()
{
	printf("[ProShader] Creating program.\n");
	this->m_program = glCreateProgram();

	for (size_t i = 0; i < m_shaderList.size(); i++)
		glAttachShader(this->m_program, m_shaderList[i]);

	glLinkProgram(this->m_program);
	glValidateProgram(this->m_program);
	ShaderSanityCheck(this->m_program, true);

	PopulateUniforms();
	printf("[ProShader] Program compiled and prepared for usage.\n");
}

void ProShader::AddVertexShader(const char * shaderFilePath)
{
	AddShader(shaderFilePath, GL_VERTEX_SHADER);
}

void ProShader::AddGeometryShader(const char * shaderFilePath)
{
	AddShader(shaderFilePath, GL_GEOMETRY_SHADER);
}

void ProShader::AddFragmentShader(const char * shaderFilePath)
{
	AddShader(shaderFilePath, GL_FRAGMENT_SHADER);
}

void ProShader::PopulateUniforms()
{
	GLuint uniformID = glGetUniformLocation(this->m_program, (GLchar*)"model");
	m_uniformList.insert_or_assign((GLchar*)"model", uniformID);

	//TODO: Try to implement this properly in the future
}

void ProShader::AddShader(const char * shaderFilePath, GLuint shaderType)
{
	GLuint shaderId = glCreateShader(shaderType);

	std::string shaderCode = ProResourceLoader::GetStringFromFile(shaderFilePath);

	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, NULL);
	glCompileShader(shaderId);

	ShaderSanityCheck(shaderId, false);

	m_shaderList.push_back(shaderId);

}

void ProShader::ShaderSanityCheck(const GLuint& id, const bool& isProgram)
{
	GLint success = GL_FALSE;
	GLchar infoLog[512];

	if (isProgram) {
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			printf("[ProShader] %s\n", infoLog);
		}
	}
	else {
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			printf("[ProShader] %s\n", infoLog);
		}
	}
}

GLuint ProShader::GetProgram() { return m_program; }

GLuint ProShader::GetUniformLocation(const GLchar *value_)
{
	return glGetUniformLocation(this->m_program, value_);
}

void ProShader::SetUniform1F(const GLchar* uniformName, const Real& value)
{
	GLuint uniformID = GetUniformLocation(uniformName);
	glUniform1f(uniformID, value);
}

void ProShader::SetUniform3F(const GLchar* uniformName, const Vector3r& value)
{
	GLuint uniformID = GetUniformLocation(uniformName);
	glUniform3fv(uniformID, 1, &(value.x));
}

void ProShader::SetUniformMatrix4F(const GLchar* uniformName, Matrix4 &value)
{
	GLuint uniformID = GetUniformLocation(uniformName);
	glUniformMatrix4fv(uniformID, 1, GL_FALSE, value.m);
}