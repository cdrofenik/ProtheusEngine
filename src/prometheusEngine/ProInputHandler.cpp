#include "ProInputHandler.h"

#include <iostream>

using namespace math;

std::vector<int> ProInputHandler::m_keys(GLFW_KEY_LAST);
std::vector<int> ProInputHandler::m_mouseButtons(GLFW_MOUSE_BUTTON_LAST);
Real ProInputHandler::m_xDistance = 0.0f;
Real ProInputHandler::m_yDistance = 0.0f;
bool ProInputHandler::m_mousePositionChanged = false;
bool ProInputHandler::m_firstMouse = true;

void ProInputHandler::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	m_keys[key] = action;
}

void ProInputHandler::MouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	m_mouseButtons[button] = action;
}

double lastX;
double lastY;

 void ProInputHandler::MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	 if (m_firstMouse)
	 {
		 lastX = xpos;
		 lastY = ypos;
		 m_firstMouse = false;
	 }

	m_xDistance = xpos - lastX;
	m_yDistance = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	m_mousePositionChanged = true;
}

bool ProInputHandler::isKeyDown(int key)
{
	return m_keys[key] == GLFW_PRESS || m_keys[key] == GLFW_REPEAT;
}

bool ProInputHandler::isMouseButtonDown(int key)
{
	return m_mouseButtons[key] == GLFW_PRESS;
}

bool ProInputHandler::getMousePositionChanged(Real& xPos, Real& yPos)
{
	xPos = m_xDistance;
	yPos = m_yDistance;
	if (m_mousePositionChanged) {
		m_mousePositionChanged = false;
		return true;
	}
	return false;
}

void ProInputHandler::Init(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

	glfwSetKeyCallback(window, KeyboardCallback);
	glfwSetMouseButtonCallback(window, MouseClickCallback);
	glfwSetCursorPosCallback(window, MouseMoveCallback);
}

void ProInputHandler::Update()
{
	glfwPollEvents();
}

void ProInputHandler::Dispose()
{
	m_keys.clear();
	m_mouseButtons.clear();
}


