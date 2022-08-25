#pragma once

#include "GLFW/glfw3.h"

#include "Comet/Renderer/GraphicsContext.h"

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
