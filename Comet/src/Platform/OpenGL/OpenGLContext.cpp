#include "cmt_pch.h"
#include "OpenGLContext.h"

#include "glad/glad.h"

namespace comet {

	void OpenGLContext::init() {
		CMT_PROFILE_FUNCTION();

		glfwMakeContextCurrent(window_handle);

		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		CMT_CORE_ASSERT(status, "Failed to initialize glad!");

		CMT_CORE_INFO("OpenGL Info:");
		CMT_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CMT_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CMT_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLContext::swapBuffers() {
		CMT_PROFILE_FUNCTION();

		glfwSwapBuffers(window_handle);
	}

	void OpenGLContext::setViewPort(int32_t x, int32_t y, uint32_t width, uint32_t height) {
		CMT_PROFILE_FUNCTION();

		glViewport(x, y, width, height);
	}

}
