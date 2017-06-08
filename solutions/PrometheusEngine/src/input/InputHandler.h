#pragma once

#include "GLFW\glfw3.h"

#include "core\math\Precision.hpp"

#include <vector>

namespace input {

	class InputHandler
	{
	public:
		static void Init(GLFWwindow* window);
		static void Update();
		static void Dispose();

		static bool isKeyDown(int key);
		static bool isMouseButtonDown(int key);
		static bool getMousePositionChanged(math::Real& xPos, math::Real& yPos);

	private:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

		static std::vector<int> m_keys;
		static std::vector<int> m_mouseButtons;
		static math::Real m_xDistance;
		static math::Real m_yDistance;
		static bool m_mousePositionChanged;
		static bool m_firstMouse;
	};
}
