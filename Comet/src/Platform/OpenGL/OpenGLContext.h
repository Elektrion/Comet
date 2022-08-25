#pragma once

#include "Comet/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace comet {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* window_handle);

		virtual void init() override;
		virtual void swapBuffers() override;
	private:
		GLFWwindow* window_handle;
	};

}
