#include "cmt_pch.h"
#include "Buffer.h"

#include "Comet/Renderer/RenderAPI.h"

#if defined(CMT_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLBuffer.h"
#elif defined(CMT_PLATFORM_MACOS)
#include "Platform/OpenGL/OpenGLBuffer.h"
#else
#error "Platform not supported!"
#endif

namespace comet {

	Ref<VertexBuffer> VertexBuffer::create() {
#if defined(CMT_PLATFORM_WINDOWS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return createRef<OpenGLVertexBuffer>();
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
				return createRef<OpenGLVertexBuffer>();
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#endif
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::create() {
#if defined(CMT_PLATFORM_WINDOWS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return createRef<OpenGLIndexBuffer>();
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
				return createRef<OpenGLIndexBuffer>();
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#endif
		return nullptr;
	}

}
