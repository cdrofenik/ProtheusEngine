#pragma once

#include "GL\glew.h"
#include "GLFW\glfw3.h"

class ProDisplayManager
{
public:
	ProDisplayManager(const int& width, const int& height, const char* title);
	~ProDisplayManager();

	void Enable(GLenum flag);

	void Render();
	void Close();

	int GetWidth();
	int GetHeight();
	bool isClosed();
	GLFWwindow* GetWindow();

private:
	GLFWwindow* m_window;
	int m_width;
	int m_height;
	bool m_isClosed;

	void CreateWindow(const char* windowTitle);
};
