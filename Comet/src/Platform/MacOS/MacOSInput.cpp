#include "cmt_pch.h"
#include "Comet/Core/Input.h"

#include "GLFW/glfw3.h"

#include "Comet/Core/Application.h"

namespace comet {

	bool Input::isKeyPressed(KeyCode key) {
		return glfwGetKey(static_cast<GLFWwindow*>(Application::get()->getWindow()->getNativeWindow()), key) == GLFW_PRESS;
	}

	bool Input::isMouseButtonPressed(MouseCode button) {
		return glfwGetMouseButton(static_cast<GLFWwindow*>(Application::get()->getWindow()->getNativeWindow()), button) == GLFW_PRESS;
	}

	glm::vec2 Input::getMousePosition() {
		double x = 0;
		double y = 0;
		glfwGetCursorPos(static_cast<GLFWwindow*>(Application::get()->getWindow()->getNativeWindow()), &x, &y);
		return { float(x), float(y) };
	}

}
