#pragma once

#include <GL\glew.h>

namespace graphics {

	class Texture
	{
	public:
		Texture();
		~Texture();

		void loadTexture(const char* filePath);

		void bind();

		GLuint getID();

	private:
		GLuint m_textureID;
	};

}

