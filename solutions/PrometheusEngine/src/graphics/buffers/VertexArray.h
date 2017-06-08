#pragma once

#include "Buffer.h"

#include <vector>

namespace graphics { namespace buffers {

	class VertexArray
	{
	private:
		GLuint m_vao;
		std::vector<Buffer*> m_buffers;

	public:
		VertexArray();
		~VertexArray();

		void addBuffer(Buffer *buffer, GLuint index);
		void addComplexBuffer(Buffer *buffer, GLuint startIndex);
		void bind();
		void unbind();


	};

} }
