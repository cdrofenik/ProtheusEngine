#pragma once

#include "GLFW\glfw3.h"

#include "core\math\Precision.hpp"

#include <vector>

class ProInputHandler
{
public:
	static void Init(GLFWwindow* window);
	static void Update();
	static void Dispose();

	static bool isKeyDown(int key);
	static bool isMouseButtonDown(int key);
	static bool getMousePositionChanged(math::Real& xPos, math::Real& yPos);

private:
	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
	static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);

	static std::vector<int> m_keys;
	static std::vector<int> m_mouseButtons;
	static math::Real m_xDistance;
	static math::Real m_yDistance;
	static bool m_mousePositionChanged;
	static bool m_firstMouse;
};

