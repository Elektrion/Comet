#include "cmt_pch.h"
#include "Comet/Core/Input.h"

#include "GLFW/glfw3.h"

#include "Comet/Core/Application.h"

namespace comet {

	bool Input::isKeyPressed(KeyCode key) {
		CMT_PROFILE_FUNCTION();

		return glfwGetKey(static_cast<GLFWwindow*>(Application::get()->getWindow()->getNativeWindow()), key) == GLFW_PRESS;
	}

	bool Input::isMouseButtonPressed(MouseCode button) {
		CMT_PROFILE_FUNCTION();

		return glfwGetMouseButton(static_cast<GLFWwindow*>(Application::get()->getWindow()->getNativeWindow()), button) == GLFW_PRESS;
	}

	std::pair<float, float> Input::getMousePosition() {
		CMT_PROFILE_FUNCTION();

		double x = 0;
		double y = 0;
		glfwGetCursorPos(static_cast<GLFWwindow*>(Application::get()->getWindow()->getNativeWindow()), &x, &y);
		return { float(x), float(y) };
	}

}
