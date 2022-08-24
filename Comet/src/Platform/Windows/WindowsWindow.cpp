#include "cmt_pch.h"
#include "WindowsWindow.h"

#include "Comet/Event/WindowEvent.h"
#include "Comet/Event/KeyEvent.h"
#include "Comet/Event/MouseEvent.h"

namespace comet {

	WindowsWindow::WindowsWindow(const WindowProperties& props) {
		init(props);
	}

	WindowsWindow::~WindowsWindow() {
		shutdown();
	}

	void WindowsWindow::setVsync(bool vsync) {
		data.vsync = vsync;
		glfwSwapInterval(vsync ? 1 : 0);
	}

	void WindowsWindow::setMinimized(bool minimized) {
		data.minimized = minimized;
		if(minimized)
			glfwIconifyWindow(window);
		else
			glfwRestoreWindow(window);
	}

	void WindowsWindow::setMaximized(bool maximized) {
		data.maximized = maximized;
		if(maximized)
			glfwMaximizeWindow(window);
		else
			glfwRestoreWindow(window);
	}

	void WindowsWindow::onUpdate(Timestep dt) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void WindowsWindow::setEventCallback(EventCallbackFn callback) {
		data.event_callback = callback;
	}

	static int glfw_window_count = 0;

	static void glfwErrorCallback(int error, const char* description) {
		CMT_CORE_ERROR("glfw error: {0}, {1}", error, description);
	}

	void WindowsWindow::init(const WindowProperties& props) {
		if(glfw_window_count == 0) {
			int success = glfwInit();
			CMT_CORE_ASSERT(success == GLFW_TRUE, "Failed to initialize glfw!");
			glfwSetErrorCallback(glfwErrorCallback);
			glfw_window_count++;
		}

		window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
		CMT_CORE_ASSERT(window, "Failed to create the glfw window!");
		data.width = props.width;
		data.height = props.height;
		data.title = props.title;
		data.vsync = true;
		data.minimized = false;
		data.maximized = false;

		glfwSetWindowUserPointer(window, &data);

		// Window callbacks

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			WindowClosedEvent e;
			data->event_callback(e);
		});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data->width = uint32_t(width);
			data->height = uint32_t(height);

			WindowResizedEvent e{ data->width, data->height };
			data->event_callback(e);
		});

		glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified) {
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data->minimized = iconified == GLFW_TRUE;

			WindowMinimizedEvent e{ data->minimized };
			data->event_callback(e);
		});

		glfwSetWindowMaximizeCallback(window, [](GLFWwindow* window, int maximized) {
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data->maximized = maximized == GLFW_TRUE;

			WindowMaximizedEvent e{ data->maximized };
			data->event_callback(e);
		});

		// key callbacks

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			if(action == GLFW_PRESS) {
				KeyPressedEvent e{ uint32_t(key) };
				data->event_callback(e);
			}
			else if(action == GLFW_REPEAT) {
				KeyPressedEvent e{ uint32_t(key), true };
				data->event_callback(e);
			}
			else {
				KeyReleasedEvent e{ uint32_t(key) };
				data->event_callback(e);
			}
		});

		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint) {
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			KeyTypedEvent e{ codepoint };
			data->event_callback(e);
		});

		// mouse callbacks

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			if(action == GLFW_PRESS) {
				MouseButtonPressedEvent e{ uint32_t(button) };
				data->event_callback(e);
			}
			else {
				MouseButtonReleasedEvent e{ uint32_t(button) };
				data->event_callback(e);
			}
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent e{ int32_t(xpos), int32_t(ypos) };
			data->event_callback(e);
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent e{ int32_t(xoffset), int32_t(yoffset) };
			data->event_callback(e);
		});

		// create context first!
		setVsync(true);
	}

	void WindowsWindow::shutdown() {
		glfwDestroyWindow(window);
		window = nullptr;
		glfw_window_count--;

		if(glfw_window_count == 0) 
			glfwTerminate();
	}

}
