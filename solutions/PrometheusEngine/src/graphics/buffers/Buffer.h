#pragma once

#include "GL\glew.h"

#include <vector>

#include "core\math\Vector2.hpp"
#include "core\math\Vector3.hpp"

namespace graphics { namespace buffers {

	class Buffer
	{
	private:
		GLuint m_bufferID;
		GLuint m_componentCount;

	public:
		Buffer(GLfloat* data, GLsizei count, GLuint componentsCount);
		Buffer(std::vector<math::Vector3r> data, int count, GLuint componentsCount);
		Buffer(std::vector<math::Vector2r> data, int count, GLuint componentsCount);
		~Buffer();

		void bind() const;
		void unbind() const;

		GLuint getSize(GLuint componentIndex) const;
		GLuint getOffset(GLuint componentIndex) const;

		inline GLuint getComponentCount() const { return m_componentCount; }
	};
} }

