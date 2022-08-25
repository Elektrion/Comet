#include "cmt_pch.h"
#include "RenderAPI.h"

#if defined(CMT_PLATFORM_WINDOWS)
	#include "Platform/OpenGL/OpenGLRenderAPI.h"
#elif defined(CMT_PLATFORM_MACOS)
	#include "Platform/OpenGL/OpenGLRenderAPI.h"
#else
	#error "Platform not supported!"
#endif

namespace comet {

	RenderAPI::API RenderAPI::api = API::NONE;

	void RenderAPI::init() {
		api = API::OPENGL;
	}

	Scope<RenderAPI> RenderAPI::createRenderAPI() {
#if defined(CMT_PLATFORM_WINDOWS)
		switch(RenderAPI::getAPI()) {
			case API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case API::OPENGL:
				return makeScope<OpenGLRenderAPI>();
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#elif defined(CMT_PLATFORM_MACOS)
		switch(RenderAPI::getAPI()) {
			case API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case API::OPENGL:
				return makeScope<OpenGLRenderAPI>();
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#endif
		return Scope<RenderAPI>(nullptr);
	}

}
