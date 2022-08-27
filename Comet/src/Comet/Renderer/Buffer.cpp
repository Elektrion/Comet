#include "cmt_pch.h"
#include "Buffer.h"

#include "Comet/Renderer/RenderAPI.h"

#if defined(CMT_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLBuffer.h"
#elif defined(CMT_PLATFORM_MACOS)
#include "GLFW/glfw3.h"
#include "Platform/OpenGL/OpenGLContext.h"
#else
#error "Platform not supported!"
#endif

namespace comet {

	BufferLayout::Type BufferLayout::Type::FLOAT{ "FLOAT", 1, 4 };
	BufferLayout::Type BufferLayout::Type::FLOAT2{ "FLOAT2", 2, 8 };
	BufferLayout::Type BufferLayout::Type::FLOAT3{ "FLOAT3", 3, 12 };
	BufferLayout::Type BufferLayout::Type::FLOAT4{ "FLOA4T", 4, 16 };

	Ref<VertexBuffer> VertexBuffer::create() {
#if defined(CMT_PLATFORM_WINDOWS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return makeRef<OpenGLVertexBuffer>();
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
				return makeRef<OpenGLVertexBuffer>();
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#endif
		return Ref<OpenGLVertexBuffer>(nullptr);
	}

	Ref<IndexBuffer> IndexBuffer::create() {
#if defined(CMT_PLATFORM_WINDOWS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return makeRef<OpenGLIndexBuffer>();
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
				return makeRef<OpenGLIndexBuffer>();
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#endif
		return Ref<OpenGLIndexBuffer>(nullptr);
	}

}
