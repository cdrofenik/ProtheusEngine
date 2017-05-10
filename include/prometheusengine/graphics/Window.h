#pragma once

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "core\math\Vector2.hpp"

#include <vector>

namespace graphics {

#define MAX_KEYS 1024
#define MAX_BUTTONS_M 8

	class Window
	{
	private:
		GLFWwindow* m_window;
		int m_width = 0;
		int m_height = 0;
	
	public:
		Window(const char* title, const int& width, const int& height);
		~Window();

		void render();
		void clear();
		void close();

		int getWidth()  const;
		int getHeight()  const;
		GLFWwindow* getWindow()  const;

	private:
		friend static void resize_callback(GLFWwindow* window, int width, int height);
	};
}