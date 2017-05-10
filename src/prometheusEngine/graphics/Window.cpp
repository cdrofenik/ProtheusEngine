#include "prometheusengine\graphics\Window.h"

#include <iostream>

using namespace math;

namespace graphics {

	Window::Window(const char * title, const int & width, const int & height) :
		m_width(width), m_height(height)
	{
		if (!glfwInit()) {
			std::cerr << "[Window] Failed to initialize GLFW!\n";
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS compatibility
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Watchdog for bad coding habits

		m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
		if (m_window == nullptr)
		{
			std::cerr << "[Window] failed to create window!\n";
			glfwTerminate();
			return;
		}

		// Set OpenGL context as the current window object
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetWindowSizeCallback(m_window, resize_callback);


		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cerr << "[Window] Failed to initialize GLEW!\n";
			return;
		}

		std::cout << "[Window] OpenGL version: " << glGetString(GL_VERSION) << std::endl;

		glViewport(0, 0, m_width, m_height);
		
		glClearColor(0.2f, 0.0f, 0.7f, 0.0f);
		//glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}

	Window::~Window()
	{
		close();
		m_window = nullptr;
	}

	void Window::render()
	{
		glfwSwapBuffers(m_window);
	}

	void Window::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::close()
	{
		glfwTerminate();
	}

	int Window::getWidth()  const
	{
		return m_width;
	}

	int Window::getHeight()  const
	{
		return m_height;
	}

	GLFWwindow * Window::getWindow()  const
	{
		return m_window;
	}
	
	void resize_callback(GLFWwindow * window, int width, int height)
	{
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		w->m_width = width;
		w->m_height = height;
		glViewport(0, 0, width, height);
	}
}