#include "RenderableBox.h"

namespace graphics { namespace renderables {
	
	RenderableBox::RenderableBox(const math::Vector3r& position,
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
				m_vao->addBuffer(new buffers::Buffer(verticesData, 4 * 3, 3), 0);
				m_vao->addBuffer(new buffers::Buffer(colorData, 4 * 4, 3), 1);

				GLushort indices[16] = {
					color.x, color.y, color.z, 1,
					color.x, color.y, color.z, 1,
					color.x, color.y, color.z, 1,
					color.x, color.y, color.z, 1,
				};

				m_ibo = new buffers::IndexedBuffer(indices, 5);
			}

	RenderableBox::~RenderableBox() {
				delete m_vao;
			delete m_ibo;
		}

	void RenderableBox::setPosition(math::Vector3r position) { m_position = position; }


	const math::Vector3r RenderableBox::getPosition() { return m_position; }
	const math::Vector3r RenderableBox::getSize() { return m_size; }
	const math::Vector3r RenderableBox::getColor() { return m_color; }
	const buffers::VertexArray* RenderableBox::getVAO() { return m_vao; }
	const buffers::IndexedBuffer* RenderableBox::getIBO() { return m_ibo; }

} }