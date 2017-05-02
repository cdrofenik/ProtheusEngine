#pragma once

#include <GL\glew.h>

class ProTexture
{
public:
	ProTexture();
	~ProTexture();

	void loadTexture(const char* filePath);

	void bind();

	GLuint getID();

private:
	GLuint m_textureID;
};

