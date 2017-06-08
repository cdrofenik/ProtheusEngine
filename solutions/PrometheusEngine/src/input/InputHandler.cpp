#include "InputHandler.h"

#include <iostream>

using namespace math;

namespace input {

	std::vector<int> InputHandler::m_keys(GLFW_KEY_LAST);
	std::vector<int> InputHandler::m_mouseButtons(GLFW_MOUSE_BUTTON_LAST);
	Real InputHandler::m_xDistance = 0.0f;
	Real InputHandler::m_yDistance = 0.0f;
	bool InputHandler::m_mousePositionChanged = false;
	bool InputHandler::m_firstMouse = true;

	void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		m_keys[key] = action;
	}

	void InputHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		m_mouseButtons[button] = action;
	}

	double lastX;
	double lastY;

	void InputHandler::mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
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

	bool InputHandler::isKeyDown(int key)
	{
		return m_keys[key] == GLFW_PRESS || m_keys[key] == GLFW_REPEAT;
	}

	bool InputHandler::isMouseButtonDown(int key)
	{
		return m_mouseButtons[key] == GLFW_PRESS;
	}

	bool InputHandler::getMousePositionChanged(Real& xPos, Real& yPos)
	{
		xPos = m_xDistance;
		yPos = m_yDistance;
		if (m_mousePositionChanged) {
			m_mousePositionChanged = false;
			return true;
		}
		return false;
	}

	void InputHandler::Init(GLFWwindow* window)
	{
		glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
		glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, mouse_move_callback);
	}

	void InputHandler::Update()
	{
		glfwPollEvents();
	}

	void InputHandler::Dispose()
	{
		m_keys.clear();
		m_mouseButtons.clear();
	}



}