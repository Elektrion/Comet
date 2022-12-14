#include "cmt_pch.h"
#include "GraphicsContext.h"

#include "Comet/Renderer/RenderAPI.h"

#if defined(CMT_PLATFORM_WINDOWS)
	#include "GLFW/glfw3.h"
	#include "Platform/OpenGL/OpenGLContext.h"
#elif defined(CMT_PLATFORM_MACOS)
	#include "GLFW/glfw3.h"
	#include "Platform/OpenGL/OpenGLContext.h"
#else
	#error "Platform not supported!"
#endif

namespace comet {

	Scope<GraphicsContext> GraphicsContext::create(void* window_handle) {
#if defined(CMT_PLATFORM_WINDOWS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return createScope<OpenGLContext>(static_cast<GLFWwindow*>(window_handle));
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#elif defined(CMT_PLATFORM_MACOS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return createScope<OpenGLContext>(static_cast<GLFWwindow*>(window_handle));
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#endif
		return nullptr;
	}

}
