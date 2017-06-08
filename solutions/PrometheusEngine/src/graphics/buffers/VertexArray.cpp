#include "VertexArray.h"

namespace graphics { namespace buffers {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_vao);
	}

	VertexArray::~VertexArray()
	{
		for (unsigned int i = 0; i < m_buffers.size(); i++) {
			auto buff = m_buffers[i];
			delete buff;
		}
	}

	void VertexArray::addBuffer(Buffer *buffer, GLuint index)
	{
		bind();
		buffer->bind();
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
		buffer->unbind();
		unbind();

		m_buffers.push_back(buffer);
	}

	void VertexArray::addComplexBuffer(Buffer * buffer, GLuint startIndex)
	{
		bind();
		buffer->bind();

		GLuint sIndex = startIndex;
		for (unsigned int i = 0; i < buffer->getComponentCount(); i++) {
			glEnableVertexAttribArray(sIndex);
			glVertexAttribPointer(sIndex,
				buffer->getComponentCount(),
				GL_FLOAT,
				GL_FALSE,
				0,
				0
			);
			sIndex++;
		}

		buffer->unbind();
		unbind();

		m_buffers.push_back(buffer);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(m_vao);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

} }
