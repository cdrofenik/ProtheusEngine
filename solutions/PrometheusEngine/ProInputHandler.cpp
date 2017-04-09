#include "ProInputHandler.h"

#include <iostream>

std::vector<int> ProInputHandler::m_keys(GLFW_KEY_LAST);
std::vector<int> ProInputHandler::m_mouseButtons(GLFW_MOUSE_BUTTON_LAST);

void ProInputHandler::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	m_keys[key] = action;
}

void ProInputHandler::MouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	m_mouseButtons[button] = action;
}

 void ProInputHandler::MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (isMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
		 std::cout << "BUTTON 0 down and moving: " << xpos << " , " << ypos << std::endl;
	 }
}

bool ProInputHandler::isKeyDown(int key)
{
	return m_keys[key] == GLFW_PRESS || m_keys[key] == GLFW_REPEAT;
}

bool ProInputHandler::isMouseButtonDown(int key)
{
	return m_mouseButtons[key] == GLFW_PRESS;
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


