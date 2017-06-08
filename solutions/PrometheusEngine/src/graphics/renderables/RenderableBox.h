#pragma once

#include "GL\glew.h"

#include "core\math\Vector3.hpp"
#include "..\buffers\VertexArray.h"
#include "..\buffers\IndexedBuffer.h"

namespace graphics { namespace renderables {

	class RenderableBox
	{
	private:
		math::Vector3r m_position;
		math::Vector3r m_size;
		math::Vector3r m_color;

		buffers::VertexArray* m_vao;
		buffers::IndexedBuffer* m_ibo;

	public:
		RenderableBox(const math::Vector3r& position,
			const math::Vector3r& size,
			const math::Vector3r& color) 
			: m_position(position), m_size(size), m_color(color)
		{
			GLfloat verticesData[12] = {
				0 ,0, 0,
				size.x, 0, 0,
				0, size.y, 0,
				0, 0, size.z
			};
			GLfloat colorData[16] = {
				color.x, color.y, color.z, 1,
				color.x, color.y, color.z, 1,
				color.x, color.y, color.z, 1,
				color.x, color.y, color.z, 1,
			};
			
			m_vao = new buffers::VertexArray();
			m_vao->addBuffer(new buffers::Buffer(verticesData, 4* 3, 3), 0);
			m_vao->addBuffer(new buffers::Buffer(colorData, 4 * 4, 3), 1);

			GLushort indices[16] = {
				color.x, color.y, color.z, 1,
				color.x, color.y, color.z, 1,
				color.x, color.y, color.z, 1,
				color.x, color.y, color.z, 1,
			};

			m_ibo = new buffers::IndexedBuffer(indices, 5);
		}
		
		~RenderableBox() {
			delete m_vao;
			delete m_ibo;
		}
		
		void setPosition(math::Vector3r position) { m_position = position; }


		const math::Vector3r getPosition() { return m_position; }
		const math::Vector3r getSize() { return m_size; }
		const math::Vector3r getColor() { return m_color; }
		const buffers::VertexArray* getVAO() { return m_vao; }
		const buffers::IndexedBuffer* getIBO() { return m_ibo; }
	};

} }
