#include "IndexedBuffer.h"

namespace graphics { namespace buffers {
	
	IndexedBuffer::IndexedBuffer(GLushort* data, const GLuint& size)
		: m_count(size)
	{
		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLushort), &data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexedBuffer::IndexedBuffer(std::vector<unsigned int> data, const int & size)
		: m_count(size)
	{
		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLushort), &data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}


	IndexedBuffer::~IndexedBuffer()
	{
		//TODO: dispose of stuff here
	}

	void IndexedBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	}

	void IndexedBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

} }
