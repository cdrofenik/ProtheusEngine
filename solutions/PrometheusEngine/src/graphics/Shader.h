#pragma once

#include "core\math\Precision.hpp"
#include "core\math\Vector3.hpp"
#include "core\math\Matrix4.hpp"

#include "GL\glew.h"

#include <vector>
#include <unordered_map>

namespace graphics {

	class Shader
	{
	private:
		GLuint m_program;
		std::vector<GLuint> m_shaderList;
		std::unordered_map<GLchar*, GLuint> m_uniformList;

	public:
		Shader();
		~Shader();

		void bind();
		void cleanUp();
		void compile();

		void addVertexShader(const char * shaderFilePath);
		void addGeometryShader(const char * shaderFilePath);
		void addFragmentShader(const char * shaderFilePath);

		void setUniform1F(const GLchar* uniformName, const math::Real& value);
		void setUniform1I(const GLchar* uniformName, const int& value);
		void setUniform3F(const GLchar* uniformName, const math::Vector3r& value);
		void setUniformMatrix4F(const GLchar* uniformName, math::Matrix4& value);

		GLuint getUniformLocation(const GLchar *value);
		GLuint getProgram();

	private:
		void populateUniforms();
		void addShader(const char * shaderFilePath, GLuint shaderType);
		void shaderSanityCheck(const GLuint& _id, const bool& _isProgram);
	};
}


