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
			const math::Vector3r& color);
		
		~RenderableBox();
		
		void setPosition(math::Vector3r position);

		const math::Vector3r getPosition();
		const math::Vector3r getSize();
		const math::Vector3r getColor();
		const buffers::VertexArray* getVAO();
		const buffers::IndexedBuffer* getIBO();
	};

} }
