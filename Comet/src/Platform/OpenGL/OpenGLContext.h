#pragma once

#include "GLFW/glfw3.h"

#include "Comet/Renderer/GraphicsContext.h"

namespace comet {

	class OpenGLContext : public GraphicsContext {
	public:
		inline OpenGLContext(GLFWwindow* window_handle) noexcept : window_handle(window_handle) {}

		virtual void init() override;
		virtual void swapBuffers() override;
		virtual void setViewPort(int32_t x, int32_t y, uint32_t width, uint32_t height) override;
	private:
		GLFWwindow* window_handle;
	};

}
