#include "ProDisplayManager.h"

#include <iostream>

void ProDisplayManager::Render()
{
	glfwSwapBuffers(m_window);
}

void ProDisplayManager::Enable(GLenum flag_)
{
	glEnable(flag_);
}

void ProDisplayManager::Close()
{
	glfwTerminate();
}

int ProDisplayManager::GetWidth()
{
	return m_width;
}

int ProDisplayManager::GetHeight()
{
	return m_height;
}

GLFWwindow * ProDisplayManager::GetWindow()
{
	return m_window;
}

bool ProDisplayManager::isClosed()
{
	m_isClosed = glfwWindowShouldClose(m_window) != 0;
	return m_isClosed;
}

void ProDisplayManager::CreateWindow(const char* windowTitle)
{
	if (!glfwInit()) {
		std::cerr << "[ProDisplayManager] Failed to initialize GLFW!\n";
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Watchdog for bad coding habits

	m_window = glfwCreateWindow(m_width, m_height, windowTitle, nullptr, nullptr);
	if (m_window == nullptr)
	{
		std::cerr << "[ProDisplayManager] failed to create window!\n";
		glfwTerminate();
		return;
	}
	// Set OpenGL context as the current window object
	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "[ProDisplayManager] Failed to initialize GLEW!\n";
		return;
	}

	glViewport(0, 0, m_width, m_height);
	m_isClosed = false;

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

ProDisplayManager::ProDisplayManager(const int& width, const int& height, const char* title) :
	m_width(width), m_height(height)
{
	CreateWindow(title);
}

ProDisplayManager::~ProDisplayManager()
{
	Close();
	m_window = nullptr;
}