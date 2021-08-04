#include "fepch.h"
#include "FoxEngine/Core/Input.h"
#include "FoxEngine/Core/Application.h"

#include <GLFW/glfw3.h>

namespace FoxEngine
{
	bool Input::isKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::isMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::getMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return std::make_pair(xPos, yPos);
	}

	float Input::getMouseX()
	{
		auto [x, y] = getMousePosition();
		return x;
	}

	float Input::getMouseY()
	{
		auto [x, y] = getMousePosition();
		return y;
	}
} 
