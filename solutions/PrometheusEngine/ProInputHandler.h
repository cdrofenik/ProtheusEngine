#pragma once

#include "GLFW\glfw3.h"

#include <vector>

class ProInputHandler
{
public:
	static void Init(GLFWwindow* window);
	static void Update();
	static void Dispose();

	static bool isKeyDown(int key);
	static bool isMouseButtonDown(int key);

private:
	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
	static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);

	static std::vector<int> m_keys;
	static std::vector<int> m_mouseButtons;
};

