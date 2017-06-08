#pragma once

#include "GL\glew.h"

#include <vector>

namespace graphics { namespace buffers {

	class IndexedBuffer
	{
	private:
		GLuint m_ebo;
		GLuint m_count;

	public:
		IndexedBuffer(GLushort* data, const GLuint& size);
		IndexedBuffer(std::vector<unsigned int> data, const int& size);
		~IndexedBuffer();

		void bind() const;
		void unbind() const;
	};
} }
