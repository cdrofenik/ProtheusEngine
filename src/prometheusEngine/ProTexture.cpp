#include "ProTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


ProTexture::ProTexture()
{
}

ProTexture::~ProTexture()
{
}

void ProTexture::loadTexture(const char * filePath)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load, create texture and generate mipmaps
	int width, height, bpp;
	unsigned char* rgb = stbi_load(filePath, &width, &height, &bpp, 3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(rgb);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_textureID = texture;
}

void ProTexture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

GLuint ProTexture::getID()
{
	return m_textureID;
}
