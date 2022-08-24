#include "cmt_pch.h"
#include "WindowsWindow.h"

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

	void WindowsWindow::onUpdate(Timestep dt) {
		glfwSwapBuffers(window);
		glfwPollEvents();
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
		glfwSwapInterval(1);
	}

	void WindowsWindow::shutdown() {
		glfwDestroyWindow(window);
		window = nullptr;
		glfw_window_count--;

		if(glfw_window_count == 0) 
			glfwTerminate();
	}

}