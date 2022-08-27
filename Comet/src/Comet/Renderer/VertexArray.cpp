#include "cmt_pch.h"
#include "VertexArray.h"

#include "Comet/Renderer/RenderAPI.h"

#if defined(CMT_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLVertexArray.h"
#elif defined(CMT_PLATFORM_MACOS)
#include "GLFW/glfw3.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#else
#error "Platform not supported!"
#endif

namespace comet {

    Ref<VertexArray> VertexArray::create() {
#if defined(CMT_PLATFORM_WINDOWS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return makeRef<OpenGLVertexArray>();
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
				return makeRef<OpenGLVertexArray>();
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#endif
		return Ref<OpenGLVertexArray>(nullptr);
    }

}
