#include "cmt_pch.h"
#include "FrameBuffer.h"

#include "Comet/Renderer/RenderAPI.h"

#if defined(CMT_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
#elif defined(CMT_PLATFORM_MACOS)
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
#else
#error "Platform not supported!"
#endif

namespace comet {

	Ref<FrameBuffer> FrameBuffer::create(uint32_t width, uint32_t height) {
#if defined(CMT_PLATFORM_WINDOWS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return createRef<OpenGLFrameBuffer>(width, height);
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
				return createRef<OpenGLFrameBuffer>(width, height);
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#endif
		return nullptr;
	}

}
