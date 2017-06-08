#include "Buffer.h"

namespace graphics { namespace buffers {

	Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentsCount)
		: m_componentCount(componentsCount)
	{
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::Buffer(std::vector<math::Vector3r> data, int count, GLuint componentsCount)
		: m_componentCount(componentsCount)
	{
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::Buffer(std::vector<math::Vector2r> data, int count, GLuint componentsCount)
		: m_componentCount(componentsCount)
	{
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::~Buffer()
	{
		//TODO: dispose of stuff here
	}

	void Buffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	}

	void Buffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GLuint Buffer::getSize(GLuint componentIndex) const
	{
		return sizeof(0);
	}

	GLuint Buffer::getOffset(GLuint componentIndex) const
	{
		return GLuint();
	}

} }