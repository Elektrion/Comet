#include "cmt_pch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>

namespace comet {

	OpenGLContext::OpenGLContext(GLFWwindow* window_handle) : window_handle(window_handle) {}

	void OpenGLContext::init() {
		glfwMakeContextCurrent(window_handle);

		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		CMT_CORE_ASSERT(status, "Failed to initialize glad!");

		CMT_CORE_INFO("OpenGL Info:");
		CMT_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CMT_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CMT_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::swapBuffers() {
		glfwSwapBuffers(window_handle);
	}

}
