#include "ProRenderUtil.h"

#include "GLFW\glfw3.h"

void ProRenderUtil::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ProRenderUtil::initGraphics()
{
	glClearColor(0.2f, 0.0f, 0.7f, 0.0f);

	//glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}
